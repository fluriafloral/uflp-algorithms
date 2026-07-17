#include "../aux/auxHeur.c"

/*
	Implementação da heurística construtiva determinística DAS (Diminui, Aumenta, Substitui)
*/

/*
	Parâmetros:
		*D: matriz de distâncias
		*C: custos para construir em cada local
		*F: conjunto de facilidades
		n: quantidade de clientes
		m: quantidade de locais possíveis
	Retorno:
		void
*/
void deterministicoDAS(Teste *t) {
	bool somaCustosMelhora = true;

	for (int i = 0; i < t->m; i++) { t->facilidades[i] = true; }

	long double somaCustosDistanciasAntiga = somaCustosDistancias(t->distancias, t->custos, t->facilidades, t->n, t->m);

	while (somaCustosMelhora) {
		diminuiF(t->distancias, t->custos, t->facilidades, t->n, t->m);
		mudaElementosEmF(t->distancias, t->custos, t->facilidades, t->n, t->m);
		aumentaF(t->distancias, t->custos, t->facilidades, t->n, t->m);
		mudaElementosEmF(t->distancias, t->custos, t->facilidades, t->n, t->m);

		long double somaCustosDistanciasNova = somaCustosDistancias(t->distancias, t->custos, t->facilidades, t->n, t->m);

		if (somaCustosDistanciasNova < somaCustosDistanciasAntiga) { somaCustosDistanciasAntiga = somaCustosDistanciasNova; } 
		else { somaCustosMelhora = false; }
	}
}

