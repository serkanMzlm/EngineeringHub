# C & C++ 
- **LValue**, bellekte kimliği (adreslenebilirliği) olan ve atamanın hedefi olabilen ifadedir. **RValue** ise genellikle geçici, kimliği olmayan ve atamanın hedefi olamayan ifadedir.
- **Call by Value / Call by Reference:** C’de parametreler kopyalanarak aktarılır; referans benzeri davranış pointerlar ile sağlanır.
- **Prefix (++i) / Postfix (i++)**
- **Recursion:** Bir fonksiyonun kendisini çağırmasıdır.
- **Redeclaration / Redefinition:** Aynı kapsamda aynı isimle yeniden tanımlama derleme hatasıdır.
- **Virgül Operatörü (,):** İfadeleri soldan sağa değerlendirir ve son ifadenin değerini üretir.
- **argc / argv:** Argument count (argüman sayısı) / Argument vector (argüman dizisi)
- **Header Guards:** Başlık dosyasının birden fazla kez dahil edilmesini önler; modern derleyicilerde bu amaçla `#pragma once` kullanımı yeterlidir. 
- **Implicit / Explicit:** Otomatik ve açık tür dönüşümleri
- **Direct Acces**, Değişken adıyla erişimdir. **Indirect Access**, Pointer üzerinden erişimdir.
- **Diziler:** Bellek adresi üzerinden erişilir; `dizi[index]` ve `index[dizi]` eşdeğerdir. (`*(dizi + index)`)
- **Temel Veri Türleri:** `int, float, double, char, void`.
- **Kullanıcı Tanımlı Türler:** `struct, enum, union`
- **Bitfield:** Hafızayı daha verimli kullanmak için bit seviyesinde alan tanımlar.
- `const` Değiştirilemezliği belirtir. `volatile` Derleyici optimizasyonlarını sınırlar.
- `sizeof` Veri veya değişken boyutunu döner.
-  `__attribute__` Yapıların bellekteki boşluklarını optimize eder.
- **Koşullar:** `if-else, switch, ?:, goto` (önerilmez).
- **Döngüler:** for, while, do - while.
- **Fonksiyonlar:** void dışındaki fonksiyonlar dönüş değeri üretmelidir.
- `break` döngüyü sonlandırır. `continue` bir sonraki iterasyona geçer. `return` Fonksiyondan çıkar.
- **Define:** Derleme zamanında sembolik isimler oluşturur, bellekte yer tutmaz.
- **String:** `\0` ile sonlanan karakter dizileridir; çift tırnakla tanımlananlara `\0` otomatik eklenir.
- `&` değişkenin adresini alır. `*` pointer adresin gösterdiği değere erişir.
- **Dinamik Bellek Yönetimi:** `malloc, calloc, realloc, free`.
- **Stack:** Sabit boyutlu, LIFO.
- **Heap:** Dinamik bellek yönetimi.
- **Linked List (Bağlı Liste):** Veri parçalarını birbirine bağlayan pointerlarla dinamik hafıza yönetimi sağlar.

## C
=== "main.h"
	```c
	#ifndef SOME_UNIQUE_NAME_HERE    // HEADER GUARDS
	#define SOME_UNIQUE_NAME_HERE 

	#define MAX_SIZE 100
	#define __MUTLAK_SONUC__         // Boş define 

	typedef int tamsayi;
	tamsayi __MUTLAK_SONUC__ degisken = (int)3.14;

	char str1[] = "Hi";  // Otomatik olarak \0 eklenir. Ya da  {'H', 'i', '\0'}

	int my_variable_name; // Snake Case
	int myVariableName;   // Camel Case
	int MyVariableName;   // Pascal Case

	// Bitfield
	typedef struct {
		unsigned int month : 4;
		unsigned int year : 11;
		unsigned int day : 5;
	} Date;

	// struct 16 * 2 = 32 byte olur fakat __attribute__  sayesinde 16 + 8 = 24 byte olur.
	typedef struct {
		uint8_t x;
		uint16_t y;
	} __attribute__((packed)) State_s;

	void info();                                      // prototip (declaration)

	#endif
	```

=== "main.c"
	```c 
	void calledFirst() {  printf("constructor\n"); }
	void calledLast(){ printf("destructor\n"); }
	void __attribute__((constructor)) calledFirst();  // int main() fonksiyonundan önce çalışır.
	void __attribute__((destructor)) calledLast();    // int main() fonksiyonundan sonra çalışır.
	
	int main() 
	{ 
		info();

		State_s state_1
		State_s state_2 = {1 ,2};
		State_s state_3 = {0};            // Bütün verilere 0 atar.
		State_s *state_ptr;
		state_ptr->x = 10;                // Ya da *(state_ptr).x = 10;

		int array[5] = {[0 ... 4] = 5};   // Derleyiciye göre kabul edilir.

		if(printf("Hello World")) {}      // Bir kez çalışır.
		while(printf("Hello World")) {}   // Sonsuz döngü.

		for(int a = 0, b = 10; a < 10 && b > 2; a++, b--);

		int *arr = (int*)malloc(sizeof(int)*10);
		free(arr);

		return 0;
	}

	void info()                           // Definition 
	{
		printf("%+f", num); 	      // Pozitif sayı önüne '+' koyar
		printf("%05x", num);   	      // Boşluklara 0 koyar
		printf("%*.*f", 2,3,number);  // '*' verilerin dışardan doldurulmasını sağlar.
		printf("%#x", number);        // '#' sayıların 0x şeklinde yazılmasını sağlar.

		char buf[100];
		sprintf(buf, "Sayı: %d", num);
		sscanf(buf, "Sayı: %d", &num);
	}

	int sum(int num, ...) {} // değişken sayıda parametre alan fonksiyon
	```

## C++ 

- Tanımlanıp hiç kullanılmayan değişkenler için derleyici uyarı verir. Bu uyarıyı bastırmak için `[[maybe_unused]]` kullanılır(C++17).
- `::` operatörü, önünde bir isim (örneğin bir namespace veya sınıf adı) yoksa “global” ad alanını ifade eder.
- `std::cin >>` operatörü boşluk karakterine kadar okurken, `std::getline(cin, str)` satır sonuna (veya belirlediğiniz başka bir sınırlayıcıya) kadar tüm girdi satırını alır. Bu sayede kullanıcıdan boşluk içeren satırlar veya tüm satırı almamız gerektiğinde **getline** tercih edilir.
- `namespace`, aynı isimli tanımlamaların çakışmasını önlemek için kullanılır. Hem değişken, hem fonksiyon, hem de sınıf ve diğer tanımları ayrı gruplarda toplayabiliriz. **İç içe namespace**’ler tanımlamak da mümkündür.
- `constexpr`, derleme zamanında hesaplanabilen ve kesinlikle sabit (compile-time constant) olan değerler için;
- `consteval`, her çağrısı derleme zamanında kesinlikle değerlendirilir (C++20).
- `const` ise derlendikten sonra değiştirilemeyen, ama derleme zamanında mutlaka hesaplanamayabilecek değerler için kullanılır
- `std::vector<T>`: Dinamik boyutlu dizi. Eleman ekledikçe otomatik büyür.
- `std::array<T, N>`: Sabit boyutlu dizi; derleme zamanında N belirlenir.
- Büyük sayılarda okunaklığını artırmak için `'` kullanılır: `100'000'000` (C++14).
- **inline fonksiyon:** Derleme aşamasında çağrıldığı yere yerleştirilir (inlining), fonksiyon çağrısı yükünü azaltır.
- **inline namespace:** Birden fazla sürüm içeren kütüphanelerde, öntanımlı sürümü belirtmek için:

!!! note "Not"
    Bir değişkeni başlatmanın en güvenli yolu **list initialization**’dır; çünkü daraltıcı (narrowing) dönüşümlere örneğin bir float değeri doğrudan int’e izin vermez.

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

### Lambda İfadeleri
- `[a, &b]` belli değişkeni değer, diğerini referans alır.
- `[=]` tüm yerek değişkenleri kopyalar, `[&]` tüm yerel değişkenlere referans verir
- mutable ile değer yakalansa bile içerde değiştirme izinli olur ama dışarı etkilemez

```c++
auto f = []() { std::cout << "Hello\n"; };
f();

auto div = [](int x, int y) -> double { return static_cast<double>(x) / y; };

int a = 1, b = 2;
auto lv = [=]() mutable { a = 5; return a; }; // dışarıdaki a değişmez
auto lf = [&]()         { b = 5; return b; }; // dışarıdaki b değişir
```

### Şablonlar (Templates)

!!! note "Not"
	Eğer tüm argümanlar aynı türden ise `< >` yazmaya gerek yoktur.

```c++
template<typename T, typename U>
auto add(T a, U b) 
{
    	return a + b;
}

template<typename T, typename U = int>   //  Varsayılan olarak int
class MyClass {
public:
	MyClass() {
		T value{};
			std::cout << typeid(value).name() << '\n';
		}
		template<typename X>
		void add(X a, X b) {
		std::cout << (a + b) << '\n';
	}
};

int main() 
{
	MyClass<double>    m1;                           // U = int
    	MyClass<char, long> m2;                          // açık belirtildi
	m1.add(1.2, 3.4);
    	m1.add<double>(5.5, 6.6);

    	std::cout << add(10, 3.5) << '\n';               // 13.5
    	std::cout << add<int, double>(10, 3.5) << '\n';  // açık belirtilmiş
}
```

### Smart Pointers

C++’ta ham işaretçiler (`new/delete`) yerine **smart pointers** kullanmak, bellek sızıntılarını ve çifte silme hatalarını büyük oranda ortadan kaldırır. Üç ana türü vardır:

1. `std::unique_ptr<T>` Tek sahipli akıllı işaretçidir. `unique_ptr` scope sonlandığında `delete` çağrılır. **Kopyalanamaz**, ancak taşınabilir (`std::move`). Bu sayede çifte silme riskini ve bellek sızıntılarını önler. İsterseniz özel bir silici (deleter) de tanımlayabilirsiniz:
```c++
auto fileCloser = [](FILE* f){ if(f) fclose(f); };
std::unique_ptr<FILE, decltype(fileCloser)> fptr(fopen("log.txt","r"), fileCloser);
```

2. `std::shared_ptr<T>` Paylaşımlı sahiplik sağlayan işaretçidir. Aynı nesneye birden fazla `shared_ptr` işaret edebilir ve referans sayısı sıfırlanana dek nesne silinmez. Döngüsel bağımlılık riskini kırmak için `std::weak_ptr` kullanarak “zayıf” işaretçi oluşturabilirsiniz. Referans sayısını yönetmek için atomik işlemler kullandığından, unique_ptr’a göre biraz daha maliyetlidir.

3. `std::make_unique<T>(...)` ve `std::make_shared<T>(...)` C++14/17 ile gelen fabrikalar (factory functions). Ham işaretçi yerine doğrudan **smart pointers** oluşturur ve exception safety (istisna güvenliği) sağlar
```c++
auto up = std::make_unique<MyClass>(ctorArg1, ctorArg2);
auto sp = std::make_shared<MyClass>(ctorArg1, ctorArg2);
```

!!! note "Not"
	**`make_unique`** yalnızca bir sahipli unique_ptr döndürür. **`make_shared`** nesneyi ve referans sayacı tek bir bellek bloğunda tutar, daha verimli bellek kullanımı sunar.

### Casting Türleri
1. **static_cast<T>(x):** Derleme zamanında güvenli dönüşümler (örneğin sayı türleri arası).
2. **dynamic_cast<T*>(p):** Çalışma zamanında polimorfik sınıflar arasında güvenli downcast/upcast.
3. **const_cast<T&>(x):** const niteliğini kaldırmak için.
4. **reinterpret_cast<T*>(p):** İki iş parçacığı arasındaki bellek gösterimini yeniden yorumlamak için (çok dikkatli kullanılmalı).

### Nesne Yönelimli Programlama (OOP)
- Erişim Belirleyicileri (Access Specifiers): `public`, `protected`, `private`
- `class` default olarak `private`'dır
- Özel Üye Fonksiyonlar: `Default`, `Delete`
- Class içinde `default constructor` `destructor`, `copy constructor`, `copy assignment operator` eğer oluşturulmazsa default olarak oluşturur: 
- **Kapsülleme (Encapsulation):** Sınıfın iç verilerini `private` tutup, public` getter/ setter` metotlarıyla korumalı erişim sağlarsınız.
- `this`, içinde bulunduğunuz nesnenin adresini gösteren işaretçidir. 
- `static` üye değişken ve fonksiyonlar sınıfa ait, nesneye değil.
- `static` üye fonksiyonlar sadece başka static üyelere erişebilir.
- Tanımı sınıf dışına bir kez yapılmalıdır
- `friend` fonksiyon veya sınıflar, private/protected üyelere erişebilir
- **Operator Overloading** Sınıfınızda var olan operatörleri özelleştirebilirsiniz; ancak tüm operatörler yüklenemez (sizeof, ::, .* vb.).
- `const`, üye fonksiyonlar (void f() const) sınıf verilerini değiştirmez. `mutable` ile işaretlenmiş üye değişkenler, const fonksiyonlar içinde bile değiştirilebilir:
- `explicit` Tek parametreli kurucularda örtük (implicit) tür dönüşümünü engeller.
- **Inheritance** -> Erişim: public, protected veya private (**default private**).
- `virtual` kalıtım diamond problemini çözer
- **Polimorfizm** (Çok Biçimlilik) virtual üye fonksiyonlar, çağrının gerçek nesne türüne göre çözülmesini sağlar.
- **Saf sanal fonksiyon** (pure virtual) ile soyut sınıf (interface) oluşturulabilir.

## QT
- **Event Loop (Mesaj Döngüsü):** Her Qt uygulaması ve thread bir event queue’ya sahiptir. `app.exec()` çağrısı mesaj döngüsünü başlatır; olaylar (klavye, mouse, timer) ilgili nesnelere iletilir.
- **Loglama:** `qDebug(), qInfo(), qWarning(), qCritical(), qFatal()` çalışma zamanı logları için kullanılı
- **Kodlama Stili:** Qt projelerinde üye değişkenler genellikle m_ önekiyle adlandırılır.
- C++' da sinyal göndermek için `emit` kullanılır
- Qt Temel Veri Tipleri: `qint8, qint16, qint32, qint64, qintptr` (platform bağımsız tipler). 
- **`Q_PROPERTY`:** C++ üye değişkenlerini QML tarafına property olarak açar.
- **Q_GADGET:** QObject mirası olmadan Q_PROPERTY ve meta-type desteği sunar.
- Model–View: **QVariantList**, QML’de dizi gibi kullanılır.  **QAbstractListModel**, ListView / Repeater ile bağlanan veri modelleri için.


### Signals & Slots

- Qt’de nesneler arası iletişimi gevşek bağlı (loosely coupled) ve güvenli şekilde kurmak için kullanılan olay tabanlı bir mekanizmadır. 
- Bu yapı sayesinde gönderici ve alıcı nesneler birbirinin iç yapısını bilmez.
- **Signal:** Bir nesnede belirli bir olay gerçekleştiğinde yayımlanan bildiridir. Parametre taşıyabilir, doğrudan çağrı içermez.
- **Slot:** Bir sinyal tetiklendiğinde otomatik olarak çağrılan, normal bir C++ üye fonksiyonu veya lambda ifadesidir.
- Bu mekanizma, nesnelerin birbirinden habersiz çalışmasını (“loosely coupled”) sağlar
- Sinyal göndermek için `emit` kullanılır

```C++
// Modern kullanım (C++11+): Tip güvenli, derleme zamanında kontrol edilir
connect(sender, &Sender::valueChanged,
        receiver, &Receiver::onValueChanged);

// Eski stil: Makro tabanlı (runtime çözümleme, yazım hataları geç fark edilir)
connect(sender, SIGNAL(valueChanged(int)),
        receiver, SLOT(onValueChanged(int)));

disconnect(...);              // Bağlantıyı koparma
emit valueChanged(m_value);   // Signal tetikleme
```

### Meta-Object System (MOC)
- Qt’nin sinyal-slot, `Q_PROPERTY`, dinamik tür bilgisi (RTTI) gibi uzantılarını sağlayan araçtır.
- Her QObject türevi sınıfa `Q_OBJECT` makrosu eklenmeli; ardından moc (Meta-Object Compiler) bu sınıf için ek kod üretir.
- MOC çıktısı derleyiciye eklenerek sinyal-slot bağlama, öz nitelik (property) kaydı vb. işler otomatik hale gelir.
- Qt’nin sinyal-slot ve dinamik özelliğini sağlayan aracı.
- Her QObject türevindeki sınıfa `Q_OBJECT` makrosunu ekleyerek MOC’un işlevselliğini aktifleştirirsiniz.
- Qt’nin sinyal-slot, Q_PROPERTY, dinamik meta-veri gibi özellikleri formlar
- Q_OBJECT makrosunu eklediğiniz sınıflar için otomatik olarak ek kod üretir.
- Sınıfınıza sinyal, slot, property tanımları eklediğinizde, MOC bunları yürütebilecek C++ kaynaklarını oluşturur.
- Derleyiciye eklenen bu MOC çıktısı, Qt’nin meta-object altyapısının temelidir.
- MOC olmasaydı, connect(), emit, Q_PROPERTY gibi üst seviye mekanizmalar çalışmazdı.
- Kaynak dosyanızı derlerken, Qt’nin build sistemi otomatik olarak moc_MyClass.cpp gibi ek dosyalar üretir ve bu dosyalar da derlemeye dahil edilir.

### QML / C++  Bağlanması:
- `qmlRegisterType<T>(uri, major, minor, name)` QML’de name { } ile yeni nesne üretmek istediğinde kullanılır.
- `qmlRegisterSingletonInstance(uri, major, minor, name, instance)` Uygulama boyunca tek örnek (singleton) olacak C++ nesnesini QML’e global sunar.
- `qmlRegisterUncreatableType<T>(...)` QML’den new yapılamayan, sadece enum/sabit gibi içeriklerine erişilecek tipler için kullanılır.
- `QVariant` Farklı türleri tek kapsayıcıda taşır; QML–C++ arası veri akışında sık kullanılır (özellikle model/veri taşımada)
- `qRegisterMetaType<T>()` Custom tiplerin özellikle queued connection (thread arası sinyal-slot) ve QVariant senaryolarında sorunsuz taşınması için meta-type kaydıdır.
- `Q_INVOKABLE` QObject tabanlı sınıfta bir C++ fonksiyonunu QML’den doğrudan çağırılabilir hâle getirir (slot yazmadan).
- `QQmlContext::setContextProperty(name, obj)` Belirli bir engine/view için QML kök bağlamına değişken/nesne enjekte eder.

!!! note "Not"
	`QQmlContext::setContextProperty` Büyük projelerde kontrolsüz büyümeyi önlemek için genellikle kısıtlı kullanılır; modüler yaklaşım için `register` yöntemleri daha ölçeklenebilirdir.

```cpp title="main.cpp"
auto settings = new Settings(&engine);
qmlRegisterType<Model>("MyApp", 1, 0, "Model");
qmlRegisterSingletonInstance<Settings>("MyApp",1,0,"Settings", settings);
qmlRegisterUncreatableType<Constants>("MyApp.Utils", 1, 0, "Constants", 
						QStringLiteral("Only static enums/constants available"));
```