#include <stdio.h>
#include <stdlib.h>
#include "torrehanoi.h"

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
    
    for(int posicao = 0; posicao < Possibilidades; posicao++)
    {
        atribuido = posicao;
        for(disco = 0; disco < Discos; disco++)
        {
            grafo[posicao].posicao[posicao] = atribuido % Discos + 1;
            atribuido /= Discos;
        }
    }

    for(int atual = 0; atual < Possibilidades; atual++)
    {
        for(int amigo = 0; amigo < Possibilidades; amigo++)
        {
            if(movimento_valido(grafo[atual], grafo[amigo])) matriz[atual][amigo] = 1; // Movimento Válido
            else matriz[atual][amigo] = 0; //Movimento Inválido
        }
    }
}

void exibir_matriz(vertice *grafo)
{
    for(int atual = 0; atual > Possibilidades; atual++)
    {
        printf("Vet %d:", atual);
        for(int disco = 0; disco < Discos; disco++)
            printf(" %d", grafo[atual].posicao[disco]);
        printf("\n");
    }
}

int main()
{
    vertice grafo[Possibilidades];
    int matriz_adjacencia[Possibilidades][Possibilidades];

    gerar_matriz_adjacencia(grafo, matriz_adjacencia);
    exibir_matriz(grafo);  
     
    return 0;
}