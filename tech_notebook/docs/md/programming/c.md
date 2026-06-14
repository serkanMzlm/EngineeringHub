# C Programlama

## Veri Tipleri ve Bellek

Veri tiplerinin boyutu **kesin olarak sabit değildir**, derleyiciye ve mimariye (16/32/64-bit) göre değişebilir. Örnek olarak **32-bit sistemlerde** pointer'lar **4 byte** (32 bit) yer kaplar. **64-bit sistemlerde** pointer'lar **8 byte** (64 bit) yer kaplar.

- Bellek boyutunu garanti altına almak için **C99** ile gelen `<stdint.h>` kullanılır. (`int8_t, uint8_t` vb.)
- **File Scope (Global):** Fonksiyonların dışında tanımlanır. Tüm dosya tarafından görülebilir.
- **Block Scope (Local):** Küme parantezleri `{ }` içinde tanımlanır. Sadece o blok içinde yaşar.
- **Implicit Conversion (Dolaylı Dönüşüm):**  Derleyici, iki farklı veri tipi arasında otomatik olarak dönüşüm yapar
- **Explicit Conversion (Casting):** Programcının manuel olarak dönüşüm yapmasıdır. `int x = (int)y;`
- **Temel Veri Türleri:** `int`, `float`, `double`, `char`, `void`
- `const` verileri sabitlenmesi için kullanılır.
- `typedef`, var olan bir veri tipine yeni bir **takma isim (alias)** vermemizi sağlar. Derleyici arka planda yeni bir veri tipi yaratmaz; sadece senin verdiğin ismi gördüğü yerde orijinal tipe yönlendirme yapar.
    - `#define`**:** Bir ön işlemci (pre-processor) direktifidir. Sadece **"bul ve değiştir" (text replacement)** yapar. Tip kontrolü yapmaz, C'nin kapsam (scope) kurallarına uymaz.
    - `typedef`: Gerçek bir C deyimidir. Derleyici (compiler) tarafından işlenir. **Tip güvenliği (type safety)** vardır.
    
    ```c
    #define PTR_INT int*
    typedef int* t_ptr_int;
    
    // **p1 bir pointer olurken, p2 düz bir int değişkeni olur!** Bu çok sinsi bir hatadır.
    PTR_INT p1, p2; 
    
    // **hem p3 hem de p4 başarıyla birer pointer (int*)** olarak tanımlanır
    t_ptr_int p3, p4;  
    ```
    
- `volatile`, bir değişkenin değerinin program akışı dışında değişebileceğini derleyiciye bildirir ve bu değişken üzerinde bazı optimizasyonları engeller. Böylece değer her erişimde doğrudan bellekten okunur
- `__attribute__`, derleyiciye özel ek özellikler vermek için kullanılır. Bellek yerleşimini düzenleyebilir ve program başlamadan önce veya bittikten sonra çalışacak fonksiyonlar tanımlayabilir

```c
void __attribute__((constructor)) calledFirst(); // main'den önce çalışır
void __attribute__((destructor)) calledLast();   // main'den sonra çalışır
  
void main() { printf("main"); }
  
void calledFirst() { printf("constructor"); }
void calledLast()  { printf("destructor");  }
```

- `enum`, numaralandırmak için kullanılır. Başlangıç değeri **default olarak 0**’dan başlar.
- `union`, üyelerinin tamamı için ortak bir bellek alanı kullanır ve yalnızca en büyük üye kadar yer kaplar. Bu sayede bellek tasarrufu sağlar. Ancak bir üyede yapılan değişiklik, aynı bellek alanını kullanan diğer üyelerin değerlerini de etkiler.
- `struct`, farklı veri türlerini tek bir yapı altında toplar. Bellekte hizalama (alignment) nedeniyle yapının boyutu, üyelerin toplamından daha büyük olabilir. Eğer bu boşlukların oluşmasını istemiyorsak ve yapının tam gerekli boyutta yer kaplamasını istiyorsak `__attribute__((packed))` kullanılır.
    - `typedef`, bir veri tipine takma ad vermemizi sağlar. Böylece `struct` tanımları için her seferinde `struct` anahtar kelimesini kullanmadan, yerleşik bir tip gibi nesne oluşturabiliriz.

```cpp
typedef struct { // packed sayesinde 48 byte yerine 40 byte olur
  uint8_t a;
  uint16_t b;
  uint16_t b;
} __attribute__((packed)) Foo;

Foo f1 = {0};               // Tüm veriler 0
Foo f2 = {1, 2, 3};         // Tüm veriler 0
Foo f3 = {.a = 1, .c = 3};  //
Foo *pf;
pf->a = 12; // ya da *(pf).a = 12;
```

<aside>
💡

**Flexible Array Member (FAM)**

Bazı durumlarda bir `struct` içinde tutulacak veri miktarı derleme zamanında bilinmez ve çalışma sırasında belirlenir. C99 ile gelen **Flexible Array Member (FAM)** özelliği, bir yapının sonuna boyutu belirtilmemiş bir dizi ekleyerek değişken uzunluktaki verilerin aynı bellek bloğu içinde saklanmasını sağlar. Bu dizi sadecestruct’ın **son elemanı** olabilir.

```c
typedef struct {
    int len;
    char data[];
} Packet;

int n = 50;
struct Packet *p = malloc(sizeof(Packet) + n); // p->data artık 50 byte olur.
```

</aside>

- `sizeof`, bir veri tipi veya değişkenin bellekte kapladığı boyutu **byte cinsinden** döndürür. Veri tipi için `sizeof(int)`, değişken için ise `sizeof(a)` veya `sizeof a` şeklinde kullanılabilir. `sizeof` bir fonksiyon değil, derleme zamanında çalışan bir operatördür (`+, -, *, /`). Bu nedenle `sizeof(a++)` ifadesinde `a++` çalıştırılmaz; yalnızca `a`'nın türüne ait boyut hesaplanır.

```c
**agrc:** argument count
**agrv:** argument vectors

int my_variable_name;  // Snake Case
int myVariableName;    // Camel Case
int MyVariableName;    // Pascal Case

typedef unsigned char BYTE;
typedef unsigned int  WORD;
```

## Bit-Field

Bir `struct` içinde, değişken isimlerinin yanına `:` koyarak o değişkenin bellekte **tam olarak kaç bit** kaplayacağını biliriz.

- İşlemciler bellek adreslerini en az **Byte** seviyesinde referans gösterebilir. Bellekte bağımsız bir **"bitin"** adresi olamaz. Dolayısıyla `&` kullanılamaz. `&araba.led_durumu` yazarsan derleyici **"cannot take address of bit-field"** hatası fırlatır. Bu değişkenleri pointer'lar ile doğrudan gösteremezsin.
- Bit alanlarından oluşan bir dizi `araba.led_durumu[5]` oluşturulamaz.
- Bitlerin soldan sağa mı (Big-Endian) yoksa sağdan sola mı (Little-Endian) yerleştirileceği tamamen derleyiciye ve donanım mimarisine bağlıdır. Ham paketleri doğrudan bir Bit-Field struct'ına `memcpy` etmek tehlikelidir; bitlerin sırası ters dönebilir.
- **İsimsiz Bit Alanları (Padding Kontrolü):** Bazen donanım register'larında bazı bitler rezerve edilmiştir ve boş bırakılması gerekir. Bunu sağlamak için isimsiz bit alanları kullanabiliriz:

```c
struct Register {
    uint8_t active : 1;
    uint8_t        : 3; // İsimsiz 3 bitlik boşluk (Padding)
    uint8_t mode   : 4;
};

// Standart değişkenlerle yapsaydık en az uint8_t -> 24 bit olur.
// bit-field olduğu için 10 bit yer kaplar
struct AracKontrol {
    uint8_t led_durumu : 1;  // Açık / Kapalı -> Sadece 1 bit
    uint8_t far_modu   : 2;  // 00, 01, 10, 11 -> Sadece 2 bit
    uint8_t sicaklik   : 7;  // 0 ile 120 derece -> Sadece 7 bit 
};

// 2 byte olmasının nedeni led_durumu + far_modu = 3 bit **ilk byte** yerleşir ve 5 bit 
// sicaklik sığmadığı için boş (padding) bırakır. derleyici bu 7 bitlik değişkeni 
// bölmemek adına onu tamamen **ikinci byte'ın içine** yerleştirir.
sizeof(AracKontrol); // 2 byte
araba.far_modu = 4;  // 100 -> ilk iki bit alınır bu yüzden '0' olur.
```

<aside>
💡

**Bit-Field Overflow ve İşaret Tuzağı**

- `araba.far_modu`  değişken sadece 2 bitlik olduğu için, derleyici sağdan itibaren sadece ilk 2 biti alır (`00`) ve baştaki `1` bitini **kırpar (truncate eder)**. Sonuç tamamen `0` olur.
- Eğer veri tipini `unsigned` yerine düz `int` (yani signed) seçerseniz, işler çok daha karmaşık bir hal alır

```c
struct Tehlikeli { int durum : 1;};   // Sadece 1 bitlik SIGNED alan!

struct Tehlikeli t;
t.durum = 1; 
printf("%d\n", t.durum); // Çıktı 1 değil -1 olur.
```

- `signed` olarak tanımlanan bit alanlarında (bit-field) en soldaki bit işaret biti olarak değerlendirilir. Bu nedenle 1 bitlik bir `signed` alan yalnızca iki farklı değeri temsil edebilir: `0` ve `-1`.
- Donanım register'ları veya bit düzeyinde paket tasarımları yaparken, negatif sayılarla çalışacağınız kesin kılınmadığı sürece **HER ZAMAN `unsigned int` veya `uint8_t` / `uint32_t` kullanmalısınız.**
</aside>

## Endianness

Birden fazla byte kaplayan bir verinin, belleğe hangi byte sırasıyla yazılacağını belirleyen mimari kuraldır.

- **MSB (Most Significant Byte):** Çok baytlı bir veride en yüksek değeri taşıyan, yani en anlamlı byte'tır.
- **LSB (Least Significant Byte):** Çok baytlı bir veride en düşük değeri taşıyan, yani en değersiz byte'tır.

<aside>
💡

**Örnek 4 byte'lık hex bir sayı:** `int sayi = 0x12345678;`

1. **Little-Endian:** LSB en küçük adrese yazılır. 
    
    ```c
    0x00 adresi -> 78
    0x01 adresi -> 56
    0x02 adresi -> 34
    0x03 adresi -> 12
    ```
    
2. **Big-Endian:** MSB en küçük adrese yazılır.
    
    ```c
    0x00 adresi -> 12
    0x01 adresi -> 34
    0x02 adresi -> 56
    0x03 adresi -> 78
    ```
    

**Gerçek Hayatta Endianness Neden Patlar?**

Little-Endian sistem bu bitleri belleğe sıkıştırırken **Little-Endian** veya **Big-Endian** yazma sırasını kendi mimarisine göre belirler. İki sistem aynı olmazsa veya dönüşüm yapılmazsa bitler **tam ters sırayla** okunur

**Sistemin Big mi Little mı Endian olduğunu nasıl anlarsın?**

```c
unsigned int test = 1;    // Bellekte 4 byte: 0x00000001  
char *p = (char *)&test;  // ilk byte char pointer cast edilir.

// 0x00000001 -> Little endian: [01 00 00 00], Big endian: [00 00 00 01]
if (*p == 1) {
    printf("Sistem: Little-Endian\n"); 
} else {
    printf("Sistem: Big-Endian\n");
}
return 0;
```

</aside>

## Storage Classes

1. `auto`: Default yerel değişken sınıfıdır. `int x -> auto int x` Yazılmasına gerek yoktur. **Artık bir hükmü kalmamıştır.**
2. `register`, bir değişkenin mümkünse CPU register'larında tutulmasını derleyiciye önerir. `register` değişkenlerinin adresi alınamaz (`&` kullanılamaz). Günümüzde modern derleyiciler bu optimizasyonu çoğunlukla otomatik olarak yapmaktadır.
3. `static`
    1. **Fonksiyon İçinde:** Değişken block scope'a sahip olur  ama ömrü program sonlanana kadar devam eder. Fonksiyon her çağrıldığında eski değerini korur. Bellekte Stack yerine **Data Segment** (BSS veya Initialized Data) bölgesinde tutulur.
    2. **Global Seviyede (Dosya Seviyesinde):** Eğer bir global değişkenin veya fonksiyonun başına `static` koyarsan, o değişken/fonksiyon **sadece tanımlandığı `.c` dosyasına özel (private)** olur. Başka bir `.c` dosyası onu `extern` ile bile çağıramaz. İsim çakışmalarını önlemek için mükemmel bir yöntemdir.
4. `extern`: Bir değişkenin veya fonksiyonun "**başka bir dosyada tanımlandığını**" bildirmek için kullanılır. Bellekte yeni bir yer ayırmaz, sadece Linker'a yol gösterir.

## Overflow ve İşaret Bitinin Etkisi

Bilgisayarlar negatif sayıları **2'ye Tümleyen (Two's Complement)** yöntemiyle saklar. En soldaki bit (MSB), sayının işaretini belirler.

- `signed char` için maksimum değer `127`'dir. `127 + 1` işlemi taşmaya (**Signed Overflow**) neden olur ve sonucu C standardına göre **tanımsız davranıştır (Undefined Behavior)**. Pratikte birçok sistemde sonuç `-128` olarak görülür.
- `unsigned char` için ise maksimum değer `255`'tir. `255 + 1` işlemi sonrasında değer başa sarar ve sonuç kesin olarak `0` olur. Bu davranış C standardı tarafından tanımlanmıştır.

## Negatif Sayıları Bellekte Nasıl Tutar?

Bilgisayarlar negatif sayıları genellikle **Two’s Complement (2’ye tümleyen)** yöntemiyle temsil eder. Bu yöntemde bir sayının negatifi, bitleri ters çevrilip üzerine `1` eklenerek elde edilir.

Two’s Complement'in tercih edilme nedeni, toplama ve çıkarma işlemlerinin aynı donanımla gerçekleştirilebilmesidir. Böylece `5 - 3` işlemi doğrudan çıkarma yapmak yerine `5 + (-3)` şeklinde hesaplanır ve işlemci yalnızca toplama devresini kullanır.

<aside>
💡

**Neden Bu Yöntem?** 

Mantığı anlamak için **8 bitlik (1 Byte)** bir alan üzerinden somut bir örnek yapalım. Hedefimiz belleğe **`-5`** sayısını yazmak.

1. **Sayının Pozitif Halini Yaz (`+5`):** 8 bitlik alanda `+5` şöyledir: `00000101`
2. **Bitleri Ters Çevir (One's Complement):** Tüm 0'ları 1, 1'leri 0 yap: `11111010`
3. **Sonuca 1 Ekle (Two's Complement):** `11111010 + 1 = 11111011` → `-5` hex karşılığı `0xFB`

Şimdi bilgisayarın neden bu yöntemi sevdiğini görelim. `5 + (-5)` işlemini yaptıralım:

```json
   00000101  (+5)
+  11111011  (-5)
------------
  100000000  (Sonuç 9 bit çıktı!)
```

8 bitlik bir değişkende baştaki `1` eldesi (carry) sığmaz ve **dışarı taşar (discard edilir)**. Sonuç olarak `00000000` yani tam olarak **0**. Matematik ve donanım kusursuz bir şekilde uyuştu.

</aside>

## Bellek Hizalaması (Memory Alignment ve Padding)

32-bit veya 64-bit işlemciler bellekten veri okurken byte byte okumazlar. Belleği bloklar halinde okurlar. **32-bit işlemci belleği** her seferinde **4 byte** ve katları olarak okur. **64-bit işlemci belleği** her seferinde **8 byte** ve katları olarak okur. İşlemcinin tek seferde en verimli şekilde okuma yapabilmesi için, değişkenlerin bellekte kendi boyutlarının katı olan adreslere yerleşmesi gerekir. Buna **Alignment (Hizalama)** denir.

<aside>
💡

```c
struct Data {
    char c;  // 1 Byte -> [ c (1 Byte) ] [Pad] [Pad] [Pad] -> İlk 4 Byte
    int i;   // 4 Byte -> [ int i (4 Byte) ]               -> İkinci 4 Byte
};

// Kötü Tasarım (Boyut: 12 Byte)
struct Data1 {
    char a;    // 1 byte + 3 byte padding
    int b;     // 4 byte
    char c;    // 1 byte + 3 byte padding
};

// İyi Tasarım (Boyut: 8 Byte)
struct Data2 {
    int b;     // 4 byte
    char a;    // 1 byte
    char c;    // 1 byte + 2 byte padding (Struct'ın genel hizalaması için)
};
```

`Data` yapısındaki üyelerin toplam boyutu `5 byte` olmasına rağmen yapının boyutu `8 byte` olur. Bunun nedeni **alignment (hizalama)** kuralıdır. İşlemci, `int` gibi 4 byte'lık verileri 4'ün katı adreslerden okumayı tercih eder. Eğer `int`, `char`'ın hemen ardına (1. adrese) yazılsaydı, 4 byte'lık `int`'in bir kısmı ilk 4 byte'lık blokta, diğer kısmı ikinci 4 byte'lık blokta kalacaktı. İşlemci o `i`'yi okumak için belleğe iki kere gitmek zorunda kalacaktı (**Performans kaybı**).

Derleyici, `char c` ile `int i` arasına `3 byte`'lık **padding (doldurma)** ekleyerek `int` değişkenini uygun adrese hizalar. Böylece performans kaybı önlenmiş olur.

</aside>

## **Stack**

**Stack**, program çalışırken fonksiyon çağrılarının ve yerel değişkenlerin tutulduğu bellek bölgesidir. **LIFO (Last In, First Out)** mantığıyla çalışır; yani son eklenen veri ilk çıkar. İşlemci tarafından doğrudan yönetildiği için bellek erişimi oldukça hızlıdır.

Bir fonksiyon çağrıldığında, o fonksiyona ait parametreler ve yerel değişkenler stack üzerinde oluşturulur. Fonksiyon tamamlanıp `return` ettiğinde ise bu alan otomatik olarak temizlenir. Bu nedenle stack'teki verilerin ömrü, ait oldukları fonksiyonun çalışma süresiyle sınırlıdır.

Ancak stack'in boyutu sınırlıdır. Çok büyük yerel diziler tanımlamak veya kontrolsüz şekilde özyinelemeli (recursive) fonksiyonlar çağırmak stack alanının tükenmesine neden olabilir. Bu durumda program **Stack Overflow** hatası verir.

## **Heap**

**Heap**, programın çalışma sırasında ihtiyaç duyduğu belleği dinamik olarak ayırabildiği bellek bölgesidir. `malloc()`, `calloc()` ve `realloc()` gibi fonksiyonlarla ayrılan veriler burada tutulur. Stack'ten farklı olarak, heap'te oluşturulan verilerin ömrü bir fonksiyona bağlı değildir; ayrılan bellek, yazılımcı `free()` çağırana kadar kullanılmaya devam eder.

Bu esneklik büyük veri yapıları ve çalışma zamanında boyutu belirlenen veriler için avantaj sağlar. Ancak bellek yönetimi tamamen programcının sorumluluğundadır. Ayrılan belleğin serbest bırakılmaması **Memory Leak (Bellek Sızıntısı)** oluştururken, `free()` edilmiş bir belleğe erişmeye çalışmak ise **Dangling Pointer (Sarkan Gösterici)** gibi hatalara yol açabilir.

## Bağlı Listeler (Linked Lists)

Diziler bellekte ardışık yer kaplar. Bu yüzden araya bir eleman eklemek veya diziyi büyütmek çok maliyetlidir. **Bağlı Listeler** ise belleğin (Heap bölgesinin) tamamen darmadağınık yerlerinde yaşayan ama birbirlerinin adreslerini saklayarak bir tren gibi birbirine bağlanan yapılardır.

- Bir struct'ın kendi tipinden bir pointer barındırmasına **Self-Referential Struct** denir.

```c
struct Dugum {
    int veri;
    struct Dugum *sonraki; // **Self-Referential Struct**
};

// 1. Düğümleri oluştur (Heap'te yer ayır)
struct Dugum *ilk = (struct Dugum*)malloc(sizeof(struct Dugum));
struct Dugum *ikinci = (struct Dugum*)malloc(sizeof(struct Dugum));

// 2. İlk düğümün verisini yaz ve ikinciye bağla
ilk->veri = 10;
ilk->sonraki = ikinci; // İlk düğüm artık ikinci düğümün adresini biliyor!

// 3. İkinci düğümün verisini yaz ve listenin bittiğini ilan et
ikinci->veri = 20;
ikinci->sonraki = NULL; // Son düğümün 'sonraki' pointer'ı her zaman NULL olmalıdır!

// Belleği temizleme (Tersten free edilmelidir!)
free(ikinci);
free(ilk);
```

<aside>
💡

**Zinciri Koparmak (Memory Lost)**

Bir bağlı listede gezinirken veya aradan eleman silerken, eğer sileceğin elemanın işaret ettiği bir sonraki adresi (`node->sonraki`) geçici bir pointer'a yedeklemeden doğrudan o elemanı `free()` edersen, o elemandan sonra gelen tüm vagonların adresleri evrende kaybolur! Bellekte yaşarlar ama onlara ulaşacak hiçbir pointer kalmadığı için devasa bir sızıntı (leak) oluşur.

**Döngüsel Tuzak (Infinite Loops)**

Eğer yanlışlıkla bir düğümün `sonraki` pointer'ını kendisinden önceki bir düğüme bağlarsan, listede arama yapan veya listeyi ekrana basan fonksiyonun o döngünün içinde sonsuza kadar döner ve işlemciyi %100 yükte kilitler.

</aside>

## Queue Veri Yapısı

**FIFO - First In First Out** mantığıyla çalışan, tıpkı bir banka veya ekmek kuyruğu gibi işleyen doğrusal bir yapıdır. Eleman eklemeler kuyruğun **arkasından (Rear)** yapılırken, eleman çıkarmalar kuyruğun **önünden (Front)** yapılır.

# Bitwise Operators ve Operatörler

- Bitwise operatörler `&, |, ^, ~, <<, >>`, verinin tipine bakmaz direkt bitleri üzerinde işlem yapar.
- `&&` ve `||` **Mantıksal** operatörlerdir. Sonuçları sadece `true` / `false` olur. Bu operatörlerin Short-Circuit Evaluation özeliği vardır. Sonuç belli olduğu durumda sağ tarafa geçmez. `if(a && 5 / a)` koşulunda `a = 0`  sonuç direkt `false` döner `5/a` kısmına bakılmaz. (**`division by zero` hatası önlenmiş olur**)
- `,` tek bir ifadeye izin verilen her yerde birden fazla ifadeyi değerlendirmenize olanak tanır.
- Bir sayıyı sola 1 kez kaydırmak, o sayıyı **2 ile çarpmak** demektir. `n` kez kaydırmak `2^n` ile çarpmaktır.
- Bir sayıyı sağa 1 kez kaydırmak, o sayıyı **2'ye bölmek** (tam bölme) demektir.
- **`postfix** (i++)`  **`prefix (**++i)`

```c
unsigned char STATUS = 0b00000000;

STATUS = STATUS | (1 << 3);     // Setting a Bit
STATUS = STATUS & ~(1 << 3);    // Clearing a Bit
STATUS = STATUS ^ (1 << 3);     // Toggling a Bit

if (STATUS & (1 << 3))          // Checking a Bit (3. bit 1 mi?)
```

# Koşul ve Döngüler

- **Koşullar:** `if-else, switch-case, ?:, goto`
- **Döngüler:** `for, while, do - while`
- `break` döngüyü sonlandırır. `continue` bir sonraki iterasyona geçer. `return` Fonksiyondan çıkar.

```c
if(printtf("Hello World")){}  // ";" kullanılmadan çıktı oluşturur. (Bir kez)
while(printtf("Hello World")) // ";" kullanılmadan çıktı oluşturur. (Sonsuz)
```

<aside>
💡

**Jump Table Nasıl Çalışır?**

Derleyici eğer case değerleri **düzenli ve yakın aralıklıysa**: `case` adreslerini içeren gizli bir pointer dizisi oluşturur. `mod` değişkeninin değeri doğrudan bu dizinin indeksi olarak kullanılır.

Yani işlemci sırayla tüm şartları kontrol etmek yerine, tek bir hamlede (`O(1)`) gereken kod satırına atlar.

**Kritik Sınır:** Eğer `case` değerleri çok dağınıksa (örneğin `case 1:`, `case 1500:`, `case 90000:`), derleyici bir tablo oluşturamaz çünkü bellek israfı olur ve kod arka planda tekrar yavaş çalışan `if-else` mantığına geri döner.

**`break` Unutma Tuzağı (Fall-Through):** Bir `case` bloğunun sonuna `break;` koymazsanız, kod bir sonraki `case`'in içine de girer. Modern C'de eğer bunu bilinçli yapıyorsan, derleyici uyarısı almamak için `[[fallthrough]];` özniteliğini (C23 standardı) eklemek iyi bir alışkanlıktır.

**Cache Locality (Önbellek Uyumluluğu) ve Döngü Sırası**

İki boyutlu bir diziyi tararken döngülerin sırası performansı tamamen değiştirebilir. C dilinde çok boyutlu diziler bellekte **satır satır (Row-Major)** saklanır.

```c
for (int i = 0; i < 1000; i++) { // MÜHENDİSLİK HARİKASI (Hızlı - Cache Friendly)
    for (int j = 0; j < 1000; j++) {
        matris[i][j] = 0; // Bellekte yan yana olan hücrelere sırayla erişir.
    }
}

for (int j = 0; j < 1000; j++) { // PERFORMANS FELAKETİ (Yavaş - Cache Miss)
    for (int i = 0; i < 1000; i++) {
        matris[i][j] = 0; // Bellekte sürekli uzak adreslere zıplar. 
									        // Cache sürekli boşalır.
    }
}
```

</aside>

# IO

### Standart IO

- `sprintf`, `char` türünde bir diziye formatlanmış veri yazmak için kullanılır. `printf` fonksiyonunun yaptığı işin benzerini yapar, ancak çıktıyı ekrana yazdırmak yerine bir karakter dizisine yazar.
- `sscanf`, bir karakter dizisini belirtilen formatla analiz eder ve veri çıkarır. `scanf` fonksiyonunun karakter dizisi versiyonudur.

```c
char buffer[100];
int num1 = 42, num2 = 25;
sprintf(buffer, "Sayılar: %d %d", num1, num2);
sscanf(buffer, "Sayım: %d %d", &num1, &num2);

char num[] = "42 65 78", text[30];
sprintf(text, "Ali %d", 10);            // Belirlenen text içine yazılmasını sağlar
sscanf(num, "%d %d %d", &a, &b, &c); 

printf("%2f, %-2f", number, number);     // Sağa / sola hizalanır.
printf("%+.3f", number);                 // Pozitif sayılara '+' koyar.
printf("%*.*f", 2, 3, number);           // '*' verilerin dışardan doldurulmasını sağlar.
printf("%#x", number);                   // '#' sayıların 0x şeklinde yazılmasını sağlar.
printf("%05x", number);                  // '0' boşluklara 0 koyulmasını sağlar.
```

### Dosya İşlemleri

C dilinde bir dosyayı açarken derleyiciye onun bir `Text` mi yoksa `Binary` mi olduğunu söyleriz. Görünüşte ikisi de diskteki byte yığınlarıdır, ancak arka planda işletim sisteminin bu byte'ları yorumlama biçimi farklıdır:

- **Metin (Text) Modu (`"r"`, `"w"`):** Veriler karakter karakter (`char`) okunur ve yazılır. En kritik fark satır sonu karakterlerinde ortaya çıkar. Örneğin, Windows sistemlerinde satır sonu `\r\n` (Carriage Return + Line Feed) iken, Linux'ta sadece `\n`'dir. Text modunda C kütüphanesi bu dönüşümleri arka planda otomatik yönetir.
- **Ham Veri (Binary) Modu (`"rb"`, `"wb"`):** Disk üzerindeki byte'lara **hiç dokunulmaz**, işletim sistemi araya girip satır sonu çevirisi yapmaz. RAM'deki bir `struct` veya `int` dizisi aynen, bit bit diske kopyalanır. Taşınabilir (portable) ve yüksek performanslı gömülü sistem uygulamalarında her zaman tercih edilir.

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("veri.txt", "w"); // "w": Yazma modunda aç (varsa sıfırlar)
    
    if (fp == NULL) // Dosya Açılamadı
        return -1;
    
    // İşlemler...
    
    fclose(fp); // Kaynağı sisteme geri ver
    return 0;
}
```

- **`fseek(fp, offset, origin);`**: İmleci istediğimiz yere taşır.
    - `SEEK_SET`: Dosyanın en başından itibaren `offset` kadar git.
    - `SEEK_CUR`: İmlecin o an bulunduğu yerden itibaren `offset` kadar git.
    - `SEEK_END`: Dosyanın sonundan itibaren geriye/ileriye git.
- **`ftell(fp);`**: İmlecin o anda dosyanın kaçıncı byte'ında olduğunu döndürür.

### İleri Düzey Hata Yönetimi ve Savunma Odaklı Programlama

C dilinde yerleşik bir `try-catch` mekanizması yoktur, ancak elimizde donanım ve işletim sistemi seviyesinde hataları yakalayan çok güçlü araçlar vardır.

C standart kütüphanesindeki birçok fonksiyon (özellikle matematik ve dosya I/O fonksiyonları), bir hata oluştuğunda işletim sistemi tarafından set edilen global bir tam sayı değişkenine sinyal bırakır. Bu değişkenin adı **`errno`**'dur.

- `ENOENT` (Error No Entry): Dosya veya dizin bulunamadı.
- `EACCES` (Error Permission Denied): İzin hatası (Yetkisiz erişim).
- `ENOMEM` (Error No Memory): RAM'de yeterli yer kalmadı.

`assert`, kodun çalışması esnasında **"kesinlikle doğru olması gereken"** varsayımları kontrol etmek için kullanılır. Eğer `assert` içine yazılan koşul yanlış (`0`) çıkarsa, program o saniye çalışmayı durdurur ve hangi dosyada, hangi satırda patladığını ekrana basar.

<aside>
💡

`assert` harika bir test aracıdır ancak production çıkacak kodda performans kaybı yaratmaması istenir. Kodun en başına `#define NDEBUG` makrosunu koyarsan, ön işlemci kodun içindeki tüm `assert` satırlarını **tek hamlede siler**. Kod sıfır maliyetle production hazır hale gelir.

</aside>

# Pointer

- Bir değişken bellekte bir değer saklar. Pointer ise içinde bellek adresi saklar.
- **Call by Value / Call by Reference**
- **`&` (Address-of) Operatörü:** Bir değişkenin RAM'deki adresini verir.
- **`*`(Dereferencing / De-referans) Operatörü:** Pointer'ın işaret ettiği adrese gidip, o adresteki **değeri** okumamızı veya değiştirmemizi sağlar.

```c
int x = 10;
int *p = &x; // p artık x'in adresini tutuyor.
```

<aside>
💡

**Neden Her Tipin Kendi Pointer'ı Var?**

Eğer pointer sadece bir adres tutuyorsa ve 64-bit bir sistemde tüm adresler 8 byte ise, neden düz bir `pointer` tipi yok da `int*`, `char*`, `double*` gibi ayrımlar var?

`*p` diyerek o adrese gittiğimizde, o adresten itibaren **kaç byte okuyacağımızı ve o bitleri nasıl yorumlayacağımızı** derleyicinin bilmesi gerekir.

- `char *cp` ise: Gittiği adresten itibaren **1 byte** okur.
- `int *ip` ise: Gittiği adresten itibaren **4 byte** okur.
</aside>

- Pointer'lar ile matematiksel işlemler yapabiliriz (`+`, `-`, `++`, `--`). Ancak bu matematik normal matematikten farklıdır. **Pointer aritmetiği, işaret ettiği veri tipinin boyutuna (`sizeof`) göre ölçeklenir.**
    
    ```c
    int dizi[3] = {10, 20, 30};
    int *p = &dizi[0]; // p, dizinin ilk elemanının adresi (örn: 0x1000)
    
    // p + 1 -> "Beni bellekte **1 tane int boyutu kadar (sizeof(int))** ileri götür" 
    p++; // **0x1000 +** **sizeof(int) =** **(0x1004)**
    ```
    

## Diziler

Dizinin **ilk elemanının başlangıç adresini gösteren sabit bir pointer'dır**. Derleyici arka planda dizi indeksleme köşeli parantezlerini `dizi[i]` gördüğünde, bunu doğrudan pointer aritmetiğine çevirir: `dizi[i] = *(dizi +i)` bu yüzden `dizi[index]` ve `index[dizi]` eşdeğerdir. (`*(dizi + index)`) bunun sebebi toplama işleminde yer değiştirme olabilmesidir.

```c
int dizi[5] = {10, 20, 30, 40, 50};

// Aşağıdaki iki ifade birbirine tamamen eşittir:
int *p1 = dizi;       
int *p2 = &dizi[0];

// Aşağıdaki iki ifade birbirine tamamen eşittir:
printf("%d", dizi[2])
printf("%d", 2[dizi])
```

## String (Metin)

C dilinde yerleşik bir **string** veri tipi yoktur. Metinler, `char` dizileri olarak tutulur ve dizinin sonu özel bir karakter olan **`\0` (Null Terminator)** ile belirtilir. Bu karakter, string'in nerede bittiğini gösterir.

1. **String Tanımlamalarındaki Sinsi Fark (Stack vs Read-Only Data):** C'de bir metni iki farklı şekilde tanımlayabilirsin. Görünüşte aynı işi yaparlar ama bellekte ikamet ettikleri yerler tamamen farklıdır:
    
    ```c
    char str1[] = "Hello";  // Yöntem A: Stack bölgesinde dizi
    char *str2 = "Hello";   // Yöntem B: Read-Only Data bölgesinde literal
    ```
    
    - **`str1` (Dizi):** "Hello" karakterleri (ve gizli `\0`), fonksiyonun **Stack** alanındaki bir diziye kopyalanır. Bu dizinin elemanlarını istediğin gibi değiştirebilirsin: `str1[0] = 'M';` geçerlidir.
    - **`str2` (Pointer):** "Hello" metni, belleğin değiştirilemez olan **Read-Only Data (veya Text) Segment** bölgesine yazılır. `str2` pointer'ı ise sadece oranın adresini tutar. Eğer `str2[0] = 'M';` dersen, salt okunur bir bellek bölgesine yazmaya çalıştığın için programın anında **Segmentation Fault** vererek çöker!
    - String pointer ile göstereceksen, yanlışlıkla değiştirmeye çalışıp programı çökertmemek için her zaman `const` ile tanımlamalısın: `const char *str2 = "Hello";`
2. **String Fonksiyonlarının:**
    1. **`strcpy(dest, src);`**: `src` string'ini `dest` alanına kopyalar. Ancak `dest` dizisinin boyutunun buna yetip yetmediğine **asla bakmaz**. Eğer hedef alan 5 byte, gelen veri 10 byte ise, `strcpy` hedef sınırını aşar ve yan taraftaki diğer değişkenlerin, hatta fonksiyonun geri dönüş adreslerinin (return address) üzerine yazar.
    2. **`strncpy(dest, src, n);`**: En fazla `n` byte kopyalayarak sınırı korur. Güvenlidir.
    3. `memset()` Bir bellek bölgesinin tüm byte'larını belirli bir değerle doldurmak (genellikle sıfırlamak) için kullanılır.
    4. `memcpy()` Bir bellek bölgesindeki ham byte'ları, başka bir bellek bölgesine doğrudan kopyalar.
    5. `memmove()` `memcpy` ile aynı işi yapar. Ancak çok kritik bir farkı vardır: **Bellek Bölgelerinin Çakışması (Memory Overlap)**. Eğer kopyalama yapacağın hedef adres ile kaynak adres bellekte üst üste biniyorsa (overlap varsa), `memcpy` kullanmak tanımsız davranışa (UB) yol açar ve veri bozulur. `memmove` ise önce veriyi geçici bir tampon bölgeye alır, ardından hedefe yazar. Bu sayede çakışan bellek alanlarında bile güvenle kopyalama yapar.
    6. `strlen`: Dizinin içindeki karakterleri `\0` görene kadar tek tek sayar (Runtime)
    
    ```c
    char text[100] = "C Language";
    printf("%zu\n", sizeof(text)); // Çıktı: 100 (Bellekte ayrılan yer)
    printf("%zu\n", strlen(text)); // Çıktı: 10 (Görünen karakter sayısı)
    ```
    

## Generic Pointer

Bazen bir pointer'ın hangi veri tipini göstereceğini önceden bilemeyiz (Örneğin `malloc` fonksiyonu bellekte yer ayırır ama oraya `int` mi `char` mi koyacağını bilmez). Bu durumlarda **`void*`** kullanılır.

- `void*` tipindeki bir pointer'a **herhangi bir tipteki adres** doğrudan atanabilir.
- **Kritik Kural:** `void*` pointer'lar doğrudan de-referans edilemez (`*p` denemez) ve üzerinde adres aritmetiği yapılamaz. Çünkü derleyici o adreste kaç byte olduğunu bilmemektedir. Kullanılmadan önce mutlaka istenen tipe cast edilmelidir

```c
int a = 5;
void *vptr = &a; // Sorunsuz

// printf("%d", *vptr); // HATA! Derleyici tipi bilmiyor.
printf("%d", *(int*)vptr); // DOĞRU: Önce int*'a çevirdik, sonra içini okuduk.
```

## `const int *p` vs `int *const p`

`const` anahtar kelimesinin pointer tanımlamasında nereye yazıldığı, neyin değiştirilemeyeceğini (salt okunur olacağını) belirler.

<aside>
💡

**Tersinden Okuma (Sağdan Sola Okuma) Tekniği**

`const int *p;` (Pointer to Constant) → **Sağdan Sola Oku** `p` is a pointer to `int` which is `const`. (p, sabit bir int'e işaret eden bir pointer'dır). **Anlamı:** İşaret edilen adresteki **veri (değer) sabittir**, değiştirilemez. Ancak pointer'ın kendisi serbesttir, **başka bir adresi gösterebilir**.

```c
int x = 10, y = 20;
const int *p = &x;

// *p = 15;  // HATA! İşaret edilen değer değiştirilemez.
p = &y;      // GEÇERLİ! Pointer başka bir adrese bakabilir.
```

`int *const p;` (Constant Pointer) **→ Sağdan Sola Oku:** `p` is a `const` pointer to `int`. (p, bir int'e işaret eden sabit bir pointer'dır). **Anlamı:** Pointer'ın **içindeki adres sabittir**, bir kere bağlandıktan sonra başka bir adresi gösteremez. Ancak o adresteki **veriyi (değeri) değiştirebilirsiniz**.

```c
int x = 10, y = 20;
int *const p = &x;

*p = 15;     // GEÇERLİ! Adresteki değer değiştirilebilir.
// p = &y;   // HATA! Pointer artık başka bir adrese taşınamaz.
```

`const int *const p;` (Constant Pointer to Constant)→Hem içindeki adres sabittir hem de işaret ettiği adresteki değer sabittir. Tam koruma sağlar.

</aside>

## Pointer to Pointer

Bir pointer da nihayetinde bellekte yer kaplayan bir değişkendir ve onun da bir RAM adresi vardır. Bir pointer'ın adresini tutan başka bir pointer'a **Pointer to Pointer (Çift Gösterici)** denir.

```c
int x = 5;
int *p = &x;   // p -> x'in adresini tutuyor
int **pp = &p; // pp -> p pointer'ının kendi adresini tutuyor
```

## Dinamik Bellek Yönetimi

**`malloc()` (Memory Allocation):** İstenen boyutta (**byte cinsinden**) bellekte ardışık bir alan ayırır ve bu alanın başlangıç adresini `void*` olarak döndürür. Bellek ayırma işlemi başarısız olursa `NULL` döndürür. Ayırdığı bellek bölgesini sıfırlamaz; bu nedenle belleğin içeriğinde daha önce bulunan **garbage değerler** yer alabilir.

**`calloc()` (Contiguous Allocation):** Parametre olarak **eleman sayısı** ve **her elemanın boyutunu** alarak bellek ayırır. `malloc()`'tan farklı olarak, ayırdığı bellek bölgesindeki tüm byte'ları **0** ile başlatır. Bu nedenle başlangıçta temiz bir bellek sağlar, ancak sıfırlama işlemi nedeniyle `malloc()`'a göre küçük bir ek maliyeti vardır.

**`realloc()` (Re-allocation):** `malloc()` veya `calloc()` ile ayrılmış bir bellek bloğunun boyutunu değiştirmek için kullanılır. Bellek alanı büyütülebilir veya küçültülebilir. Eğer mevcut bloğun yanında yeterli boş alan varsa, boyut aynı yerde değiştirilir. Aksi durumda, sistem yeni bir bellek alanı ayırır, mevcut verileri bu alana kopyalar, eski alanı serbest bırakır ve yeni adresi döndürür.

**`free()`:** Heap bölgesinden aldığın her byte bellek, işletim sistemine borçtur. İşin bittiğinde o adresi sisteme geri iade etmek zorundasın. `free(p);` dediğinde o bellek alanı artık boşa çıkar.

```c
int n = 10;

int *ptr_1 = malloc(n * sizeof(int)); // n * 4 byte yer ayrıldı (İçerisi çöp dolu)
int *ptr_2 = calloc(n, sizeof(int));

if(ptr_1 == NULL || ptr_2 == NULL)
    return -1;

int *ptr_3 = realloc(ptr_2, 10 * sizeof(int));

for(int i = 0; i < n; i++)
{
    ptr_1[i] = i * 10;
}

free(ptr_1);
free(ptr_2);
free(ptr_3);
```

<aside>
💡

**Dikkat Edilmesi Gereken Konular**

1. **Memory Leak (Bellek Sızıntısı):** Ayırdığın belleği `free()` etmeden, o belleği gösteren pointer'ı kaybedersen (örneğin pointer'a başka adres atarsan veya fonksiyon biterse), o bellek program kapanana kadar RAM'de kilitli kalır. 7/24 çalışan bir sunucu yazılımında bu hata zamanla RAM'in tükenmesine ve sistemin çökmesine neden olur.
2. **Dangling Pointer (Sarkan Gösterici):** Bir pointer'ın gösterdiği alanı `free()` ettikten sonra, pointer'ın içini temizlemezsen o pointer hala eski adresi göstermeye devam eder. O adrese tekrar erişmeye çalışırsan program patlar. (`free(p);` işleminden hemen sonra **`p = NULL;`** yapmak hayat kurtarır.)
3. **`realloc` Tuzağı:** `realloc` başarısız olursa (RAM'de yer kalmadıysa) `NULL` döndürür. Eğer kodu şöyle yazarsan `p = realloc(p, 10000);` `realloc` başarısız olduğunda `p`'ye `NULL` atanır ve senin eski `p` adresin kaybolur. Böylece hem veri gider hem de bellek sızıntısı oluşur. Doğrusu geçici bir pointer kullanmaktır.
</aside>

### Fonksiyon Göstericileri (Function Pointers)

C dilinde fonksiyonların da bellekte bir adresi vardır. **Fonksiyon göstericileri (Function Pointers)**, bu adresleri tutan göstericilerdir. Böylece fonksiyonlar veri gibi taşınabilir, başka fonksiyonlara parametre olarak gönderilebilir ve çalışma zamanında hangi fonksiyonun çağrılacağı dinamik olarak belirlenebilir. Bu yapı, özellikle **callback** mekanizmaları ve esnek yazılım mimarileri oluşturmak için kullanılır.

```c
int topla(int a, int b) { return a + b; }
int cikar(int a, int b) { return a - b; }
int carp(int a, int b)  { return a * b; }

// Bu fonksiyonun parametre listesini okumak zor:
int compute1(int (*op)(int, int), int x, int y) {
    return op(x, y);
}

// Bu fonksiyonun parametre listesini okumak zor:
// typedef kullanılarak daha düzenli ve anlaşılır yapı
typedef int (*IslemPtr)(int, int);
int compute2(IslemPtr op, int x, int y) {
    return op(x, y);
}

int main(void) {
    // Fonksiyon göstericisi tanımı: fonksiyonun imzası ile aynı olması lazım. 
    //                               **(return type, parametre sayısı, parametre tipleri)**
    int (*fp)(int, int); 
    fp = topla;                 // topla fonksiyonunun adresini fp'ye atadık.

    // İki yöntem de geçerlidir
    int sonuc1 = fp(5, 3);
    int sonuc2 = (*fp)(10, 20);
    printf("Sonuc: %d\n", sonuc1);
    
    // 3 elemanlı bir fonksiyon göstericisi dizisi tanımlıyoruz:
    int (*islem_tablosu[3])(int, int) = {topla, cikar, carp};
    int secim = 2; // Diyelim ki kullanıcı 'carp' işlemine denk gelen 2'yi seçti
    
    // Devasa bir switch-case yapmadan, doğrudan ilgili fonksiyona zıplıyoruz:
    int sonuc = islem_tablosu[secim](10, 5); 
    
    printf("Sonuc: %d\n", sonuc); // Çıktı: 50
    
    printf("%d\n", compute1(topla, 5, 3));
    printf("%d\n", compute1(cikar, 5, 3));
}
```

# Önişlemci Komutları (#)

Ön İşlemci saf bir **"Metin Düzenleyicidir" (Text Processor)**. Sadece `#` ile başlayan satırları okur, kodun üzerinde kesme biçme yapıştırma işlemleri yapar ve saf C kodunu derleyiciye teslim eder.

- `#define` sembolik isimler atanması için kullanılır. Değişkenlerin önüne boş bir **`#define`** koyarak, o değişkenin kullanım amacı hakkında bilgi verilebilir. `#define` bellek kısmında alan tutmaz derleme sırasında otomatik olarak düzeltilir.
- Derleme öncesi (**Preprocessing**) metin düzenleme aşamasıdır.
- Kütüphane ekleme (`#include`), makro tanımlama (`#define`) yapar.
- **Include Guard** yapılması sağlanır
- Makroya gönderilen bir argümanın başına `#` koyarsan, ön işlemci o argümanı çift tırnak içine alarak bir **string literal** haline getirir.
- `##` İki farklı kelimeyi veya simgeyi arka planda birleştirerek **tek bir yeni değişken/fonksiyon ismi** oluşturmamızı sağlar. Kod üreten kod yazarken kullanılır.
- **Predefined Macros (Hazır Derleyici Makroları):**
    - `__FILE__` : O an çalıştırılan kaynak kod dosyasının adını (string) verir.
    - `__LINE__` : O anki satır numarasını (int) verir.
    - `__DATE__` : Derlemenin yapıldığı tarihi (string) verir.
    - `__TIME__` : Derlemenin yapıldığı saati (string) verir.

```c
// Donanim.h dosyası
#ifndef DONANIM_H
#define DONANIM_H
// ya da direkt olarak 
#pragma once

#define __MUTLAK_SONUC__    //boş define 
#define PRINT_DEBUG(degisken) printf(#degisken " değişkeninin değeri: %d\n", degisken)
// Dinamik olarak değişken ismi üreten makro
#define DEGISKEN_YARAT(id) int kullanici_##id = id

#define LOG_ERROR(mesaj) printf("[HATA] Dosya: %s, Satır: %d -> %s\n", \
																									__FILE__, __LINE__, mesaj)

int __MUTLAK_SONUC__ degisken;

void test(void)
{
	int sensor_isi = 45;
    PRINT_DEBUG(sensor_isi);
    DEGISKEN_YARAT(5); // Ön işlemci bunu 'int kullanici_5 = 5;' haline getirir.
   
    printf("%d\n", kullanici_5); // Çıktı: 5
     
    LOG_ERROR("Kritik donanim dosyasi eksik!");
		
}

#endif // DONANIM_H
```

# Fonksiyonlar

C dilinde **fonksiyonlar (functions)**, belirli bir görevi yerine getiren ve gerektiğinde tekrar kullanılabilen kod bloklarıdır. Ancak fonksiyonlar yalnızca kodu düzenlemek için değil, işlemci ve bellek seviyesinde belirli kurallarla yönetilen **alt programlar (subroutines)** olarak da düşünülebilir.

Bir fonksiyon çağrıldığında işlemci, mevcut kod akışını geçici olarak durdurur ve fonksiyonun bulunduğu adrese gider. Bu süreç sırasında fonksiyona ait bilgiler **Stack** üzerinde oluşturulan bir **Stack Frame** içinde saklanır. Fonksiyon parametreleri, yerel değişkenler ve geri dönüş adresi bu yapının içinde tutulur.

Fonksiyon çağrısı sırasında genel olarak şu adımlar gerçekleşir:

1. Fonksiyona gönderilen argümanlar uygun register'lara veya stack'e yerleştirilir.
2. Fonksiyon tamamlandığında dönülecek adres (**Return Address**) saklanır.
3. İşlemci, fonksiyonun başlangıç adresine atlayarak kodu çalıştırır.
4. Yerel değişkenler için stack üzerinde alan ayrılır.
5. Fonksiyon sona erdiğinde stack frame kaldırılır.
6. Saklanan geri dönüş adresi okunur ve program kaldığı yerden çalışmaya devam eder.

Bu mekanizma sayesinde fonksiyonlar birbirlerini çağırabilir ve program akışı güvenli bir şekilde yönetilebilir.

**Recursion Fonksiyonlar:** Bir fonksiyonun kendi kendini çağırması durumudur.

**Variadic Functions:** Değişken sayıda parametre alan fonksiyonlardır.

### `inline` Fonksiyonlar

Küçük fonksiyonların çok sık çağrılması, her çağrıda oluşan **fonksiyon çağrı maliyetine (Function Call Overhead)** neden olabilir. Bu maliyet; parametrelerin hazırlanması, geri dönüş adresinin saklanması ve stack frame oluşturulması gibi işlemlerden kaynaklanır.

`inline` anahtar kelimesi, derleyiciye fonksiyon çağrısı yapmak yerine fonksiyonun içeriğini çağrıldığı noktaya yerleştirmesini önerir. Böylece fonksiyon çağrı maliyeti ortadan kalkabilir ve performans artışı sağlanabilir.

Makrolardan farklı olarak `inline` fonksiyonlar:

- Tip kontrolüne sahiptir.
- Derleyici tarafından denetlenir.
- Daha güvenli ve okunabilir kod yazılmasını sağlar.

Bu nedenle küçük ve sık kullanılan fonksiyonlarda `inline` kullanımı tercih edilebilir.

```c
#include <stdio.h>
#include <stdarg.h>

int kare_al(int x);  // Prototip (Declaration)

int kare_al(int x) { // Tanımlama (Definition)
    return x * x;
}

inline int max(int a, int b) {
    return (a > b) ? a : b;
}

/*
faktoriyel(5) -> faktoriyel(4) -> faktoriyel(3)... 
Bellekte peş peşe 5 tane Stack Frame açılır ve bekletilir.
**Tehlike:** Koşul yanlış yazılırsa **Stack Overflow** olur ve sistem çöker.
*/
int faktoriyel(int n) {
    if (n <= 1) return 1;
    return n * faktoriyel(n - 1);
}

// İlk parametre, arkadan kaç tane sayı geleceğini söyler
double ortalama_bul(int sayi_adedi, ...) {
    va_list argumanlar;
    va_start(argumanlar, sayi_adedi); // Listeyi başlat

    double toplam = 0;
    for (int i = 0; i < sayi_adedi; i++) {
        toplam += va_arg(argumanlar, int); // Sırayla sıradaki int'i çek
    }

    va_end(argumanlar); // Listeyi temizle
    return toplam / sayi_adedi;
}
```

# **Concurrency** ve **Parallelism**

### Multi-processing (`fork`)

Linux ve Unix tabanlı sistemlerde yeni bir **process** oluşturmanın temel yolu `fork()` sistem çağrısını kullanmaktır. `fork()` çağrıldığında işletim sistemi, mevcut sürecin neredeyse birebir bir kopyasını oluşturur ve böylece birbirinden bağımsız iki süreç çalışmaya başlar. Hem **parent** hem de **child** `fork()` satırından itibaren çalışmaya devam eder.

Her süreç kendine ait ayrı bir sanal bellek alanına sahiptir. Bu nedenle bir süreçte yapılan değişiklikler diğer süreci etkilemez. Süreçler arasında veri paylaşımı gerektiğinde **IPC (Inter-Process Communication)** mekanizmaları; örneğin Pipe, Message Queue veya Shared Memory kullanılır.

Süreçler birbirinden tamamen izole olduğu için güvenlidir; ancak yeni bir süreç oluşturmak ve süreçler arasında geçiş yapmak (**context switch**) işletim sistemi açısından görece maliyetli işlemlerdir. Bu nedenle multi-processing, yüksek izolasyon sağlarken daha fazla sistem kaynağı tüketir.

```c
pid_t pid;

pid = fork();   // Süreç burada ikiye bölünüyor! Child için 0 olur.

if (pid < 0) // Fork başarısız olmuştur -1 
    return 1;
else if (pid == 0) { // child süreç
    for(int i = 0; i < 5; i++) {
        printf("👶 Çocuk Süreç çalışıyor... i = %d\n", i);
        sleep(1); // 1 saniye uyutalım ki eşzamanlılığı görelim
    }
} 
else { // Bu blok sadece Parent süreç tarafından çalıştırılır
    for(int i = 0; i < 5; i++) {
        printf("👨 Ana Süreç çalışıyor... i = %d\n", i);
        sleep(1);
    }
    // Parent süreç, chiled sürecin bitmesini bekler (Zombi süreç olmasın diye)
    wait(NULL); 
      printf("Parent: Çocuk bitti, ben de kapanıyorum.\n");
}
```

### Multi-threading (`pthread`)

Günümüzde modern uygulamalarda, özellikle aynı veriler üzerinde eş zamanlı çalışılması gerektiğinde, **multi-threading** yaklaşımı sıklıkla tercih edilir. POSIX tabanlı sistemlerde thread oluşturmak ve yönetmek için genellikle `pthread.h` kütüphanesi kullanılır.

Bir süreç içinde oluşturulan tüm thread'ler aynı kod, veri ve heap alanını paylaşır. Bu sayede veriler arasında hızlı ve kolay iletişim kurulabilir. Ancak her thread'in kendine ait bir **Stack** alanı bulunur.

- **Bellek Alanı:** Thread'ler aynı sürecin **Heap, Global Değişkenler ve Kod Segmentini** paylaşır. Yalnızca Stack alanları ayrıdır.
- **İletişim:** Ortak belleği kullandıkları için veri paylaşımı ve haberleşme oldukça hızlıdır.
- **Maliyet:** Oluşturulmaları ve yönetilmeleri süreçlere göre daha hızlı ve daha az kaynak gerektirir (**lightweight**).
- **Risk:** Aynı verilere eş zamanlı erişim, **Race Condition** problemlerine yol açabilir. Bu nedenle **Mutex**, Semaphore veya diğer senkronizasyon mekanizmaları kullanılır.

```c
// Thread'lerin çalıştıracağı fonksiyonlar 'void*' alıp 'void*' dönmelidir.
void* ThreadFonksiyonu1(void* arg) {
    for(int i = 0; i < 5; i++) {
        printf("🧵 Thread 1 çalışıyor... i = %d\n", i);
        sleep(1);
    }
    return NULL;
}

void* ThreadFonksiyonu2(void* arg) {
    for(int i = 0; i < 5; i++) {
        printf("🚀 Thread 2 çalışıyor... i = %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    printf("Main: Thread'ler oluşturuluyor...\n");

    // Thread'leri başlatıyoruz
    pthread_create(&thread1, NULL, ThreadFonksiyonu1, NULL);
    pthread_create(&thread2, NULL, ThreadFonksiyonu2, NULL);

    // Main fonksiyonunun, thread'ler işini bitirmeden sonlanmasını engelliyoruz.
    // pthread_join, thread bitene kadar main thread'i bloke eder.
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main: Tüm thread'ler işini bitirdi. Program kapanıyor.\n");
    return 0;
}
```

## Mutex (Mutual Exclusion)

Bu kaosu engellemek için elimizdeki en temel silah **Mutex**'tir. Mutex'i, kritik bir odaya girmek için kullanılan tek bir **anahtar** gibi düşünebilirsin. Odaya giren kapıyı arkasından kilitler (Lock), işi bitince açar (Unlock). O içerideyken gelen diğer thread'ler kapıda kuyruğa girer ve bekler.

# Hatalar

- **Linker Hataları:** Compiler her `.c` dosyasını ayrı ayrı kontrol eder ve nesne dosyalarına (`.o`) dönüştürür. Bu aşamada kodun **syntax** doğruysa hata vermeyebilir. Daha sonra **Linker**, tüm `.o` dosyalarını ve kütüphaneleri birleştirerek tek bir çalıştırılabilir program oluşturur. Eğer kullanılan bir fonksiyonun veya değişkenin gerçek tanımını bulamazsa linker hatası oluşur.
    
    **En Meşhur Linker Hatası:** `undefined reference to 'X'` veya `LNK2019: unresolved external symbol`.
    
    **Nedeni:** Bir fonksiyonun sadece bildirimi (**prototipi**) vardır, fakat tanımı (**gövdesi**) yoktur veya ilgili `.c` dosyası derlemeye eklenmemiştir.
    
- **Multiple Definition:** Aynı global değişkenin veya fonksiyonun birden fazla `.c` dosyasında tanımlanmasıdır. Linker hata verir.
    - **`.c` dosyası include edilmez:** `#include "matematik.c"` yazmak kodun birden fazla kez derlenmesine neden olabilir. Sadece `.h` dosyaları include edilir.
    - **`extern`:** Bir global değişken başka dosyalarda kullanılacaksa, bir `.c` dosyasında tanımlanır; `.h` dosyasında ise `extern` ile bildirilir.
- **Makroların Tehlikeleri:** Makrolar, pre-processor tarafından sadece **"bul ve değiştir" (text replacement)** mantığıyla çalışır. **Type safety** yapmazlar ve bu durum hatalara yol açabilir.
    - Makrolarda her zaman her argümanı ve tüm makroyu parantez içine almalısın: `#define KARE(x) ((x) * (x))`. Ya da daha iyisi, modern C standardında tip güvenliği olan `inline` fonksiyonları tercih etmelisiniz.
    
    ```c
    #define KARE(x) x * x
    int sonuc = KARE(3 + 2);  // 3 + 2 * 3 + 2, 25 yerine 11 sonucu çıkar.
    ```
    
- **Undefined Behavior (UB).** C standartları derleyici üreticilerine der ki: *"Eğer yazılımcı şu hatayı yaparsa, derleyicinin ne çıktı üreteceğini garanti etmek zorunda değilsin. İsterse program çöksün, isterse doğru çalışsın, isterse bilgisayarı kilitlesin."*
    
    Derleyiciler optimizasyon yaparken kodun UB içermediğini varsayar. Eğer UB varsa, derleyici kodu optimize ederken tamamen bozabilir.
    
    - **Uninitialized Variable (İlk Değer Atanmamış Değişken):** O an RAM'in o hücrelerinde ne kaldıysa (garbage value) o yazılır. Ne çıkacağını asla bilemezsin.
    - **Dizi Sınırlarını Aşmak (Out of Bounds):** 5 elemanlı bir dizinin 10. elemanına erişmeye çalışmak (`dizi[10] = 50;`). O sırada bellekte başka bir değişkenin üzerine yazıyor olabilirsin ve programın saatler sonra alakasız bir yerde patlar.
    - **Signed Overflow:** İşaretli bir tam sayının sınırını aşması durumu.
    - **Dangling pointer**, işaret ettiği bellek alanı artık geçerli olmadığı halde hâlâ o adresi tutan pointer’dır./
- **Deadlock:** Mutex kullanırken düşebileceğin en büyük tuzaktır. İki veya daha fazla thread'in, birbirlerinin elindeki kilitleri açmasını sonsuza kadar beklemesi durumudur.
    
    > **Klasik Deadlock Senaryosu:**
    > 
    > - Thread A, Mutex 1'i kilitledi. O sırada Thread B, Mutex 2'yi kilitledi.
    > - Thread A çalışmaya devam etmek için Mutex 2'yi istiyor (Beklemede).
    > - Thread B çalışmaya devam etmek için Mutex 1'i istiyor (Beklemede).
    > - Sonuç: Program dondu, iki thread de sonsuza kadar birbirini bekleyecek.