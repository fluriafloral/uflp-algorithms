# Implementação de algoritmos para o problema da localização de instalações não capacitado

O programa gera soluções para instâncias do problema da localização de instalações não capacitado, atualmente conta com três algoritmos implementados:

 - Heurística determinística DAS (Diminui, Aumenta, Substitui), proposto por Soumen Atta, Priya Ranjan Sinha Mahapatra e Anirban Mukhopadhyay (igi-global.com/gateway/article/225822).

 - Procedimento baseado em dualidade DUALOC, proposto Donald Erlenkotter (https://www.jstor.org/stable/170260). 

 - Meta-Heurística híbrida de Algoritmo Genético & Arrefecimento Simulado, proposto por Songul Kısaboyun e Emrullah Sonuç (comdem.org/index.php/comdem/article/view/13781).

# Implementation of algorithms to the uncapacitated facility location problem

The program generates solutions for instances of the uncapacitated facility location problem, currently it has three implemented algorithms:

 - Deterministic heuristic BFR (Backward, Forward, Replacement), proposed by Soumen Atta, Priya Ranjan Sinha Mahapatra e Anirban Mukhopadhyay (igi-global.com/gateway/article/225822).
 
 - Dual-Based procedure DUALOC, proposed by Donald Erlenkotter (https://www.jstor.org/stable/170260). 
 
 - Hybrid metaheuristic combining genetic algorithm and simulated annealing, proposed by Songul Kısaboyun e Emrullah Sonuç (comdem.org/index.php/comdem/article/view/13781).

## Pré-requisitos

cc v15.2.0 ou superior

## Prerequisites

cc v15.2.0 or superior

## Instalação

Clone o repositório

```

```

## Installation

Clone the repo

```

```

## Utilização

Executar o programa em uma única instância de teste:

```./uflp caminho/para/teste/teste.txt caminho/para/resultado/ [-h] [-e] [-m N G T0 α]
```
    
Executar o programa em um conjunto de instâncias de teste:

```./todos[Heur|Exato|Meta N G T0 α]
```

Onde: 
 - caminho/para/teste/teste.txt: É o caminho para o arquivo contendo a instância de teste
 - caminho/para/resultado/: É a pasta onde deve ser armazenado o resultado
 - -h: Executa a heurística determinística DAS 
 - -e: Executa o procedimento DUALOC
 - -m N G T0 α: Executa a meta-heurística híbrida com os seguintes parâmetros:
    • N = tamanho da população
    • G = número máximo de gerações
    • T0 = temperatura inicial do arrefecimento simulado
    • α = taxa de resfriamento
 - ./todosHeur: executa executa o programa no conjunto de instâncias de testes com a heurística determinística DAS
 - ./todosExato: executa o programa no conjunto de instâncias de teste com o procedimento DUALOC
 - ./todosMeta N G T0 α: executa o programa no conjunto de instâncias de testes com a meta-heurística híbrida e os parâmetros fornecidos

## Usage

Execute the program in a single test instance:

```./uflp path/to/test/test.txt path/to/result/ [-h] [-e] [-m N G T0 α]
```
    
Execute the program in a set of test instances

```./todos[Heur|Exato|Meta N G T0 α]
```

Onde: 
 - path/to/test/test.txt: It's the path to the file containing the test instance
 - path/to/result/: It's the path to the folder where the result should be stored 
 - -h: Executes the deterministic heuristic BFR
 - -e: Executes the DUALOC procedure
 - -m N G T0 α: Executes the hybrid metaheuristic with the following parameters:
    • N = population dize
    • G = maximum number of generations
    • T0 = simulated annealing initial temperature
    • α = cooling rate
 - ./todosHeur: executes the program on the instances data sets using the deterministic heuristic BFR
 - ./todosExato: executes the program on the instances data sets using the DUALOC procedure
 - ./todosMeta N G T0 α: executes the program on he instances data sets using the hybrid metaheuristic and the given parameters
    
## Instâncias de teste

Foram utilizadas instâncias de testes capacitadas e não capacitadas, extraídas dos conjuntos de teste IV ao XIII, A a C, dos bancos de instâncias Max Planck Institut Informatik e OR-Library. Estão disponíveis na pasta /testes e apresentam o seguinte formato:

m n
capacidade-1 custo-1
capacidade-2 custo-2
...
capacidade-m custo-m
demanda-1
distância-1,1 distância-1,2 ... distância-1,m
demanda-2
distância-2,1 distância-2,2 ... distância-2,m
...
demanda-n
distância-n,1 distância-n,2 ... distância-n,m

Onde:

 - m = número de localizações possíveis.
 - n = número de clientes.
 - capacidade-i = capacidade do i-ésimo local, i ∈ {1, 2, …, m} (no caso das instâncias não-capacitadas, há uma string ou um valor ignorável).
 - custo-i = custo para construir facilidade no i-ésimo local, i ∈ {1, 2, …, m}.
 - demanda-j = demanda do cliente j ∈ {1, 2, …, n}(no caso das instâncias não-capacitadas, há uma string ou um valor ignorável).
 - distância-j,i = custo de atender o cliente j ∈ {1, 2, …, n} a partir do local i ∈ {1, 2, …, m}.

## Test instances

capacitated and non-capacitated test instances were used, extracted from the test sets IV to XII, A to C, from the instances data sets Max Planck Institut Informatik and OR-Library. They are available in /testes folder and are presented in the following format:

m n
capacity-1 cost-1
capacity-2 cost-2
...
capacity-m cost-m
demand-1
distance-1,1 distance-1,2 ... distance-1,m
demand-2
distance-2,1 distance-2,2 ... distance-2,m
...
demand-n
distance-n,1 distance-n,2 ... distance-n,m

Where:

 - m = number of possible locations.
 - n = number of clientes.
 - capacity-i = capacity of the i-th possible location, i ∈ {1, 2, …, m} (for non-capacitated instances, there is a string or a negligible value).
 - custo-i = construction cost for the i-th possible location,  i ∈ {1, 2, …, m}.
 - demand-j = demand of the j-th client, j ∈ {1, 2, …, n} (for non-capacitated instances, there is a string or a negligible value).
 - distance-j,i = cost of serving the j-th client, j ∈ {1, 2, …, n}, from the i-th location, i ∈ {1, 2, …, m}.

## Créditos

Esse programa foi implementado apenas com fins educacionais
Feito e mantido por Pedro Henrique Teixeira e Silva
Projeto inicialmente desenvolvido para a disciplina Projeto e Análise de Algoritmos do bacharelado em tecnologia da informação na Universidade Federal do Rio Grande do Norte, em dezembro de 2025

## Credits

This program was implemented with educational purposes only
Created and maintained by Pedro Henrique Teixeira e Silva
Project initially developed for the algorithms project and analysis course in the bachellor degree program at the Federal University of Rio Grande do Norte, in december 2025
