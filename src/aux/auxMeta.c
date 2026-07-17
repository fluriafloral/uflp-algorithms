#include <math.h> // RAND_MAX, exp
#include <string.h> // memcpy

#include "../cabec/teste.h"

void geraPopulacaoInicial(bool populacao[], int tamanho, int m) {
	for (int i = 0; i < tamanho * m; i++) {
		populacao[i] = rand() & 1;
	}
}

/*
void geraPopulacaoInicialOrdenada(Teste *instancia, bool populacao[], int tamanho) {
	// gera tP soluções aleatórias de P, inserido-as na matriz de forma ordenada
	long double custos[tamanho];
	bool solucaoAleatoria[instancia->m];
	long double custoSolucaoAleatoria;

        for (int b = 0; b < instancia->m; b++) {
                solucaoAleatoria[b] = rand() & 1;
        }

	for (int b = 0; b < instancia->m; b++) {
                populacao[b] = solucaoAleatoria[b];
        }
        custos[0] = somaCustosDistancias(instancia->distancias, instancia->custos, solucaoAleatoria, instancia->n, instancia->m);

	for (int s = 1; s < tamanho; s++) {
		for (int b = 0; b < instancia->m; b++) {
                	solucaoAleatoria[b] = rand() & 1;
        	}
		custoSolucaoAleatoria = somaCustosDistancias(instancia->distancias, instancia->custos, solucaoAleatoria, instancia->n, instancia->m);

		int t = s - 1;

		while (t >= 0 && custos[t] > custoSolucaoAleatoria) {
			custos[t + 1] = custos [t];
			t--;
		}

		for (int b = 0; b < instancia->m; b++) {
                	populacao[((t + 1) * instancia->m) + b] = solucaoAleatoria[b];
        	}
		custos[t + 1] = custoSolucaoAleatoria;
        }
}
*/

/* Ordena uma população em função do custo total da solução crescente, implementação bubble sort
*/
void ordenaPopulacaoPorCustoCrescente(Teste *instancia, bool populacao[], int tamanho) {
	bool solucao1[instancia->m], solucao2[instancia->m];
	long double custo1, custo2;

	for (int i = 0; i < tamanho - 1; i++) {
		for (int j = i + 1; j < tamanho; j++) {
			memcpy(solucao1, &populacao[i * instancia->m], instancia->m * sizeof(populacao[0]));
			memcpy(solucao2, &populacao[j * instancia->m], instancia->m * sizeof(populacao[0]));
/*
			for (int k = 0; k < instancia->m; k++) {
				solucao1[k] = populacao[(i * instancia->m) + k];
				solucao2[k] = populacao[(j * instancia->m) + k];
			}
*/
			custo1 = somaCustosDistancias(instancia->distancias, instancia->custos, solucao1, instancia->n, instancia->m);
			custo2 = somaCustosDistancias(instancia->distancias, instancia->custos, solucao2, instancia->n, instancia->m);

			if (custo1 > custo2) {
				for (int k = 0; k < instancia->m; k++) {
					bool tmp = solucao1[k];
					populacao[(i * instancia->m) + k] = solucao2[k];
					populacao[(j * instancia->m) + k] = tmp;
				}
			}
		}
	}

}

bool aceitaSolucaoPior(long double delta, double temperatura) {
	long double numAleatorio = rand() / RAND_MAX;
	long double divisao = (-1 * delta) / temperatura;
	return exp(divisao) > numAleatorio;
}
