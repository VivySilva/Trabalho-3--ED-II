#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define max_func 1000
#define max_vet 101

typedef struct Funcionario
{
    char matricula[7];
    char nome[7];
    char funcao[7];
    float salario;
}funcionario;

typedef struct tabela_hash
{
    int vetor[max_vet];
    funcionario func[max_func];
}t_hash;


funcionario gerar_funcionarios()
{
    funcionario Func;
    

    int numero = 1000000 + rand() % 9000000;
    snprintf(Func.matricula, sizeof(Func.matricula), "%d", numero);

    snprintf(Func.nome, sizeof(Func.nome), "Nome%d", rand() % 1000);
    snprintf(Func.funcao, sizeof(Func.funcao), "Func%d", rand() % 100);

    Func.salario = (float)(rand() % 10000) / 100.0;

    return Func;
    

}

void inicializar_tabela(t_hash *tabela) 
{
    for (int i = 0; i < max_vet; i++) {
        tabela->vetor[i] = -1;
    }
}

int funcao_hash(char *matricula) 
{
    char matri_aux[7];
    matri_aux[0] = matricula[5];
    matri_aux[1] = matricula[6];

    for(int i = 2; i < 6; i++)
    {
        matri_aux[i] = matricula[i-2];
    }
    matri_aux[6] = '\0';

    strcpy(matricula, matri_aux);

    char extracao[4];
    int j = 1;
    for(int i = 0; i < 3; i++)
    {
        extracao[i] = matricula[j];
        j += 2;
    }
    extracao[3] = '\0';

    int extraido = atoi(extracao);

    int resto = extraido % max_vet;

    int pri_digito = matricula[0] - '0';
    resto = resto + pri_digito;
    
    return resto;
}

int colisao(t_hash tabela, int resto)
{
    for(int i = 0; i < max_vet; i++)
    {
        if(tabela.vetor[i] == resto);
        resto +=
    }
}

int main()
{
    srand(time(NULL));
    funcionario *novo_func;
    novo_func = (funcionario *)malloc(100 * sizeof(funcionario));
    
    //for(int i = 0; i < 100; i++)
    //{
       //novo_func[i] = gerar_funcionarios();
    //}

    free(novo_func);
    return 0;
}