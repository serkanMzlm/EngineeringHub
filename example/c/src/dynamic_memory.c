#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================= SAFE ALLOC WRAPPERS =================

// malloc başarısız olursa NULL döner.
// Embedded / production sistemlerde bu kontrol kritik, çünkü NULL dereference
// genellikle undefined behavior + crash üretir.
void *safeMalloc(size_t size)
{
    void *ptr = malloc(size);

    if (!ptr)
    {
        printf("malloc failed!\n");
        exit(EXIT_FAILURE); // production'da alternatif recovery mekanizması olabilir
    }

    return ptr;
}

// calloc = malloc + memset(0)
// Buradaki kritik fark: tüm memory sıfırlanır.
// Bu özellikle struct ve array başlangıç state'i için güvenlidir.
void *safeCalloc(size_t count, size_t size)
{
    void *ptr = calloc(count, size);

    if (!ptr)
    {
        printf("calloc failed!\n");
        exit(EXIT_FAILURE);
    }

    return ptr;
}

// realloc en riskli fonksiyonlardan biridir:
// - eski pointer geçersiz olabilir
// - move (memory relocation) yapabilir
// - failure durumunda eski pointer kaybolmamalıdır
void *safeRealloc(void *ptr, size_t size)
{
    void *new_ptr = realloc(ptr, size);

    if (!new_ptr)
    {
        printf("realloc failed!\n");
        exit(EXIT_FAILURE);
    }

    return new_ptr;
}

// ================= BASIC ALLOCATION =================
void demoBasicMalloc(void)
{
    int *arr = (int *)safeMalloc(5 * sizeof(int));

    // malloc sonrası memory garbage içerir (initialize edilmemiş)
    // bu yüzden mutlaka manuel doldurma gerekir
    for (int i = 0; i < 5; i++)
    {
        arr[i] = i * 10;
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    // free sonrası pointer dangling olur (hala adres tutar ama invalid)
    free(arr);
}

// ================= CALLOC =================
void demoCalloc(void)
{
    int *arr = (int *)safeCalloc(5, sizeof(int));

    // calloc kullanıldığı için tüm değerler otomatik 0'dır
    // bu özellikle state machine / buffer init için önemli avantajdır
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    free(arr);
}

// ================= REALLOC (CRITICAL PART) =================
void demoRealloc(void)
{
    int size = 3;
    int *arr = (int *)safeMalloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
        arr[i] = i + 1;

    // realloc kritik nokta:
    // memory block taşınabilir (heap fragmentation nedeniyle)
    // bu yüzden eski pointer kullanılmamalıdır
    size = 6;
    arr = (int *)safeRealloc(arr, size * sizeof(int));

    // yeni alan initialize edilmez → garbage olabilir
    for (int i = 3; i < size; i++)
        arr[i] = (i + 1) * 10;

    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");

    free(arr);
}

// ================= STRING ALLOCATION =================
void demoStringAllocation(void)
{
    const char *src = "Dynamic Memory";

    // strlen + 1 -> NULL terminator için zorunlu
    // C string'lerinde en sık yapılan hata: +1 unutmak
    char *buffer = (char *)safeMalloc(strlen(src) + 1);

    strcpy(buffer, src);

    printf("String: %s\n", buffer);

    free(buffer);
}

// ================= STRUCT ALLOCATION =================
typedef struct
{
    char name[20];
    int age;
} Person_t;

void demoStructAllocation(void)
{
    // struct heap allocation:
    // embedded sistemlerde sık kullanılır (dynamic object creation)
    Person_t *p = (Person_t *)safeMalloc(sizeof(Person_t));

    // pointer üzerinden erişim -> stack vs heap farkını net gösterir
    strcpy(p->name, "Serkan");
    p->age = 30;

    printf("Name: %s | Age: %d\n", p->name, p->age);

    free(p);

    // free sonrası p hala aynı adresi tutar (dangling pointer riski)
    // production'da p = NULL yapılması önerilir
}

// ================= MAIN =================
int main(void)
{
    printf("=== MALLOC DEMO ===\n");
    demoBasicMalloc();

    printf("=== CALLOC DEMO ===\n");
    demoCalloc();

    printf("=== REALLOC DEMO ===\n");
    demoRealloc();

    printf("=== STRING DEMO ===\n");
    demoStringAllocation();

    printf("=== STRUCT DEMO ===\n");
    demoStructAllocation();

    return 0;
}