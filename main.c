#include <stdio.h>
#include <omp.h>

int main() {
    long long int numero = 0;

    while(numero < 1000000000)
    {
        printf("Digite um numero maior que 1 bilhão");
        scanf("%lld", &numero);
    }

    long long int soma1 = 0;
    #pragma omp parallel shared(numero) reduction(+:soma1)
    {
        #pragma omp for
        for (long long int i = 1; i <= numero; i++) {
            if (numero % i == 0) {
                #pragma omp critical
                {
                    soma1 += i;
                }
            }
        }
    }

    long long int soma2 = 0;
    #pragma omp parallel for reduction(+:soma2)
    for (long long int i = 1; i <= numero; i++) {
        if (numero % i == 0) {
            soma2 += i;
        }
    }

    long long int soma3 = 0;
    #pragma omp parallel for reduction(+:soma3) schedule(dynamic)
    for (long long int i = 1; i <= numero; i++) {
        if (numero % i == 0) {
            soma3 += i;
        }
    }

    printf("Soma Regiao Critica: %lld\n", soma1);
    printf("Soma For estatico: %lld\n", soma2);
    printf("Soma For dinamico: %lld\n", soma3);

    return 0;
}
