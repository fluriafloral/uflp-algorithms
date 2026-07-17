#include "../cabec/teste.h"
#include "../aux/auxExato.c"

/*
        Parâmetros:
                Cls[]: subconjunto dos clientes
*/
void ascensaoDual(Teste *t, double V[], double S[], int locsPorProx[], bool JMais[]) {
    int K[t->n];

    for (int j = 0; j < t->n; j++) {
        K[j] = 0;

        for (int k = 0; k < t->m; k++) {
            int loc = locsPorProx[(j * t->m) + k];

            if (t->distancias[(j * t->m) + loc] >= V[j] - EPSILON) {
                K[j] = k;

                if (t->distancias[(j * t->m) + loc] <= V[j] + EPSILON) {
                    K[j] = k + 1;
                }

                break;
            }
        }

        if (K[j] >= t->m) K[j] = t->m;
    }

    bool removeFacilidade;

    do {
        removeFacilidade = false;

        for (int j = 0; j < t->n; j++) {
            if (!JMais[j]) { continue; }

            double folgaDelta = DBL_MAX;
            for (int i = 0; i < t->m; i++) {
                if (V[j] >= t->distancias[(j * t->m) + i] - EPSILON) {
                    if (S[i] < folgaDelta) {
                        folgaDelta = S[i];
                    }
                }
            }

            double custo = DBL_MAX;
            if (K[j] < t->m) {
                int loc = locsPorProx[(j * t->m) + K[j]];
                custo = t->distancias[(j * t->m) + loc] - V[j];
            }

            double delta = folgaDelta;
            if (custo < folgaDelta) {
                delta = custo;

                if (K[j] < t->m) { K[j]++; }
                removeFacilidade = true;
            }

            if (delta > EPSILON) {
                for (int i = 0; i < t->m; i++) {
                    if (V[j] >= t->distancias[(j * t->m) + i] - EPSILON) {
                        S[i] -= delta;
                        if (S[i] < 0) { S[i] = 0; }
                    }
                }

                V[j] += delta;
            }
        }
    } while (removeFacilidade);
}

void ajusteDual(Teste *t, double V[], double S[], int locsPorProx[], bool IAst[]) {
    bool alteracao;

    do {
        alteracao = false;

        for (int j = 0; j < t->n; j++) {
            int tamIjMais = 0;
            int iMais = -1;
            int iLinha = -1;

            for (int k = 0; k < t->m; k++) {
                int fac = locsPorProx[(j * t->m) + k];
                if (IAst[fac]) {
                    if (V[j] > t->distancias[(j * t->m) + fac] + EPSILON) {
                        tamIjMais++;

                        if (iMais == -1) { iMais = fac; }
                        else if (iLinha == -1) { iLinha = fac; }
                    }
                }
            }

            if (tamIjMais > 1) {
                bool *JMais_iMais = JMaisi(t->distancias, V, IAst, t->n, t->m, iMais);
                bool *JMais_iLinha = JMaisi(t->distancias, V, IAst, t->n, t->m, iLinha);

                int tamMais = tamanhoSubConjunto(JMais_iMais, t->n);
                int tamLinha = tamanhoSubConjunto(JMais_iLinha, t->n);

                if (tamMais > 0 && tamLinha > 0) {
                    double v = V[j];
                    alteracao = true;

                    double cjm = cjmenos(t->distancias, V[j], t->m, j);

                    for (int i = 0; i < t->m; i++) {
                        if (V[j] > t->distancias[(j * t->m) + i] + EPSILON) {
                            S[i] += (V[j] - cjm);
                        }
                    }

                    V[j] = cjm;

                    bool *JMaisA = uniaoJMais(JMais_iMais, JMais_iLinha, t->n);
                    ascensaoDual(t, V, S, locsPorProx, JMaisA);
                    atualizaF(S, IAst, t->m);

                    JMaisA[j] = true;
                    ascensaoDual(t, V, S, locsPorProx, JMaisA);
                    atualizaF(S, IAst, t->m);

                    bool todosJ[t->n];
                    for(int k = 0; k < t->n; k++) { todosJ[k] = true; }
                    ascensaoDual(t, V, S, locsPorProx, todosJ);
                    atualizaF(S, IAst, t->m);

                    if (V[j] < v - EPSILON) {
                        j--;
                    }

                    free(JMaisA);
                }

                free(JMais_iMais);
                free(JMais_iLinha);
            }
        }
    } while (alteracao);
}

void algoritmoDual(Teste *t) {
    int locsPorProx[t->n * t->m];

    for (int j = 0; j < t->n; j++) {
        double subDist[t->m];
        int subLoc[t->m];

        for (int i = 0; i < t->m; i++) {
            subDist[i] = t->distancias[(j * t->m) + i];
            subLoc[i] = i;
        }

	qsort_r(subLoc, t->m, sizeof(int), comparaListaDouble, subDist);

	for (int i = 0; i < t->m; i++) {
            locsPorProx[(j * t->m) + i] = subLoc[i];
        }
    }

    double V[t->n];
    bool JMais[t->n];
    for (int i = 0; i < t->m; i++) { t->facilidades[i] = false; }
    for (int j = 0; j < t->n; j++) {
        int localMaisProximo = locsPorProx[j * t->m];
        V[j] = t->distancias[(j * t->m) + localMaisProximo];
        t->facilidades[localMaisProximo] = true;
        JMais[j] = true;
    }

    double S[t->m];
    bool *IAst = t->facilidades;
    for (int i = 0; i < t->m; i++) {
        double soma = 0;
        for (int j = 0; j < t->n; j++) {
            double dif = V[j] - t->distancias[(j * t->m) + i];
            if (dif > 0) { soma += dif; }
        }

        S[i] = t->custos[i] - soma;
        if (S[i] < 0) { S[i] = 0; }

        IAst[i] = (S[i] <= EPSILON);
    }

    ascensaoDual(t, V, S, locsPorProx, JMais);
    atualizaF(S, IAst, t->m);

    ajusteDual(t, V, S, locsPorProx, IAst);
    atualizaF(S, t->facilidades, t->m);

    diminuiF(t->distancias, t->custos, t->facilidades, t->n, t->m);
}
