#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEMANAS 2
#define DIAS    7

typedef struct {
    int   semana;
    char  dia_nombre[12];
    float precio;
    int   cantidad;
    char  paquete[100];
} Venta;

int main() {

    Venta sema[14] = {
        {1, "Lunes",     49,  300, "Hamburguesa con queso"},
        {1, "Martes",   169,  250, "Combo parejas"},
        {1, "Miercoles",129,  180, "Combo Whopper con cono"},
        {1, "Jueves",   129,  400, "Combo Classic Crispy King + cono"},
        {1, "Viernes",  139,  450, "Combo Whopper + papas"},
        {1, "Sabado",    99,  280, "Auto King 3 hamburguesas"},
        {1, "Domingo",   59,  300, "Long rodeo (hamburguesa grande)"},
        {2, "Lunes",     49,  400, "Hamburguesa con queso"},
        {2, "Martes",   169,  350, "Combo parejas"},
        {2, "Miercoles",129,  320, "Combo Whopper con cono"},
        {2, "Jueves",   129,  499, "Combo Classic Crispy King + cono"},
        {2, "Viernes",  139,  520, "Combo Whopper + papas"},
        {2, "Sabado",    99,  350, "Auto King 3 hamburguesas"},
        {2, "Domingo",   99,  400, "Long rodeo (hamburguesa grande)"}
    };

    /* --- Escritura --- */
    FILE *archivo = fopen("ventas.dat", "wb");
    if (archivo != NULL) {
        fwrite(sema, sizeof(Venta), 14, archivo);   /* tamaño por elemento, no total */
        fclose(archivo);
        printf("Registros guardados correctamente\n");
    }

    /* --- Lectura --- */
    archivo = fopen("ventas.dat", "rb");            /* reutiliza el puntero */
    if (archivo == NULL) {                          /* if + return, no while */
        printf("Error al abrir el archivo\n");
        return 1;
    }

    Venta venta;
    float vSemana1 = 0, vSemana2 = 0;

    printf("=======================================================\n");
    printf("                   REPORTE DE VENTAS\n");
    printf("=======================================================\n");
    printf("%-4s | %-10s | %-34s | %s\n",
           "SEM", "DIA", "PRODUCTO", "VENTA TOTAL");
    printf("-------------------------------------------------------\n");

    while (fread(&venta, sizeof(Venta), 1, archivo) == 1) {
        float subtotal = venta.precio * venta.cantidad;

        if (venta.semana == 1) vSemana1 += subtotal;
        else                   vSemana2 += subtotal;

        printf("%-4d | %-10s | %-34s | $%.2f\n",
               venta.semana, venta.dia_nombre, venta.paquete, subtotal);
    }

    printf("=======================================================\n");
    printf("  SEMANA 1: $%.2f\n", vSemana1);
    printf("  SEMANA 2: $%.2f\n", vSemana2);
    printf("  TOTAL:    $%.2f\n", vSemana1 + vSemana2);
    printf("=======================================================\n");

    fclose(archivo);
    return 0;
}