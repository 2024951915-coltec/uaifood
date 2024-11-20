#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//largura das strings
#define STRLEN 20
//número máximo de pratos
#define N_PRATOS 4
//número máximo de restaurantes
#define N_REST 3
//número máximo de usuários
#define N_USUARIO 2

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

struct usuario {
    int id;
    char nome[STRLEN];
    struct prato *carrinho;
    int n_prat;
};

typedef struct rest rest_t;
typedef struct usuario user_t;

//Funções para operar as structs:

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

    void leruser(int numerodousuario, user_t *user)
    {
        user_t u;

        printf("Digite o codigo e nome do usuario %d:\n", numerodousuario); scanf("%d %[^\n]", &u.id, u.nome);
        u.carrinho = NULL;
        u.n_prat = 0;

        *user = u;
    }


//loops

    void vercard(user_t *u, rest_t rest)
    {
        int opc = !0;
        int validprat = 0;

        printf("%s (#%05d)\n", rest.nome, rest.codrest);
        printf("Escolha um prato:\n");

        while(opc != 0)
        {
            
            for(int i = 0; i < N_PRATOS; i ++)
                printf("%d - %s (Preco: R$%.2f)\n", rest.cardapio[i].codprat, rest.cardapio[i].desc, rest.cardapio[i].preco);
            printf("Ou digite 0 para voltar\n\n");
            
            printf("> "); scanf("%d", &opc);

            for(int i = 0; i < N_PRATOS; i ++)
                if(rest.cardapio[i].codprat == opc && opc != 0)
                {
                    validprat ++;
                    u->n_prat ++;

                    u->carrinho = (struct prato *) realloc(u->carrinho, u->n_prat * sizeof(struct prato));
                    u->carrinho[u->n_prat - 1] = rest.cardapio[i];
                    
                    if(u->carrinho != NULL)
                        printf("\n%s (#%05d) adicionado ao carrinho!\n\n", rest.cardapio[i].desc, rest.cardapio[i].codprat);
                    else 
                    {
                        printf("Ocorreu um problema inesperado\n");
                        exit(EXIT_FAILURE);
                    }
                }

            if(validprat == 0)
                printf("Prato invalido!\n\n");
        }
    }

    void loginuser(user_t *u, rest_t r[N_REST])
    {
        int opc = 1;
        int validrest = 0;

        while(opc >= 0)
        {
            printf("---------------------------------------------------------\n");
            printf("Bem-vindo, %s (#%05d)!\n", u->nome, u->id);
            printf("Selecione um restaurante:\n\n");

            for(int i = 0; i < N_REST; i++)
                printf("%d - %s\n", r[i].codrest, r[i].nome);
            printf("Digite 0 para finalizar sua compra e -1 para logout\n\n");

            printf("> "); scanf("%d", &opc);

            if(opc == 0)
            {
                double total = 0;
                int tmp_pratos = 0;

                if(u->n_prat > 0)
                {
                    printf("Reveja seu pedido, %s:\n", u->nome);
                    printf("**************************************************\n");
                    
                    for(int i = 0; i < N_REST; i ++)
                    {
                        printf("%s:\n\n", r[i].nome);

                        for(int j = 0; j < N_PRATOS; j ++)
                        {
                            for(int k = 0; k < u->n_prat; k ++)
                                if(r[i].cardapio[j].codprat == u->carrinho[k].codprat)
                                {
                                    total += r[i].cardapio[j].preco;
                                    tmp_pratos ++;
                                }

                            if(tmp_pratos > 0 && tmp_pratos != 1)
                                printf("- %dx %s - R$%.2f (Totalizando R$%.2f)\n", tmp_pratos, r[i].cardapio[j].desc, r[i].cardapio[j].preco, tmp_pratos * r[i].cardapio[j].preco);
                            else if(tmp_pratos == 1)
                                printf("- %s - R$%.2f\n", r[i].cardapio[j].desc, r[i].cardapio[j].preco);

                            tmp_pratos = 0;
                        }
                        printf("\n\n- TOTAL: R$%.2f\n", total);
                        printf("**************************************************\n\n");

                        printf("Qual sera a forma de pagamento?\n");
                        printf("1 - Dinheiro\n");
                        printf("2 - PIX\n");
                        printf("3 - Cartao de debito\n");
                        printf("4 - Cartao de credito\n");
                        printf("0 - Cancelar compra\n");

                        printf("> "); scanf(" %[^\n]");

                        free(u->carrinho);
                        u->carrinho = NULL;
                        u->n_prat = 0;
                    }
                }
            }
            else if(opc > 0)
            {
                for(int i = 0; i < N_REST; i ++)
                    if(r[i].codrest == opc && opc != 0)
                    {
                        vercard(u, r[i]);
                        validrest ++;
                    }

                if(validrest == 0)
                    printf("Restaurante invalido!\n\n");     
            }    
        }
    }


//Função main:

int main(void)
{
    rest_t rests[N_REST];
    user_t users[N_USUARIO];

    //o usuário que está logado
    int login = 1;

    //quantos restaurantes foram logados
    int werelogged = 0;

    printf("*********************************************************\n");
    printf("                    UaiFood - Pedidos                    \n");
    printf("*********************************************************\n\n");
    
    //ler todos os restaurantes
    for (int i = 0; i < N_REST; i ++)
        lerrests(i + 1, &rests[i]);



    for(int i = 0; i < N_USUARIO; i ++)
        leruser(i + 1, &users[i]);

    printf("LOGIN UAIFOOD\n");

    //loop do programa
    while(login >= 0)
    {
        printf("---------------------------------------------------------\n");
        printf("Codigo do usuario para login (digite -1 para sair): "); scanf("%d", &login);

        for(int i = 0; i < N_USUARIO; i ++)
            if(users[i].id == login && login >= 0)
            {
                loginuser(&users[i], rests);
                werelogged ++;
            }

        if(werelogged <= 0)
        {
            printf("Usuario invalido!\n\n");
        }
        
    }

    return 0;
}
