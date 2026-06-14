## **systemctl Dosyaları**
- Systemd, modern Linux dağıtımlarında “init” sisteminin yerini alan bir sistem ve hizmet yöneticisidir.
- Amaçları:
    - Paralel başlatma ile açılış süresini kısaltmak.
    - Bağımlılık grafiği kullanarak servisler arası doğru sırayı garantilemek.
    - Journald ile merkezi günlük kaydı (log) tutmak.
    - Socket, D-Bus, timer, mount ve daha pek çok birimi yönetmek.
-Genel Konumlar
    - Sistem geneli: `/etc/systemd/system/`
    - Dağıtım birincil: `/lib/systemd/system/` veya `/usr/lib/systemd/system/`
    - Kullanıcı bazlı: `~/.config/systemd/user/`
- Her `.service` dosyası üç ana başlığa sahiptir:
```service
[Unit]
Description=Kısa ve öz açıklama
After=network.target
Wants=postgresql.service

[Service]
Type=simple
ExecStart=/usr/bin/my-daemon --option
ExecReload=/bin/kill -HUP $MAINPID
Restart=on-failure
RestartSec=5s
User=myuser
Environment=ENV_VAR=value

[Install]
WantedBy=multi-user.target
```

- `[Unit]`
    - **Description:** Hizmetin ne yaptığını özetler.
    - **After / Before:** Başlama sırasını ayarlar. Örneğin **After=network.target → ağ** hazır olmadan başlamaz.
    - **Wants / Requires:** Zayıf / güçlü bağımlılık ilişkileri kurar.

- `[Service]`
    - **Type:** Başlatma davranışını belirler.
        - **simple (default):** ExecStart arka planda ayrılmadan çalışır.
        - **forking:** Daemon arka plana fork ettiğinde kabul edilir.
        - **oneshot:** Tek seferlik kısa işler için.
        - `notify, dbus, idle vb.` gelişmiş tipler de var.
    - **ExecStart, ExecReload, ExecStop:** Başlatma, yeniden yükleme ve durdurma komutları.
    - **Restart:** Yeniden başlatma koşulları (no, on-success, on-failure, always vb.).
    - **RestartSec:** Yeniden başlatma öncesi bekleme süresi.
    - **User / Group:** Hizmeti hangi kullanıcı/grup altında çalıştıracağını belirler.
    - **Environment:** Çevresel değişkenleri tanımlar.
    - **WorkingDirectory:** Çalışma dizinini ayarlar.

- `[Install]`
    - **WantedBy:** Hangi target’a “enable” edildiğinde ekleneceğini tanımlar. Örneğin `multi-user.target → systemctl enable my.service ile /etc/systemd/system/multi-user.target.wants/my.service` bağlantısı oluşturulur.
    - **RequiredBy:** Zorunlu alt birim ilişkisi oluşturur

## **systemctl Komutları**
```bash
sudo systemctl start   my.service   # Başlatır
sudo systemctl stop    my.service   # Durdurur
sudo systemctl restart my.service   # Yeniden başlatır
sudo systemctl status  my.service   # Durum bilgisini gösterir

sudo systemctl enable  my.service   # Boot’ta otomatik başlayacak şekilde işaretler
sudo systemctl disable my.service   # Artık otomatik başlamaz
sudo systemctl is-enabled my.service  # Etkin mi diye kontrol eder

sudo systemctl daemon-reload # Yeni veya güncellenmiş birim dosyalarını tanıtmak

systemctl list-units --all # Tüm birimleri listeler
systemctl list-units --type=target  # Sadece target’ları gör

# Sistemi kapat / yeniden başlat / uyku moduna al
sudo systemctl poweroff
sudo systemctl reboot
sudo systemctl suspend
sudo systemctl hibernate
```

```
[Unit]
Description=ROS 2 Startup Service
After=network.target

[Service]
Type=simple
User=rosuser
Environment=HOME=/home/rosuser
ExecStart=/home/rosuser/start_ros2.sh
Restart=on-failure
RestartSec=10s

[Install]
WantedBy=multi-user.target
```

- Bu dosyayı `/etc/systemd/system/ros2-start.service` olarak kaydedin.

```bash 
sudo systemctl daemon-reload
sudo systemctl enable  ros2-start.service
sudo systemctl start   ros2-start.service
```

### Birim (Unit) Türleri
| Tip	| Uzantı	| Ne İşe Yarar? |
|-----|---------|-----------------|
| Service	| .service	 | Arka plan hizmetlerini (daemon) tanımlar. |
| Target	| .target |	Çeşitli birimleri gruplar, run level yerine geçer. |
| Socket	| .socket |	Socket-activated servisler tanımlar. |
| Timer	    |  .timer |	Zamanlanmış görevler (cron alternatifi). |
| Mount	    |  .mount | 	Dosya sistemleri otomatik monteler. |
| Path	    | .path |	Dosya/dizin değişikliklerini tetikleyici yapar. |