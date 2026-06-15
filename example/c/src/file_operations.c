#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DB_FILE "car.db"
#define TXT_FILE "car.txt"

typedef enum
{
    AUTOMATIC = 0,
    MANUAL = 1
} Gear_t;

typedef struct
{
    char brand[30];
    int year;
    float price;
    Gear_t gear;
} Car_t;

// ================= FILE HELPERS =================

// fopen wrapper:
// - fopen NULL dönebilir (dosya yok, permission yok, path hatası)
// - production sistemlerde her file operation kontrol edilmelidir
FILE *safeOpen(const char *filename, const char *mode)
{
    FILE *fp = fopen(filename, mode);

    if (!fp)
    {
        // perror sistem error mesajını errno üzerinden basar
        // debugging için kritik bir noktadır
        perror("File open error");
        exit(EXIT_FAILURE);
    }

    return fp;
}

// ================= USER INPUT =================

// struct return etmek stack üzerinde güvenlidir
// ancak büyük structlarda copy maliyeti göz önüne alınmalıdır
Car_t createCar(void)
{
    Car_t car;

    printf("\nEnter car information:\n");

    // %29s -> buffer overflow prevention
    // C'de scanf en riskli fonksiyonlardan biridir
    printf("Brand: ");
    scanf("%29s", car.brand);

    printf("Year: ");
    scanf("%d", &car.year);

    printf("Price: ");
    scanf("%f", &car.price);

    // enum -> int cast:
    // burada tip güvenliği compile-time değil runtime sağlanır
    printf("Gear (0=AUTOMATIC, 1=MANUAL): ");
    scanf("%d", (int *)&car.gear);

    return car;
}

// ================= BINARY WRITE =================

void writeBinaryDB(void)
{
    FILE *fp = safeOpen(DB_FILE, "wb");

    int count;

    printf("How many cars? ");
    scanf("%d", &count);

    // metadata yazıyoruz:
    // bu çok kritik bir pattern:
    // -> file format versioning / header mantığı
    fwrite(&count, sizeof(int), 1, fp);

    for (int i = 0; i < count; i++)
    {
        Car_t car = createCar();

        // binary write:
        // struct memory layout direkt diske yazılır
        // risk: endian + padding + compiler alignment bağımlılığı
        fwrite(&car, sizeof(Car_t), 1, fp);
    }

    fclose(fp);

    printf("Binary DB saved.\n");
}

// ================= BINARY READ =================

void readBinaryDB(void)
{
    FILE *fp = safeOpen(DB_FILE, "rb");

    int count = 0;

    // metadata read:
    // format bozulursa burada crash/garbage veri riski vardır
    fread(&count, sizeof(int), 1, fp);

    // dynamic allocation:
    // burada kritik nokta: count kontrol edilmezse malloc overflow riski oluşur
    Car_t *cars = malloc(sizeof(Car_t) * count);

    if (!cars)
    {
        printf("Memory allocation failed\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fread(cars, sizeof(Car_t), count, fp);

    fclose(fp);

    printf("\n=== BINARY DB OUTPUT ===\n");

    for (int i = 0; i < count; i++)
    {
        printf("Car %d\n", i + 1);
        printf("Brand: %s\n", cars[i].brand);
        printf("Year: %d\n", cars[i].year);
        printf("Price: %.2f\n", cars[i].price);

        // enum display:
        // burada implicit mapping kullanılıyor
        printf("Gear: %s\n\n", cars[i].gear ? "MANUAL" : "AUTOMATIC");
    }

    free(cars);

    // free sonrası pointer kullanılmamalıdır (dangling pointer)
}

// ================= TEXT FILE WRITE =================

void writeTextFile(void)
{
    FILE *fp = safeOpen(TXT_FILE, "w");

    Car_t car = createCar();

    // text format:
    // human-readable ama parsing hataya açık
    fprintf(fp, "%s %d %.2f %d\n",
            car.brand,
            car.year,
            car.price,
            car.gear);

    fclose(fp);

    printf("Text file saved.\n");
}

// ================= TEXT FILE READ =================

void readTextFile(void)
{
    FILE *fp = safeOpen(TXT_FILE, "r");

    Car_t car;

    // fscanf:
    // whitespace parsing yapar
    // input validation yapılmazsa format break olabilir
    fscanf(fp, "%29s %d %f %d",
           car.brand,
           &car.year,
           &car.price,
           (int *)&car.gear);

    fclose(fp);

    printf("\n=== TEXT FILE OUTPUT ===\n");
    printf("Brand: %s\nYear: %d\nPrice: %.2f\nGear: %s\n",
           car.brand,
           car.year,
           car.price,
           car.gear ? "MANUAL" : "AUTOMATIC");
}

// ================= MAIN =================

int main(void)
{
    int choice;

    printf("\nFILE I/O DEMO SYSTEM\n");
    printf("1 - Write Binary DB\n");
    printf("2 - Read Binary DB\n");
    printf("3 - Write Text File\n");
    printf("4 - Read Text File\n");
    printf("Choice: ");

    scanf("%d", &choice);

    // switch-case:
    // compile-time değil runtime dispatch mekanizmasıdır
    switch (choice)
    {
    case 1:
        writeBinaryDB();
        break;

    case 2:
        readBinaryDB();
        break;

    case 3:
        writeTextFile();
        break;

    case 4:
        readTextFile();
        break;

    default:
        printf("Invalid selection\n");
        break;
    }

    return 0;
}