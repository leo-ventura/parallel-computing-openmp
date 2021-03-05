#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define COLUMNS    3000
#define ROWS       3000
#define TEMP_BORDA 20
#define TEMP_INICIAL 20
#define MAX_TEMP_ERROR 0.01

double Anew[ROWS+2][COLUMNS+2];
double A[ROWS+2][COLUMNS+2];

void iniciar();

int main(int argc, char *argv[]) {
int i, j;
int max_iterations= 1<<10;
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

    // preenche a placa de calor toda com a temperatura inicial
    for (i = 0; i <= ROWS+1; i++) {
        for (j = 0; j <= COLUMNS+1; j++) {
            A[i][j] = TEMP_INICIAL;
        }
    }

    // Fonte de calor localizada no ponto 800x800
    A[800][800] = 100.0;
}