# GStreamer

## GStreamer Nedir?
GStreamer, ses, video ve diğer multimedya verilerinin işlenmesi, kodlanması, dönüştürülmesi ve akış oluşturulması için kullanılan açık kaynaklı bir çerçevedir. Temel çalışma modeli:

```mermaid
graph LR
  A[Source] --> B[Filter];
  B --> C[Sink];
```

```mermaid
graph LR
  A[Element 1] --> |sink| B[Element 2];
  B --> |source| C[Element 3];
```

## Mimari Özellikler
- **Modüler & Esnek:** Her işlev `“element”` adı verilen bileşenlerle sağlanır.
- **Geniş Codec Desteği:** Çok sayıda format ve codec plug‑in olarak sunulur.
- **Gerçek Zamanlı İşleme:** Düşük gecikmeyle canlı akışları işleyebilir.
- **Düşük Seviye Kontrol:** Pipeline’ı elle kurup detaylı yönetim imkânı.
- **Açık Kaynak:** İstediğiniz gibi genişletip özelleştirebilirsiniz.

## Pipeline, Element ve Pad
- **Pipeline:** Boru hattı (pipeline), elementlerin zincirlenmesidir. 

```bash
gst-launch-1.0 videotestsrc ! videoconvert ! autovideosink
```

- `videotestsrc`→ Test kaynağı
- `videoconvert`→ Renk formatı dönüştürücü
- `autovideosink` → Ekrana çizici sink

- **Element:** Pipeline’ın yapı taşıdır; her biri tek bir görevi üstlenir (kaynak, dönüştürücü, sink…).

- **Pad:** Elementler arası veri akış noktalarıdır:
    - Source Pad: Elementten dışarı veri gönderir.
    - Sink Pad: Elemente veri alır.
- Uyumlu pad türleri eşleşmeli; aksi takdirde bağlantı kurulamaz.

## Hata Ayıklama & Sorgulama
- **GST_DEBUG:** Log seviyesini ayarlar (`0–5`). 
- `gst-launch-1.0 --gst-debug-help`

```bash
export GST_DEBUG=3
```

- `gst-inspect-1.0 [element]` Element veya plugin’in özelliklerini, pad’lerini ve ayarlarını gösterir.
- `gst-discoverer-1.0 [uri]` Medya dosyasının codec, çözünürlük, bit hızı vb. teknik detaylarını çıkarır.

```bash title="Yararlı CLI Komutları"
# Basit test pipeline’ı
gst-launch-1.0 videotestsrc ! ximagesink

# GStreamer versiyon ve kurulu plugin’ler
gst-launch-1.0 --version
gst-inspect-1.0 --plugins

# Kamera servisini yeniden başlat (Jetson örneği)
sudo service nvargus-daemon restart

# Video4Linux cihazları
v4l2-ctl --list-devices
v4l2-ctl -d /dev/video0 --all
v4l2-ctl -d /dev/video0 --list-formats-ext

# Ayrıntılı çıktı
gst-launch-1.0 -v videotestsrc ! videoconvert ! autovideosink
```

!!! note "Not"
    GUI tabanlı uygulamaları uzaktan kullanırken ekran yönlendirmesi için:
    ```bash
    export DISPLAY=:0
    ```