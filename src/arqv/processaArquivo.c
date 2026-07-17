#include "../arqv/leitorVariaveis.c"
#include "../cabec/teste.h"

/*
        Funções de processamento dos arquivos de testes
*/

/* Abre o buffer de leitura do arquivo de teste e retorna ponteiro para ele
        Parâmetros:
                c[]: arquivo de teste no formato "caminho/para/arquivo.txt"
        Retorno
                *b: buffer de leitura do arquivo
*/
FILE* abreArquivo(char  c[], char p[]) {

        FILE *b = fopen(c, p);

        if (b == NULL) {
                imprimeErro("Erro na abertura do arquivo");
        }

	return b;
}

/* Aloca memória para lista de valores
	Parâmetros:
		tam: tamanho da lista
		tipoTam: tamanho do tipo armazenado
		errMsg[]: mensagem de erro apresentada em caso de falha
	Retorno:
		l*: ponteiro apontando para o primeiro elemento da lista
*/
void* alocaLista(int tam, size_t tipoTam, char errMsg[]) {

	void *l = malloc(tam * tipoTam);

	if (l == NULL) { imprimeErro(strcat("Erro na alocação de memória da lista de ", errMsg)); }

	return l;
}

/* Aloca memória necessária para as variáveis do arquivo de teste e as armazena
        Parâmetros:
                c[]: local onde da instância de teste
        Retorno
                *inst: instância de teste contendo os valores lidos no arquivo
*/
Teste* alocaInstancia(char c[]) {
        FILE *buffer = abreArquivo(c, "r");
        Teste *inst;

        // Alocação de memória da instância do tipo Teste
        inst = malloc(sizeof(Teste));
        if (inst == NULL) {
                imprimeErro("Erro na alocação de memória necessária para a instância");
        }

        // Leitura e atribuição da quantidade de clientes e localizações possíveis
        inst->m = leituraQuantidade(buffer, "Erro na leitura da quantidade de locais");
        inst->n = leituraQuantidade(buffer, "Erro na leitura da quantidade de clientes");

        // Alocação de memória das listas de capacidades e custos de construção
        inst->capacidades = (long*) alocaLista(inst->m, sizeof(long), "capacidades");
        inst->custos = (double*) alocaLista(inst->m, sizeof(double), "custos de construção");

        // Leitura de m linhas contendo as capacidades e custos de cada localização
        leituraCapacidadesCustos(buffer, inst->capacidades, inst->custos, inst->m);

        // Alocação de memória das listas de demandas e distâncias
        inst->demandas = (long*) alocaLista(inst->n, sizeof(long), "demandas");
        inst->distancias = (double*) alocaLista((inst->n * inst->m), sizeof(double), "distâncias");

        // Leitura das demandas dos n clientes e as distâncias para cada local m
        leituraDemandasDistancias(buffer, inst->demandas, inst->distancias, inst->n, inst->m);

	fclose(buffer);

	printf("************************************************************************\n");
	printf("Instância de teste lida: %s\n", c);
	printf("Número de locais possíveis: %d\n", inst->m);
	printf("Número de clientes: %d\n", inst->n);

	// Alocação de memória do conjunto de facilidades abertas
        inst->facilidades = (bool*) alocaLista(inst->m, sizeof(bool), "facilidades");
        for (int i = 0; i < inst->m; i++) { inst->facilidades[i] = true; }

        return inst;
}

/* Desaloca memória da instância de teste
        Parâmetros:
                *inst: instância de teste utilizada
        Retorno
                void
*/
void liberaInstancia(Teste *inst) {
        free(inst->distancias);
        free(inst->demandas);

        free(inst->custos);
        free(inst->capacidades);

	free(inst->facilidades);

        free(inst);
}

char* geraNomeArquivo(char aR[], char res[], char aS[], char r[]) {
	strcpy(aR, res);
        int tamAS = strlen(aS) - 1;

        while(aS[tamAS] != '/') { tamAS--; }

        strncat(aR, aS + tamAS + 1, strcspn(aS + tamAS + 1, "."));
        strcat(aR, r);

	// calculo do momento da execução do algoritmo
	char m[25];
        calculaMomentoFormatado(m);
	strcat(aR, m);

	strcat(aR, ".txt");
}

void imprimeResultados(Teste *t, FILE *bufferResultado, long double custoOtimo, double tD) {
	// impressão dos locais selecionados ao fim da execução
        printf("Locais selecionados: ");
        for (int i = 0; i < t->m; i++) {
                if (t->facilidades[i]) {
			printf("%d ", i);
			fprintf(bufferResultado, "%d ", i);
		}
        }
        printf("\n");
	fprintf(bufferResultado, "\n");

        // impressão das facilidades que atenderão os n clientes
        printf("Facilidades que atenderão os %d clientes: \n", t->n);
        for (int j = 0; j < t->n; j++) {
                int local = localMaisPertoEmF(t->distancias, t->facilidades, t->m, j);
                printf("%d ", local);
                fprintf(bufferResultado, "%d ", local);
                if (j > 0 && (j + 1) % 20 == 0) { printf("\n"); }
        }
        printf("\n");
	fprintf(bufferResultado, "\n");

        // impressão do custo total da solução
        long double custoTotal = somaCustosDistancias(t->distancias, t->custos, t->facilidades, t->n, t->m);
        printf("Custo total da solução: %Lf\n", custoTotal);
        fprintf(bufferResultado, "%Lf\n", custoTotal);

	// impressão do afastamento em relação a melhor solução
	long double afastamento = custoTotal - custoOtimo;
        printf("Afastamento da solução ótima para a solução gerada: %Lf\n", afastamento);
	fprintf(bufferResultado, "%Lf\n", afastamento);

        // impressão do tempo de execução
        printf("Tempo de execução: %lfs\n", tD);
        fprintf(bufferResultado, "%lf\n", tD);
}

long double imprimeSolucaoOtima(char arqv[], int n, int m) {
	char arqvSolucao[150];
	strcpy(arqvSolucao, arqv);
        strcat(arqvSolucao, ".opt");
        FILE *bufferSolucao = abreArquivo(arqvSolucao, "r");

	printf("------------------------------------------------------------------------\n");
	printf("Locais na solução ótima: ");

        bool locaisEscolhidos[m];
        int localPorCliente[n];

        for (int i = 0; i < m; i++) { locaisEscolhidos[i] = false; }

        for (int j = 0; j < n; j++) {
                fscanf(bufferSolucao, "%d", &localPorCliente[j]);
                locaisEscolhidos[localPorCliente[j]] = true;
       	}

        for (int i = 0; i < m; i++) {
                if (locaisEscolhidos[i]) { printf("%d ", i); }
        }
        printf("\n");

        printf("Facilidades que atenderão os %d clientes:\n", n);
        for (int j = 0; j < n; j++) {
                printf("%d ", localPorCliente[j]);
                if (j > 0 && (j + 1) % 20 == 0) { printf("\n"); }
        }
        printf("\n");

        long double custoOtimo;
        fscanf(bufferSolucao, "%Lf", &custoOtimo);
        printf("Custo total da solução ótima: %Lf\n", custoOtimo);

	return custoOtimo;
}

/* Imprime resultado obtido e grava em arquivo
        Parâmetros:
                *t: instância de teste processada
		custoOtimo: custo da melhor solução do problema
		c[]: caminho para local do arquivo da instancia e solução (solução deve estar na mesma pasta, com o mesmo nome da instancia + .opt)
                r[]: nome do algoritmo utilizado para o arquivo
		a[]: algoritmo utilizado
                tD: tempo de execução do algoritmo
*/
void processaResultados(Teste *t, long double custoOtimo, char c[], char res[], char r[],char a[], double tD) {
	char *arqvSolucao, *arqvResultado;

	// Abertura do arquivo da solução ótima
        arqvSolucao = (char*) malloc(100 * sizeof(char));
        strcpy(arqvSolucao, c);
        strcat(arqvSolucao, ".opt");
        FILE *bufferSolucao = abreArquivo(arqvSolucao, "r");

        // criação do arquivo dos resultados
	arqvResultado = (char*) malloc(50 * sizeof(char));
	geraNomeArquivo(arqvResultado, res, arqvSolucao, r);
	FILE *bufferResultado = abreArquivo(arqvResultado, "w");

	printf("========================================================================\n");
	printf("Algoritmo utilizado: %s\n", a);

	// Imprime na tela e grava em arquivo resultados da solução gerada
	imprimeResultados(t, bufferResultado, custoOtimo, tD);

	printf("solução armazenada em %s com sucesso\n", arqvResultado);

	// libera memória alocada para strings
	free(arqvSolucao);
        free(arqvResultado);

	// fechamento do buffer de leitura do arquivo da solução
	fclose(bufferSolucao);

        // fechamento do buffer de escrita do arquivo resultado
        fclose(bufferResultado);
}

/*
void leituraSolucaoOtima(char c[], int n, int m) {
	FILE *buffer = fopen(strcat(c, ".opt"), "r");

	if (buffer != NULL) {
		printf("------------------------------------------------------------------------\n");
		printf("Solução ótima da instância de teste encontrada em: %s\n", c);

		printf("Locais na solução ótima: ");

		bool locaisEscolhidos[m];
		int localPorCliente[n];

		for (int i = 0; i < m; i++) { locaisEscolhidos[i] = false; }

		for (int j = 0; j < n; j++) {
			fscanf(buffer, "%d", &localPorCliente[j]);
			locaisEscolhidos[localPorCliente[j]] = true;
		}

		for (int i = 0; i < m; i++) {
			if (locaisEscolhidos[i]) { printf("%d ", i); }
		}
		printf("\n");

		printf("Facilidades que atenderão os %d clientes:\n", n);
		for (int j = 0; j < n; j++) {
			printf("%d ", localPorCliente[j]);
			if (j > 0 && (j + 1) % 20 == 0) { printf("\n"); }
		}
		printf("\n");

		long double custoTotal;
		fscanf(buffer, "%Lf", &custoTotal);
		printf("Custo total da solução ótima: %Lf\n", custoTotal);
	}

	printf("========================================================================\n");
}
*/
