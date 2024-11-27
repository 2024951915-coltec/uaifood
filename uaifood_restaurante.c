#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//largura das strings
#define STRLEN 65

#define REST_DIR "dat/rest.txt"
#define PRAT_DIR "dat/prat.txt"
#define TEMP_DIR "dat/temp.txt"

#define NAO_E_PRATO -69

//structure para os pratos. OBS: Chame usando "struct prato"
struct prato{
    int codprat;
    int codrest;
    double preco;
    char desc[STRLEN];
};

//structure para os restaurantes
struct rest {
    int codrest;
    char nome[STRLEN];
};

//definir "struct rest" como um tipo "rest_t"
typedef struct rest rest_t;
typedef struct prato prato_t;

int ultimocodigo(const char *path, int rest)
{
    int ret = 1, i;
    FILE *f;
    f = fopen(path, "r");

    while(!feof(f))
    {
        if(!(rest < 0))
        {
            int restid;
            fscanf(f, "id:%d rest:%d", &i, &restid);

            if(i >= ret && rest == restid)
                ret = i;
        }
        else
        {
            fscanf(f, "id:%d", &i);

            if(i > ret)
                ret = i;
        }
    }

    return ret;
}

static void flinedel(const char *path, int id, int rest)
{
    FILE *fread;
    FILE *fwrite;

    fread = fopen(path, "r");
    fwrite = fopen(TEMP_DIR, "w");

    char buffer[STRLEN];
    int tmp_id;
    int tmp_rest;

    while(fgets(buffer, STRLEN, fread))
    {  
        if(rest > 0)
        {
            sscanf(buffer, "id:%d rest:%d", &tmp_id, &tmp_rest);

            if(!(tmp_id == id && tmp_rest == rest))
                fprintf(fwrite, buffer);
        }
        else 
        {
            sscanf(buffer, "id:%d", &tmp_id);

            if(tmp_id != id)
                fprintf(fwrite, buffer);
        }
    }

    fclose(fread);
    fclose(fwrite);

    fread = fopen(TEMP_DIR, "r");
    fwrite = fopen(path, "w");

    while(fgets(buffer, STRLEN, fread))
        fprintf(fwrite, buffer);

    fclose(fread);
    fclose(fwrite);
}

void sortintofile_rest(rest_t rest)
{
    FILE *fread;
    FILE *fwrite;

    fread = fopen(REST_DIR, "r");
    fwrite = fopen(TEMP_DIR, "w");

    rest_t tmp;
    int wasinserted = 0;

    while(!feof(fread))
    {
        fscanf(fread, "id:%d nome:%[^\n]\n", &tmp.codrest, tmp.nome);

        
        if(wasinserted == 0 && tmp.codrest > rest.codrest)
        {
            fprintf(fwrite, "id:%d nome:%s\nid:%d nome:%s\n", rest.codrest, rest.nome, tmp.codrest, tmp.nome);
            wasinserted = 1;
        }
        else
            fprintf(fwrite, "id:%d nome:%s\n", tmp.codrest, tmp.nome);
    }

    fclose(fread);
    fclose(fwrite);

    fread = fopen(TEMP_DIR, "r");
    fwrite = fopen(REST_DIR, "w");

    while(!feof(fread))
    {
        fscanf(fread, "id:%d nome:%[^\n]\n", &tmp.codrest, tmp.nome);
        fprintf(fwrite, "id:%d nome:%s\n", tmp.codrest, tmp.nome);
    }
        

    fclose(fread);
    fclose(fwrite);
}

void sortintofile_prat(prato_t prato)
{
    FILE *fread;
    FILE *fwrite;

    fread = fopen(PRAT_DIR, "r");
    fwrite = fopen(TEMP_DIR, "w");

    prato_t tmp;
    int wasinserted = 0;

    while(!feof(fread))
    {
        fscanf(fread, "id:%d rest:%d preco:%lf nome:%[^\n]\n", &tmp.codprat, &tmp.codrest, &tmp.preco, tmp.desc);

        if(tmp.codrest > prato.codrest && wasinserted == 0)
        {
            fprintf(fwrite, "id:%d rest:%d preco:%.2lf nome:%s\n", prato.codprat, prato.codrest, prato.preco, prato.desc);
            fprintf(fwrite, "id:%d rest:%d preco:%.2lf nome:%s\n", tmp.codprat, tmp.codrest, tmp.preco, tmp.desc);
            wasinserted = 1;
        }
        else if(tmp.codrest == prato.codrest && wasinserted == 0)
        {
            if(tmp.codprat > prato.codprat && wasinserted == 0)
            {
                fprintf(fwrite, "id:%d rest:%d preco:%.2lf nome:%s\n", prato.codprat, prato.codrest, prato.preco, prato.desc);
                fprintf(fwrite, "id:%d rest:%d preco:%.2lf nome:%s\n", tmp.codprat, tmp.codrest, tmp.preco, tmp.desc);
                wasinserted = 1;
            }
            else
                fprintf(fwrite, "id:%d rest:%d preco:%.2lf nome:%s\n", tmp.codprat, tmp.codrest, tmp.preco, tmp.desc);
        }
        else
            fprintf(fwrite, "id:%d rest:%d preco:%.2lf nome:%s\n", tmp.codprat, tmp.codrest, tmp.preco, tmp.desc);
    }

    fclose(fread);
    fclose(fwrite);

    fread = fopen(TEMP_DIR, "r");
    fwrite = fopen(PRAT_DIR, "w");

    while(!feof(fread))
    {
        fscanf(fread, "id:%d rest:%d preco:%lf nome:%[^\n]\n", &tmp.codprat, &tmp.codrest, &tmp.preco, tmp.desc);
        fprintf(fwrite, "id:%d rest:%d preco:%.2lf nome:%s\n", tmp.codprat, tmp.codrest, tmp.preco, tmp.desc);;
    }
        

    fclose(fread);
    fclose(fwrite);
}

//Funções para operar as structs:

    void recadrest(rest_t r)
    {
        FILE *f;
        f = fopen(REST_DIR, "a");

        fprintf(f, "id:%d nome:%s\n", r.codrest, r.nome);
        fclose(f);
    }

    void recadprato(prato_t p)
    {
        FILE *f;
        f = fopen(PRAT_DIR, "a");

        fprintf(f, "id:%d rest:%d preco:%g nome:%s\n", p.codprat, p.codrest, p.preco, p.desc);
        fclose(f);
    }

    void renomearrest(rest_t rest)
    {
        char new_name[STRLEN];
        printf("Escreva o novo nome: "); scanf(" %[^\n]", new_name);


        rest_t new_rest = rest;
        strcpy(new_rest.nome, new_name);

        flinedel(PRAT_DIR, rest.codrest, NAO_E_PRATO);
        sortintofile_rest(new_rest);
    }

    void deletarrest(int codrest)
    {
        char opc;
        //perguntar se o usuario realmente quer deletar o restaurante
        printf("Voce tem certeza que deseja deletar o restaurante? NAO HA COMO REVERTER DEPOIS! (S/N): "); scanf(" %c", &opc);
        
        if(opc == 's' || opc == 'S')
        {
            flinedel(REST_DIR, codrest, NAO_E_PRATO);
        }
    }

    void renomearprato(prato_t p)
    {
        char new_name[STRLEN];
        printf("Escreva o novo nome: "); scanf(" %[^\n]", new_name);

        prato_t new_prat = p;
        strcpy(new_prat.desc, new_name);

        flinedel(PRAT_DIR, p.codprat, p.codrest);
        sortintofile_prat(new_prat);
    }

    void deletarprato(int codrest, int codprat)
    {
        char opc;
        //perguntar se o usuario realmente quer deletar o prato
        printf("Voce tem certeza? Nao ha como reverter depois! (S/N): "); scanf(" %c", &opc);
        
        if(opc == 's' || opc == 'S')
        {
            flinedel(PRAT_DIR, codprat, codrest);
        }
    }

    //cadastrar um prato
    void cadnprato(int _codrest)
    {
        struct prato p;

        printf("Escreva o preco e descricao do prato:\n"); scanf("%lf %[^\n]", &p.preco, p.desc);

        p.codprat = ultimocodigo(PRAT_DIR, _codrest);
        p.codrest = _codrest;

        sortintofile_prat(p);

        printf("Adicionou prato \"%s\" para restaurante #%08d! (Codigo #%08d)", p.desc, p.codrest, p.codprat);
    }

    //cadastrar um restaurante
    void cadnrest()
    {
        FILE *f;
        rest_t r;

        f = fopen(REST_DIR, "w");

        printf("Digite nome do restaurante:\n"); scanf(" %[^\n]", r.nome);

        r.codrest = ultimocodigo(REST_DIR, NAO_E_PRATO);

        cadnprato(r.codrest);
        sortintofile_rest(r);

        printf("Criado restaurante \"%s\" (Codigo #%05d)", r.nome, r.codrest);
    }

//Loops para operação de structs

    void pratomenu(struct prato p)
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
                    deletarprato(p.codprat, p.codrest);
                    return;
                    break;

                case 0:
                    return;
            }
        }
    }

    //escrever e printar o cardápio do restaurante
    void vercardapio(rest_t rest)
    {
        int opc = !0;
        FILE *f;

        prato_t prat;
        prato_t *cardapio;

        //loop
        while(opc != 0)
        {
            f = fopen(PRAT_DIR, "r");

            printf("*********************************************************\n");
            //printar todos os pratos que não foram deletados (tem código > 0)
            while(!feof(f))
            {
                fscanf(f, "id:%d rest:%d preco:%lf nome:%[^\n]\n", &prat.codprat, &prat.codrest, &prat.preco, prat.desc);

                if(prat.codrest == rest.codrest)
                    printf(" %d - Ver prato \"%s\"\n", prat.codprat, prat.desc);
            }

            printf(" 0 - Cadastrar novo prato\n");
            printf("-1 - Voltar\n\n");
            printf("> "); scanf("%d", &opc);

            //se o usuário digitar o nome de um prato, escrever as informações do prato e abrir configurações

            switch(opc)
            {
                case 0:
                    cadnprato(rest.codrest);
                    break;
                
                case -1:
                    return;
                    break;
                
                default:
                    fclose(f);
                    f = fopen(PRAT_DIR, "r");
                    while(!feof(f))
                    {
                        fscanf(f, "id:%d rest:%d preco:%lf nome:%[^\n]\n", &prat.codprat, &prat.codrest, &prat.preco, prat.desc);
                        if(prat.codrest == rest.codrest && prat.codprat == opc)
                        {
                            printf("Codigo do prato: %d\nCodigo do restaurante: %d\nDescricao: %s\nPreco: R$%.2lf\n", prat.codprat, prat.codrest, prat.desc, prat.preco);
                            pratomenu(prat);
                        }
                    }
                    break;
            }
            
            fclose(f);
        }
    }

    //logar no restaurante e mostrar opções
    void restmenu(rest_t r)
    {
        int opc = !0;

        while(opc != 0)
        {
            //para a interface, ignorar
            printf("Restaurante %s (codigo #%05d)\n\n", r.nome, r.codrest);
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
                    deletarrest(r.codrest);
                    return;
                    break;
                
                //não é necessário usar break após o return
                case 0:
                    return;
            }
        } 
    }

void login()
{
    int opc = !0;
    FILE *f;

    rest_t rest;
    
    int logged = 0;

    while(logged >= 0)
    {
        printf("LOGIN UAIFOOD\n\n");
        printf("---------------------------------------------------------\n");
        printf("Codigo do restaurante para login (digite -1 para voltar): "); scanf("%d", &logged);

        f = fopen(REST_DIR, "r");

        while(!feof(f) && logged != 0)
        {
            fscanf(f, "id:%d nome:%[^\n]\n", &rest.codrest, rest.nome);
            if(rest.codrest == logged)
            {
                logged = 0;
                restmenu(rest);
            }
        }

        fclose(f);

        if(logged != 0)
            printf("\nRestaurante nao existe. Registre-o antes de tentar logar nele.\n\n");
    }
}
//Função main:

int main(void)
{
    int opc;
    while(opc != 0)
    {
        printf("*********************************************************\n");
        printf("                  UaiFood - Restaurante                  \n");
        printf("*********************************************************\n\n");
        printf("Gerencie ou registre seu restaurante\n\n");

        printf("1 - Cadastrar novo restaurante\n");
        printf("2 - Fazer login em restaurante ja existente\n");
        printf("0 - Sair\n\n");

        printf("> "); scanf("%d", &opc);

        switch(opc)
        {
            case 1:
                cadnrest();
                printf("Agora, faca login usando o codigo que voce registrou para gerenciar seu restaurante\n");
                break;
            
            case 2:
                login();
                break;

            case 0:
                printf("Ate mais!\n");
                return 0;
                break;

            default:
                break;
        }
    }
}
