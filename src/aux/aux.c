#include <float.h>
#include <stdbool.h>

/* Retorna o local em F mais próximo de um determinado cliente
        Parâmetros:
                D[]: matriz de distâncias
                F[]: conjunto de facilidades
                m: numero de locais possíveis
                j: cliente
        Retorno:
                lMPEF: local mais próximo n em F
*/
int localMaisPertoEmF(double D[], bool F[], int m, int j) {
        int lMPEF;
        double dMin = DBL_MAX;

        for (int i = 0; i < m; i++) {
                if (F[i]) {
                        int indice = (j * m) + i;

                        if (D[indice] < dMin) {
                                dMin = D[indice];
                                lMPEF = i;
                        }
                }
        }

        return lMPEF;
}

/* Retorna o tamanho de um subconjunto de elementos recebido
        Parâmetros:
                B[]: lista de booleanos representando subconjunto
                tam: tamanho do conjunto original
        Retorno:
                nFa: número de facilidades abertas
*/
int tamanhoSubConjunto(bool B[], int tam) {
        int tamS = 0;

        for (int i = 0; i < tam; i++) { if (B[i]) { tamS++;} }

        return tamS;
}

/* Calcula o custo total da solução, que é a soma das distâncias dos n clientes até os locais em F mais os custos de construção nos tamF locais
        Parâmetros:
                D[]: matriz de distâncias
                C[]: custo de construção em cada local m
                F[]: conjunto de facilidades
                n: quantidade de clientes
                m: quantidade de locais possíveis
        Retorno:
                sD: soma das distâncias dos n clientes para a facilidade mais próxima em F
*/
long double somaCustosDistancias(double D[], double C[], bool F[], int n, int m) {
        long double sCD = 0.;

        for (int i = 0; i < m; i++) {
                if (F[i]) { sCD += C[i]; }
        }

        for (int j = 0; j < n; j++) {
                sCD += D[(j * m) + localMaisPertoEmF(D, F, m, j)];
        }

        return sCD;
}

/* Fase onde se removem elementos de F enquanto a soma das distâncias diminui
        Parâmetros:
                D[]: matriz de distâncias
                C[]: custos para construir em cada local
                F[]: conjunto de facilidades abertas
                n: número de clientes
                n: número de locais possíveis
*/
void diminuiF(double D[], double C[], bool F[], int n, int m) {
        int numFacilidadesAbertas = tamanhoSubConjunto(F, m);

        bool somaCustosDistanciasMelhora = true;

        if (numFacilidadesAbertas > 1) {
                while (somaCustosDistanciasMelhora) {
                        long double somaCustosDistanciasAntiga = somaCustosDistancias(D, C, F, n, m);
                        bool tempMelhorQueAntiga = false;
                        int indiceRemovido;

                        for (int i = 0; i < m; i++) {
                                if (F[i]) {
                                        bool Ftemp[m];
                                        for (int j = 0; j < m; j++) { Ftemp[j] = F[j]; }
                                        Ftemp[i] = false;

                                        long double somaCustosDistanciasTemp = somaCustosDistancias(D, C, Ftemp, n, m);

                                        if (somaCustosDistanciasTemp < somaCustosDistanciasAntiga) {
                                                indiceRemovido = i;
                                                somaCustosDistanciasAntiga = somaCustosDistanciasTemp;
                                                tempMelhorQueAntiga = true;
                                        }
                                }
                        }

                        if (tempMelhorQueAntiga) {
                                F[indiceRemovido] = false;
                        } else {
                                somaCustosDistanciasMelhora = false;
                        }
                }
        }
}

/* Fase onde se verifica se substituem elementos de F caso seja possível
        Parâmetros:
                D[]: matriz de distâncias
                C[]: custos para construir em cada local
                F[]: conjunto de facilidades abertas
                n: número de clientes
*/
void mudaElementosEmF(double D[], double C[], bool F[], int n, int m) {
        for (int i = 0; i < m; i++) {
                if (F[i]) {
                        long double somaCustosDistanciasAntiga = somaCustosDistancias(D, C, F, n, m);
                        bool tempMelhorQueAntiga = false;
                        int indiceCustosDistanciasMinimos;

                        for (int j = 0; j < m; j++) {
                                if (F[j]) {
                                        bool Ftemp[m];
                                        for (int k = 0; k < m; k++) { Ftemp[k] = F[k]; }
                                        Ftemp[i] = true;
                                        Ftemp[j] = false;

                                        long double somaCustosDistanciasTemp = somaCustosDistancias(D, C, Ftemp, n, m);

                                        if (somaCustosDistanciasTemp < somaCustosDistanciasAntiga) {
                                                indiceCustosDistanciasMinimos = j;
                                                somaCustosDistanciasAntiga = somaCustosDistanciasTemp;
                                                tempMelhorQueAntiga = true;
                                        }
                                }
                        }

                        if (tempMelhorQueAntiga) {
                                for (int j = 0; j < m; j++) {
                                        if (j == indiceCustosDistanciasMinimos) { F[j] = true; }
                                        if (j == i) { F[j] = false; }
                                }
                        }
                }
        }
}
