#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <stdarg.h>

#include "stdio_fundamentals.h"

People_t person_1 = {"Ali", 35, 70.0f};
People_t *person_2 = NULL;

State_u system_state = {1, 2, 4};

// Program başlamadan önce çalışan init fonksiyonu
void __attribute__((constructor)) systemInitializer(void);

// Program bittikten sonra çalışan cleanup fonksiyonu
void __attribute__((destructor)) systemFinalizer(void);

int main(int argc, char *argv[])
{
    (void)argc; // unused
    (void)argv; // unused

    People_t temp_person = {"Mert", 10, 40.0f};
    person_2 = &temp_person;

    int function_selector = 0;

    printf("Select function:\n");
    printf("1 - Print formats\n");
    printf("2 - Scanf input\n");
    printf("3 - Sprintf example\n");
    printf("4 - Sscanf example\n");
    printf("5 - Getchar loop\n");
    printf("6 - Type conversions demo\n");
    printf("7 - Constants and limits demo\n");
    printf("8 - Static behavior demo\n");
    printf("9 - String input demo\n");
    printf("10 - String operations demo\n");
    printf("11 - String search demo\n");
    printf("12 - Struct access demo\n");
    printf("13 - Pointer access demo\n");
    printf("14 - Union access demo\n");
    printf("15 - Bitwise operations demo\n");
    printf("16 - Shift operations demo\n");
    printf("17 - Unsigned bitwise demo\n");
    printf("18 - Function pointers demo\n");
    printf("19 - Basic pointer demo\n");
    printf("20 - Const pointers demo\n");
    printf("Choice: ");

    scanf("%d", &function_selector);
    printf("====================================\n");

    switch (function_selector)
    {
    case 1:
        handlePrint(23.45678f, 42);
        break;
    case 2:
        handleScanf();
        break;
    case 3:
        handleSprintf();
        break;
    case 4:
        handleSscanf();
        break;
    case 5:
        handleGetchar();
        break;
    case 6:
        demoTypeConversions();
        break;
    case 7:
        demoConstantsAndLimits();
        break;
    case 8:
        demoStaticBehavior();
        break;
    case 9:
        demoStringInput();
        break;
    case 10:
        demoStringOperations();
        break;
    case 11:
        demoStringSearch();
        break;
    case 12:
        demoStructAccess();
        break;
    case 13:
        demoPointerAccess();
        break;
    case 14:
        demoUnionAccess();
        break;
    case 15:
        demoBitwiseOperations(18, 10);
        break;
    case 16:
        demoShiftOperations(18);
        break;
    case 17:
        demoUnsignedBitwise();
        break;
    case 18:
        demoFunctionPointers();
        break;
    case 19:
        demoBasicPointer();
        break;
    case 20:
        demoConstPointers();
        break;
    default:
        printf("Invalid selection\n");
        break;
    }

    printf(COLOR_RST LINE);
    printf(COLOR_BLK "Color: Black\n");
    printf(COLOR_RED "Color: Red\n");
    printf(COLOR_GRN "Color: Green\n");
    printf(COLOR_YLW "Color: Yellow\n");
    printf(COLOR_BLE "Color: Blue\n");
    printf(COLOR_MGT "Color: Magenta\n");
    printf(COLOR_CYN "Color: Cyan\n");
    printf(COLOR_WHT "Color: White\n");
    printf(COLOR_RST LINE);
    
    return 0;
}

void systemInitializer(void)
{
    printf("System initialization completed\n"); // program öncesi hazırlık
}

void systemFinalizer(void)
{
    printf("System cleanup completed\n"); // program sonrası temizlik
}

// Fonksiyon implementasyonları
void hello(void)
{
    printf("Hello!\n");
}

int add(int a, int b)
{
    return a + b;
}

// Pointer parametre (call by reference)
void swapValues(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Array parametre kullanımı
int sumArray(int arr[], int size)
{
    int sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }

    return sum;
}

// Variadic function (değişken sayıda parametre)
int sumVariadic(int count, ...)
{
    va_list args;
    va_start(args, count);

    int sum = 0;

    for (int i = 0; i < count; i++)
    {
        sum += va_arg(args, int);
    }

    va_end(args);

    return sum;
}

// Recursive (özyinelemeli / yineleyici) fonksiyon
int sumRecursive(int arr[], int size)
{
    if (size <= 0)
        return 0;

    return arr[size - 1] + sumRecursive(arr, size - 1);
}

void handlePrint(float temperature_value, unsigned int device_id)
{
    printf("[1] %7.3f\n", temperature_value);       // sağa yaslı, toplam 7 karakter, 3 ondalık
    printf("[2] %-7.3f\n", temperature_value);      // sola yaslı, 7 genişlik
    printf("[3] %+2.3f\n", temperature_value);      // işaret göster (+/-)
    printf("[4] %*.*f\n", 2, 3, temperature_value); // dinamik genişlik ve precision
    printf("[5] %o\n", device_id);                  // octal (8'lik taban)
    printf("[6] %x\n", device_id);                  // hex (küçük harf)
    printf("[7] %#04x\n", device_id);               // hex + prefix + padding
    printf("====================================\n");
}

void handleScanf(void)
{
    int user_id;
    float sensor_value;

    printf("Enter user ID and sensor value: ");

    // Return value kontrolü: scanf() beklenen sayıda argüman okuyamazsa EOF veya 0 döndürebilir.
    if (scanf("%d %f", &user_id, &sensor_value) != 2)
    {
        printf("Invalid input format\n"); // beklenen format sağlanmadı
        return;
    }

    printf("User ID: %d\n", user_id);             // ID yazdır
    printf("Sensor Value: %.2f\n", sensor_value); // float formatlı çıktı

    printf("Input processing completed\n");
    printf("====================================\n");
}

// sprintf: veriyi string buffer içine formatlayarak yazar
void handleSprintf(void)
{
    char output_buffer[100];

    int device_id = 42;
    float temperature = 36.567f;

    // formatlı string üretimi (memory içine yazılır)
    sprintf(output_buffer, "DeviceID=%d | Temperature=%.2f", device_id, temperature);

    printf("Formatted String: %s\n", output_buffer); // üretilen string'i yazdır
    printf("====================================\n");
}

// sscanf: string içinden formatlı veri parse eder
void handleSscanf(void)
{
    char input_buffer[] = "DeviceID=42 Temperature=36.57";

    int device_id;
    float temperature;

    // string içinden parse işlemi
    sscanf(input_buffer, "DeviceID=%d Temperature=%f", &device_id, &temperature);

    printf("Parsed Device ID: %d\n", device_id);       // çıkarılan int
    printf("Parsed Temperature: %.2f\n", temperature); // çıkarılan float
    printf("====================================\n");
}

void handleGetchar(void)
{
    int input_char; // getchar int döndürür (EOF kontrolü için)

    printf("Press a key (q to quit): ");

    // getchar() standart input stream üzerinden her çağrıda tek bir byte (char) okur.
    // Kullanıcı birden fazla karakter girip Enter'a bastığında, bu karakterler input buffer'a
    // sıralı şekilde (FIFO) yerleşir ve getchar() her iterasyonda bu buffer'dan sırayla tüketir.
    //
    // Bu nedenle döngü içerisinde kullanıldığında, girilen tüm karakterler tek tek işlenebilir.
    //
    // EOF (End Of File), normal klavye girdisiyle otomatik oluşmaz.
    // Terminal ortamında kullanıcı CTRL + D (Linux/macOS) kombinasyonu
    // ile input stream'i sonlandırır ve getchar() EOF döndürür.
    //
    // Alternatif olarak program bir pipe veya file redirection ile çalıştırıldığında EOF otomatik oluşur:
    // `cat file.txt | ./program` Bu senaryoda getchar(), dosya içeriğinin sonuna ulaştığında EOF üretir.
    //
    // Bu döngü, input stream aktif olduğu sürece çalışmaya devam eder.
    while ((input_char = getchar()) != EOF)
    {                                         // Ya da '\n' ile sınırlandırılabilir
        printf("Received: %c\n", input_char); // girilen karakteri yazdır

        if (input_char == 'q') // çıkış koşulu
        {
            printf("Exit command received\n");
            break;
        }

        printf("Press a key (q to quit): ");
    }

    printf("Input session closed\n");
    printf("====================================\n");
}

// ASCII ve string dönüşüm demo
void demoTypeConversions(void)
{
    // __attribute__((unused)) ile tanımlanan değişken, derleyici tarafından
    // kullanılmayan bir değişken olarak işaretlenir. Hata vermeden derlenmesini sağlar.
    char ascii_char __attribute__((unused)) = 65; // 65 ASCII -> 'A'
    const char *string_float = "15.48";
    const char *string_int = "253";

    char char_array[4] = {'A', 65, 'B', 'D'};

    int parsed_int = atoi(string_int);       // string -> int
    float parsed_float = atof(string_float); // string -> float

    printf("Parsed int: %d\n , %ld byte", parsed_int, sizeof(parsed_int));
    printf("Parsed float: %.2f\n, %ld byte", parsed_float, sizeof(parsed_float));

    printf("Char array: %c %c %c %c\n",
           char_array[0], char_array[1], char_array[2], char_array[3]);

    printf("====================================\n");
}

// Sabitler ve veri tip limitleri
void demoConstantsAndLimits(void)
{
    const int fixed_value = 20;

    printf("Const value: %d\n", fixed_value);

    printf("INT   range: [%d, %d]\n", INT_MIN, INT_MAX);
    printf("CHAR  range: [%d, %d]\n", SCHAR_MIN, SCHAR_MAX);

    printf("FLOAT range: [%e, %e]\n", FLT_MIN, FLT_MAX);
    printf("DOUBLE range: [%e, %e]\n", DBL_MIN, DBL_MAX);

    printf("====================================\n");
}

// static vs local değişken davranışı
void demoStaticBehavior(void)
{
    int normal_counter = 0;
    static int static_counter = 0;

    normal_counter++;
    static_counter++;

    printf("normal_counter = %d | static_counter = %d\n",
           normal_counter, static_counter);
}

// Kullanıcı input ve temel string davranışı
void demoStringInput(void)
{
    char raw_chars[] = {'A', 'B', 'C', '\0'}; // null-terminated hale getirildi
    char user_name[30];

    const char *country_list[3] = {"Ankara", "Antalya", "Bursa"};

    printf("Raw string output: %s\n", raw_chars); // güvenli kullanım
    printf("Enter your name: ");

    scanf("%29s", user_name); // buffer overflow önlemi

    printf("Name: %s\n", user_name);
    puts(country_list[1]);

    printf("====================================\n");
}

// strcat / strcpy / strcmp davranışları
void demoStringOperations(void)
{
    char word1[50] = "asdfgh";
    char word2[20] = "zxcvbn";

    printf("word1: %s | word2: %s\n", word1, word2);

    strcat(word1, word2); // word2 → word1 sonuna eklenir
    printf("After strcat -> word1: %s\n", word1);

    strcpy(word2, word1); // word1 → word2 kopyalanır
    printf("After strcpy -> word2: %s\n", word2);

    if (strcmp(word1, word2) == 0)
        printf("Strings are equal\n");
    else
        printf("Strings are not equal\n");

    printf("====================================\n");
}

// strchr / strrchr davranışı
void demoStringSearch(void)
{
    char text[] = "asdfghmzxcm";

    char *first_match = strchr(text, 'm'); // ilk 'm'
    char *last_match = strrchr(text, 'm'); // son 'm'

    if (first_match)
        printf("First match from m: %s\n", first_match);

    if (last_match)
        printf("Last match from m: %s\n", last_match);

    printf("====================================\n");
}

// struct erişim yöntemleri
void demoStructAccess(void)
{
    printf("Name: %s | Age: %d | Weight: %.2f\n",
           person_1.name, person_1.age, person_1.weight);

    printf("====================================\n");
}

// pointer ile struct erişimi
void demoPointerAccess(void)
{
    printf("Name (->): %s\n", person_2->name);
    printf("Name (*.): %s\n", (*person_2).name);

    printf("====================================\n");
}

// union memory overlay davranışı
void demoUnionAccess(void)
{
    printf("Direct access -> x: %d y: %d z: %d\n",
           system_state.x, system_state.y, system_state.z);

    printf("Array access  -> x: %d y: %d z: %d\n",
           system_state.state[STATE_X],
           system_state.state[STATE_Y],
           system_state.state[STATE_Z]);

    printf("====================================\n");
}

void demoBitwiseOperations(int a, int b)
{
    int results[6];

    results[0] = a << 1; // left shift
    results[1] = a >> 1; // right shift
    results[2] = a & b;  // AND
    results[3] = a | b;  // OR
    results[4] = a ^ b;  // XOR
    results[5] = ~a;     // NOT

    const char *labels[] = {
        "a << 1",
        "a >> 1",
        "a & b",
        "a | b",
        "a ^ b",
        "~a"};

    printf("Bitwise operations (a=%d, b=%d)\n", a, b);

    for (int i = 0; i < 6; i++)
    {
        printf("%-6s = %d\n", labels[i], results[i]);
    }

    printf("====================================\n");
}

// Shift demo (loop tabanlı)
void demoShiftOperations(int value)
{
    printf("Shift operations (value=%d)\n", value);

    for (int i = 1; i <= 2; i++)
    {
        printf("value << %d = %d\n", i, value << i);
    }

    for (int i = 1; i <= 2; i++)
    {
        printf("value >> %d = %d\n", i, value >> i);
    }

    printf("====================================\n");
}

// unsigned bitwise demo
void demoUnsignedBitwise(void)
{
    unsigned int a = 18; // 00010010
    unsigned int b = 10; // 00001010

    unsigned int and_r = a & b;
    unsigned int or_r = a | b;
    unsigned int xor_r = a ^ b;
    unsigned int not_r = (unsigned char)~a;

    printf("Unsigned bitwise operations\n");
    printf("(a & b) = %u\n", and_r);
    printf("(a | b) = %u\n", or_r);
    printf("(a ^ b) = %u\n", xor_r);
    printf("~a      = %u\n", not_r);

    printf("====================================\n");
}

// Function pointer demo
void demoFunctionPointers(void)
{
    void (*funcPtr)(void) = hello; // void fonksiyon pointer
    int (*addPtr)(int, int) = add; // int dönen fonksiyon pointer

    funcPtr(); // indirect call
    int result = addPtr(3, 5);

    printf("Add result: %d\n", result);
    printf("====================================\n");
}

// Basic pointer demo
void demoBasicPointer(void)
{
    int value = 10;
    int *ptr = &value;

    printf("ptr address: %p | value: %d\n", (void *)ptr, *ptr);

    printf("====================================\n");
}

// const pointer davranışları
void demoConstPointers(void)
{
    int x = 10;
    int y = 20;

    const int *ptr1 = &x; // pointer değişebilir, değer değişmez
    ptr1 = &y;            // OK

    int *const ptr2 = &x; // pointer sabit, değer değişebilir
    *ptr2 = 15;           // OK

    printf("ptr1 (const value ptr): %d\n", *ptr1);
    printf("ptr2 (const ptr): %d\n", *ptr2);

    printf("====================================\n");
}