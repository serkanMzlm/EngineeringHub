# Package Management

## **`dpkg` Low Level Package Manager**

`dpkg`, Debian paket yönetim sisteminin **en alt seviyesindeki** araçtır. Temel görevi, `.deb` uzantılı paketlerin **dosya bazında** sisteme kurulması, kaldırılması ve durumlarının takip edilmesidir.

Eğer paket, başka paketlere bağımlıysa bu bağımlılıklar sistemde yoksa veya herhangi bir nedenden dolayı kurulum yarım kalırsa paket durumu  **half-installed** veya **unconfigured** olarak kalır. Bu durum apt ile kurulumda da olabilir `package is not fully configured`  hatası alınır. Çözüm olarak `dpkg --configure -a` kullanılır.

```bash
dpkg -i <package>.deb  # Manuel kurulum yapar.

dpkg --configure -a    # kurulumu tamamlanamamış tüm paketlerin konfigürasyon aşamasını 
                       # tamamlamayı dener.

dpkg -l                # Kurulu paket listesi ve durumları
dpkg -L <package>      # Paketin sisteme hangi dosyaları kurduğunu gösterir
dpkg -S <file>         # Bir dosyanın hangi pakete ait olduğunu bulur
```

## **`apt` High-level package manager**

`apt` (Advanced Package Tool), Debian paket yönetim sisteminin **high level** aracıdır. `apt`, `dpkg`’yi kullanarak çalışır fakat onun eksik olduğu tüm alanları tamamlar.

- Repository’lerden paket indirir
- Dependency resolution yapar
- Kurulum sırasını belirler
- Hata durumunda kurtarma senaryoları uygular

```bash
# Sistemde tanımlı repository paket metadata bilgisini indirir.
# metadata: hangi paketler var, paket versiyonları ve bağımlılıkları 
# hiçbir paketi kurmaz veya güncelemez 
apt update 

# sistemde halihazırda kurulu olan paketlerin, repository’de 
# mevcut daha yeni sürümleriyle güncellenmesini sağlar
apt upgrade

apt list --upgradable                 # Bu komut, sistemde güncellenebilir paketlerin listesini gösterir.
apt list --installed                  # Kurulu tüm paketleri listeler
apt --reinstall install <paket_adı>   # Mevcut paket sürümünü yeniden yükler.

# upgrade daha agrasiftir. Gerektiği durumlarda paket ekleyip silebilir
apt full-upgrade 
apt dist-upgrade

apt-cache             # Paket metadata bilgileri için kullanılır. 
											# güncel sistemlerde kullanılmadanda çalışır
apt-cache show <package> 
apt-cache policy <package>
apt-cache search <word> 

apt search <word>     # Arama yapar
apt show <package>    # Paket metadata bilgilerini gösterir. 
apt policy <package>  # Pin priority bilgilerini gösterir
apt edit-sources      # Depo listelerini düzenlemeye yarar (örn. sudo nano /etc/apt/sources.list).

apt install <package> # Paket ve bağımlılıklarını kurar
apt remove  <package> # Paketi kaldırır
apt purge   <package> # Paketi ve konfigürasyon dosyalarını tamamen siler

apt autoremove        # Artık hiçbir paket tarafından kullanılmayan paketleri 
                      # sistemden kaldırır

apt autoclean         # İndirilen ancak artık repository’de bulunmayan (obsolete) 
                      # paket dosyalarını siler.
                      
apt clean             # Tüm indirilen paket cache’ini tamamen temizler.

apt install -f        # Bozuk veya eksik bağımlılıkları düzeltmeyi hedefler (--fix-broken)
```

## **`apt` vs `apt-get`**

Debian tabanlı sistemlerde paket yönetimi uzun süre **`apt-get`** ve **`apt-cache`** araçlarıyla yapılmıştır. Daha sonra **`apt`**, bu araçların üstüne inşa edilmiş **modern, kullanıcı dostu bir arayüz** olarak tanıtılmıştır. Bu iki araç **aynı altyapıyı** (APT libraries + `dpkg`) kullanır; fark, **hedef kitle ve davranış modelindedir**.
