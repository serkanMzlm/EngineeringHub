### Arduino Port Olarak Görünmemesi

```bash
sudo usermod -a -G dialout <user_name> (${USER})
sudo usermod -a -G tty <user_name>
```

```bash
# 85-brltty.rules dosyasının [ ENV{PRODUCT}=="1a86/7523/*",
# ENV{BRLTTY_BRAILLE_DRIVER}="bm", GOTO="brltty_usb_run"] 
# kısmı yorum satırı yapılır.
sudo nano /usr/lib/udev/rules.d/85-brltty.rules
```

### USB Hata Vermesi

USB dosya aktarırken hata vermesi durumunda `sudo ntfsfix /dev/sdb1` komutu girilir.

### Wifi Şifrelerini Görme

```bash
sudo grep psk= /etc/NetworkManager/system-connections/*
```

### Sudo Şifre İstemeyi Kaldırma

```bash
sudo visudo     # Bu komut sudoers dosyasnını açar buda sudo ayarları dosyasıdır.
[usr] ALL=(ALL) NOPASSWD:ALL  #Belirtilen kullanıcının şifre girmesini kaldırır.
```

### Terminalden Bir Uygulama Başlatmak

- Eğer indirilen uygulama terminalden direkt çalışmıyorsa çalıştırılabilir dosyası `/usr/local/bin/` altına dosya link yapılır.

```cpp
sudo ln -s $(readlink -f qtcreator) /usr/local/bin/qtcreator
```