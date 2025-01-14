#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>

#define VERTICES 6 

int encontrar_max_confiabilidade(float confiabilidade[], bool visitado[]) 
{
    float max_valor = -1.0;
    int max_indice = -1;

    for (int i = 0; i < VERTICES; i++) 
    {
        if (!visitado[i] && confiabilidade[i] > max_valor) 
        {
            max_valor = confiabilidade[i];
            max_indice = i;
        }
    }

    return max_indice;
}

void dijkstra(float grafo[VERTICES][VERTICES], int origem, float confiabilidade[], bool visitado[], int caminho[]) 
{
    for (int i = 0; i < VERTICES; i++) 
    {
        confiabilidade[i] = 0.0;
        visitado[i] = false;
        caminho[i] = -1;
    }

    confiabilidade[origem] = 1.0; 

    for (int i = 0; i < VERTICES - 1; i++) 
    {
        int u = encontrar_max_confiabilidade(confiabilidade, visitado);

        if (u == -1) break;

        visitado[u] = true;

        for (int v = 0; v < VERTICES; v++) 
        {
            if (grafo[u][v] > 0 && !visitado[v]) 
            {
                float nova_confiabilidade = confiabilidade[u] * grafo[u][v];
                
                if (nova_confiabilidade > confiabilidade[v]) 
                {
                    confiabilidade[v] = nova_confiabilidade;
                    caminho[v] = u;
                }
            }
        }
    }
}

void mostrar_caminho(int origem, int destino, int caminho[], float confiabilidade[]) 
{
    if (confiabilidade[destino] == 0.0) printf("Nao existe caminho entre %d e %d.\n", origem, destino);
    
    else
    {
        printf("Caminho mais confiavel de %d para %d com confiabilidade %.6f:\n", origem, destino, confiabilidade[destino]);

        int atual = destino;
        int pilha[VERTICES], topo = -1;

        while (atual != -1) 
        {
            pilha[++topo] = atual;
            atual = caminho[atual];
        }

        while (topo >= 0)
            printf("-> %d ", pilha[topo--]);
        
        printf("\n");
    }
}

int main() 
{
    float confiabilidade[VERTICES];
    bool visitado[VERTICES];
    int caminho[VERTICES];

    float grafo[VERTICES][VERTICES] = {
        {0, 0.7, 0.4, 0.0, 0.0, 0.0}, 
        {0.7, 0, 0.6, 0.8, 0.0, 0.0}, 
        {0.4, 0.6, 0, 0.5, 0.8, 0.0}, 
        {0.0, 0.8, 0.5, 0, 0.7, 0.9}, 
        {0.0, 0.0, 0.8, 0.7, 0, 0.6}, 
        {0.0, 0.0, 0.0, 0.9, 0.6, 0} 
    };

    int origem, destino;

    printf("\nInforme o vertice de origem: ");
    scanf(" %d", &origem);
    printf("\nInforme o vertice de destino: ");
    scanf(" %d", &destino);

    dijkstra(grafo, origem, confiabilidade, visitado, caminho);

    mostrar_caminho(origem, destino, caminho, confiabilidade);

    return 0;
}
