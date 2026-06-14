# AVR
### GPIO Kontrolü
![pinout](../../assets/img/embedded/pinout.png)

- **Data Direction Register:** DDRx register’ı, ilgili port pinlerinin giriş (0) mi yoksa çıkış (1) mi olduğunu belirler. (DDRB, DDRC, DDRD...)
- **Port Output Register:** `PORTx` register’ı, çıkış modundaki pinlere **HIGH (1)** veya **LOW (0)** çıkış seviyesini atar.
- PINx register’ı, o porta bağlı pinlerin **INPUT** durumunda okunan dijital seviyesini **(HIGH/LOW)** yansıtır.
    - AVR’de: `PINB`, `PINC`, `PIND` gibi isimlerle kullanılır.
    - **Pull‑Up ve Pull‑Down:** Arduino kartlarında dahili pull‑up dirençleri vardır; bu sayede unconnected pinler HIGH seviyede sabitlenir. Eğer dahili pull‑up’u devre dışı bırakmak isterseniz, MCUCR’daki PUD bitini 1 yapabilirsiniz: `MCUCR |= (1 << PUD);  // Pull‑Up Disable`
- En temiz yöntem, bit kaydırma (1 << bit_no) ve mantıksal operatörler kullanmaktır:
- `|=` ve `&=` kullanımı, diğer pin değerlerini koruyarak yalnızca istediğiniz biti değiştirir.

```c title="PORTD DDRD Kontol"
DDRD = 0b00000001;   // aynı: DDRD = 0x01;
DDRD = 0xFF;         // 0b11111111 tüm pinler
```

```c title="PORTD PORT Kontol"
DDRD  = 0x01;        // D0 pinini OUTPUT yap
PORTD = 0x01;        // D0 pinini HIGH (5V)

PORTD = 0xFF;        // 0b11111111 tüm pinler
PORTD = 0x00;        // 0b00000000
```

```c linenums="1"
PORTD |= (1 << PORTD0);  // D0 pinini HIGH yapar (diğer pinler etkilenmez)
PORTD &= ~(1 << PORTD0); // D0 pinini LOW yapar (diğer pinler etkilenmez)
PORTD |= (1 << PORTD0) | (1 << PORTD1); // D0 ve D1 pinlerini HIGH yapar
```

```c title="" linenums="1"

DDRD = 0xFF;   // Tüm PORTD pinlerini OUTPUT olarak ayarla

while (1) {
    
    for (uint8_t i = 0; i < 8; i++) { // Sırayla LED’i yak
        PORTD |= (1 << i);
        _delay_ms(100);
    }
    
    for (uint8_t i = 0; i < 8; i++) { // Sırayla LED’i söndür
        PORTD &= ~(1 << i);
        _delay_ms(100);
    }
    
    for (uint8_t i = 0; i < 8; i++) { // Alternatif olarak XOR ile toggle:
        PORTD ^= (1 << i);
        _delay_ms(100);
    }
}

// Veri okuma 
bool button_press = PINB & (1 << PORTB0);

// Debouncing (Titreşim Giderme)
if (PINB & (1 << PORTB0)) {     // Butona basıldıysa
    _delay_ms(50);              // 50 ms bekle
    if (PINB & (1 << PORTB0)) { // Hala basılı mı?
        // Geçerli basış
    }
}
```

!!! note "Not"
    `int` gibi bilgisayarın sistemine göre değişen boyutların kullanımı bazı durumlarda değişik alanlar kapladığından sorun yartabilir bu yüzden platform bağımsız olması için her sistemde aynı bellek alanı genişliği tutan birimlerin kullanımı daha güvenlidir. `uint8_t` ,`uint16_t` ….

- **DDRD** ve **PORTD** bellek adresleri üzerinden doğrudan erişilen **I/O** register’larıdır. olarak **DDRD** bellek alanı `0x2A` bu kısıma erişip bu kısımda değişiklikler yapıp pinlerin durumları belirlenebilir.

![data](../../assets/img/embedded/data.png)

```c
#define myDDRD *((uint8_t*)0x2A) 
```

## ISR – Interrupt Service Routine

- **SREG** içindeki I biti (`sei()`) set edilirse ve bir kesme kaynağı tetiklenirse, ilgili **ISR()** fonksiyonu çalışır.
- Kesmenin işlenebilmesi için:
    - **Global interrupt** (sei()) açık olmalı.
    - İlgili **Mask Register’da** (ör. **EIMSK**) o kesme kaynağı izinli olmalı.

```c title="Dış Kesme INT0" linenums="1"
int main() {
    EIMSK |= (1 << INT0); // 1. INT0 maskesini aç (EIMSK)

    // 2. Kesme tetikleme konfigürasyonu (EICRA: düşük/rising seçimi)
    EICRA |= (1 << ISC01);  // ISC01=1, ISC00=0 → fall edge

    sei(); // 3. Global interrupt aç

    while (1) {}
}


// INT0 kesmesi gerçekleşince burası çalışır
ISR(INT0_vect) {
    // Kesme işleme kodu
}
```

| Register	| İşlevi |
|----------|---------|
| EIMSK	| External Interrupt Mask Register |
| EICRA	| External Interrupt Control Register A |
| EIFR	| External Interrupt Flag Register |
| MCUCR	| MCU Control Register (örn. PUD bit’i) |
| SREG	| Status Register (I biti = global interrupt) |

### Pin Change Interrupt (PCINT)
- **PCICR** register’ı ile belirli portlardaki pin değişim kesmelerini etkinleştirirsiniz.
- **PCMSKx** (Pin Change Mask) ile hangi pinlerin izleceğini seçersiniz.

### Timer/Counter:
- AVR mikrodenetleyicilerde üç temel timer vardır:

| Timer	 | Bit Genişliği |	Maks Sayaç Değeri |
|------|----|----|
| Timer0 | 8 bit	| 255 |
| Timer1 | 16 bit	| 65535 |
| Timer2 | 8 bit	| 255 |

- **CPU Frekansı ve Zaman Adımı:** 
    - Arduino Uno’da `F_CPU = 16 MHz → 1 döngü = 1 / 16 000 000 s ≈ 0.0625 μs`
    - Timer sayaç adımı = Prescaler’a bağlı olarak CPU döngü süresinin katları olur.

- **Basit Delay Hesabı:** 
    - **CTC (Clear Timer on Compare)** modunda, belirli bir gecikme için “compare match” değeri hesaplanır `OCRn = (DesiredDelay_s / TickTime_s) - 1`
    - TickTime_s = Prescaler × (1 / F_CPU)
    - Örnek: 10 ms gecikme, prescaler = 64:

```c linenums="1"
TickTime = 64 / 16 000 000 = 4 μs
OCRn = (0.010 s / 4e‑6) - 1 ≈ 2499
```

```c title="CTC Mode Örneği (Timer1)" linenums="1"
void timer1_ctc_init(uint16_t ocr) {
    TCCR1B |= (1 << WGM12);         // CTC modu
    OCR1A = ocr;                    // Compare değeri
    TCCR1B |= (1 << CS11) | (1 << CS10); // Prescaler = 64
    TIMSK1 |= (1 << OCIE1A);        // Compare A kesmesini aç
    sei();                          // Global interrupt
}

ISR(TIMER1_COMPA_vect) {
    // 1 ms veya belirlediğiniz sürede burada çalışır
}

int main(void) {
    // Yaklaşık 1 ms için
    uint16_t ocr = (16e6/64/1000) - 1;  
    timer1_ctc_init(ocr);
    while (1) { }
}
```