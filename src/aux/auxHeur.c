#include <stdlib.h>

/* Função auxiliar de comparação, para ordenar os índices em relação a soma de distâncias crescente
        Parâmetros:
                *a: índice do valor a
                *b: índice do valor b
                *c: array com somatório das distancias dos n clientes para as m facilidades
        Retorno:
                -1: se c[a] < c[b]
                1: se c[a] > c[b]
                0: se c[a] == c[b]
*/
int comparaLongDouble(const void *a, const void *b, void *c) {
        long double *sL = (long double*)c;
        int indcA = *(int*)a;
        int indcB = *(int*)b;

        if (sL[indcA] < sL[indcB]) { return -1; }
        if (sL[indcA] > sL[indcB]) { return 1; }

        return 0;
}

/* Retorna o índice do local m cuja soma das distâncias para os n clientes é a menor
        Parâmetros:
                D[]: Matriz de distâncias
                n: número de clientes
                m: número de locais possíveis
        Retorno:
                indicesClientes[0]: índice do cliente cujo somátorio das distâncias é o menor
*/
int menorSomaDistancias(double D[], int n, int m) {
        long double somaColunas[m];
        int indicesLocais[m];

        for (int i = 0; i < m; i++) {
                somaColunas[i] = 0;

                for(int j = 0; j < n; j++) { somaColunas[i] += D[(j * m) + i]; }

                indicesLocais[i] = i;
        }

        qsort_r(indicesLocais, m, sizeof(int), comparaLongDouble, somaColunas);

        return indicesLocais[0];
}

/* Fase onde se adicionam elementos à F enquanto a soma das distâncias diminui
        Parâmetros:
                D[]: matriz de distâncias
                C[]: custos para construir em cada local
                F[]: conjunto de facilidades abertas
                n: número de clientes
*/
void aumentaF(double D[], double C[], bool F[], int n, int m) {
        int numFacilidadesAbertas = tamanhoSubConjunto(F, m);
        bool somaCustosDistanciasMelhora = true;

        if (numFacilidadesAbertas == 0) {
                F[menorSomaDistancias(D, n, m)] = true;
                numFacilidadesAbertas++;
        }

        while(somaCustosDistanciasMelhora) {
                long double somaCustosDistanciasAntiga = somaCustosDistancias(D, C, F, n, m);
                bool tempMelhorQueAntiga = false;
                int indiceCustosDistanciasMinimos;

                for (int i = 0; i < m; i++) {
                        if (!F[i]) {
                                bool Ftemp[m];
                                for (int j = 0; j < m; j++) { Ftemp[j] = F[j]; }
                                Ftemp[i] = true;

                                long double somaCustosDistanciasTemp = somaCustosDistancias(D, C, Ftemp, n, m);

                                if (somaCustosDistanciasTemp < somaCustosDistanciasAntiga) {
                                        indiceCustosDistanciasMinimos = i;
                                        somaCustosDistanciasAntiga = somaCustosDistanciasTemp;
                                        tempMelhorQueAntiga = true;
                                }
                        }
                }

                if (tempMelhorQueAntiga) {
                        F[indiceCustosDistanciasMinimos] = true;
                } else {
                        somaCustosDistanciasMelhora = false;
                }
        }
}
