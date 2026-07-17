#include <stdbool.h>
#include <stdlib.h>
#include <float.h>

#define EPSILON 1e-9
#define _GNU_SOURCE

int comparaListaDouble(const void *a, const void *b, void *c) {
    double *lC = (double*)c;
    int indcA = *(int*)a;
    int indcB = *(int*)b;

    if (lC[indcA] < lC[indcB]) { return -1; }
    if (lC[indcA] > lC[indcB]) { return 1; }
    return 0;
}

bool* IjAst(double D[], bool IAst[], double v, int m, int j) {
    bool *IjA = (bool *) malloc(m * sizeof(bool));
    if (!IjA) { return NULL; }

    for (int i = 0; i < m; i++) {
        if (IAst[i] && v >= D[(j * m) + i] - EPSILON) { IjA[i] = true; }
        else { IjA[i] = false; }
    }

    return IjA;
}

bool* JMaisi(double D[], double V[], bool IAst[], int n, int m, int l) {
    bool *JMi = (bool*) malloc(n * sizeof(bool));
    if (!JMi) return NULL;

    for (int j = 0; j < n; j++) {
        bool *IjA = IjAst(D, IAst, V[j], m, j);

        if (tamanhoSubConjunto(IjA, m) == 1 && IjA[l]) { JMi[j] = true; }
	else { JMi[j] = false; }

        free(IjA);
    }

    return JMi;
}

double cjmenos(double D[], double v, int m, int j) {
    double cjm = -1.0;

    for (int i = 0; i < m; i++) {
        double r = D[(j * m) + i];

        if (r < v - EPSILON) {
            if (cjm < 0 || r > cjm) { cjm = r; }
        }
    }

    return (cjm < 0) ? 0 : cjm; 
}

bool* uniaoJMais(bool Ja[], bool Jb[], int n) {
    bool *Jab = (bool*) malloc(n * sizeof(bool));
    if (!Jab) return NULL;

    for (int j = 0; j < n; j++) {
        if (Ja[j] || Jb[j]) { Jab[j] = true; }
        else { Jab[j] = false; }
    }

    return Jab;
}

void atualizaF(double S[], bool F[], int m) {
    for (int i = 0; i < m; i++) {
        if (S[i] <= EPSILON) { F[i] = true; }
        else { F[i] = false; }
    }
}
