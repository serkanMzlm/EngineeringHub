# Temel Bilgiler

## **Temel Sistem Kavramları**
- **root**, en yetkili kullanıcı `#` gösterilir. Diğer kullanıcılar `$` ile gösterilir.
- **Soft Link:** Başka bir dosyaya referans oluşturur. Gerçek dosyanın kopyası değildir.
- **Hard Link:** Dosyanın tam içeriğine işaret eder; silinirse bile diğer link üzerinden erişilebilir.
- **inode:** Bir dosya veya dizinin kimliğini belirleyen bir numaradır.
- **Daemon:** Genellikle sistem başlatıldığında arka planda çalışan uzun ömürlü süreçlerdir.
- **Process:** Bir uygulama veya komut çalıştırıldığında oluşan yürütülebilir birimdir. Kısa ömürlü olabilir.
- **Dosya Türleri**: Directory(`d`), Symbolic Link(`l`), Dosya(`-`), Karakter Aygıtı(`c`), Blok Aygıtı(`b`), Socket(`s`), FIFO(`p`)
- **CPU (Central Processing Unit)**
- **RAM (Random Access Memory)**
- **Root Filesystem (RootFS)**
- **Scheduler:** CPU zamanını process’ler arasında paylaştıran kernel alt sistemi.
- **Polling:** CPU’nun bir donanımın durumunu belirli aralıklarla aktif olarak kontrol etmesi yöntemi.
- **Dosya İzinleri:** Okuma (`r=4`), yazma (`w=2`), çalıştırma (`x=1`).
- Büyük küçük harf duyarlılığı vardır.
- Dosya veya dizin isminin başında `.` olursa, Linux tarafından gizli kabul edilir. Örnek: `.config/`
- `;` birden fazla komutun sırayla çalışmasını sağlar. `komut1; komut2; komut3`
- `&` komutların arka planda çalışmasını sağlar. `sleep 10 &`
- `|` bir komutun çıktısını diğer komutun girdisi olarak ayarlar. 
- `*` sıfır veya daha fazla, `?` tek bir karakter her şey anlamına gelir.
- `^` düzenli ifadelerde satır başını ifade eder. 
- `[...]` içeriğinin herhangi biriyle eşleşir. 
- `{x..y}` Belirli bir aralıktaki sayıları veya karakterleri üretir.
- `>`  Standart çıktıyı (stdout) belirtilen dosyaya yazar, önceki içerik silinir.  `>>` üstüne yazar.
- `<`  Standart girdiyi (stdin) bir dosyadan alır. 
- `2>`  Standart hata çıktısını (stderr) belirtilen dosyaya yönlendirir. 
- `&>`  Hem stdout hem stderr’i aynı anda yönlendirir. 
- `tee`  Standart çıktıyı hem ekrana basar hem de dosyaya yazar. `-a` ile eklemeli yazma yapılır. 

```bash
sleep 10 & 
touch a{1..7}.txt # 1'den 7'ye dosyalar oluşturur
ls [ab]*          # 'a' veya 'b' ile bağlayan
ls [a-z]          # a'dan z'ye kadar

echo "hello world" > file_name.txt
ls >> file.txt
cat < file.txt
telnet localhost 2> errorfile.txt
echo "hello world" | tee -a file.txt
```

## **Dizin Yapısı**

- **`/`  (Root Directory):** Tüm dosya sisteminin kök noktasıdır.
- **`/bin` ve `/sbin` (Essential Binaries):** Sistemin minimum hayatta kalma setidir. Boot sonrası temel işlemler için gereken komutlar buradadır. Birçok modern distro’da `/bin` → `/usr/bin` symlink olsa da embedded minimal sistemlerde mantık aynı kalır: “kritik komutlar her koşulda erişilebilir olmalı”.
- **`/etc` (system configuration):** Sistemin yapılandırma dosyaları bu kısımda bulunur. örneğin, ağ ayarları, kullanıcı hesapları, güvenlik ayarları bu dizinde bulunur.
- **`/usr` (system software distribution):** Sistemin “dağıtılan yazılım” alanıdır: çoğu binary, library ve read-only içerik burada konumlanır.
- **`/lib`, `/lib64` (essential shared libraries + kernel modules):** Minimal boot için gerekli shared libraries burada bulunur. Ayrıca kernel modules hiyerarşisi  `/lib/modules/<version>/` altındadır. Driver stratejinde “built-in vs module” kararı burada operasyonel sonuç üretir.
- **`/dev` (device nodes):** Kernel’in userspace’e açtığı **device interface** noktasıdır. UART, I2C, SPI, mmc block device gibi donanımlar `/dev` altında “node” olarak görünür. `udev` ile dinamik oluşturulabilir veya statik oluşturulur. Embedded bring-up sırasında “donanım görüyor mu?” sorusunun ilk kanıt noktasıdır.
- **`/proc` (procfs):** Kernel runtime state’inin process-centric görünümüdür. Tamamı virtual’dır. Debug için çok değerlidir:
    - Kernel cmdline (`/proc/cmdline`)
    - Memory / CPU info (`/proc/meminfo`, `/proc/cpuinfo`)
    - Process bilgileri (`/proc/<pid>/`)
- **`/sys` (sysfs):** Kernel object model’in (devices, drivers, buses) userspace arayüzüdür. Embedded’de donanım debug ve kontrol için kritik
- **`/var`** (variable data): Runtime sırasında değişen, **persistent olması beklenen** veridir:
    - logs (`/var/log`)
    - state (`/var/lib`)
- **`/tmp` (temporary, usually volatile):** Geçici dosyalar için alan. Çoğu sistemde tmpfs ile RAM’de tutulur. Reboot sonrası kaybolması beklenir. Embedded’de disk yazımını azaltmak için önemlidir.
- **`/boot` (boot artifacts – distro dependent):** Kernel image, DTB, initramfs gibi boot artifact’leri için konum. Embedded’de çoğu zaman ayrı partition olur
- **`opt`** Üçüncü taraf yazılımlar için isteğe bağlı paketler.
- **`/home`** Kullanıcıların dizinidir.
- **`/mnt, /media`**  Harici medya ve dosya sistemleri bu noktalara bağlanır. 
- **`/run`** Geçici çalışma süresi bilgisi (PID dosyaları, kilitler).

## **System Logs**

Linux'ta sistem olayları, hata mesajları ve uyarılar genellikle `/var/log` dizininde depolanır. Ayrıca systemd kullanan sistemlerde `journalctl` ile günlüğe erişim mümkündür.

- Dinamik içerik için `/etc/profile.d/` altına script eklenebilir.

| Dosya / Komut | Açıklama |
|---------------|----------|
| `/var/log/boot.log` | Önyükleme sırasında oluşan mesajlar (init, kernel, servis bilgileri). |
| `dmesg` | Çekirdek (kernel) ring buffer’ını gösterir. |
| `/var/log/auth.log` | Kimlik doğrulama ve güvenlik olayları (giriş denemeleri, sudo kullanımı). |
| `/var/log/syslog` | Genel sistem ve uygulama mesajları (Debian/Ubuntu). |
| `/var/log/messages` | Genel sistem ve uygulama mesajları (Red Hat/CentOS gibi dağıtımlarda). |
| `/var/log/kern.log` | Kernel’e ait detaylı günlük kayıtları. |
| `journalctl` | systemd journal kayıtlarını okur |

```bash 
journalctl -b          # Son önyüklemeden itibaren tüm logları gösterir
journalctl -u <servis> # Belirli bir servisin günlüklerini filtreler
```


## **Run Levels**
Linux’un geleneksel SysV init sistemi, farklı işletim durumu “seviyelerini” (run levels) rakamlarla tanımlar. Her run level, hangi servislerin ve işlevlerin aktif olacağını belirler:

```bash
sudo init 3 # Run level değiştirme (örnek: seviye 3)
```

| Run Level	| Anlamı | 
|-------|-------|
| 0	 | Kapatma (shutdown). | 
| 1	 | Tek kullanıcı modu (sistem bakım/onarım). | 
| 2	 | Çoklu kullanıcı modu, ağ hizmeti kapalı (dağıtıma göre değişir). | 
| 3	 | Çoklu kullanıcı modu, ağ hizmeti aktif. | 
| 4	 | Tanımlanmamış / Kullanılmaz. | 
| 5	 | Çoklu kullanıcı + grafik arayüzlü (X11/Wayland) + ağ hizmeti. | 
| 6	 | Yeniden başlatma (reboot). | 


!!! note "Not"
    Modern dağıtımlarda Systemd kullanılıyorsa systemctl isolate `multi-user.target` veya `graphical.target` komutlarını tercih etmek daha güncel bir yöntemdir.

## **Device Tree**
Gömülü Linux sistemlerinde (örn. ARM tabanlı kartlar), donanımı çekirdeğe tanıtmak için Device Tree kullanılır.

- **`.dts` (Device Tree Source):** İnsan tarafından okunabilir metin formatı.
- **`.dtb` (Device Tree Blob):** Derlenmiş, ikili format.
- Bir sensör, kontrolcü veya başka bir aygıt için özellikler .dts dosyasında tanımlanır.
- Kernel açılırken bu veriyi okur, uygun sürücüyü yükler ve donanımı yapılandırır.
- Cihazını Linux’e “tanıştırmanın” en düzenli yolu: Device Tree!

```bash
dtc -I dts -O dtb -o output.dtb input.dts
```

## **Driver**
Linux çekirdeği ile donanım arasında köprü kuran yazılım bileşenidir. Donanımı algılar, kontrol eder ve veri akışını yönetir. Yeni bir cihaz eklediğinde, ilgili sürücüyü kernel modülü (ör. *.ko) olarak yüklersin.


## **Terminal Kısayolları**

| Terminal Kısayolları | İşlevi |
|------|------|
| `Alt + F2` | Komut çalıştırma penceresini açar (grafik ortam). |
| `Ctrl + C` | Çalışan komutu sonlandırır. |
| `Ctrl + R` | Önceki komutlarda arama yapar. |
| `Ctrl + S` | Terminal akışını durdurur / sürdürür (komut yürütme durmaz). |
| `Ctrl + Q` | Terminal akışını sürdürür |
| `Ctrl + U` | İmlecin solundaki tüm metni siler. |
| `Ctrl + Z` | Çalışan komutu arka plana alır (durdurur). |