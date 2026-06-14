## QML Programlama
- `import` QML modülünü projeye dahil eder. Versiyon parametresi (örn. 2.0), modülün sürümünü belirtir.
- `Item` Genel kapsayıcıdır. Diğer tüm görselleri içine ekleyebilirsiniz.
- `Text` Sabit metin gösterimi.
- `TextInput` Kullanıcıdan metin girişi almak için.
- `Image` resim eklenmesini sağlar.
- `Rectangle` Dörtgen alan oluşturur. `clip` İçerik sınırları dışında kalan bölgeleri keser.
- `id` Ögeye özgün bir ad atar; başka yerden bu adla erişim sağlar.
- `width/height` Genişlik ve yükseklik değerlerini belirler.
- `x/y` Ögenin konumunu belirler; iç içe yapıda üst kapsayıcı köşesini referans alır.
- `color` Renk ayarlaması yapar; isim, hex (#aarrggbb) veya Qt.rgba() ile belirtilebilir.
- `opacity` Ögenin saydamlığını (0–1) ayarlar; iç içe geçiyorsa üst elemanla birleşir.
- `scale` Ögenin ekrandaki ölçeğini değiştirir; gerçek width/height sabit kalır.
- `rotation` Ögeyi derece cinsinden döndürür; transformOrigin ile dönüş merkezini belirleyebilirsiniz.
- `anchors` Ögelerin konum ve boyutunu başka ögelere sabitlemek için kullanılır (örn. anchors.left, anchors.verticalCenter).
- `MouseArea` Fare veya dokunmatik etkileşimleri algılar (onClicked, onPressed, onPositionChanged vb.).
- `preventStealing` MouseArea içindeyken diğer MouseArea’ların olayı “çalmasını” engeller.
- Keys Klavye tuşu olaylarını dinler (Keys.onPressed, Qt.Key_Up vb.).
- `property` Ögeye dinamik özellik eklemek için kullanılır; tip ve isteğe bağlı başlangıç değeriyle tanımlanır (örn. property int count: 0).
- `NumberAnimation` Belirli bir özellik üzerinde animasyon sağlar; from, to, duration ve `on <property>` ile ayarlanır.

## XML Programlama

- **XML (Extensible Markup Language)**, veri depolama ve taşınmasını kolaylaştıran, hem insan hem de makine tarafından okunabilir bir işaretleme dilidir.
- Gereksiz derin iç içe geçişlerden kaçının; okunabilirliği bozar.
- Boyutsal verileri (tarih, saat) parçalara ayırmak yerine kısa string formatı tercih edin.
- XML boşlukları korur; `<a> </a>` içinde iki boşluk gerçek içerik olur.
- Belgeleri minify ederek küçültün, aktarımı hızlandırın. Dosyayı küçültmek için tüm satır sonu ve gereksiz boşlukları kaldırabilirsiniz 
- Karmaşık veri yapıları için `JSON` veya `YAML` formatlarını kullanın.
- **Öznitelikler (Attributes):** `<person id="123" role="admin">Ali</person>`
    - Etiket içinde ad="değer" biçiminde tanımlanır.
    - Aynı öğe içinde birden fazla öznitelik kullanılabilir.
    - Öznitelik değerleri her zaman tırnak ("…" veya '…') içinde olmalıdır.
- Prolog (`<?xml …?>`): **version**, **encoding** karakter kodlaması (örn. `"UTF-8"`, `"ISO-8859-1"`).
- **Tek bir root (kök)** eleman zorunludur; tüm diğer etiketler bu kökün içinde tanımlanır.
- **Etiket adları** rakamla veya `xml` ile **başlayamaz**; büyük/küçük harf duyarlıdır.
- **Açılış/kapama:** `<tag> … </tag>`,  XML’de iç içe etiketler, doğru açılış/kapama sırasıyla tanımlanmalıdır.
- **Boş eleman:** `<tag/>`
- **İçerik:** Metin, başka etiketler veya her ikisi birden olabilir.
- Yorum Satırı `<!-- Bu bir yorum satırıdır -->`
- **CDATA bölgesi:** Özel karakterlerin kaçış gerektirmeden yer aldığı ham metin. 

```xml
<?xml version="1.0" encoding="utf-8"?>
<root>
    <parent>
        <child>Metin içeriği</child>
        <emptyTag/>           <!-- Kendini kapatan boş etiket -->
    </parent>

    <script><![CDATA[
    if (a < b && b > c) { /* kod */ }
    ]]></script>

</root>
```

### Özel Karakterler ve Escaping
Bazı karakterler doğrudan yazılamaz, yerlerine entity referansları kullanılır:

| Entity          |   Karakter    |    Açıklama    |
|-----------------|---------------|----------------|
| `&lt;`          | `<`     |  küçüktür     |
| `&gt;`          | `>`     |  büyüktür     |
| `&amp;`         | `&`     |  ampersand    |
| `&quot;`        | `"`     |  çift tırnak     |
| `&apos;`        | `'`     |  tek tırnak     |

```xml
<note>Use &lt;tag&gt; to define elements &amp; entities.</note>
```

### Namespace (Ad Alanı)
- İsim çakışmalarını engellemek için kullanılır. Kök öğede tanımlanır:
```xml
<root xmlns:h="http://www.w3.org/TR/html4"
      xmlns:f="https://www.w3schools.com/furniture">
  <h:table>
    <h:tr><h:td>Apples</h:td></h:tr>
  </h:table>
  <f:table>
    <f:name>African Coffee Table</f:name>
  </f:table>
</root>
```
- `xmlns:prefix="URI": prefix:` ile başlayan öğeler bu URI kapsamında tanımlanır.
- URI gerçek bir web adresi olmak zorunda değil; tanımlama amacıdır.

### Şema ve DTD (Doctype)
XML belgelerinin yapısını tanımlayan mekanizmalardır:

- DTD (Document Type Definition):
```xml
<!DOCTYPE note [
  <!ELEMENT note (to,from,heading,body)>
  <!ELEMENT to (#PCDATA)>
  …
]>
```

- XSD (XML Schema Definition):
``` xml
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">
  <xs:element name="note">
    <xs:complexType>
      <xs:sequence>
        <xs:element name="to" type="xs:string"/>
        …
      </xs:sequence>
    </xs:complexType>
  </xs:element>
</xs:schema>
```