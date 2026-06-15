# C++ Programlama

## Genel Bilgiler

- Tanımlanıp hiç kullanılmayan değişkenler için derleyici uyarı verir. Bu uyarıyı bastırmak için `[[maybe_unused]]` kullanılır(C++17).

- `::` operatörü, önünde bir isim (örneğin bir namespace veya sınıf adı) yoksa “global” ad alanını ifade eder.

- Büyük sayılarda okunaklığını artırmak için `'` kullanılır: `100'000'000` (C++14).

- `constexpr`, derleme zamanında hesaplanabilen ve kesinlikle sabit (compile-time constant) olan değerler için; Bir değişken `constexpr` tanımlandığında, onun derleme zamanında kesin bir sabit olacağı garantilenir. `const` ile farkı şudur: `const` çalışma zamanında da ilk değerini alabilir (örneğin kullanıcıdan alınan girdiyle), ama `constexpr` kesinlikle derleme anında bilinmelidi

- `consteval`, her çağrısı derleme zamanında kesinlikle değerlendirilir (C++20).

- Bir değişkeni başlangıçta değer atamanın 3 yolu vardır. Bunlardan en çok ve en güvenilir olanı **link initialization** çünkü daraltıcı dönüşümlere izin vermez. Örnek olarak `int` değere bir `float` değeri ataması yapılmasına **link**  izin vermezken diğer yöntemler izin verir.

- Büyük sayılarda okunaklığını artırmak için `'` kullanılır: `100'000'000` (C++14).

- **inline fonksiyon:** Derleme aşamasında çağrıldığı yere yerleştirilir (inlining), fonksiyon çağrısı yükünü azaltır.

- **inline namespace:** Birden fazla sürüm içeren kütüphanelerde, öntanımlı sürümü belirtmek için:

!!! note "Not"
    Bir değişkeni başlatmanın en güvenli yolu **list initialization**’dır; çünkü daraltıcı (narrowing) dönüşümlere örneğin bir float değeri doğrudan int’e izin vermez.

```cpp
[[maybe_unused]] int a = 5; // copy initialization
int b(5);                   // direct initialization
int c{5}                    // direct list initialization

bitset<5> a; // Bitset -> 5 bitlik değer alır.

char *buffer {new char[8]}; //bellekte yer ayırma
delete[] buffer // bir dizi silme 

//Pointer içindeki değer değiştirilemez ama pointer adresi değiştirilebilir.
const int* ptr_1; 

// Pointer adresi değiştirilemez ama içinde bulunan değer değiştirilebilir.
int const* ptr_2;

int (*array)[5] { new int[x][5] }; 
```

- **Veri Tipleri:** `int, char, bool, double, void, float, union, enum, struct, std::string`
- `std::initializer_list<T>`, süslü parantez (`{}`) ile verilen bir grup değeri fonksiyona veya constructor'a tek bir nesne olarak iletmek için kullanılan standart bir sınıftır.
- Sayının başına 0 koymak 8’lik sistemde yapar. `012` ekranda göstermek için `std::oct`
- Sayının başına 0x koymak 16’lik sistemde yapar. `0x12` ekranda göstermek için `std::hex`
- Sayının başına 0b koymak binary yapar. `0b10`
- C++'ta `std::string` ve `std::string_view` tercih edilmesinin nedeni daha güvenli, daha okunabilir ve daha kullanışlı olmalarıdır. `std::string` uzunluğu otomatik takip eder ve bellek yönetimini kendisi yapar. `std::string_view` ise gereksiz kopyalama yapmadan metne erişmeyi sağlar.
- `std::string_view` bir metnin sahibi değildir. Var olan bir karakter dizisine veya `std::string`'e sadece "bakış" sağlar. Kendi belleğini ayırmaz, metni kopyalamaz ve genellikle sadece başlangıç adresi ile uzunluğu tutar.
- `std::string_view` özellikle fonksiyon parametrelerinde, metni sadece okumak gerektiğinde, alt dizelerle çalışırken ve büyük metinleri performans kaybı olmadan geçirmek istediğimiz durumlarda kullanılır. Çünkü yeni bir `std::string` oluşturup veri kopyalamak yerine mevcut metne doğrudan referans verir. Bu sayede daha az bellek kullanılır ve daha hızlı çalışır. Ancak verinin sahibi olmadığı için gösterdiği metnin yaşam süresinin devam ediyor olması gerekir; aksi halde geçersiz bir veriye işaret edebilir.

| **Özellik / Yapı** | **C Dilinde Durum** | **C++ Dilinde Durum** |
| --- | --- | --- |
| **`struct` Tanımlama** | `struct YapıAdı var;` veya `typedef` şarttır. | `YapıAdı var;` doğrudan kullanılabilir. |
| **`struct` İçi Fonksiyon** | İzin verilmez (Sadece fonksiyon pointer kullanılabilir). | Tam desteklenir (Üye fonksiyonlar, OOP yetenekleri). |
| **`struct` Varsayılanı** | Her şey her zaman `public` erişimlidir. | Her şey `public` erişimlidir (istenirse `private` yapılabilir). |
| **`enum` Tip Güvenliği** | Zayıftır; `int` ve farklı `enum`lar birbirine karışabilir. | Sıkıdır; `enum class` ile tamamen izole edilmiş tipler oluşturulur. |
| **`enum` Kapsamı** | Elemanlar tanımlandığı kapsama sızar (Çakışma riski). | `enum class` ile elemanlar kendi kapsama alanı içinde kalır. |
| **`enum` Boyutu** | Derleyiciye bağlıdır, öngörülemez. | Yazılımcı tarafından (`: type`) dikte edilebilir. |

- **`typedef` ve `using` (Type Alias):** İkiside aynı işe yarar.

```cpp
typedef unsigned long long ulong64; // C tarzı typedef
using ulong64 = unsigned long long; // Modern C++ Type Alias
```

- `++i` (Prefix): Değişkenin değerini hemen artırır ve değişkenin kendisini referans olarak döndürür. Bellekte ek bir geçici nesne oluşturmaz.
- `i++` (Postfix): Değişkenin mevcut değerinin bir kopyasını (geçici nesne/temporary) alır, ardından orijinal değeri artırır ve kopyayı döndürür.
- **Bölme ve Mod İşlemlerinin Maliyeti:** İşlemci mimarilerinde toplama, çıkarma ve bit kaydırma işlemleri 1 saat çevriminde (clock cycle) tamamlanabilirken, bölme (`/`) ve mod (`%`) işlemleri onlarca saat çevrimi gerektiren en maliyetli aritmetik işlemlerdir. Derleyiciler, eğer bölen sayı derleme zamanında biliniyorsa (örneğin ikiye bölme), bu işlemi otomatik olarak bit kaydırma (`>>`) işlemine optimize eder.
- **C++20 Üç Yönlü Karşılaştırma (Spaceship Operator - `<=>`):** Modern C++ ile dile eklenen bu operatör, tek bir satırda iki değerin küçüklik, büyüklük ve eşitlik durumunu analiz eder. Geriye `std::strong_ordering` veya `std::partial_ordering` gibi tip güvenli yapılar döner.

- C++ derleyicileri mantıksal ifadeleri soldan sağa doğru değerlendirirken performansı artırmak adına kısa devre mekanizmasını kullanır

```cpp
// Eğer ptr nullptr ise, ikinci kısım (ptr->data) asla çalıştırılmaz. 
// Bu sayede "Null Pointer Dereference" çökmesi engellenir.
if (ptr != nullptr && ptr->data == 5) { /* ... */ }
```

- `if - else if - else, switch - case, while, for, do - while, goto`
- **Range-based for loop:** Bir koleksiyonun (dizi, vektör, liste, map vb.) tüm elemanları üzerinde baştan sona sıralı bir şekilde gezinmeyi (iteration) sağlayan, modern ve güvenli bir döngü mekanizmasıdır. **(Foreach)**

```cpp
  std::vector<int> sayilar = {10, 20, 30, 40};

  // C++ Modern Foreach Modeli
  // Performans için 'const auto&' kullanılarak kopyalama maliyeti önlenir.
  for (const auto& sayi : sayilar) {
      std::cout << sayi << " "; 
  }

```


## Type Casting

C++‘de **Type Casting**, bir veri tipindeki değerin başka bir veri tipine çevrilmesi işlemidir. C dilindeki tipleme felsefesi esnek ve tehlikeli bir yapıya sahipken, C++ bu süreci tamamen kontrol altına almak ve compile time hataları yakalamak için **4 özel cast operatörü** geliştirmiştir.

1. **static_cast:** En sık kullanılan, en güvenli ve temel yönlü cast operatörüdür. Derleme zamanında (compile-time) mantıksal olarak birbiriyle ilişkili olan tipler arasında dönüşüm sağlar. Eğer derleyici iki tip arasında mantıksal bir bağ bulamazsa derleme hatası (`compile error`) verir. 
    
    ```cpp
    double pi = 3.14159;
    int tam_sayi = static_cast<int>(pi); // Güvenli veri kaybı, niyet açık.
    
    void* ham_veri = &tam_sayi;
    int* veri_ptr = static_cast<int*>(ham_veri); // Geçerli ve güvenli
    
    // Alakasız iki tip int* ve char* arasında static_cast denemesi:
    // char* char_ptr = static_cast<char*>(veri_ptr); 
    // HATA! Derleyici iki pointer tipi arasında static_cast yapılmasına izin vermez.
    ```
    
2. **dynamic_cast:** Sadece OOP, **Polimorfizm** söz konusu olduğunda kullanılır. Base pointer, derived pointer dönüştürmek (**Downcasting**) için tasarlanmıştır.
    - `dynamic_cast`'in çalışabilmesi için temel sınıfın **polimorfik** olması gerekir. Yani en az bir `virtual` fonksiyon bulunmalıdır.
    - `static_cast` compile time’da çalışır, `dynamic_cast` ise runtime gerçekleşir. Derleyici, nesnenin gerçekte o alt sınıfa ait olup olmadığını kontrol etmek için **RTTI (Run-Time Type Information)** mekanizmasını ve `vtable` yapısını kullanır.
    - `vtable` (Virtual Table), C++'ta sanal fonksiyonların (`virtual`) çalışma zamanında doğru fonksiyonu çağırabilmesini sağlayan gizli bir tablo yapısıdır.
    - Eğer dönüşüm pointer ile yapılıyorsa ve başarısız olursa, geriye `nullptr` döner. Eğer dönüşüm referans (`&`) ile yapılıyorsa ve başarısız olursa, `std::bad_cast` exception fırlatılır.
    
    ```cpp
    // vtable oluşması için en az bir sanal fonksiyon şarttır
    class Base { virtual void dummy() {} }; 
    class Derived : public Base { public: void alt_metot() {} };
    
    Base* base_ptr = new Base();
    Derived* derived_ptr = dynamic_cast<Derived*>(base_ptr);
    
    if (derived_ptr != nullptr) {
        derived_ptr->alt_metot();
    } else {
        // Dönüşüm başarısız! Nesne gerçekte Derived değil, Base nesnesidir.
    }
    ```
    
3. **const_cast:** Bir değişkenin `const` veya `volatile` niteleyicilerini (qualifiers) eklemek veya kaldırmak için kullanılan **tek** cast operatörüdür.
    - `const_cast` ile `const` kaldırılan bir nesnenin değerini değiştirmek, eğer nesne en başında `const` olarak tanımlandıysa **Undefined Behavior** oluşturur. Bu operatör genellikle `const` doğruluğu iyi tasarlanmamış legacy C kütüphanelerine parametre gönderirken zorunluluktan kullanılır.
    
    ```cpp
    void eski_c_kutuphane_fonksiyonu(char* str) { /* veri üzerinde değişiklik yapmıyor 
    ama char* bekliyor */ }
    
    void modern_cpp_fonksiyonu(const char* güvenli_str) {
        // eski_c_kutuphane_fonksiyonu(güvenli_str); // HATA! const char*, char*'a atanamaz.
        
        // Sabitlik geçici olarak kaldırıldı
        char* degisken_str = const_cast<char*>(güvenli_str); 
        eski_c_kutuphane_fonksiyonu(degisken_str); 
    }
    ```
    
4. **reinterpret_cast:** C++ dilindeki en tehlikeli ve low level cast operatörüdür. Derleyiciye tip kontrolünü tamamen devre dışı bırakmasını söyler. Bellekteki bit dizilimini aynen koruyarak veriyi tamamen farklı bir tipmiş gibi yorumlar
    - Donanım seviyesinde programlama (Hardware register adresleme), network üzerinden gelen ham byte dizilerini (`char*` veya `uint8_t*`) struct yapılarına dönüştürme. Sıfır güvenlik sunar. Taşınabilir  değildir.
    
    ```cpp
    struct AgPaketi {
        unsigned int id;
        float veri;
    };
    
    char raw_buffer[8] = {0}; // Networkten gelen ham 8 byte veri
    
    // Ham byte dizisini doğrudan struct yapısı gibi okuyoruz
    AgPaketi* paket = reinterpret_cast<AgPaketi*>(raw_buffer);
    ```
    

| **Cast Operatörü** | **Gerçekleşme Zamanı** | **Performans Maliyeti** | **Temel Amaç** |
| --- | --- | --- | --- |
| **`static_cast`** | Derleme Zamanı (Compile-time) | Sıfır (Maliyet getirmez) | Güvenli, mantıksal tip dönüşümleri. |
| **`dynamic_cast`** | Çalışma Zamanı (Runtime) | **Yüksek** (RTTI ve vtable taraması yapar) | Polimorfik hiyerarşide güvenli downcast. |
| **`const_cast`** | Derleme Zamanı (Compile-time) | Sıfır (Maliyet getirmez) | `const` niteleyicisini manipüle etme. |
| **`reinterpret_cast`** | Derleme Zamanı (Compile-time) | Sıfır (Maliyet getirmez) | Bit seviyesinde ham ve tehlikeli dönüşüm. |


!!! note "C’de Kullanım ve Tehlikeleri"
	Tür dönüşümü `(hedef_tip)degisken` sözdizimi ile yapılır. Bu dönüşüm mekanizması derleyiciye şu mesajı verir: ***"Ne yaptığımı biliyorum, sorgulamayı bırak ve bu tipi zorla dönüştür."***

	```cpp
	double d = 3.14;
	int i = (int)d; // Veri kaybı (Truncation), derleyici sessiz kalır.

	const int sabit = 10;
	int* p = (int*)&sabit; // const kuralı delindi, Undefined Behavior
	```

	- **Aşırı Güçlü ve Ayrım gözetmeyen Yapı:** C tarzı cast, arka planda durumun ne olduğuna bakmaksızın const'luğu kaldırabilir, tamamen alakasız pointer'ları birbirine dönüştürebilir (reinterpretation) veya sayısal dönüşüm yapabilir. Yazılımcının gerçek niyetini derleyiciye aktaramaz.

	- **Kod Okunabilirliği ve Arama Zorluğu:** Büyük bir kod tabanında parantez içindeki bir tipi `(int)` aratıp bulmak, regex (düzenli ifadeler) kullanılsa dahi oldukça zordur.



## Namespace

Mantıksal olarak ilişkili olan kod bloklarını, sınıfları, fonksiyonları ve değişkenleri belirli bir isim altında gruplayan ve onları global kapsamdan izole eden sanal bir kapsamdır. 

=== "main.hpp"
	```c++
	#pragma once    // HEADER GUARDS

	namespace A {   
		namespace B {
			void foo();
		}
	}

	namespace V1 {
		void doSomething() { std::cout << "V1\n"; }
	}
	inline namespace V2 {
		void doSomething() { std::cout << "V2\n"; }
	}

	struct Foo { int a, b, c; };

	typedef unsigned long long ULLI1;  // Eski stil alias
	using ULLI2 = unsigned long long;  // Yeni stil alias

	void info();
	```

=== "main.cpp"
	```c++  
	using namespace std;  // Tüm std isimlerini doğrudan kullanmamıza izin verir
			      // Sadece belli bir ögeyi dahil etmek için: `using std::cout`

	// Designated Initializer
	Foo f0 {1, 2, 3};                   // Tüm üyeleri sırayla atar
	Foo f1 {.a = 1, .c = 3};            // Sadece a ve c’yi atar; b = 0
	Foo f2 {.c = 3, .a = 1};            // C++20’de üye sırası önemli değil: Geçerli 

	int main() 
	{
		[[maybe_unused]] int a = 5;    // Copy initialization
		[[maybe_unused]] int b(5);     // Direct initialization
		[[maybe_unused]] int c{5};     // List initialization

		std::vector words{ "peter"s, "likes"s, "frozen"s };
		for (auto& word : words) {
			std::cout << word << ' ';
		} // Çıktı: peter likes frozen 

		V1::doSomething(); // V1
		V2::doSomething(); // V2
    		doSomething();     // inline namespace → V2

		auto f = []() { std::cout << "Hello\n"; };  // Lambda
		f();
	}

	void info()
	{
		std::cout << "Decimal: a=" << a << " b=" << b << " c=" << c << "\n";
		std::cout << std::oct;
		std::cout << "Octal  : a=" << a << " b=" << b << " c=" << c << "\n";
		std::cout << std::hex << std::showbase << std::uppercase;
		std::cout << "Hex    : a=" << a << " b=" << b << " c=" << c << "\n";
		std::cout << std::dec << std::noshowbase << std::nouppercase;

		char* buffer = new char[8];   // Bellekten dizi ayırma
		delete[] buffer;              // Dizi silme

		const int* ptr1; // İşaret ettiği değer sabit, adres değişebilir
		int* const ptr2; // Adres sabit, işaret ettiği değer değişebilir
		int (*array)[5] = new int[x][5];  // x×5’lik matris
	}
	```

```cpp
// C++17 Öncesi
namespace Sirket {
    namespace Altyapi {
        namespace Veritabani {
            void baglan() {}
        }
    }
}

// C++17 ve Sonrası (Sadeleştirilmiş Sözdizimi)
namespace Sirket::Altyapi::Veritabani {
    void baglan() {} // Sirket::Altyapi::Veritabani::baglan();
}
```

- **İsme sahip olmayan namespace:** Bu yapının amacı, içerisindeki fonksiyon veya değişkenlerin **sadece tanımlandığı dosya (.cpp) içinde görünür (linkage)** olmasını sağlamaktır. C dilindeki `static` anahtar kelimesinin C++'taki modern karşılığıdır.

```cpp
// VeriIsleme.cpp dosyası içi
namespace {
    void gizliYardimciFonksiyon() {
        // Bu fonksiyona başka hiçbir .cpp dosyasından (extern edilse dahi) erişilemez.
        // Sadece bu dosya içindeki global scope'a görünürdür.
    }
}
```

- C++11 ile gelen bu özellik, özellikle kütüphane tasarımcıları için **sürüm yönetimi (versioning)** açısından kritiktir. `inline` olarak tanımlanan bir iç namespace elemanına, üst namespace üzerinden doğrudan (sürüm belirtmeden) erişilebilir.

```cpp
namespace Kitaplik {
    inline namespace V2 { // Güncel sürüm inline yapılmış
        void hesapla(int x) {}
    }
    namespace V1 { // Eski sürüm
        void hesapla(double x) {}
    }
}

int main() {
    Kitaplik::hesapla(5); // Doğrudan V2::hesapla çağrılır (inline olduğu için)
    Kitaplik::V1::hesapla(5.5); // Eski sürüme hala açıkça erişilebilir
    return 0;
}
```

## Standart IO

- `std::cout` ve `std::cin`, C'deki `printf` ve `scanf` fonksiyonları type-safe değildir. `%d` yerine yanlışlıkla float basmaya çalışmak çalışma zamanı hatalarına yol açar. C++ ise **Stream** mantığını kullanır ve operator overloading sayesinde veri tipini otomatik tespit eder.
- `std::cout` tamponlu çalışır. Veriler doğrudan ekrana yazılmak yerine önce bellekte bir buffer alınır. Buffer dolduğunda, program normal şekilde sonlandığında veya akış manuel olarak boşaltıldığında veriler topluca ekrana basılır. Bu durum I/O işlemlerinin getirdiği system call maliyetini azaltarak performansı artırır.
- `std::cin >> veri;` kullanımı, akıştaki verileri okurken boşluk ( ``), tab (`\t`) veya yeni satır (`\n`) karakterlerini **veri ayırıcı (delimiter)** olarak kabul eder. Dolayısıyla, klavyeden girilen metindeki ilk boşluğa kadar olan kısmı okur, geri kalanını akış tamponunda (stream buffer) bırakır.
- Boşluk içeren tüm bir satırı (örneğin bir isim ve soyisim) tek seferde okumak için `>>` operatörü yerine global `std::getline()` fonksiyonu kullanılmalıdır.
- `std::cerr` Standart hata akış nesnesidir. Programdaki hata mesajlarını ve kritik uyarıları raporlamak için tasarlanmıştır. Tamponsuz çalışır. Akışa gönderilen her karakter, bellekte bekletilmeden **anında** çıkış aygıtına yazılır. **Bir çökme (crash) durumunda**, eğer hata mesajı tampon bellekte bekliyor olsaydı, program bellek alanını boşaltamadan kapanacağı için hata mesajı ekrana hiç yansımayabilirdi. `std::cerr` tamponsuz çalışarak hatanın oluştuğu anın kesin olarak loglanmasını garanti eder. Ayrıca, işletim sistemi seviyesinde standart çıktılar bir dosyaya yönlendirildiğinde (`./program > output.txt`), hata mesajlarının ekranda kalmaya devam etmesini sağlar.
- `std::endl`: Akışa bir yeni satır karakteri (`\n`) ekler ve ardından akış tamponunu zorla boşaltır (`flush` işlemi yapar). Sık kullanımı performans kritik sistemlerde tamponlama avantajını öldürdüğü için bottleneck (darboğaz) yaratabilir.
- `std::flush`: Yeni satır eklemeden sadece mevcut tamponu anında çıkış aygıtına yazar.
- `std::setw(int w)`: Çıktının kaplayacağı minimum karakter genişliğini belirler (Sağa hizalı).
- `std::setprecision(int p)`: Kayan noktalı sayıların virgülden sonra kaç basamak (hassasiyet) gösterileceğini ayarlar.
- `std::fixed`: Kesirli sayıların bilimsel gösterimle ($1.2e+02$) değil, standart sabit gösterimle yazılmasını dikte eder.
- `std::hex`, `std::oct`, `std::dec`: Sayısal verilerin sırasıyla 16'lık (hexadecimal), 8'lik (octal) veya 10'luk tabanda yazdırılmasını/okunmasını sağlar.
- `<<` (Insertion / Ekleme Operatörü): Veriyi akışa göndermek (yazmak) için kullanılır.
- `>>` (Extraction / Çıkarma Operatörü): Veriyi akıştan çekmek (okumak) için kullanılır.


## Fonksiyonlar

- **Function Overloading** eklenmiştir. C++ derleyicisi, aşırı yüklenmiş fonksiyonları birbirinden ayırmak için arka planda benzersiz isimler üretir. Buleme **Name Mangling** denir. Derleyici, fonksiyon isminin sonuna parametre tiplerini sembolize eden ekler getirir.
- C++'ta bir fonksiyonun parametrelerine varsayılan (default) değerler atanabilir. Eğer fonksiyon çağrılırken bu parametreler boş bırakılırsa, varsayılan değerler otomatik olarak devreye girer. Varsayılan değer ataması parametre listesinde sağdan sola doğru yapılmalıdır. Varsayılan değere sahip bir parametrenin sağında, varsayılan değeri olmayan bir parametre bulunamaz (`void f(int a = 10, int b);` hatadır).
- C++ dile **Referans (`&`)** kavramını kazandırmıştır. Referanslar, arka planda güvenli pointer mekanizması kullanan, fakat sözdizimi olarak normal değişken gibi davranan takma isimlerdir **(Call by Reference)**.

!!! note "Not"
	Eğer C++ projenize eski bir C kütüphanesini dahil ediyorsanız veya C++ ile yazdığınız bir fonksiyonun C derleyicileri tarafından okunabilmesini istiyorsanız, Name Mangling mekanizmasını kapatmanız gerekir. Bunun için `extern "C"` bloku kullanılır:

	```cpp
	extern "C" {
		void c_tarzi_fonksiyon(int x); // Name mangling uygulanmaz, 
																	// saf C ismiyle sembol masasında kalır.
	}
	```

### Lambda İfadeleri

Lambda ifadeleri (Lambda Expressions), **ismi olmayan, bulunduğu yerde tanımlanıp kullanılabilen küçük fonksiyonlardır.**

- Değer olarak yakaladığın bir değişkeni lambdanın içinde değiştiremezsin. Değiştirmek istiyorsan, lambdaya **`mutable`** demelisin.
- `[]` Buna **capture list** denir. Lambda'nın dışarıdaki değişkenlere erişip erişemeyeceğini belirler.
    - `[]` dışarda bulunan değişkenlere erişemez
    - `[x]` belirtilen değişkenin kopyasını alır.
    - `[&x]` doğrudan değişkene erişir.
    - `[=]` bütün değişkenlere kopyalama ile erişir.
    - `[&]` bütün değişkenlere referans ile erişir.

```cpp
// [capture](parametreler) -> dönüş_tipi { kodlar };

[](int a, int b) { return a + b; }
```


## Pointer

- C dilinde bir pointer'ın hiçbir yeri göstermediğini belirtmek için `NULL` makrosu kullanılır. `NULL`, arka planda aslında saf `0` (tam sayı) değeridir. Bu durum, fonksiyon aşırı yüklemesi (function overloading) esnasında derleyicinin kafasını karıştırarak ciddi tip güvenliği zafiyetlerine yol açar.
- C++11 ile gelen **`nullptr`**, doğrudan bir işaretçi sabitidir (türü `std::nullptr_t`'dir). Asla bir tam sayı olan `0` ile karışmaz.
- C dilinde `void*` türündeki ham bir işaretçi, herhangi bir başka işaretçi türüne **hiçbir cast işlemi olmaksızın (implicit olarak)** atanabilir. C++'ta ise bu durum kesinlikle yasaktır; derleyici sıkı tip kontrolü yapar ve açıkça dönüşüm (explicit cast) yapılmasını dikte eder.
- C dilinde `malloc` ile tahsis edilen bellek, pointer üzerinden manuel olarak `free` edilmek zorundadır. Yazılımcı `free` etmeyi unutursa **Bellek Sızıntısı (Memory Leak)**, birden fazla kez silerse **Double Free**, sildiği adrese erişmeye çalışırsa **Dangling Pointer** gibi ölümcül bellek hataları oluşur.

!!! note "Not"
	Donanım seviyesinde adres okuma/yazma mekanizması C ile tamamen aynıdır; ancak modern C++ mimarisinde ham pointer'lar (`*`) ve `delete` kullanımı birer güvenlik zafiyeti (code smell) olarak görülür. Endüstriyel projelerde bunların yerini `nullptr` ve Akıllı İşaretçiler (`std::unique_ptr`) almıştır.


- **Pointer ():** Bellekte başka bir değişkenin adresini (`0x7ffe...`) kendi içinde veri olarak saklayan bağımsız bir değişkendir. Kendine ait bir bellek alanı ve adresi vardır.
- **Referans (`&`):** Bellekte halihazırda var olan bir nesneye verilen **takma isimdir (alias)**. Kendisi bağımsız bir nesne veya değişken değildir; bağlandığı orijinal nesnenin ta kendisidir.

| **Akademik / Mimari Kriter** | **Pointer (*)** | **Referans (&)** |
| --- | --- | --- |
| **Temel Tanım** | Başka bir değişkenin bellek adresini içinde veri olarak saklayan **bağımsız bir değişkendir**. | Bellekte halihazırda var olan bir nesneye verilen **takma isimdir (alias)**. |
| **İlk Değer Atama (Initialization)** | Tanımlandığı an bir adres göstermek zorunda değildir. Boş bırakılabilir (`int* ptr;`). | Tanımlandığı an **kesinlikle** geçerli bir nesneye bağlanmalıdır (`int& ref = x;`). |
| **Yeniden Bağlanabilirlik (Re-seating)** | Ömrü boyunca istediği an adresini değiştirip başka bir nesneyi gösterebilir. | Bir kez bir nesneye bağlandıktan sonra, ömrünün sonuna kadar **başka bir nesneye bağlanamaz**. |
| **Null Değeri Alabilme** | Hiçbir yeri göstermediğini belirtmek için güvenle `nullptr` değerini alabilir. | Dil seviyesinde `null` referans diye bir kavram **yoktur**, her zaman bir nesneye ait olmalıdır. |
| **Adres Çözme (Dereferencing)** | Gösterdiği veriye erişmek için açıkça `*` veya `->` operatörleri kullanılmalıdır. | Ekstra hiçbir operatöre gerek yoktur. Normal bir yerel değişken gibi doğrudan ismiyle kullanılır. |
| **Aritmetik İşlemler** | Pointer aritmetini destekler (`ptr++`, `ptr += 2`). Bellekte ileri/geri hareket edebilir. | Aritmetik işlemleri destekler ancak işlem referansın adresine değil, **bağlandığı nesnenin değerine** uygulanır. |
| **Bellek Alanı (`sizeof` davranışı)** | Bulunulan mimariye göre (`64-bit` için **8 byte**) kendi bağımsız bellek boyutunu verir. | Doğrudan **bağlandığı nesnenin** bellekte kapladığı boyutu verir. |
| **Derleyici Seviyesi (Low-level)** | Bellekte doğrudan bir adres saklar. | Arka planda derleyici tarafından **sabit bir işaretçi (`Type* const`)** gibi yönetilir, otomatik adres çözümü yapılır. |
| **Çoklu Seviye (Multi-level)** | Bir işaretçinin işaretçisi (indirection) tanımlanabilir (`int** pptr`). | Bir referansın referansı (yerel kapsamda) tanımlanamaz. `int&&` ifadesi C++11 ile gelen bambaşka bir kavramdır (Rvalue). |


### Smart Pointers

- C++11, nesnelerin ömür döngüsünü (lifetime) otomatik yöneten ve kapsam dışına (scope) çıkıldığında belleği kendiliğinden iade eden **Akıllı İşaretçiler** mekanizmasını tanıtmıştır. `delete` anahtar kelimesini manuel kullanma zorunluluğunu ortadan kaldırır (RAII Prensibi).
    - **`std::unique_ptr`:** Bellekteki bir alanın (nesnenin) sadece tek bir sahibinin (owner) olabileceğini garanti eder. Kopyalanamaz, sadece taşınabilir (`std::move`). En performanslı akıllı pointer'dır, ham pointer ile arasında sıfır performans farkı (zero-overhead) vardır.
    - **`std::shared_ptr`:** Bellekteki bir alanın birden fazla sahibi olmasına izin verir. İçeride bir **referans sayacı (reference counter)** tutar. Nesneyi gösteren shared_ptr sayısı sıfıra ulaştığında bellek otomatik olarak temizlenir.
    - **`std::weak_ptr`:** `std::shared_ptr` hiyerarşisinde ortaya çıkabilecek döngüsel bağımlılıkları (circular dependency / deadlock benzeri bellek kilitlenmeleri) çözmek için kullanılan, referans sayacını artırmayan gözlemci işaretçidir.
- `move` bir nesnenin değerinin taşınmasını sağlar. Nesnenin kopyasını oluşturmaz direkt taşır.
- `unique_ptr`  bu akıllı işaretçi, dinamik bellek yönetimini güvenli bir şekilde gerçekleştirmek için kullanılır. Bir **`unique_ptr`**, sahibi olduğu nesnenin yaşam döngüsünü otomatik olarak yönetir ve sahip olduğu nesnenin bellekten otomatik olarak serbest bırakılmasını sağlar bu sayede bellek sızıntılarını önler ve bellek kaynaklarını paylaşma sorunlarını azaltır.
- `shared_ptr` birden fazla işaretçi aynı nesneyi işaret edebilir ve nesne, tüm işaretçilerin yaşam döngüsü sona erene kadar bellekte kalır. Bu, bellek sızıntılarını önlemeye ve kaynak yönetimini kolaylaştırmaya yardımcı olur.
- `make_unique`, C++14 birlikte standart kütüphaneye eklenen bir yardımcı işlevdir. Bu işlev, dinamik bellekten bir nesne oluşturmak için kullanılır ve bu nesnenin ömrünü `unique_ptr` tarafından yönetilen bir Smart Pointers devreder.

```cpp
// int türünde nesne ve onun sahibi olan bir unique_ptr döndürülür.
std::unique_ptr<int> ptr = std::make_unique<int>(42);

//Dinamik bellekten dizi oluşturur. (5 elemanlık bir dizi oluşturulur)
std::unique_ptr<int[]> arr = std::make_unique<int[]>(5);
```

## Dosya İşlemleri

C++'ta dosya işlemleri `<fstream>` kütüphanesi içinde üç ana sınıf üzerinden yürütülür. Bu sınıfların tamamı `std::ios_base` tabanlı bir kalıtım hiyerarşisine sahiptir.

- **`ifstream` (Input File Stream):** Dosyadan **veri okumak** (read) için kullanılır.
- **`ofstream` (Output File Stream):** Dosyaya **veri yazmak** (write) için kullanılır. Dosya yoksa oluşturur, varsa (varsayılan olarak) içini temizler.
- **`fstream` (File Stream):** Aynı dosya üzerinde **hem okuma hem yazma** (read/write) işlemlerini aynı anda yapmak için kullanılır.

!!! note "Not"
	C++'ta dosyayı `.close()` ile kapatmak şart değildir (manuel kapatmak iyi bir pratik olsa da). Sınıfların destructor'ı (yıkıcısı) kapsamdan (`scope`) çıkıldığı anda dosyayı otomatik olarak kapatır ve işletim sistemine kaynağı iade eder.


| **Özellik** | **Text Files (std::ios::text)** | **Binary Files (std::ios::binary)** |
| --- | --- | --- |
| **Yorumlama** | Karakterleri ASCII/UTF-8 olarak okur/yazar. | Veriyi bellekteki **ham byte (raw byte)** haliyle doğrudan kopyalar. |
| **Satır Sonu (`\n`)** | Windows'ta `\n` otomatik olarak `\r\n` (CRLF) yapılır. Linux'ta `\n` kalır. | Dönüşüm yapılmaz. `\n` neyse o byte olarak yazılır. |
| **Performans** | Dönüşümler ve formatlama yüzünden daha yavaştır. | Çok hızlıdır. Büyük veriler/struct'lar doğrudan diske dökülür. |
| **Metotlar** | `<<`, `>>`, `getline()` kullanılır. | `.write()` ve `.read()` metotları kullanılır. |


## Hata Yönetimi (Error Handling)

- **Klasik Yaklaşım: Hata Kodları:** C++ öncesinden kalan ve hala performans kritik (özellikle gömülü sistemler ve çekirdek seviyesi) yerlerde kullanılan yöntemdir. Fonksiyonlar bir hata kodu (genellikle `int` veya `enum`) döner, asıl üretilen veri ise pointer/referans yoluyla parametre üzerinden dışarı aktarılır.
- **Exceptions:** C++'ın standart hata yönetimi mekanizmasıdır. Hata oluştuğunda normal program akışı kesilir ve hata yakalanana kadar çağrı yığınında (`call stack`) yukarı doğru fırlatılır.
    - C++11 ile gelen `noexcept`, derleyiciye "Bu fonksiyon asla exception fırlatmayacak" garantisi verir. Derleyici, `noexcept` olan bir fonksiyonda stack unwinding kodları üretmez, bu da binary boyutunu küçültür ve optimizasyonu artırır. `noexcept` bir fonksiyon içinde yanlışlıkla exception fırlatılırsa, `catch` bloklarına bakılmaksızın program anında `std::terminate()` çağırarak çöker.
    - **`throw` (Hata Fırlatma):** Hata durumunun tespit edildiği noktada, normal akışı durdurup bir hata nesnesini havaya fırlatmak için kullanılır. `throw` ifadesinden sonra herhangi bir veri tipi (primitive türler, pointer'lar veya nesneler) fırlatılabilir.
    - **`try` ve `catch` (Arama ve Yakalama):** Hata fırlatma potansiyeli olan kod blokları `try` içerisine alınır. Eğer içeride bir hata fırlatılırsa, derleyici hemen `try` bloğunu terk eder ve sırayla `catch` bloklarını kontrol etmeye başlar.

```cpp
double divide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("Sıfıra bölme hatası!"); // Hata fırlatılıyor
    }
    return a / b;
}

int main() {
    try {
        double result = divide(10.0, 0.0);
        std::cout << "Sonuç: " << result << "\n";
    } catch (const std::invalid_argument& e) { // Referans ile yakalamak Best Practice'tir
        std::cerr << "Hata yakalandı: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Genel bir hata: " << e.what() << "\n";
    }
    return 0;
}
```

!!! note "Not"
	**RAII Bağlantısı:** Eğer kaynaklarınızı (bellek, dosya, mutex) akıllı pointer'lar (`std::unique_ptr`) veya RAII sınıfları ile yönetmiyorsanız, stack unwinding esnasında ham pointer'lar temizlenemez ve **Memory Leak** oluşur.

## Template Temelleri

Şablonların temel amacı, veri tipini kodun kendisinden ayırarak aynı algoritmayı farklı tipler için tekrar tekrar yazmayı (code duplication) önlemektir.

!!! note "Not"
	Eğer tüm argümanlar aynı türden ise `< >` yazmaya gerek yoktur.

- **Function Templates:** Derleyicinin, verilen argümanlara bakarak fonksiyonun ilgili tipe özel halini derleme anında üretmesini sağlar.

```cpp
template <typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    // 1. Explicit (Açık) Belirtim
    std::cout << maxValue<double>(5.5, 3.2) << "\n";

    // 2. Implicit (Örtük) Tür Çıkarımı (Template Argument Deduction)
    // Derleyici parametrelere bakarak T'nin 'int' olduğuna kendisi karar verir.
    std::cout << maxValue(10, 20) << "\n"; 
}
```

- **Class Templates:** Veri yapılarını (Container'ları) türden bağımsız hale getirmek için kullanılır. En popüler örneği `std::vector` veya `std::pair`'dir.

```cpp
template <typename T, size_t Size> // Tür parametresi ve Tür-Dışı (Non-type) parametre
class FixedArray {
private:
    T data[Size]; // Derleme zamanında boyutu belli olan dizi
public:
    void set(size_t index, const T& value) { data[index] = value; }
    T get(size_t index) const { return data[index]; }
};

int main() {
    FixedArray<std::string, 5> myStrings; // C++17 öncesi zorunluydu
    // Modern C++ (C++17 CTAD - Class Template Argument Deduction):
    // Derleyicinin constructor argümanlarından sınıf şablon parametrelerini çıkarabilmesi özelliğidir.
}
```

- **Template Specialization:** Bazen genel şablon algoritması, belirli bir veri tipi için optimize çalışmaz veya farklı bir mantık gerektirir. Bir tipe özel şablon yazmaya **Full Specialization** denir.

```cpp
// Genel Şablon
template <typename T>
bool isEqual(T a, T b) {
    return a == b;
}

// 'const char*' (C-Style string) için TAM ÖZELLEŞTİRME
// Genel şablonu ezip, pointer karşılaştırması yerine strcmp yapmasını sağlıyoruz.
template <>
bool isEqual<const char*>(const char* a, const char* b) {
    return std::strcmp(a, b) == 0;
}
```


## OOP

C++ dünyasında `struct` ve `class` anahtar kelimeleri teknik olarak **neredeyse tamamen aynı yeteneklere sahiptir**. Aralarındaki tek akademik fark **varsayılan erişim belirleyicisidir (default access specifier)**

- `default` Derleyicinin varsayılan implementasyonu oluşturmasını ister.
- `delete` Bir fonksiyonun kullanılmasını yasaklar.
- **`struct`** içinde tanımlanan tüm üyeler varsayılan olarak **`public`** kabul edilir.
- **`class`** içinde tanımlanan tüm üyeler varsayılan olarak **`private`** kabul edilir.
- Aynı kural kalıtım için de geçerlidir: `struct Derived : Base` yazıldığında kalıtım varsayılan olarak public olur.
- **`explicit`** anahtar kelimesi, bir sınıfın tek parametreli yapıcı fonksiyonunun, otomatik dönüşümlere (automatic conversions) izin verilmemesini belirtir. Özellikle, **`explicit`** , bir türün diğerine dönüştürülmesi işlemlerini kontrol etmeye yardımcı olur. Bu, özellikle beklenmeyen ve istenmeyen otomatik dönüşümleri önlemek için önemlidir.
- **Encapsulation:** Sınıflarda bulunan private özelliklere erişmek  için public özelliklerinde bulunan **set** ve **get**  fonksiyonları ile erişme işlemidir.
- **Erişim Belirleyiciler:** **`public, private, protected`**

!!! note "Not"
	- Shallow Copy nesnenin içindeki pointer adresleri aynen kopyalanır. İki nesne de Heap'teki aynı adresi göstermeye başlar. Nesnelerin ömrü bittiğinde, destructor'lar aynı adresi iki kez silmeye çalışır (**Double Free Crash**). 
	
	- Deep Copy (`Copy Constructor` ile yaptığımız gibi) Heap'te yeni bir alan açılır ve içerideki veri kopyalanır; nesnelerin bellek bağları ayrılır.

!!! note "Not"
	- Eğer bir sınıftan başka sınıflar **Inheritance** ve Base Class pointer'ı üzerinden Derived Class nesnesi yönetilecekse, taban sınıfın destructor'ı **kesinlikle `virtual` olmalıdır**.

	- Eğer yapılmazsa, nesne silindiğinde (`delete base_ptr;`) sadece taban sınıfın destructor'ı çalışır; Derived yıkıcısı **çalışmaz**. Bu durum alt sınıfın Heap'te oluşturduğu tüm dinamik belleklerin sızmasına (**Memory Leak**) yol açar

### Inheritance

Bir class özelliklerini ve metotlarını başka bir sınıfa aktarması demektir. Kod tekrarını önler ve düzenli bir yapı kurmanı sağlar. Default olarak `private`

- Kalıtım alınmış class özelliğini `delete` ile sınıftan silinebilir.

| **Base Member** | **public Kalıtım Sonrası** | **protected Kalıtım Sonrası** | **private Kalıtım Sonrası** |
| --- | --- | --- | --- |
| **`public`** | `public` | `protected` | `private` |
| **`protected`** | `protected` | `protected` | `private` |
| **`private`** | Gizli (Erişilemez) | Gizli (Erişilemez) | Gizli (Erişilemez) |

- **Single Inheritance:** Bir çocuk sınıf, sadece bir ana sınıftan miras alır. (Baba ve oğul gibi).
- **Multiple Inheritance:** Birden fazla ana sınıftan miras almasıdır. (Hem anneden hem babadan özellik almak gibi).
- **Multilevel Inheritance:** Bir sınıfın başka bir türetilmiş sınıftan miras almasıdır. Bir zincir gibidir. (Dede → Baba →Torun ilişkisi).
- **Hierarchical Inheritance:** Bir ana sınıftan birden fazla çocuk sınıfın türemesidir. Bir şirketteki müdür ve işçilerin aynı CEO'ya bağlı olması veya bir babanın birden fazla çocuğu olması gibidir.

| **Kalıtım Türü** | **Yapısı** | **Örnek İlişki** |
| --- | --- | --- |
| **Single** | A → B | Baba → Çocuk |
| **Multiple** | A + B → C | Anne + Baba → Çocuk |
| **Multilevel** | A → B → C | Dede →Baba → Torun |
| **Hierarchical** | A → B ve A → C | Tek anne babanın iki farklı çocuğu |


### Polymorphism

Nesne yönelimli programlamada (OOP), **farklı nesnelerin aynı mesaja (fonksiyon çağrısına) farklı şekillerde yanıt verebilmesi** yeteneğidir.

- **Pure Virtual Function:** Bir sanal (virtual) fonksiyonun gövdesini vermeyip `= 0` ile tanımlarsanız, o fonksiyon **pure virtual function** olur. Burada fonksiyonunun nasıl çalışacağı belirtilmemiştir. Bu fonksiyonu türeyen sınıfların mutlaka gerçekleştirmesi (override etmesi) gerekir.
- **Abstract Class:** İçerisinde en az bir adet pure virtual function bulunan sınıfa **abstract class** denir. Bu sınıftan doğrudan nesne oluşturulamaz.
- **Object Slicing:** C++'ta türemiş (derived) bir nesnenin taban (base) sınıf nesnesine **değer olarak** atanması veya geçirilmesi sırasında, türemiş sınıfa ait kısmın "kesilip atılması" durumudur.

- **Compile-Time (Static) Polymorphism:** Derleyici, hangi fonksiyonun veya kod bloğunun çağrılacağını **derleme aşamasında** (compile-time) veri tiplerine bakarak çözer. En büyük avantajı **sıfır performans maliyeti (zero-overhead)** olmasıdır, çünkü çalışma zamanında bir arama mekanizması işletilmez.
    - Function Overloading
    - Operator Overloading
    - Templates
- **Runtime (Dynamic) Polymorphism:** Gerçek "nesne yönelimli" esnekliği sağlayan yapıdır. Hangi fonksiyonun çağrılacağı, **program çalışırken (runtime)** nesnenin gerçek türüne (dynamic type) bakılarak belirlenir. Bu mekanizma **Kalıtım (Inheritance)** ve **Sanal Fonksiyonlar (Virtual Functions)** kullanılarak gerçekleştirilir.
    - Fonksiyon taban sınıfta (Base) `virtual` olarak tanımlanmalıdır.
    - Türetilmiş sınıfta (Derived) aynı isim ve imza ile `override` edilmelidir.
    - Çağrı, Taban sınıfın **pointer (`Base*`)** veya **referansı (`Base&`)** üzerinden yapılmalıdır.

!!! note "Not"
	Derleyici, içinde en az bir tane `virtual` fonksiyon barındıran her sınıf için bir **VTABLE (Virtual Table)** oluşturur. Bu tablo, o sınıfın sanal fonksiyonlarının bellek adreslerini tutan bir fonksiyon gösterici dizisidir (function pointer array).

	O sınıftan bir nesne üretildiğinde ise, nesnenin bellekteki ilk elemanı olarak gizli bir pointer eklenir: **VPTR (Virtual Pointer)**. Bu pointer, ait olduğu sınıfın VTABLE'ını işaret eder.

	- `animalPtr->makeValue()` çağrıldığında, program önce nesnenin içindeki `vptr`'ye gider.

	- `vptr` üzerinden ilgili sınıfın `VTABLE`'ına ulaşır.

	- Tablodaki doğru indeksteki fonksiyon adresini çözer ve o fonksiyonu tetikler.

	- **Maliyet:** Bu işlem runtime'da bir ekstra pointer takibi (indirection) gerektirdiği için cache-miss olasılığını artırır ve az da olsa performans maliyeti yaratır.

!!! note "Not"
	- Eğer bir taban sınıf pointer'ı üzerinden türetilmiş bir sınıf nesnesini `delete` etmeye çalışırsanız ve taban sınıfın yıkıcısı `virtual` değilse, **Undefined Behavior** oluşur. Pratik olarak, sadece taban sınıfın yıkıcısı çağrılır; türetilmiş sınıfın yıkıcısı çağrılmaz. Bu da türetilmiş sınıfın içinde ayrılan kaynakların (Dynamic memory, file handles vb.) temizlenememesine, yani **Memory Leak**'e yol açar

	- C++'ta nesneler taban sınıftan türetilmiş sınıfa doğru inşa edilir. Taban sınıfın constructor'ı çalışırken, türetilmiş sınıf henüz var olmamıştır (inşa edilmemiştir). Bu yüzden constructor içinde çağrılan `virtual` fonksiyon, dynamic polymorphism kurallarına uymaz; **taban sınıftaki versiyonu çalışır**.

	- `override`Zorunlu değildir ancak C++11 ile gelen çok güçlü bir derleme zamanı güvencesidir. Eğer türetilmiş sınıfta fonksiyon imzasını (const takısı, parametre tipi vb.) yanlışlıkla küçük bir farkla yazarsanız, derleyici bunu yeni bir fonksiyon gibi algılar (overloading sanır) ve runtime polymorphism bozulur. `override` yazdığınızda, derleyiciye *"Bu fonksiyon mutlaka taban sınıfta virtual olmalı, kontrol et"* dersiniz. Eşleşme yoksa derleme hatası verir.

### Operator Overloading

 Bu mekanizma; kullanıcı tanımlı tiplerin, dilin yerleşik temel tipleri (`int`, `float` vb.) gibi doğal, sezgisel ve okunabilir bir syntax aritmetik, karşılaştırma veya mantıksal işlemlere tabi tutulmasını sağlar.  "kod şık görünsün" diye değil; bellek yönetimi, performans (`rvalue` referansları ve kopyalamadan kaçınma) ve standart kütüphane (`std::sort`, `std::cout`) uyumluluğu için kritik önem taşır.

C++ derleyicisi, dilin kararlılığını korumak adına operatör aşırı yüklemesine çok katı akademik kurallar koymuştur:

- **Yeni Operatör İcat Edilemez:** Dilde halihazırda var olmayan bir sembol (örneğin  veya `@`) operatör olarak tanımlanamaz.
- **Temel Tiplerin Davranışı Değiştirilemez:** İki `int` sayının toplama (`+`) işleminin davranışını değiştiremezsiniz. İşlemin işlenenlerinden en az birinin kullanıcı tanımlı bir tip (`class` veya `struct`) olması zorunludur.
- **Öncelik ve İlişkilendirilebilirlik Değişmez:** Aşırı yüklenen bir operatörün öncelik sırası ve soldan sağa/sağdan sola birleşme özellikleri dilin standart tablosundaki haliyle kalır.
- **Aşırı yüklenemeyen operatörler:** `.` (member access), `.*` (pointer to member), `::` (scope resolution), `?:` (ternary conditional) ve `sizeof`.
1. **Üye Fonksiyon Olarak Aşırı Yükleme:** Operatör, sınıfın bir metodu olarak tanımlanır. Bu durumda sol taraftaki işlenen (left-hand side operand) gizli `this` işaretçisi vasıtasıyla fonksiyonu çağıran nesnenin kendisidir. Sağ taraftaki işlenen ise fonksiyona parametre olarak geçilir.
2. **Global (veya Friend) Fonksiyon Olarak Aşırı Yükleme**: Operatör, sınıfın dışında bağımsız bir fonksiyon olarak tanımlanır ve her iki işleneni de açıkça parametre olarak alır. Eğer bu fonksiyonun sınıfın `private` üyelerine erişmesi gerekiyorsa, sınıf içinde **`friend`** anahtar kelimesiyle yetkilendirilmelidir.


### Friend Yapıları

- **Friend Functions:** Bir sınıfın üyesi (member fonksiyonu) olmadığı halde, o sınıfın `private` ve `protected` alanlarına doğrudan erişim yetkisi olan bağımsız fonksiyonlardır.
    - Sınıfın içinde `friend` keyword'ü ile **deklarasyonu (bildirimi)** yapılır.
    - Fonksiyonun asıl **tanımı (implementasyonu)** sınıf dışında yapılır ve tanımlanırken `friend` veya `Sınıf_Adı::` takısı kullanılmaz.
    - Sınıfın üyesi olmadığı için `this` pointer'ına sahip değildir. Bu yüzden nesneye erişebilmek için parametre olarak o nesnenin pointer veya referansını almak zorundadır.

- **Friend Classes:** Eğer bir sınıfın, başka bir sınıfın tüm `private` ve `protected` üyelerine tamamen erişmesini istiyorsanız, o sınıfı komple `friend` ilan edebilirsiniz.

!!! note "Not"
	- **Friendship is not mutual (Dostluk karşılıklı değildir):** Eğer `A` sınıfı `B`'yi `friend` ilan ederse, `B` sınıfı `A`'nın private alanlarına erişebilir. Ancak `A`, `B`'nin private alanlarına **erişemez**. (B, A'ya dostunu söyler ama A, B'ye sırlarını açar).
	- **Friendship is not transitive (Dostluk geçişli değildir):** `A` sınıfı `B` ile dostsa, `B` sınıfı da `C` sınıfı ile dostsa; `C` sınıfı otomatik olarak `A` ile dost **olamaz**. (Arkadaşımın arkadaşı benim arkadaşım değildir).
	- **Friendship is not inherited (Dostluk miras kalmaz):** Taban sınıfın (`Base`) dostu olan bir fonksiyon veya sınıf, türetilmiş sınıfın (`Derived`) private alanlarına otomatik olarak **erişemez**. Aynı şekilde, taban sınıf türetilmiş sınıfın dostluklarını miras almaz.

## STL (Standard Template Library)

- **Containers**, verileri bellekte nasıl tuttuğumuzu ve organize ettiğimizi belirler

### Sequence Containers

#### Vector

C++ STL en çok kullanılan ardışık (sequential) konteyneridir. En basit tanımıyla: **Dinamik olarak büyüyebilen, elemanları bellekte ardışık (contiguous) olarak tutan bir dizidir.** Bellekte ardışık olması  bize müthiş bir **Cache Locality (Önbellek Uyumu)** avantajı sağlar. İşlemci bir elemana eriştiğinde, sonraki elemanları da önbelleğe alır ve erişim hızımız artırır

- `size()`, konteyner içerisinde **aktif olarak bulunan eleman sayısını** döndürür.
- `capacity()`, konteynerin yeniden bellek tahsisi yapmadan saklayabileceği **maksimum eleman sayısını** gösterir. `capacity()` değeri genellikle `size()`'dan büyük veya eşittir.
- `reserve(n)`: Sadece **capacity** en az `n` olacak şekilde ayarlar. `size` değişmez, nesneler initialize edilmez. `push_back` yapıldığında sıradan devam edilir.
- `resize(n)`: **Size** `n` yapar. Eğer `n` mevcut boyuttan büyükse, aradaki fark kadar yeni nesne default constructor ile oluşturulur. `push_back` yapıldığında n +1’den devam edilir.
- `push_back()` ve `emplace_back()` ikisi de konteynerin sonuna eleman ekler. Temel fark, nesnenin **nasıl oluşturulduğudur**.
- `push_back()`: Nesneyi dışarıda oluşturup `vector`ün son kısmına kopyalar veya taşır (`move`).
- `emplace_back()`: Nesneyi dışarıda oluşturmaz. Verilen parametreleri doğrudan `vector`ün kendi bellek alanına gönderir ve nesneyi **içeride (in-place)** inşa eder. Temporary (geçici) nesne oluşumunu engeller.

!!! note "Capacity Dolunca Ne Olur"
	1. **Reallocation:** `vector`, mevcut kapasitesinin genellikle 1.5 veya 2 katı büyüklüğünde **yeni ve boş** bir bellek alanı ister
	2. **Taşıma/Kopyalama:** Eski alandaki elemanlar yeni alana taşınır (mümkünse `move`, değilse `copy` edilir).
	3. **İmha:** Eski bellek alanı işletim sistemine iade edilir.

	Reallocation işlemi ciddi bir performans maliyetidir. Ayrıca bu işlem gerçekleştiğinde, eski elemanlara işaret eden tüm pointer, referans ve iterator'lar geçersiz kalır (**Iterator Invalidation**).

	```cpp
	std::vector<int> v;

	v.reserve(10);  // resize kullanılırsa bu durumda size da 12 olur. 
									// size, capacity geçtiği için 10 * 2 = 20 olur.
	v.push_back(1);
	v.push_back(2);

	std::cout << "Size: " << v.size() << std::endl;           // 2
	std::cout << "Capacity: " << v.capacity() << std::endl;   // 10
	```

!!! note "Fonksiyonları"
	- `pop_back()` son elemanı siler.
	- `erase()` belirli bir elemanı veya aralığı siler.
	- `clear()` tüm elemanları siler. (`size = 0` , `capacity = değişmez`)
	- `[]` hızlı bir şekilde elemalara erişmeyi sağlar fakat sınır kontrolü yapmaz.
	- `at()` elemana erişmeyi sağlar. Sınır kontolü yapar.
	- `front()` ilk elemanı döndürür.
	- `back()` son elemanı döndürür.
	- `empty()` boş mu kontol eder.
	- `shrink_to_fit()` fazla belleği iade etmeyi talep eder.
	- `insert()` belirli konuma eleman ekler
	- `data()` İç belleğin ham adresini verir.
	- `swap()` İki vektörün içeriğini çok hızlı değiştirir.
	- `begin()` İlk elemana iterator döndürür.
	- `end()` Son elemandan sonraki iterator.

!!! note "`std::vector<bool>` neden özel bir uzmanlık/dikkat gerektirir?"
    - C++ standardı tarafından space optimizasyonu yapılması için özelleştirilmiş bir sınıftır. Standart bir `vector` her eleman için en az 1 byte yer kaplarken, `std::vector<bool>` her bir `bool` değeri için bellekten sadece **1 bit** ayırır.
	- Bit olduğu için doğrudan adres(`&`) alınamaz.
    - Thread-safety açısından tehlikelidir; aynı byte içindeki farklı bitlere farklı thread'lerden yazma yapmak **"data race"** yaratır
    - Eğer bu optimizasyonu istemiyorsak `std::vector<char>` veya `std::bitset` tercih edilmelidir.

!!! note "`clear()`,  bellek işletim sistemine geri iade edilir mi?"
	1. `vec.clear()` çağrıldığında içerideki nesnelerin destructor'ları çağrılır ve `size` 0 olur; ancak `capacity` değişmez. Yani bellek hala o `vector` tarafından rezerve edilmiş durumdadır.
	2. **`shrink_to_fit()`:** Derleyiciye kapasiteyi boyuta eşitlemesi için bir istekte bulunuruz. 
	3. **Swap Trick:** Boş ve geçici bir vector oluşturup mevcut vector ile swap yaparız. Bu sayede bellek boyutunu iade etmiş oluruz.
		

!!! tip "Not"
	Bir `vector`ün ortasından `erase()` ile eleman silmek, silinen elemandan sonraki tüm elemanların sola doğru kaydırılmasına (`copy/move`) sebep olur. Bunu bir döngü (`for`) içinde yapmak `O(N^2)` zaman karmaşıklığına yol açar ve performansı felç eder. Bunun yerine **Erase-Remove Idiom** kullanmalıyız. `std::remove` veya `std::remove_if` algoritması silinecek elemanları vector'ün sonuna taşır ve bize geçerli elemanların bittiği yeni bir iterator döner. Sonra tek bir `erase` çağrısı ile arkada kalan çöpleri sileriz. Bu işlem `O(N)` karmaşıklığındadır.

!!! note "Not"
	`O(N)` İngilizcedeki **"Order of"** (mertebesinden, derecesinden) ifadesini temsil eder. Matematiksel olarak fonksiyonların büyüme hızını sınırlandırmak için kullanılır. Buradaki **N**, algoritmaya fonksiyon girdisi olarak verilen **veri miktarıdır**

#### Deque

`std::deque` (Double-Ended Queue) , adından da anlaşılacağı gibi **hem başından hem de sonundan** çok hızlı bir şekilde eleman ekleme (`push_front`, `push_back`) ve silme (`pop_front`, `pop_back`) işlemlerini yapabilen bir ardışık konteynerdir. `std::vector` tek bir dinamik dizi iken, `std::deque` **parçalı bir bellek yapısı** kullanır. Arka planda, sabit büyüklükte küçük bellek blokları (chunks/pages) vardır. Bu blokların adreslerini tutan bir de **Merkezi Harita (Map/Directory)** mekanizması bulunur. Bu harita aslında pointer'lardan oluşan bir dizidir.

- **Başa Eleman Ekleme Performansı:** `vector`ün başına eleman eklemek `O(N)` karmaşıklıktadır çünkü tüm elemanları sağa kaydırmak gerekir. `deque` ise başa eleman ekleneceği zaman, eğer mevcut ilk blokta yer yoksa, belleğin başka bir yerinde **yeni bir blok açar** ve merkezi haritaya ekler. Elemanları kaydırmaz! Bu yüzden başa eleman eklemek de tıpkı sona eklemek gibi **`O(1)`** yani sabit zaman alır.
- **Kesintisiz Bellek Garantisi Yoktur.**
- **Rastgele Erişim (Random Access):** `deq[5]` veya `deq.at(5)` dediğinde hala `O(1)` sürede elemana erişebilirsin. Ancak arka planda önce merkezi haritaya bakıp, sonra doğru bloğu bulup, onun içindeki indekse gittiği için `std::vector`e göre ufak bir pointer aritmetiği maliyeti (indirection) vardır. `vector` bu konuda her zaman daha hızlıdır.
- **Bellek Tüketimi:** `deque`, merkezi harita yönetimi ve her ihtimale karşı önceden açılan bloklar yüzünden küçük veri setlerinde `vector`den daha fazla bellek harcar.

!!! note "Not"
	- `std::vector` kapasitesi dolduğunda tüm belleği kopyalamak veya taşımak zorundadır. Bu durum büyük veri setlerinde ani performans düşüşlerine (latency spikes) sebep olur.
	- `std::deque` ise büyürken eski elemanları asla taşımaz, sadece yeni bellek blokları bağlar. Bu, bellek yönetimini daha stabil ve öngörülebilir kılar. Ayrıca `std::queue` yapısı doğası gereği hem baştan silme (`pop`) hem sondan ekleme (`push`) yaptığı için `deque`ün çift yönlü $O(1)$ performansı biçilmiş kaftandır.
	- `std::deque`ün ortasına eleman eklemek veya silmek $O(N)$ karmaşıklıktadır. Ancak `deque` akıllı bir optimizasyon yapar: Eklenen/silinen yerin, başa mı yoksa sona mı daha yakın olduğunu hesaplar. Hangi uca daha yakınsa, sadece o taraftaki elemanları kaydırır.

```cpp
// Deque -> Vector ile aynı
push_back(), pop_back(), insert(), erase(), clear()
size(), empty(), front(), back(), at(), operator[],
begin(), end(), rbegin(), rend(), emplace_back(), emplace()

// Deque olmayan
capacity(), reserve(), shrink_to_fit()

// Deque’de olan
push_front(), pop_front() 
```

- **Mükemmel Araya Ekleme/Silme Performansı:** Listenin neresinde olursan ol, bir eleman eklemek veya silmek sadece pointer'ların yönünü değiştirmekten ibarettir. Bu yüzden araya eleman ekleme/silme işlemi **O(1) (Sabit Zaman)** alır. `vector`deki gibi elemanları sağa sola kaydırmak veya belleği yeniden büyütmek (reallocation) diye bir dert yoktur.

- **Rastgele Erişim Yoktur (No Random Access):** `list[5]` diyerek 5. indekse doğrudan zıplayamazsın! Çünkü elemanların RAM'deki yerleri belirsizdir. 5. elemana ulaşmak için `begin()` iterator'ından başlayıp pointer'ları tek tek (`next -> next -> next...`) takip etmen gerekir. Bu yüzden rastgele erişim maliyeti **O(N)**'dir.


#### List - Forward_list

`std::list` Elemanları bellekte **ardışık OLMAYAN** bir konteynerdir. Bellekteki her bir eleman bir **Node (Düğüm)** olarak adlandırılır. Her bir node şunları içerir:

1. Tutulacak gerçek veri (Value).
2. Kendisinden önceki düğümün adresini tutan bir pointer (`prev`).
3. Kendisinden sonraki düğümün adresini tutan bir pointer (`next`).
- **`unique()`**: Arka arkaya gelen tekrar eden elemanları siler. (Genelde önce `sort()` yapılır, sonra bu çağrılır).

!!! note "Not"
	- **`std::deque` (Parçalı Dizi):** Sabit büyüklükteki bellek bloklarının (chunks) bir merkezi harita (map) ile yönetilmesiyle oluşur. Blokların kendi içindeki elemanlar ardışıktır.
	- **`std::list` (Bağlı Liste):** Her bir eleman (node) belleğin tamamen bağımsız yerlerindedir. Elemanlar birbirine `prev` ve `next` pointer'ları ile zincirleme bağlıdır.

| **Özellik** | **std::deque** | **std::list** |
| --- | --- | --- |
| **Rastgele Erişim (`operator[]`)** | **Var** - O(1) sürede (Ufak bir pointer aritmetiği ile). | **Yok** - O(N) sürede (Baştan başlayıp tek tek saymak gerekir). |
| **Başa/Sona Ekleme & Silme** | O(1) (Çok hızlı, yeni blok açar). | O(1) (Çok hızlı, sadece pointer bağlar). |
| **Araya Eleman Ekleme & Silme** | O(N) (Elemanların kaydırılması gerekir). | **O(1)** (Yalnızca pointer adresleri güncellenir). |
| **Bellek Tüketimi (Overhead)** | **Düşük** (Sadece blok başı ve harita için ufak bir ek yük). | **Yüksek** (Her eleman için ekstra 2 tane pointer (16 byte) saklanır). |
| **Cache Uyumu (Cache Locality)** | **Yüksek** (Blok içindeki elemanlar ardışık olduğu için CPU cache'i sever). | **Çok Düşük** (Düğümler RAM'e dağıldığı için sürekli Cache Miss yaşanır). |


```cpp
// List -> Vector ile aynı
push_back(), pop_back(), insert(), erase(), clear()
size(), empty(), front(), back(), 
begin(), end(), rbegin(), rend(), emplace_back(), emplace()

// List olmayan
capacity(), reserve(), shrink_to_fit(), at(), operator[],

// List'de olan
push_front(), pop_front() 
```

- **`sort()`**: Listeyi kendi içinde, elemanları bellekte hiç oynatmadan, sadece pointer'ların bağlarını güncelleyerek sıralar. `O(N log N)` karmaşıklıktadır.
- **`reverse()`**: Listenin sırasını tersine çevirir (`O(N)`).
- **`unique()`**: Arka arkaya gelen tekrar eden elemanları siler. (Genelde önce `sort()` yapılır, sonra bu çağrılır).
- **`splice(iterator, other_list)`**: Harika bir senior oyuncağıdır! Bir listedeki elemanları veya listenin tamamını, **hiçbir kopyalama veya taşıma yapmadan**, sadece pointer bağlarını koparıp hedef listeye bağlayarak aktarır (`O(1)`).
- `std::list` iki yönlüydü; her düğümde hem ileri (`next`) hem geri (`prev`) pointer'ı bulunuyordu. `std::forward_list` ise **sadece ileriye doğru** hareket edebilir.
    - Tutulacak gerçek Value.
    - Kendisinden sonraki düğümün adresini tutan tek bir pointer (`next`).

!!! note "Not"
	C++ tasarımcıları bu konteyner şu felsefeyle geliştirdi: **"Ham bir C tek yönlü bağlı listesinden daha fazla bellek kaplamasın ve daha yavaş olmasın."**

	Geriye doğru pointer tutmadığı için, `std::list`'e göre eleman başına **8 byte** (64-bit sistemlerde) bellek tasarrufu sağlar. Hatta bu yapının kendi kontrol bloğunda listenin boyutunu tutan bir `size` değişkeni bile **yoktur**. Yani `forward_list.size()` diye bir fonksiyon bulamazsın; boyutu öğrenmek istersen baştan sona tüm elemanları tek tek sayman gerekir (O(N)).

- Tek yönlü bağlı listelerde bir elemanın *önüne* eleman eklemek imkansızdır, çünkü geriye dönüp pointer güncellenemez. Bu yüzden `forward_list` alışılagelmiş fonksiyonlar yerine adında **`_after`** geçen özel fonksiyonlar kullanır:
    - **`push_front(val)`**: Listenin en başına O(1) sürede eleman ekler. (Sona ekleme yani `push_back` yoktur! Çünkü son elemana gitmek için tüm listeyi yürümek gerekir).
    - **`insert_after(iterator, val)`**: Verilen iterator'ın işaret ettiği elemanın **arkasına** O(1) sürede yeni eleman ekler.
    - **`erase_after(iterator)`**: Verilen iterator'ın işaret ettiği elemanın **arkasındaki** elemanı O(1) sürede listeden siler.

#### Array

- C++11 ile hayatımıza giren ve **boyutu derleme zamanında (compile-time) sabit olan** bir ardışık konteynerdir. (**runtime’da büyüyemez/küçülemez**)
- En kritik özelliği şudur: `std::vector` elemanlarını **Heap** bellekte tutarken, `std::array` elemanlarını tıpkı ham bir C dizisi (`int arr[5]`) gibi doğrudan **Stack** bellekte (veya nesnenin gömülü olduğu yerde) tutur.
- Şablon tanımı şu şekildedir: `std::array<T, N>`. Burada `T` veri tipini, `N` ise eleman sayısını belirtir. `N` değeri kesinlikle derleme zamanında bilinen bir sabit (constant expression) olmak zorundadır.
- C++ standart kütüphanesinin en hafif, en performanslı ve saf C dizilerine en yakın konteynerıdır.
- C++ standartlarına önem verir. `std::array`, ham C dizilerinin tüm performans avantajlarını korurken, sıfır ek maliyetle (**zero-overhead**) bize şu harika özellikleri sunur:
    - **Boyutunu Bilir:** `arr.size()` diyerek boyutunu anında alabilirsin. Ham dizilerdeki gibi boyutu ayrı bir değişkende taşımak veya fonksiyonlara pointer ile birlikte boyut geçmek zorunda kalmazsın.
    - **Güvenli Erişim:** `arr.at(index)` fonksiyonu sayesinde, sınırların dışına çıkılıp çıkılmadığı (out-of-bounds) kontrol edilir. Eğer sınır aşılırsa `std::out_of_range` hatası fırlatır.
    - **Kopyalanabilirlik:** Ham dizileri doğrudan birbirine atayamazsın (`arr1 = arr2` çalışmaz). Ama `std::array` standart bir nesne olduğu için doğrudan kopyalanabilir veya fonksiyonlardan geri döndürülebilir.
    - **STL Algoritmalarıyla Uyum:** `std::sort`, `std::find` gibi tüm standart algoritmalarla kusursuz çalışır.

```cpp
// Tanımlama ve Değer Atama
std::array<int, 5> modernArr = {5, 2, 9, 1, 6};

// STL Algoritmalarıyla doğrudan kullanım
std::sort(modernArr.begin(), modernArr.end());

// Güvenli erişim
try {
    modernArr.at(10) = 100; // Sınır dışı! Hata fırlatır.
} catch (const std::out_of_range& e) {
    std::cout << "Hata yakalandı: " << e.what() << "\n";
}

// Doğrudan kopyalama
std::array<int, 5> yeniArr = modernArr; 
return 0;
```

```cpp
// Olan Fonksiyonlar 
size(), empty(), front(),back()

begin(), end(), rbegin(), rend()

at(), operator[], fill(), swap(), data()
```

|  | **Bellek Konumu (RAM)** | **Rastgele Erişim ([])** | **En Güçlü Olduğu İşlem** | **En Büyük Zafiyeti** |
| --- | --- | --- | --- | --- |
| **`array`** | **Stack** (Ardışık) | Çok Hızlı (O(1)) | Sıfır bellek yükü, maksimum hız | Boyutu değiştirilemez |
| **`vector`** | **Heap** (Ardışık) | Çok Hızlı (O(1)) | Sona ekleme ve Cache dostu olması | Yeniden büyüme (Reallocation) maliyeti |
| **`deque`** | **Heap** (Parçalı Bloklar) | Hızlı (O(1) - Ufak maliyetli) | Hem başa hem sona O(1) ekleme/silme | Ortadan eleman silerken ağır kaydırma maliyeti |
| **`list`** | **Heap** (Dağınık Düğümler) | Yavaş (O(N) - İndex yok) | Araya kopyalamasız eleman ekleme/silme | Berbat CPU Cache performansı, yüksek bellek israfı |

### Associative Containers (İlişkisel Kapsayıcılar)

- Genel olarak iç yapısı **Red-Black Tree (**Self-balancing Binary Search Tree**)**’dir.
- **Otomatik Sıralama:** İçine eklenen her eleman, ağaç yapısı gereği anında (küçükten büyüğe) sıralanır.
- **Hızlı Arama/Ekleme/Silme:** Rastgele erişim yoktur ama bir elemanı bulmak, eklemek veya silmek sadece **O(log N)**  alır. Milyonlarca eleman içinde bile bir şeyi bulmak sadece 20-30 adıma biter.

1. `std::set` Matematikteki "küme" kavramının birebir karşılığıdır. İçindeki elemanlar **benzersizdir (unique)**. Aynı elemandan iki tane ekleyemezsin.
    - `insert()` Set’e eleman ekler. Eğer eleman zaten varsa eklemez.
    - `emplace()` insert ile aynı işi yapar ama elemanı **yerinde oluşturur** gereksiz kopya/move azaltır.
    - `erase()` verilen değeri siler.
    - `clear()` set içindeki **tüm elemanları siler** set boş hale gelir.
    - `find()` elemanı arar. Bulursa iterator döndürür bulamazsa `end()` döndürür.
    - `count()` eleman var mı yok mu kontrol eder sonuç sadece 1 ve 0 dır. `contains()` aynı işe yarar **false** veya **true** döner.
    - `size()` eleman sayısını döndürür.
    - `empty()` boşmu kontrol eder.
    - `begin()` en küçük (sorted structure olduğu için) elemanı gösterir. `rbegin()` en büyük elemandan başlar (ters iterator)
    - `end()` son elemandan sonra gelen “geçersiz” konumu gösterir direkt dereference edilmez. `rend()` ters iterasyonun sonu.
    - `lower_bound()` belirlenen değerden küçük olan ilk elemanı bulur. `upper_bound()` büyük olan ilk elemanı bulur.
2. **`std::multiset`** `std::set` ile tamamen aynıdır, tek bir farkı vardır: **Aynı elemandan birden fazla barındırabilir.**
3. **`std::map`** Geliştiricilerin en çok kullandığı yapılardan biridir. 
    - Verileri **Key-Value (Anahtar-Değer)** çiftleri olarak tutar. **Key (Anahtar):** Benzersiz olmak zorundadır. Ağacın sıralanması bu anahtara göre yapılır.
    - **Value (Değer):** O anahtara karşılık gelen veridir. Tekrar edebilir.
    - Arka planda her eleman bir `std::pair<const Key, Value>` nesnesidir.
    - `insert()` Set’e eleman ekler. Eğer eleman zaten varsa eklemez.
    - `emplace()` insert ile aynı işi yapar ama elemanı **yerinde oluşturur** gereksiz kopya/move azaltır.
    - `operator[]` en çok kullanılan yöntem key yoksa oluşturur varsa günceller.
    - `at()` key ile erişim key yoksa exception fırlatır.
    - `erase()` key siler.
    - `clear()` tüm elemanları siler
    - `find()` key arar yoksa `end()` döner.
    - `count()` key var mı? Sonuç 1 - 0. contains() **false** ve **true**
    - `size()`, `empty()`, `begin()`, `end()`, `rbegin()` , `rend()`
    - `lower_bound()` , `upper_bound()`
    - `equal_range()`,  pair döner → lower_bound, upper_bound
4. `std::multimap` `std::map`'in **aynı anahtardan (key) birden fazla** barındırabilen versiyonudur.
    - **Çok kritik not:** `multimap` içinde **`operator[]` YOKTUR**. Çünkü aynı anahtardan birkaç tane olabileceği için `m[key]` dediğinde hangi değeri getireceğini derleyici bilemez.
    - Eleman eklemek için `insert` veya `emplace` kullanılmalıdır.

### Unordered Containers (Sıralanmamış Konteynerler)

- C++11 ile standart kütüphaneye eklenen `unordered_set` ve `unordered_map`, elemanları belirli bir sıraya göre değil, **Hash Table (Karma Tablo)** veri yapısını kullanarak depolayan konteynerlerdir.
- Bir `std::unordered_map` oluşturduğumuzda, derleyici bellekte yan yana dizilmiş kutucuklar (yani bir array) hazırlar. Biz bu kutucukların her birine **Bucket (Kova)** diyoruz.

```cpp
// 1. Haritamızı oluşturuyoruz
std::unordered_map<std::string, int> ogrenci_notlari;

// 2. Eleman ekleme işlemi
ogrenci_notlari["Ahmet"] = 85;
```

- **`std::map`**: Kitapların türüne ve yazar adına göre alfabetik dizildiği raflardır. Araya yeni bir kitap eklemek zordur (rafları kaydırmak gerekir), ama gidip "Bana A ile C harfi arasındaki tüm kitapları getir" demek çok kolaydır.
- `unordered_set` Bir değerin yalnızca **bir kez** bulunmasına izin veren kümedir.
- **`std::unordered_map`**: Emanet dolapları gibidir. Her kitabın ismini bir formüle sokarsınız, size bir dolap numarası verir, gidip kitaba doğrudan ulaşırsınız. Çok hızlıdır ama dolapları açtığınızda kitaplar karmakarışıktır. "Bana alfabetik sıra ver" derseniz, tüm dolapları tek tek açıp baştan sıralamanız gerekir.
- Kullanılma nedenleri: Sıralama gerekmiyorsa, En hızlı arama isteniyorsa, Anahtar bazlı erişim yapılıyorsa

| Container | Veri Yapısı | Arama | Ekleme | Silme |
| --- | --- | --- | --- | --- |
| `set`, `map` | Red-Black Tree | O(log n) | O(log n) | O(log n) |
| `unordered_set`, `unordered_map` | Hash Table | Ortalama O(1) | Ortalama O(1) | Ortalama O(1) |

| Fonksiyon | Açıklama |
| --- | --- |
| `insert()` | Eleman ekler. |
| `emplace()` | Elemanı yerinde (in-place) oluşturup ekler. |
| `find()` | Elemanı/anahtarı arar, iterator döndürür. |
| `count()` | Varsa `1`, yoksa `0` döndürür. |
| `contains()` (C++20) | Eleman var mı diye kontrol eder. |
| `erase()` | Eleman siler. |
| `clear()` | Tüm elemanları siler. |
| `size()` | Eleman sayısını verir. |
| `empty()` | Container boş mu kontrol eder. |
| `begin()`, `end()` | Iterasyon için başlangıç ve bitiş iteratorları. |


| `unordered_map'e` Özel Fonksiyon | Açıklama |
| --- | --- |
| `operator[]` | Anahtar üzerinden erişim/ekleme yapar. |
| `at()` | Anahtarın değerini döndürür, yoksa exception fırlatır. |
| `try_emplace()` | Anahtar yoksa ekler. |
| `insert_or_assign()` | Varsa günceller, yoksa ekler. |

### Container Adaptors

- **`stack**:` **LIFO (Last In, First Out - Son Giren İlk Çıkar)** prensibiyle çalışan bir adaptördür. Bir masanın üzerine üst üste konulmuş kitaplar gibi düşünebilirsin. Sadece en üstteki kitabı alabilirsin (`top`), yeni kitabı en üste koyabilirsin (`push`) ve en üstteki kitabı kaldırabilirsin (`pop`).
- **`queue:`** **FIFO (First In, First Out - İlk Giren İlk Çıkar)** prensibiyle çalışır. Tam olarak bir banka veya süpermarket kuyruğudur. Kuyruğa giren ilk kişi ilk hizmeti alır ve çıkar.
Elemanlar her zaman kuyruğun arkasından (`back`) eklenir ve her zaman kuyruğun önünden (`front`) çıkarılır. `std::queue` da varsayılan olarak arka planda **`std::deque`** yapısını kullanır. Çünkü `std::vector` kuyruk için kötü bir seçimdir; vektörün önünden eleman silmek tüm elemanların kaydırılmasına ($O(n)$) yol açar, oysa `std::deque` hem önden hem arkadan $O(1)$ ile eleman silebilir.
- **`priority_queue:`** normal bir kuyruk gibi elemanların geliş sırasına bakmaz. Her elemanın bir **önceliği (priority)** vardır. Kuyruktan her zaman **önceliği en yüksek olan** eleman ilk önce çıkar.

### STL Algorithms

- `std::sort`, elemanları belirli bir düzene göre sıralar.
- `std::find` ve `std::count` Bu iki algoritma, veri setini baştan sona lineer olarak tarar. Bu yüzden zaman karmaşıklıkları **O(n)**'dir.
    - `std::find`: Aranan elemanı bulduğu an taramayı durdurur ve o elemanı gösteren bir iterator döner. Bulamazsa listenin sonunu (`end()`) döner.
    - `std::count`: Durmaz! Listenin sonuna kadar gidip aranan elemandan kaç tane olduğunu sayar.
- `std::transform` Bir veri setindeki tüm elemanları bir fonksiyondan geçirerek değiştirmek ve sonucu ya aynı konteynere ya da farklı bir konteynere yazmak için kullanılır.
- `std::accumulate` Bu algoritma diğerlerinden farklı olarak `<numeric>` kütüphanesinde yaşar. Belirtilen aralıktaki tüm elemanları, verdiğiniz bir başlangıç değerinin üzerine ekleyerek (veya başka bir matematiksel işlemle birleştirerek) tek bir sonuç üretir (Reduce/Fold işlemi). Zaman karmaşıklığı **$O(n)$**'dir.

## Modern C++ (C++11 ve Sonrası)

- `auto`, değişkenin türünü sağ taraftaki **başlatıcı ifadeden (initializer)** çıkarır. Buradaki en kritik kural şudur: `auto` kullanımı tamamen **Derleme Zamanında (Compile-time)** çözülür. Çalışma zamanında (Runtime) hiçbir performans kaybı veya ek maliyet **getirmez**. Kod derlendiğinde, `auto` yazan yerde gerçek tür neyse o yazar.
- `decltype` (declared type), içerisine yazılan ifadenin veya değişkenin tanımlanmış olan **tam türünü (exact type)** const ve referans niteliklerini **asla bozmadan** bize verir. `auto` gibi sağ taraftaki değere bakıp çıkarım yapmaz; doğrudan ifadenin deklarasyonuna bakar.
- **Rule of Three:** Copy Constructor, Assignment Operator, Destructor
- std::atomic: ise **Lock-Free (Kilit gerektirmeyen)** bir dünya sunar. İşletim sistemini araya sokmadan, doğrudan **CPU çekirdeklerinin donanımsal yeteneklerini (Atomic Instructions)** kullanarak senkronizasyon sağlar. Çekirdekler uyutulup uyandırılmaz; işlem doğrudan işlemci mimarisi seviyesinde bölünemez tek bir adımda halledilir.


## RAII (Resource Acquisition Is Initialization)

Modern C++ mimarisinin, bellek güvenliğinin ve "sıfır bellek sızıntısı" (zero memory leak) garantisinin arkasındaki en büyük felsefeye geldik: **RAII (Resource Acquisition Is Initialization - Kaynak Edinimi İlklendirmedir)**.

C++'ta bir fonksiyon içinde hata (exception) fırlatıldığında veya fonksiyon erken sonlandığında (`return`), o ana kadar oluşturulmuş tüm yerel nesnelerin yıkıcı fonksiyonlarının (`destructor`) otomatik olarak çağrıldığını (Stack Unwinding) biliyoruz. İşte RAII, dilin bu garantisini kullanarak kaynak yönetimini otomatize eder

- **Bellek İçin:** `std::unique_ptr`, `std::shared_ptr` (Asla `delete` yazmazsınız).
- **Dosya İçin:** `std::ifstream`, `std::ofstream` (Dosyayı otomatik kapatır).
- **Thread Kilidi İçin:** `std::lock_guard`, `std::unique_lock` (Mutex kilidini otomatik açar).

## Çoklu İş Parçacığı (Multithreading)

### `std::thread` ve Çalışma Prensibi

Bir `std::thread` nesnesi oluşturduğumuzda, işletim sistemi seviyesinde yeni bir yürütme yolu (execution path) tetikleriz. Bu yeni thread, ana programdan bağımsız olarak kendisine verdiğimiz fonksiyonu işletmeye başlar.

Bir thread nesnesinin yaşam döngüsünü yönetirken uyulması gereken çok katı bir kural vardır: **Bir `std::thread` nesnesi scope dışına çıkıp yok edilmeden (`destructor`'ı çalışmadan) önce kesinlikle ya `join()` ya da `detach()` edilmelidir.**

Eğer thread nesnesini bu ikisinden birini yapmadan kendi haline bırakırsan, destructor içerisindeki kontrol mekanizması **`std::terminate()`** fonksiyonunu çağırır ve programı anında çökertir (crash).

- **`join()` (Bekleme):** Ana thread, çağrılan thread'in işini tamamen bitirmesini bekler. Thread bittiği an kaynakları temizlenir ve thread nesnesi "joinable" durumdan çıkar.
- **`detach()` (Bağımsız Bırakma):** Thread'in ana programla olan bağını koparır. Thread arka planda (background/daemon olarak) kendi başına dönmeye devam eder. İşletim sistemi thread bittiğinde kaynaklarını otomatik temizler. Ancak ana thread (main) bittiğinde detached thread'ler de anında sonlandırılır.

Birden fazla thread aynı bellek alanındaki bir değişkene aynı anda erişip en az biri yazma (`write`) işlemi yapıyorsa, orada **Data Race (Veri Yarışı)** oluşur. Data Race, C++ dünyasında **Undefined Behavior** (Belirsiz Davranış) demektir. Belleği korumak için senkronizasyon mekanizmaları (kilitler) kullanırız.

### 1. `std::mutex` (Mutual Exclusion)

En temel kilit mekanizmasıdır. Bir kritik bölgeye (critical section) aynı anda sadece **tek bir thread'in** girmesine izin verir. Diğer thread'ler kilit açılana kadar sırada bekler (block olurlar).

### 2. `std::recursive_mutex`

Normal bir `std::mutex`, zaten kilitlemiş olan thread tarafından **tekrar kilitlenmeye çalışılırsa** kendi kendini kilitleme (Self-Deadlock) hatasına yol açar.

`std::recursive_mutex` ise, kilidi elinde tutan thread'in aynı kilidi **defalarca (içe içe) kilitlemesine** izin verir. Genellikle özyinelemeli (recursive) fonksiyonlarda veya bir üye fonksiyonun başka bir üye fonksiyonu çağırdığı sınıf tasarımlarında kullanılır.

**3. `std::shared_mutex` (C++17)**
Finansal sistemlerde veya veritabanı mimarilerinde en sık kullanılan kilit türüdür. **Reader-Writer Lock** olarak da bilinir.
Şu felsefeye dayanır: Aynı anda 100 farklı thread'in bir veriyi sadece **okumasında (read)** hiçbir sakınca yoktur. Ancak bir thread veriyi **güncelleyecekse (write)**, o sırada kimsenin okumaması ve başka kimsenin yazmaması gerekir.
• **Shared Lock (Okuyucu Kilidi):** Birden fazla thread aynı anda shared kilidi alıp veriyi paralel okuyabilir ($O(1)$ paralellik).
• **Exclusive Lock (Yazıcı Kilidi):** Sadece tek bir thread alabilir. Okuyucuların ve diğer yazıcıların tamamen bitmesini bekler.

## 17.5 Futures ve Async

- std::future
- std::promise
- std::async

# İleri Seviye OOP ve Tasarım

## 16.1 SOLID Prensipleri

- SRP
- OCP
- LSP
- ISP
- DIP

## 16.2 Design Patterns

- Singleton
- Factory
- Builder
- Observer
- Strategy
- Adapter
- Decorator
- Command

# 21. Algoritmalar

## 21.1 Sorting

- Bubble Sort
- Selection Sort
- Insertion Sort
- Merge Sort
- Quick Sort
- Heap Sort

## 21.2 Searching

- Linear Search
- Binary Search

## 21.3 Graph Algorithms

- BFS
- DFS
- Dijkstra
- Bellman-Ford
- Floyd-Warshall
- A*