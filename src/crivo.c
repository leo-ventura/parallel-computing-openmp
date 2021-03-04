#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define NUM_THREADS 1

int main(int argc, char *argv[]) {
    long long n;
    int raizN;
    double inicio, fim;
    long long primos = 0;
    int *array; // 0 = é primo. 1 = não é primo

    omp_set_num_threads(NUM_THREADS);

    if (argc < 2) {
        printf("Entre com o valor de n.\n");
        return 1;
    }
    else {
        n = strtol(argv[1], (char**) NULL, 10); 
    }


    array = (int*) calloc(n, sizeof(int)); 
    
    array[0] = 1;
    array[1] = 1;

    raizN = ((int) sqrt(n));

    inicio = omp_get_wtime();
    
    for (long long i = 2; i <= raizN; i++) {
        if (array[i] == 0) {
            #pragma omp parallel for schedule(static) // static, pois todos terão a mesma complexidade
            for (long long j = 2*i; j < n; j+=i) {
                #pragma omp atomic write
                array[j] = 1;
            }
        }
    }


    #pragma omp parallel for reduction(+:primos)
    for (long long i = 0; i < n; i++) {
        if (array[i] == 0)
            primos++;
    }

    fim = omp_get_wtime();

    printf("Threads: %d\tTempo de execução: %.3f\tN: %lld\tPrimos: %lld\n", NUM_THREADS, fim-inicio, n, primos);
}