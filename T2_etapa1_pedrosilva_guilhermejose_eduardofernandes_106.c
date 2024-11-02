//TODO: Fazer alguma forma de impedir o usuário de digitar o mesmo código duas vezes

#include <stdio.h>

//máximo de caracteres
#define STRLEN 20

//máximo de pratos p/ restaurante
#define N_PRATOS 4

//máximo de restaurantes
#define N_REST 3

struct prato{
    int codprat;
    double preco;
    char desc[STRLEN];
};

struct rest {
    int codrest;
    char nome[STRLEN];
    struct prato cardapio[N_PRATOS];
};

//Definir a estrutura "rest" como tipo "rest_t"
typedef struct rest rest_t;

//Não julguei necessário criar um tipo específico para os pratos - Pedro

//inclusive, se forem fazer algum comentário para expressar alguma opinião sobre o código (que não seja explicando o que ele faz) favor dizer o seu nome

//Lê a struct de um prato
void lerpratos(int numerodoprato, struct prato *pratos)
{
    struct prato p;

    printf("Escreva o codigo, preco e descricao do prato %d:\n", numerodoprato); scanf("%d %lf %s", &p.codprat, &p.preco, p.desc);
    printf("\n");

    *pratos = p;
}

//Ler a struct de um restaurante
void lerrests(int numerodorest, rest_t *rests)
{
    rest_t r;

    printf("Digite o codigo e nome do restaurante %d:\n", numerodorest); scanf("%d %s", &r.codrest, r.nome);
    printf("---------------------------------------------------------\n");

    //usar função lerpratos para ler os pratos servidos por esse restaurante
    for(int i = 0; i < N_PRATOS; i ++)
        lerpratos(i + 1, &r.cardapio[i]);

    printf("---------------------------------------------------------\n");

    *rests = r;
}

//imprime o cardápio de um restaurante e fornesce mais informações sobre um prato em específico
void vercardapio(rest_t rest)
{
    int opc = !0;

    //loop que para quando o usuário digita um valor menor que 0
    while(opc != 0)
    {
        printf("*********************************************************\n");
        for(int i = 0; i < N_PRATOS; i ++)
        printf("(#%05d) - %s.....R$%.2lf\n", rest.cardapio[i].codprat, rest.cardapio[i].desc, rest.cardapio[i].preco);

        printf("Digite o codigo do prato para ver mais informacoes ou 0 para voltar:\n\n");

        printf("> "); scanf("%d", &opc);

        //se o valor for zero, termine a função
        //esse IF pode ser removido se não fizer diferença (preguiça de testar)
        if(opc == 0)
            return;
        //verifica se o número digitado é o código de algum dos pratos
        for(int j = 0; j < N_PRATOS; j ++)
            if(rest.cardapio[j].codprat == opc) //se for, escreva todas as informações sobre aquele prato
                printf("Codigo do prato: %d\nCodigo do restaurante: %d\nDescricao: %s\nPreco: R$%.2lf\n", rest.cardapio[j].codprat, rest.codrest, rest.cardapio[j].desc, rest.cardapio[j].preco);
    }
}


//dá as opções para o usuário após fazer o login
//não tem muito o que explicar honestamente
void logrest(rest_t rest)
{
    printf("Restaurante %s (codigo #%05d)\n\n", rest.nome, rest.codrest);

    int opc = !0;

    //loop que para quando o usuário digita um valor menor que 0
    while(opc != 0)
    {
        printf("---------------------------------------------------------\n");
        printf("Opcoes:\n");
        printf("1 - Ver cardapio\n");
        printf("0 - Logout\n\n");
        printf("> "); scanf("%d", &opc);

        if(opc == 1)
            vercardapio(rest);
    } 
}

int main(void)
{
    rest_t rests[N_REST];
    int logged = 1;

    printf("*********************************************************\n");
    printf("                  UaiFood - Restaurante                  \n");
    printf("*********************************************************\n\n");
    
    for (int i = 0; i < N_REST; i ++)
        lerrests(i + 1, &rests[i]);

    printf("LOGIN UAIFOOD\n\n");

    //loop que para quando o usuário digita um valor menor que 0
    while(logged >= 0)
    {
        printf("---------------------------------------------------------\n");
        printf("Codigo do restaurante para login (digite -1 para sair): "); scanf("%d", &logged);

        //verifica se o código digitado pelo usuário é o de algum dos restaurantes
        for(int i = 0; i < N_REST; i ++)
            if(rests[i].codrest == logged)
            {
                logrest(rests[i]);
            }
    }

    return 0;
}
