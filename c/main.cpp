#include <iostream>

struct AracKontrol {
    uint8_t led_durumu : 1;  // Sadece 1 bit kapla
    uint8_t far_modu   : 2;  // Sadece 2 bit kapla
    uint8_t sicaklik   : 7;  // Sadece 7 bit kapla
};

int main(void) {
    struct AracKontrol araba;

    araba.led_durumu = 1;   // Arka planda maskeleme yapıldı
    araba.far_modu = 3;     // İkili tabanda 11 (Maksimum 2 bit)
    araba.sicaklik = 95;    // İkili tabanda 1011111 (7 bit)

    printf("Boyut: %zu byte\n", sizeof(araba)); // Çıktı: 2
    
    // Taşma Tuzağı!
    araba.far_modu = 4; // 4 sayısı ikili tabanda '100' (3 bit) demektir.
    // Far modu 2 bit olduğu için baştaki '1' atılır ve ekrana '0' (00) basılır!
    printf("Far Modu: %d\n", araba.far_modu); 

    struct Tehlikeli {
    int durum : 2; // Sadece 1 bitlik SIGNED alan!
};

struct Tehlikeli t;
t.durum = 3;

    printf("Tehlikeli Durum: %d\n", t.durum);
    
    return 0;
}