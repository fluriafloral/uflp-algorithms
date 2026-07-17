#include <stdlib.h>
#include <float.h>
#include <stdbool.h>
#include <time.h>

#include "../aux/auxMeta.c"
#include "../cabec/teste.h"

void buscaLocal(Teste *instancia, bool *solucao) {
	long double melhorCusto = somaCustosDistancias(instancia->distancias, instancia->custos, solucao, instancia->n, instancia->m);

	for (int i = 0; i < instancia->m; i++) {
		bool solucaoVizinha[instancia->m];
		memcpy(solucaoVizinha, solucao, instancia->m * sizeof(solucao[0]));
		solucaoVizinha[i] = !solucaoVizinha[i];

		long double custoVizinho = somaCustosDistancias(instancia->distancias, instancia->custos, solucaoVizinha, instancia->n, instancia->m);

		if (custoVizinho < melhorCusto) {
			memcpy(solucao, solucaoVizinha, instancia->m * sizeof(solucaoVizinha[0]));
                        melhorCusto = custoVizinho;
		}
	}
}

void arrefecimentoSimulado(Teste *instancia, bool *solucao, double tempInicial, double taxaResfriamento) {
	long double custoAtual = somaCustosDistancias(instancia->distancias, instancia->custos, solucao, instancia->n, instancia->m);
	double temperatura = tempInicial;

	while (temperatura > 1) {
		// Gera solução vizinha mudando um índice aleatório de solucao
		bool solucaoVizinha[instancia->m];
		int indice = rand() % (instancia->m - 1);
		memcpy(solucaoVizinha, solucao, instancia->m * sizeof(solucao[0]));
		solucaoVizinha[indice] = !solucaoVizinha[indice];

		long double custoVizinho = somaCustosDistancias(instancia->distancias, instancia->custos, solucaoVizinha, instancia->n, instancia->m);

		long double delta = custoVizinho - custoAtual;
		if (delta < 0 || aceitaSolucaoPior(delta, temperatura)) {
			memcpy(solucao, solucaoVizinha, instancia->m * sizeof(solucaoVizinha[0]));
			custoAtual = custoVizinho;
		}

		temperatura *= taxaResfriamento;
	}
}

void algoritmoHibrido(Teste *instancia, int tamPopulacao, int maxGeracoes, double tempInicial, double taxaResfriamento) {
	srand(time(NULL));

	// Gera população inicial com tamPopulacao soluções aleatórias
	bool populacao[tamPopulacao * instancia->m];
	geraPopulacaoInicial(populacao, tamPopulacao, instancia ->m);

	long double melhorCusto = LDBL_MAX;

	for (int g = 0; g < maxGeracoes; g++) {
		ordenaPopulacaoPorCustoCrescente(instancia, populacao, tamPopulacao);

		bool solucao[instancia->m];
		memcpy(solucao, populacao, instancia->m * sizeof(populacao[0]));

		long double custo = somaCustosDistancias(instancia->distancias, instancia->custos, solucao, instancia->n, instancia->m);

		if (custo < melhorCusto) {
			memcpy(instancia->facilidades, solucao, instancia->m * sizeof(solucao[0]));
			melhorCusto = custo;
		}

		// Seleciona as dez melhores soluções
		bool novaPopulacao[tamPopulacao * instancia->m];
		int tamNovaPopulacao = 10;
		memcpy(novaPopulacao, populacao, (10 * instancia->m) * sizeof(populacao[0]));

		while (tamNovaPopulacao < tamPopulacao) {
			// Seleciona aleatoriamente dois pais entre as 20 melhores soluções
			bool pai1[instancia->m], pai2[instancia->m];

			int indice1 = rand() % 19;
			memcpy(pai1, &populacao[indice1 * instancia->m], instancia->m * sizeof(populacao[0]));

			int indice2 = rand() % 19;
			memcpy(pai2, &populacao[indice2 * instancia->m], instancia->m * sizeof(populacao[0]));

			// Gera filho usando cruzamento uniforme
			bool filho[instancia->m];
			for (int j = 0; j < instancia->m; j++) {
				int p = (j + 1) % 2 == 0 ? indice1 : indice2;
				filho[j] = populacao[(p * instancia->m) + j];
			}

			arrefecimentoSimulado(instancia, filho, tempInicial, taxaResfriamento);

			buscaLocal(instancia, filho);

			memcpy(&novaPopulacao[tamNovaPopulacao * instancia->m], filho, instancia->m * sizeof(filho[0]));
			tamNovaPopulacao++;
		}

		memcpy(populacao, novaPopulacao, (tamPopulacao * instancia->m) * sizeof(novaPopulacao[0]));
	}
}
