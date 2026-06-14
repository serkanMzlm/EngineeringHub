# Python 
- `#` Satır içi yorum başlatır.
- `\` Satır devamı için kullanılır. `\\` Kaçış karakteri olarak tek bir `\` üretir.
- `"""...""" / '''...'''`: Çok satırlı string ve dokümantasyon (docstring) tanımlamak için kullanılır.
- `**`: Üst alma işlemi yapar. (`pow()` ile aynı işlemi yapar)
- **Immutable(Değiştirilemez):** int, float, complex, str, tuple
- **Mutable(Değiştirilebilir):** list, dict, set
- **Döngüler - Koşullar:** `for, while`, `if – elif – else`
    - **pass:** Gövdesi boş bir blok bırakmak için (ileride doldurmak üzere).
    - **break:** Döngüyü tamamen sonlandırır.
    - **continue:** Döngünün bir sonraki yinelemesine atla
    - `and` ve `or` ifadeler birleştirebilir, `not` ile terslenir.
    - `in` öğende olup olmadığını kontrol eder. `is` kimlik (aynı nesneye işaret etme) kontrol eder. 
    - `for - while` döngüsüne bir `else` bloğu ekleyebilirsiniz. Döngü normal sonlanırsa (yani `break` ile kesilmezse) else çalışır:
- `:=` (Walrus Operatörü), bir ifadeye değer atarken aynı anda o değeri kullanmayı sağlar. (Python 3.8+)
- `print(*objs, sep=' ', end='\n', file=sys.stdout, flush=False)`
    - `sep` Öğeler arası ayırıcı.
    - `end` Sonuna eklenen karakter.
    - `file` Yazma hedefi (dosya veya başka bir çıktı akışı).
    - `flush` Anında yazmayı zorlar.
- `input(prompt)` Kullanıcıdan girdi alır **(her zaman string döner)**.
- `*` operatörü
    - Fonksiyon çağrısında `*iterable`: elemanları ayrı argüman olarak geçirir.
    - String çarpımında `"deneme" * 3 ‑> "denemedenedeme"`.
- `split(sep=None, maxsplit=-1) / rsplit(sep=None, maxsplit=-1) / splitlines(keepends=False)`
    - `split` Varsayılan boşluk/kaydırma karakterlerine göre böler.
    - `rsplit` Sağdan başlayarak böler (özellikle maxsplit kullanırken fark eder).
    - `splitlines` Satır sonu karakterlerine göre böler; keepends=True satır sonlarını korur.
- `strip(chars=None) / lstrip(chars=None) / rstrip(chars=None)` Başlangıç ve/veya sondaki boşluk ya da chars parametresindeki karakterleri siler.
- `join(iterable)` Iterable içindeki tüm öğeleri birleştirip tek bir string döner; self araya konur.
- `count(sub[, start[, end]])` Bir alt string’in kaç kez geçtiğini sayar.
- `index(sub[, start[, end]]) / rindex(sub[, start[, end]])` 
    - `index` İlk eşleşmenin başlangıç indeksini döner, bulunamazsa ValueError.
    - `rindex` Sağdan aramaya başlar.
- `find(sub[, start[, end]]) / rfind(sub[, start[, end]])`
    - `find` İlk eşleşmenin indeksini döner; bulunamazsa -1.
    - `rfind` Sağdan arar.
- `center(width[, fillchar]) / ljust(width[, fillchar]) / rjust(width[, fillchar])` Metni belirtilen genişliğe ortalar veya sola/sağa yaslar; boşluk dışı karakter için fillchar verebilirsiniz.
- `zfill(width)` Sağa yaslayarak sol tarafı sıfır ('0') ile doldurur.
- `partition(sep) / rpartition(sep)` String’i üç parçaya ayırır: (önce, sep, sonra). rpartition sağdan başlar.
- `encode(encoding="utf-8", errors="strict")` String’i belirtilen kodlamaya göre byte dizisine çevirir.
- `str.maketrans(x, y=None, z=None)` & `translate(table)`
    - `maketrans(x, y)` İki string’in karakterlerini eşleştiren bir dönüşüm tablosu (sözlük) oluşturur.
    - `maketrans('', '', z)` z içindeki karakterleri kaldırmak için tablo üretir.
    - `translate(table)` String’i tabloya göre dönüştürür veya siler.

| Genel Fonksiyon | Açıklama |
|--------|--------|
| `eval(expr)`                        | expr string’ini değerlendirir, sonuç döner.  |
| `exec(code)`                        | code string’ini çalıştırır, değer döndürmez.  |
| `compile(...)`                      | String’i çalıştırılabilir koda çevirir.  |
| `globals()`                         | Global isim alanı sözlüğünü döner.  |
| `locals()`                          | Mevcut local isim alanı sözlüğünü döner.  |
| `callable(obj)`                     | obj() çağrılabilir mi? (True/False)  |
| `hash(obj)`                         | obj hash değerini döner.  |
| `isinstance(obj, type)`             | Tür denetimi yapar.   |
| `issubclass(cls, classinfo)`        |  Alt sınıf sorgusu.  |
| `dir(obj)`                          | obj’in metot/özellik adlarını listeler.  |
| `vars([obj])`                       | obj’in __dict__ öğesini döner (varsayılan local/global).  |
| `help(obj)`                         | Yardım sistemini açar, dokümantasyonu gösterir.  |
| `id(obj)`                           | obj’in benzersiz kimlik numarası (bellek adresi).   |
| `input(prompt)`                     | Kullanıcıdan girdi alır (string).  |
| `exit(), quit()`                    | Çıkış işlevi (REPL için)  |
| `replace(old, new, count=-1)`       | String içinde değişim yapılmasını sağlar.  |
| `abs(x)`                            |  Mutlak değer |
| `pow(x, y, z)`                      |  `(x**y) % z`   |
| `round(x, n)`                       |  x’i n ondalığa yuvarlar (default n=0). |
| `divmod(a, b)`                      |  `(a // b, a % b)` döner.   |
| `max() / min()`                     | En büyük / küçük eleman |
| `sum(iterable, start=0)`            | Toplam. (start varsayılan 0)  |
| `range(start, stop, step)`          | Sayı dizisi üretir (start varsayılan 0, step varsayılan 1)  |
| `int(x, base)`, `float(x)`          | x’i tam / float türüne çevirir.  |
| `complex(re, im=0)`, `str(x)`       | x’i karmaşık / string türüne çevirir.  |
| `bytes(x, encoding)`                | x’i bytes yapar.  |
| `bytearray(x, …)`                   | Değiştirilebilir bytes.   |
| `bin(x), oct(x), hex(x)`            | x’i sırasıyla ikili, sekizli, onaltılıya çevirir.  |
| `ord(c)`                            | Tek bir karakterin Unicode kod noktasını (tamsayı) döndürür.  |
| `chr(i)`                            | Verilen Unicode kod noktasına karşılık gelen karakteri döndürür.  |
| `len(x)`                            |  Eleman sayısı / uzunluk.  |
| `type(obj)`                         |  Nesnenin türü  |
| `sorted(iterable, key, reverse)`    |  Sıralı liste döner.   |
| `reversed(seq)`                     |  Ters yönde iterator döner.  |
| `all(iter)`                         |  Tüm öğeler True ise True   |
| `any(iter)`                         |  En az bir öğe True ise True   |
| `enumerate(iter, start=0)`          |  (index, value) çiftlerinden iter oluşturur   |
| `zip(*iterables)`                   |  Paralel iterasyon için tuple iterator  |
| `filter(func, iterable)`            |  func(item) True ise öğeyi geçirir  |
| `map(func, iterable)`               |  func(item) dönen yeni öğe iteratoru  |
| `slice(start, stop, step)`          |  Dilim objesi (obj[slice])  |


```py title="Temel Kullanımlar" linenums="1"
a = b = 10                       # Birden fazla değişkene değer atama
a, b, c = 10, 20, 30             # Çoklu atama
a, b = b, a                      # swap (a->b, b->a)

if (n := len(input("deger: "))) < 10:
    print(f"Girdi {n} karakterden kısa")

l = [1,2,3,4,5,6]
print(list(filter(lambda x: x%2, l)))       # [1,3,5]
print(list(map(lambda x: x*x, l)))          # [1,4,9,16,25,36]

# Direkt liste halinde görmek için `*` kullanılabilir 
print(*enumerate("istihza")) # Ya da for kullanılır
for idx, harf in enumerate("istihza", start=1):
    print(idx, harf)


exec("print('Merhaba')")  # print yazılmış gibi davranır
result = eval("10 + 20")  # 30

with open("deneme.txt", "w") as dosya:
    ad = input("adiniz: ")
    yas = int(input("yas: "))
    print(ad, yas, sep="-", file=dosya, flush=True)

n = 42

if (n > 10) and (n < 100):
    print("10 ile 100 arasında")
elif (n > 100) or (n < 0):
    print("0’dan küçük veya 100’den büyük")
elif not (n == 42):
    print("Yanlış sayı")
else:
    print("Diğer durumlar")

if 'a' in "ali":
    print("‘a’ var")

a = None
if a is None:
    pass

metin = "Bu yAzıdA küçük a yok."
for harf in metin:
    if harf == 'a':
        print("‘a’ bulundu.")
        break
else:
    print("‘a’ bulunmadı.")

for i in range(17):
    # {:^9} → Onlu, {:^9o} → Sekizli (oct)
    # {:^9x} → Onaltılı (hex, küçük harf)
    # {:^9b}   → İkili (bin)
    print("{0:^9} {0:^9o} {0:^9x} {0:^9b}".format(i))
```
### Strings
- Tek (`'…'`), çift (`"…"`) veya üçlü tırnak (`'''…''' / """…"""`) kullanılabilir.
- Üçlü tırnak çok satırlı metin tanımı içindir.
- İç içe tırnak gerekirse diğer tip tırnak kullanılır veya kaçış karakteri (`\", \'`) kullanılır.
- `expandtabs(tabsize)` Sekme (`\t`) karakterlerini belirtilen genişlikte boşluklara çevirir.

```python title="İndeksleme ve Dilimleme" linenums="1"
kelime = "ali"
kelime[0]       # 'a'
kelime[-1]      # 'i' (son eleman)
kelime[:2]      # 'al' (başlangıçtan 2. karaktere kadar, 2 dahil değil)
kelime[1:]      # 'li' (1. karakterden sona kadar)
kelime[::-1]    # 'ila' (ters çevirme)
kelime[::2]     # 'ai' (iki karakterde bir atlayarak)
"A" + kelime[1:]# 'Ali' (ilk harfi değiştirerek)
```
```python title="String Gömülü Fonkisyonlar" linenums="1"
s = "python Programlama"
s.capitalize()   # 'Python programlama' – sadece ilk harf
s.title()        # 'Python Programlama' – her kelimenin ilk harfi
s.upper()        #  ya da s.lower() 
s.casefold()     # 'python programlama' – dil bağımsız, daha agresif küçültme
s.swapcase()     # Büyük harf küçük, küçük harf büyük yapılır.

s.islower() / s.isupper()  # tümü küçük / büyük mü?
s.startswith("py")         # py ile mi başlıyor?
s.endswith("ma")           # ma ile mi bitiyor?
s.isalpha() / s.isdigit()  # yalnızca harflerden / rakamlardan mı oluşuyor?
s.isalnum()     # harf veya rakam mı?
s.isdecimal()   # ondalık rakam mı?
s.isnumeric()   # sayısal karakter mi?
s.isidentifier()# geçerli Python tanımlayıcı mı?
s.isspace()     # yalnızca boşluk karakterlerinden mi?
s.isprintable() # yazdırılabilir karakterler mi?
```

### String Biçimlendirme
- `%`, işaretinden sonra gelen biçim belirteçleri (`%d, %s, %f, %x` vb.) C tarzı yer tutuculardır.
    - Genişlik ve hassasiyet belirtilebilir: `%6.2f, %03d`
    - Hizalama ve doldurma: `%10s, %-10s`
    - Birden fazla değer, tuple ile verilir: "`%d %s`" % (n, text)
- **str.format()**, `{}` yer tutucularını, format() içindeki argümanlarla doldurur.
    - `{0}, {1}…` sayılarla pozisyon belirtebilir; `{name}` ile isimli argüman kullanabilirsiniz
    - İsteğe bağlı format belirtimleri için `:` kullanılır
    - Hizalama: `{:>10} (sağa)`, `{:^10} (ortala)`, `{:<10} (sola)`.
    - Tip ve hassasiyet: `{:d}, {:.2f}` vb.
    - Binlik ayırıcı: `{:,}` (her 3 basamakta virgül).
- **F-String (Python 3.6+)**, Dizge başına `f` eklenir, `{}` içinde doğrudan değişken veya ifadeler yazılır.
    - Esnek: aritmetik, metod çağrısı, format belirtimi doğrudan kullanılabilir.

```python
# % format
print("Ad: %s, Yas: %s" % ("Ali", 19))

# str format
template = "Ad : {} Yas: {}"
print(template.format("Serkan", "30"))
print("Kullanıcı: {user}".format(user="serkan"))

# f format
isim, yas = "Serkan", 45
print(f"Selam {isim}, yas = {yas}")
print(f"Sayıların toplamı = {int(input('1. sayı: ')) + int(input('2. sayı: '))}")
```

### List
- `[]` içinde tanımlanır, öğeler `,` ile ayrılır `liste = [1, "iki", 3.0, True]`
- **Mutable (değiştirilebilir):** Aynı liste üzerinde ekleme, silme, değiştirme yapabilirsiniz.
- Tekrar eden elemanlar olabilir.
- Eleman sayısını len(liste) ile alırsınız.
- İç içe listeler desteklenir
- `b = a → referans` aynı listeyi işaret eder; birinde değişiklik diğerini etkiler.
- `b = a[:]` veya `b = list(a)` veya `b = a.copy() → yeni liste` bağımsız kopya.

```python linenums="1"
my_list = [1, 2, 2, 3, 'a', 'b', 'c']

matris = [[1,2,3], [4,5,6], [7,8,9]]
print(matris[1][2])  # 6

bos = list()                 # []
chars = list("python")       # ['p','y','t','h','o','n']
nums  = list(range(5))       # [0,1,2,3,4]

a = [3,1,4]
a.append(2)           # [3,1,4,2]
a.extend([5,6])       # [3,1,4,2,5,6]
a.insert(1, 99)       # [3,99,1,4,2,5,6]
a.remove(99)          # [3,1,4,2,5,6]
x = a.pop()           # x=6, a=[3,1,4,2,5]
a.sort()              # [1,2,3,4,5]
a.reverse()           # [5,4,3,2,1]
b = a.copy()          # b bağımsız kopya

meyveler = ["elma","armut","çilek","kiraz"]
print(meyveler[0])     # 'elma'
print(meyveler[-1])    # 'kiraz'
print(meyveler[1:3])   # ['armut','çilek']
print(meyveler[:2])    # ['elma','armut']
print(meyveler[::2])   # ['elma','çilek']


liste = [i for i in range(1000)]  # 0–999 arası sayılar
even = [i for i in range(1000) if i % 2 == 0] # çift sayılar

matris = [[1,2],[3,4]]                    # iç içe açma
duz = [x for row in matris for x in row]  # [1,2,3,4]
```

### Tuple 
- Parantez içinde veya virgülle oluşturulur
- **Immutable:** İçerik değiştirilemez; yeni bir atama eski nesneden farklı kimlik üretir.
- Erişim, dilimleme listelerle aynı şekilde
- Tekrar eden elemanlar olabilir.
- Tek öğeli demet: sonuna virgül koyun.
- Yüzeysel kopya gerekmez; atama hep referans davranışı verir.
- `count(x)` x’in kaç kez geçtiğini sayar.
- `index(x)` İlk x’in indeksini döner; bulunmazsa `ValueError`.

```python linenums="1"
t = (1, 2, 3)
t2 = 4, 5, 6

print(t[0], t[-1], t[1:3])
single = (42,) # Tek elemanlı Demet

t = (1,2,1,3)
print(t.count(1))   # 2
print(t.index(3))   # 3
```

### Dict
- Anahtarlar immutable ve benzersiz olmalı; değerler mutable olabilir.
- Süslü parantezle oluşturulur: `{}`.
- Key – Value çiftlerinden oluşur
- Değişik veri tipleri kullanılabilir:
    - Key olarak immutable tipler (str, int, tuple vs.).
    - Value olarak her tür (list, dict, başka dict vs.).
- Yeni öğe eklemek/güncellemek:
- `keys()` Tüm anahtarları döner.
- `values()` Tüm değerleri döner.
- `items()` (key, value) çiftlerini döner.
- `get(key, default=None)` Key yoksa default döner, hata vermez.
- `pop(key, default=…)` Key’i silip değerini döner; yoksa default veya KeyError.
- `popitem()` Son eklenen çifti silip döner.
- `setdefault(key, default=None)` Key yoksa ekler ve default döner; varsa mevcut değeri döner.
- `update(other_dict)` Başka bir sözlüğün içeriğini ekler/günceller.
- `clear()` Tüm öğeleri siler ({}).
- `copy()` Yüzeysel kopya oluşturur.
- `fromkeys()` Belirli anahtarlarla hepsi aynı değere sahip yeni bir sözlük oluşturur:

```python linenums="1"
sozluk = {
    "kitap"      : "book",
    "bilgisayar" : "computer",
    "dil"        : "language"
}

sozluk["Ahmet"] = "Adana"

sozluk = {"a": 1, "b": 2}
print(list(sozluk.keys()))    # ['a', 'b']
print(sozluk.get("c", 0))     # 0
sozluk.update({"b": 3, "c": 4})
print(sozluk)                 # {'a':1, 'b':3, 'c':4}

kisiler = {
    "Ahmet": {"Sehir": "Istanbul", "Meslek": "Ogretmen"},
    "Mehmet": {"Sehir": "Adana", "Meslek": "Muhendis"}
}
print(kisiler["Ahmet"]["Meslek"])  # Ögretmen

keys = ['a', 'b', 'c']
sozluk = dict.fromkeys(keys, 0)
# {'a':0, 'b':0, 'c':0}
```

### Set
- `set()` ile veya `{}` içinde virgülle oluşturulur.
- **Mutable** (değiştirilebilir), sırasız, benzersiz elemanlar.
- **Immutable** set: `frozenset()` oluşturulduktan sonra değiştirilemez.
- `add(x)` Eleman ekler.
- `update(iterable)` Birden fazla elemanı ekler.
- `remove(x)` Eleman siler; yoksa KeyError.
- `discard(x)` Eleman siler; yoksa hata vermez.
- `pop()` Rastgele bir elemanı siler ve döner.
- `clear()` Tüm elemanları siler.
- `copy()` Yüzeysel kopya döner.
- `union(other)` / `|`: Birleşim.
- `intersection(other)` / `&`: Kesişim.
- `difference(other)` / `-`: Fark.
- `symmetric_difference(other)` / `^`: Karşılıklı fark.
- `_update` versiyonları (`intersection_update`, vb.) sonucu aynı kümeye uygular.
- Sorgular:
    - `isdisjoint(other)` Ortak eleman yok mu?
    - `issubset(other)` Alt küme mi?
    - `issuperset(other)` Üst küme mi?

```python linenums="1"
my_set = {1, 2, 3, 'a', 'b', 'c'}
s = set([1,2,3])
t = {"elma", "armut", "kiraz"}
f = frozenset([1,2,3])

s = {1,2,3}
s.add(4)           # {1,2,3,4}
s.update([5,6])    # {1,2,3,4,5,6}
s.discard(2)       # {1,3,4,5,6}
s.remove(3)        # {1,4,5,6}

a = {1,2,3,4}
b = {3,4,5,6}

print(a | b)   # {1,2,3,4,5,6}
print(a & b)   # {3,4}
print(a - b)   # {1,2}
print(a ^ b)   # {1,2,5,6}
print(a.issubset({1,2,3,4,5}))  # True
```

```python
# for döngüsü
for harf in "deneme":
    print(harf)

# enumerate ile indeksli yineleme
for idx, harf in enumerate("deneme"):
    print(idx, harf)

# while döngüsü
i = 0
while i < 3:
    print(i)
    i += 1
```

### Hata Yakalama ve İstisnalar
- **try – except** `try` bloğu içindeki kod çalıştırılır; eğer tanımlı bir istisna (Exception) fırlatılırsa uygun `except` bloğu devreye girer. Birden fazla `except` ile farklı hata türlerini ayrı işleyebilirsiniz. Hiçbir tür belirtilmeden yazılan `except` tüm istisnaları yakalar **(genellikle önerilmez)**.
- **raise** Kendi hata durumlarınızı fırlatmak için
- **assert** Bir koşulun doğru olduğunu doğrulamak için. Yanlışsa `AssertionError` fırlatır:

```python
try:
    deger = input("Sayı: ")
    deger_int = int(deger)
    if deger == 10:
        raise Exception("10 sayısı yasaktır!")
except ValueError:
    print("Geçerli bir sayı değil.")
except ZeroDivisionError:
    print("Sıfıra bölme hatası.")
except (TypeError, NameError) as hata:
    print("Başka bir hata:", hata)
else:
    print("Başarılı dönüşüm:", deger_int)
finally:
    print("Bu blok her zaman çalışır.")

giris = input("Adınız: ")
assert giris, "İsim boş olamaz!"
print("Hoş geldiniz,", giris)
```

### Temel Dosya İşlemleri

- open(path, mode, encoding=None) ile dosya açılır.
- mode:
    - `'r'` – okuma (varsayılan)
    - `'w'` – yazma (varsa üzerine yazar, yoksa oluşturur)
    - `'a'` – ekleme (varsa sona ekler, yoksa oluşturur)
    - b eklenirse ikili mod (örn. `'rb'`, `'wb'`)
    - + eklenirse hem okuma hem yazma (örn. `'r+'`, `'w+'`)

- Windows yollarında ters eğik çizgi (`\`) kaçış karakteri olduğundan:
- **Context manager (with)** kullandığınızda `close()` otomatik çağrılır
- `f.read(size=-1)` Tüm içeriği (size=-1) veya en fazla size byte/karakter okur.
- `f.readline()` Bir satır okur (satır sonunu da içerir).
- `f.readlines()` Tüm satırları liste olarak döner.
- `f.write(text) / f.writelines(iterable)` Metni yazar. write tek string, writelines birden çok satır içeren iterable alır.
- `print(..., file=f, flush=True)` print fonksiyonu ile doğrudan dosyaya yazabilirsiniz.
- `f.seek(offset, whence=0)` 
    - İmleci offset byte ileri/geri taşır.
        - whence=0: baştan (seek(0) başa dön).
        - whence=1: mevcut pozisyondan.
        - whence=2: sondan.
- `f.tell()` Geçerli imleç pozisyonunu byte cinsinden döner.
- `f.readable(), f.writable(), f.seekable()` İzin sorguları (bool).
- `f.truncate(size=None)` Dosyayı `size` byte’a kadar kısaltır (default: mevcut pozisyona kadar).
- `f.mode` → açılış modu ('r', 'wb', vb.)
- `f.name` → dosya adı veya yol
- `f.encoding` → metin modunda kullanılan kodlama

```python linenums="1"
f = open("C:\\klasor\\dosya.txt", "r") # Ya çift ters eğik kullanın
f = open(r"C:\klasor\dosya.txt", "r")  # Ya ham string (raw) ile

try:
    f = open("veri.txt", "r", encoding="utf-8")
    içerik = f.read()
except IOError:
    print("Dosya açılamadı veya okuma hatası!")
finally:
    f.close()

# with bloğu bitince f.close() otomatik yapılır
with open("veri.txt", "r", encoding="utf-8") as f:
    for satır in f:
        print(satır.rstrip("\n"))

with open("cikti.txt", "w", encoding="utf-8") as f:
    f.write("Merhaba\n")
    print("Dosyaya ek satır", file=f, flush=True)

# Metin modu (satır sonu çevirisi, encoding)
with open("notlar.txt", "w+", encoding="utf-8") as f:
    f.write("Türkçe karakter: ç\n")
    f.seek(0)
    print(f.read())

with open("resim.png", "rb") as f: # İkili mod (raw byte)
    header = f.read(8)
    print(header)  # b'\x89PNG\r\n\x1a\n'
```

### PDF Dosyaları Üzerinde Basit İşlemler
- PDF’ler genellikle ikili dosyalardır; içinde `/Producer`, `/CreationDate` gibi metaveri etiketleri bulunur. Örneğin üretici bilgisini okumak için

```python
with open("belge.pdf", "rb") as f:
    data = f.read()
    idx = data.find(b"/Producer")
    if idx != -1:
        print(data[idx:idx+50])
```

!!! note "Not"

    Gerçek PDF işleme için PyPDF2, pdfminer.six gibi kütüphaneleri kullanmak çok daha güvenli ve pratiktir.

| Etiket | Anlamı |
|--------|--------|
| `/Creator`          | Belgeyi oluşturan uygulama veya yazılım (ör. Adobe InDesign) |
| `/Producer`         | PDF’yi üreten kütüphane veya araç (ör. “PDFLib” vb.) |
| `/Author`           | Belge yazarı |
| `/Title`            | Belge başlığı |
| `/Subject`          | Belge konusu veya özeti |
| `/Keywords`         | Anahtar kelimeler (arama ve sınıflandırma için) |
| `/CreationDate`     | Oluşturulma tarihi (D:YYYYMMDDHHmmSSZ formatında) |
| `/ModDate`          | Son değiştirilme tarihi |
| `/Trapped`          | Baskı iş akışı notu (“True”, “False” veya “Unknown”) |	
	
```python
with open("belge.pdf", "rb") as f:
    data = f.read()
    for tag in [b"/Creator", b"/Producer", b"/Author", b"/Title", b"/Subject", b"/Keywords", b"/CreationDate", b"/ModDate"]:
        idx = data.find(tag)
        if idx != -1:
            snippet = data[idx:idx+100].split(b"\n",1)[0]
            print(snippet)
```

### Dosya Türü Algılama (Magic Numbers)

- Bazı dosyalar, içerdikleri “magic number” (sihrî sayı) adı verilen sabit bayt dizileri sayesinde türleri kolayca tespit edilebilir:
- **JPEG** – Başlangıç baytları: `FF D8 FF E0 ?? ?? 4A 46 49 46` (JFIF) Veya `FF D8 FF E0 ?? ?? 45 78 69 66` (Exif)
- **PNG** – İlk 8 bayt: 
    - Onluk: `137 80 78 71 13 10 26 10` 
    - Onaltılık: `89 50 4E 47 0D 0A 1A 0A`
    - Karakter karşılığı: `\x89 P N G \r \n \x1A \n`
- **GIF** – İlk 3 bayt: `47 49 46` (“GIF”)
- **TIFF** – İlk 2 bayt: `49 49` (“II”) veya `4D 4D` (“MM”)
- **BMP** – İlk 2 bayt: `42 4D` (“BM”)

```python
for path in dosyalar:
    header = open(path, 'rb').read(10)
    if header[6:10] in (b'JFIF', b'Exif'):
        print(f"{path} → JPEG")
    elif header[:8] == b"\x89PNG\r\n\x1a\n":
        print(f"{path} → PNG")
    elif header[:3] == b"GIF":
        print(f"{path} → GIF")
    elif header[:2] in (b"II", b"MM"):
        print(f"{path} → TIFF")
    elif header[:2] == b"BM":
        print(f"{path} → BMP")
    else:
        print(f"{path} → Bilinmeyen tür")
```

### Karakter, Byte ve Bytearray

- Kodlama Hataları (`errors`): 
    - Dosya açarken errors parametresi, çözümlenemeyen karakterlerle ne yapılacağını belirler:
        - `'strict'` → Hata fırlatır.
        - `'ignore'` → Hatayı atlatarak karakteri atlar.
        - `'replace'` → Geçersiz karakter yerine ? koyar.
        - `'xmlcharrefreplace'` → XML karakter referansı (&#1234;) ekler.
- `repr(obj)` Nesnenin resmi (parse edilebilir) gösterimini döner; kaçış dizilerini gösterir.
- `ascii(obj)` repr() benzeri, ama ASCII olmayan karakterleri \x../\u.. biçiminde kodlar.
- `ord(c)` Karakter c’nin Unicode kod noktasını döner (int).
- `chr(n)` Kod noktası n’e karşılık gelen karakteri döner.
- `bytes` Değiştirilemez (immutable) bayt dizisi.
- `bytearray` Değiştirilebilir (mutable) bayt dizi
- `s.encode(encoding, errors)` → bytes
- `b.decode(encoding, errors)` → str
- `fromhex()` Onaltılık dizeden bytes oluşturur

```python
# 'ç' ASCII’e çevrilmez:
"çalış".encode("ascii", errors="ignore")   # b"al s"
"çalış".encode("ascii", errors="replace")  # b"?al?s"

print(repr("Line\nNew"))    # "'Line\\nNew'"
print(ascii("Türkçe"))      # "'T\\xfcrk\\xe7e'"

print(ord('A'))  # 65
print(chr(65))   # 'A'

b = b"hello"                         # literal
b2 = bytes([65,66,67])               # b"ABC"
ba = bytearray(b"mutable")           # bytearray(b"mutable")

s = "İstanbul"
b = s.encode("utf-8")            # b'\xc4\xb0stanbul'
print(b.decode("utf-8"))         # 'İstanbul'

bytes.fromhex("deadbeef")      # b'\xde\xad\xbe\xef'

# Bir karakterin byte uzunluğu, kullandığınız kodlamaya göre değişir:
print(len("ş".encode("utf-8")))    # 2 byte
print(len("ş".encode("cp1254")))   # 1 byte
```

### Fonksiyonlar (def)

- `def` anahtar kelimesiyle fonksiyon tanımlanır.
- İlk satırdaki string (docstring), fonksiyonun belgelendirilmesi içindir (`help()` ile erişilebilir).
- `Default` değerler **tanım sırasında** belirlenir.
- Default’lar yalnızca sondaki parametrelerde kullanılabilir.
- **Değişken Sayıda Parametre:** `*args` → pozisyonel argümanları tuple olarak alır. `**kwargs` → keyword argümanları dict olarak alır.
- `*args` ve `**kwargs` aynı fonksiyonda birlikte kullanılabilir.
- Sıralama:
    - Pozisyonel zorunlu parametreler
    - Default parametreler
    - `*args`
    - Keyword-only parametreler (sadece * sonrası gelenler)
    - `**kwargs`

- `*` işaretiyle, sonrasında gelen parametrelerin yalnızca keyword ile atanmasını zorunlu kılabilirsiniz
- `return` ile fonksiyonu sonlandırıp değer döndürür.
- `return` yoksa `None` döner.
- **Lambda (Anonim Fonksiyonlar)** Tek satırlık fonksiyonlar oluşturulur.
- **Local** değişkenler fonksiyon içinde tanımlıdır.
- `global` ile fonksiyon içinde `global` scope’daki bir değişkene atama yapabilirsiniz
- `nonlocal` ile dış (ancak global olmayan) scope’daki değişkene erişebilirsiniz

```python linenums="1"
def kayit_olustur(isim, soyisim, sehir):
    """
    Üç zorunlu parametre alan kayıt oluşturma fonksiyonu.
    """
    print(f"İsim   : {isim}")
    print(f"Soyisim: {soyisim}")
    print(f"Şehir  : {sehir}")

def kur(kurulum_dizini="/usr/bin/"):
    """
    Kurulum dizini verilmezse varsayılan "/usr/bin/" kullanılır.
    """
    print(f"Program {kurulum_dizini} dizinine kuruldu!")

def carp(*sayilar):
    """İstediğiniz kadar sayı alır, hepsini çarpar."""
    sonuc = 1
    for s in sayilar:
        sonuc *= s
    return sonuc

def kayit(**bilgiler):
    """Anahtar=değer çiftlerini sözlük olarak yazdırır."""
    for k, v in bilgiler.items():
        print(f"{k:10}: {v}")

def islem(a, b, *, verbose=False):
    """verbose ancak key=value ile geçilebilir."""
    result = a + b
    if verbose:
        print(f"{a} + {b} = {result}")
    return result

def sayi_uret(bas=0, bit=50, adet=5):
    """Tekrarsız rastgele sayılar seti döner."""
    sonuc = set()
    while len(sonuc) < adet:
        sonuc.add(random.randint(bas, bit))
    return sonuc
    
kayit_olustur("Fırat", "Özgül", "İstanbul") # Pozisyonel argümanlarla
kayit_olustur(soyisim="Özgül", isim="Fırat", sehir="İstanbul") # Keyword argümanlarla (sıra farketmez)

kur()                    # Program /usr/bin/ dizinine kuruldu!
kur("/opt/myapp/")       # Program /opt/myapp/ dizinine kuruldu!

print(carp(2, 3, 5))  # 30
kayit(ad="Ahmet", soyad="Öz", sehir="Ankara")

islem(2, 3, verbose=True)  # 5 satırını yazdırır
# islem(2,3,True)          # TypeError!

rastgele = sayi_uret(1, 100, adet=3)
print(rastgele)  # örn. {42, 7, 99}
```

```py title="lambda fonksiyonları"
carp = lambda *s, **k: __import__("functools").reduce(lambda x,y: x*y, s, 1)
print(carp(2,3,4))  # 24

kare = lambda x: x*x
print(kare(5))      # 25

# Lambda olarak fonk = lambda param1, param2: param1 + param2
def fonk(param1, param2):
    return param1 + param2

harfler = "abcçdefgğhıijklmnoöprsştuüvyz"
isimler = ["ahmet", "ışık", "ismail", "can", "iskender"]

çevrim = {i: harfler.index(i) for i in harfler}           
print(sorted(isimler, key=lambda x: çevrim.get(x[0])))

l = [2, 5, 10, 23, 3, 6]
print(*map(lambda sayı: sayı ** 2, l))
```

```python title="İç İçe Fonksiyonlar"
isim = "Fırat"

def yazıcı():
    def yaz(mesaj):
        print(mesaj)
    return yaz

def fonksiyon_sayıcı():
    sayı = 0
    def say():
        nonlocal sayı   #localde bulunan değişkene erişmeyi sağlar
        sayı += 1
        return sayı
    return say

def degistir():
    global isim
    isim += " Özgül"

degistir()
print(isim)  # Fırat Özgül
```

```python linenums="1" title="Öz yinelemeli"
def azalt(s):
    if len(s) < 1:
        return s
    else:
        print(s)
        return azalt(s[1:])

print(azalt('istihza'))
```


#### Fonksiyon İmzası ve Anotasyonlar
- Parametre ve dönüş türü açıklamaları için **type hints**

```python linenums="1"
from typing import List, Dict

def ortalama(sayilar: List[int]) -> float:
    return sum(sayilar) / len(sayilar)

print(ortalama([10, 20, 30]))  # 20.0
```

- Bu anotasyonlar çalışma zamanı değil, statik araçlar (mypy, IDE) içindir.

#### Üreteçler (Generators)

- Python üreteçleri, `yield` anahtar kelimesiyle tanımlanan, duraklatılabilir ve devam ettirilebilir fonksiyonlardır. Büyük veri setlerini adım adım üretmek ve bellek tasarrufu sağlamak için idealdir.
- `yield`: Fonksiyonu duraklatır ve bir değer döndürür.
- Bir sonraki değeri almak için `next()` kullanılır
- Üreteç sonsuz döngüde çalışabilir; ihtiyaç duyulana kadar bellek kullanmaz.
- **Bellek Verimliliği:** Tüm veriyi aynı anda saklamaz, ihtiyaç duyulana kadar hesaplar.
- **Akış Tabanlı İşlemler:** Dosya satır satır okuma, sonsuz veri akışları, büyük diziler vb.

```python linenums="1"
def uretec():
    sayi = 0
    while True:
        sayi += 1
        yield sayi

def iki_yazi():
    yield "Merhaba"
    yield "Dünya"

g = uretec()
print(next(g))  # 1
print(next(g))  # 2
print(next(g))  # 3

g = iki_yazi()
print(next(g))  # "Merhaba"
print(next(g))  # "Dünya"
# print(next(g))  # StopIteration hatası (artık değer kalmadı)

# Başka bir üreteci doğrudan çağırmak ve alt değerleri yeniden üretmek için
def uretec1():
    yield "A başladı"
    yield "A bitti"

def uretec2():
    yield "B başladı"
    yield from uretec1()
    yield "B bitti"

for v in uretec2():
    print(v)

# Çıktı:
# B başladı
# A başladı
# A bitti
# B bitti
```

```python linenums="1" title="Üreteç İfadeleri (Generator Expressions)"
# Kısa söz dizimiyle üreteç oluşturma
# Liste üretmek yerine üreteç:
liste = [i*i for i in range(5)]         # normal liste
uretec = (i*i for i in range(5))         # üreteç ifadesi

print(type(uretec))  # <class 'generator'>
print(next(uretec))  # 0
print(list(uretec))  # [1, 4, 9, 16]
```

- `()` içinde, `[]` listesinden tek farkı bellek yerine değerleri teker teker üretir.
- `Send / Throw / Close` Üreteç ile çift yönlü iletişim sağlar.
- `StopIteration` Üreteç tükendiğinde (ek `yield` yoksa), `next()` StopIteration fırlatır.

```python linenums="1"
def echo():
    while True:
        value = (yield)
        print("Gelen:", value)

g = echo()
next(g)            # başlat (ilk yield’e kadar)
g.send("Merhaba")  # "Gelen: Merhaba"
g.close()          # üreteci kapat
```

### Modüller ve Paketler
- `os.name, os.listdir()` gibi tam yolu kullanırsınız.
- Bir klasörün paket olarak tanınması için içinde bir **__init__.py** dosyası bulunmalıdır (Python 3.3+’ta bu zorunlu değil, ama iyi pratiktir).
- `sys.path` ile Özel Yol Ekleme: Python, modülleri sys.path listesindeki klasörlerde arar. Dinamik olarak ekleme yapabilirsiniz
- `sys.path` değişkeni, `import` sırasında bakılan dizin listesini tutar.
- Yolu ekledikten sonra, o klasördeki `.py` dosyalarını doğrudan `import` edebilirsiniz.

```python linenums="1" title="Tüm modülü içe aktarma"
import os
import subprocess as sp              # Alias ile kısaltma 
import urllib.request                # Modül içindeki alt modülü tam yoluyla kullan
from os import name, listdir, getcwd # Belirli fonksiyonları dahil eder
from os import path as p             # Alias ile kısaltma
from sys import *                    # Tüm nitelikleri içe aktarma (genellikle önerilmez)

# same package altında
from . import helper       # mypkg/helper.py
from .sub import utils     # mypkg/sub/utils.py
# bir üst pakete çıkmak
from ..core import config

home = os.environ.get('HOME') or os.environ.get('HOMEPATH')
desktop = os.path.join(home, 'Desktop')
sys.path.append(desktop)  # artık Desktop’taki modülleri import edebilirsiniz
```

### Standart Kütüphanaler

#### Düzenli İfadeler (re Modülü)
Python’un `re` modülü, metin içinde karmaşık desen aramaları ve dönüşümleri için kullanılır. Gereksiz yere değil, gerçekten ihtiyaç duyduğunuzda tercih edin.

- Bağlam Belirleyiciler
    - `^` → Metnin başlangıcı
    - `$` → Metnin sonu
    - `\b` → Kelime sınırı
    - `\B` → Kelime sınırı değil

- Gruplama ve Yakalama: Parantez içinde oluşturulur:
    - `(...)` → Yakalama grubu (daha sonra `.group(n)` ile erişilir).
    - `(?:...)` → Yakalamadan sadece grup oluşturur.

- Bayraklar (Flags): Regex’i satır satır (`re.MULTILINE`), büyük/küçük harf duyarsız (`re.IGNORECASE`) veya noktanın yeni satırı da yakalaması için (`re.DOTALL`) yapılandırın:

|**Temel Fonksiyon** |	**Açıklama** |
|-------------|------------------|
| `re.match(pattern, text)` | Metnin başında pattern ile eşleşme arar. |
| `re.search(pattern, text)` | Metnin her yerinde ilk eşleşmeyi bulur. |
| `re.findall(pattern, text)` | Tüm eşleşmeleri liste olarak döner. |
| `re.finditer(pattern, text)`	| Tüm eşleşmeleri iterator olarak döner (match objeleri). |
| `re.sub(pattern, repl, text)`	| Deseni repl ile değiştirir (tüm eşleşmelerde). |
| `re.split(pattern, text) ` | Desene göre bölerek liste döner. |

|**Desen**   | **Anlamı** |
|------------|--------|
| `[abc]`     | a veya b veya c |
| `[0-9]`     | 0–9 arası |
| `[^abc]`	     | a, b, c dışındaki karakterler |
| `.`	         | Yeni satır (\n) hariç her karakter |
| `\d`	         | Ondalık rakam ([0-9]) |
| `\D`	         | Ondalık olmayan ([^0-9]) |
| `\w`	         | Alfanümerik ve alt çizgi ([A-Za-z0-9_]) |
| `\W`	         | Alfanümerik olmayan ([^A-Za-z0-9_]) |
| `\s`	         | Boşluk karakterleri ([ \t\n\r\f\v]) |
| `\S`	         | Boşluk olmayan karakterler |

| Tekrarlama Metakarakter |	Anlamı |
|------------|-------------|
| `*`	    | 0 veya daha fazla kez |
| `+`	    | 1 veya daha fazla kez |
| `?`	    | 0 veya 1 kez |
| `{m}	`    | Tam olarak m kez |
| `{m,}`	| En az m kez |
| `{m,n}`	| m ile n kez arası |

```python linenums="1" title=""
text = "Foo123 Bar456 Baz789"

# Başta “Foo” olup olmadığını kontrol
print(bool(re.match(r"Foo", text)))          # True

# Metinde ilk sayısal bloku bul
m = re.search(r"\d+", text)
print(m.group(), m.start())                  # '123', 3

# Tüm sayı bloklarını listele
print(re.findall(r"\d+", text))              # ['123', '456', '789']

# Harf ve rakam arasına tire ekle
print(re.sub(r"([A-Za-z]+)(\d+)", r"\1-\2", text))
# 'Foo-123 Bar-456 Baz-789'

# Büyük harfle başlayıp rakamla biten satır
pattern = r"^[A-Z].*\d$"
print(bool(re.match(pattern, "Hello123")))  # True
print(bool(re.match(pattern, "hello123")))  # False

m = re.search(r"(\d+)-(\d+)-(\d+)", "Tarih: 2021-12-31")
print(m.groups())    # ('2021', '12', '31')

# 'cat' veya 'dog'
re.findall(r"cat|dog", "cat dog mouse")  # ['cat', 'dog']

pattern = r"^foo"
text = "foo\nbar\nfoo"

print(re.findall(pattern, text))  # ['foo']
print(re.findall(pattern, text, flags=re.MULTILINE))  # ['foo', 'foo']
```

- İpuçları ve İyi Uygulamalar: 
    - Ham string (raw): `r"..."` kullanın, böylece \ kaçış sorunlarıyla uğraşmazsınız.
    - **Derlenmiş desen:** Çok sık kullanılan deseni re.compile() ile derleyip tekrar kullanın.
    - **Yorumlayın:** Karmaşık desenler için (?x) flag’i ile boşluk ve yorum yazabilirsiniz

```python
pattern = re.compile(r"""
    ^               # satır başı
    [A-Za-z]+       # harflerden oluşan bir veya daha fazla karakter
    \d{2,4}         # 2 ila 4 rakam
    $               # satır sonu
""", re.VERBOSE)
```


### Nesne Yönelimli Programlama (OOP)
- `class` anahtar kelimesiyle başlar, sınıf adı **PascalCase** (büyük harfle başlayan her kelime) olur.
- `__init__` metodu, nesne oluşturulurken otomatik çağrılır.
- `self`, o örneğe (nesneye) referans verir; her metot ilk parametresi `self` olmalıdır.
- Sınıf nitelikleri (toplam) tüm örnekler arasında paylaşılır.
- Örnek nitelikleri (self.id) yalnızca o nesneye özeldir.
- Sınıf içindeki her işlev, metot olarak adlandırılır.
- İlk parametresi `self` olduğu için örneğe erişebilir.
- `@classmethod` ile işaretlenen metotlara ilk parametre olarak sınıf `(cls)` gelir.
- Sınıf niteliği üzerinde işlem yapmak için kullanılır.
- `@staticmethod` ile tanımlanan metotlar ne self ne de cls alır; sınıfa bağlı değil, bağımsız işlev gibidir.
- `@property` ile metodu öznitelik gibi (d.alan) kullanabilirsiniz.
- Okuma (`@<isim>.setter`) ve silme (`@<isim>.deleter`) işlemleri de eklenebilir.
- **Public** (her yerden erişilebilir): isim
- **Protected** (alt sınıflarda kullanılabilir): _isim
- **Private** (sınıf içinde saklı): __isim → arkasında isim eşleme (`name mangling`)
- **Bir sınıf class AltSinif(UstSinif):** ile miras alır.
- `super()` ile üst sınıfın metotlarını çağırabilirsiniz.
- Çoklu kalıtım: `class C(A, B)`
- Dunder (double underscore) metotları, nesnelere özel davranışlarla Python’un yerleşik işlemlerini yeniden tanımlar:
- Böylece +, -, len(), str(), == gibi işlemleri nesnenize özgü hale getirebilirsiniz.

```python 
class Sayac:
    toplam  = 0        # Sınıf niteliği

    def __init__(self):
        Sayac.toplam += 1
        self.id = Sayac.toplam   # Örnek niteliği
        self.__gizli = 42

    @classmethod
    def toplam_sayac(cls):
        return cls.toplam
        
    @staticmethod
    def topla(a, b):
        return a + b

    @property
    def alan(self, r):
        return 3.1416 * r ** 2



print(Sayac.toplam_sayac())   # 0
a, b = Sayac(), Sayac()
print(Sayac.toplam_sayac())   # 2
print(Sayac.topla(3, 4))      # 7
# print(a.__gizli)            # AttributeError
print(a._Sayac__gizli)        # 42 (name mangling)


class Calisan
    def __init__(self, isim):
        self.isim = isim

    def calis(self):
        print(f"{self.isim} çalışıyor")

class Yonetici(Calisan):
    def calis(self):
        super().calis()
        print(f"{self.isim} yönetiyor")

y = Yonetici("Ayşe")
y.calis()

class Nokta:
    def __init__(self, x, y):
        self.x, self.y = x, y

    def __add__(self, other):
        return Nokta(self.x + other.x, self.y + other.y)

    def __repr__(self):
        return f"Nokta({self.x}, {self.y})"

p1, p2 = Nokta(1,2), Nokta(3,4)
print(p1 + p2)  # Nokta(4, 6)
```

### Pip 

```bash linenums="1"
# pip3 içinde geçerlidir
pip show numpy
pip install numpy
pip install numpy==1.25.0  # Belirli bir version indirilir.
pip install --upgrade scikit-learn
pip list         # Yüklü olan python paketlerini listeler
```