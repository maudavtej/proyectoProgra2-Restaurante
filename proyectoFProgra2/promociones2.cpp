#include <stdio.h>
#include <string.h>
#include <ctype.h>

// ============================================================
//  STRUCTS
// ============================================================

typedef struct
{
    char nombre[50];
    int  precio;
    char diapromo[20];
    int  numComp;
    union opciones
    {
        char comp[20];
        int  desc;
    };
} marzo;

typedef enum {lun=1, mar, mier, juev, vier, sab, dom} semana;

// ============================================================
//  DATOS GLOBALES DE PROMOCIONES
// ============================================================

marzo dias[7] = {
    {"Lunes de queso",    49,  "Lunes",     1},
    {"Martes de Pareja",  169, "Martes",    3},
    {"Miercoles de Cono", 129, "Miercoles", 2},
    {"Jueves del Rey",    129, "Jueves",    2},
    {"Viernes Whoper",    139, "Viernes",   2},
    {"Sabado de amigos",  99,  "Sabado",    3},
    {"Domingo de Rodeo",  59,  "Domingo",   1},
};

// ============================================================
//  ARCHIVOS BINARIOS - GUARDAR
// ============================================================

void guardarPromociones() {
    FILE *f = fopen("promociones.bin", "wb");
    if (!f) { printf("Error al guardar promociones\n"); return; }

    fwrite(dias, sizeof(marzo), 7, f);

    fclose(f);
    printf("Promociones guardadas correctamente.\n");
}

// ============================================================
//  ARCHIVOS BINARIOS - CARGAR
// ============================================================

void cargarPromociones() {
    FILE *f = fopen("promociones.bin", "rb");
    if (!f) {
        // Si no existe el archivo, usa los valores por defecto
        // y genera el .bin por primera vez
        printf("Archivo no encontrado. Usando promociones por defecto.\n");
        guardarPromociones();
        return;
    }

    fread(dias, sizeof(marzo), 7, f);

    fclose(f);
}

// ============================================================
//  LOGICA PRINCIPAL
// ============================================================

int eleccionD() {
    int fin = 0;
    int opcion, opcCom, opc3;

    do {
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

        if (opcion >= 1 && opcion <= 7) {
            int idx = opcion - 1;
            printf("PROMO:       %s\n",  dias[idx].nombre);
            printf("PRECIO:      $%d\n", dias[idx].precio);
            printf("DIA:         %s\n",  dias[idx].diapromo);
            printf("COMPONENTES: #%d\n", dias[idx].numComp);

            // Solo el lunes tiene logica de complemento implementada
            if (opcion == 1) {
                printf("1.Elegir un complemento\n2.Aceptar descuento\n");
                scanf("%d", &opcCom);
                if (opcCom == 1) {
                    printf("1.Refresco\n2.Cono\n3.Empanada\n");
                    scanf("%d", &opc3);
                    switch (opc3) {
                        case 1: printf("Complemento: Refresco\n");  break;
                        case 2: printf("Complemento: Cono\n");      break;
                        case 3: printf("Complemento: Empanada\n");  break;
                        default: printf("Opcion invalida.\n");      break;
                    }
                }
            }
        } else if (opcion == 8) {
            fin = 1;
        } else {
            printf("Seleccione una opcion valida.\n");
        }

    } while (!fin);

    return 0;
}

int main() {
    // Carga promociones desde archivo (o genera el .bin si no existe)
    cargarPromociones();

    eleccionD();

    return 0;
}