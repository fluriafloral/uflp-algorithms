#include "aux/aux.c"
#include "metaNC/algHibrido.c"
#include "exatoNC/procedimentoDual.c"
#include "heurNC/deterministicoDAS.c"
#include "tempo/calculaTempo.c"
#include "arqv/processaArquivo.c"

int main(int argc, char* argv[]) {

	// Abertura do arquivo e leitura dos dados da instância de teste
	Teste *instancia = alocaInstancia(argv[1]);

	long double custoOtimo = imprimeSolucaoOtima(argv[1], instancia->n, instancia->m);

	double tempoDecorrido;

	for (int i = 3; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0) {
			tempoDecorrido = calculaTempoExecucao(deterministicoDAS, instancia);
			processaResultados(instancia, custoOtimo, argv[1], argv[2], "Heur", "Heurística Construtiva Determinística DAS", tempoDecorrido);
		}

		if (strcmp(argv[i], "-e") == 0) {
			tempoDecorrido = calculaTempoExecucao(algoritmoDual, instancia);
			processaResultados(instancia, custoOtimo, argv[1], argv[2], "Exato", "Branch-and-Bound Baseado em Dualidade", tempoDecorrido);
		}

		if (strcmp(argv[i], "-m") == 0) {
			double t0, a;
			sscanf(argv[i + 3], "%lf", &t0);
			sscanf(argv[i + 4], "%lf", &a);

			tempoDecorrido = calculaTempoExecucaoMeta(algoritmoHibrido, instancia, atoi(argv[i + 1]), atoi(argv[i + 2]), t0, a);
			processaResultados(instancia, custoOtimo, argv[1], argv[2], "Meta", "Híbrido Genético & Arrefecimento Simulado", tempoDecorrido);
		}
	}

	// Liberação da memória alocada para a instância de teste
        liberaInstancia(instancia);
}
