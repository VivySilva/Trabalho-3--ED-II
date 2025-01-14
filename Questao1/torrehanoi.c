#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <windows.h>
#include "torrehanoi.h"

int movimento_valido(vertice v1, vertice v2)
{
    int valido = 1, diferenca = 0, posicao_diferente = -1;

    // Verifica se apenas um disco foi movido
    for (int posicao = 0; posicao < Discos && diferenca <= 1; posicao++)
    {
        if (v1.posicao[posicao] != v2.posicao[posicao]) // Se as posições não forem iguais
        {
            diferenca++; // Aumenta a diferença e para o 'for' se for maior ou igual a 1
            posicao_diferente = posicao; // Armazena a posção onde houve a diferença
        }
    }

    if (diferenca > 1)
        valido = 0; // Se a diferença for maior que 1, o movimento será inválido

    else // Se não
    {
        int invalido = 1;

        // Verifica se o movimento viola as regras da Torre de Hanói
        for (int verificar_posicao = 0; verificar_posicao < Discos && invalido; verificar_posicao++)
        {
            if (verificar_posicao != posicao_diferente && // Verifica se não é o mesmo disco que já foi verificado E
                ((v1.posicao[verificar_posicao] == v1.posicao[posicao_diferente] && verificar_posicao < posicao_diferente) || // Verifica se há um disco menor abaixo do disco movido OU
                 (v2.posicao[verificar_posicao] == v2.posicao[posicao_diferente] && verificar_posicao < posicao_diferente)))  // Verifica se o disco movido foi colocado sobre um disco menor
                invalido = 0; // Se sim, marca o movimento como inválido
        }

        if (!invalido)
            valido = 0; // Se o movimento é inválido, atualiza a variável de retorno
    }

    return valido;
}

void gerar_matriz_adjacencia(vertice *grafo, int matriz[][Possibilidades])
{
    int disco, atribuido;

    // Preenche as posições iniciais do grafo
    for (int atual = 0; atual < Possibilidades; atual++)
    {
        atribuido = atual;

        for (disco = 0; disco < Discos; disco++)
        {
            grafo[atual].posicao[disco] = atribuido % Pinos + 1; // Calcula o pino em que o disco está
            atribuido /= Pinos; // Atualiza o número para processar o próximo disco
        }
    }

    // Gera a matriz de adjacência com base nas regras
    for (int atual = 0; atual < Possibilidades; atual++)
    {
        for (int vizinho = 0; vizinho < Possibilidades; vizinho++)
        {
            if (movimento_valido(grafo[atual], grafo[vizinho]) == 1)
                matriz[atual][vizinho] = 1; // Movimento Válido
            else
                matriz[atual][vizinho] = 0; // Movimento Inválido
        }
    }
}

void exibir_matriz(vertice *grafo)
{
    for (int atual = 0; atual < Possibilidades; atual++)
    {
        printf("Vet. %.2d:", atual);
        for (int disco = 0; disco < Discos; disco++)
            printf(" %d", grafo[atual].posicao[disco]);
        printf("\n");
    }
}

int dijkstra(int matriz[][Possibilidades], int inicio, int fim)
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
                u = i;
        }

        visitados[u] = 1;

        for (v = 0; v < Possibilidades; v++)
        {
            if (!visitados[v] && matriz[u][v] && distancias[u] != INT_MAX &&
                distancias[u] + matriz[u][v] < distancias[v])
                distancias[v] = distancias[u] + matriz[u][v];
        }
    }

    return distancias[fim];
}

void menor_caminho(int matriz[][Possibilidades])
{
    int inicio = 0, resultado, fim;

    printf("\nInforme o qual o indice que a torre precisa chegar: ");
    scanf(" %d", &fim);

    LARGE_INTEGER inicio_w, fim_w, frequencia; 
    double tempo;

    QueryPerformanceFrequency(&frequencia); 
    QueryPerformanceCounter(&inicio_w); 

    resultado = dijkstra(matriz, inicio, fim);

    QueryPerformanceCounter(&fim_w); 

    tempo = (double)(fim_w.QuadPart - inicio_w.QuadPart) * 1000.0 / frequencia.QuadPart;

    printf("Menor caminho de %d para %d: %d\n", inicio, fim, resultado);
    printf("Tempo decorrido: %.5f milissegundos\n", tempo);
}

int main()
{
    vertice grafo[Possibilidades];
    int matriz_adjacencia[Possibilidades][Possibilidades];

    gerar_matriz_adjacencia(grafo, matriz_adjacencia);
    exibir_matriz(grafo);

    menor_caminho(matriz_adjacencia);
    return 0;
}