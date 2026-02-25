#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


//FUNCIONES

void menuVentas(char pedido[]);
int genNOrden() {
    return rand() % 90000 + 10000;
}
int validacion(int min, int max){
    int valor;
    while (scanf("%d", &valor) != 1 || valor < min || valor > max) {
        printf("Opción inválida. Intente nuevamente: ");
        while(getchar() != '\n');
    }
    return valor;
}
void menuVentas(char pedido[]){

    int eleccion, cantidad, opcSab,opcTam, opcion;
    char saboresH[4][50] = {
        "Hamburguesa Sencilla",
        "Hamburguesa Con queso",
        "Hamburguesa Hawaiana",
        "Hamburguesa Doble queso"
    };
    char saboresR[3][20]={
        "Coca-Cola",
        "Sprite",
        "Manzanita"
    };
    char saboresP[3][30]={
        "Pay de Manzana",
        "Pay de Pinia",
        "Pay de Queso"
    };

    do {
        printf("\n============ MENÚ ===========\n");
        printf("Bienvenido a MAC Burguer\nElija una opcion\n");
        printf("1.Hamburguesas\n2.Adicionales\n3.Combo\n4.Pagar\n");
        eleccion=validacion(1,4);
        switch (eleccion){

        case 1:
            printf("Ingrese el numero de hamburguesas que desea ordenar: \n");
            cantidad = validacion(1,50);

            for(int i = 0; i < cantidad; i++){
                printf("Elija el sabor de la hamburguesa #%d:\n", i+1);     
                for (int i = 0; i < 4; i++)
                {
                    printf("%d.%s\n", i+1, saboresH[i]);
                }
                
                opcion = validacion(1,5);
                
                 if(opcion==5){
                    printf("Regresando al menu principal...\n");
                    break;}
                strcat(pedido, saboresH[opcion-1]);
                strcat(pedido, "\n");
            }break;
                    


        case 2:
            printf("1.Papas\n2.Refrescos\n3.Helados\n4.Pay\n5.Salir\n");
            opcion=validacion(1,5);

            switch (opcion){
                case 1: 
                    printf("1.Grandes\n2.Chicas\n3.Salir\n");
                    opcTam=validacion(1,2);
                    if(opcion==1){
                        strcat(pedido, "Papas Grandes\n");
                    }else if(opcion==2){
                        strcat(pedido, "Papas chicas\n");
                    }else if(opcion==3){
                    printf("Regresando al menu principal...\n");
                    }break;
                
                case 2:
                    printf("Ingrese el numero de bebidas a ordenar:\n");
                    cantidad=validacion(1,20);
                    for (int i = 0; i < cantidad; i++)
                    {
                        printf("Elija el sabor de su bebida #%d u oprima 0 para regresar\n", i+1);
                        for (int i = 0; i < 3; i++)
                        {printf("%d.%s\n", i+1, saboresR[i]);
                        }
                        opcion=validacion(0,3);
                        if (opcion)
                        {
                            printf("1.Grande\n2.Chico\n");
                            scanf("%d", &opcTam);
                            strcat(pedido, saboresR[opcion-1]);
                            strcat(pedido, " ");
                            if(opcTam==1){
                                strcat(pedido,"Grande");
                            }else if(opcTam==2){
                                strcat(pedido, "Chico");
                            }
                            strcat(pedido, "\n");
                        }else if(opcion==0){
                            printf("Regresando al menu principal...\n");
                    }break;}break;
                    
                    case 3:
                        printf("Elija el número de helados a ordenar: \n"); 
                        cantidad = validacion(1,5);
                        for (int i = 0; i <cantidad; i++)
                        {
                            printf("Sabor del helado #%d:\n1.Chocolate\n2.Vainilla\n", i+1);
                            scanf("%d", &opcSab);
                            if (opcSab==1)
                            {
                                strcat(pedido, "Helado de Chocolate\n");
                            }else if(opcSab==2){
                                strcat(pedido, "Helado de Vainilla\n");
                            }else{
                                printf("Opcion invalida.");
                                i--;
                            }
                            
                        }break;
                    case 4: 
                        printf("Indique el numero de pays a ordenar: \n");
                        cantidad=validacion(1,5);
                        for (int i = 0; i < cantidad; i++)
                        {
                            printf("Elija el sabor del pay #%d o presione 0 para regresar: \n", i+1);
                            for(int i = 0; i < 3; i++){
                                printf("%d.%s\n", i+1, saboresP[i]);
                            }
                            opcSab = validacion(0,3);
                            strcat(pedido, saboresP[opcSab-1]);
                            strcat(pedido, " ");
                            if (opcSab==0)
                            {
                                printf("Regresando al menu..."); 
                             }break;
                            }break;
                    case 5: printf("Regresando al menu..."); break;

                default: 
                    printf("Opción inválida\n");
            }
            break;

        case 3:
            printf("1.Individual\n2.Paquete grande\n");
            scanf("%d", &eleccion);
            if(eleccion==1){
                printf("Paquete individual:\n-Hamburguesa Sencilla\n-Refresco\n-Papas chicas\n");
                strcat(pedido, "Paquete individual\n");
                strcat(pedido, " ");

            }else if(eleccion==2){
                printf("Combo:\n-Hamburguesa Hawaiana+ Sencilla\n-Refresco Grande+1 Ref.chico\n-Papas grandes\n-Pay");
                strcat(pedido, "Paquete Grande\n");
                strcat(pedido, " ");
            }break;

        case 4:
            printf("Finalizando pedido...\n");
            break;

        default:
            printf("Opción inválida\n");
        }

    } while(eleccion != 4);
}
int main(){
    srand(time(NULL));
    char pedido[500]= "";
    menuVentas(pedido);
    int folio = genNOrden();
    printf("===== TICKET ====\n");
    printf("= Orden Nº %d =\n", folio);
    printf("==== PEDIDO ====\n");
    printf("%s", pedido);
    return 0;
}