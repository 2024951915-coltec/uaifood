#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct restaurante{
    char nome[50];
    int codigo;
}restaurante;

typedef struct prato{
    char nomepr[50];
    int codigopr;
    int codigores;
    float preco;
}prato;

int main(){
    printf("**************************************************");
    printf("\nuaiFood - Restaurante");
    printf("\n**************************************************");

    restaurante res[3];
    prato pratos[4];
    
    for(int i = 0; i < 3; i++){
    printf("\nCadastre o codigo e nome do restaurante %d:", i + 1);
    scanf("%d", res[i].codigo);
    scanf("%s", res[i].nome);

    printf("\nCadastre codigo do prato, codigo do restaurante, descricao e preco dos pratos do restaurante Tempero Mineiro:");
 for(int j = 0; j<4; j++){    
 scanf("%d", pratos[i].codigopr);
 scanf("%d", pratos[i].codigores);
 scanf("%s", pratos[i].nomepr);
 scanf("%f", pratos[i].preco);
    }
}
return 0;
}