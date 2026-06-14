# Raspberry Pi

- GPIO numaralarının karşılıklarını görmek için `/sys/kernel/debug/gpio` dosyasına bakılabilir

```bash
sudo cat /sys/kernel/debug/gpio
```

- `/etc/udev/rules.d` dosyasının altına belirli kurallar eklenebilir bu kısımda eklenen dosyanın başında yazan sayı öncelik durumunu belirtir ne kadar büyük bir sayıyısa o kadar sonra olucagını ayarlar. 

### GPIO Erişilebilir Yapmak (rules)

```bash
sudo nano /etc/udev/rules.d/99-gpio-permissions.rules
```
```
SUBSYSTEM=="gpio*", PROGRAM="/bin/sh -c 'chown -R root:gpio /sys/class/gpio && chmod -R 770 /sys/clas>
```

```bash
sudo udevadm control --reload-rules
```

### Config File Dosyası 
- `config.txt` dosyası, Raspberry Pi'nin SD kartındaki kök dizine yerleştirilir ve düz metin dosyasıdır. Raspberry Pi’yi başlatırken sistem bu dosyayı okuyarak uygun donanım ayarlarını yapar.
- `#` yorum satırı anlamına gelir.
- `dtoverlay=imx219` -> **"device tree overlay"** parametresidir

### Kamera Test

1. `vcgencmd get_camera`:
    - **`supported=1 detected=1`:** Kamera bağlı ve Raspberry Pi tarafından tespit edilmiş.
    - **`supported=1 detected=0`:** Kamera bağlı ama Raspberry Pi tarafından tespit edilmemiş.
    - **`supported=0 detected=0`:** Kamera bağlı değil veya desteklenmiyor.

2. `dmesg | grep -i camera`

3. **v4l2-ctl:**
    ```bash
    v4l2-ctl --list-devices

    v4l2-ctl --device=/dev/video0 --list-formats

    v4l2-ctl --device=/dev/video0 --list-formats-ext

    v4l2-ctl --device=/dev/video0 --all
    ```

### Kalıcı Swap Alanı Oluşturma
```bash
# swap dosyası oluşturur.
sudo fallocate -l 2G /swapfile

#  2 GB boyutunda bir swap dosyası oluşturur
sudo dd if=/dev/zero of=/swapfile bs=1M count=2048

# Swap dosyasının kullanabilmesi için uygun izinleri verir
sudo chmod 600 /swapfile

# Swap alanını aktif hale getirir.
sudo mkswap /swapfile
sudo swapon /swapfile
```
- Kalıcı olarak yapmak için `sudo nano /etc/fstab` dosyasının son kısmına `/swapfile none swap sw 0 0` eklenir.