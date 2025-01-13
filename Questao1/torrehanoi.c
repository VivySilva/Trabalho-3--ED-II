#include <stdio.h>
#include <stdlib.h>
#include "torrehanoi.h"
#include <limits.h>
#include <time.h>

int movimento_valido(vertice v1, vertice v2)
{
    int valido = 1, diferenca = 0, posicao_diferente = -1;

    // Verifica se apenas um disco foi movido
    for(int posicao = 0; posicao < Discos && diferenca <= 1; posicao++)
    {
        if(v1.posicao[posicao] != v2.posicao[posicao]) // Se as posições não forem iguais 
        {
            diferenca++; // Aumenta a diferença e para o 'for' se for maior ou igual a 1
            posicao_diferente = posicao; // Armazena a posção onde houve a diferença
        }
    }

    if(diferenca > 1) // Se a diferença for maior que 1
        valido = 0; // O movimento será inválido

    else // Se não
    {
        int invalido = 1;
        for(int posVerificacao = 0; posVerificacao < Discos && invalido; posVerificacao++)
            if(posVerificacao != posicao_diferente &&
            ((v1.posicao[posVerificacao] == v1.posicao[posicao_diferente] && posVerificacao < posicao_diferente) ||
            (v2.posicao[posVerificacao] == v2.posicao[posicao_diferente] && posVerificacao < posicao_diferente)))
            invalido = 0;

        if (!invalido)
        valido = 0;
  }

  return (valido);
}

void gerar_matriz_adjacencia(vertice *grafo, int matriz[][Possibilidades])
{
    int disco, atribuido;
    
    for(int atual = 0; atual < Possibilidades; atual++)
    {
        atribuido = atual;
        for(disco = 0; disco < Discos; disco++)
        {
            grafo[atual].posicao[disco] = atribuido % Pinos + 1;
            atribuido /= Pinos;
        }
    }

    for(int atual = 0; atual < Possibilidades; atual++)
    {
        for(int amigo = 0; amigo < Possibilidades; amigo++)
        {
            if(movimento_valido(grafo[atual], grafo[amigo]) == 1) matriz[atual][amigo] = 1; // Movimento Válido
            else matriz[atual][amigo] = 0; //Movimento Inválido
        }
    }
}

void exibir_matriz(vertice *grafo)
{
    for(int atual = 0; atual < Possibilidades; atual++)
    {
        printf("Vet %.2d:", atual);
        for(int disco = 0; disco < Discos; disco++)
            printf(" %d", grafo[atual].posicao[disco]);
        printf("\n");
    }
}

void dijkstra(int matriz[][Possibilidades], int inicio, int fim)
{
    int distancias[Possibilidades];
    int visitados[Possibilidades], i, contador, v;

    for (i = 0; i < Possibilidades; i++)
    {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
    }

    distancias[inicio] = 0;

    for (contador = 0; contador < Possibilidades - 1; contador++)
    {
        int u = -1;

        for (i = 0; i < Possibilidades; i++)
        {
            if (!visitados[i] && (u == -1 || distancias[i] < distancias[u]))
            {
                u = i;
            }
        }

        visitados[u] = 1;

        for (v = 0; v < Possibilidades; v++)
        {
            if (!visitados[v] && matriz[u][v] && distancias[u] != INT_MAX &&
                distancias[u] + matriz[u][v] < distancias[v])
            {
                distancias[v] = distancias[u] + matriz[u][v];
            }
        }
    }

    printf("Menor caminho de %d para %d: %d\n", inicio, fim, distancias[fim]);
}

void menor_caminho(int matriz[][Possibilidades])
{
    int inicio = 0;
    int fim = Possibilidades - 1;

    clock_t startVerticies_time, end_time;
    double time;

    startVerticies_time = clock();
    dijkstra(matriz, inicio, fim);
    end_time = clock();

    time = (double)(end_time - startVerticies_time) / CLOCKS_PER_SEC;

    printf("Tempo gasto - Dijkstra: %lf ms\n", time * 1000);
}

int main()
{
    vertice grafo[Possibilidades];
    int matriz_adjacencia[Possibilidades][Possibilidades];

    gerar_matriz_adjacencia(grafo, matriz_adjacencia);
    //exibir_matriz(grafo);  
    
    menorcaminho(matriz_adjacencia);
    return 0;
}