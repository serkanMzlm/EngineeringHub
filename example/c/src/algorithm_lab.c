#include <stdio.h>
#include <stdlib.h>

#include "algorithm_lab.h"

/*
 * NOT:
 * Global array kullanımı küçük örneklerde kabul edilir
 * ancak production seviyede data dependency yaratır.
 * Fonksiyonlara parametre olarak geçmek daha doğrudur.
 */

int array[] = {1, 2, 3, 4, 5, 12, 36, 12, 298, 76, 71, 23};

// ================= MAIN =================
int main(void)
{
    int number;

    printf("Input: ");
    scanf("%d", &number);

    decimalToBinary(number);

    printf("%sArmstrong\n",
           isArmstrongNumber(number) ? "" : "Not ");

    printf("%sPalindrome number.\n",
           isPalindrome(number) ? "" : "Not ");

    return 0;
}

// ARMSTRONG
int isArmstrongNumber(int number)
{
    int original = number;
    int sum = 0;

    while (number > 0)
    {
        int digit = number % 10;
        sum += digit * digit * digit;
        number /= 10;
    }

    return (sum == original);
}

// PALINDROME
int isPalindrome(int number)
{
    return number == reverseNumber(number);
}

// REVERSE
int reverseNumber(int number)
{
    int reverse = 0;

    while (number > 0)
    {
        int digit = number % 10;
        reverse = reverse * 10 + digit;
        number /= 10;
    }

    return reverse;
}

void decimalToBinary(int number)
{
    static int binary[MAX_BITS]; 
    int i = 0;

    // Edge case:
    // number = 0 ise loop çalışmaz → özel kontrol gerekir
    if (number == 0)
    {
        printf("Binary: 0\n");
        return;
    }

    while (number > 0 && i < MAX_BITS)
    {
        binary[i++] = number % 2;
        number /= 2;
    }

    printf("Binary: ");

    // LSB → MSB ters basılır
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%d", binary[j]);
    }

    printf("\n");
}

// ================= FACTORIAL (RECURSIVE - RETURN VERSION) =================
int factorial(int number)
{
    // Base case:
    // recursion'ın durma noktası olmazsa stack overflow oluşur
    if (number <= 1)
        return 1;

    // recursive relation:
    // n! = n * (n-1)!
    return number * factorial(number - 1);
}


// ================= FACTORIAL PRINT (RECURSIVE TRACE) =================
void printFactorial(int number)
{
    // Base case:
    // en küçük parçaya inmeden recursion bitmez
    if (number <= 0)
    {
        printf("1");
        return;
    }

    // recursive descent (önce zinciri kur)
    printf("%d", number);

    if (number > 1)
        printf(" * ");

    printFactorial(number - 1);
}

// ================= ITERATIVE FIBONACCI =================
void fibonacci(int number)
{
    int a = 0;
    int b = 1;
    int next;

    // NOTE:
    // Fibonacci iterative çözüm O(n) ve stack kullanmaz
    // Embedded sistemlerde tercih edilen yöntem budur

    for (int i = 0; i < number; i++)
    {
        printf("%d", a);

        if (i < number - 1)
            printf(", ");

        next = a + b;
        a = b;
        b = next;
    }

    printf("\n");
}


// ================= RECURSIVE FIBONACCI =================
static int fibRecursiveHelper(int number, int *a, int *b)
{
    // Base case:
    if (number == 0)
        return 0;

    int next = (*a) + (*b);

    printf("%d", *a);

    if (number > 1)
        printf(", ");

    *a = *b;
    *b = next;

    return fibRecursiveHelper(number - 1, a, b);
}


// Wrapper function (API clean)
void fibonacciRecursion(int number)
{
    int a = 0;
    int b = 1;

    // NOTE:
    // static/global state yerine stack-based local state kullanıldı
    fibRecursiveHelper(number, &a, &b);

    printf("\n");
}

// ================= SEQUENTIAL SEARCH =================
int sequentialSearch(int arr[], int size, int search)
{
    // Linear search:
    // O(n) complexity
    // unsorted data üzerinde çalışır
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == search)
        {
            printf("Found at index %d\n", i);
            return i;
        }
    }

    return -1;
}


// ================= BINARY SEARCH =================
int binarySearch(int arr[], int left, int right, int search)
{
    // IMPORTANT:
    // binary search ONLY works on sorted arrays

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == search)
            return mid;

        if (arr[mid] < search)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}


// ================= BUBBLE SORT =================
void bubbleSort(int arr[], int n)
{
    // Bubble sort:
    // O(n^2) complexity
    // educational purpose only (not production)

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            // ASCENDING SORT (binary search requirement)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/*
 * SAFE SWAP (TEMP VARIABLE)
 * En güvenli ve en yaygın kullanılan yöntemdir.
 * Compiler optimizasyonları zaten bunu optimize eder.
 */
void swapWithTemp(int *lhs, int *rhs)
{
    int temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}


/*
 * ARITHMETIC SWAP (RISKY APPROACH)
 *
 * NOT:
 * Bu yöntem integer overflow riski taşır.
 * Özellikle embedded / high-range integer sistemlerde
 * undefined behavior oluşturabilir.
 *
 * Genellikle production kodda önerilmez.
 */
void swapWithArithmetic(int *lhs, int *rhs)
{
    *lhs = *lhs + *rhs;
    *rhs = *lhs - *rhs;
    *lhs = *lhs - *rhs;
}