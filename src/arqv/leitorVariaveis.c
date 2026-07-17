#include <stdio.h> // fprintf
#include <stdlib.h> // exit
#include <errno.h> // errno
#include <string.h> // atol
#include <ctype.h> // isdigit

/*
	Funções para leitura e processamento dos arquivos de testes
*/

/* Imprime no terminal o tipo do erro ocorrido e a mensagem gerada, e encerra a execução do programa
	Parâmetros:
		t[]: string descrevendo o erro ocorrido
	Retorno:
		void
*/
void imprimeErro(char t[]) {
	fprintf(stderr, "%s: %s\n", t, strerror(errno));
	exit(1);
}

/* Lê um valor inteiro no arquivo e o retorna como int
	Parâmetros:
		*ptr: ponteiro apontando para o buffer do arquivo sendo lido
		e[]: tipo do erro ocorrido durante a execução da função
	Retorno:
		q: long com valor do inteiro lido
*/
int leituraQuantidade(FILE *ptr, char e[]) {
	int q;

        if (fscanf(ptr, "%d", &q) != 1) { imprimeErro(e); }

	return q;
}

/* Lê as m capacidades e custos da instância de teste e armazena em arrays
	Parâmetros:
		*ptr: ponteiro apontando para o buffer do arquivo sendo lido
		cap[]: capacidade dos m locais
		cus[]: custo de construção nos m locais
		m: número de locais possíveis
	Retorno:
		void
*/
void leituraCapacidadesCustos(FILE *ptr, long cap[], double cus[], int m) {
        char c[10];

	for (int i = 0; i < m; i++) {
		if (fscanf(ptr, "%s %lf", &c, &cus[i]) != 2) { imprimeErro("Erro na leitura das capacidades e custos"); }

		/* Verifica se a capacidade é uma string (não capacitado) ou um long (capacitado)
		   se for capacitado armazena o valor lido, caso contrário armazena -1 */
		if (isdigit(c[0])) { cap[i] = atol(c); }
		else { cap[i] = -1; }
	}
}

/* Lê as demandas dos n clientes e as distâncias para os locais possíveis, e armazena em arrays
	Parâmetros:
		*ptr: ponteiro apontando para o buffer do arquivo sendo lido
		dem[]: demanda dos n clientes
		dist[]: distância dos clientes para os locais
		n: número de clientes
		m: número de locais possíveis
*/
void leituraDemandasDistancias(FILE *ptr, long dem[], double dist[], int n, int m) {

	for (int i = 0; i < n; i++) {

		if (fscanf(ptr, "%ld", &dem[i]) != 1) { imprimeErro("Erro na leitura das demandas"); }

		for (int j = 0; j < m; j++) {
			if (fscanf(ptr, "%lf", &dist[(i * m) + j]) != 1) { imprimeErro("Erro na leitura das distâncias"); }
		}
	}
}
