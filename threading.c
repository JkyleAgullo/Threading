// Define header files
#include <stdio.h>
#include <pthread.h>
#include <math.h>

//Define max values
#define FIB_NUM 10
#define SQUARES_NUM 10
#define SORT_NUM_SIZE 5

// Define struct for Fibonacci Sequence
typedef struct { 
    pthread_t thread;
    int num;
    int fib_sequence[FIB_NUM];
} Fib;

// Define struct for Squares
typedef struct {
    pthread_t thread;
    int num;
    int squares[SQUARES_NUM];
} Squares;

// Define struct for Sorting Numbers 
typedef struct {
    pthread_t thread;
    int numbers[SORT_NUM_SIZE];
} SortNum;

// Define function for every thread
void* runFib(void* arg);
void* runSquares(void* arg);
void* runSortNum(void* arg);

void* runFib(void* arg) {
    Fib* fib = (Fib*)arg;
    int num = fib->num;

    int a = 0;
    int b = 1;
    int i, fibo;

    fib->fib_sequence[0] = a;
    fib->fib_sequence[1] = b;

    for (i = 2; i < num; i++) {
        fibo = a + b;
        a = b;
        b = fibo;
        fib->fib_sequence[i] = fibo;
    }

    pthread_exit(NULL);
}

void* runSquares(void* arg) {
    Squares* squares = (Squares*)arg;
    int num = squares->num;
    int i, current, square;

    for (i = 0, current = 1; i < num; i++, current++) {
        square = current * current;
        squares->squares[i] = square;
    }

    pthread_exit(NULL);
}

void* runSortNum(void* arg) {
    SortNum* sortnum = (SortNum*)arg;
    int temp, i, j;

    for (i = 0; i < SORT_NUM_SIZE - 1; i++) {
        for (j = i + 1; j < SORT_NUM_SIZE; j++) {
            if (sortnum->numbers[i] > sortnum->numbers[j]) {
                temp = sortnum->numbers[i];
                sortnum->numbers[i] = sortnum->numbers[j];
                sortnum->numbers[j] = temp;
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    Fib fthread;
    fthread.num = FIB_NUM;

    Squares sthread;
    sthread.num = SQUARES_NUM;

    SortNum snthread;
    snthread.numbers[0] = 5;
    snthread.numbers[1] = 4;
    snthread.numbers[2] = 3;
    snthread.numbers[3] = 2;
    snthread.numbers[4] = 1;

    pthread_create(&fthread.thread, NULL, runFib, &fthread);
    pthread_create(&sthread.thread, NULL, runSquares, &sthread);
    pthread_create(&snthread.thread, NULL, runSortNum, &snthread);

    pthread_join(fthread.thread, NULL);
    pthread_join(sthread.thread, NULL);
    pthread_join(snthread.thread, NULL);

    // Print Fibonacci sequence
    printf("Fibonacci Series to %d terms:\n\t", fthread.num);
    for (int i = 0; i < fthread.num; i++) {
        printf("%d ", fthread.fib_sequence[i]);
    }
    printf("\n");

    // Print squares
    printf("Squares up to %d:\n\t", sthread.num);
    for (int i = 0; i < sthread.num; i++) {
        printf("%d ", sthread.squares[i]);
    }
    printf("\n");

    // Print sorted numbers
    printf("Sorted Numbers:\n\t");
    for (int i = 0; i < SORT_NUM_SIZE; i++) {
        printf("%d ", snthread.numbers[i]);
    }
    printf("\n");

    return 0;
}
