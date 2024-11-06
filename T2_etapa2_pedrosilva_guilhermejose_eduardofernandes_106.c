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

void deletarrest(rest_t *r)
{
    char opc;

    printf("Voce tem certeza? Nao ha como reverter depois! (S/N): "); scanf(" %c", &opc);
    
    if(opc == 's' || opc == 'S')
    {
        r->codrest = -1;
        *r->nome = "";
    }
}

void renomearrest(rest_t *r)
{
    printf("Escreva o novo nome: "); scanf("%[^\n]", r->nome);
}

void renomearprato(struct prato *p)
{
    printf("Escreva o novo nome: "); scanf("%[^\n]", p->desc);
}

void deletarprato(struct prato *p)
{
    char opc;

    printf("Voce tem certeza? Nao ha como reverter depois! (S/N): "); scanf(" %c", &opc);
    
    if(opc == 's' || opc == 'S')
    {
        p->codprat = -1;
        *p->desc = "";
    }
}


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

void verprato(struct prato *p)
{
    int opc = !0;
    while(opc != 0)
    {
        printf("O que deseja fazer com esse prato?\n");
        printf("1 - Renomear\n");
        printf("2 - Deletar\n");
        printf("0 - Voltar\n\n");

        printf("> "); scanf("%d", &opc);

        switch(opc)
        {
            case 1:


            default: break;
        }
    }
}

//escrever e printar o cardápio do restaurante
void vercardapio(rest_t *rest)
{
    int opc = !0;
    while(opc != 0)
    {
        printf("*********************************************************\n");
        for(int i = 0; i < N_PRATOS; i ++)
        {
            if(rest->cardapio[i].codprat > 0)
                printf("(#%05d) - %s.....R$%.2lf\n", rest->cardapio[i].codprat, rest->cardapio[i].desc, rest->cardapio[i].preco);
            else 
                printf("Prato vazio\n");
        }

        printf("Digite o codigo do prato para ver mais informacoes ou 0 para voltar:\n\n");

        printf("> "); scanf("%d", &opc);

        //se o usuário digitar o nome de um prato, escrever as informações do prato 
        for(int j = 0; j < N_PRATOS; j ++)
            if(rest->cardapio[j].codprat == opc)
            {
                printf("Codigo do prato: %d\nCodigo do restaurante: %d\nDescricao: %s\nPreco: R$%.2lf\n", rest->cardapio[j].codprat, rest->codrest, rest->cardapio[j].desc, rest->cardapio[j].preco);
            }
    }
}

//logar no restaurante e mostrar opções
void logrest(rest_t *r)
{
    printf("Restaurante %s (codigo #%05d)\n\n", r->nome, r->codrest);

    int opc = !0;

    while(opc != 0)
    {
        printf("---------------------------------------------------------\n");
        printf("Opcoes:\n");
        printf("1 - Ver cardapio\n");
        printf("2 - Renomear\n");
        printf("3 - Deletar\n");
        printf("0 - Logout\n\n");
        printf("> "); scanf("%d", &opc);

        switch(opc)
        {
            case 1:
                vercardapio(r);
                break;

            case 2:
                renomearrest(r);

            case 3:
                deletarrest(r);
            
            case 0:
                return;

            default: break;
        }
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
            logrest(&rests[i]);
        }
    }

    return 0;
}
