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

void limpiarPantalla()
{
    // Código ANSI: \033[2J borra pantalla, \033[H mueve cursor al inicio
    cout << "\033[2J\033[H";
}
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
        printf("Opcion invalida. Intente nuevamente: ");
        while (getchar() != '\n')
            ;
    }
    return valor;
}

void procesarCompra(autoPack paquete, int *contadorTotal, float *acumuladorDinero, char historial[])
{
    int eleccionMen, cantidad;
    cout << "\nPaquete: " << paquete.caracteristicas << "- $" << paquete.precio << endl;
    cout << "\nDescripcion:\n"
         << paquete.descr.descripcion << endl;
    cout << "1.Continuar | 2.Regresar" << endl;
    eleccionMen = validacion(1, 2);
    if (eleccionMen == 2)
    {
        cout << "Regresando al menu...";
    }
    else
    {
        cout << "Cantidad de paquetes que desea agregar:";
        cantidad = validacion(1, 10);
        *contadorTotal += cantidad;
        *acumuladorDinero += (paquete.precio * cantidad);
        strcat(historial, paquete.caracteristicas);
        strcat(historial, "\n");
        cout << "AGREGADO CORRECTAMENTE\n";
        cout << "Presione enter para continuar.\n";
        getchar();
        getchar();
    }
}

float menu(char historial[])
{
    autoPack paquetes[3] = {
        {1, "ADULTO", 249, {"Hamburguesa doble + hamburguesa sencilla\nPapas grandes\nRefresco grande"}},
        {2, "NINIO", 149, {"Hamburguesa sencilla\nPapas chicas\nRefresco chico\nNuggets"}},
        {3, "FAMILIAR", 499, {"4 hamburguesas con queso\n4 refrescos grandes\n4 papas grandes, 4 helados"}}};
    autoPack *apunt = paquetes;
    int eleccion, contador = 0;
    float total = 0;
    do
    {
        limpiarPantalla();
        cout << "==== Bienvenido a auto-burguer ====\n Seleccione una opcion:\n1.Paquete adulto ($249)\n2.Paquete ninio ($149)\n3.Paquete familiar ($499)\n4.Pagar\n";
        eleccion = validacion(1, 4);
        switch (eleccion)
        {
        case 1:
            procesarCompra(apunt[0], &contador, &total, historial);
            break;
        case 2:
            procesarCompra(apunt[1], &contador, &total, historial);
            break;

        case 3:
            procesarCompra(apunt[2], &contador, &total, historial);
            break;

        default:

            break;
        }
    } while (eleccion != 4);
    return total;
}
int main()
{
    srand(time(NULL));
    char historial[1000] = "";
    float total = menu(historial);
    int folio = genNOrden();
    if (total > 0)
    {
        cout << "\n ==== TICKET ====" << endl;
        cout << "ORDEN:" << folio << endl;
        cout << "PAQUETES SELECCIONADOS: \n"
             << historial << endl;
        cout << "TOTAL A PAGAR:$" << total << endl;
    }
    else
    {
        cout << "No se agregaron articulos.";
    }
}
