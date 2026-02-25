#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
// structs
typedef struct
{
    char nombre[50];
    float precio;
} producto;

typedef struct
{
    char nombre[50];
    float precioG;
    float precioCh;
} prod2;

// FUNCIONES

float menuVentas(char pedido[]);
int genNOrden()
{
    return rand() % 90000 + 10000;
}
int validacion(int min, int max)
{
    int valor;
    while (scanf("%d", &valor) != 1 || valor < min || valor > max)
    {
        printf("Opción inválida. Intente nuevamente: ");
        while (getchar() != '\n')
            ;
    }
    return valor;
}
float menuVentas(char pedido[])
{

    int eleccion, cantidad, opcSab, opcTam, opcion;
    float total = 0;
    producto hamburguesas[4] = {
        {"Hamburguesa Sencilla", 45},
        {"Hamburguesa Con queso", 65},
        {"Hamburguesa Hawaiana", 90},
        {"Hamburguesa Doble queso", 85}};
    prod2 refresco[3] = {
        {"Coca-Cola", 35, 45},
        {"Sprite", 35, 45},
        {"Manzanita", 35, 45}};
    producto pay[3] = {
        {"Pay de Manzana", 30},
        {"Pay de Pinia", 40},
        {"Pay de Queso", 35}};
    producto papas[2] = {
        {"Papas grandes", 45},
        {"Papas chicas", 35}};
    producto helado[2] = {
        {"Chocolate", 30},
        {"Vainilla", 25}};
    producto paquete1[1] = {
        {"PAQUETE INDIVIDUAL", 110}};
    producto paquete2[1] = {
        {"COMBO", 239}

    };

    do
    {
        printf("\n============ MENU===========\n");
        printf("Bienvenido a MAC Burguer\nElija una opcion\n");
        printf("1.Hamburguesas\n2.Adicionales\n3.Combo\n4.Pagar\n");
        eleccion = validacion(1, 4);
        switch (eleccion)
        {

        case 1:
            printf("Ingrese el numero de hamburguesas que desea ordenar: \n");
            cantidad = validacion(1, 50);

            for (int i = 0; i < cantidad; i++)
            {
                printf("Elija el sabor de la hamburguesa #%d:\n", i + 1);
                for (int i = 0; i < 4; i++)
                {
                    printf("%d.%s\n", i + 1, hamburguesas[i].nombre);
                }

                opcion = validacion(1, 5);

                if (opcion == 5)
                {
                    printf("Regresando al menu principal...\n");
                    break;
                }
                strcat(pedido, hamburguesas[opcion - 1].nombre);
                strcat(pedido, "\n");
                total += hamburguesas[opcion - 1].precio;
            }
            break;

        case 2:
            printf("1.Papas\n2.Refrescos\n3.Helados\n4.Pay\n5.Salir\n");
            opcion = validacion(1, 5);

            switch (opcion)
            {
            case 1:
                printf("Ingrese cuantas papas desea ordenar: \n");
                cantidad = validacion(1, 10);
                for (int i = 0; i < cantidad; i++)
                {
                    printf("Seleccione el tamanio de sus papas #%d\n", i + 1);
                    printf("1.Grandes\n2.Chicas\n3.Salir\n");
                    opcTam = validacion(1, 3);
                    if (opcTam == 3)
                    {
                        printf("Regresando al menu principal...\n");
                        break;
                    }
                    strcat(pedido, papas[opcTam - 1].nombre);
                    strcat(pedido, "\n");
                    total += papas[opcTam - 1].precio;
                }
                break;

            case 2:
                printf("Ingrese el numero de bebidas a ordenar:\n");
                cantidad = validacion(1, 20);
                for (int i = 0; i < cantidad; i++)
                {
                    printf("Elija el sabor de su bebida #%d u oprima 0 para regresar\n", i + 1);
                    for (int i = 0; i < 3; i++)
                    {
                        printf("%d.%s\n", i + 1, refresco[i].nombre);
                    }
                    opcion = validacion(0, 3);
                    if (opcion == 0)
                    {
                        printf("Regresando al menu principal...\n");
                    }
                    else
                    {
                        printf("1.Grande\n2.Chico\n");
                        scanf("%d", &opcTam);
                        strcat(pedido, refresco[opcion - 1].nombre);
                        if (opcTam == 1)
                        {
                            strcat(pedido, refresco[opcion - 1].nombre);
                            total += refresco[opcion - 1].precioG;
                            strcat(pedido, "\n");
                        }
                        else if (opcTam == 2)
                        {
                            strcat(pedido, refresco[opcion - 1].nombre);
                            strcat(pedido, "\n");
                            total += refresco[opcion - 1].precioCh;
                        }
                    }
                }
                break;

            case 3:
                printf("Elija el número de helados a ordenar: \n");
                cantidad = validacion(1, 5);
                for (int i = 0; i < cantidad; i++)
                {
                    printf("Sabor del helado #%d:\n1.Chocolate\n2.Vainilla\n", i + 1);
                    scanf("%d", &opcSab);
                    if (opcSab == 1)
                    {
                        strcat(pedido, helado[opcSab - 1].nombre);
                        strcat(pedido, " ");
                        total += helado[opcSab - 1].precio;
                    }
                    else if (opcSab == 2)
                    {
                        strcat(pedido, helado[opcSab - 1].nombre);
                        strcat(pedido, " ");
                        total += helado[opcSab - 1].precio;
                    }
                    else
                    {
                        printf("Opcion invalida.");
                        i--;
                    }
                }
                break;
            case 4:
                printf("Indique el numero de pays a ordenar: \n");
                cantidad = validacion(1, 5);
                for (int i = 0; i < cantidad; i++)
                {
                    printf("Elija el sabor del pay #%d o presione 0 para regresar: \n", i + 1);
                    for (int i = 0; i < 3; i++)
                    {
                        printf("%d.%s\n", i + 1, pay[i].nombre);
                    }
                    opcSab = validacion(0, 3);
                    if (opcSab == 0)
                    {
                        printf("Regresando al menu...");
                        break;
                    }
                    strcat(pedido, pay[opcSab - 1].nombre);
                    strcat(pedido, " ");
                    total += pay[opcSab - 1].precio;
                }
                break;
            case 5:
                printf("Regresando al menu...");
                break;

            default:
                printf("Opción inválida\n");
            }
            break;

        case 3:
            printf("1.Individual\n2.Paquete grande\n3.Salir");
            eleccion = validacion(1, 3);
            if (eleccion == 1)
            {
                printf("-Hamburguesa sencilla\n-Papas chicas\n-Refresco chico\n-Helado");
                printf("%s", paquete1[eleccion - 1].nombre);
                strcat(pedido, paquete1[eleccion - 1].nombre);
                strcat(pedido, " ");
                total += paquete1[eleccion - 1].precio;
            }
            else if (eleccion == 2)
            {
                printf("Combo:\n-Hamburguesa Hawaiana+Sencilla\n-Refresco Grande+1 Ref.chico\n-Papas grandes\n-Pay de manzana");
                strcat(pedido, paquete2[eleccion - 1].nombre);
                strcat(pedido, " ");
                total += paquete2[eleccion - 1].precio;
            }
            break;

        case 4:
            printf("Finalizando pedido...\n");
            break;

        default:
            printf("Opción inválida\n");
        }

    } while (eleccion != 4);
    return total;
}
int main()
{
    srand(time(NULL));
    char pedido[500] = "";
    float total = menuVentas(pedido);
    int folio = genNOrden();
    printf("===== TICKET ====\n");
    printf("= Orden Nº %d =\n", folio);
    printf("==== PEDIDO ====\n");
    printf("%s", pedido);
    printf("=== TOTAL ===\n");
    printf("%.2f", total);
    return 0;
}