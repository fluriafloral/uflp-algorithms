#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#include "../calc/calculaCustos.c"

/*
	Funções para processamento das três fases da heurística construtiva
*/

/* Fase onde se adicionam elementos à F enquanto a soma das distâncias diminui
        Parâmetros:
                **D: matriz de distâncias
                *C: custos para construir em cada local
                *F: conjunto de facilidades abertas
                n: número de clientes
*/
void faseAumenta(double *D, double *C, bool *F, int n, int m) {
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

/* Fase onde se removem elementos de F enquanto a soma das distâncias diminui
	Parâmetros:
		**D: matriz de distâncias
		*C: custos para construir em cada local
		*F: conjunto de facilidades abertas
		n: número de clientes
		n: número de locais possíveis
*/
void faseDiminui(double *D, double *C, bool *F, int n, int m) {
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
                **D: matriz de distâncias
                *C: custos para construir em cada local
                *F: conjunto de facilidades abertas
                n: número de clientes
*/
void faseSubstituicao(double *D, double *C, bool *F, int n, int m) {
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
