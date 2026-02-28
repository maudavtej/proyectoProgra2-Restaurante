#include <stdio.h>
#include <string.h>
#include <ctype.h>
typedef struct 
{
    char nombre[50];
    int precio;
    char diapromo[20];
    int numComp;    
    union opciones
    {
        char comp[20];
        int desc;
    };
}marzo;
typedef enum {lun=1,mar,mier,juev,vier,sab,dom}semana;




int eleccionD(){
    int fin = 0;
    marzo dias[7]={
        {"Lunes de queso", 49,"Lunes", 1},
        {"Martes de Pareja", 169,"Martes", 3},
        {"Miercoles de Cono", 129,"Miercoles", 2},
        {"Jueves del Rey", 129,"Jueves", 2},
        {"Viernes Whoper", 139,"Viernes", 2},
        {"Sabado de amigos", 99,"Sabado", 3},
        {"Domingo de Rodeo", 59,"Domingo", 1},

    };
    int opcion,opcCom, opc3;
    do{
    printf("Elija un dia de la semana (1-7):\n");
    printf("1. Lunes\n");
    printf("2. Martes\n");
    printf("3. Miercoles\n");
    printf("4. Jueves\n");
    printf("5. Viernes\n");
    printf("6. Sabado\n");
    printf("7. Domingo\n");
    printf("8. Salir\n");
    scanf("%d", &opcion);
    
    switch (opcion)
    {
    case 1:
        printf("PROMO:%s\n", dias[0].nombre);
        printf("PRECIO:$%d\n", dias[0].precio);
        printf("DIA:%s\n", dias[0].diapromo );
        printf("COMPONENTES:#%d\n", dias[0].numComp);
        printf("1.Elegir un complemento\n2.Aceptar descuento\n");
        scanf("%d", &opcCom);
        if (opcCom==1)
        {
            printf("1.Refresco\n2.Cono\n3.Empanada\n");
            scanf("%d", &opc3);
            switch (opc3)
            {
            case 1:
                
                break;
            
            default:
                break;
            }
        }
        
        break;
    case 2:
        printf("PROMO:%s\n", dias[1].nombre);
        printf("PRECIO:$%d\n", dias[1].precio);
        printf("DIA:%s\n", dias[1].diapromo );
        printf("COMPONENTES:#%d\n", dias[1].numComp);
        break;
    case 3:
        printf("PROMO:%s\n", dias[2].nombre);
        printf("PRECIO:$%d\n", dias[2].precio);
        printf("DIA:%s\n", dias[2].diapromo );
        printf("COMPONENTES:#%d\n", dias[2].numComp);
        break;
    case 4:
        printf("PROMO:%s\n", dias[3].nombre);
        printf("PRECIO:$%d\n", dias[3].precio);
        printf("DIA:%s\n", dias[3].diapromo );
        printf("COMPONENTES:#%d\n", dias[3].numComp);
        break;
    case 5:
        printf("PROMO:%s\n", dias[4].nombre);
        printf("PRECIO:$%d\n", dias[4].precio);
        printf("DIA:%s\n", dias[4].diapromo );
        printf("COMPONENTES:#%d\n", dias[4].numComp);
        break;
    case 6:
        printf("PROMO:%s\n", dias[5].nombre);
        printf("PRECIO:$%d\n", dias[5].precio);
        printf("DIA:%s\n", dias[5].diapromo );
        printf("COMPONENTES:#%d\n", dias[5].numComp);
        break;
    case 7:
        printf("PROMO:%s\n", dias[6].nombre);
        printf("PRECIO:$%d\n", dias[6].precio);
        printf("DIA:%s\n", dias[6].diapromo );
        printf("COMPONENTES:#%d\n", dias[6].numComp);
        break;
    case 8: 
        fin = 1;
        break;
    default:
        printf("Seleccione una opcion valida.");
        break;
    }
    } while (!fin);
    printf("Elija su complemento:\n");

    return 0;

}
int main(){
    eleccionD();
}
