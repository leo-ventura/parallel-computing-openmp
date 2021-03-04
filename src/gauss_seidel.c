#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define COLUMNS    3000
#define ROWS       3000
#define TEMP_BORDA 20
#define MAX_TEMP_ERROR 0.01

double Anew[ROWS+2][COLUMNS+2];
double A[ROWS+2][COLUMNS+2];

void iniciar();

int main(int argc, char *argv[]) { /* jacobi_seq.c  */
int i, j;
int max_iterations= 2<<10;
int iteration = 1;
double dt = 100;

    iniciar();
    double start_time = omp_get_wtime();
    while (dt > MAX_TEMP_ERROR && iteration <= max_iterations ) {
        #pragma omp parallel for collapse(2)
        for (i = 1; i <= ROWS; i++) 
            for (j = 1; j <= COLUMNS; j++) {
                Anew[i][j] = 0.25 * (A[i+1][j] + 
                    A[i-1][j] + A[i][j+1] + A[i][j-1]);
            }
        dt = 0.0;

        #pragma omp parallel for collapse(2)
        for (i = 1; i <= ROWS; i++)
            for (j = 1; j <= COLUMNS; j++) {
                dt = fmax( fabs(Anew[i][j]-A[i][j]), dt);
                A[i][j] = Anew[i][j];
            }

        iteration++;
    }
    double end_time = omp_get_wtime();
    printf("Demorou %.4f segundos para executar o algoritmo.", end_time - start_time);
    printf(" Erro maximo na iteracao %d era %f\n", iteration-1, dt);
    return(0);
}

void iniciar(){
    int i,j;

    // preenche a matriz toda com 0
    for (i = 0; i <= ROWS+1; i++) {
         for (j = 0; j <= COLUMNS+1; j++) {
              A[i][j] = 0.0;
         }
    }

    // para cada linha, preenche primeira posição com temperatura 0
    // e última com calor aumentando gradativamente
    for (i = 0; i <= ROWS+1; i++) {
        //  A[i][0] = 0.0;
        //  A[i][COLUMNS+1] = (100.0/ROWS)*i;
        A[i][0] = TEMP_BORDA;
        A[i][COLUMNS+1] = TEMP_BORDA;
    }

    // para cada coluna, preenche primeira posição com temperatura 0
    // e última com calor aumentando gradativamente
    for (j = 0; j <= COLUMNS+1; j++) {
         A[0][j] = 0.0;
         A[ROWS+1][j] = (100.0/COLUMNS)*j;
    }
}