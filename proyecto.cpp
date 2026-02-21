#include <stdio.h>
#include <ctype.h>
#include <string.h>



void menuVentas(){

    int eleccion, cantidad;
    char productosA[50];
    printf("============ MENÚ ===========\n");
    printf("Elija una opción\n");
    printf("1.Hamburguesas\n2.Adicionales\n3.Combo\n");
    scanf("%d",&eleccion);
    switch (eleccion)
    {
    case 1:
        printf("======SABORES=====\n");
        printf("1.Sencilla\n2.Con queso\n3.Hawaiana\n4.Doble Queso\n");
        scanf("%d", &eleccion);
        switch (eleccion)
        {
        case 1:
            printf("1.Seleccionar ingredientes:\n2.Regresar al menú\n");
            break;
        
        default:
            break;
        }
        break;
    case 2:
        printf("1.Papás\n2.Refrescos\n3.Pay\n4.Helados\n");
    case 3:
        printf("1.Individual\n2.Paquete grande\n");
    default:
        break;
    }
    printf("Elige una opción: \n");
    scanf("%d", &eleccion);
    switch (eleccion)
    {
    case 1:
    case 2:
        printf("");
        break;
    
    default:
        break;
    }
}

int main(){
    menuVentas();
}