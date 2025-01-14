#include <stdio.h>
#include <stdlib.h>

#define Pinos 3
#define Discos 4
#define Possibilidades 81 // Pinos^Discos = 3^4

typedef struct
{
    int posicao[Discos]; // Posição dos Discos em relação aos Pinos
}vertice;

int movimento_valido(vertice v1, vertice v2); 
void gerar_matriz_adjacencia(vertice *grafo, int matriz[][Possibilidades]);
void exibir_matriz(vertice *grafo);

void menor_caminho(int matriz[][Possibilidades]);
void dijkstra(int matriz[][Possibilidades], int inicio, int fim);