# Design Pattern

## Creational

1. **Factory Method** 
    - Nesne oluşturma sorumluluğunu doğrudan client kodundan alarak, bu sorumluluğu bir fabrika metoduna devreden bir tasarım desenidir. Temel amaç, sistemin hangi somut sınıfı üreteceğine dair bilgisinin merkezi bir noktada toplanması ve üst seviye bileşenlerin alt seviye detaylara bağımlılığının azaltılmasıdır. Bu yaklaşım sayesinde sistem; genişletilmeye açık, değişikliğe kapalı (Open/Closed Principle) bir mimari kazanır. Yeni bir nesne türü eklendiğinde, mevcut istemci kodunda değişiklik yapılmasına gerek kalmaz.
    - **Kavramsal Örnek** Bir lojistik sisteminde kara, deniz ve hava taşımacılığı yapılmaktadır. Sipariş yönetim sistemi yalnızca “taşıma” işlemini bilir; ancak taşımanın kamyon, gemi ya da uçak ile yapılacağını bilmez.
    Factory Method, siparişin türüne veya konfigürasyona göre doğru taşıma nesnesinin üretilmesini sağlar. Sipariş sistemi yalnızca “taşıma başlat” talebinde bulunur, hangi aracın kullanıldığı detayından tamamen soyutlanır.

2. **Abstract Factory**
    - Birbiriyle ilişkili veya birlikte çalışması gereken nesnelerin, somut sınıfları belirtilmeden bir “ürün ailesi” halinde oluşturulmasını sağlayan bir tasarım desenidir. Bu desen, özellikle platform bağımlı veya varyantlı sistemlerde tutarlılığı korumak için kullanılır. Aynı ürün ailesine ait nesnelerin birbiriyle uyumlu olmasını garanti altına alır ve istemci tarafında yanlış kombinasyonların oluşmasını engeller.
    - **Kavramsal Örnek** Bir kullanıcı arayüzü kütüphanesinin hem masaüstü hem de gömülü sistemler için çalıştığını düşünelim. Masaüstü ortamında buton, menü ve pencere bileşenleri farklı; gömülü sistemde ise daha sade ve hafif bileşenler gereklidir. Abstract Factory, “masaüstü arayüz ailesi” veya “gömülü arayüz ailesi” seçildiğinde, bu aileye ait tüm bileşenlerin birlikte ve uyumlu şekilde üretilmesini sağlar. Böylece farklı platformlara ait bileşenlerin yanlışlıkla birlikte kullanılması önlenir.
3. **Builder**
    - Karmaşık nesnelerin oluşturulma sürecini, nesnenin son temsilinden ayıran bir tasarım desenidir. Özellikle çok sayıda opsiyonel alanı bulunan veya farklı konfigürasyonlarla üretilebilen nesneler için kullanılır. Bu desen, nesne oluşturma sürecini adımlara böler ve her adımın kontrollü bir şekilde ilerlemesini sağlar. Aynı oluşturma süreci kullanılarak farklı varyantlarda nesneler üretilebilir.
    - **Kavramsal Örnek** Bir insansız hava aracı (İHA) konfigürasyon sürecini ele alalım. Aynı temel platform üzerinde farklı sensörler, haberleşme modülleri ve güç sistemleri seçilebilir. Builder yaklaşımı ile önce gövde, ardından sensörler, daha sonra haberleşme ve en son yazılım bileşenleri eklenir. Aynı adımlar kullanılarak keşif amaçlı veya lojistik amaçlı farklı İHA konfigürasyonları oluşturulabilir. Oluşturma süreci standart kalırken, ortaya çıkan ürün değişir.

4. **Prototype**
    - Yeni nesnelerin sıfırdan oluşturulması yerine, mevcut bir nesnenin kopyalanması (klonlanması) yoluyla üretilmesini sağlayan bir tasarım desenidir. Bu desen, nesne oluşturma maliyetinin yüksek olduğu veya nesnenin karmaşık bir başlangıç konfigürasyonuna sahip olduğu durumlarda tercih edilir. Sistem, referans alınacak bir prototip nesne üzerinden hızlı ve tutarlı üretim yapar.
    - **Kavramsal Örnek** Simülasyon ortamında kullanılan bir sensör modelinin çok sayıda kopyasına ihtiyaç duyulduğunu varsayalım. Her sensör aynı temel özelliklere sahiptir ancak küçük parametre farkları bulunur. Prototype kullanılarak, önceden yapılandırılmış bir sensör modeli klonlanır ve yalnızca gerekli parametreler değiştirilir. Böylece hem zaman kazanılır hem de tutarlı bir yapı korunur.

5. **Singleton**
    - Bir sınıftan sistem genelinde yalnızca tek bir örnek oluşturulmasını garanti altına alan bir tasarım desenidir. Ayrıca bu örneğe kontrollü ve merkezi bir erişim noktası sağlar. Bu desen, paylaşılan kaynakların yönetimi, global konfigürasyonlar veya sistem çapında tekil olması gereken servisler için kullanılır. Yanlış veya aşırı kullanımı mimari bağımlılıkları artırabileceğinden dikkatli uygulanmalıdır.
    - **Kavramsal Örnek** Bir sistemde merkezi bir konfigürasyon yöneticisi olduğunu düşünelim. Tüm modüller sistem ayarlarını buradan okumaktadır. Eğer bu yapıdan birden fazla örnek oluşturulursa, ayarların tutarsızlaşması ve beklenmeyen davranışlar ortaya çıkabilir. Singleton sayesinde sistem genelinde tek bir konfigürasyon yöneticisi bulunur ve tüm bileşenler aynı kaynağı kullanır.

## Structural
1. **Adapter**
    - Birbiriyle uyumsuz arayüzlere sahip bileşenlerin birlikte çalışmasını sağlayan bir yapısal tasarım desenidir. Mevcut bir sınıfın arayüzünü, istemcinin beklediği arayüze dönüştürerek sistem içinde yeniden kullanılabilir hâle getirir. Bu desen, özellikle üçüncü parti kütüphaneler, legacy sistemler veya değiştirilemeyen bileşenlerle entegrasyon süreçlerinde tercih edilir. Temel hedef, mevcut kodu değiştirmeden uyumluluk sağlamaktır.
    - **Kavramsal Örnek**  Bir sistemin standart veri formatı JSON iken, entegre edilmesi gereken harici bir servis XML formatında veri üretmektedir. Adapter, XML veriyi alıp sistemin beklediği JSON yapısına dönüştürerek, üst seviye bileşenlerin bu farklılıktan etkilenmeden çalışmasını sağlar.
2. **Bridge**
    - Soyutlama (abstraction) ile implementasyonu birbirinden ayırarak, her ikisinin de bağımsız olarak geliştirilmesini sağlayan bir tasarım desenidir. Bu yaklaşım, sınıf hiyerarşisinin kontrolsüz büyümesini engeller ve “çok boyutlu değişkenlik” içeren sistemlerde esnekliği artırır.
    - **Kavramsal Örnek** Bir görüntü işleme sistemi düşünelim. Sistem hem farklı görüntü kaynaklarını (kamera, dosya, ağ) hem de farklı işleme yöntemlerini (filtreleme, sıkıştırma, analiz) desteklemektedir. Bridge kullanıldığında, görüntü kaynağı ile işleme algoritması birbirinden ayrılır. Yeni bir kamera türü eklendiğinde mevcut işleme yöntemleri etkilenmez; yeni bir algoritma eklendiğinde ise kaynaklar değişmeden kullanılabilir.
3. **Composite**
    - Nesneleri tree yapısı içerisinde organize ederek, tekil nesneler ile nesne gruplarının aynı arayüz üzerinden yönetilmesini sağlar. Bu desen, hiyerarşik yapılarda istemcinin tekil mi yoksa bileşik bir yapı ile mi çalıştığını bilmesine gerek kalmadan işlem yapabilmesini hedefler.
    - **Kavramsal Örnek** Bir dosya sistemi yapısını ele alalım. Dosyalar tekil nesneler, klasörler ise dosya ve alt klasörlerden oluşan bileşik yapılardır. Composite sayesinde bir dosya üzerinde yapılan “boyut hesaplama” işlemi, klasör üzerinde de aynı şekilde çağrılabilir ve tüm alt elemanların toplam boyutu otomatik olarak hesaplanır.
4. **Decorator**
    - Bir nesneye çalışma zamanında yeni davranışlar eklenmesini sağlayan bir tasarım desenidir. Kalıtım (inheritance) kullanmadan, nesnenin sorumluluklarını genişletmeye olanak tanır. Bu yaklaşım, sınıf sayısının kontrolsüz artmasını önler ve daha esnek bir genişletme mekanizması sunar.
    - **Kavramsal Örnek** Bir haberleşme modülünde temel veri gönderimi yapılmaktadır. Bazı senaryolarda şifreleme, bazılarında ise sıkıştırma gerekmektedir. Decorator ile temel gönderim yapısı korunur; ihtiyaç duyulduğunda şifreleme veya sıkıştırma katmanları eklenerek davranış genişletilir. Bu katmanlar isteğe bağlı olarak kombine edilebilir.
5. **Facade**
    - Karmaşık bir alt sistemin önüne basitleştirilmiş ve tek bir giriş noktası koyarak, istemcinin bu alt sistemle olan etkileşimini kolaylaştıran bir tasarım desenidir. Amaç, istemcinin sistem içindeki detaylı bağımlılıkları bilmesini engellemek ve kullanım kolaylığı sağlamaktır.
    - **Kavramsal Örnek** Bir multimedya sisteminde ses, video, ağ ve donanım sürücüleri ayrı ayrı çalışmaktadır. Facade, “medya oynat” gibi tek bir operasyon sunarak, istemcinin bu alt sistemlerin başlatılması, senkronizasyonu ve kapatılması gibi detaylarla uğraşmasını engeller.
6. **Flyweight**
    - Çok sayıda benzer nesnenin bulunduğu sistemlerde bellek kullanımını optimize etmek amacıyla kullanılan bir tasarım desenidir. Bu desen, nesnelerin ortak (intrinsic) durumlarını paylaşarak, her nesne için tekrar tekrar aynı verinin tutulmasını önler.
    - **Kavramsal Örnek** Bir harita uygulamasında binlerce ağaç nesnesi olduğunu düşünelim. Ağaçların türü, rengi ve modeli aynıdır; yalnızca konumları farklıdır. Flyweight yaklaşımı ile ağaç model bilgisi tek bir yerde tutulur, her ağaç için yalnızca konum bilgisi ayrı olarak saklanır. Böylece bellek tüketimi ciddi ölçüde azaltılır.
7. **Proxy**
    - Başka bir nesneye erişimi kontrol eden veya bu erişimi yöneten bir ara katman nesnesidir. Bu desen; erişim kontrolü, gecikmeli başlatma (lazy initialization), önbellekleme veya güvenlik gibi gereksinimlerin karşılanması için kullanılır.
    - **Kavramsal Örnek** Uzak bir sunucudan büyük boyutlu veriler çeken bir sistem düşünelim. Her erişimde doğrudan sunucuya gitmek maliyetlidir. Proxy, ilk istekte veriyi sunucudan alır ve önbelleğe koyar. Sonraki taleplerde aynı veri doğrudan proxy üzerinden sunularak performans artırılır ve sistem yükü azaltılır.


## Behavioral
1. **Chain of Responsibility**
    - Bir isteğin birden fazla nesne tarafından ele alınabileceği durumlarda, isteği gönderen taraf ile isteği işleyen taraflar arasındaki sıkı bağımlılığı ortadan kaldıran bir tasarım desenidir. İstek, zincir (chain) hâlinde sıralanmış işleyiciler boyunca iletilir ve uygun olan işleyici tarafından karşılanır. İsteğin hangi nesne tarafından işleneceği istemci tarafından bilinmez ve bilinmesi de gerekmez. 
    - **Kavramsal Örnek** Bir teknik destek sisteminde talepler; seviye 1, seviye 2 ve seviye 3 destek ekipleri tarafından ele alınmaktadır. Basit bir sorun ilk seviyede çözülürken, daha karmaşık talepler otomatik olarak bir üst seviyeye aktarılır. Talep sahibi, isteğin hangi ekip tarafından çözüldüğünü bilmeden süreci başlatır.
2. **Command**
    - Bir isteği nesne olarak kapsülleyerek; isteğin parametreleriyle birlikte saklanmasını, kuyruklanmasını veya geri alınmasını (undo) mümkün kılan bir tasarım desenidir. Bu desen, isteği başlatan nesne ile isteği yerine getiren nesne arasındaki bağımlılığı minimize eder ve işlemlerin daha esnek yönetilmesini sağlar.
    - **Kavramsal Örnek** Bir uzaktan kumanda sisteminde farklı cihazlar (ışık, klima, perde) kontrol edilmektedir. Her buton, belirli bir işlemi temsil eden bir komut nesnesine bağlıdır. Butona basıldığında kumanda, hangi cihazın nasıl çalıştığını bilmeden yalnızca ilgili komutu tetikler.
3. **Iterator**
    - Belirli bir dilin veya ifade yapısının kurallarını tanımlayarak, bu ifadelerin yorumlanmasını sağlayan bir tasarım desenidir. Genellikle basit ve sık tekrarlanan kurallara sahip mini dillerde veya yapılandırılabilir ifade sistemlerinde kullanılır.
    - **Kavramsal Örnek** Bir konfigürasyon dosyasında “AND”, “OR”, “NOT” gibi mantıksal ifadelerle kurallar tanımlandığını düşünelim. Interpreter, bu ifadeleri parse eder ve sistemin davranışını bu kurallara göre dinamik olarak belirler.
4. **Mediator**
    - Bir koleksiyonun iç yapısını açığa çıkarmadan, elemanları üzerinde sıralı bir şekilde gezinilmesini sağlayan bir tasarım desenidir. Bu desen, farklı veri yapılarının aynı erişim mantığıyla kullanılmasına imkân tanır.
    - **Kavramsal Örnek** Bir sistemde liste, ağaç ve grafik yapılarında tutulan veriler bulunmaktadır. Iterator sayesinde istemci, bu veri yapılarını nasıl saklandıklarını bilmeden, elemanlar üzerinde tek tip bir dolaşım mantığıyla işlem yapabilir.
5. **Memento**
    - Birden fazla nesne arasındaki doğrudan iletişimi ortadan kaldırarak, bu iletişimi merkezi bir aracı nesne üzerinden yöneten bir tasarım desenidir. Bu yaklaşım, nesneler arası bağımlılıkları azaltır ve sistemin daha okunabilir ve yönetilebilir olmasını sağlar.
    - **Kavramsal Örnek** Bir hava trafik kontrol sisteminde uçaklar birbirleriyle doğrudan iletişim kurmaz. Tüm koordinasyon, merkezi bir kontrol kulesi üzerinden sağlanır. Mediator, uçaklar arasındaki etkileşimi düzenleyerek karmaşıklığı tek noktada toplar.
6. **Observer**
    - Bir nesnede meydana gelen durum değişikliklerinin, bu nesneye bağımlı diğer nesnelere otomatik olarak bildirilmesini sağlayan bir tasarım desenidir. Bu desen, olay tabanlı (event-driven) mimarilerin temel yapı taşlarından biridir.
    - **Kavramsal Örnek** Bir sensör verisi güncellendiğinde; izleme ekranı, kayıt sistemi ve alarm modülü bu değişiklikten eş zamanlı olarak haberdar edilir. Sensör, bu bileşenleri doğrudan çağırmaz; yalnızca durumu değiştiğini bildirir.
7. **State**
    - Bir nesnenin iç durumuna bağlı olarak davranışını değiştirmesini sağlayan bir tasarım desenidir. Bu yaklaşım, çok sayıda koşul ifadesi (if/else, switch) kullanımını ortadan kaldırarak, duruma özel davranışları ayrı yapılar hâline getirir.
    - **Kavramsal Örnek** Bir otonom aracın “beklemede”, “hareket hâlinde” ve “acil durum” gibi farklı çalışma modları vardır. Araç, mevcut durumuna göre farklı tepkiler verir. State kullanıldığında, her mod kendi davranış kurallarını içerir.
8. **Strategy**
    - Aynı işi yapan ancak farklı algoritmalara sahip davranışların, çalışma zamanında değiştirilebilir olmasını sağlayan bir tasarım desenidir. Bu desen, algoritma ailesini kapsüller ve istemcinin algoritma detaylarından bağımsız çalışmasını sağlar.
    - **Kavramsal Örnek** Bir rota planlama sisteminde; en kısa yol, en hızlı yol veya en güvenli yol seçenekleri bulunmaktadır. Kullanıcı tercihine göre uygun strateji seçilir ve sistem bu stratejiye göre rota üretir.
9. **Template Method**
    - Bir algoritmanın iskeletini tanımlar ve bazı adımlarının alt sınıflar tarafından özelleştirilmesine izin verir. Algoritmanın genel akışı sabit kalırken, değişken adımlar kontrollü şekilde esnetilir.
    - **Kavramsal Örnek** Bir veri işleme sürecinde; veri okuma, doğrulama, işleme ve raporlama adımları her zaman aynıdır. Ancak doğrulama veya raporlama yöntemi projeye göre değişebilir. Template Method, bu değişken adımların özelleştirilmesini sağlar.
10. **Visitor**
    - Bir nesne yapısı üzerinde çalışacak yeni operasyonların, nesnelerin kendisini değiştirmeden eklenmesini sağlayan bir tasarım desenidir. Bu desen, özellikle kararlı (stabil) nesne yapıları üzerinde sık sık yeni işlemler eklenmesi gereken durumlarda tercih edilir.
    - **Kavramsal Örnek** Bir soyut sözdizimi ağacı (AST) üzerinde; analiz, optimizasyon ve raporlama gibi farklı işlemler yapılmaktadır. Visitor sayesinde bu işlemler, ağacın yapısı değiştirilmeden sisteme eklenebilir.
