
# Terminal Komutları

## **File & Directory Operations**
- `pwd` , `touch` , `mv` , `ls` , `tree` , `cat`  , `find`, `cp`
- **`cd`:** `.` bulunduğun dizin, `..` bir üst dizin, `-` bir önce ki dizin, `~` home
- `rmdir` Boş dizini siler.
- `ln` Hard veya sembolik link oluşturur. `-s` sembolink link, `-i` hard link
- `file` : Bir dosyanın **gerçek türünü** içeriğini analiz ederek belirler. Dosyanın uzantısına güvenilmez
- `stat` : `ls -l` göre daha detaylı dosya meta bilgilerini gösterir.
- `install`: Genellikle **`build` ve `deployment`** süreçlerinde kullanılan, `cp + chmod + chown` birleşimi bir komuttur
- `less` , `more` , `head` , `tail`
    - `less` : Büyük dosyaları **sayfalı**, **scroll edilebilir** ve **arama destekli** şekilde görüntüler.
    - `more` :`less`’in daha eski ve sınırlı versiyonudur. Sadece ileri yönde sayfalama yapar.
- `locate` : Önceden oluşturulmuş bir **dosya indeksini** kullanarak arama yapar. `find`’e göre çok hızlıdır; ancak **gerçek zamanlı değildir**.   
- `which` : Bir komut çağrıldığında **shell’in PATH environment variable** üzerinden **hangi executable dosyayı çalıştıracağını** gösterir
- `whereis`  : Bir komutun **binary**, **source** ve **manual** dosyalarının olası konumlarını birlikte listeler. `which`’ten farklı olarak **PATH** ile sınırlı değildir; standart dizinlerde arama yapar.
- `readlink`  Bu komut sayesinde link edilmiş bir dosyanın gerçek konumunu gösterir.

```bash
ls -t              # zamana göre sıralar
ls -S              # boyuta göre sıralar

tree  -d           # sadece dizinleri gösterir
tree  -h           # boyutları gösterir 

rm -i <file>       # silmeden önce onay ister
rm -rf             # Belirtilen her şeyi siler
rm -rf  !(a.txt)   # a.txt dışında dosyaları siler.

cat -n <file>      #satır numarası ekler

find . -type d -name "log"   # Dosya türüne göre filtreler (file, directory, link).
find /var -size +10M         # Dosya boyutuna göre arama yapar.

cp -r <dir> <copy>  # Dizinleri ve içinde bulunan her şeyi kopylamayı sağlar. 
cp -l <file> <copy> # Kopyalama işlemini link şeklinde yapar.

mv a.txt /home/       # Dosya taşıma
mv a.txt b.txt        # Dosyanın ismini değiştirme

mkldir -p dizin/dizin      # İç içe dizin  oluşturur.

cat a.txt                      # içeriği gösterir  
cat > a.txt                    # a dosaysını oluşturup içine yazı yazmamızı sağlarla
cat >> a.txt                   # a dosyası varsa üstüne yazmamızı sağlar.
cat a.txt >  b.txt             # a dosaysını b dosyasına kopyalar.
cat a.txt >> b.txt             # a dosaysını b dosyasının üstüne yazar.

install -m 755 app ~/app               # permission set eder
install -d /etc/myapp                  # dizin oluşturur
sudo install -o root app ~/app         # owner belirler
sudo install -o myuser app ~/app       # dizin oluşturur

dmesg | less
less large.log

head -c 100 <file>  # Dosya başından byte sayısına göre çıktı verir.
tail -c 100 <file>  # Dosya sonundan byte sayısına göre çıktı verir.

locate -i network   # Büyük/küçük harf duyarsız arama
updatedb            # locate komutunun datebase günceller.


find . -size +100M        # 100mb büyük dosyaları arar
find . -type f -perm 0777 # Belirtilen izinlere sahip dosyaları bulur.
find . --name *.gz        # gz uzantılı dosyaları bulur.
find . -mtime 3           # 3 gün içinde değişiklik yapılan dosyaları bulur.

which ls
which -a gcc    # Tüm eşleşmeleri gösterir

whereis ls
whereis -b gcc  # Sadece binary dosyaları gösterir.
```

## **Arşivleme ve Sıkıştırma**

- `tar` , `gzip` , `gunzip` ,  `zip` , `unzip` , `xz` , `7z`
- `truncate` Dosyayı belirtilen boyuta keser.
- `zcat` : `.gz` dosyasının içeriğini **diskte açmadan** stdout’a basar. Log analizi ve pipe senaryolarında idealdir.  

```bash
# -c arşiv oluşturur
# -x arşiv açar.
# -f arşiv dosya adını belirtir.
# -p dizinin izinlerinin korunmasını sağlar
# -v işlem sırasında dosyaları listeler.
# -z gzip ile sıkıştırır
tar -cvf backup.tar project/  
tar -xvf backup.tar

# -k orijinal dosyayı korur.
# -d açma işlemi (gunzip eşdeğeri)
# -l sıkıştırılmış dosya bilgilerini gösterir
# -9 maksimum sıkıştırma
gzip -k file.txt
gzip -9 big.log  

gunzip *.gz  # .gz dosyalarını açar

zcat archive.log.gz
zcat system.log.gz | grep error

truncate -s 40 file.txt  #dosyayı 40 byte olarak keser fazlalık olan kısmı siler. Sıkıştırma işlemi yapmaz.
```

## **Text Processing**

- `grep - egrep` Metin içinde desen arar.
- `cut` Belirtilen sütunları veya karakterleri keser.
- `awk` Alan bazlı metin işleme sağlar.
- `sed` Satır içi metin değiştirmeye yarar.
- `sort` Satırları belirli kritere göre sıralar.
- `uniq` Birbirini izleyen tekrarları filtreler.
- `tr` Karakter dönüşümleri yapar.
- `wc` Satır, kelime ve byte sayar.
- `diff` Dosyalar arasındaki satır farklılıklarını gösterir. (line by line)
- `cmp` Dosyaları byte byte karşılaştırır. (byte by byte)
- `truncate` kesme işlemi yapar.

```bash
grep keyword file.txt            # Belirtilen kelimeyi dosya içinde arar
grep -c keyword file.txt         # Belirtilen kelimenin dosyada kaç tane olduğunu gösterir.
grep -i keyword file.txt         # Belirtilen kelimeyi dosya içinde arar. Arama yaparken büyük küçük duyarlılığı kapatır.
grep -n keyword file.txt         # Hnagi satırlarada bulunaduklarını    gösterir.
grep -v keyword file.txt         # Belirtilen anahtar kelimesi dışındaki yerleri alır
grep -R "GZ_SIM_RESOURCE_PATH" . # Belirltilen dizinin içinde bulunan bütün dosyaların içinde arama yapar

ls | grep Desktop
egrep -i "keyword1|keyword2" file.txt  # Arama yaparken keyword1 veya keyword2 birinin olması yeterli olur.


cut -c1 file.txt           # 1. sütünda bulunan karakterleri gösterir.
cut -c1,3,4,5 file.txt     # 1., 3., 4., 5. sütünda bulunan karakterleri gösterir.
cut -c1-4 file.txt         # 1. sütündan 4. sütüna kadar bulunan karakterleri gösterir.
cut -c1-4, 6-8 file.txt
cut -b1-3 file.txt         # 1. sütündan başlayıp 3 byte veri al
ls -la | cut -c2-4


awk '{print $1}' file.txt                  # Dosyanın içinde bulunan her satırda bulunan ilk kelimeyi gösterir.
awk '{print $2, $4}' file.txt 
awk '{print $NF}' file.txt                 # Her satırın son kelimesini gösterir. 
awk '/jer/ {print}' file.txt               # Dosyanın içinde jey arar ve varsa ekranda gösterir. 
cat file.txt | awk '{$2="hi"; print $0}'   # Bu dosaynın içinde bulunan her satırda 2. kelimesini "hi" ile değiştirir.
awk 'lenght($0) > 20' file.txt             # İlk karakteri 20 bytetan fazla olan satırları gösterir.
ls -l | awk '{if($9 == "Des") print $0;}'  # Şartı sağlayan satırı gösterir.


sed 's/[kelime]/[yeni_kelime]/g' dosya.txt      # kelime olan kısımlar  yeni_kelime ile değiştirilir.
sed -i 's/[kelime]/[yeni_kelime]/g' dosya.txt   #  -i parametresi sayesinde dosyanın içinde yapılır değişiklik
sed -i 's/[kelime]/d' dosya.txt                 #  kelime siler


sort file.txt      # Alfabetik sıraya göre sıralar
sort -r file.txt   # Alfabetik sıranın tersine  göre sıralar
sort -k2 file.txt  # Alfabetik sıraya göre sıralar (2. kelimeye bakarak sıralam yapılır)


uniq file.txt      # Aynı olan satıorların sadece birini gösterir
uniq -c  file.txt  # Her satırın kaç kez geçtiğini gösterir.


sort file.txt | uniq
sort file.txt | uniq -c
sort file.txt | uniq -d   #Sadece tekrarlanan kısmı gösterir.

cat a.txt | tr ‘a-z’  ‘A-Z’              # Bütün harfleri büyük yazar

wc file.txt    # Stır kelime byte çıktısı verir
wc -l file.txt # Satır sayısını verir.
wc -w file.txt # Kelime sayısını verir.
wc -c file.txt # Byte sayısını verir.
ls -l | wc -l
grep  keyword file | wc -l   # Belirtilen keyword kaç kez geçtiğini bulmuş oluruz

truncate -s 40 file.txt      # Dosyayı 40 byte olarak keser fazlalık olan kısmı siler. Sıkıştırma işlemi yapmaz.
```


## **Süreç & Kaynak Yönetimi**
- `ps` Çalışan süreçleri listeler.
    - TTY sütunu, işlemin hangi terminalde yürütüldüğünü,
    - TIME sütunu, o işlemin ne kadar süredir çalıştığını,
    - CMD sütunu ise hangi komutun çalıştırıldığını gösterir.
    - `ps aux` çıktısındaki STAT sütununda yer alan harflerin anlamları ise şunlardır:
        - **D:** uyku modu (disk I/O için bekliyor)
        - **R:** çalışıyor
        - **T:** duraklatılmış
        - **X:** zorla durdurulmuş
        - **Z:** zombi işlem
        - **S:** işlem için kaynak (örneğin CPU) bekliyor
- `pstree` ise bu işlemleri adeta bir aile ağacı gibi detaylı şekilde görselleştirir—kim kimin çocuğu, kim kimin ebeveyni, hepsini tek bakışta anlarsınız!
- `top` Canlı sistem kaynak kullanımını gösterir. PID, USER, PR(öncelik seviyesi), RES(RAM miktarı) gibi durumlar gözlenebilir.
- `kill` Süreci sonlandırmak için sinyal gönderir.
- `nohup` Komutu oturumdan bağımsız çalıştırır. Yani terminal kapansa dahi komut yürütülmeye devam eder.
- `bg` Durdurulan işlemi arka plana alır.
- `fg` Arka plandaki işlemi ön plana getirir.
- `jobs` O anki kabuk işlerinin durumunu listeler.
- `nice - renice` Komuta öncelik (niceness) atar. / Çalışan sürecin önceliğini değiştirir.
- `script` Terminal oturumunu kaydeder.
- `timeout` Komutun çalışmasını süre ile sınırlar.
- `dd` “Disk Dump” kısaltmasıyla bilinir. Unix/Linux’ta dosya, disk ve blok düzeyinde kopyalama yapmanızı sağlar. Veri bloklarını farklı biçimlerde işleyerek yedekleme, klonlama veya sıfırlama (örneğin `/dev/zero` kullanarak) gibi işlemlerde kullanılabilir.

```bash
ps 
ps -a
ps aux
ps -e                  # O kullanıcı tarafından yapılan tüm işlemler
ps -u [user_name]      # Belirli bir kullanıcının yaptıklarını gösterir.
ps -ef
pstree

kill -l                # Sinyallari sitler.
kill -9 PID_number     # İşlemi sonlandırır.
kill -1 PID_number     # İşlemi yeniden başlatır.
killall       top      # PID numarası yerine direkt işlemin adı verilir.

# En fazla CPU tüketen 5 uygulamayı listeler
ps H -eo pid,pcpu | sort -nk2 | tail

# PID karşılık Gelen uygulamanın hangisi olduğu anlaşılır.
# ll ilede gösterilebilir.
ps aux | fgrep [PID] 
ll /proc/[PID]

top -u [user_name]   # Belirli bir kullanıcının detaylı gösterilmesini sağlar.

# nohup process &
# nohup process > /dev/null 2>&1 &
nohup sleep 75 &
nohup sleep 70 > /dev/null 2>&1 &

timeout 10s ping google.com
timeout 1m ping google.com
timeout 1h ping google.com

dd if=/dev/sda of=/mnt/backup/sda.img bs=64K conv=noerror,sync
```


## **Sistem Bilgisi & İstatistik**
- `uname` Sistem bilgilerini görüntüler.
- `arch` İşletim sistemi mimarisini gösterir. (64 / 32)
- `df` Dosya sistemi kullanım özetini verir.
- `du` Dizin veya dosya boyutunu hesaplar.
- `free` Bellek (RAM) kullanımını gösterir.
- `dmesg` Kernel mesajlarını okur.
- `lsusb`
- `lsmod` Yüklü çekirdek modüllerini listeler.
- `lsblk` Blok aygıtlarını ağaç yapısında gösterir.
- `fdisk` Disk bölüm bilgilerini yönetir.
- `blkid` Blok aygıtlarının UUID ve tür bilgilerini listeler.
- `badblocks` Bozuk disk bloklarını tarar.
- `fsck` Dosya sistemini onarır.
- `lspci` PCIe cihazlarını listeler (GPU, NIC, NVMe, Wi-Fi).
- `modprobe` Kernel modülü **yükler veya kaldırır**. Dependency’leri otomatik çözer. `insmod`’a göre tercih edilir çünkü bağımlılık yönetir.
- `modinfo` Bir modül hakkında **metadata** verir.
- `dmesg`Kernel ring buffer’ını okur. **Boot, driver, donanım hataları** burada konuşur.
- `mount`  bir dosya sistemini **mount point’e bağlar**.  `mount /dev/sdb1 /mnt/data`
- `umount`bağlı bir dosya sistemini **güvenli şekilde ayırır**. `umount /dev/sdb1`
- `findmnt`  mount ilişkilerini **ağaç yapısında** gösterir.
- `mountpoint` bir dizinin **gerçekten mount edilmiş olup olmadığını** kontrol eder.
- `mkfs`

```bash
uname -a    # Tüm sistem bilgileri
uname -s    # İşletim sisteminin adı
uname -r    # İşletim sisteminin sürümünü gösterir.
uname -m    # Mimari (x86_64, aarch64)

du dosya_yolu
du -h dosya_yolu    # Boyutları okunabilirliğini artırır.
du -sh dosya_yolu   # Alt dizinleri almaz

free 
cat /proc/cpuinfo   # Tüm sistem bilgilerinin bulunduğu dosyadır.
cat /proc/meminfo   # RAM hakkında bilgi verir.

lsusb -v   # Ayrıntılı modda USB cihaz bilgilerini gösterir.
lsusb -t   # USB cihaz hiyerarşisini gösterir.

dmesg
dmesg | less
dmesg -H  #Anlaşılır
dmesg -c  #Günlüğü temizler
dmesg -l  #Günlükleri filtrelemek için kullanılı (-l err sadece hataları gösterir)
lspci -k  # Hangi device hangi kernel driver’ını kullanıyor net görülür.
```

## **Kullanıcı & İzinler**
- `chmod` Dosya/dizin izinlerini değiştirir. (u = user, g = groups, o = or)
- `chown` Sahiplik bilgilerini değiştirir.
- `chgrp` Grup bilgisini değiştirir.
- `useradd` Yeni kullanıcı ekler.
- `usermod` Mevcut kullanıcıyı düzenler.
- `userdel` Kullanıcı siler.
- `groupadd` Yeni grup oluşturur.
- `groupdel` Grup siler.
- `passwd` Kullanıcı şifresi ayarlar.
- `chfn` Kullanıcı bilgilerini değiştirir.
- `getfacl`etfacl — ACL bazlı izinleri yönetir.
- `id` Kullanıcının bağlı olduğu ID gösterir.
- `w` Sistemde çevrim içi kullanıcı sayısını gösterir.
- `lastb - last` lastb Sisteme başarısız girişleri gösterir. last bütün girişleri gösterir
- `users`  Sistemde aktif kullanıcıları gösterir.
- `whoami`  O an ki kullanıcı adını verir.

```bash
chmod 777 file
chmod ugo+rwx file
chmod g-x file
chmod +x file

chown root file
chgrp root file

chown yeni_kullanıcı a.txt
chgrp grupadi dosyaadi

userdel -r user_1  # Kullanıcıyı home dizini ile beraber siler
usermod -U user_1  # Aktif 
usermod -L user_1  # Pasif

sudo useradd -m -s /bin/bash ali    # -m home dizini, -s login shell
sudo usermod -aG arge ali

sudo userdel -r ali                 # home birlikte kullanıcı silme
```

## **Ağ & İnternet**
- `ip` modern Linux’ta ağ yapılandırmasının merkez komutudur. `ifconfig`, `route`, `arp` gibi eski araçların yerini alır. Linux kernel netlink arayüzü üzerinden ağ yapılandırmasını ve durumunu yöneten ana araçtır. Ağ ile ilgili üç temel varlığı tek komut ailesi altında toplar:
    - **link** → fiziksel / sanal arayüz
    - **addr** → IP adresleri
    - **route** → yönlendirme (routing)
- `ping` Ağ bağlantısını test eder. `-c` ile kaç kez atılacağı ayarlanır.
- `ifconfig`p addr — Ağ arayüzü yapılandırmasını gösterir.
- `netstat - ss` Aktif bağlantıları listeler.
- `curl` URL’lerden veri transferi yapar.
- `wget` Dosya indirir.
- `dig - nslookup` Komutları, belirli bir alan adı veya IP adresi hakkında bilgi almak için DNS (Domain Name System) sunucularına sorgu yapmak için kullanılan komut satırı araçlarıdır.
- `iptables` Paket filtreleme ve NAT kurallarını yönetir.
- `arp` ARP tablosunu gösterir.
- `hostname` Sistem adı ve IP adresini verir. Sistemin ağ üzerindeki adını (hostname) `/etc/hostname` dosyasından okur ve değiştirir `sudo hostnamectl set-hostname yeni_hostname`
- `netdiscover` Ağ taraması yapar.
- `nmcli` NetworkManager’ı komut satırı üzerinden yönetmenizi sağlayan güçlü bir araçtır. Ağ bağlantıları oluşturabilir, düzenleyebilir, silebilir ve mevcut durum hakkında ayrıntılı bilgi alabilirsiniz.
- `nm-connection-editor` NetworkManager bağlantılarını grafiksel (GUI) ortamda düzenlemenizi sağlar. Masaüstü kullanıcıları için idealdir.

```bash
wget https:/...../.....tar.gz
curl -o putty httğs:/..../...tar.gz

# l → listening socket’ler
# n → numeric (DNS çözme yapma)
# t → TCP, u → UDP
# p → process (PID / binary)
ss -lntp     # Kim hangi portu dinliyor
ss -lunp
ss -nt       # Tüm aktif bağlantıları görme

nmcli general status   # Temel durum kontrolü
nmcli device status    # Arayüz bazlı durum
nmcli connection show  # Bağlantıları listele
nmcli connection show --active
nmcli connection delete "Wired connection 1" 
nmcli con show                      # Mevcut ethernet profili
nmcli con up "Wired connection 1"   # Elle aktif etme 

nmcli con mod "Wired connection 1" \
  ipv4.method manual \
  ipv4.addresses 192.168.1.50/24 \
  ipv4.gateway 192.168.1.1 \
  ipv4.dns "8.8.8.8 1.1.1.1"
  
sudo nmcli connection add \
  type ethernet \
  ifname eth0 \
  con-name eth0-dhcp \
  ipv4.method auto \
  ipv6.method ignore

sudo nmcli connection delete eth0

# Create a new DHCP profile
sudo nmcli connection add type ethernet ifname eth0 con-name eth0 ipv4.method auto ipv6.method ignore

# Fix permissions
# Without these, NetworkManager can see the profile but cannot activate it.
sudo chmod 600 /etc/NetworkManager/system-connections/eth0
sudo chown root:root /etc/NetworkManager/system-connections/eth0

# Restart NM
sudo nmcli connection reload
sudo systemctl restart NetworkManager

# Bring up the interface
sudo nmcli connection down eth0
sudo nmcli connection up eth0


nmcli con down "Wired connection 1"
nmcli con up "Wired connection 1"

nmcli radio wifi        # Wi-Fi donanımı açık mı
nmcli radio wifi on
nmcli radio wifi off
nmcli dev wifi list     # Ağları tara
nmcli dev wifi connect "SSID_ADI" password "SIFRE"  # Ağa bağlanma

# Aynı anda birden fazla profil varsa, öncelik belirlenir.
nmcli con mod "EvWifi" connection.autoconnect-priority 10
nmcli con mod "OfisWifi" connection.autoconnect-priority 20

# Arayüz bazlı aç/kapa
nmcli device disconnect wlan0
nmcli device connect wlan0
nmtui # nmcli’nin metin tabanlı, kullanıcı dostu arayüzüdür. CLI yerine basit menülerle ağ ayarlarını yönetmek isterseniz tercih edebilirsiniz.
```


## **Zaman & Planlama**
- `date` Tarih ve saati gösterir veya ayarlar.
- `sleep` Belirtilen süre bekler. `sleep 10`
- `watch` Komutu belirli aralıklarla tekrarlar.
- `crontab` Zamanlanmış görevler oluşturur.
- `at` Tek seferlik zamanlanmış iş başlatır.
- `uptime` Çalışma süresi ve kullanıcı sayısını gösterir.

```bash
date                                # Tarih ve saati gösterir
sudo date --set="$(date)"           # Tarih ve saati düzenler
sudo date -s "10 MAR 2023 10:19:23" # Tarih ve saati düzenler
sudo date -s "2023-12-16 09:16:00"
sudo date +%T -s "13:30:00"
# Ya da 
timedatectl set-time '2015-11-20 22:13:20'
```

!!! note "Not"
    Linux sisteminde belirli zaman aralıklarında veya zamanlamalar da tekrarlanması gereken görevleri otomatikleştirmek için kullanılır. crontab komutu belirli günlerde belirli haftalarda belirli zaman aralıklarında tekrarlamasını istediğimiz komutlar için kullanılır. Oluşan dosyalar `etc/cron.[]` konumunda bulunur. `crontab -e`  crontab dosyasını düzenlemek için kullanılır. Açılan dosyananın içine dakika saat gün ay ve haftanın günü son olarakda yapılacak komut yazılır.
    ```bash
    crontab -e
    0 2 * * * echo "hello world" > a.txt   # Bu kısımda * işareti o kabsadığı alanın her zaman dilimini alır.

    at now + 1 hour echo "hello world"   # ctrl + D işlemi tamamlanır.
    ```

## **Kernel & Yardım**
- `reboot` Sistemi yeniden başlatır.
- `poweroff` Sistemi anında kapatır.
- `shutdown`  Sistemi kapatırken seçenekler sunar.
- `exit` Açık olan kullanıcıdan çıkar.
- `env - printenv` Sistemde bulunan evrensel değişkenleri gösterir. Ortam değişkenini kullanmak için `$` kullanılır
- `su` Kullanıcı değiştirmeyi sağlar.
- `bash` Yeni bir kabuk başlatır.
- `source` Betik dosyasını mevcut kabuğa yükler.
- `clear` Terminali temizler
- `history` Kabuk komut geçmişini listeler.
- `man` Komut kılavuz sayfasını açar.
- `info` GNU bilgi sayfasını gösterir.
- `--help` Komut yardımını ekrana basar.
- `alias - unalias` Takma ad oluşturur veya siler.
- `apropos` Belirtilen anahtar kelimeye göre kılavuz sayfalarını arar.
- `export` Ortam değişkeni tanımlar.
- `lsb_realease`  Kullanılan sürüm hakkında bilgi verir.
- `who`  Sisteme giriş yapmış kullanıcıları gösterir.
- `whatis`  Komut hakkında kısa bilgi verir.
- `whereis / which`  Komutun konumunu gösterir.
- `wall` Tüm kayıtlı kullanıcılara terminal üzerinden mesaj iletmenizi sağlar. Yalnızca yetkili kullanıcılar tarafından çalıştırılabilir.
- `write` Belirli bir kullanıcıya doğrudan mesaj göndermek için kullanılır. İleti girdisini tamamlamak için Ctrl +D tuşuna basmanız yeterlidir.


```bash
env
printenv
echo $PATH

su user_1   # user_1 kullanıcısına geçer
sudo su     # root kullanıcısına geçer
sudo -i     # root kullanıcısı olarak yeni bir kulanıcı kabugu açılmış gibi davranır.
sudo -s     # o an ki kabugun root gibi davranmasını sağlar.

apropos "list directory contents"

history
HISTSIZE=2000      # history komutunda en fazla kaç komut tutulacağını ayarlar.
!124               # history komutunda 124 sırada komut çalışır.
!!                 # Bir önceki komut çalışır
!-3                # Üç önceki komut çalışır.
!:2                # Son komutun 2. indexte bulunan parametresini ifade eder

wall "Sistem bakımı yapılacaktır. Lütfen oturumunuzu kaydedin ve bekleyin."
write user_1   # Mesajınızı yazın, ardından Ctrl + D ile gönderin
```

## **ACL (Access Control List)**
Standart Unix izinlerinin ötesinde, her dosya veya dizine kullanıcı ve grup bazlı ayrıntılı erişim hakları tanımlamanıza imkân verir. Böylece belirli bir kullanıcının veya grubun okuma, yazma, çalıştırma gibi izinlerini hassas biçimde ayarlayabilirsiniz.

- `getfacl` Dosya/dizin üzerindeki ACL girişlerini ve temel izinleri gösterir.
- `setfacl` ACL üzerinden izin ekleme, düzenleme veya silme işlemleri yapar.