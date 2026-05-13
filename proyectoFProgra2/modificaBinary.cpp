#include <stdlib.h>
#include <stdio.h>
#include <iostream>
typedef struct
{
    char nombre[50];
    float precio;
} producto;
char nombreArchivo[50];
void mostrarArchivo();

int main(){
    char nombre[50];
    int opc;
    int posicionBin;
    producto p;
    printf("Indique el nombre del archivo: ");
    fgets(nombreArchivo, sizeof(nombreArchivo), stdin);
    nombreArchivo[strcspn(nombreArchivo, "\n")] = 0; // quitar salto de línea
    FILE *fi= fopen(nombreArchivo, "r+b");
    if(fi == NULL){
        printf("Ocurrió un error al abrir el archivo\n");
        exit(1);
    }
    
    mostrarArchivo();

    printf("\n¿Desea modificar el archivo? si=1 / no=2\n");
    scanf("%d", &opc);getchar();
    if (opc==1)
    {
        printf("indique el nombre de la hamburguesa a modificar: \n");
        fgets(nombre, sizeof(nombre),stdin);
        nombre[strcspn(nombre, "\n")] = 0;
        while (fread(&p, sizeof(p),1,fi)==1)
        {
            if (strcmp(nombre,p.nombre)==0)
            {
                printf("Ingrese el nombre de la nueva hamburguesa: ");
                fgets(p.nombre, sizeof(p.nombre), stdin);
                p.nombre[strcspn(p.nombre, "\n")]=0;
                printf("Ingrese el nuevo precio: ");
                scanf("%f", &p.precio);getchar();
                //escribir el registro modificado
                posicionBin = ftell(fi) - sizeof(p);
                fseek(fi, posicionBin, SEEK_SET);
                fwrite(&p, sizeof(p), 1, fi);

                printf("Registro modificado exitosamente\n");
                break;                
            }
        }
    }
    
}
