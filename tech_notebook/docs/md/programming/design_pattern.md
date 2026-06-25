# Design Pattern

Design Pattern, problemlere karşı geliştirilmiş çözüm yollarıdır. Kod parçası değil, bir **düşünce biçimidir**.


## Creational

Nesne **oluşturma** süreçlerini soyutlar. `new` yerine sistemin hangi nesneyi ne zaman üreteceğini kontrol altına alır.

### Factory Method

**Özü:** Nesne oluşturma kararını alt sınıflara bırakır.

**Problem:** Kod belirli bir iş yapar ama bu işi yapacak nesneyi direkt `new` ile oluşturduğunda, nesne türü ilerleyen süreçte değişince o koda dokunmak zorunlu kalırsın. Bu **Open/Closed Principle'ı** ihlal eder mevcut koda dokunmadan genişleyebilmek gerekir.

**Analoji:** Bir şube müdürü çalışana "bu görevi üstlen" der ama görevi kimin yapacağına işe alım departmanı karar verir. Müdür kimin işe alındığını bilmez; sadece işin yapılacağını bilir.

**Nasıl Çalışır:** Üst sınıf (`Creator`) bir `factoryMethod()` tanımlar ama ne üretileceğini bilmez. Alt sınıflar bu metodu override ederek hangi nesnenin üretileceğine karar verir. Üst sınıf sadece "bir ürün oluştur ve kullan" der, somut sınıfı bilmez.



```cpp
class Transport { // Soyut -> Tüm Taşıma İçin Ortak
public:
    virtual void deliver() = 0;
    virtual ~Transport() = default;
};

class Truck : public Transport {
public:
    void deliver() override { std::cout << "Truck\n"; }
};

class Ship : public Transport {
public:
    void deliver() override { std::cout << "Ship\n"; }
};

class Logistics { // Soyut Creator -> Ne Üretileceğini Bilmez, Sadece Kullanır
public:
    virtual std::unique_ptr<Transport> createTransport() = 0;

    void planDelivery() {
        auto transport = createTransport(); // hangi tür olduğu önemli değil
        transport->deliver();
    }

    virtual ~Logistics() = default;
};

// Concrete Creator — hangi nesnenin üretileceğine burada karar verilir
class RoadLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() override { return std::make_unique<Truck>(); }
};

class SeaLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() override { return std::make_unique<Ship>(); }
};

int main() {
    std::unique_ptr<Logistics> logistics = std::make_unique<RoadLogistics>();
    logistics->planDelivery(); // Kara yolu ile teslimat

    logistics = std::make_unique<SeaLogistics>();
    logistics->planDelivery(); // Deniz yolu ile teslimat
    // planDelivery() kodu hiç değişmedi sadece Creator değişti
}
```

!!! example "Gerçek Senaryo"
    Bir lojistik sisteminde kara, deniz ve hava taşımacılığı var. Sipariş yönetimi sadece "taşıma başlat" der. `RoadLogistics` Truck üretir, `SeaLogistics` Ship üretir. Yeni bir hava hattı eklemek istediğinde mevcut kodun hiçbirine dokunmadan yeni bir `AirLogistics` sınıfı yazarsın.

!!! tip "Ne Zaman Kullanılır?"
    - Hangi nesnenin oluşturulacağı çalışma zamanında belli oluyorsa
    - Yeni ürün türleri eklenecek ve mevcut koda dokunmak istemiyorsan
    - Ürün oluşturma sürecinin ortak bir şablonu var ama somut tipler değişiyorsa

!!! danger "Ne Zaman Kullanılmaz"
    Nesne türleri sabitse ve değişmeyecekse gereksiz soyutlamadır. Direkt `new` daha sade ve anlaşılır olur.

---

### Abstract Factory

**Özü:** Birbiriyle uyumlu nesne aileleri üretir; yanlış kombinasyonu imkânsız kılar.

**Problem:** Factory Method tek bir nesne üretir. Ama bazı sistemlerde birlikte çalışması gereken, birbiriyle uyumlu birden fazla nesne gerekir. Bunları ayrı ayrı oluşturmak yanlış kombinasyona yol açabilir (Windows butonu + Mac menüsü gibi).

**Analoji:** Mobilya mağazasında "Mid-century" tarz koleksiyon seçtiğinde, o koleksiyonun koltuk, masa ve rafı otomatik olarak uyumludur. Ayrı ayrı seçsen yanlış eşleştirme yapabilirsin.

```mermaid
classDiagram
    class AbstractFactory {
        <<interface>>
        +createButton() Button
        +createMenu() Menu
    }
    class DesktopFactory {
        +createButton() DesktopButton
        +createMenu() DesktopMenu
    }
    class EmbeddedFactory {
        +createButton() EmbeddedButton
        +createMenu() EmbeddedMenu
    }
    class Button {
        <<interface>>
        +render()
    }
    class Menu {
        <<interface>>
        +show()
    }
    AbstractFactory <|.. DesktopFactory
    AbstractFactory <|.. EmbeddedFactory
    DesktopFactory ..> Button
    DesktopFactory ..> Menu
    EmbeddedFactory ..> Button
    EmbeddedFactory ..> Menu
```

**Nasıl Çalışır:** `AbstractFactory` birden fazla ürün oluşturma metodunu tanımlar. Her konkret fabrika, aynı aileden tüm ürünleri üretir. İstemci hangi fabrikayı kullandığını bilir ama fabrikaların içindeki somut sınıfları bilmez.

```cpp
// Soyut ürünler
class Button {
public:
    virtual void render() = 0;
    virtual ~Button() = default;
};

class Menu {
public:
    virtual void show() = 0;
    virtual ~Menu() = default;
};

// Desktop ailesi
class DesktopButton : public Button {
public:
    void render() override { std::cout << "Desktop buton\n"; }
};

class DesktopMenu : public Menu {
public:
    void show() override { std::cout << "Desktop menü\n"; }
};

// Embedded ailesi
class EmbeddedButton : public Button {
public:
    void render() override { std::cout << "Embedded buton\n"; }
};

class EmbeddedMenu : public Menu {
public:
    void show() override { std::cout << "Embedded menü\n"; }
};

// Soyut fabrika — bir aile üretmekten sorumlu
class UIFactory {
public:
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Menu>   createMenu()   = 0;
    virtual ~UIFactory() = default;
};

class DesktopFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<DesktopButton>();
    }
    std::unique_ptr<Menu> createMenu() override {
        return std::make_unique<DesktopMenu>();
    }
};

class EmbeddedFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<EmbeddedButton>();
    }
    std::unique_ptr<Menu> createMenu() override {
        return std::make_unique<EmbeddedMenu>();
    }
};

// İstemci — hangi fabrika gelirse aynı kod çalışır; yanlış kombinasyon imkânsız
void buildUI(UIFactory& factory) {
    auto btn  = factory.createButton();
    auto menu = factory.createMenu();
    btn->render();
    menu->show();
}

int main() {
    DesktopFactory desktop;
    buildUI(desktop); // Desktop buton + Desktop menü (uyumlu)

    EmbeddedFactory embedded;
    buildUI(embedded); // Embedded buton + Embedded menü (uyumlu)
}
```

!!! example "Gerçek Senaryo"
    Cross-platform UI kütüphanesi: `WindowsFactory` her şeyin Windows stilini, `MacFactory` Mac stilini üretir. Uygulama platform seçimine göre fabrikayı değiştirir; tüm bileşenler otomatik uyumlu gelir.

!!! tip "Ne Zaman Kullanılır?"
    - Bir "tema" veya "platform" kavramıyla birden fazla nesnenin birlikte değişmesi gerektiğinde
    - Ürünlerin yanlış kombinasyonlarını derleme aşamasında önlemek istediğinde
    - İstemci kodu aynı kalırken sadece hangi ailenin kullanıldığı değişiyorsa

!!! tip "Factory Method ile Farkı"
    Factory Method **tek bir ürün** üretir, sınıf kalıtımıyla çalışır. Abstract Factory **uyumlu bir ürün ailesi** üretir, nesne bileşimiyle çalışır.

---

### Builder

**Özü:** Karmaşık nesnenin oluşturulmasını adım adım kontrol eder.

**Problem:** Bir nesnenin 10+ parametresi varsa ve bazıları opsiyonelse constructor felakete döner. `new Car(red, 4, true, false, null, "sport", 2.0)` — hangi parametre ne anlama geliyor? Ayrıca aynı nesnenin birden fazla varyantı olabilir (spor araba, SUV, elektrikli). Buna **Telescoping Constructor Anti-Pattern** denir: her kombinasyon için ayrı constructor yazmak zorunda kalırsın.

**Analoji:** Ev inşa etmek gibi düşün. Temel atılır, duvarlar örülür, çatı kurulur, içi döşenir. Her adım bağımsız ama sıralı. Hangi inşaat şirketi (builder) seçersen o şirkete göre sonuç değişir.

```mermaid
classDiagram
    class Builder {
        <<interface>>
        +setEngine()
        +setSensor()
        +setCamera()
        +getResult() UAV
    }
    class ReconBuilder {
        +setEngine()
        +setSensor()
        +setCamera()
        +getResult() UAV
    }
    class LogisticsBuilder {
        +setEngine()
        +setSensor()
        +setCamera()
        +getResult() UAV
    }
    class Director {
        -builder Builder
        +construct()
    }
    Builder <|.. ReconBuilder
    Builder <|.. LogisticsBuilder
    Director --> Builder
```

**Nasıl Çalışır:** Builder arayüzü yapım adımlarını tanımlar. Her konkret Builder bu adımları farklı biçimde uygular. `Director` (isteğe bağlı) hangi adımların hangi sırayla çağrılacağını bilir. Son olarak `getResult()` ile tamamlanmış nesne alınır.

```cpp
struct UAVConfig {
    std::string engine;
    std::string sensor;
    std::string camera;

    void print() const {
        std::cout << "Motor: " << engine
                  << " | Sensör: " << sensor
                  << " | Kamera: " << camera << "\n";
    }
};

// Builder arayüzü — hangi adımların var olduğunu tanımlar
class UAVBuilder {
public:
    virtual void setEngine() = 0;
    virtual void setSensor() = 0;
    virtual void setCamera() = 0;
    virtual UAVConfig getResult() = 0;
    virtual ~UAVBuilder() = default;
};

// Keşif İHA'sı — uzun menzil ve termal kamera
class ReconBuilder : public UAVBuilder {
    UAVConfig config;
public:
    void setEngine() override { config.engine = "Uzun menzil motoru"; }
    void setSensor() override { config.sensor = "Termal sensör"; }
    void setCamera() override { config.camera = "Yüksek çözünürlüklü kamera"; }
    UAVConfig getResult() override { return config; }
};

// Lojistik İHA'sı — güçlü motor ve kargo sistemi
class LogisticsBuilder : public UAVBuilder {
    UAVConfig config;
public:
    void setEngine() override { config.engine = "Yük taşıma motoru"; }
    void setSensor() override { config.sensor = "Temel sensör"; }
    void setCamera() override { config.camera = "Kargo kamerası"; }
    UAVConfig getResult() override { return config; }
};

// Director — hangi adımların hangi sırayla çağrılacağını bilir
class Director {
    UAVBuilder* builder;
public:
    Director(UAVBuilder* b) : builder(b) {}

    void construct() {
        builder->setEngine();
        builder->setSensor();
        builder->setCamera();
    }
};

int main() {
    ReconBuilder recon;
    Director dir(&recon);
    dir.construct();
    recon.getResult().print();
    // Motor: Uzun menzil motoru | Sensör: Termal sensör | Kamera: Yüksek çözünürlüklü kamera

    LogisticsBuilder logistics;
    Director dir2(&logistics);
    dir2.construct();
    logistics.getResult().print();
    // Motor: Yük taşıma motoru | Sensör: Temel sensör | Kamera: Kargo kamerası
}
```

!!! example "Gerçek Senaryo"
    İHA (İnsansız Hava Aracı) konfigürasyonu: aynı platform üzerinde keşif amaçlı (termal kamera, uzun menzil pili) veya lojistik amaçlı (kargo sistemi, kısa menzil) yapılandırma yapılabilir. `ReconBuilder` ve `LogisticsBuilder` aynı adımları farklı değerlerle doldurur. Director her iki İHA için de aynı `construct()` akışını çağırır.

!!! tip "Ne Zaman Kullanılır?"
    - 4'ten fazla parametreli constructor varsa
    - Opsiyonel parametreler çoksa
    - Aynı nesnenin birden fazla varyantı inşa edilecekse
    - Nesne oluşturma süreci birden fazla adım gerektiriyorsa

!!! note "Modern Dillerde Fluent Builder"
    `Car.builder().color("red").wheels(4).sport(true).build()` — zincirleme çağrı (method chaining) ile Builder'ın kullanıcı dostu hali. Her setter `*this` döndürür, böylece çağrılar zincir oluşturur. Pek çok modern kütüphanede bu yaklaşım kullanılır.

---

### Prototype

**Özü:** Sıfırdan oluşturmak yerine, var olan nesneyi klonla.

**Problem:** Bazı nesneler oluşturulması pahalıdır: veritabanı sorgusu, dosya okuma, ağır hesaplama gerektirebilir. Üstelik nesnenin karmaşık bir iç durumu varsa bunu sıfırdan tekrar kurmak hem zaman hem de kaynak israfıdır. İkinci sorun: bir nesneyi kopyalamak istiyorsun ama sınıfını bilmiyorsun (sadece soyut arayüzü biliyorsun), dolayısıyla direkt `new` kullanamazsın.

**Analoji:** Hücre bölünmesi — yeni hücre üretmek için sıfırdan tüm genetik bilgiyi oluşturmak yerine mevcut hücreyi kopyala ve gerekli küçük değişiklikleri yap.

**Nasıl Çalışır:** Her nesne kendi `clone()` metodunu uygular. İstemci kopyasını almak istediği nesneden `clone()` çağırır. İç yapıyı bilmesine gerek yoktur.

```cpp
// Her sensörün kendi clone() metodu var
class Sensor {
protected:
    std::string type;
    double      frequency;
    std::vector<double> calibration; // pahalı yapılandırma verisi

public:
    Sensor(std::string t, double f, std::vector<double> cal)
        : type(t), frequency(f), calibration(std::move(cal)) {}

    virtual std::unique_ptr<Sensor> clone() const = 0;

    void setFrequency(double f) { frequency = f; }

    virtual void report() const {
        std::cout << type << " @ " << frequency << " Hz, "
                  << calibration.size() << " kalibrasyon noktası\n";
    }

    virtual ~Sensor() = default;
};

class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(double freq, std::vector<double> cal)
        : Sensor("Sıcaklık", freq, std::move(cal)) {}

    // Kopya constructor'ı çağırır — deep copy otomatik
    std::unique_ptr<Sensor> clone() const override {
        return std::make_unique<TemperatureSensor>(*this);
    }
};

int main() {
    // Temel sensör bir kez pahalı şekilde kurulur
    TemperatureSensor base(100.0, {0.1, 0.2, 0.3, 0.4, 0.5});

    // Geri kalanlar klonlanır; sadece farklı parametre güncellenir
    auto sensor1 = base.clone();
    auto sensor2 = base.clone();
    sensor2->setFrequency(200.0); // yalnızca bu klonun frekansı değişir

    base.report();    // Sıcaklık @ 100 Hz, 5 kalibrasyon noktası
    sensor1->report();// Sıcaklık @ 100 Hz, 5 kalibrasyon noktası
    sensor2->report();// Sıcaklık @ 200 Hz, 5 kalibrasyon noktası
}
```

!!! warning "Deep Copy vs Shallow Copy — Kritik Nokta"
    **Shallow copy:** iç nesnelerin referansları kopyalanır, aynı belleği paylaşırlar. Bir kopyadaki değişiklik diğerini etkiler. **Deep copy:** tüm iç nesneler de ayrı kopyalanır. Prototype uygularken hangi derinlikte kopyalama yapılacağı açıkça belirlenmeli; yanlış seçim sessiz hatalara yol açar. C++'da kullanıcı tanımlı kopya constructor yazarak deep copy sağlanır.

!!! example "Gerçek Senaryo"
    Simülasyon ortamında yüzlerce sensör modeli var; hepsinin temel konfigürasyonu aynı ama küçük parametreler farklı. Temel sensör bir kez yapılandırılır, geri kalanlar klonlanır ve sadece farklı olan parametre güncellenir. Hem hız kazanılır hem de tutarlı başlangıç yapısı korunur.

!!! tip "Ne Zaman Kullanılır?"
    - Nesne oluşturma maliyeti yüksekse (DB sorgusu, ağ çağrısı, ağır hesaplama)
    - Nesnenin sınıfını bilmeden kopyası gerekiyorsa
    - Sadece küçük farklılıklarla çok sayıda benzer nesne üretilecekse

---

### Singleton

**Özü:** Sistem genelinde yalnızca tek bir örnek garanti eder ve ona kontrollü erişim noktası sağlar.

**Problem:** Bazı kaynakların birden fazla örneğinin olması anlamsız veya tehlikelidir: birden fazla logger çakışabilir, birden fazla config manager farklı ayarlar okuyabilir, birden fazla connection pool gereksiz kaynak tüketebilir.

**Analoji:** Bir ülkede tek bir hükümet olur. Birden fazla olursa çelişkili kararlar çıkar, kaos oluşur.

```mermaid
classDiagram
    class Singleton {
        -instance$ Singleton
        -Singleton()
        +getInstance()$ Singleton
        +operation()
    }
    Singleton --> Singleton : creates
```

**Nasıl Çalışır:** Constructor private'tır — dışarıdan `new` ile örnek alınamaz. Tek erişim noktası statik `getInstance()` metodudur. İlk çağrıda örnek oluşturulur, sonraki çağrılarda aynı örnek döner.

```cpp
class Logger {
public:
    // Kopya ve taşıma operasyonları kapalı — ikinci örnek yaratılamaz
    Logger(const Logger&)            = delete;
    Logger& operator=(const Logger&) = delete;

    // C++11: static local variable thread-safe garantilidir
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& msg) {
        std::cout << "[LOG] " << msg << "\n";
    }

private:
    Logger() { std::cout << "Logger oluşturuldu\n"; }
};

int main() {
    Logger::getInstance().log("Sistem başlatıldı");
    Logger::getInstance().log("Bağlantı kuruldu");
    // "Logger oluşturuldu" yalnızca bir kez yazdırılır
    // Her çağrı aynı nesneyi kullanır
}
```

!!! danger "Ciddi Tuzaklar Var — Dikkatli Kullanın"
    - **Test edilemezlik:** Global durum yarattığı için unit testlerde izole etmek zordur. Bir testin değiştirdiği state başka testi etkiler.
    - **Gizli bağımlılık:** Sınıfın hangi bağımlılıklara sahip olduğu constructor'dan anlaşılmaz; Singleton sınıf içinde gizlenir.
    - **Thread safety:** C++11 öncesinde static local variable thread-safe değildi. C++11 sonrasında bu sorun dil garantisiyle çözülmüştür.
    - **Çoğu durumda yanlış araç:** "Tek örnek" isteği genellikle Dependency Injection ile daha temiz çözülür.

!!! tip "Ne Zaman Kullanılır?"
    Gerçekten sistem genelinde tek örnek **zorunlu** olduğunda: logger, yapılandırma yöneticisi, thread pool, donanım sürücüsü arayüzü. Bunların dışında DI container tercih edilmeli.

---

## Structural (Yapısal Desenler)

Sınıflar ve nesneler arasındaki **ilişkileri** düzenler. Bileşenleri birleştirirken bağımlılıkları kontrol altında tutar.

---

### Adapter

**Özü:** Uyumsuz arayüzleri birbirine bağlayan çevirmen.

**Problem:** Kullanmak istediğin bir kütüphane veya servis var ama arayüzü sisteminde beklenen arayüzle uyuşmuyor. Kütüphaneyi değiştiremezsin (üçüncü parti), kendi kodunu da köklü değiştirmek istemiyorsun.

**Analoji:** Seyahatte farklı priz adaptörü kullanırsın. Cihazın (istemci) ve prizin (servis) hiçbiri değişmez; sadece araya bir adaptör girer.

```mermaid
classDiagram
    class Target {
        <<interface>>
        +request() JSON
    }
    class Adaptee {
        +specificRequest() XML
    }
    class Adapter {
        -adaptee Adaptee
        +request() JSON
    }
    class Client {
        +operation()
    }
    Target <|.. Adapter
    Adapter --> Adaptee
    Client --> Target
```

**Nasıl Çalışır:** Adapter, istemcinin beklediği `Target` arayüzünü uygular. İçinde `Adaptee` nesnesini tutar. İstemci `request()` çağırdığında, Adapter bunu `Adaptee`'nin uyumsuz metoduna çevirir.

```cpp
// Sistemin beklediği arayüz — JSON döndürmeli
class DataSource {
public:
    virtual std::string getData() = 0;
    virtual ~DataSource() = default;
};

// Üçüncü parti sensör servisi — XML döndürüyor, değiştirilemiyor
class XmlSensor {
public:
    std::string getXmlData() {
        return "<data><temp>25.5</temp><hum>60</hum></data>";
    }
};

// Adapter: XmlSensor'ı DataSource arayüzüne uyarlar
class XmlToJsonAdapter : public DataSource {
    XmlSensor sensor;
public:
    std::string getData() override {
        std::string xml = sensor.getXmlData();
        // Gerçek projede XML parser kullanılır; burada basit dönüşüm
        return R"({"temp": 25.5, "hum": 60})";
    }
};

// İstemci — sadece DataSource bilir; XmlSensor'ın varlığından habersiz
void process(DataSource& src) {
    std::cout << src.getData() << "\n";
}

int main() {
    XmlToJsonAdapter adapter;
    process(adapter); // {"temp": 25.5, "hum": 60}
}
```

!!! example "Gerçek Senaryo"
    Sistemin standart veri formatı JSON, ama entegre etmen gereken harici bir sensör servisi XML döndürüyor. Adapter araya girerek XML'i JSON'a çevirir. Ne sisteme ne de sensör servisine dokunmazsın.

!!! tip "Ne Zaman Kullanılır?"
    - Üçüncü parti kütüphane entegrasyonunda (arayüz değiştirilemez)
    - Legacy sistem ile yeni sistem arasında köprü kurulurken
    - Aynı işi yapan ama farklı arayüzlere sahip birden fazla servis kullanılacaksa

!!! note "Bridge ile Farkı"
    Adapter **mevcut** uyumsuzluğu giderir (reaktif çözüm). Bridge ise tasarım aşamasında kasıtlı olarak soyutlamayı implementasyondan ayırır (proaktif tasarım).

---

### Bridge

**Özü:** Soyutlamayı implementasyondan ayırır; her ikisi bağımsız olarak geliştirilebilir.

**Problem:** İki boyutta değişen bir sistemi kalıtımla modellemek istiyorsun. 3 kaynak × 3 algoritma = 9 sınıf. Yeni algoritma eklenince 3 sınıf daha, yeni kaynak eklenince 3 sınıf daha. Bu **sınıf patlaması** sürdürülemez.

**Analoji:** Uzaktan kumanda (soyutlama) ve TV (implementasyon) ayrıdır. Farklı kumanda modelleri (temel, gelişmiş) farklı TV markaları (Sony, Samsung) ile çalışabilir. Her ikisi bağımsız olarak genişleyebilir.

```mermaid
classDiagram
    class Abstraction {
        #impl Implementation
        +operation()
    }
    class RefinedAbstraction {
        +operation()
    }
    class Implementation {
        <<interface>>
        +operationImpl()
    }
    class ConcreteImplA {
        +operationImpl()
    }
    class ConcreteImplB {
        +operationImpl()
    }
    Abstraction <|-- RefinedAbstraction
    Abstraction --> Implementation
    Implementation <|.. ConcreteImplA
    Implementation <|.. ConcreteImplB
```

**Nasıl Çalışır:** Soyutlama katmanı bir `Implementation` referansı tutar. Kendi metodları bu implementasyona delege eder. İki hiyerarşi birbirinden bağımsız büyüyebilir. 3 kaynak + 3 algoritma = toplam 6 sınıf (9 yerine).

```cpp
// Implementation hiyerarşisi — görüntü işleme algoritmaları
class ImageProcessor {
public:
    virtual void process(const std::string& data) = 0;
    virtual ~ImageProcessor() = default;
};

class FilterProcessor : public ImageProcessor {
public:
    void process(const std::string& data) override {
        std::cout << "Filtre uygulandı: " << data << "\n";
    }
};

class CompressionProcessor : public ImageProcessor {
public:
    void process(const std::string& data) override {
        std::cout << "Sıkıştırıldı: " << data << "\n";
    }
};

// Abstraction hiyerarşisi — veri kaynakları
// Kaynak, hangi algoritmanın kullanıldığını bilmez
class DataSource {
protected:
    ImageProcessor* processor;
public:
    DataSource(ImageProcessor* p) : processor(p) {}
    virtual void capture() = 0;
    virtual ~DataSource() = default;
};

class CameraSource : public DataSource {
public:
    CameraSource(ImageProcessor* p) : DataSource(p) {}
    void capture() override {
        processor->process("kamera görüntüsü");
    }
};

class FileSource : public DataSource {
public:
    FileSource(ImageProcessor* p) : DataSource(p) {}
    void capture() override {
        processor->process("dosya içeriği");
    }
};

int main() {
    FilterProcessor filter;
    CompressionProcessor compress;

    CameraSource cam1(&filter);    // kamera + filtre
    CameraSource cam2(&compress);  // kamera + sıkıştırma
    FileSource   file(&filter);    // dosya + filtre

    cam1.capture(); // Filtre uygulandı: kamera görüntüsü
    cam2.capture(); // Sıkıştırıldı: kamera görüntüsü
    file.capture(); // Filtre uygulandı: dosya içeriği
    // Yeni algoritma eklense Camera/FileSource'a dokunulmaz
}
```

!!! example "Gerçek Senaryo"
    Görüntü işleme sistemi: farklı veri kaynakları (kamera, dosya, ağ akışı) × farklı işleme algoritmaları (filtreleme, sıkıştırma, nesne tespiti). Bridge ile kaynak ve algoritma birbirinden ayrılır. Yeni kamera tipi eklenince algoritmalara dokunulmaz; yeni algoritma eklenince kaynaklara dokunulmaz.

!!! tip "Ne Zaman Kullanılır?"
    - İki bağımsız boyutta büyüyecek bir sistem tasarlarken
    - Runtime'da implementasyonu değiştirme ihtiyacı olduğunda
    - Platform bağımsızlığı gerektiğinde (farklı OS, farklı donanım)

---

### Composite

**Özü:** Tekil nesneleri ve nesne gruplarını aynı arayüzle kullan.

**Problem:** Ağaç yapısı gibi hiyerarşik bir veri var: dosyalar ve klasörler, askerler ve birlikler, UI bileşenleri ve konteynerler. İstemcinin "bu bir yaprak mı, yoksa grup mu?" diye sorgulamadan işlem yapabilmesi gerekiyor.

**Analoji:** Askeri hiyerarşi — tek bir asker de "ateş et" emri alır, tüm bir tugay da. Komutan kimi emrettiğini sorgulamaz; emir kademelere göre aşağı iner.

```mermaid
classDiagram
    class Component {
        <<interface>>
        +operation()
        +add(Component)
        +remove(Component)
    }
    class Leaf {
        +operation()
    }
    class Composite {
        -children List~Component~
        +operation()
        +add(Component)
        +remove(Component)
    }
    Component <|.. Leaf
    Component <|.. Composite
    Composite --> Component : içerir
```

**Nasıl Çalışır:** Her şey (hem yaprak hem grup) aynı `Component` arayüzünü uygular. `Composite` nesnesi çocuklarını tutar ve kendine gelen `operation()` çağrısını tüm çocuklarına iletir. İstemci her ikisine de aynı şekilde davranır.

```cpp
// Hem dosya hem klasör bu arayüzü uygular
class FileComponent {
public:
    virtual int  getSize() const = 0;
    virtual void print(int depth = 0) const = 0;
    virtual ~FileComponent() = default;
};

// Yaprak — çocuğu yoktur
class File : public FileComponent {
    std::string name;
    int size;
public:
    File(std::string n, int s) : name(std::move(n)), size(s) {}

    int getSize() const override { return size; }

    void print(int depth = 0) const override {
        std::cout << std::string(depth * 2, ' ')
                  << name << " (" << size << " KB)\n";
    }
};

// Bileşik — içinde başka Component'lar barındırır
class Directory : public FileComponent {
    std::string name;
    std::vector<std::unique_ptr<FileComponent>> children;
public:
    Directory(std::string n) : name(std::move(n)) {}

    void add(std::unique_ptr<FileComponent> c) {
        children.push_back(std::move(c));
    }

    int getSize() const override {
        int total = 0;
        for (const auto& c : children) total += c->getSize();
        return total;
    }

    void print(int depth = 0) const override {
        std::cout << std::string(depth * 2, ' ') << "[" << name << "]\n";
        for (const auto& c : children) c->print(depth + 1);
    }
};

int main() {
    auto root = std::make_unique<Directory>("root");
    root->add(std::make_unique<File>("main.cpp", 10));

    auto src = std::make_unique<Directory>("src");
    src->add(std::make_unique<File>("utils.cpp", 5));
    src->add(std::make_unique<File>("driver.cpp", 8));
    root->add(std::move(src));

    root->print();
    // [root]
    //   main.cpp (10 KB)
    //   [src]
    //     utils.cpp (5 KB)
    //     driver.cpp (8 KB)

    std::cout << "Toplam: " << root->getSize() << " KB\n"; // 23 KB
}
```

!!! example "Gerçek Senaryo"
    Dosya sistemi: "boyut hesapla" komutu bir dosyaya da klasöre de uygulanabilir. Klasör, kendi içindeki tüm dosya ve alt klasörlerin boyutunu toplar. Kod yazan kişi her iki durumu ayrı ayrı ele almak zorunda kalmaz.

!!! tip "Ne Zaman Kullanılır?"
    - Ağaç yapısı temsil edilecekse
    - İstemcinin tekil ve bileşik nesneleri aynı şekilde kullanması gerekiyorsa
    - Hiyerarşinin derinliği önceden belli değilse

---

### Decorator

**Özü:** Nesneye çalışma zamanında yeni davranış ekler; kalıtım kullanmaz.

**Problem:** Bir nesneye davranış eklemek istiyorsun ama alt sınıf açmak istemiyorsun. Çok fazla kombinasyon varsa (şifreli+sıkıştırılmış, sadece şifreli, sadece sıkıştırılmış, ikisi de yok — her biri için ayrı sınıf mı?) ya da davranışın çalışma zamanında dinamik olarak eklenmesi/çıkarılması gerekiyorsa.

**Analoji:** Kahve siparişi — temel espresso, üzerine süt ekle (cafe latte), üzerine krema ekle (cappuccino). Her katman bir öncekini "sarar" ve yeni davranış ekler. Kombinasyonlar serbesttir.

```mermaid
classDiagram
    class Component {
        <<interface>>
        +operation()
    }
    class ConcreteComponent {
        +operation()
    }
    class BaseDecorator {
        -wrappee Component
        +operation()
    }
    class EncryptionDecorator {
        +operation()
    }
    class CompressionDecorator {
        +operation()
    }
    Component <|.. ConcreteComponent
    Component <|.. BaseDecorator
    BaseDecorator <|-- EncryptionDecorator
    BaseDecorator <|-- CompressionDecorator
    BaseDecorator --> Component
```

**Nasıl Çalışır:** Decorator, sardığı nesneyle aynı arayüzü uygular. `operation()` çağrıldığında önce/sonra kendi davranışını ekler ve sarılan nesnenin `operation()`'ını da çağırır. Birden fazla Decorator zincir şeklinde birbirini sarabilir.

```cpp
// Ortak arayüz — hem gerçek kanal hem decorator bunu uygular
class DataChannel {
public:
    virtual void send(const std::string& data) = 0;
    virtual ~DataChannel() = default;
};

// Gerçek kanal — ham gönderim
class BasicChannel : public DataChannel {
public:
    void send(const std::string& data) override {
        std::cout << "Gönderildi: " << data << "\n";
    }
};

// Temel Decorator — sarılan nesneyi tutar ve ona delege eder
class ChannelDecorator : public DataChannel {
protected:
    DataChannel* wrappee;
public:
    ChannelDecorator(DataChannel* c) : wrappee(c) {}
};

class EncryptionDecorator : public ChannelDecorator {
public:
    EncryptionDecorator(DataChannel* c) : ChannelDecorator(c) {}

    void send(const std::string& data) override {
        // Önce kendi işini yap, sonra zincirin geri kalanına ilet
        wrappee->send("[ENC:" + data + "]");
    }
};

class CompressionDecorator : public ChannelDecorator {
public:
    CompressionDecorator(DataChannel* c) : ChannelDecorator(c) {}

    void send(const std::string& data) override {
        wrappee->send("[ZIP:" + data + "]");
    }
};

int main() {
    BasicChannel base;

    // Sadece şifreleme
    EncryptionDecorator encrypted(&base);
    encrypted.send("veri");
    // Gönderildi: [ENC:veri]

    // Önce sıkıştır, sonra şifrele
    CompressionDecorator both(&encrypted);
    both.send("veri");
    // Gönderildi: [ENC:[ZIP:veri]]
    // Kombinasyonlar çalışma zamanında, sınıf açmadan oluşturulur
}
```

!!! example "Gerçek Senaryo"
    Haberleşme modülü: temel veri gönderimi var. Bazı senaryolarda şifreleme, bazılarında sıkıştırma, bazılarında ikisi birden gerekiyor. Her kombinasyon için ayrı sınıf açmak yerine `EncryptionDecorator` ve `CompressionDecorator` isteğe bağlı zincire eklenir ve çıkarılabilir.

!!! tip "Ne Zaman Kullanılır?"
    - Nesneye çalışma zamanında dinamik davranış eklenmesi/çıkarılması gerektiğinde
    - Çok sayıda bağımsız özellik birbirleriyle kombine edilebilecekse
    - Alt sınıf açmak sınıf sayısını patlatacaksa

!!! note "Kalıtıma Karşı Avantajı"
    Kalıtım derleme zamanında sabittir. Decorator çalışma zamanında esnektir ve kombine edilebilir.

---

### Facade

**Özü:** Karmaşık alt sistemin önüne sade bir yüz koyar.

**Problem:** Bir alt sistem birden fazla sınıftan oluşuyor; birini kullanmak için diğerini başlatman, birini diğerine bağlaman gerekiyor. İstemci bu karmaşıklığa maruz kalıyor ve alt sistemin iç detaylarını bilmek zorunda kalıyor.

**Analoji:** Ev sinema sistemi kurarken — TV'yi aç, amplifikatörü doğru girişe al, Blu-ray'i bağla, ışıkları kıs, perdeleri indir. Ya da "film izleme modunu başlat" diyen tek buton — hepsini sıralı yapar.

**Nasıl Çalışır:** Facade tüm alt sistemlerin referanslarını tutar. İstemciye basit, yüksek seviyeli metodlar sunar. Bu metodların içinde gerekli alt sistem çağrıları doğru sırayla yapılır.

```cpp
// Alt sistem sınıfları — ayrı ayrı karmaşık ve birbirine bağımlı
class AudioDriver {
public:
    void initialize()  { std::cout << "Ses sürücüsü başlatıldı\n"; }
    void setVolume(int v) { std::cout << "Ses seviyesi: " << v << "\n"; }
    void shutdown()    { std::cout << "Ses sürücüsü kapatıldı\n"; }
};

class VideoCodec {
public:
    void load(const std::string& f) { std::cout << "Video yüklendi: " << f << "\n"; }
    void decode() { std::cout << "Decode ediliyor\n"; }
    void release() { std::cout << "Codec serbest bırakıldı\n"; }
};

class NetworkBuffer {
public:
    void allocate(int mb) { std::cout << "Buffer: " << mb << " MB ayrıldı\n"; }
    void flush() { std::cout << "Buffer temizlendi\n"; }
};

// Facade — istemci yalnızca bunu kullanır
class MediaFacade {
    AudioDriver  audio;
    VideoCodec   codec;
    NetworkBuffer buffer;
public:
    void play(const std::string& file) {
        buffer.allocate(256);
        audio.initialize();
        audio.setVolume(80);
        codec.load(file);
        codec.decode();
        std::cout << ">> Oynatılıyor: " << file << "\n";
    }

    void stop() {
        codec.release();
        audio.shutdown();
        buffer.flush();
        std::cout << ">> Durduruldu\n";
    }
};

int main() {
    MediaFacade media;
    media.play("video.mp4");
    // Alt sistemlerin sırası ve bağımlılıkları istemciden tamamen gizlendi
    media.stop();
}
```

!!! example "Gerçek Senaryo"
    Bir multimedya sistemi: ses sürücüsü, video codec, ağ tamponu, donanım hızlandırıcı ayrı ayrı çalışıyor. `MediaFacade.play(file)` tek çağrısı tüm bu bileşenleri doğru sırayla başlatır ve senkronize eder.

!!! tip "Ne Zaman Kullanılır?"
    - Karmaşık bir kütüphane veya framework'e basit bir giriş noktası sağlamak istediğinde
    - Alt sistem bağımlılıklarını istemciden gizlemek istediğinde
    - Katmanlı mimaride katmanlar arası erişimi tek noktadan yönetmek için

!!! note "Önemli Ayrım"
    Facade alt sistemi gizlemez, sadece basit bir arayüz ekler. İsteyen istemci hâlâ alt sistemle doğrudan etkileşebilir. Bu bir kısıtlama değil, kolaylıktır.

---

### Flyweight

**Özü:** Çok sayıda benzer nesnenin ortak verilerini paylaştır; belleği boşa harcama.

**Problem:** Binlerce (ya da milyonlarca) benzer nesne oluşturuyorsun. Her nesne aynı verinin kopyasını taşıyorsa bellek tükenir.

**Analoji:** Kelime işlemcide her karakter için ayrı bir nesne oluşturuluyor. Her "A" harfinin font, boyut, stil bilgisini ayrı ayrı tutmak yerine bu bilgiler paylaşılır. Sadece pozisyon bilgisi her karakter için ayrı tutulur.

**Nasıl Çalışır:**

- **Intrinsic (içsel, değişmez) durum:** Tüm örneklerde aynı olan veri. Flyweight nesnesinde saklanır ve paylaşılır.
- **Extrinsic (dışsal, değişken) durum:** Her örnek için farklı olan veri. Flyweight'e parametre olarak dışarıdan geçirilir, içinde saklanmaz.

```cpp
// Intrinsic (paylaşılan) veri — büyük, her ağaç için aynı
struct TreeType {
    std::string name;
    std::string color;
    std::string texture; // 3D model, yüksek boyutlu veri

    void render(int x, int y) const {
        std::cout << name << " (" << color << ") konumu: ("
                  << x << "," << y << ")\n";
    }
};

// Flyweight Factory — aynı tür için tek nesne döner
class TreeFactory {
    std::unordered_map<std::string, TreeType> cache;
public:
    const TreeType& getType(const std::string& name,
                             const std::string& color,
                             const std::string& texture) {
        std::string key = name + "|" + color;
        if (cache.find(key) == cache.end()) {
            cache[key] = {name, color, texture};
            std::cout << "Yeni TreeType oluşturuldu: " << key << "\n";
        }
        return cache[key];
    }
};

// Extrinsic (eşsiz) veri — sadece konum her ağaç için farklı
struct Tree {
    int x, y;
    const TreeType* type; // paylaşılan nesnenin pointer'ı

    void render() const { type->render(x, y); }
};

int main() {
    TreeFactory factory;
    std::vector<Tree> forest;

    // 10.000 ağaç — ama yalnızca 1 TreeType nesnesi
    for (int i = 0; i < 10000; ++i) {
        const auto& type = factory.getType("Meşe", "Yeşil", "buyuk_texture.bin");
        forest.push_back({i % 100, i / 100, &type});
    }
    // "Yeni TreeType oluşturuldu" yalnızca 1 kez yazdırılır
    forest[0].render();
    forest[999].render();
}
```

!!! example "Gerçek Senaryo"
    Harita uygulamasında 10.000 ağaç nesnesi: her ağacın türü, rengi ve 3D modeli aynı (intrinsic). Sadece konum bilgisi farklı (extrinsic). 10.000 ayrı büyük nesne yerine tek bir `TreeType` nesnesi paylaşılır, konumlar ayrı tutulur. Bellek kullanımı dramatik biçimde düşer.

!!! tip "Ne Zaman Kullanılır?"
    - Çok sayıda benzer nesne oluşturulacak ve bellek kritikse
    - Nesnenin büyük kısmı paylaşılabilir (intrinsic) durumdan oluşuyorsa
    - Oyun motorları, grafik sistemleri, metin işleme motorları

!!! danger "Dikkat"
    Extrinsic durumu yönetmek karmaşıklaşır. Nesne sayısı gerçekten büyük değilse eklenen karmaşıklık faydasızdır. Önce profil et, sonra uygula.

---

### Proxy

**Özü:** Başka bir nesneye erişimi kontrol eden ya da yöneten vekil nesne.

**Problem:** Bir nesneye erişmeden önce ek kontrol yapmak istiyorsun: yetki kontrolü, önbellekleme, gecikmeli yükleme, loglama. Ama bu kontrolleri nesnenin kendisine eklemek onun sorumluluklarını genişletir ve Tek Sorumluluk Prensibi'ni ihlal eder.

**Analoji:** Şirket avukatı müvekkil adına iş yapar. Sözleşme imzalamak için doğrudan müvekkile ulaşmak zorunda değilsin. Avukat (proxy) müvekkili temsil eder ve gerekli kontrolleri yapar.

**Proxy Türleri:**

| Tür | Amaç |
|-----|------|
| **Virtual Proxy** | Gecikmeli başlatma — pahalı nesneyi gerçekten gerektiğinde oluştur |
| **Protection Proxy** | Erişim kontrolü — kim neyi görebilir/yapabilir |
| **Caching Proxy** | Önbellekleme — aynı sonucu tekrar hesaplama |
| **Remote Proxy** | Uzak nesneye yerel arayüzden eriş (RPC, stub) |

```cpp
// Ortak arayüz — hem gerçek nesne hem proxy bunu uygular
class Document {
public:
    virtual std::string getContent() = 0;
    virtual ~Document() = default;
};

// Gerçek nesne — oluşturması pahalı
class RealDocument : public Document {
    std::string filename;
    std::string content;
public:
    RealDocument(const std::string& f) : filename(f) {
        // Disk okuma simülasyonu — yavaş işlem
        std::cout << "Disk'ten okunuyor: " << filename << "\n";
        content = "Dosya içeriği: " + filename;
    }
    std::string getContent() override { return content; }
};

// Virtual Proxy — gerçek nesneyi ilk erişime kadar oluşturmaz
class DocumentProxy : public Document {
    std::string filename;
    std::unique_ptr<RealDocument> real; // başlangıçta null
public:
    DocumentProxy(const std::string& f) : filename(f) {
        std::cout << "Proxy oluşturuldu: " << filename << " (henüz yüklenmedi)\n";
    }

    std::string getContent() override {
        if (!real) {
            real = std::make_unique<RealDocument>(filename); // lazy load
        }
        return real->getContent();
    }
};

int main() {
    DocumentProxy doc("rapor.pdf");
    // "Proxy oluşturuldu" — disk henüz okunmadı

    std::cout << "Belge henüz açılmadı\n";
    std::cout << doc.getContent() << "\n";
    // İlk erişimde: "Disk'ten okunuyor: rapor.pdf"

    std::cout << doc.getContent() << "\n";
    // İkinci erişimde disk okuması yok — zaten yüklü
}
```

!!! example "Gerçek Senaryo"
    Büyük veri dosyası yükleyen bir sistem: dosya henüz gerekmeyebilir. Virtual Proxy ile gerçek dosya nesnesi `getContent()` ilk çağrılana kadar oluşturulmaz. Kullanıcı dosyayı hiç açmazsa kaynak harcanmamış olur.

!!! tip "Ne Zaman Kullanılır?"
    - Pahalı nesnenin gecikmeli başlatılması gerekiyorsa (Virtual)
    - Nesneyi değiştirmeden erişim kontrolü eklemek istiyorsan (Protection)
    - Ağ çağrılarını veya hesaplamaları önbelleğe almak istiyorsan (Caching)

---

## Behavioral (Davranışsal Desenler)

Nesneler arasındaki **iletişimi** ve **sorumluluk dağılımını** düzenler. Kim ne yapmalı, kim kimi bilmeli sorularını yanıtlar.

---

### Chain of Responsibility

**Özü:** İsteği bir zincir boyunca ilet; kimin işleyeceğini başlatıcı bilmek zorunda değil.

**Problem:** Bir istek birden fazla işleyici tarafından ele alınabilir ama hangisinin devreye gireceği önceden belli değil veya değişebilir. İstemci koduna "bu durumda A'ya git, şu durumda B'ye git" yazmak kodu kırılgan yapar.

**Analoji:** Şirket içi onay süreci: 1.000 TL'ye kadar müdür onaylar, 10.000 TL'ye kadar direktör, üzeri CEO. Her onaylayan kendi limitini aşan talepleri bir üst kademeye iletir. Talep sahibi kime gideceğini bilmez; zincire bırakır.

```mermaid
flowchart LR
    Client -->|istek| H1[Handler 1]
    H1 -->|işleyemezse| H2[Handler 2]
    H2 -->|işleyemezse| H3[Handler 3]
    H3 -->|işleyemezse| X([İşlenemedi])
    H1 -->|işlerse| R1([Çözüldü])
    H2 -->|işlerse| R2([Çözüldü])
    H3 -->|işlerse| R3([Çözüldü])
```

**Nasıl Çalışır:** Her işleyici bir sonraki işleyiciye referans tutar. İsteği işleyebiliyorsa işler, işleyemiyorsa zincirdeki bir sonrakine iletir. İstemci sadece zincirin başını bilir.

```cpp
// Her onaylayıcı zincirin bir halkası
class ApprovalHandler {
protected:
    ApprovalHandler* next = nullptr;
public:
    void setNext(ApprovalHandler* n) { next = n; }

    virtual void handleRequest(int amount) {
        if (next) {
            next->handleRequest(amount);
        } else {
            std::cout << amount << " TL onaylanamadı — limit aşıldı\n";
        }
    }

    virtual ~ApprovalHandler() = default;
};

class Manager : public ApprovalHandler {
public:
    void handleRequest(int amount) override {
        if (amount <= 1000) {
            std::cout << "Müdür onayladı: " << amount << " TL\n";
        } else {
            ApprovalHandler::handleRequest(amount); // bir üste ilet
        }
    }
};

class Director : public ApprovalHandler {
public:
    void handleRequest(int amount) override {
        if (amount <= 10000) {
            std::cout << "Direktör onayladı: " << amount << " TL\n";
        } else {
            ApprovalHandler::handleRequest(amount);
        }
    }
};

class CEO : public ApprovalHandler {
public:
    void handleRequest(int amount) override {
        std::cout << "CEO onayladı: " << amount << " TL\n";
    }
};

int main() {
    Manager  mgr;
    Director dir;
    CEO      ceo;

    // Zinciri kur — istemci yalnızca zincirin başını bilir
    mgr.setNext(&dir);
    dir.setNext(&ceo);

    mgr.handleRequest(500);    // Müdür onayladı: 500 TL
    mgr.handleRequest(5000);   // Direktör onayladı: 5000 TL
    mgr.handleRequest(50000);  // CEO onayladı: 50000 TL
}
```

!!! example "Gerçek Senaryo"
    Web framework'lerindeki middleware pipeline: istek sırayla kimlik doğrulama, yetkilendirme, rate limiting, loglama katmanlarından geçer. Her katman isteği işler veya reddeder; reddedilmezse bir sonrakine iletir.

!!! tip "Ne Zaman Kullanılır?"
    - Birden fazla nesnenin aynı isteği işleyebileceği ve hangisinin işleyeceğinin önceden bilinmediği durumlarda
    - İşleyici kümesinin çalışma zamanında dinamik değişmesi gerektiğinde
    - İsteğin birden fazla işleyiciden sırayla geçmesi gerektiğinde (middleware pattern)

!!! danger "Dikkat"
    Zincir sonuna kadar hiçbir işleyici devreye girmezse istek yanıtsız kalır. Zincir sonunda default bir işleyici tanımlamak iyi pratiktir.

---

### Command

**Özü:** Bir eylemi nesne olarak kapsüller; sakla, kuyruğa al, geri al.

**Problem:** Bir işlem yapmak istiyorsun ama işlemi yapacak kodu hemen çalıştırmak istemiyorsun. Ya da aynı işlemi farklı bağlamlarda (menü tıklaması, tuş basımı, zamanlayıcı) tetiklemek istiyorsun. Ya da "geri al" (undo) özelliği gerekiyor.

**Analoji:** Restoran siparişi — garson siparişi kağıda yazar (komut), mutfağa verir, aşçı kağıdı okuyarak yemeği hazırlar. Garson pişirme detaylarını bilmez. Sipariş nesnesi: başlatan (garson), uygulayan (aşçı) ve işlem (yemek) arasındaki bağı koparır.

```mermaid
classDiagram
    class Command {
        <<interface>>
        +execute()
        +undo()
    }
    class LightOnCommand {
        -light Light
        +execute()
        +undo()
    }
    class Invoker {
        -history List~Command~
        +executeCommand(Command)
        +undoLast()
    }
    class Light {
        +on()
        +off()
    }
    Command <|.. LightOnCommand
    LightOnCommand --> Light
    Invoker --> Command
```

**Nasıl Çalışır:** Her işlem bir `Command` nesnesine dönüştürülür. `execute()` işlemi yapar, `undo()` geri alır. `Invoker` komutları kuyruğa alır ve çalıştırır. `Receiver` gerçek işi yapan nesnedir.

```cpp
// Command arayüzü
class Command {
public:
    virtual void execute() = 0;
    virtual void undo()    = 0;
    virtual ~Command() = default;
};

// Receiver — gerçek işi yapan nesne
class Light {
    bool on = false;
public:
    void turnOn()  { on = true;  std::cout << "Işık açıldı\n"; }
    void turnOff() { on = false; std::cout << "Işık kapatıldı\n"; }
};

// Concrete Command — execute/undo çiftini kapsüller
class LightOnCommand : public Command {
    Light& light;
public:
    LightOnCommand(Light& l) : light(l) {}
    void execute() override { light.turnOn(); }
    void undo()    override { light.turnOff(); }
};

class LightOffCommand : public Command {
    Light& light;
public:
    LightOffCommand(Light& l) : light(l) {}
    void execute() override { light.turnOff(); }
    void undo()    override { light.turnOn(); }
};

// Invoker — komutları çalıştırır ve geçmişi saklar
class RemoteControl {
    std::stack<Command*> history;
public:
    void press(Command* cmd) {
        cmd->execute();
        history.push(cmd);
    }

    void undoLast() {
        if (!history.empty()) {
            history.top()->undo();
            history.pop();
        }
    }
};

int main() {
    Light          light;
    LightOnCommand  onCmd(light);
    LightOffCommand offCmd(light);
    RemoteControl   remote;

    remote.press(&onCmd);   // Işık açıldı
    remote.press(&offCmd);  // Işık kapatıldı
    remote.undoLast();      // Işık açıldı  (undo: off->on)
    remote.undoLast();      // Işık kapatıldı (undo: on->off)
}
```

!!! example "Gerçek Senaryo"
    Metin editörü: her yazma, silme, formatlama işlemi bir Command nesnesidir. Ctrl+Z her seferinde son Command'ın `undo()`'sunu çağırır. İşlemler log'lanabilir, tekrar oynatılabilir (macro), hatta ağ üzerinden gönderilebilir.

!!! tip "Ne Zaman Kullanılır?"
    - Undo/redo gerektiğinde
    - İşlemleri log'lamak veya sıraya almak (queue) gerektiğinde
    - Aynı işlemi farklı tetikleyicilerden (buton, tuş kısayolu, menü) çağırmak istediğinde
    - İşlemi tetikleyen ile gerçekleştiren arasındaki bağımlılığı kesmek gerektiğinde

---

### Interpreter

**Özü:** Özel bir dili veya ifade gramerini sınıf hiyerarşisiyle temsil et ve yorumla.

**Problem:** Tekrarlayan, belirli kurallara sahip bir mini dil veya ifade sistemi oluşturman gerekiyor: SQL benzeri basit sorgular, kural motoru için koşul ifadeleri, matematiksel ifadeler gibi.

**Nasıl Çalışır:** Her gramer kuralı bir sınıf olur (`TerminalExpr`, `AndExpr`, `OrExpr`). İfade bir ağaca dönüştürülür ve `interpret()` her düğüm için recursive çağrılır.

```cpp
// Context — değişken değerlerini tutar
class Context {
    std::unordered_map<std::string, bool> vars;
public:
    void set(const std::string& name, bool value) { vars[name] = value; }
    bool get(const std::string& name) const { return vars.at(name); }
};

// Her gramer kuralı bir sınıf
class Expression {
public:
    virtual bool interpret(const Context& ctx) = 0;
    virtual ~Expression() = default;
};

// Terminal: yaprak düğüm — değişken değerine bakar
class VariableExpr : public Expression {
    std::string name;
public:
    VariableExpr(std::string n) : name(std::move(n)) {}
    bool interpret(const Context& ctx) override { return ctx.get(name); }
};

// Non-terminal: AND — her iki tarafı da değerlendirir
class AndExpr : public Expression {
    std::unique_ptr<Expression> left, right;
public:
    AndExpr(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}

    bool interpret(const Context& ctx) override {
        return left->interpret(ctx) && right->interpret(ctx);
    }
};

class OrExpr : public Expression {
    std::unique_ptr<Expression> left, right;
public:
    OrExpr(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}

    bool interpret(const Context& ctx) override {
        return left->interpret(ctx) || right->interpret(ctx);
    }
};

int main() {
    // "sicaklik AND nem" OR alarm
    auto expr = std::make_unique<OrExpr>(
        std::make_unique<AndExpr>(
            std::make_unique<VariableExpr>("sicaklik"),
            std::make_unique<VariableExpr>("nem")
        ),
        std::make_unique<VariableExpr>("alarm")
    );

    Context ctx;
    ctx.set("sicaklik", true);
    ctx.set("nem", false);
    ctx.set("alarm", true);

    std::cout << expr->interpret(ctx) << "\n"; // 1 (true — alarm aktif)
}
```

!!! example "Gerçek Senaryo"
    IoT sisteminde cihaz kuralları: `"sıcaklık > 80 AND nem < 30"` ifadesi parse edilir. `AndExpr` iki alt ifade tutar. Sistem bu ağacı yürüterek kuralı değerlendirir. Yeni kural tipi eklemek için yeni bir sınıf yazılır.

!!! tip "Ne Zaman Kullanılır?"
    - Basit, tekrarlayan bir gramer yapısı varsa
    - Kullanıcı tanımlı kurallar/ifadeler çalışma zamanında parse edilecekse
    - Gramer sık değişmeyecekse

!!! danger "Sınırlı Kullanım Alanı"
    Gramer karmaşıklaştıkça sınıf sayısı ve bakım maliyeti patlar. Gerçek dil işleme ihtiyacında ANTLR, yacc/bison gibi parser generator araçları kullanılmalı.

---

### Iterator

**Özü:** Koleksiyonun iç yapısını açığa çıkarmadan elemanları üzerinde dolaş.

**Problem:** Liste, ağaç, graf veya özel bir veri yapısı üzerinde dolaşmak istiyorsun. Her veri yapısı için farklı dolaşım kodu yazmak istemiyorsun. Üstelik aynı veri yapısı farklı sıralarda dolaşılabilmeli (önce derinlik, önce genişlik gibi).

**Analoji:** Netflix'te içerik listesi — ister grid görünümde ister liste görünümde gez. Görünüm değişse de "bir sonraki içerik" mantığı aynı. İç yapıyı bilmeden geziniyorsun.

**Nasıl Çalışır:** `Iterator` arayüzü `hasNext()` ve `next()` metodlarını tanımlar. Her koleksiyon kendi Iterator'ını döner. İstemci koleksiyonun yapısını bilmeden döngüyle dolaşır.

```cpp
// Özel koleksiyon — sadece tek sayıları tutan filtreli range
class OddRange {
    int from, to;
public:
    OddRange(int f, int t) : from(f), to(t) {}

    // C++ range-based for ile uyumlu olması için Iterator sınıfı
    class Iterator {
        int current;
    public:
        Iterator(int v) : current(v) {
            if (current % 2 == 0) ++current; // tek sayıya atla
        }

        int  operator*()  { return current; }
        Iterator& operator++() { current += 2; return *this; } // bir sonraki tek
        bool operator!=(const Iterator& o) { return current <= o.current; }
    };

    Iterator begin() { return Iterator(from); }
    Iterator end()   { return Iterator(to); }
};

int main() {
    OddRange range(1, 10);

    // İç yapı bilinmeden dolaşım
    for (int x : range) {
        std::cout << x << " "; // 1 3 5 7 9
    }
    std::cout << "\n";
}
```

!!! note "Modern Dillerde Standart Hale Geldi"
    Python'da `for x in obj` (dunder metodlar), C++'da range-based for ve STL iteratorlar, Java'da `Iterable/Iterator` — hepsi bu desenin dil seviyesindeki uygulamalarıdır. Günümüzde çoğu durumda language feature'ı kullanırsın; deseni sıfırdan yazmak nadirdir.

!!! tip "Ne Zaman Kullanılır?"
    - Özel veri yapısı oluşturup for-each ile kullanılabilmesini istediğinde
    - Aynı koleksiyon üzerinde farklı dolaşım sırası gerektiğinde
    - İstemcinin veri yapısının iç detaylarından bağımsız olmasını istediğinde

---

### Mediator

**Özü:** Nesnelerin birbirini doğrudan tanıması yerine iletişimi merkezi bir aracıya delege et.

**Problem:** Birden fazla nesne birbirleriyle iletişim kuruyor. Her nesne diğerlerini doğrudan tanıdığında bağımlılık ağı karmaşık bir örümcek ağına döner. Birini değiştirmek diğerlerini etkiler.

**Analoji:** Hava trafik kontrolü — uçaklar birbirleriyle doğrudan konuşmaz, tümü kontrol kulesiyle konuşur. 10 uçakla 10×9=90 doğrudan bağlantı yerine 10 bağlantı yeterlidir.

```mermaid
classDiagram
    class Mediator {
        <<interface>>
        +notify(sender, event)
    }
    class ConcreteMediator {
        -componentA ComponentA
        -componentB ComponentB
        +notify(sender, event)
    }
    class ComponentA {
        -mediator Mediator
        +doA()
    }
    class ComponentB {
        -mediator Mediator
        +doB()
    }
    Mediator <|.. ConcreteMediator
    ConcreteMediator --> ComponentA
    ConcreteMediator --> ComponentB
    ComponentA --> Mediator
    ComponentB --> Mediator
```

**Nasıl Çalışır:** Her bileşen sadece `Mediator`'ı tanır. Bir şey olduğunda `mediator.notify(this, "event")` çağırır. Mediator kimin ne zaman ne yapacağına karar verir ve ilgili bileşeni tetikler.

```cpp
class ChatRoom; // ileriye bildirim

class User {
    std::string name;
    ChatRoom*   room;
public:
    User(std::string n, ChatRoom* r) : name(std::move(n)), room(r) {}

    void send(const std::string& msg);

    void receive(const std::string& from, const std::string& msg) {
        std::cout << "[" << name << "] " << from << " dedi: " << msg << "\n";
    }

    const std::string& getName() const { return name; }
};

// Mediator — kullanıcılar birbirini doğrudan tanımaz
class ChatRoom {
    std::vector<User*> users;
public:
    void join(User* u) { users.push_back(u); }

    void broadcast(const std::string& msg, User* sender) {
        for (auto* u : users) {
            if (u != sender) {
                u->receive(sender->getName(), msg);
            }
        }
    }
};

void User::send(const std::string& msg) {
    std::cout << "[" << name << "] gönderdi: " << msg << "\n";
    room->broadcast(msg, this);
}

int main() {
    ChatRoom room;
    User ali("Ali", &room);
    User veli("Veli", &room);
    User ayse("Ayşe", &room);

    room.join(&ali);
    room.join(&veli);
    room.join(&ayse);

    ali.send("Merhaba!");
    // [Veli] Ali dedi: Merhaba!
    // [Ayşe] Ali dedi: Merhaba!
    // Yeni kullanıcı eklemek mevcut User sınıfını etkilemez
}
```

!!! example "Gerçek Senaryo"
    Chat uygulaması: kullanıcılar birbirini doğrudan bilmez. Mesajlaşma sunucusu (Mediator) mesajı alır, ilgili kullanıcılara iletir, grupları yönetir. Yeni bir kullanıcı eklenmesi diğer kullanıcıların kodunu etkilemez.

!!! tip "Ne Zaman Kullanılır?"
    - Çok sayıda nesne arasındaki bağımlılıklar spaghetti'ye dönüşüyorsa
    - Nesnelerin yeniden kullanılabilirliği bağımlılıklar yüzünden azalıyorsa
    - İletişim mantığını tek bir noktada toplamak istediğinde

!!! danger "Dikkat"
    Mediator kendisi "God Object"e dönüşebilir. Tüm mantık Mediator'a yığılırsa monolitik bir iletişim merkezi ortaya çıkar. Mediator'ın sorumluluklarını sınırlı tut.

---

### Memento

**Özü:** Nesnenin iç durumunu kapsüllemeyi bozmadan kaydet; gerektiğinde geri yükle.

**Problem:** Bir nesnenin önceki durumuna geri dönmek istiyorsun. Ama nesnenin iç durumu private — dışarıdan okuyamazsın. Durumu dışa aktarmak encapsulation'ı bozar.

**Analoji:** Video oyununda kaydetme noktası (checkpoint). Oyun motoruna iç mekanizmaları bilmeden "buraya kaydet" ve "buraya geri dön" diyebiliyorsun.

```mermaid
classDiagram
    class Originator {
        -state string
        +save() Memento
        +restore(Memento)
    }
    class Memento {
        -state string
        +getState() string
    }
    class Caretaker {
        -history List~Memento~
        +backup(Originator)
        +undo(Originator)
    }
    Originator --> Memento : oluşturur
    Caretaker --> Memento : saklar
    Caretaker --> Originator
```

**Nasıl Çalışır:**

- **Originator:** Durumu olan asıl nesne. `save()` ile kendi durumunun anlık görüntüsünü Memento olarak döner.
- **Memento:** Durumu saklayan opak nesne. Sadece Originator içini okuyabilir.
- **Caretaker:** Memento'ları saklar ama içini okuyamaz. Undo için Originator'a geri verir.

```cpp
// Memento — durumu saklayan opak nesne
class Memento {
    std::string content; // dışarıdan erişilemez
    friend class Editor; // yalnızca Editor okuyabilir
public:
    Memento(std::string c) : content(std::move(c)) {}
};

// Originator — asıl nesne
class Editor {
    std::string content;
public:
    void type(const std::string& text) { content += text; }

    Memento save() const {
        return Memento(content); // o anki durumun anlık görüntüsü
    }

    void restore(const Memento& m) {
        content = m.content; // friend erişimi — dışarıdan mümkün değil
    }

    void print() const { std::cout << "İçerik: \"" << content << "\"\n"; }
};

// Caretaker — Memento'ları saklar, içini okuyamaz
class History {
    std::stack<Memento> snapshots;
public:
    void backup(const Editor& editor) {
        snapshots.push(editor.save());
    }

    void undo(Editor& editor) {
        if (!snapshots.empty()) {
            editor.restore(snapshots.top());
            snapshots.pop();
        }
    }
};

int main() {
    Editor  editor;
    History history;

    history.backup(editor);    // snapshot: ""
    editor.type("Merhaba ");
    history.backup(editor);    // snapshot: "Merhaba "
    editor.type("Dünya");

    editor.print();            // İçerik: "Merhaba Dünya"
    history.undo(editor);
    editor.print();            // İçerik: "Merhaba "
    history.undo(editor);
    editor.print();            // İçerik: ""
}
```

!!! example "Gerçek Senaryo"
    Metin editörü Ctrl+Z: her değişiklik öncesi `editor.save()` çağrılır, dönen Memento geçmişe eklenir. Ctrl+Z'de son Memento alınır ve `editor.restore(memento)` çağrılır. Editörün içindeki karmaşık durumun tamamı kurtarılır.

!!! tip "Ne Zaman Kullanılır?"
    - Undo/redo gerektiğinde ve nesnenin iç durumu karmaşıksa
    - Nesnenin durumunun anlık görüntüsünü almak gerektiğinde
    - Encapsulation'ı bozmadan durum geçmişi yönetimi gerektiğinde

!!! tip "Command ile Farkı"
    Command undo için *işlemi tersine çeviren kod* yazar (davranış odaklı). Memento *önceki durumu saklar* (veri odaklı). Karmaşık durum geri almaları için Memento daha uygundur; çünkü ters işlemi yazmak bazen imkânsız veya çok karmaşıktır.

---

### Observer

**Özü:** Bir nesnedeki değişikliği ilgilenen herkese otomatik bildir.

**Problem:** Bir nesnenin durumu değiştiğinde buna bağlı diğer nesnelerin de güncellenmesi gerekiyor. Ama bu bağımlı nesneler dinamik olarak değişebilir ve hepsini tek tek çağırmak sıkı bağımlılık yaratır.

**Analoji:** Gazete aboneliği — gazete her yayınlandığında abone olan herkese otomatik gönderilir. Gazete kaç abonesi olduğunu veya ne yaptıklarını bilmez. İsteyen abone olur, isteyen aboneliği iptal eder.

```mermaid
classDiagram
    class Subject {
        -observers List~Observer~
        +subscribe(Observer)
        +unsubscribe(Observer)
        +notify()
    }
    class Observer {
        <<interface>>
        +update(data)
    }
    class Display {
        +update(data)
    }
    class Logger {
        +update(data)
    }
    class AlarmSystem {
        +update(data)
    }
    Subject --> Observer
    Observer <|.. Display
    Observer <|.. Logger
    Observer <|.. AlarmSystem
```

**Nasıl Çalışır:** `Subject` (yayıncı) Observer listesi tutar. Durum değişince `notify()` çağırır — tüm Observer'ların `update()` metodu tetiklenir. Observer'lar `subscribe()`/`unsubscribe()` ile listeye girip çıkabilir.

```cpp
class Observer {
public:
    virtual void update(float temperature) = 0;
    virtual ~Observer() = default;
};

// Subject (yayıncı) — Observer listesi tutar
class TemperatureSensor {
    float temperature = 0.0f;
    std::vector<Observer*> observers;
public:
    void subscribe(Observer* o)   { observers.push_back(o); }
    void unsubscribe(Observer* o) {
        observers.erase(std::remove(observers.begin(), observers.end(), o),
                        observers.end());
    }

    void setTemperature(float t) {
        temperature = t;
        notify(); // değişim tüm abonelere iletilir
    }

private:
    void notify() {
        for (auto* o : observers) o->update(temperature);
    }
};

// Bağımsız gözlemciler — birbirinden habersiz, yalnızca Subject'i bilir
class Display : public Observer {
public:
    void update(float temp) override {
        std::cout << "Ekran: " << temp << " C\n";
    }
};

class AlarmSystem : public Observer {
public:
    void update(float temp) override {
        if (temp > 80.0f)
            std::cout << "ALARM: Kritik sicaklik! " << temp << " C\n";
    }
};

int main() {
    TemperatureSensor sensor;
    Display      display;
    AlarmSystem  alarm;

    sensor.subscribe(&display);
    sensor.subscribe(&alarm);

    sensor.setTemperature(50.0f);
    // Ekran: 50 C

    sensor.setTemperature(90.0f);
    // Ekran: 90 C
    // ALARM: Kritik sicaklik! 90 C

    sensor.unsubscribe(&alarm);
    sensor.setTemperature(95.0f);
    // Ekran: 95 C  (alarm artık abone değil)
}
```

!!! example "Gerçek Senaryo"
    Sensör sistemi: sıcaklık sensörü her ölçüm yaptığında izleme ekranı, log kaydı ve alarm modülü otomatik haberdar olur. Yeni bir "SMS uyarısı" modülü eklemek istersen sadece Observer'a kaydettirirsin; sensör koduna dokunmazsın.

!!! tip "Ne Zaman Kullanılır?"
    - Bir nesnenin değişikliği belirsiz sayıda başka nesneyi tetikleyecekse
    - Yayıncı ile abonelerin gevşek bağlı (loose coupling) olması gerekiyorsa
    - Event-driven mimari, reaktif sistemler, GUI event handling

!!! note "Publish-Subscribe ile İlişki"
    Observer, publish-subscribe mimarisinin temel prensibidir. Modern sistemlerde (Kafka, RabbitMQ, Redux, event bus) bu desenin çeşitli varyasyonları uygulanır.

---

### State

**Özü:** Nesnenin davranışı iç durumuna göre değişir; durum geçişlerini if/else yerine ayrı nesnelerle yönet.

**Problem:** Bir nesnenin birden fazla durumu var ve her durumda aynı metodlar farklı davranıyor. Bunu if/else veya switch ile yönetmek hem uzar hem kırılganlaşır. Yeni durum eklenince mevcut kodun her yerine if eklenmesi gerekir.

**Analoji:** Trafik lambası — kırmızıda "dur", yeşilde "geç", sarıda "yavaşla". Aynı "ne yapmalıyım?" sorusunun cevabı lambanın durumuna göre tamamen değişir. Her durum kendi kurallarını bilir.

```mermaid
stateDiagram-v2
    [*] --> Idle : Sistem başlat
    Idle --> Moving : Hareket komutu
    Moving --> Idle : Dur komutu
    Moving --> Emergency : Tehlike algıla
    Idle --> Emergency : Tehlike algıla
    Emergency --> Idle : Tehlike geçti
```

**Nasıl Çalışır:** Her durum ayrı bir sınıf olur; tümü aynı `State` arayüzünü uygular. Context nesnesi mevcut durumuna referans tutar; metodları çağrıldığında mevcut State nesnesine delege eder. Durum geçişleri State sınıflarının içinde yönetilir.

```cpp
class UAV; // ileriye bildirim

// Her durum aynı arayüzü uygular
class State {
public:
    virtual void handle(UAV& uav, const std::string& cmd) = 0;
    virtual std::string name() const = 0;
    virtual ~State() = default;
};

class UAV {
    std::unique_ptr<State> state;
public:
    UAV();
    void setState(std::unique_ptr<State> s) {
        std::cout << "Durum: " << state->name()
                  << " -> " << s->name() << "\n";
        state = std::move(s);
    }
    void command(const std::string& cmd) { state->handle(*this, cmd); }
};

// Her durum kendi geçişlerinden sorumlu
class IdleState : public State {
public:
    void handle(UAV& uav, const std::string& cmd) override;
    std::string name() const override { return "Beklemede"; }
};

class MovingState : public State {
public:
    void handle(UAV& uav, const std::string& cmd) override;
    std::string name() const override { return "Hareket"; }
};

class EmergencyState : public State {
public:
    void handle(UAV& uav, const std::string& cmd) override;
    std::string name() const override { return "Acil Durum"; }
};

void IdleState::handle(UAV& uav, const std::string& cmd) {
    if      (cmd == "move")   uav.setState(std::make_unique<MovingState>());
    else if (cmd == "danger") uav.setState(std::make_unique<EmergencyState>());
    else std::cout << "Beklemede: '" << cmd << "' komutu geçersiz\n";
}

void MovingState::handle(UAV& uav, const std::string& cmd) {
    if      (cmd == "stop")   uav.setState(std::make_unique<IdleState>());
    else if (cmd == "danger") uav.setState(std::make_unique<EmergencyState>());
    else std::cout << "Hareket halinde: '" << cmd << "' komutu geçersiz\n";
}

void EmergencyState::handle(UAV& uav, const std::string& cmd) {
    if (cmd == "clear") uav.setState(std::make_unique<IdleState>());
    else std::cout << "Acil durumda: yalnızca 'clear' kabul edilir\n";
}

UAV::UAV() : state(std::make_unique<IdleState>()) {}

int main() {
    UAV uav;
    uav.command("move");    // Beklemede -> Hareket
    uav.command("danger");  // Hareket -> Acil Durum
    uav.command("move");    // Acil durumda: yalnızca 'clear' kabul edilir
    uav.command("clear");   // Acil Durum -> Beklemede
}
```

!!! example "Gerçek Senaryo"
    Otonom araç: `IdleState`, `MovingState`, `EmergencyState` ayrı sınıflar. "Engel algılandı" komutu verildiğinde Moving durumundaki araç Emergency'ye geçer. Her durum kendi tepkisini bilir. Yeni bir durum (`ParkingState`) eklemek mevcut durumları etkilemez.

!!! tip "Ne Zaman Kullanılır?"
    - Nesnenin davranışı durumuna göre köklü biçimde değişiyorsa
    - Çok sayıda if/else veya switch-case ile durum yönetiliyorsa
    - Durum sayısı artacaksa ve her durumun kendi karmaşık davranışı varsa
    - Durum geçişleri açıkça modellenmek isteniyorsa (state machine)

!!! tip "Strategy ile Farkı"
    Strategy'de istemci algoritmayı seçer ve genellikle değiştirmez. State'de nesne kendi durumunu ve geçişlerini yönetir; değişimler otomatik gerçekleşebilir. State nesneleri birbirini tanıyabilir; Strategy nesneleri genellikle birbirinden habersizdir.

---

### Strategy

**Özü:** Aynı işi yapan farklı algoritmalar arasında çalışma zamanında geçiş yap.

**Problem:** Bir işlemin birden fazla yapılış biçimi var ve hangisinin kullanılacağı değişebilir. Tüm algoritmaları tek bir sınıfa koymak hem şişirir hem de Open/Closed Principle'ı ihlal eder — yeni algoritma eklemek mevcut koda dokunmayı gerektirir.

**Analoji:** Navigasyon uygulaması — en kısa yol, en hızlı yol, en az yakıt harcayan yol. Algoritma farklı ama "rota bul" talebi aynı. Kullanıcı tercihine göre strateji değişir.

```mermaid
classDiagram
    class RouteContext {
        -strategy RouteStrategy
        +setStrategy(RouteStrategy)
        +findRoute(src, dst)
    }
    class RouteStrategy {
        <<interface>>
        +buildRoute(src, dst)
    }
    class ShortestRoute {
        +buildRoute(src, dst)
    }
    class FastestRoute {
        +buildRoute(src, dst)
    }
    class SafestRoute {
        +buildRoute(src, dst)
    }
    RouteContext --> RouteStrategy
    RouteStrategy <|.. ShortestRoute
    RouteStrategy <|.. FastestRoute
    RouteStrategy <|.. SafestRoute
```

**Nasıl Çalışır:** Her algoritma ayrı bir sınıfa (`ConcreteStrategy`) taşınır. Tümü aynı `Strategy` arayüzünü uygular. `Context` nesnesi algoritma detaylarını bilmez; çalışma zamanında `setStrategy()` ile strateji değiştirilebilir.

```cpp
// Strateji arayüzü — tüm rota algoritmaları bunu uygular
class RouteStrategy {
public:
    virtual void buildRoute(const std::string& src,
                             const std::string& dst) = 0;
    virtual ~RouteStrategy() = default;
};

class ShortestRoute : public RouteStrategy {
public:
    void buildRoute(const std::string& src,
                    const std::string& dst) override {
        std::cout << src << " -> " << dst << ": En kısa rota (Dijkstra)\n";
    }
};

class FastestRoute : public RouteStrategy {
public:
    void buildRoute(const std::string& src,
                    const std::string& dst) override {
        std::cout << src << " -> " << dst << ": En hızlı rota (A*)\n";
    }
};

class SafestRoute : public RouteStrategy {
public:
    void buildRoute(const std::string& src,
                    const std::string& dst) override {
        std::cout << src << " -> " << dst << ": En güvenli rota\n";
    }
};

// Context — strateji detaylarını bilmez, delege eder
class Navigator {
    std::unique_ptr<RouteStrategy> strategy;
public:
    void setStrategy(std::unique_ptr<RouteStrategy> s) {
        strategy = std::move(s);
    }

    void route(const std::string& src, const std::string& dst) {
        if (strategy) strategy->buildRoute(src, dst);
    }
};

int main() {
    Navigator nav;

    nav.setStrategy(std::make_unique<ShortestRoute>());
    nav.route("Ankara", "İstanbul");
    // Ankara -> İstanbul: En kısa rota (Dijkstra)

    nav.setStrategy(std::make_unique<FastestRoute>());
    nav.route("Ankara", "İstanbul");
    // Ankara -> İstanbul: En hızlı rota (A*)
    // Context kodu değişmedi — sadece strateji değişti
}
```

!!! example "Gerçek Senaryo"
    Sıralama sistemi: küçük veri için insertion sort, büyük veri için quicksort, neredeyse sıralı veri için merge sort tercih edilir. Context veri boyutuna göre strateji seçer. Yeni algoritma eklemek için sadece yeni bir Strategy sınıfı yazılır; Context'e dokunulmaz.

!!! tip "Ne Zaman Kullanılır?"
    - Aynı işi yapan birden fazla algoritma varsa ve aralarında çalışma zamanında geçiş gerekiyorsa
    - Algoritma detaylarını istemciden gizlemek istediğinde
    - Koşullu algoritmik dallanma (if/else zinciri) kodu karmaşıklaştırıyorsa

---

### Template Method

**Özü:** Algoritmanın iskeletini üst sınıfa yaz; değişen adımları alt sınıflara bırak.

**Problem:** Birden fazla sınıf aynı genel akışı paylaşıyor ama bazı adımlarda farklı davranıyor. Ortak akışı kopyala-yapıştırla her sınıfa yazmak kod tekrarına yol açar ve bakımı zorlaştırır.

**Analoji:** Franchise restoranı — tüm şubeler aynı müşteri hizmet protokolünü uygular (karşıla, siparişi al, hazırla, sun, ödeme al). Ama hazırlama adımı her ürün için farklıdır. Protokol sabittir; hazırlama detayı değişkendir.

**Nasıl Çalışır:** Üst sınıf `process()` tanımlar — genel akışı sabit sırayla çağırır. Değişmez adımlar üst sınıfta uygulanır. Değişen adımlar `virtual` (override edilebilir) metodlar olarak tanımlanır. Alt sınıflar sadece bu adımları override eder; genel akışa dokunamaz.

```cpp
// Üst sınıf — algoritma iskeleti burada, değişen adımlar abstract
class DataProcessor {
public:
    // Template method — akışı sabitler; alt sınıflar override edemez
    void process() {
        readData();
        validate();   // sabit adım
        transform();
        report();     // sabit adım
    }

    virtual ~DataProcessor() = default;

protected:
    virtual void readData()  = 0; // alt sınıf dolduracak
    virtual void transform() = 0; // alt sınıf dolduracak

    void validate() { std::cout << "Veri dogrulanıyor\n"; }
    void report()   { std::cout << "Rapor olusturuldu\n\n"; }
};

// Sadece değişen adımları override eder — akışa dokunmaz
class CSVProcessor : public DataProcessor {
protected:
    void readData()  override { std::cout << "CSV dosyası okunuyor\n"; }
    void transform() override { std::cout << "CSV ayrıstırılıyor\n"; }
};

class XMLProcessor : public DataProcessor {
protected:
    void readData()  override { std::cout << "XML dosyası okunuyor\n"; }
    void transform() override { std::cout << "XML parse ediliyor\n"; }
};

int main() {
    CSVProcessor csv;
    csv.process();
    // CSV dosyası okunuyor
    // Veri dogrulanıyor
    // CSV ayrıstırılıyor
    // Rapor olusturuldu

    XMLProcessor xml;
    xml.process();
    // XML dosyası okunuyor
    // Veri dogrulanıyor
    // XML parse ediliyor
    // Rapor olusturuldu
}
```

!!! example "Gerçek Senaryo"
    Veri işleme pipeline'ı: her kaynak için sıra aynı — oku, doğrula, işle, raporla. `CSVProcessor` okuma ve işleme adımlarını CSV mantığıyla uygular. `XMLProcessor` aynı adımları XML için uygular. Doğrulama ve raporlama üst sınıftan kalıtılır ve değişmez.

!!! tip "Ne Zaman Kullanılır?"
    - Birden fazla sınıfın aynı algoritmik iskelet üzerinde çalıştığı ama belirli adımların farklılaştığı durumlarda
    - Kod tekrarını ortadan kaldırmak için ortak akış üst sınıfa çekilmek istendiğinde
    - Alt sınıfların tüm algoritmayı değiştirmesini engellemek ama özelleştirmesine izin vermek gerektiğinde

!!! note "Hollywood Prensibi"
    "Bizi arama, biz seni ararız" — Alt sınıf adımları uygular ama akışın ne zaman ve hangi sırayla çalışacağını üst sınıf yönetir. Kontrolün ters çevrilmesidir.

!!! tip "Strategy ile Farkı"
    Template Method kalıtım kullanır; algoritmanın iskeletini değiştirmeyi engeller. Strategy bileşim (composition) kullanır; tüm algoritmayı çalışma zamanında değiştirebilir.

---

### Visitor

**Özü:** Kararlı nesne yapısına, nesneleri değiştirmeden yeni operasyonlar ekle.

**Problem:** Birçok farklı nesne türünden oluşan bir yapı var (AST, belge, nesne grafiği). Bu yapı üzerinde sık sık yeni operasyonlar eklenmesi gerekiyor (analiz, optimizasyon, yazdırma, serileştirme). Her yeni operasyon için her nesne sınıfına dokunmak Open/Closed Principle'ı ihlal eder.

**Analoji:** Vergi denetçisi — şehirdeki her farklı iş yeri türünü (restoran, mağaza, fabrika) ziyaret eder. Her yerin kendine özgü vergi hesaplama kuralları var. Denetçi yeni bir hesaplama metodu getirdiğinde iş yerlerine dokunmaz; sadece yeni bir denetçi (Visitor) oluşturulur.

```mermaid
classDiagram
    class Visitor {
        <<interface>>
        +visitLiteral(LiteralNode)
        +visitBinaryOp(BinaryOpNode)
    }
    class PrintVisitor {
        +visitLiteral(LiteralNode)
        +visitBinaryOp(BinaryOpNode)
    }
    class EvalVisitor {
        +visitLiteral(LiteralNode)
        +visitBinaryOp(BinaryOpNode)
    }
    class Node {
        <<interface>>
        +accept(Visitor)
    }
    class LiteralNode {
        +accept(Visitor)
    }
    class BinaryOpNode {
        +accept(Visitor)
    }
    Visitor <|.. PrintVisitor
    Visitor <|.. EvalVisitor
    Node <|.. LiteralNode
    Node <|.. BinaryOpNode
    Node --> Visitor
```

**Nasıl Çalışır:** Her nesne türü `accept(Visitor& v)` metodunu uygular ve `v.visit(*this)` çağırır (double dispatch). Yeni operasyon eklemek = yeni bir Visitor sınıfı yazmak. Var olan nesnelere dokunulmaz.

```cpp
// İleriye bildirimler
class LiteralNode;
class BinaryOpNode;

// Visitor arayüzü — her node türü için ayrı metod
class Visitor {
public:
    virtual void visitLiteral(LiteralNode& node) = 0;
    virtual void visitBinaryOp(BinaryOpNode& node) = 0;
    virtual ~Visitor() = default;
};

// AST node arayüzü — kararlı yapı; sık değişmez
class Node {
public:
    virtual void accept(Visitor& v) = 0;
    virtual ~Node() = default;
};

class LiteralNode : public Node {
public:
    int value;
    LiteralNode(int v) : value(v) {}
    void accept(Visitor& v) override { v.visitLiteral(*this); }
};

class BinaryOpNode : public Node {
public:
    char op;
    std::unique_ptr<Node> left, right;
    BinaryOpNode(char o, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
        : op(o), left(std::move(l)), right(std::move(r)) {}
    void accept(Visitor& v) override { v.visitBinaryOp(*this); }
};

// Operasyon 1: ağacı yazdır — node sınıflarına dokunmadan yeni özellik
class PrintVisitor : public Visitor {
public:
    void visitLiteral(LiteralNode& node) override {
        std::cout << node.value;
    }
    void visitBinaryOp(BinaryOpNode& node) override {
        std::cout << "(";
        node.left->accept(*this);
        std::cout << " " << node.op << " ";
        node.right->accept(*this);
        std::cout << ")";
    }
};

// Operasyon 2: hesapla — node sınıflarına dokunmadan yeni özellik
class EvalVisitor : public Visitor {
public:
    int result = 0;
    void visitLiteral(LiteralNode& node) override { result = node.value; }
    void visitBinaryOp(BinaryOpNode& node) override {
        EvalVisitor lv, rv;
        node.left->accept(lv);
        node.right->accept(rv);
        if      (node.op == '+') result = lv.result + rv.result;
        else if (node.op == '*') result = lv.result * rv.result;
    }
};

int main() {
    // (3 + 4) * 2
    auto tree = std::make_unique<BinaryOpNode>('*',
        std::make_unique<BinaryOpNode>('+',
            std::make_unique<LiteralNode>(3),
            std::make_unique<LiteralNode>(4)
        ),
        std::make_unique<LiteralNode>(2)
    );

    PrintVisitor printer;
    tree->accept(printer);       // ((3 + 4) * 2)
    std::cout << "\n";

    EvalVisitor evaluator;
    tree->accept(evaluator);
    std::cout << evaluator.result << "\n"; // 14
}
```

!!! example "Gerçek Senaryo"
    Derleyici: AST (Abstract Syntax Tree) üzerinde tip kontrolü, optimizasyon, kod üretimi, hata raporlama gibi farklı geçişler yapılır. Her geçiş ayrı bir Visitor'dır. AST node sınıfları değişmez; yeni analiz eklemek yeni Visitor yazmak demektir.

!!! tip "Ne Zaman Kullanılır?"
    - Nesne yapısı kararlı (sık değişmiyor) ama üzerindeki operasyonlar sık ekleniyor/değişiyorsa
    - Birçok farklı türde nesne üzerinde aynı gruptan işlemler yapılacaksa
    - Nesne sınıflarına davranış eklemek yerine ayrı operasyon sınıfları isteniyorsa

!!! danger "Ne Zaman Kullanılmaz"
    Yeni eleman türü eklendiğinde tüm Visitor implementasyonları güncellenmek zorundadır. Eğer nesne yapısı (element türleri) sık değişiyorsa Visitor uygun değildir — her değişiklik tüm Visitor'lara yayılır.
