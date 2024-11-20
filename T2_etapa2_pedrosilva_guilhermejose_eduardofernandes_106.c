/*
 NOTA (PEDRO):
 * Eu usei ponteiros para mudar os valores das structs usando funções.
 * Basicamente, você não precisa igualar as structs à função para trocar o seu valor, apenas chamar a função e colocar uma referência da struct
 * Por exemplo:

-   rest_t rest;
-   lerrest(&rest);

 * Fiz isso pq achei que isso fosse mais fácil de entender do que se fosse assim:

-   rest_t rest;
-   rest = lerrest();

 * Mas podem mudar se acharem melhor
*/

#include <stdio.h>
#include <string.h>

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

//Funções para operar as structs:

    void renomearrest(rest_t *r)
    {
        printf("Escreva o novo nome: "); 
        //trocar o valor do nome do restaurante apontado pelo ponteiro
        scanf(" %[^\n]", r->nome);
    }

    void deletarrest(rest_t *r)
    {
        char opc;
        //perguntar se o usuario realmente quer deletar o restaurante
        printf("Voce tem certeza que deseja deletar o restaurante? NAO HA COMO REVERTER DEPOIS! (S/N): "); scanf(" %c", &opc);
        
        if(opc == 's' || opc == 'S')
        {
            //mudar o código do restaurante apontado pelo ponteiro para -1 e trocar o nome para " "
            (*r).codrest = -1;
            strcpy((*r).nome, " "); 
        }
    }

    void renomearprato(struct prato *p)
    {
        printf("Escreva o novo nome: ");
        //trocar o valor da descrição do prato apontado pelo ponteiro
        scanf(" %[^\n]", p->desc);
    }

    void deletarprato(struct prato *p)
    {
        char opc;
        //perguntar se o usuario realmente quer deletar o prato
        printf("Voce tem certeza? Nao ha como reverter depois! (S/N): "); scanf(" %c", &opc);
        
        if(opc == 's' || opc == 'S')
        {
            //mudar o código do prato apontado pelo ponteiro para -1, trocar a descrição para " " e configurar o valor para 0
            (*p).codprat = -1;
            (*p).preco = 0.00;
            strcpy((*p).desc, " ");
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

//Loops para operação de structs

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

            //opções do prato
            switch(opc)
            {
                case 1:
                    renomearprato(p);
                    break;
                
                case 2:
                    deletarprato(p);
                    break;

                case 0:
                    return;
            }
        }
    }

    //escrever e printar o cardápio do restaurante
    void vercardapio(rest_t *rest)
    {
        int opc = !0;
        //loop
        while(opc != 0)
        {
            printf("*********************************************************\n");
            //printar todos os pratos que não foram deletados (tem código > 0)
            for(int i = 0; i < N_PRATOS; i ++)
                if(rest->cardapio[i].codprat > 0)
                    printf("(#%05d) - %s.....R$%.2lf\n", rest->cardapio[i].codprat, rest->cardapio[i].desc, rest->cardapio[i].preco);


            printf("Digite o codigo do prato para ver mais informacoes ou 0 para voltar:\n\n");
            printf("> "); scanf("%d", &opc);

            //se o usuário digitar o nome de um prato, escrever as informações do prato e abrir configurações

            //passar por todos os pratos
            for(int j = 0; j < N_PRATOS; j ++)
                if(rest->cardapio[j].codprat == opc) //se o prato que abrimos for o que o usuário digitou
                {
                    printf("Codigo do prato: %d\nCodigo do restaurante: %d\nDescricao: %s\nPreco: R$%.2lf\n", rest->cardapio[j].codprat, rest->codrest, rest->cardapio[j].desc, rest->cardapio[j].preco);
                    verprato(&(rest->cardapio[j]));
                }
        }
    }

    //logar no restaurante e mostrar opções
    void logrest(rest_t *r)
    {
        int opc = !0;

        while(opc != 0)
        {
            //para a interface, ignorar
            printf("Restaurante %s (codigo #%05d)\n\n", r->nome, r->codrest);
            printf("---------------------------------------------------------\n");
            printf("Opcoes:\n");
            printf("1 - Ver cardapio\n");
            printf("2 - Renomear\n");
            printf("3 - Deletar\n");
            printf("0 - Logout\n\n");
            printf("> "); scanf("%d", &opc);


            //switch para as opções possíveis
            switch(opc)
            {
                case 1:
                    vercardapio(r);
                    break;

                case 2:
                    renomearrest(r);
                    break;

                case 3:
                    deletarrest(r);
                    return;
                    break;
                
                //não é necessário usar break após o return
                case 0:
                    return;
            }
        } 
    }

//Função main:

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
        if(rests[i].codrest == logged && logged >= 0)
        {
            logrest(&rests[i]);
        }
    }

    return 0;
}
