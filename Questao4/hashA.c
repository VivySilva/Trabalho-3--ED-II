#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FUNC 1000
#define VET1 101
#define VET2 150

typedef struct Funcionario
{
    char matricula[7];
    char nome[30];
    char funcao[20];
    float salario;
} Funcionario;

typedef struct tabela_hash1
{
    int vetor[VET1];
    Funcionario func[VET1];
} t_hash1;

typedef struct tabela_hash2
{
    int vetor[VET2];
    Funcionario func[VET2];
} t_hash2;

Funcionario gerar_funcionarios()
{
    Funcionario Func;

    int numero = 1000000 + rand() % 9000000;
    
    snprintf(Func.matricula, sizeof(Func.matricula), "%d", numero);
    snprintf(Func.nome, sizeof(Func.nome), "Nome%d", rand() % 1000);
    snprintf(Func.funcao, sizeof(Func.funcao), "Func%d", rand() % 100);

    Func.salario = (float)(rand() % 10000) / 100.0;

    return Func;
}

void inicializar_tabela1(t_hash1 *tabela) 
{
    for (int i = 0; i < VET1; i++) 
        tabela->vetor[i] = -1;
}
void inicializar_tabela2(t_hash2 *tabela) 
{
    for (int i = 0; i < VET2; i++) 
        tabela->vetor[i] = -1;
}

int funcao_hash1(char *matricula) 
{
    char matri_aux[7];

    matri_aux[0] = matricula[5];
    matri_aux[1] = matricula[6];

    for (int i = 2; i < 6; i++)
        matri_aux[i] = matricula[i-2];
    
    matri_aux[6] = '\0';

    char extracao[4] = {matri_aux[1], matri_aux[3], matri_aux[5], '\0'};
    int extraido = atoi(extracao);

    int resto = extraido % VET1;
    
    return resto;
}
int funcao_hash2(char *matricula) 
{
    char matri_aux[7];

    matri_aux[0] = matricula[5];
    matri_aux[1] = matricula[6];

    for (int i = 2; i < 6; i++)
        matri_aux[i] = matricula[i-2];
    
    matri_aux[6] = '\0';

    char extracao[4] = {matri_aux[1], matri_aux[3], matri_aux[5], '\0'};
    int extraido = atoi(extracao);

    int resto = extraido % VET2;
    
    return resto;
}

int resolver_colisao1(t_hash1 *tabela, Funcionario *funcionario, int posicao)
{
    int colisoes = 0;   
    int tentativas = 0; 
    int sucesso = 0;   

    while (tabela->vetor[posicao] != -1 && tentativas < VET1)
    {
        colisoes++; 
        tentativas++;

        posicao += (funcionario->matricula[0] - '0');
    }

    if (tentativas >= VET1) sucesso = -1; 

    if (sucesso != -1) 
    { 
        tabela->vetor[posicao] = 1;  
        tabela->func[posicao] = *funcionario;
    }

    return sucesso == -1 ? -1 : colisoes;
}
int resolver_colisao2(t_hash2 *tabela, Funcionario *funcionario, int posicao)
{
    int colisoes = 0;   
    int tentativas = 0; 
    int sucesso = 0;   

    while (tabela->vetor[posicao] != -1 && tentativas < VET2)
    {
        colisoes++; 
        tentativas++;

        posicao += (funcionario->matricula[0] - '0');
    }

    if (tentativas >= VET2) sucesso = -1; 

    if (sucesso != -1) 
    { 
        tabela->vetor[posicao] = 1;  
        tabela->func[posicao] = *funcionario;
    }

    return sucesso == -1 ? -1 : colisoes;
}

void inserir_na_tabela1(t_hash1 *tabela, Funcionario func, int *quant_colisoes)
{
    int indice_resto = funcao_hash1(func.matricula);

    int colisoes = resolver_colisao1(tabela, &func, indice_resto);

    if (colisoes != -1) *quant_colisoes += colisoes; 
}
void inserir_na_tabela2(t_hash2 *tabela, Funcionario func, int *quant_colisoes)
{
    int indice_resto = funcao_hash2(func.matricula);

    int colisoes = resolver_colisao2(tabela, &func, indice_resto);

    if (colisoes != -1) *quant_colisoes += colisoes; 
}

int main()
{
    srand(time(NULL));
    
    t_hash1 tabela1;
    t_hash2 tabela2;
    inicializar_tabela1(&tabela1);
    inicializar_tabela2(&tabela2);
    
    int quant_colisoes101 = 0;
    int quant_colisoes150 = 0;
    
    for (int i = 0; i < FUNC; i++)
    {
        Funcionario novo_func = gerar_funcionarios();
        inserir_na_tabela1(&tabela1, novo_func, &quant_colisoes101);
        inserir_na_tabela2(&tabela2, novo_func, &quant_colisoes150);
    }

    printf("Quantidade de colisoes com vet101: %d\n", quant_colisoes101);
    printf("Quantidade de colisoes com vet150: %d\n", quant_colisoes150);
    
    return 0;
}