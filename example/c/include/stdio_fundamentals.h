#ifndef STDIO_FUNDAMENTALS_H
#define STDIO_FUNDAMENTALS_H

#ifndef MAX_ENABLE
#define PI 3.13
#define SQUARE(value) value*value
#define MAX(x , y) (x) < (y) ?  (y) : (x)
#endif

#define COLOR_RED "\x1b[31m"
#define COLOR_GRN "\x1b[32m"
#define COLOR_YLW "\x1b[33m"
#define COLOR_BLE "\x1b[34m"
#define COLOR_WHT "\x1b[37m"
#define COLOR_RST "\x1b[0m"
#define COLOR_BLK "\x1b[30m"
#define COLOR_MGT "\x1b[35m"
#define COLOR_CYN "\x1b[36m"

#define LINE "=================================================================\n"
#define ERROR(X) printf("\n"COLOR_RED"%s"COLOR_RST"\n",X)
#define WARN(X)  printf("\n"COLOR_YLW"%s"COLOR_RST"\n",X)
#define DEBUG(X) printf("\n"COLOR_GRN"%s"COLOR_RST"\n",X)
#define INFO(X)  printf("\n"COLOR_WHT"%s"COLOR_RST"\n",X)

// Enum: state index mapping
typedef enum
{
    STATE_X = 0,
    STATE_Y,
    STATE_Z,
    STATE_ALL
} State_t;

// Struct: klasik kullanım
typedef struct
{
    char name[20];
    int age;
    float weight;
} People_t;

// Union + struct overlay (memory sharing demo)
typedef union
{
    struct
    {
        int x;
        int y;
        int z;
    };

    int state[STATE_ALL]; // aynı memory üzerinden array erişimi
} State_u;

void hello(void);
int add(int a, int b);
void swapValues(int *a, int *b);
int sumArray(int arr[], int size);
int sumVariadic(int count, ...);
int sumRecursive(int arr[], int size);

void handlePrint(float temperature_value, unsigned int device_id);
void handleScanf(void);
void handleSprintf(void);
void handleSscanf(void);
void handleGetchar(void);

void demoTypeConversions(void);
void demoConstantsAndLimits(void);
void demoStaticBehavior(void);

void demoStringInput(void);
void demoStringOperations(void);
void demoStringSearch(void);

void demoStructAccess(void);
void demoPointerAccess(void);
void demoUnionAccess(void);

void demoBitwiseOperations(int a, int b);
void demoShiftOperations(int value);
void demoUnsignedBitwise(void);

void demoFunctionPointers(void);
void demoBasicPointer(void);
void demoConstPointers(void);

#endif // STDIO_FUNDAMENTALS_H