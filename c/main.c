#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h>

typedef struct {
  uint8_t a;
  uint16_t b;
  uint16_t c;
} __attribute__((packed)) Foo;

int main(int argc, char *argv[]) {

    Foo foo = {.c = 1, .a = 12}; // Tüm alanları sıfırla
    
    // foo.a = 12;
    // foo.b = 50;
    // foo.c = 100;

    printf("Size of Foo: %zu bytes\n", sizeof(Foo)); // Çıktı: 5 bytes
    printf("Values: a = %u, b = %u, c = %u\n", foo.a, foo.b, foo.c); // Çıktı: a = 12, b = 50, c = 100

    return 0;
}