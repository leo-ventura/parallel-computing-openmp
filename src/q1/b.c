#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char *argv[])
{
    int i, n, ipntp, ipnt, ii, k, t, r;
    int *x, *v, *w, *u, *z, *y;
    n = 4;
    // ii = n;
    // ipntp = 0;
    // do
    // {
    //     printf("ii=%d\n", ii);
    //     ipnt = ipntp;
    //     ipntp += ii;
    //     ii /= 2;

    //     i = ipntp - 1;
    //     for (k = ipnt + 1; k < ipntp; k = k + 2)
    //     {
    //         i++;
    //         printf("r: %d %d %d w: %d\n", k-1, k, k+1, i);
    //         // x[i] = x[k] - v[k] * x[k - 1] - v[k + 1] * x[k + 1];
    //     }
    // } while (ii > 0);

    // for (i = 1; i < n; i++)
    // {
    //     for (k = 0; k < i; k++)
    //     {
    //         printf("r: %d w: %d\n", (i - k) - 1, i);
    //         // w[i] += b[k][i] * w[(i - k) - 1];
    //     }
    // }

    for (k = 0; k < n; k++)
    {
        x[k] = u[k] + r * (z[k] + r * y[k]) +
               t * (u[k + 3] + r * (u[k + 2] + r * u[k + 1]) +
                t * (u[k + 6] + r * (u[k + 5] + r * u[k + 4])));
    }
}