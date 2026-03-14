#include <stdio.h>
#include <string.h>
#include <iostream>
#include <ctype.h>
#include <time.h>
using namespace std;

struct caract
{
    char descripcion[100];
};

struct autoPack
{
    int opcion;
    char caracteristicas[50];
    float precio;
    caract descr;
};


float menu(char historial[]);
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

float menu(char historial[]){
    autoPack paquetes[3]={
        {1, "ADULTO", 249, "Hamburguesa doble + hamburguesa sencilla\nPapas grandes\nRefresco grande"},
        {2, "NIÑO", 149,"Hamburguesa sencilla\nPapas chicas\nRefresco chico\n-Nuggets"},
        {3, "FAMILIAR", 499, "4 hamburguesas con queso\n4 refrescos grandes\n4 papas grandes, 4 helados"}
    };
    autoPack *apunt = paquetes;
int eleccion, eleccionMen;
float total=0;
do
{
    cout<< "Bienvenido a auto-burguer\n Seleccione una opcion:\n1.Paquete adulto\n2.Paquete niño\n3.Paquete familiar\n4.Pagar\n";
    eleccion = validacion(1,3);
    switch (eleccion)
    {
    case 1:
        cout<<"Paquete:"<<apunt[0].caracteristicas<<"\n";
        cout<<"$"<<apunt[0].precio<<"\n";
        cout<<"\nDescripcion\n"<<apunt[0].descr.descripcion<<"\n";
        

        cout<<"\n1.Continuar con la compra\n2.regresar al menu\n";
        eleccionMen=validacion(1,2);
        if (eleccionMen==2)
        {
            cout<<"regresando al menu principal...\n";
            break;
        }else{
            cout<<"ingrese el numero de paquetes que desea agregar: \n";
            eleccion = validacion(1,10);
            strcat(historial, apunt[0].caracteristicas);
            strcat(historial, "\n");
            total+= (apunt[0].precio*eleccion);
            break;
            }
    case 2:
        cout<<"Paquete:\n"<<apunt[1].caracteristicas<<"\n";
        cout<<"$"<<apunt[1].precio<<"\n";
        cout<<"\nDescripcion\n"<<apunt[1].descr.descripcion;


        cout<<"\n1.Continuar con la compra\n2.regresar al menu\n";
        eleccionMen=validacion(1,2);
        if (eleccionMen==2)
        {
            cout<<"regresando al menu principal...\n";
            break;
        }else{
            cout<<"ingrese el numero de paquetes que desea agregar: \n";
            eleccion = validacion(1,10);
            strcat(historial, apunt[1].caracteristicas);
            strcat(historial, "\n");
            total+= (apunt[1].precio*eleccion);
            break;
            }
    case 3:
    cout<<apunt[2].caracteristicas<<"\n";
    cout<<"$"<<apunt[2].precio<<"\n";
    cout<<"\nDescripcion\n"<<apunt[2].descr.descripcion;


    cout<<"\n1.Continuar con la compra\n2.regresar al menu\n";
    eleccionMen=validacion(1,2);
    if (eleccionMen==3)
    {
        cout<<"regresando al menu principal...\n";
        break;
    }else{
        cout<<"ingrese el numero de paquetes que desea agregar: \n";
        eleccion = validacion(1,10);
        strcat(historial, apunt[2].caracteristicas);
        strcat(historial, "\n");
        total+= (apunt[2].precio*eleccion);
        break;
        }
    default:
        break;
    }
} while (eleccion!=4);
return total;

}
int main(){
    srand(time(NULL));
    char historial[100]= "";
    float total = menu(historial);
    int folio = genNOrden();
}
