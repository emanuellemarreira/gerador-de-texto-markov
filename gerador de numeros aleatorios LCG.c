//livro: Numerical Recipes, 3rd ed. (Press et. al., 2007)
//Capitulo: 7.1.2 Recommended methods for use in combined generators
//Algoritmo: C - LCG modulo 2^64


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>  // Para PRIu64
#include <time.h>

//parâmetros C1 do LCG
#define A 3935559000370003845ULL
#define C 2691343689449507681ULL

#define NUM_GERACOES 4

//função inline para utilizar registradores
static inline uint64_t lcg(uint64_t *x) {
    *x = A * (*x) + C;
    return *x;
}

int main() {
    int j;
    uint64_t x = time(NULL); 
    float resultados[100];
    for(j = 0; j < 100; j++){
        uint64_t rand_num = lcg(&x);
        resultados[j] = (rand_num >> 11) * (1.0 / 9007199254740992.0); //normalizar o valor gerado pelo LCG para que ele caia no intervalo [0, 1]
    }
    FILE *arquivo = fopen("probabilidades_gerador.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    for (int i = 0; i < 100; i++) {
        fprintf(arquivo, "%.3f\n", resultados[i]);
    }
    fclose(arquivo);
    return 0;
}
