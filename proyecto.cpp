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

    // Arreglos de estructuras
    producto hamburguesas[4] = {
        {"Hamburguesa Sencilla", 45},
        {"Hamburguesa Con Queso", 65},
        {"Hamburguesa Hawaiana", 90},
        {"Hamburguesa Doble queso", 85}};

    prod2 refresco[3] = {
        {"Coca-Cola", 45, 35},
        {"Sprite", 45, 35},
        {"Manzanita", 45, 35}};

    producto pay[3] = {
        {"Pay de Manzana", 30},
        {"Pay de Pinia", 40},
        {"Pay de Queso", 35}};

    producto papas[2] = {
        {"Papas Grandes", 45},
        {"Papas Chicas", 35}};

    producto helado[2] = {
        {"Helado Chocolate", 30},
        {"Helado Vainilla", 25}};

    producto paquetes[2] = {
        {"PAQUETE INDIVIDUAL", 110},
        {"COMBO", 239}};

    do
    {
        printf("\n============ MENU ===========\n");
        printf("1. Hamburguesas\n2. Adicionales\n3. Combos\n4. Pagar\n");
        eleccion = validacion(1, 4);

        switch (eleccion)
        {
        case 1:
            printf("¿Cuantas hamburguesas desea?: ");
            cantidad = validacion(1, 10);
            for (int i = 0; i < cantidad; i++)
            {
                printf("Sabor para la hamburguesa #%d:\n", i + 1);
                for (int j = 0; j < 4; j++)
                {
                    printf("%d. %s $%.2f\n", j + 1, hamburguesas[j].nombre, hamburguesas[j].precio);
                }
                opcion = validacion(1, 4);
                strcat(pedido, hamburguesas[opcion - 1].nombre);
                strcat(pedido, "\n");
                total += hamburguesas[opcion - 1].precio;
            }
            break;

        case 2:
            printf("1.Papas\n2.Refrescos\n3.Helados\n4.Pay\n5.Regresar\n");
            opcion = validacion(1, 5);
            switch (opcion)
            {
            case 1:
                printf("1.Grandes\n2.Chicas\n");
                opcTam = validacion(1, 2);
                strcat(pedido, papas[opcTam - 1].nombre);
                strcat(pedido, "\n");
                total += papas[opcTam - 1].precio;
                break;

            case 2:
                printf("Sabor:\n1.Coca\n2.Sprite\n3.Manzanita\n");
                opcSab = validacion(1, 3);
                printf("1.Grande\n2.Chico\n");
                opcTam = validacion(1, 2);

                strcat(pedido, refresco[opcSab - 1].nombre);
                if (opcTam == 1)
                {
                    strcat(pedido, " (G), ");
                    strcat(pedido, "\n ");
                    total += refresco[opcSab - 1].precioG;
                }
                else
                {
                    strcat(pedido, " (Ch)");
                    strcat(pedido, "\n");
                    total += refresco[opcSab - 1].precioCh;
                }
                break;

            case 3:
                printf("1.Chocolate\n2.Vainilla\n");
                opcSab = validacion(1, 2);
                strcat(pedido, helado[opcSab - 1].nombre);
                strcat(pedido, ", ");
                total += helado[opcSab - 1].precio;
                break;

            case 4:
                for (int j = 0; j < 3; j++)
                    printf("%d.%s\n", j + 1, pay[j].nombre);
                opcSab = validacion(1, 3);
                strcat(pedido, pay[opcSab - 1].nombre);
                strcat(pedido, "\n");
                total += pay[opcSab - 1].precio;
                break;
            }
            break;

        case 3:
            printf("1. Individual $110\n2. Paquete Grande $239\n3. Salir\n");
            opcion = validacion(1, 3);
            if (opcion <= 2)
            {
                strcat(pedido, paquetes[opcion - 1].nombre);
                strcat(pedido, "\n");
                total += paquetes[opcion - 1].precio;
            }
            break;
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
    printf("%s\n", pedido);
    printf("=== TOTAL ===\n");
    printf("%.2f\n", total);
    return 0;
}