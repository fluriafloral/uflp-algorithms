#include <time.h>

#include "../cabec/teste.h"

double calculaTempoExecucao(void (*func)(Teste*), Teste *instancia) {
	clock_t inicio = clock();

	(*func)(instancia);

	clock_t fim = clock();
        return (double) (fim - inicio) / CLOCKS_PER_SEC;
}

double calculaTempoExecucaoMeta(void (*func)(Teste*, int, int, double, double), Teste *instancia, int tamPopulacao, int maxGeracoes, double tempInicial, double taxaResfriamento) {

	clock_t inicio = clock();

	(*func)(instancia, tamPopulacao, maxGeracoes, tempInicial, taxaResfriamento);

	clock_t fim = clock();
	return (double) (fim - inicio) / CLOCKS_PER_SEC;
}

void calculaMomentoFormatado(char m[]) {
	time_t tempo;
        struct tm *info;

	time(&tempo);
        info = localtime(&tempo);

        strftime(m, 15, "%d%m%y_%H%M%S", info);
}
