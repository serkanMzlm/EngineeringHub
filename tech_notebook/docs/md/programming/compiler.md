# Compiler

!!! note "Genel Bakış"
    C/C++ kaynak kodu çalıştırılabilir bir programa dönüştürülürken dört aşamadan geçer: **Preprocessor → Compiler → Assembler → Linker**.

```mermaid
graph LR
    A["main.c / main.cpp\nKaynak Kod"] -->|Preprocessor| B["main.i\nGenişletilmiş Kod"]
    B -->|Compiler| C["main.s\nAssembly"]
    C -->|Assembler| D["main.o\nObject File"]
    D -->|Linker| E["main\nExecutable"]

    style A fill:#4CAF50,color:#fff
    style E fill:#F44336,color:#fff
```

---

## Derleme Aşamaları

| # | Aşama | Girdi | Çıktı | Açıklama |
|---|-------|-------|-------|---------|
| 1 | **Preprocessing** | `.c` / `.cpp` | `.i` | Macro ifadeleri çözümlenir, `#include` dosyaları gömülür, yorum satırları temizlenir |
| 2 | **Compilation** | `.i` | `.s` | Temizlenen kod, hedef mimarinin assembly diline çevrilir |
| 3 | **Assembly** | `.s` | `.o` | Assembly kodu makine diline (binary) dönüştürülerek object file oluşturulur |
| 4 | **Linking** | `.o` + kütüphaneler | executable | Object file'lar ve kütüphaneler birleştirilerek nihai çalıştırılabilir dosya üretilir |

!!! example "Adım Adım Derleme"
    ```bash
    gcc -E main.c -o main.i         # 1. Preprocessing  → .i
    gcc -S main.i -o main.s         # 2. Compilation    → .s (assembly)
    gcc -c main.s -o main.o         # 3. Assembly       → .o (object)
    gcc main.o -o main              # 4. Linking        → executable

    gcc -save-temps main.c -o main  # Tek komut, tüm ara dosyalar saklanır
    ```

---

## GCC / G++ Parametreleri

!!! tip "Temel Öneri"
    Geliştirme ortamında `-Wall -Wextra` kombinasyonu minimum standart olarak benimsenmelidir. Production derlemelerinde `-Werror` eklenerek uyarılar hata olarak ele alınır.

| Parametre | Açıklama |
|-----------|---------|
| `-Wall` | Temel warning mesajlarını aktif eder |
| `-Wextra` | Standart uyarıların ötesinde daha hassas uyarıları gösterir |
| `-Wconversion` | Veri kaybına yol açabilecek type conversion işlemlerini uyarır |
| `-Wsign-conversion` | Signed/unsigned dönüşümlerindeki riskleri bildirir |
| `-Werror` | Tüm uyarıları hata olarak ele alır; uyarı varsa derleme durur |
| `-std=c++17` | Kaynak kodun belirtilen C++ standardına göre derleneceğini belirtir |
| `-I<dizin>` | Header dosyalarının aranacağı ek dizini (include path) ekler |
| `-O<n>` | Optimizasyon seviyesini ayarlar (`0`: yok, `1-3`: artan, `s`: boyut) |
| `-g` | Debug bilgisi ekler; GDB gibi araçlarla kullanım için gereklidir |
| `-o <dosya>` | Çıktı dosyasının adını belirtir |
| `-c` | Yalnızca object file üretir; link aşamasını atlar |
| `-E` | Yalnızca preprocessor çıktısı üretir |
| `-S` | Yalnızca assembly çıktısı üretir |

!!! example "Kullanım Örnekleri"
    ```bash
    gcc  -o output main.c   -Wall -Wextra -Wconversion -Wsign-conversion
    g++  -o output main.cpp -std=c++17 -Wall -Wextra -Werror -O2
    g++  -o output main.cpp -std=c++11 -I./include -I/usr/local/include
    g++  -o output main.cpp -g -O0     # Debug derlemesi (optimizasyon kapalı)
    ```

!!! note "VS Code Derleyici Ayarları"
    ```json title="tasks.json"
    {
        "version": "2.0.0",
        "tasks": [
            {
                "label": "C++ Build",
                "type": "shell",
                "command": "g++",
                "args": [
                    "-std=c++20", "-Wall", "-Wextra",
                    "-Wconversion", "-Wsign-conversion",
                    "-Werror", "-o", "main", "main.cpp"
                ],
                "group": { "kind": "build", "isDefault": true }
            }
        ]
    }
    ```

---

## Kconfig ve Menuconfig

**Kconfig** ve **Menuconfig**, özellikle Linux kernel ve gömülü sistem projelerinde derleme öncesi konfigürasyon yönetimini sağlayan araçlardır.

!!! tip "Katman Ayrımı"
    - **Kconfig:** Projedeki özelliklerin, bağımlılıkların ve varsayılan değerlerin tanımlandığı metin tabanlı konfigürasyon dosyasıdır.
    - **Menuconfig:** Kconfig dosyalarını okuyarak geliştiriciye terminal veya grafik tabanlı arayüz sunan araçtır.

### Veri Türleri

| Tür | Açıklama |
|-----|---------|
| `bool` | Açık (`y`) / Kapalı (`n`) |
| `tristate` | Kapalı (`n`) / Açık (`y`) / Modül (`m`) |
| `string` | Metin değeri |
| `int` | Ondalık sayı |
| `hex` | Onaltılık sayı |

### Anahtar Kelimeler

| Kelime | Açıklama |
|--------|---------|
| `mainmenu` | Konfigürasyon ekranının ana başlığını tanımlar |
| `comment` | Arayüzde görünecek bilgi/açıklama satırı ekler |
| `menu / endmenu` | Seçenekleri hiyerarşik alt menü altında gruplar |
| `choice / endchoice` | Listeden yalnızca tek seçime izin veren grup oluşturur |
| `config` | Yeni bir yapılandırma parametresi tanımlar |
| `default` | Parametrenin başlangıç varsayılan değerini belirler |
| `depends on` | Seçeneğin görünürlüğünü başka bir parametreye bağlar |
| `select` | Seçenek aktif edildiğinde bağımlılıklarını otomatik etkinleştirir |
| `range` | `int` veya `hex` girdilerin min/max sınırlarını belirler |
| `help` | Yardım butonuna basıldığında gösterilecek açıklama metnini içerir |

!!! example "Örnek Kconfig"
    ```kconfig
    mainmenu "Proje Konfigürasyonu"

    config ENABLE_LOGGING
        bool "Loglama aktif et"
        default y
        help
            Sistem loglarını aktif eder.

    config LOG_LEVEL
        int "Log seviyesi"
        range 0 5
        default 3
        depends on ENABLE_LOGGING
    ```

---

## Make

Make, kaynak dosyalar arasındaki bağımlılıkları takip ederek yalnızca değişen dosyaları yeniden derleyen bir build otomasyon aracıdır.

```makefile
target: dependencies
	command   # TAB ile girintilenmeli, boşluk değil!
```

### Özel Karakterler

| Karakter | Açıklama |
|----------|---------|
| `#` | Yorum satırı |
| `@` | Komutun kendisini terminalde gizler; yalnızca çıktısını gösterir |
| `$` | Değişkenlere veya otomatik değişkenlere referans verir |
| `\` | Uzun satırı bir sonraki satırda devam ettirir |

### Değişken Atama Operatörleri

| Operatör | Tür | Açıklama |
|----------|-----|---------|
| `=` | Recursive (gecikmeli) | Değişken çağrıldığı andaki güncel içeriğe göre değerlenir |
| `:=` | Simple (anında) | Atama anında değerlendirilerek sabitlenir |
| `?=` | Koşullu | Değişken tanımlı değilse atar; tanımlıysa mevcut değeri korur |
| `+=` | Ekleme | Mevcut değerin sonuna yeni değeri ekler |

### Otomatik Değişkenler

| Değişken | Açıklama |
|----------|---------|
| `$@` | Mevcut kuralın **target** adı |
| `$^` | Target'a ait **tüm dependency**'lerin listesi |
| `$<` | Target'ı tetikleyen **ilk dependency** |
| `$?` | Target'tan **daha yeni** olan dependency'lerin listesi |

### Joker ve Pattern Karakterler

| Karakter | Açıklama |
|----------|---------|
| `*` | Dosya adı genişletmesinde tüm dosyalarla eşleşir (wildcard) |
| `%` | Pattern kurallarında değişken kısmı temsil eder (örn: `%.o: %.c`) |
| `:` | Target ile dependency arasındaki ilişkiyi kurar |
| `::` | Aynı target için birbirinden bağımsız birden fazla kural tanımlar |

### Make Bayrakları

| Bayrak | Açıklama |
|--------|---------|
| `make -s` | Silent mode; komutların kendisini terminale basmaz |
| `make -k` | Hata olsa bile bağımsız diğer target'lar derlemeye devam eder |
| `make -i` | Hataları yok sayarak sona kadar devam eder |
| `make -j<n>` | `n` paralel iş parçacığıyla derler (örn: `make -j4`) |

!!! danger "Kritik Kurallar"
    1. Makefile komut satırları **kesinlikle TAB** ile girintilenmeli. Boşluk (Space) kullanılması `Makefile:N: *** missing separator` hatasına yol açar.
    2. Target adında bir dizin veya dosya varsa `make: '...' is up to date.` hatası oluşur. Bunu önlemek için `.PHONY` kullanılır.
    3. `wildcard` fonksiyonu mutlaka `:=` ile kullanılmalıdır; aksi hâlde genişletilmez.

!!! example "Örnek Makefile"
    ```makefile
    CC     := gcc
    CFLAGS := -Wall -Wextra -O2
    SRC    := $(wildcard *.c)
    OBJ    := $(SRC:.c=.o)
    TARGET := output

    .PHONY: all clean

    all: $(TARGET)

    $(TARGET): $(OBJ)
    	$(CC) $^ -o $@

    %.o: %.c
    	$(CC) $(CFLAGS) -c $< -o $@

    clean:
    	rm -f $(OBJ) $(TARGET)
    ```

---

## CMake

CMake, platformlar arası derleme süreçlerini otomatikleştiren ve Makefile, Ninja gibi build dosyalarını üreten bir meta-derleme sistemidir.

```mermaid
graph LR
    A["CMakeLists.txt"] -->|"cmake -S . -B build"| B["Build Sistemi\nMakefile / Ninja"]
    B -->|"make / ninja"| C["Executable / Library"]

    style A fill:#2196F3,color:#fff
    style C fill:#4CAF50,color:#fff
```

### Dosya Türleri

| Dosya | Açıklama |
|-------|---------|
| `CMakeLists.txt` | Projenin her dizininde yer alan ana yapı taşı |
| `<script>.cmake` | `cmake -P` ile doğrudan çalıştırılan script dosyaları |
| `<module>.cmake` | `include()` veya `find_package()` ile dahil edilen yardımcı modüller |

### Temel Komutlar

| Komut | Açıklama |
|-------|---------|
| `cmake_minimum_required(VERSION x.y)` | Minimum CMake sürümünü zorunlu kılar |
| `project(ad VERSION x.y LANGUAGES CXX)` | Proje adını, versiyonunu ve dillerini tanımlar |
| `add_executable(hedef kaynak...)` | Kaynak kodlardan çalıştırılabilir program üretir |
| `add_library(hedef TÜR kaynak...)` | Static, shared veya interface kütüphane üretir |
| `add_subdirectory(dizin)` | Alt dizindeki `CMakeLists.txt` dosyasını çalıştırır |
| `target_include_directories(hedef KAPSAM dizin...)` | Header arama dizinlerini hedefe tanımlar |
| `target_link_libraries(hedef KAPSAM kütüphane...)` | Hedefe kütüphane bağlar |

### Kapsam Belirteçleri

!!! tip "PUBLIC / PRIVATE / INTERFACE"
    | Belirteç | Hedef kullanır | Tüketiciler kullanır |
    |----------|:--------------:|:-------------------:|
    | `PUBLIC` | ✓ | ✓ |
    | `PRIVATE` | ✓ | ✗ |
    | `INTERFACE` | ✗ | ✓ |

### Değişken Yönetimi

| Komut | Açıklama |
|-------|---------|
| `set(VAR değer)` | Değişken tanımlar; `${VAR}` ile erişilir |
| `unset(VAR)` | Değişkeni bellekten siler |
| `$ENV{VAR}` | İşletim sistemi ortam değişkenine erişir |
| `set(VAR değer CACHE TÜR "açıklama" [FORCE])` | Cache'e yazılan kalıcı değişken |

!!! note "Tırnak ve Liste Davranışı"
    ```cmake
    set(LIST_VAR a b c)      # Liste: ["a", "b", "c"]
    set(STR_VAR "a b c")     # Tek string: "a b c"
    set(LIST_VAR2 "a;b;c")   # Liste: ["a", "b", "c"]  (manuel ayraç)
    ```

### Akış Kontrolü

| Komut | Açıklama |
|-------|---------|
| `if / elseif / else / endif` | Koşullu bloklar |
| `foreach / endforeach` | Döngü |
| `while / endwhile` | Koşul döngüsü |
| `function / endfunction` | Local scope'lu fonksiyon |
| `macro / endmacro` | Inline yapıştırılan makro (parent scope kullanır) |

!!! tip "function vs macro"
    `function` yeni bir scope açar; içerideki değişkenler dışarıyı etkilemez, etkilemesi için `PARENT_SCOPE` kullanılır.
    `macro` çağrıldığı yere kopyalanır ve o noktanın scope'unu doğrudan kullanır.

!!! example "foreach Kullanımı"
    ```cmake
    foreach(x RANGE 10)       # 0'dan 10'a kadar (10 dahil)
    foreach(x RANGE 10 20)    # 10'dan 20'ye kadar
    foreach(x RANGE 10 20 5)  # 10'dan 20'ye 5'erli artışla

    foreach(item IN LISTS MY_LIST)
        message(STATUS "Eleman: ${item}")
    endforeach()
    ```

!!! tip "if Koşul Operatörleri"
    **1, TRUE, Y, YES, ON** ifadeleri doğru; **0, FALSE, N, NO, OFF, IGNORE, NOTFOUND** ve boş string'ler yanlış kabul edilir.

    | Operatör | Açıklama |
    |----------|---------|
    | `DEFINED` | Değişkenin tanımlı olup olmadığını kontrol eder |
    | `COMMAND` | Belirtilen CMake komutunun mevcut olup olmadığını kontrol eder |
    | `EXISTS` | Dosya veya dizin yolunun var olup olmadığını kontrol eder |
    | `STREQUAL` | İki string değerin eşitliğini kontrol eder |
    | `STRGREATER` / `STRLESS` | String karşılaştırması |
    | `NOT`, `AND`, `OR` | Mantıksal operatörler |

### Yardımcı Komutlar

| Komut | Açıklama |
|-------|---------|
| `message(DURUM "metin")` | Terminale çıktı basar (`STATUS`, `WARNING`, `FATAL_ERROR`) |
| `include(dosya)` | `.cmake` dosyasını dahil eder |
| `find_package(pkg REQUIRED)` | Sistemde kurulu paketi arar |
| `option(VAR "açıklama" ON/OFF)` | Kullanıcıya açma/kapama anahtarı sunar |
| `install(TARGETS/FILES ...)` | Kurulum kurallarını tanımlar |
| `file(GLOB VAR şablon)` | Şablona uyan dosyaları listeler |
| `add_compile_options(flags...)` | Geçerli dizindeki tüm hedeflere derleyici parametresi ekler |
| `add_custom_command(...)` | Derleme sürecine özel komut adımı ekler |
| `add_custom_target(...)` | Dosya üretmeyen bağımsız build hedefi oluşturur |
| `execute_process(COMMAND ...)` | Yapılandırma anında terminal komutu çalıştırır |
| `cmake_policy(...)` | Sürümler arası davranış uyumluluğunu yönetir |

!!! note "execute_process Parametreleri"
    | Parametre | Açıklama |
    |-----------|---------|
    | `COMMAND` | Çalıştırılacak komutu tanımlar |
    | `WORKING_DIRECTORY` | Komutun çalışacağı dizini belirtir |
    | `RESULT_VARIABLE` | Başarıda `0`, hata durumunda `1` döner |
    | `OUTPUT_VARIABLE` | Komut çıktısını değişkene atar |
    | `ERROR_VARIABLE` | Hata mesajını sakladığı değişkeni belirtir |

### Önemli CMake Değişkenleri

| Değişken | Açıklama |
|----------|---------|
| `PROJECT_NAME` | `project()` komutundaki güncel proje adı |
| `CMAKE_PROJECT_NAME` | Kök dizindeki ana proje adı |
| `CMAKE_VERSION` | Çalışan CMake sürümü |
| `CMAKE_GENERATOR` | Kullanılan build sistemi (Ninja, Unix Makefiles) |
| `CMAKE_SOURCE_DIR` | Ana proje dizininin tam yolu |
| `CMAKE_CURRENT_SOURCE_DIR` | İşlenen `CMakeLists.txt`'in bulunduğu dizin |
| `PROJECT_SOURCE_DIR` | En son çağrılan `project()` komutuna ait dizin |
| `CMAKE_BINARY_DIR` | Ana build dizini |
| `CMAKE_SYSTEM_NAME` | Hedef işletim sistemi (Linux, Windows, Darwin) |
| `CMAKE_INSTALL_PREFIX` | `install()` komutunun hedef kök dizini |
| `CMAKE_MODULE_PATH` | Ek modüllerin aranacağı klasör yolları |

### CMake CLI

```bash
cmake --help                         # Genel yardım
cmake --help-variable-list           # Kullanılabilir değişkenleri listeler
cmake --help-variable CMAKE_VERSION  # Belirli değişken hakkında detay

cmake -S . -B build                  # Kaynak dizin ve build dizini tanımla
cmake --build build                  # Build dizinini derle
cmake -P script.cmake                # Script modunda çalıştır (derleme yapmaz)

cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release -S . -B build
```

=== "Derleme Yöntem 1"
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```

=== "Derleme Yöntem 2"
    ```bash
    cmake -S . -B build
    cd build && make
    ```

=== "Derleme Yöntem 3"
    ```bash
    cmake -B build
    cmake --build build
    ```

!!! danger "Dikkat Edilmesi Gerekenler"
    1. Modern CMake'te `file(GLOB)` yerine kaynak dosyaları elle listelemek tercih edilir. `GLOB`, yeni dosyalar eklendiğinde CMake'in otomatik yeniden tetiklenmemesine yol açabilir.
    2. `CACHE` değişkenleri `build/CMakeCache.txt` dosyasında saklanır. Komut satırından `-D` ile verilen değerlerin önbellekteki değerlerin üzerine yazılması için `FORCE` kullanılır.
    3. `CMakeLists.txt` dosyası `-P` (Script modu) ile çalıştırılamaz. `-P` yalnızca `add_executable` gibi derleme hedefleri içermeyen saf `.cmake` script dosyaları içindir.

!!! example "Minimal CMakeLists.txt"
    ```cmake
    cmake_minimum_required(VERSION 3.20)
    project(MyProject VERSION 1.0 LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    add_executable(myapp
        src/main.cpp
        src/utils.cpp
    )

    target_include_directories(myapp PRIVATE include/)
    target_compile_options(myapp PRIVATE -Wall -Wextra)
    ```

---

## CI (Continuous Integration)

**Sürekli Entegrasyon (CI)**, geliştiricilerin yazdığı kodun düzenli aralıklarla (her commit veya pull request'te) ortak bir depoda birleştirilmesi ve otomatik olarak derleme ile testlerden geçirilmesi sürecidir. Amaç, hataları erken aşamada yakalamak ve "bende çalışıyor" sorununu ortadan kaldırmaktır.

!!! note "CI Neden Gereklidir?"
    - Büyük ekiplerde farklı geliştiricilerin yazdığı kodlar birbirine entegre edilirken çakışmalar ortaya çıkar.
    - CI olmadan bu çakışmalar ancak yayına alma aşamasında fark edilir ve düzeltmek çok daha maliyetli olur.
    - CI sistemi, her değişikliği otomatik olarak derleyip test ederek sorunları dakikalar içinde raporlar.

```mermaid
graph LR
    A["👨‍💻 Geliştirici\nKod Yazar"] -->|"git push"| B["📦 Kod Deposu\nGitHub / GitLab"]
    B -->|"Tetikler"| C["🤖 CI Sunucusu\nGitHub Actions / Jenkins"]
    C --> D["🔨 Build\nDerleme"]
    D --> E["🧪 Test\nUnit & Entegrasyon"]
    E --> F{Sonuç}
    F -->|"✅ Başarılı"| G["✅ Onaylandı\nMerge edilebilir"]
    F -->|"❌ Hata"| H["❌ Bildirim\nGeliştirici uyarılır"]

    style A fill:#2196F3,color:#fff
    style G fill:#4CAF50,color:#fff
    style H fill:#F44336,color:#fff
```

### CI Temel Kavramlar

| Kavram | Açıklama |
|--------|---------|
| **Pipeline** | CI sürecindeki adımların sıralı çalıştığı yapı (build → test → raporlama) |
| **Job** | Pipeline içinde bağımsız olarak çalışan bir görev birimi |
| **Step / Stage** | Job içindeki tek bir komut ya da eylem |
| **Trigger** | Pipeline'ı başlatan olay (push, pull request, schedule gibi) |
| **Artifact** | Build sonucunda üretilen çıktı dosyaları (binary, rapor, paket) |
| **Runner / Agent** | CI komutlarını çalıştıran sunucu veya sanal makine |

### Popüler CI Araçları

| Araç | Açıklama |
|------|---------|
| **GitHub Actions** | GitHub reposuna entegre, YAML tabanlı CI/CD platformu |
| **GitLab CI/CD** | GitLab'a gömülü, `.gitlab-ci.yml` dosyasıyla yapılandırılır |
| **Jenkins** | Açık kaynak, eklenti tabanlı, kendi sunucunuzda çalışır |
| **CircleCI** | Bulut tabanlı, hızlı kurulum sunan CI servisi |
| **Travis CI** | Özellikle açık kaynak projeler için yaygın kullanılır |

!!! example "GitHub Actions ile C++ CI (`.github/workflows/ci.yml`)"
    ```yaml
    name: C++ CI

    on:
      push:
        branches: [ main, develop ]
      pull_request:
        branches: [ main ]

    jobs:
      build-and-test:
        runs-on: ubuntu-latest

        steps:
          - name: Kodu İndir
            uses: actions/checkout@v4

          - name: Bağımlılıkları Kur
            run: sudo apt-get install -y cmake g++ ninja-build

          - name: CMake ile Yapılandır
            run: cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release

          - name: Derle
            run: cmake --build build

          - name: Testleri Çalıştır
            run: cd build && ctest --output-on-failure
    ```

!!! tip "İyi bir CI Pipeline'ı"
    1. **Hızlı olmalı:** 10 dakikayı geçen pipeline'lar geliştiricileri yavaşlatır.
    2. **Deterministik olmalı:** Aynı kod her çalıştırmada aynı sonucu vermelidir.
    3. **Anlamlı hata mesajı üretmeli:** Sorunun kaynağını açıkça göstermelidir.
    4. **Her commit'te çalışmalı:** Özellikle ana branch'e giden her değişiklikte tetiklenmelidir.

---

## CD (Continuous Delivery / Deployment)

**Sürekli Teslimat (Continuous Delivery)** ve **Sürekli Dağıtım (Continuous Deployment)** CI'nın devamı niteliğinde iki kavramdır. İkisi de üretim ortamına yazılım gönderme sürecini otomatize eder; aralarındaki tek fark son adımdaki insan müdahalesinin varlığıdır.

!!! tip "Delivery vs Deployment Farkı"
    | | Continuous Delivery | Continuous Deployment |
    |-|--------------------|-----------------------|
    | **Tanım** | Yazılım her an yayına alınmaya **hazır** tutulur | Yazılım her başarılı build'de **otomatik** olarak yayına alınır |
    | **Son adım** | İnsan onayı gerekir | Tamamen otomatik, insan müdahalesi yoktur |
    | **Risk** | Daha düşük; kontrollü yayın | Daha yüksek; otomatik yayın |
    | **Kullanım alanı** | Kritik sistemler, bankacılık | SaaS uygulamaları, web servisleri |

```mermaid
graph LR
    A["✅ CI Başarılı\nBuild & Test"] -->|"Otomatik"| B["📦 Artifact\nÜretildi"]
    B -->|"Otomatik"| C["🧪 Staging\nTest Ortamı"]
    C --> D{Onay}
    D -->|"👤 Manuel Onay\n(Delivery)"| E["🚀 Production\nYayın"]
    D -->|"🤖 Otomatik\n(Deployment)"| E

    style A fill:#4CAF50,color:#fff
    style E fill:#FF9800,color:#fff
```

### CD Ortamları

| Ortam | Açıklama |
|-------|---------|
| **Development (Dev)** | Geliştiricilerin aktif çalıştığı, en sık değişen ortam |
| **Staging** | Üretim ortamının birebir kopyası; son testler burada yapılır |
| **Production (Prod)** | Gerçek kullanıcıların eriştiği canlı ortam |

### Temel CD Stratejileri

| Strateji | Açıklama |
|----------|---------|
| **Blue-Green Deployment** | İki özdeş ortam tutulur; yeni versiyon yeşil'e alınır, trafik anahtarlanır |
| **Canary Release** | Yeni versiyon önce küçük bir kullanıcı grubuna sunulur, sorun yoksa genişletilir |
| **Rolling Update** | Sunucular sırayla güncellenir; sistem hiç tamamen kapanmaz |
| **Feature Flag** | Yeni özellik kodda var ama açık/kapalı yapılandırmayla kontrol edilir |

!!! example "GitHub Actions ile CD (Staging'e Otomatik Deploy)"
    ```yaml
    name: CD - Staging Deploy

    on:
      push:
        branches: [ main ]

    jobs:
      deploy-staging:
        runs-on: ubuntu-latest
        needs: build-and-test       # CI job'ı başarılıysa çalışır

        steps:
          - name: Kodu İndir
            uses: actions/checkout@v4

          - name: Docker Image Oluştur
            run: docker build -t myapp:${{ github.sha }} .

          - name: Staging'e Gönder
            run: |
              docker tag myapp:${{ github.sha }} registry.example.com/myapp:staging
              docker push registry.example.com/myapp:staging

          - name: Staging Ortamını Güncelle
            run: ssh deploy@staging.example.com "docker pull && docker-compose up -d"

      deploy-production:
        runs-on: ubuntu-latest
        needs: deploy-staging
        environment:
          name: production          # GitHub'da manuel onay gerektirir
        steps:
          - name: Production'a Deploy
            run: ssh deploy@prod.example.com "docker pull && docker-compose up -d"
    ```

!!! danger "CD için Dikkat Edilmesi Gerekenler"
    1. **Rollback planı:** Her deployment otomatik olarak geri alınabilmeli; önceki versiyona dönmek hızlı ve güvenli olmalıdır.
    2. **Health check:** Deploy sonrası uygulamanın ayakta olduğu doğrulanmalı, sorun varsa otomatik rollback tetiklenmelidir.
    3. **Secret yönetimi:** Parola, API anahtarı gibi hassas bilgiler asla kaynak kodda bulunmamalı; CI/CD sistemi secret store'lardan okumalıdır.
    4. **Ortam değişkenleri:** Dev/Staging/Prod farkları kod değil, konfigürasyon üzerinden yönetilmelidir.

---

## clang-tidy

**clang-tidy**, LLVM/Clang altyapısını kullanan bir **statik analiz** ve **linting** aracıdır. Kodu çalıştırmadan okuyarak potansiyel hataları, stil ihlallerini ve modernleştirme fırsatlarını tespit eder.

!!! note "Statik Analiz Nedir?"
    Statik analiz, programın **çalıştırılmadan** kaynak kod üzerinde incelenmesidir. Derleyici uyarılarının ötesine geçerek mantık hataları, kaynak sızıntıları ve güvenlik açıkları gibi sorunları önceden fark ettirir.

### clang-tidy Nasıl Çalışır?

```mermaid
graph LR
    A["📄 Kaynak Kod\n(.cpp / .c)"] --> B["🔍 clang-tidy\nAST Analizi"]
    B --> C{Kontrol Listesi}
    C -->|"❌ İhlal Var"| D["📋 Uyarı / Hata\nRaporu"]
    C -->|"✅ Temiz"| E["✅ Kod Onaylı"]
    D -->|"--fix ile"| F["🔧 Otomatik\nDüzeltme"]

    style A fill:#2196F3,color:#fff
    style E fill:#4CAF50,color:#fff
    style F fill:#FF9800,color:#fff
```

### Kontrol Kategorileri

| Kategori | Prefix | Açıklama |
|----------|--------|---------|
| **Clang Analizör** | `clang-analyzer-*` | Bellek sızıntısı, null pointer dereference gibi ciddi hatalar |
| **C++ Modernizasyon** | `modernize-*` | Eski C++ kodunu C++11/14/17 idiomlarına dönüştürür |
| **Performans** | `performance-*` | Gereksiz kopyalama, verimsiz döngü gibi sorunları yakalar |
| **Okunabilirlik** | `readability-*` | İsimlendirme, karmaşıklık ve anlaşılırlık sorunlarını raporlar |
| **Güvenlik** | `cert-*` | CERT C/C++ güvenli kodlama standartlarını uygular |
| **Google Stili** | `google-*` | Google C++ stil kurallarını kontrol eder |
| **Hata Yatkınlığı** | `bugprone-*` | Sık yapılan mantık hatalarını ve tehlikeli kalıpları saptar |
| **Taşınabilirlik** | `portability-*` | Platformlar arası uyumsuzlukları bildirir |

### Kurulum ve Temel Kullanım

```bash
# Kurulum (Ubuntu/Debian)
sudo apt-get install clang-tidy

# Tek dosyayı analiz et
clang-tidy main.cpp -- -std=c++17

# Tüm kontrolleri etkinleştir
clang-tidy main.cpp --checks="*" -- -std=c++17

# Belirli kategorileri seç
clang-tidy main.cpp --checks="modernize-*,bugprone-*,performance-*" -- -std=c++17

# Sorunları otomatik düzelt
clang-tidy main.cpp --checks="modernize-*" --fix -- -std=c++17

# CMake build diziniyle kullan (compile_commands.json gerekir)
clang-tidy -p build/ main.cpp
```

!!! note "compile_commands.json Nedir?"
    clang-tidy, her dosyanın nasıl derlendiğini bilmek ister (hangi include path'ler, hangi bayraklar). Bu bilgiyi `compile_commands.json` dosyasından okur. CMake ile üretmek için:
    ```bash
    cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    ```

### `.clang-tidy` Yapılandırma Dosyası

Proje kök dizinine `.clang-tidy` dosyası eklenerek kontroller kalıcı olarak yapılandırılır:

!!! example "`.clang-tidy` Örneği"
    ```yaml
    ---
    Checks: >
      -*,
      clang-analyzer-*,
      modernize-*,
      bugprone-*,
      performance-*,
      readability-identifier-naming,
      -modernize-use-trailing-return-type

    WarningsAsErrors: "bugprone-*"

    CheckOptions:
      - key: readability-identifier-naming.ClassCase
        value: CamelCase
      - key: readability-identifier-naming.FunctionCase
        value: camelCase
      - key: readability-identifier-naming.VariableCase
        value: lower_case
      - key: readability-identifier-naming.ConstantCase
        value: UPPER_CASE
    ```

### CMake ile Entegrasyon

!!! example "CMakeLists.txt'te clang-tidy"
    ```cmake
    # Tüm hedeflere clang-tidy uygula
    find_program(CLANG_TIDY clang-tidy)
    if(CLANG_TIDY)
        set(CMAKE_CXX_CLANG_TIDY
            ${CLANG_TIDY}
            --checks=modernize-*,bugprone-*,performance-*
            --warnings-as-errors=bugprone-*)
    endif()
    ```

!!! tip "Sık Kullanılan Kontroller"
    | Kontrol | Açıklama |
    |---------|---------|
    | `modernize-use-nullptr` | `NULL` yerine `nullptr` kullanımını önerir |
    | `modernize-use-auto` | Tip açık olduğunda `auto` kullanımını önerir |
    | `modernize-range-based-for` | İndeks döngülerini range-based for'a çevirir |
    | `modernize-use-override` | Sanal fonksiyon override'larına `override` eklenmesini zorunlu kılar |
    | `bugprone-use-after-move` | `std::move` sonrası nesne kullanımını tespit eder |
    | `performance-unnecessary-copy-initialization` | Gereksiz kopyalamaları işaret eder |
    | `clang-analyzer-cplusplus.NewDelete` | Bellek sızıntılarını ve çifte silmeleri tespit eder |

---

## clang-format

**clang-format**, C, C++, Java, JavaScript ve diğer dillerde **kaynak kodunu otomatik olarak biçimlendiren** bir araçtır. Girintileme, boşluk, satır uzunluğu gibi stil kurallarını tek tip hale getirir; böylece ekip içinde kod stili tartışmaları ortadan kalkar.

!!! note "Neden Otomatik Formatlama?"
    Kodu elle formatlamak zaman kaybıdır ve kişiden kişiye farklılık gösterir. `clang-format` kullanıldığında ekibin tamamı farklı editörler kullansa bile her commit aynı formata sahip olur. Code review'lar yalnızca mantıksal değişikliklere odaklanabilir.

### Yerleşik Stil Şablonları

| Stil | Açıklama |
|------|---------|
| `LLVM` | LLVM projesinin kodlama standartları |
| `Google` | Google C++ Stil Kılavuzu |
| `Chromium` | Google'ın Chromium projesi stili |
| `Mozilla` | Mozilla kodlama standartları |
| `WebKit` | WebKit projesinin stili |
| `Microsoft` | Microsoft C++ kodlama stili |
| `GNU` | GNU projesinin stil kuralları |

### Kurulum ve Temel Kullanım

```bash
# Kurulum (Ubuntu/Debian)
sudo apt-get install clang-format

# Çıktıyı terminale yaz (dosyayı değiştirmez)
clang-format main.cpp

# Dosyayı yerinde formatla
clang-format -i main.cpp

# Belirli bir stil şablonuyla formatla
clang-format -i --style=Google main.cpp

# Birden fazla dosyayı formatla
clang-format -i --style=LLVM src/*.cpp include/*.h

# Yalnızca belirli satırları formatla (CI'da fark kontrolü için)
clang-format --dry-run --Werror main.cpp   # Değişiklik varsa hata döner
```

### `.clang-format` Yapılandırma Dosyası

Proje kök dizinindeki `.clang-format` dosyası, tüm ekip için ortak kuralları tanımlar:

!!! example "`.clang-format` Örneği"
    ```yaml
    ---
    BasedOnStyle: LLVM

    # Girinti
    IndentWidth: 4
    TabWidth: 4
    UseTab: Never
    AccessModifierOffset: -4

    # Satır uzunluğu
    ColumnLimit: 120

    # Süslü parantez stili
    BreakBeforeBraces: Allman    # Her { yeni satırda

    # Boşluk kuralları
    SpaceBeforeParens: ControlStatements
    SpaceInEmptyParentheses: false
    SpacesInAngles: false

    # Pointer ve referans hizalama
    PointerAlignment: Left       # int* ptr  (sola yapışık)

    # Include sıralama
    SortIncludes: CaseSensitive
    IncludeBlocks: Regroup

    # Constructor initializer listesi
    BreakConstructorInitializers: BeforeColon

    # Namespace içi girinti
    NamespaceIndentation: None
    ```

!!! tip "BreakBeforeBraces Seçenekleri"
    | Değer | Görünüm | Kullanım |
    |-------|---------|---------|
    | `Allman` | `{` her zaman yeni satırda | C/C++ geleneksel stili |
    | `Attach` | `{` önceki satırın sonunda | Java / Google stili |
    | `Linux` | Fonksiyonda `{` yeni satır, kontrolde ekli | Linux kernel stili |
    | `Mozilla` | Allman benzeri, kendi kurallarıyla | Mozilla stili |

### Editör ve CI Entegrasyonu

=== "VS Code"
    ```json title=".vscode/settings.json"
    {
        "editor.formatOnSave": true,
        "editor.defaultFormatter": "xaver.clang-format",
        "C_Cpp.clang_format_style": "file",
        "C_Cpp.clang_format_fallbackStyle": "LLVM"
    }
    ```

=== "CMake"
    ```cmake title="CMakeLists.txt"
    find_program(CLANG_FORMAT clang-format)
    if(CLANG_FORMAT)
        file(GLOB_RECURSE ALL_SOURCE_FILES
            ${CMAKE_SOURCE_DIR}/src/*.cpp
            ${CMAKE_SOURCE_DIR}/include/*.h)

        add_custom_target(format
            COMMAND ${CLANG_FORMAT} -i --style=file ${ALL_SOURCE_FILES}
            COMMENT "Kod formatlaniyor...")

        add_custom_target(format-check
            COMMAND ${CLANG_FORMAT} --dry-run --Werror ${ALL_SOURCE_FILES}
            COMMENT "Format kontrolu yapiliyor...")
    endif()
    ```

=== "GitHub Actions"
    ```yaml title=".github/workflows/format-check.yml"
    name: Format Check

    on: [ push, pull_request ]

    jobs:
      clang-format:
        runs-on: ubuntu-latest
        steps:
          - uses: actions/checkout@v4

          - name: clang-format Kur
            run: sudo apt-get install -y clang-format

          - name: Format Kontrolü
            run: |
              find src/ include/ -name "*.cpp" -o -name "*.h" | \
              xargs clang-format --dry-run --Werror
    ```

!!! tip "Mevcut Koddan Stil Üretme"
    Mevcut bir proje için `.clang-format` dosyasını sıfırdan yazmak yerine LLVM'den türetip geçerli koda göre ayarlamak daha kolaydır:
    ```bash
    clang-format --dump-config --style=LLVM > .clang-format
    # Sonra .clang-format dosyasını tercihlere göre düzenle
    ```

!!! danger "Dikkat Edilmesi Gerekenler"
    1. `.clang-format` dosyası proje kök dizininde olmalıdır; yoksa clang-format üst dizinlere bakarak arar.
    2. Mevcut bir projeye ilk kez `clang-format -i` uygulandığında çok büyük bir diff oluşur. Bu değişikliği tek bir "format" commit'ine toplamak, git history'nin okunabilirliğini korur.
    3. `ColumnLimit: 0` satır kesimi yapılmamasını sağlar; büyük projelerde okunabilirliği bozabilir.