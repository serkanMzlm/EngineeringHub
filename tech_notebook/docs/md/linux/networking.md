
## **IP Adresleri ve Sınıfları**
Ağ üzerinde iletişim kuran her cihaza atanan benzersiz 32‑bit (IPv4) veya 128‑bit (IPv6) sayıdır. IPv4’te dört ondalık bölümle ***(ör. 192.168.1.10)***, IPv6’da ise sekiz grup onaltılık sayıyla **(2001:0db8:85a3::8a2e:0370:7334)** gösterilir.
- **IP (Internet Protocol):** İnternetteki her cihazın benzersiz kimliğidir. Trafiğin doğru hedefe yönlendirilmesini sağlar.
- **Sınıflar:** Eskiden her ip adresi 5 sınıfa ayrılırdı. Günümüzde CIDR yaygın olsa da temel fikir halen öğretici:

| Sınıf	| Aralık	| Kullanım Alanı | 
|-------|-----------|-----------------|
| A |	0.0.0.0   - 127.255.255.255 |	Çok büyük ağlar | 
| B |	128.0.0.0 - 191.255.255.255 |	Orta boy ağlar | 
| C |	192.0.0.0 - 223.255.255.255 |	Küçük ağlar | 
| D |	224.0.0.0 - 239.255.255.255 |	Multicast yayınlar | 
| E |	240.0.0.0 - 255.255.255.255 |	Deneysel / rezerve | 

- **Loopback:** 127.0.0.1 “kendi kendinle konuşman” için. Yerel sistem testi ve geliştirme için vazgeçilmez.

## **Subnet Mask (Alt Ağ Maskesi)**
- IP adresini **“ağ kısmı”** ve **“cihaz kısmı”** olarak ikiye bölen 32‑bit değer. Genellikle dört ondalık bölümle gösterilir (ör. 255.255.255.0). **255** olan bitler → ağ adresini, **0** olan bitler → host (cihaz) adresini temsil eder
- Örnek: 255.255.255.0 → ilk 24 bit ağ, son 8 bit host.
- CIDR karşılığı: /24

```bash
ip addr show eth0
# Çıktıda "inet 192.168.1.10/24" görürseniz:
#   - IP: 192.168.1.10
#   - Alt ağ masking: /24 (255.255.255.0)
```

## **Gateway (Varsayılan Ağ Geçidi)**
- Yerel ağdan çıkış noktasıdır. Genellikle bir router veya firewall cihazı.
- Farklı ağları birbirine bağlar.
- Bir cihaz başka ağdaki IP’lere paket gönderdiğinde kullanılır.
```bash
ip route
# default via 192.168.1.1 dev eth0 (Burada 192.168.1.1 sizin gateway’inizdir.)
```

## **MAC Adresi**
- Her NIC (Network Interface Card) için üretici tarafından atanan 48‑bit benzersiz donanım adresi. Genellikle altı çift onaltılık sayı ile gösterilir (00:1A:2B:3C:4D:5E).
- Veri Bağlantı Katmanı (OSI Katman 2).
- Donanıma gömülü, normalde değiştirilemez (ancak ip link set dev eth0 address ile yazılımla da değiştirilebilir).
- IP adresi katmanından bağımsız çalışır; LAN içi iletişimde kullanılır.
```bash
ip link show eth0
# link/ether 00:1a:2b:3c:4d:5e brd ff:ff:ff:ff:ff:ff
```

## **DNS (Domain Name System)**
- Alan adlarını (ör. chat.openai.com) IP adreslerine çeviren hiyerarşik dağıtık bir sistem.
- “İnsan-dostu” isimlerle internette gezinmeyi mümkün kılar.
```bash
dig +short example.com
# ya da
nslookup example.com
```

## **NIC (Network Interface Card)**
- Ağa bağlı cihazlar ve bilgisayarlar arasındaki veri iletişimini yönetmek için kullanılan bir donanım bileşenidir. NIC, bir bilgisayarın ağa bağlanabilmesi için gereken fiziksel bağlantıyı sağlar ve verilerin kablosuz veya kablolu ağlar üzerinden transfer edilmesini sağlar
- Fiziksel veya sanal ağ adaptörü.
- Ethernet, Wi‑Fi, Bluetooth vs. gibi farklı türleri vardır.

!!! note "Not"
    `/etc/hosts` Küçük ölçekli isim‑adres eşleştirmelerini içerir. 

## **FTP (File Transfer Protocol)**
- Port 21 üzerinden çalışan eski işlevsel dosya aktarım protokolü. Şifrelenmemiştir, bu yüzden güvensiz kabul edilir.
```bash
ftp ftp.example.com
# kullanıcı ve şifre ile oturum açarsınız
```

## **Rsync**
- Dosya ve dizinleri hem yerelde hem de uzak sistemlerde senkronize eden, delta-transfer (sadece değişen blokları) destekli araç.
    - `-a` Arşiv modu (izinler, tarih, vs.)
    - `-v` Ayrıntılı çıktı
    - `-z` Sıkıştırma
    - `--progress` Aktarım durumu
    - `--delete` ile hedefde olmayan dosyaları siler.
    - `--dry-run` ile neler yapılacağını test edersiniz.

```bash
rsync -avz --progress /local/dir/ user@remote:/backup/dir/
```

## **SCP (Secure Copy Protocol)**
- SSH tüneli üzerinden dosya transferi yapan, verileri otomatik olarak şifreleyen araç.
- `-r:` Dizinleri recursive kopyalar.
```bash
scp -r ./project user@192.168.1.100:/var/www/html/
```

## **SSH (Secure Shell)**
- Uzak makinaya şifreli bağlantı kuran, komut satırı ve port yönlendirme gibi özellikler sunan protokol. `ssh user@remote_host`
- Önemli Ayarlar (/etc/ssh/sshd_config):

| Ayar |	Açıklama | 
|-----|--------------|
| Port	| SSH dinleme portu (varsayılan 22). | 
| PermitRootLogin no	| Direkt root girişini engeller. | 
| PermitEmptyPasswords	| Boş parola kullanımını yasaklar. | 
| AllowUsers serkan	| Sadece belirtilen kullanıcı(lar) giriş yapabilir. | 
| ClientAliveInterval	| Boşta kalındığında sunucudan istemciye ping gönderme aralığı (s). | 
| ClientAliveCountMax	| Kaç ping sonrası bağlantıyı keser (0 = sınırsız). | 

```bash title="Anahtar Tabanlı Kimlik Doğrulama"
ssh-keygen -t ed25519     # Anahtar çifti oluşturur
ssh-copy-id user@host     # Public anahtarı uzak sunucuya kopyalar
ssh -i ~/.ssh/id_ed25519 user@host  # Belirli anahtar ile bağlanma
```
## **Cockpit**
- Web tabanlı, interaktif sunucu yönetim konsolu. Sistem durumu, servisler, konteynerler ve kullanıcı yönetimi gibi işlemleri tarayıcıda yapmanızı sağlar.

## **DHCP (Dynamic Host Configuration Protocol)**
- LAN’a katılan cihazlara otomatik IP, subnet mask, gateway ve DNS bilgisi atayan protokol.
