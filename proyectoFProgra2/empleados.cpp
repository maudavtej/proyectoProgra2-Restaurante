#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Persona {
    char nombre[20];
    char direccion[50];
    char telefono[15];
};

struct Producto {
    char nombre[30];
    int cantidad;
};

struct Empleado {
    struct Persona emplePer;
    int edad;
    int sueldoDiario;
    int sueldoMensual;
    char area[30];
    char puesto[30];

    void calcularSueldo(){
        sueldoMensual = sueldoDiario * 20;
    }

    void guardarInfo(){
        int opcionArea = 0;
        int opcionPuesto = 0;
        char buffer[20];

        printf("\nIndique el Area de trabajo eligiendo una opcion del 1-3:");
        printf("\n1.- Area de cocina");
        printf("\n2.- Area de Servicio y ventas");
        printf("\n3.- Area Administrativa y de apoyo");
        printf("\nOpcion: ");
        fgets(buffer, 20, stdin);
        sscanf(buffer, "%d", &opcionArea);

        switch (opcionArea){
            case 1:
                printf("\nSeleccione su rol del 1-4: ");
                printf("\n1.- Encargado de cocina (Chef)");
                printf("\n2.- Parrillero");
                printf("\n3.- Ayudante de cocina");
                printf("\n4.- Lavaloza");
                printf("\nOpcion: ");
                fgets(buffer, 20, stdin);
                sscanf(buffer, "%d", &opcionPuesto);
                switch (opcionPuesto){
                    case 1:
                        strcpy(puesto, "Chef");
                        strcpy(area, "Cocina");
                        break;
                    case 2:
                        strcpy(puesto, "Parrillero");
                        strcpy(area, "Cocina");
                        break;
                    case 3:
                        strcpy(puesto, "Ayudante de cocina");
                        strcpy(area, "Cocina");
                        break;
                    case 4:
                        strcpy(puesto, "Lavaloza");
                        strcpy(area, "Cocina");
                        break;
                    default:
                        printf("Indique una opcion valida por favor\n");
                        system("pause");
                        break;
                }
                break;
            case 2:
                printf("\nSeleccione su rol del 1-4: ");
                printf("\n1.- Cajero");
                printf("\n2.- Mesero");
                printf("\n3.- Hostess");
                printf("\n4.- Repartidor");
                printf("\nOpcion: ");
                fgets(buffer, 20, stdin);
                sscanf(buffer, "%d", &opcionPuesto);
                switch (opcionPuesto){
                    case 1:
                        strcpy(puesto, "Cajero");
                        strcpy(area, "Servicio y ventas");
                        break;
                    case 2:
                        strcpy(puesto, "Mesero");
                        strcpy(area, "Servicio y ventas");
                        break;
                    case 3:
                        strcpy(puesto, "Hostess");
                        strcpy(area, "Servicio y ventas");
                        break;
                    case 4:
                        strcpy(puesto, "Repartidor");
                        strcpy(area, "Servicio y ventas");
                        break;
                    default:
                        printf("Indique una opcion valida por favor\n");
                        system("pause");
                        break;
                }
                break;
            case 3:
                printf("\nSeleccione su rol del 1-2: ");
                printf("\n1.- Gerente de sucursal");
                printf("\n2.- Personal de limpieza");
                printf("\nOpcion: ");
                fgets(buffer, 20, stdin);
                sscanf(buffer, "%d", &opcionPuesto);
                switch (opcionPuesto){
                    case 1:
                        strcpy(puesto, "Gerente de sucursal");
                        strcpy(area, "Administracion y apoyo");
                        break;
                    case 2:
                        strcpy(puesto, "Personal de limpieza");
                        strcpy(area, "Administracion y apoyo");
                        break;
                    default:
                        printf("Indique una opcion valida por favor\n");
                        system("pause");
                        break;
                }
                break;
            default:
                printf("Ingrese una opcion valida por favor\n");
                system("pause");
                break;
        }
    }
};

struct Cliente {
    struct Persona clienPer;
    int puntos = 0;
};

struct Proveedor {
    struct Persona provePer;
    Producto producto;

    void registrarProducto(){
        char buffer[50];
        printf("\nIngrese el producto que suministra: ");
        fgets(producto.nombre, 30, stdin);
        producto.nombre[strcspn(producto.nombre, "\n")] = 0;
        printf("Ingrese la cantidad: ");
        fgets(buffer, 50, stdin);
        sscanf(buffer, "%d", &producto.cantidad);
    }

    void mostrarProducto(){
        printf("Producto: %s | Cantidad: %d\n", producto.nombre, producto.cantidad);
    }
};


const int MAX_CLIENTES    = 100;
const int MAX_EMPLEADOS   = 50;
const int MAX_PROVEEDORES = 10;

Cliente   clientes[MAX_CLIENTES];
Empleado  empleados[MAX_EMPLEADOS];
Proveedor proveedores[MAX_PROVEEDORES];

int numClientes    = 0;
int numEmpleados   = 0;
int numProveedores = 0;


// ============================================================
//  ARCHIVOS BINARIOS - GUARDAR
// ============================================================

void guardarEmpleados() {
    FILE *f = fopen("Empleados.dat", "wb");
    if (!f) { printf("Error al guardar empleados\n"); return; }
    fwrite(&numEmpleados, sizeof(int), 1, f);
    fwrite(empleados, sizeof(Empleado), numEmpleados, f);
    fclose(f);
}

void guardarClientes() {
    FILE *f = fopen("Clientes.dat", "wb");
    if (!f) { printf("Error al guardar clientes\n"); return; }
    fwrite(&numClientes, sizeof(int), 1, f);
    fwrite(clientes, sizeof(Cliente), numClientes, f);
    fclose(f);
}

void guardarProveedores() {
    FILE *f = fopen("Proveedores.dat", "wb");
    if (!f) { printf("Error al guardar proveedores\n"); return; }
    fwrite(&numProveedores, sizeof(int), 1, f);
    fwrite(proveedores, sizeof(Proveedor), numProveedores, f);
    fclose(f);
}

// ============================================================
//  ARCHIVOS BINARIOS - CARGAR
// ============================================================

void cargarEmpleados() {
    FILE *f = fopen("Empleados.dat", "rb");
    if (!f) return;
    fread(&numEmpleados, sizeof(int), 1, f);
    fread(empleados, sizeof(Empleado), numEmpleados, f);
    fclose(f);
}

void cargarClientes() {
    FILE *f = fopen("Clientes.dat", "rb");
    if (!f) return;
    fread(&numClientes, sizeof(int), 1, f);
    fread(clientes, sizeof(Cliente), numClientes, f);
    fclose(f);
}

void cargarProveedores() {
    FILE *f = fopen("Proveedores.dat", "rb");
    if (!f) return;
    fread(&numProveedores, sizeof(int), 1, f);
    fread(proveedores, sizeof(Proveedor), numProveedores, f);
    fclose(f);
}


// ============================================================
//  FUNCIONES GENERALES
// ============================================================

void registrarPersona(Persona &p){
    printf("\nIngrese nombre: ");
    fgets(p.nombre, 20, stdin);
    p.nombre[strcspn(p.nombre, "\n")] = 0;

    printf("Ingrese direccion: ");
    fgets(p.direccion, 50, stdin);
    p.direccion[strcspn(p.direccion, "\n")] = 0;

    printf("Ingrese telefono: ");
    fgets(p.telefono, 15, stdin);
    p.telefono[strcspn(p.telefono, "\n")] = 0;
}

int pedirEdad(){
    char buffer[20];
    int edad;
    do {
        printf("Ingrese edad: ");
        fgets(buffer, 20, stdin);
        sscanf(buffer, "%d", &edad);
        if(edad < 18){
            printf("El empleado debe ser mayor de 18 anos\n");
            system("pause");
        }
    } while(edad < 18);
    return edad;
}

void agregarCliente(){
    if(numClientes >= MAX_CLIENTES){
        printf("\nNo se pueden agregar mas clientes\n");
        system("pause");
        return;
    }
    registrarPersona(clientes[numClientes].clienPer);
    numClientes++;
    guardarClientes();   // <-- guarda tras agregar
    printf("\nCliente agregado correctamente\n");
    system("pause");
}

void agregarEmpleado(){
    if(numEmpleados >= MAX_EMPLEADOS){
        printf("\nNo se pueden agregar mas empleados\n");
        system("pause");
        return;
    }
    registrarPersona(empleados[numEmpleados].emplePer);
    empleados[numEmpleados].edad = pedirEdad();
    char buffer[20];
    printf("Ingrese sueldo diario: ");
    fgets(buffer, 20, stdin);
    sscanf(buffer, "%d", &empleados[numEmpleados].sueldoDiario);
    empleados[numEmpleados].calcularSueldo();
    empleados[numEmpleados].guardarInfo();
    numEmpleados++;
    guardarEmpleados();  // <-- guarda tras agregar
    printf("\nEmpleado agregado correctamente\n");
    system("pause");
}

void agregarProveedor(){
    if(numProveedores >= MAX_PROVEEDORES){
        printf("\nNo se pueden agregar mas proveedores\n");
        system("pause");
        return;
    }
    registrarPersona(proveedores[numProveedores].provePer);
    proveedores[numProveedores].registrarProducto();
    numProveedores++;
    guardarProveedores();  // <-- guarda tras agregar
    printf("\nProveedor agregado correctamente\n");
    system("pause");
}

void mostrarClientes(){
    if(numClientes == 0){
        printf("\nNo hay clientes registrados este mes\n");
        system("pause");
        return;
    }
    system("cls");
    printf("\n--- Clientes atendidos este mes ---\n");
    for(int i = 0; i < numClientes; i++){
        printf("\nCliente #%d\n", i + 1);
        printf("Nombre:    %s\n", clientes[i].clienPer.nombre);
        printf("Direccion: %s\n", clientes[i].clienPer.direccion);
        printf("Telefono:  %s\n", clientes[i].clienPer.telefono);
        printf("Puntos:    %d\n", clientes[i].puntos);
    }
}

void mostrarEmpleados(){
    if(numEmpleados == 0){
        printf("\nNo hay empleados registrados\n");
        system("pause");
        return;
    }
    system("cls");
    printf("\n--- Empleados registrados ---\n");
    for(int i = 0; i < numEmpleados; i++){
        printf("\nEmpleado #%d\n", i + 1);
        printf("Nombre:         %s\n", empleados[i].emplePer.nombre);
        printf("Direccion:      %s\n", empleados[i].emplePer.direccion);
        printf("Telefono:       %s\n", empleados[i].emplePer.telefono);
        printf("Edad:           %d\n", empleados[i].edad);
        printf("Area:           %s\n", empleados[i].area);
        printf("Puesto:         %s\n", empleados[i].puesto);
        printf("Sueldo diario:  %d\n", empleados[i].sueldoDiario);
        printf("Sueldo mensual: %d\n", empleados[i].sueldoMensual);
    }
}

void mostrarProveedores(){
    if(numProveedores == 0){
        printf("\nNo hay proveedores registrados\n");
        system("pause");
        return;
    }
    system("cls");
    printf("\n--- Proveedores registrados ---\n");
    for(int i = 0; i < numProveedores; i++){
        printf("\nProveedor #%d\n", i + 1);
        printf("Nombre:    %s\n", proveedores[i].provePer.nombre);
        printf("Direccion: %s\n", proveedores[i].provePer.direccion);
        printf("Telefono:  %s\n", proveedores[i].provePer.telefono);
        proveedores[i].mostrarProducto();
    }
}


void eliminarCliente(){
    if(numClientes == 0){
        printf("\nNo hay clientes para eliminar\n");
        system("pause");
        return;
    }
    mostrarClientes();
    char buffer[20];
    printf("\nIngrese el numero del cliente a eliminar: ");
    fgets(buffer, 20, stdin);
    int idx;
    sscanf(buffer, "%d", &idx);
    idx--;
    if(idx < 0 || idx >= numClientes){
        printf("Indice invalido\n");
        system("pause");
        return;
    }
    for(int i = idx; i < numClientes - 1; i++){
        clientes[i] = clientes[i + 1];
    }
    numClientes--;
    guardarClientes();   // <-- guarda tras eliminar
    printf("Cliente eliminado correctamente\n");
    system("pause");
}

void eliminarEmpleado(){
    if(numEmpleados == 0){
        printf("\nNo hay empleados para eliminar\n");
        system("pause");
        return;
    }
    mostrarEmpleados();
    char buffer[20];
    printf("\nIngrese el numero del empleado a eliminar: ");
    fgets(buffer, 20, stdin);
    int idx;
    sscanf(buffer, "%d", &idx);
    idx--;
    if(idx < 0 || idx >= numEmpleados){
        printf("Indice invalido\n");
        system("pause");
        return;
    }
    for(int i = idx; i < numEmpleados - 1; i++){
        empleados[i] = empleados[i + 1];
    }
    numEmpleados--;
    guardarEmpleados();  // <-- guarda tras eliminar
    printf("Empleado eliminado correctamente\n");
    system("pause");
}

void eliminarProveedor(){
    if(numProveedores == 0){
        printf("\nNo hay proveedores para eliminar\n");
        system("pause");
        return;
    }
    mostrarProveedores();
    char buffer[20];
    printf("\nIngrese el numero del proveedor a eliminar: ");
    fgets(buffer, 20, stdin);
    int idx;
    sscanf(buffer, "%d", &idx);
    idx--;
    if(idx < 0 || idx >= numProveedores){
        printf("Indice invalido\n");
        system("pause");
        return;
    }
    for(int i = idx; i < numProveedores - 1; i++){
        proveedores[i] = proveedores[i + 1];
    }
    numProveedores--;
    guardarProveedores();  // <-- guarda tras eliminar
    printf("Proveedor eliminado correctamente\n");
    system("pause");
}

void preguntarContinuar(bool &enSubmenu){
    char buffer[20];
    int opcion;
    printf("\n1.- Volver al submenu");
    printf("\n2.- Volver al menu principal");
    printf("\n3.- Salir");
    printf("\nOpcion: ");
    fgets(buffer, 20, stdin);
    sscanf(buffer, "%d", &opcion);
    switch(opcion){
        case 1: break;
        case 2: enSubmenu = false; break;
        case 3:
            printf("\nHasta luego!\n");
            exit(0);
        default:
            printf("Opcion invalida, regresando al submenu\n");
            system("pause");
    }
}

void submenuClientes(){
    bool enSubmenu = true;
    while(enSubmenu){
        system("cls");
        printf("\n=== CLIENTES ===");
        printf("\n1.- Ver clientes");
        printf("\n2.- Agregar cliente");
        printf("\n3.- Eliminar cliente");
        printf("\n4.- Volver al menu principal");
        printf("\nOpcion: ");
        char buffer[20];
        int opcion;
        fgets(buffer, 20, stdin);
        sscanf(buffer, "%d", &opcion);
        switch(opcion){
            case 1:
                mostrarClientes();
                if(numClientes > 0) preguntarContinuar(enSubmenu);
                break;
            case 2:
                agregarCliente();
                preguntarContinuar(enSubmenu);
                break;
            case 3:
                eliminarCliente();
                preguntarContinuar(enSubmenu);
                break;
            case 4:
                enSubmenu = false;
                break;
            default:
                printf("Opcion invalida\n");
                system("pause");
        }
    }
}

void submenuEmpleados(){
    bool enSubmenu = true;
    while(enSubmenu){
        system("cls");
        printf("\n=== EMPLEADOS ===");
        printf("\n1.- Ver empleados");
        printf("\n2.- Agregar empleado");
        printf("\n3.- Eliminar empleado");
        printf("\n4.- Volver al menu principal");
        printf("\nOpcion: ");
        char buffer[20];
        int opcion;
        fgets(buffer, 20, stdin);
        sscanf(buffer, "%d", &opcion);
        switch(opcion){
            case 1:
                mostrarEmpleados();
                if(numEmpleados > 0) preguntarContinuar(enSubmenu);
                break;
            case 2:
                agregarEmpleado();
                preguntarContinuar(enSubmenu);
                break;
            case 3:
                eliminarEmpleado();
                preguntarContinuar(enSubmenu);
                break;
            case 4:
                enSubmenu = false;
                break;
            default:
                printf("Opcion invalida\n");
                system("pause");
        }
    }
}

void submenuProveedores(){
    bool enSubmenu = true;
    while(enSubmenu){
        system("cls");
        printf("\n=== PROVEEDORES ===");
        printf("\n1.- Ver proveedores");
        printf("\n2.- Agregar proveedor");
        printf("\n3.- Eliminar proveedor");
        printf("\n4.- Volver al menu principal");
        printf("\nOpcion: ");
        char buffer[20];
        int opcion;
        fgets(buffer, 20, stdin);
        sscanf(buffer, "%d", &opcion);
        switch(opcion){
            case 1:
                mostrarProveedores();
                if(numProveedores > 0) preguntarContinuar(enSubmenu);
                break;
            case 2:
                agregarProveedor();
                preguntarContinuar(enSubmenu);
                break;
            case 3:
                eliminarProveedor();
                preguntarContinuar(enSubmenu);
                break;
            case 4:
                enSubmenu = false;
                break;
            default:
                printf("Opcion invalida\n");
                system("pause");
        }
    }
}

int main(){
    // Cargar datos guardados al iniciar el programa
    cargarEmpleados();
    cargarClientes();
    cargarProveedores();

    bool corriendo = true;
    while(corriendo){
        system("cls");
        printf("\n==============================");
        printf("\n  Bienvenido al sistema de");
        printf("\n     gestion de personal");
        printf("\n==============================");
        printf("\n1.- Clientes");
        printf("\n2.- Empleados");
        printf("\n3.- Proveedores");
        printf("\n4.- Salir");
        printf("\nOpcion: ");
        char buffer[20];
        int opcion;
        fgets(buffer, 20, stdin);
        sscanf(buffer, "%d", &opcion);
        switch(opcion){
            case 1:
                submenuClientes();
                break;
            case 2:
                submenuEmpleados();
                break;
            case 3:
                submenuProveedores();
                break;
            case 4:
                corriendo = false;
                break;
            default:
                printf("Opcion invalida, intente de nuevo\n");
                system("pause");
        }
    }
    printf("\nHasta luego!\n");
    return 0;
}