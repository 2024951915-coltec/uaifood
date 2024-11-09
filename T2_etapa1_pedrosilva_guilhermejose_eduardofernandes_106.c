<<<<<<< HEAD
#include <stdio.h>

#define STRLEN 20
#define N_PRATOS 4
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

typedef struct rest rest_t;

void lerpratos(int numerodoprato, struct prato *pratos)
{
    struct prato p;

    printf("Escreva o codigo, preco e descricao do prato %d:\n", numerodoprato); scanf("%d %lf %s", &p.codprat, &p.preco, p.desc);
    printf("\n");

    *pratos = p;
}

void lerrests(int numerodorest, rest_t *rests)
{
    rest_t r;

    printf("Digite o codigo e nome do restaurante %d:\n", numerodorest); scanf("%d %s", &r.codrest, r.nome);
    printf("---------------------------------------------------------\n");

    for(int i = 0; i < N_PRATOS; i ++)
        lerpratos(i + 1, &r.cardapio[i]);

    printf("---------------------------------------------------------\n");

    *rests = r;
}

void lercardapio(rest_t rest)
{
    int opc = !0;
    while(opc != 0)
    {
        printf("*********************************************************\n");
        for(int i = 0; i < N_PRATOS; i ++)
        printf("(#%05d) - %s.....R$%.2lf\n", rest.cardapio[i].codprat, rest.cardapio[i].desc, rest.cardapio[i].preco);

        printf("Digite o codigo do prato para ver mais informacoes ou 0 para voltar:\n\n");

        printf("> "); scanf("%d", &opc);

        if(opc == 0)
            return;
        for(int j = 0; j < N_PRATOS; j ++)
            if(rest.cardapio[j].codprat == opc)
                printf("Codigo do prato: %d\nCodigo do restaurante: %d\nDescricao: %s\nPreco: R$%.2lf\n", rest.cardapio[j].codprat, rest.codrest, rest.cardapio[j].desc, rest.cardapio[j].preco);
    }
}

void logrest(rest_t rest)
{
    printf("Restaurante %s (codigo #%05d)\n\n", rest.nome, rest.codrest);

    int opc = !0;

    while(opc != 0)
    {
        printf("---------------------------------------------------------\n");
        printf("Opcoes:\n");
        printf("1 - Ver cardapio\n");
        printf("0 - Logout\n\n");
        printf("> "); scanf("%d", &opc);

        if(opc == 1)
            lercardapio(rest);
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

    while(logged >= 0)
    {
        printf("---------------------------------------------------------\n");
        printf("Codigo do restaurante para login (digite -1 para sair): "); scanf("%d", &logged);

        for(int i = 0; i < N_REST; i ++)
        if(rests[i].codrest == logged)
        {
            logrest(rests[i]);
        }
    }

    return 0;
}
=======
#include <stdio.h>

//largura das strings
#define STRLEN 20
//número máximo de pratos
#define N_PRATOS 4
//número máximo de restaurantes
#define N_REST 3

//structure para os pratos. OBS: Chame usando "struct prato"
struct prato{
    int codprat;
    double preco;
    char desc[STRLEN];
};

//structure para os restaurantes
struct rest {
    int codrest;
    char nome[STRLEN];
    struct prato cardapio[N_PRATOS];
};


//definir "struct rest" como um tipo "rest_t"
typedef struct rest rest_t;


//ler os pratos que o usuário digitar
void lerpratos(int numerodoprato, struct prato *pratos)
{
    struct prato p;

    printf("Escreva o codigo, preco e descricao do prato %d:\n", numerodoprato); scanf("%d %lf %[^\n]", &p.codprat, &p.preco, p.desc);
    printf("\n");

    *pratos = p;
}

//ler os restaurantes que o usuário digitar
void lerrests(int numerodorest, rest_t *rests)
{
    rest_t r;

    printf("Digite o codigo e nome do restaurante %d:\n", numerodorest); scanf("%d %[^\n]", &r.codrest, r.nome);
    printf("---------------------------------------------------------\n");

    //ler todos os pratos do restaurante
    for(int i = 0; i < N_PRATOS; i ++)
        lerpratos(i + 1, &r.cardapio[i]);

    printf("---------------------------------------------------------\n");

    *rests = r;
}

//escrever e printar o cardápio do restaurante
void lercardapio(rest_t rest)
{
    int opc = !0;
    while(opc != 0)
    {
        printf("*********************************************************\n");
        for(int i = 0; i < N_PRATOS; i ++)
        printf("(#%05d) - %s.....R$%.2lf\n", rest.cardapio[i].codprat, rest.cardapio[i].desc, rest.cardapio[i].preco);

        printf("Digite o codigo do prato para ver mais informacoes ou 0 para voltar:\n\n");

        printf("> "); scanf("%d", &opc);

        //se o usuário digitar o nome de um prato, escrever as informações do prato 
        for(int j = 0; j < N_PRATOS; j ++)
            if(rest.cardapio[j].codprat == opc)
                printf("Codigo do prato: %d\nCodigo do restaurante: %d\nDescricao: %s\nPreco: R$%.2lf\n", rest.cardapio[j].codprat, rest.codrest, rest.cardapio[j].desc, rest.cardapio[j].preco);
    }
}

//logar no restaurante e mostrar opções
void logrest(rest_t rest)
{
    printf("Restaurante %s (codigo #%05d)\n\n", rest.nome, rest.codrest);

    int opc = !0;

    while(opc != 0)
    {
        printf("---------------------------------------------------------\n");
        printf("Opcoes:\n");
        printf("1 - Ver cardapio\n");
        printf("0 - Logout\n\n");
        printf("> "); scanf("%d", &opc);

        if(opc == 1)
            lercardapio(rest);
    } 
}

int main(void)
{
    rest_t rests[N_REST];

    //restaurante no qual o usuário está logado
    int logged = 1;

    printf("*********************************************************\n");
    printf("                  UaiFood - Restaurante                  \n");
    printf("*********************************************************\n\n");
    
    //ler todos os restaurantes
    for (int i = 0; i < N_REST; i ++)
        lerrests(i + 1, &rests[i]);

    printf("LOGIN UAIFOOD\n\n");

    //loop do programa
    while(logged >= 0)
    {
        printf("---------------------------------------------------------\n");
        printf("Codigo do restaurante para login (digite -1 para sair): "); scanf("%d", &logged);

        for(int i = 0; i < N_REST; i ++)
        if(rests[i].codrest == logged)
        {
            logrest(rests[i]);
        }
    }

    return 0;
}
>>>>>>> c4b3d154163a40f17a9e95fbe50756ff59ea5be4
