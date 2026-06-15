#pragma once 

#define MAX_BITS 32

/*
 * ARMSTRONG NUMBER:
 * n basamaklı sayının her basamağının n'inci kuvvetleri 
 * toplamı sayıya eşitse.
 */
int isArmstrongNumber(int number);

/*
 * PALINDROME NUMBER:
 * Ters çevrildiğinde aynı kalan sayı.
 */
int isPalindrome(int number);

/*
 * REVERSE NUMBER:
 * Sayıyı ters çevirir.
 */
int reverseNumber(int number);

/*
 * DECIMAL TO BINARY:
 * Sayıyı ikili tabana çevirir.
 */
void decimalToBinary(int number);

/*
 * FACTORIAL:
 * Sayının faktöriyelini hesaplar.
 */
int factorial(int number);

/*
 * PRINT FACTORIAL:
 * Sayının faktöriyelini yazdırır.
 */
void printFactorial(int number);

/*
 * FIBONACCI (ITERATIVE):
 * O(n) time complexity, O(1) space complexity.
 * Embedded ve real-time sistemlerde tercih edilir.
 * Sayıları sırayla ekrana basar.
 */
void fibonacci(int number);

/*
 * FIBONACCI (RECURSIVE):
 * Recursive helper + wrapper pattern ile implement edilmiştir.
 * Stack kullanımı vardır, iteratif versiyona göre daha maliyetlidir.
 * Eğitim ve algoritma gösterimi için uygundur.
 */
void fibonacciRecursion(int number);


/*
 * SEQUENTIAL SEARCH:
 * O(n) time complexity.
 * Unsorted array üzerinde çalışır.
 * İlk eşleşen index’i döndürür, bulunamazsa -1.
 */
int sequentialSearch(int arr[], int size, int search);

/*
 * BINARY SEARCH:
 * O(log n) time complexity.
 * SADECE sorted array üzerinde çalışır.
 * Bulunamazsa -1 döndürür.
 *
 * NOTE:
 * Precondition: arr must be sorted (ascending).
 */
int binarySearch(int arr[], int left, int right, int search);

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
void swapWithArithmetic(int *lhs, int *rhs);

/*
 * SAFE SWAP (TEMP VARIABLE)
 * En güvenli ve en yaygın kullanılan yöntemdir.
 * Compiler optimizasyonları zaten bunu optimize eder.
 */
void swapWithTemp(int *lhs, int *rhs);