#ifndef STDIO_FUNDAMENTALS_H
#define STDIO_FUNDAMENTALS_H

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

#endif // STDIO_FUNDAMENTALS_H