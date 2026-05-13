#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// ============================================================
//  STRUCTS
// ============================================================

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

producto hamburguesas[4] = {
    {"Hamburguesa Sencilla",      45},
    {"Hamburguesa Con queso",     65},
    {"Hamburguesa Hawaiana",      90},
    {"Hamburguesa Doble queso",   85}
};

prod2 refresco[3] = {
    {"Coca-Cola",   35, 45},
    {"Sprite",      35, 45},
    {"Manzanita",   35, 45}
};

producto pay[3] = {
    {"Pay de Manzana", 30},
    {"Pay de Pinia",   40},
    {"Pay de Queso",   35}
};

producto papas[2] = {
    {"Papas grandes", 45},
    {"Papas chicas",  35}
};

producto helado[2] = {
    {"Chocolate", 30},
    {"Vainilla",  25}
};

producto paquete1[1] = {
    {"PAQUETE INDIVIDUAL", 110}
};

producto paquete2[1] = {
    {"COMBO", 239}
};

void guardarProductos() {
    FILE *f = fopen("productos.bin", "wb");
    if (!f) { printf("Error al guardar productos\n"); return; }

    fwrite(hamburguesas, sizeof(producto), 4, f);
    fwrite(refresco,     sizeof(prod2),    3, f);
    fwrite(pay,          sizeof(producto), 3, f);
    fwrite(papas,        sizeof(producto), 2, f);
    fwrite(helado,       sizeof(producto), 2, f);
    fwrite(paquete1,     sizeof(producto), 1, f);
    fwrite(paquete2,     sizeof(producto), 1, f);

    fclose(f);
    printf("Productos guardados correctamente.\n");
}

void cargarProductos() {
    FILE *f = fopen("productos.bin", "rb");
    if (!f) {
        // Si no existe el archivo, se usan los valores por defecto
        // definidos arriba y se genera el archivo por primera vez
        printf("Archivo no encontrado. Usando productos por defecto.\n");
        guardarProductos();
        return;
    }

    fread(hamburguesas, sizeof(producto), 4, f);
    fread(refresco,     sizeof(prod2),    3, f);
    fread(pay,          sizeof(producto), 3, f);
    fread(papas,        sizeof(producto), 2, f);
    fread(helado,       sizeof(producto), 2, f);
    fread(paquete1,     sizeof(producto), 1, f);
    fread(paquete2,     sizeof(producto), 1, f);

    fclose(f);
}

//  FUNCIONES GENERALES

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
        while (getchar() != '\n');
    }
    return valor;
}

float menuVentas(char pedido[])
{
    int eleccion, cantidad, opcSab, opcTam, opcion;
    float total = 0;

    do
    {
        printf("\n============ MENU ===========\n");
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
                for (int j = 0; j < 4; j++)
                    printf("%d.%s\n", j + 1, hamburguesas[j].nombre);

                opcion = validacion(1, 5);
                if (opcion == 5) { printf("Regresando al menu principal...\n"); break; }

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
                    printf("Seleccione el tamanio de sus papas #%d\n1.Grandes\n2.Chicas\n3.Salir\n", i + 1);
                    opcTam = validacion(1, 3);
                    if (opcTam == 3) { printf("Regresando al menu principal...\n"); break; }
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
                    for (int j = 0; j < 3; j++)
                        printf("%d.%s\n", j + 1, refresco[j].nombre);
                    opcion = validacion(0, 3);
                    if (opcion == 0) { printf("Regresando al menu principal...\n"); break; }

                    printf("1.Grande\n2.Chico\n");
                    scanf("%d", &opcTam);
                    strcat(pedido, refresco[opcion - 1].nombre);
                    if (opcTam == 1)
                    {
                        total += refresco[opcion - 1].precioG;
                        strcat(pedido, " (Grande)\n");
                    }
                    else
                    {
                        total += refresco[opcion - 1].precioCh;
                        strcat(pedido, " (Chico)\n");
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
                    if (opcSab == 1 || opcSab == 2)
                    {
                        strcat(pedido, helado[opcSab - 1].nombre);
                        strcat(pedido, "\n");
                        total += helado[opcSab - 1].precio;
                    }
                    else { printf("Opcion invalida."); i--; }
                }
                break;

            case 4:
                printf("Indique el numero de pays a ordenar: \n");
                cantidad = validacion(1, 5);
                for (int i = 0; i < cantidad; i++)
                {
                    printf("Elija el sabor del pay #%d o presione 0 para regresar: \n", i + 1);
                    for (int j = 0; j < 3; j++)
                        printf("%d.%s\n", j + 1, pay[j].nombre);
                    opcSab = validacion(0, 3);
                    if (opcSab == 0) { printf("Regresando al menu..."); break; }
                    strcat(pedido, pay[opcSab - 1].nombre);
                    strcat(pedido, "\n");
                    total += pay[opcSab - 1].precio;
                }
                break;

            case 5:
                printf("Regresando al menu...");
                break;
            }
            break;

        case 3:
            printf("1.Individual\n2.Paquete grande\n3.Salir");
            eleccion = validacion(1, 3);
            if (eleccion == 1)
            {
                printf("-Hamburguesa sencilla\n-Papas chicas\n-Refresco chico\n-Helado\n");
                strcat(pedido, paquete1[0].nombre);
                strcat(pedido, "\n");
                total += paquete1[0].precio;
            }
            else if (eleccion == 2)
            {
                printf("Combo:\n-Hamburguesa Hawaiana+Sencilla\n-Refresco Grande+1 Ref.chico\n-Papas grandes\n-Pay de manzana\n");
                strcat(pedido, paquete2[0].nombre);
                strcat(pedido, "\n");
                total += paquete2[0].precio;
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

    // Carga productos desde archivo (o genera el .bin si no existe)
    cargarProductos();

    char pedido[500] = "";
    float total = menuVentas(pedido);
    int folio = genNOrden();

    printf("===== TICKET ====\n");
    printf("= Orden No. %d =\n", folio);
    printf("==== PEDIDO ====\n");
    printf("%s", pedido);
    printf("=== TOTAL ===\n");
    printf("$%.2f\n", total);

    return 0;
}