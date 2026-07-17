#ifndef TESTE_H
#define TESTE_H

#include <stdbool.h>

typedef struct {
        int n; // Quantidade de clientes
        int m; // Quantidade de potenciais localizações para facilidade

        long *demandas; // Demanda de cada cliente
        double *distancias; // Custos de deslocamento dos locais até os clientes

        long *capacidades; // Capacidade das facilidades
        double *custos; // Custos para construir uma facilidade em cada localização

	bool *facilidades; // Conjunto de facilidades abertas
} Teste;

#endif
