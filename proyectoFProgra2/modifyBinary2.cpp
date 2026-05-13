#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct { char nombre[50]; float precio; } producto;
typedef struct { char nombre[50]; float precioG; float precioCh; } prod2;
void verArchivo();
int main(){
    FILE *fi = fopen("productos.bin", "r+b");
    if(fi == NULL){ printf("Error al abrir el archivo\n"); exit(1); }
    verArchivo();
    char nombre[50];
    printf("Nombre del producto a modificar: ");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    int encontrado = 0;

    // --- Busca en productos (hamburguesas, pay, papas, helado, paquetes) ---
    producto p;
    long offset = 0;
    int counts[] = {4, 3, 2, 2, 1, 1}; // hamburguesas, pay, papas, helado, paq1, paq2
    long salto_refresco = 4*sizeof(producto); // parte donde empiezan refrescos

    // Buscar antes de refrescos (hamburguesas)
    fseek(fi, 0, SEEK_SET);
    for(int i = 0; i < 4 && !encontrado; i++){
        long pos = ftell(fi);
        fread(&p, sizeof(producto), 1, fi);
        if(strcmp(nombre, p.nombre) == 0){
            printf("Nuevo precio: "); scanf("%f", &p.precio);
            fseek(fi, pos, SEEK_SET);
            fwrite(&p, sizeof(producto), 1, fi);
            encontrado = 1;
        }
    }

    // Buscar en refrescos (prod2)
    if(!encontrado){
        prod2 r;
        fseek(fi, salto_refresco, SEEK_SET);
        for(int i = 0; i < 3 && !encontrado; i++){
            long pos = ftell(fi);
            fread(&r, sizeof(prod2), 1, fi);
            if(strcmp(nombre, r.nombre) == 0){
                printf("Nuevo precio grande: "); scanf("%f", &r.precioG);
                printf("Nuevo precio chico: ");  scanf("%f", &r.precioCh);
                fseek(fi, pos, SEEK_SET);
                fwrite(&r, sizeof(prod2), 1, fi);
                encontrado = 1;
            }
        }
    }

    // Buscar en el resto (pay, papas, helado, paquetes)
    if(!encontrado){
        long resto_offset = salto_refresco + 3*sizeof(prod2);
        fseek(fi, resto_offset, SEEK_SET);
        while(fread(&p, sizeof(producto), 1, fi) == 1 && !encontrado){
            long pos = ftell(fi) - sizeof(producto);
            if(strcmp(nombre, p.nombre) == 0){
                printf("Nuevo precio: "); scanf("%f", &p.precio);
                fseek(fi, pos, SEEK_SET);
                fwrite(&p, sizeof(producto), 1, fi);
                encontrado = 1;
            }
        }
    }

    if(!encontrado)
        printf("Producto no encontrado\n");
    else
        printf("Modificado exitosamente\n");
        verArchivo();

    fclose(fi);
    return 0;
}
void verArchivo(){
    FILE *ficheroa = fopen("productos.bin", "rb");
    if(ficheroa == NULL){ printf("Error en la apertura del archivo\n"); exit(1); }

    producto p;
    prod2 r;

    printf("\n========== PRODUCTOS ==========\n");

    // Hamburguesas (4)
    printf("\n-- Hamburguesas --\n");
    for(int i = 0; i < 4; i++){
        fread(&p, sizeof(producto), 1, ficheroa);
        printf("%-30s $%.2f\n", p.nombre, p.precio);
    }

    // Refrescos (3) 
    printf("\n-- Refrescos --\n");
    for(int i = 0; i < 3; i++){
        fread(&r, sizeof(prod2), 1, ficheroa);
        printf("%-30s Grande: $%.2f  Chico: $%.2f\n", r.nombre, r.precioG, r.precioCh);
    }

    // Pay (3)
    printf("\n-- Pay --\n");
    for(int i = 0; i < 3; i++){
        fread(&p, sizeof(producto), 1, ficheroa);
        printf("%-30s $%.2f\n", p.nombre, p.precio);
    }

    // Papas (2)
    printf("\n-- Papas --\n");
    for(int i = 0; i < 2; i++){
        fread(&p, sizeof(producto), 1, ficheroa);
        printf("%-30s $%.2f\n", p.nombre, p.precio);
    }

    // Helado (2)
    printf("\n-- Helado --\n");
    for(int i = 0; i < 2; i++){
        fread(&p, sizeof(producto), 1, ficheroa);
        printf("%-30s $%.2f\n", p.nombre, p.precio);
    }

    // Paquetes (2)
    printf("\n-- Paquetes --\n");
    for(int i = 0; i < 2; i++){
        fread(&p, sizeof(producto), 1, ficheroa);
        printf("%-30s $%.2f\n", p.nombre, p.precio);
    }

    fclose(ficheroa);
}