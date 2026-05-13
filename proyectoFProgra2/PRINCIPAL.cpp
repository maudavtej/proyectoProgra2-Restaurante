
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <iostream>
using namespace std;
#include <graphics.h>  


// --- Productos ---
typedef struct { char nombre[50]; float precio; } producto;
typedef struct { char nombre[50]; float precioG; float precioCh; } prod2;

// --- Promociones ---
typedef struct {
    char nombre[50];
    int  precio;
    char diapromo[20];
    int  numComp;
    union opciones { char comp[20]; int desc; };
} marzo;
typedef enum { lun=1, mar, mier, juev, vier, sab, dom } semana;

// --- Empleados / Clientes / Proveedores ---
struct Persona  { char nombre[20]; char direccion[50]; char telefono[15]; };
struct Producto { char nombre[30]; int cantidad; };
struct Empleado {
    struct Persona emplePer;
    int edad, sueldoDiario, sueldoMensual;
    char area[30], puesto[30];
    void calcularSueldo(){ sueldoMensual = sueldoDiario * 20; }
    void guardarInfo(){
        int opcionArea=0, opcionPuesto=0;
        char buffer[20];
        printf("\nArea de trabajo:\n1.Cocina\n2.Servicio y ventas\n3.Administrativa\nOpcion: ");
        fgets(buffer,20,stdin); sscanf(buffer,"%d",&opcionArea);
        switch(opcionArea){
            case 1:
                printf("1.Chef\n2.Parrillero\n3.Ayudante\n4.Lavaloza\nOpcion: ");
                fgets(buffer,20,stdin); sscanf(buffer,"%d",&opcionPuesto);
                { const char *puestos[]={"Chef","Parrillero","Ayudante de cocina","Lavaloza"};
                  if(opcionPuesto>=1&&opcionPuesto<=4){ strcpy(puesto,puestos[opcionPuesto-1]); strcpy(area,"Cocina"); } }
                break;
            case 2:
                printf("1.Cajero\n2.Mesero\n3.Hostess\n4.Repartidor\nOpcion: ");
                fgets(buffer,20,stdin); sscanf(buffer,"%d",&opcionPuesto);
                { const char *puestos[]={"Cajero","Mesero","Hostess","Repartidor"};
                  if(opcionPuesto>=1&&opcionPuesto<=4){ strcpy(puesto,puestos[opcionPuesto-1]); strcpy(area,"Servicio y ventas"); } }
                break;
            case 3:
                printf("1.Gerente de sucursal\n2.Personal de limpieza\nOpcion: ");
                fgets(buffer,20,stdin); sscanf(buffer,"%d",&opcionPuesto);
                { const char *puestos[]={"Gerente de sucursal","Personal de limpieza"};
                  if(opcionPuesto>=1&&opcionPuesto<=2){ strcpy(puesto,puestos[opcionPuesto-1]); strcpy(area,"Administracion y apoyo"); } }
                break;
            default: printf("Opcion invalida\n"); break;
        }
    }
};
struct Cliente   { struct Persona clienPer; int puntos=0; };
struct Proveedor {
    struct Persona provePer;
    Producto producto;
    void registrarProducto(){
        char buffer[50];
        printf("Producto que suministra: "); fgets(producto.nombre,30,stdin);
        producto.nombre[strcspn(producto.nombre,"\n")]=0;
        printf("Cantidad: "); fgets(buffer,50,stdin); sscanf(buffer,"%d",&producto.cantidad);
    }
    void mostrarProducto(){ printf("Producto: %s | Cantidad: %d\n",producto.nombre,producto.cantidad); }
};

// --- Auto Burguer ---
struct caract    { char descripcion[100]; };
struct autoPack  { int opcion; char caracteristicas[50]; float precio; caract descr; };

// --- Ventas ---
typedef struct {
    int semana; char dia_nombre[12]; float precio; int cantidad; char paquete[100];
} Venta;

// ============================================================
//  ===  DATOS GLOBALES  ===
// ============================================================

// Productos
producto hamburguesas[4]={{"Hamburguesa Sencilla",45},{"Hamburguesa Con queso",65},{"Hamburguesa Hawaiana",90},{"Hamburguesa Doble queso",85}};
prod2    refresco[3]    ={{"Coca-Cola",35,45},{"Sprite",35,45},{"Manzanita",35,45}};
producto pay[3]         ={{"Pay de Manzana",30},{"Pay de Pinia",40},{"Pay de Queso",35}};
producto papas[2]       ={{"Papas grandes",45},{"Papas chicas",35}};
producto helado[2]      ={{"Chocolate",30},{"Vainilla",25}};
producto paquete1[1]    ={{"PAQUETE INDIVIDUAL",110}};
producto paquete2[1]    ={{"COMBO",239}};

// Promociones
marzo dias[7]={
    {"Lunes de queso",    49, "Lunes",     1},
    {"Martes de Pareja", 169, "Martes",    3},
    {"Miercoles de Cono",129, "Miercoles", 2},
    {"Jueves del Rey",   129, "Jueves",    2},
    {"Viernes Whoper",   139, "Viernes",   2},
    {"Sabado de amigos",  99, "Sabado",    3},
    {"Domingo de Rodeo",  59, "Domingo",   1},
};

// Empleados / Clientes / Proveedores
const int MAX_CLIENTES=100, MAX_EMPLEADOS=50, MAX_PROVEEDORES=10;
Cliente   clientes[MAX_CLIENTES];
Empleado  empleados[MAX_EMPLEADOS];
Proveedor proveedores[MAX_PROVEEDORES];
int numClientes=0, numEmpleados=0, numProveedores=0;

// ============================================================
//  ===  UTILIDADES  ===
// ============================================================

int validacion(int min, int max){
    int valor;
    while(scanf("%d",&valor)!=1||valor<min||valor>max){
        printf("Opcion invalida. Intente nuevamente: ");
        while(getchar()!='\n');
    }
    return valor;
}

int genNOrden(){ return rand()%90000+10000; }

void limpiarBuffer(){ while(getchar()!='\n'); }

// ============================================================
//  ===  PERSISTENCIA - PRODUCTOS  ===
// ============================================================

void guardarProductos(){
    FILE *f=fopen("productos.bin","wb"); if(!f){printf("Error al guardar productos\n");return;}
    fwrite(hamburguesas,sizeof(producto),4,f); fwrite(refresco,sizeof(prod2),3,f);
    fwrite(pay,sizeof(producto),3,f);          fwrite(papas,sizeof(producto),2,f);
    fwrite(helado,sizeof(producto),2,f);       fwrite(paquete1,sizeof(producto),1,f);
    fwrite(paquete2,sizeof(producto),1,f);     fclose(f);
    printf("Productos guardados.\n");
}

void cargarProductos(){
    FILE *f=fopen("productos.bin","rb");
    if(!f){ printf("Archivo no encontrado. Usando productos por defecto.\n"); guardarProductos(); return; }
    fread(hamburguesas,sizeof(producto),4,f); fread(refresco,sizeof(prod2),3,f);
    fread(pay,sizeof(producto),3,f);          fread(papas,sizeof(producto),2,f);
    fread(helado,sizeof(producto),2,f);       fread(paquete1,sizeof(producto),1,f);
    fread(paquete2,sizeof(producto),1,f);     fclose(f);
}

// ============================================================
//  ===  PERSISTENCIA - PROMOCIONES  ===
// ============================================================

void guardarPromociones(){
    FILE *f=fopen("promociones.bin","wb"); if(!f){printf("Error al guardar promociones\n");return;}
    fwrite(dias,sizeof(marzo),7,f); fclose(f); printf("Promociones guardadas.\n");
}

void cargarPromociones(){
    FILE *f=fopen("promociones.bin","rb");
    if(!f){ printf("Archivo no encontrado. Usando promociones por defecto.\n"); guardarPromociones(); return; }
    fread(dias,sizeof(marzo),7,f); fclose(f);
}

// ============================================================
//  ===  PERSISTENCIA - EMPLEADOS / CLIENTES / PROVEEDORES  ===
// ============================================================

void guardarEmpleados(){ FILE *f=fopen("Empleados.dat","wb"); if(!f)return; fwrite(&numEmpleados,sizeof(int),1,f); fwrite(empleados,sizeof(Empleado),numEmpleados,f); fclose(f); }
void guardarClientes(){  FILE *f=fopen("Clientes.dat","wb");  if(!f)return; fwrite(&numClientes,sizeof(int),1,f);  fwrite(clientes,sizeof(Cliente),numClientes,f);   fclose(f); }
void guardarProveedores(){FILE *f=fopen("Proveedores.dat","wb");if(!f)return;fwrite(&numProveedores,sizeof(int),1,f);fwrite(proveedores,sizeof(Proveedor),numProveedores,f);fclose(f);}

void cargarEmpleados(){  FILE *f=fopen("Empleados.dat","rb");   if(!f)return; fread(&numEmpleados,sizeof(int),1,f);  fread(empleados,sizeof(Empleado),numEmpleados,f);   fclose(f); }
void cargarClientes(){   FILE *f=fopen("Clientes.dat","rb");    if(!f)return; fread(&numClientes,sizeof(int),1,f);   fread(clientes,sizeof(Cliente),numClientes,f);    fclose(f); }
void cargarProveedores(){FILE *f=fopen("Proveedores.dat","rb"); if(!f)return; fread(&numProveedores,sizeof(int),1,f);fread(proveedores,sizeof(Proveedor),numProveedores,f);fclose(f);}

// ============================================================
//  ===  MODULO 1 - VENTAS (MENU PRODUCTOS)  ===
// ============================================================

float menuVentas(char pedido[]){
    int eleccion,cantidad,opcSab,opcTam,opcion;
    float total=0;
    do {
        printf("\n===== MENU MAC BURGUER =====\n");
        printf("1.Hamburguesas\n2.Adicionales\n3.Combo\n4.Pagar\n");
        eleccion=validacion(1,4);
        switch(eleccion){
        case 1:
            printf("Numero de hamburguesas: "); cantidad=validacion(1,50);
            for(int i=0;i<cantidad;i++){
                printf("Sabor hamburguesa #%d:\n",i+1);
                for(int j=0;j<4;j++) printf("%d.%s\n",j+1,hamburguesas[j].nombre);
                opcion=validacion(1,5);
                if(opcion==5){printf("Regresando...\n");break;}
                strcat(pedido,hamburguesas[opcion-1].nombre); strcat(pedido,"\n");
                total+=hamburguesas[opcion-1].precio;
            } break;
        case 2:
            printf("1.Papas\n2.Refrescos\n3.Helados\n4.Pay\n5.Salir\n");
            opcion=validacion(1,5);
            switch(opcion){
            case 1:
                printf("Papas a ordenar: "); cantidad=validacion(1,10);
                for(int i=0;i<cantidad;i++){
                    printf("Tamano papas #%d:\n1.Grandes\n2.Chicas\n3.Salir\n",i+1);
                    opcTam=validacion(1,3); if(opcTam==3)break;
                    strcat(pedido,papas[opcTam-1].nombre); strcat(pedido,"\n"); total+=papas[opcTam-1].precio;
                } break;
            case 2:
                printf("Bebidas a ordenar: "); cantidad=validacion(1,20);
                for(int i=0;i<cantidad;i++){
                    for(int j=0;j<3;j++) printf("%d.%s\n",j+1,refresco[j].nombre);
                    opcion=validacion(0,3); if(opcion==0)break;
                    printf("1.Grande\n2.Chico\n"); scanf("%d",&opcTam); limpiarBuffer();
                    strcat(pedido,refresco[opcion-1].nombre);
                    if(opcTam==1){total+=refresco[opcion-1].precioG;strcat(pedido," (Grande)\n");}
                    else         {total+=refresco[opcion-1].precioCh;strcat(pedido," (Chico)\n");}
                } break;
            case 3:
                printf("Helados a ordenar: "); cantidad=validacion(1,5);
                for(int i=0;i<cantidad;i++){
                    printf("Sabor #%d:\n1.Chocolate\n2.Vainilla\n",i+1);
                    scanf("%d",&opcSab); limpiarBuffer();
                    if(opcSab==1||opcSab==2){strcat(pedido,helado[opcSab-1].nombre);strcat(pedido,"\n");total+=helado[opcSab-1].precio;}
                    else{printf("Invalido\n");i--;}
                } break;
            case 4:
                printf("Pays a ordenar: "); cantidad=validacion(1,5);
                for(int i=0;i<cantidad;i++){
                    for(int j=0;j<3;j++) printf("%d.%s\n",j+1,pay[j].nombre);
                    opcSab=validacion(0,3); if(opcSab==0)break;
                    strcat(pedido,pay[opcSab-1].nombre); strcat(pedido,"\n"); total+=pay[opcSab-1].precio;
                } break;
            case 5: break;
            } break;
        case 3:
            printf("1.Individual\n2.Paquete grande\n3.Salir\n");
            eleccion=validacion(1,3);
            if(eleccion==1){printf("-Hamburguesa sencilla\n-Papas chicas\n-Refresco chico\n-Helado\n");strcat(pedido,paquete1[0].nombre);strcat(pedido,"\n");total+=paquete1[0].precio;}
            else if(eleccion==2){printf("Combo completo\n");strcat(pedido,paquete2[0].nombre);strcat(pedido,"\n");total+=paquete2[0].precio;}
            break;
        case 4: printf("Finalizando pedido...\n"); break;
        }
    } while(eleccion!=4);
    return total;
}

void moduloVentas(){
    char pedido[500]="";
    float total=menuVentas(pedido);
    int folio=genNOrden();
    printf("\n===== TICKET =====\n");
    printf("Orden No. %d\n",folio);
    printf("====  PEDIDO  ====\n%s",pedido);
    printf("====  TOTAL  ====\n$%.2f\n",total);
    printf("Presione ENTER para continuar..."); limpiarBuffer(); getchar();
}

// ============================================================
//  ===  MODULO 2 - PROMOCIONES  ===
// ============================================================

void moduloPromociones(){
    int opcion,opcCom,opc3,fin=0;
    do {
        printf("\n===== PROMOCIONES DEL DIA =====\n");
        printf("1.Lunes\n2.Martes\n3.Miercoles\n4.Jueves\n5.Viernes\n6.Sabado\n7.Domingo\n8.Regresar\n");
        scanf("%d",&opcion); limpiarBuffer();
        if(opcion>=1&&opcion<=7){
            int idx=opcion-1;
            printf("PROMO: %s\nPRECIO: $%d\nDIA: %s\nCOMPONENTES: #%d\n",
                   dias[idx].nombre,dias[idx].precio,dias[idx].diapromo,dias[idx].numComp);
            if(opcion==1){
                printf("1.Elegir complemento\n2.Aceptar descuento\n");
                scanf("%d",&opcCom); limpiarBuffer();
                if(opcCom==1){
                    printf("1.Refresco\n2.Cono\n3.Empanada\n");
                    scanf("%d",&opc3); limpiarBuffer();
                    const char *comp[]={"Refresco","Cono","Empanada"};
                    if(opc3>=1&&opc3<=3) printf("Complemento: %s\n",comp[opc3-1]);
                }
            }
        } else if(opcion==8) fin=1;
        else printf("Opcion invalida.\n");
    } while(!fin);
}

// ============================================================
//  ===  MODULO 3 - AUTO BURGUER  ===
// ============================================================

float menuAutoBurguer(char historial[]){
    autoPack paquetes[3]={
        {1,"ADULTO",  249,{"Hamburguesa doble + sencilla\nPapas grandes\nRefresco grande"}},
        {2,"NINO",    149,{"Hamburguesa sencilla\nPapas chicas\nRefresco chico\nNuggets"}},
        {3,"FAMILIAR",499,{"4 hamburguesas con queso\n4 refrescos grandes\n4 papas grandes\n4 helados"}}
    };
    int eleccion,eleccionMen; float total=0;
    do {
        printf("\n===== AUTO BURGUER =====\n1.Paquete ADULTO\n2.Paquete NINO\n3.Paquete FAMILIAR\n4.Pagar\n");
        eleccion=validacion(1,4);
        if(eleccion>=1&&eleccion<=3){
            int idx=eleccion-1;
            printf("Paquete: %s  $%.0f\n%s\n",paquetes[idx].caracteristicas,paquetes[idx].precio,paquetes[idx].descr.descripcion);
            printf("1.Agregar al pedido\n2.Regresar\n"); eleccionMen=validacion(1,2);
            if(eleccionMen==1){
                printf("Numero de paquetes: "); int cant=validacion(1,10);
                strcat(historial,paquetes[idx].caracteristicas); strcat(historial,"\n");
                total+=paquetes[idx].precio*cant;
            }
        }
    } while(eleccion!=4);
    return total;
}

void moduloAutoBurguer(){
    char historial[500]="";
    float total=menuAutoBurguer(historial);
    int folio=genNOrden();
    printf("\n===== TICKET AUTO BURGUER =====\n");
    printf("Orden No. %d\n",folio);
    printf("%s\nTOTAL: $%.2f\n",historial,total);
    printf("Presione ENTER para continuar..."); limpiarBuffer(); getchar();
}

// ============================================================
//  ===  MODULO 4 - REPORTE DE VENTAS (2 SEMANAS)  ===
// ============================================================

void moduloVentasSemanas(){
    Venta sema[14]={
        {1,"Lunes",    49, 300,"Hamburguesa con queso"},
        {1,"Martes",  169, 250,"Combo parejas"},
        {1,"Miercoles",129,180,"Combo Whopper con cono"},
        {1,"Jueves",  129, 400,"Combo Classic Crispy King + cono"},
        {1,"Viernes", 139, 450,"Combo Whopper + papas"},
        {1,"Sabado",   99, 280,"Auto King 3 hamburguesas"},
        {1,"Domingo",  59, 300,"Long rodeo (hamburguesa grande)"},
        {2,"Lunes",    49, 400,"Hamburguesa con queso"},
        {2,"Martes",  169, 350,"Combo parejas"},
        {2,"Miercoles",129,320,"Combo Whopper con cono"},
        {2,"Jueves",  129, 499,"Combo Classic Crispy King + cono"},
        {2,"Viernes", 139, 520,"Combo Whopper + papas"},
        {2,"Sabado",   99, 350,"Auto King 3 hamburguesas"},
        {2,"Domingo",  99, 400,"Long rodeo (hamburguesa grande)"}
    };
    FILE *archivo=fopen("ventas.dat","wb");
    if(archivo){fwrite(sema,sizeof(Venta),14,archivo);fclose(archivo);printf("Registros guardados.\n");}
    archivo=fopen("ventas.dat","rb");
    if(!archivo){printf("Error al abrir archivo\n");return;}
    Venta venta; float vS1=0,vS2=0;
    printf("\n==========================================\n");
    printf("          REPORTE DE VENTAS\n");
    printf("==========================================\n");
    printf("%-4s | %-10s | %-30s | %s\n","SEM","DIA","PRODUCTO","TOTAL");
    printf("------------------------------------------\n");
    while(fread(&venta,sizeof(Venta),1,archivo)==1){
        float sub=venta.precio*venta.cantidad;
        if(venta.semana==1)vS1+=sub; else vS2+=sub;
        printf("%-4d | %-10s | %-30s | $%.2f\n",venta.semana,venta.dia_nombre,venta.paquete,sub);
    }
    printf("==========================================\n");
    printf("  SEMANA 1: $%.2f\n  SEMANA 2: $%.2f\n  TOTAL:    $%.2f\n",vS1,vS2,vS1+vS2);
    printf("==========================================\n");
    fclose(archivo);
    printf("Presione ENTER para continuar..."); limpiarBuffer(); getchar();
}

// ============================================================
//  ===  MODULO 5 - MODIFICAR BINARIO  ===
// ============================================================

void moduloModificaBinary(){
    char nombreArchivo[50];
    printf("Nombre del archivo binario a modificar: ");
    fgets(nombreArchivo,sizeof(nombreArchivo),stdin);
    nombreArchivo[strcspn(nombreArchivo,"\n")]=0;
    FILE *fi=fopen(nombreArchivo,"r+b");
    if(!fi){printf("Error al abrir el archivo\n");return;}
    producto p; int pos;
    printf("\n--- Contenido actual ---\n");
    while(fread(&p,sizeof(p),1,fi)==1) printf("  %s  $%.2f\n",p.nombre,p.precio);
    rewind(fi);
    int opc; printf("\nModificar? 1=Si / 2=No: "); scanf("%d",&opc); limpiarBuffer();
    if(opc==1){
        char nombre[50];
        printf("Nombre del producto a modificar: "); fgets(nombre,sizeof(nombre),stdin);
        nombre[strcspn(nombre,"\n")]=0;
        rewind(fi);
        while(fread(&p,sizeof(p),1,fi)==1){
            if(strcmp(nombre,p.nombre)==0){
                printf("Nuevo nombre: "); fgets(p.nombre,sizeof(p.nombre),stdin); p.nombre[strcspn(p.nombre,"\n")]=0;
                printf("Nuevo precio: "); scanf("%f",&p.precio); limpiarBuffer();
                pos=(int)ftell(fi)-sizeof(p);
                fseek(fi,pos,SEEK_SET);
                fwrite(&p,sizeof(p),1,fi);
                printf("Registro modificado exitosamente.\n"); break;
            }
        }
    }
    fclose(fi);
    printf("Presione ENTER para continuar..."); getchar();
}

// ============================================================
//  ===  MODULO 6 - GESTION DE PERSONAL  ===
// ============================================================

void registrarPersona(Persona &p){
    printf("Nombre: ");    fgets(p.nombre,20,stdin);    p.nombre[strcspn(p.nombre,"\n")]=0;
    printf("Direccion: "); fgets(p.direccion,50,stdin); p.direccion[strcspn(p.direccion,"\n")]=0;
    printf("Telefono: ");  fgets(p.telefono,15,stdin);  p.telefono[strcspn(p.telefono,"\n")]=0;
}

void agregarEmpleado(){
    if(numEmpleados>=MAX_EMPLEADOS){printf("Limite alcanzado\n");return;}
    registrarPersona(empleados[numEmpleados].emplePer);
    char buffer[20];
    do{ printf("Edad: "); fgets(buffer,20,stdin); sscanf(buffer,"%d",&empleados[numEmpleados].edad); } while(empleados[numEmpleados].edad<18);
    printf("Sueldo diario: "); fgets(buffer,20,stdin); sscanf(buffer,"%d",&empleados[numEmpleados].sueldoDiario);
    empleados[numEmpleados].calcularSueldo();
    empleados[numEmpleados].guardarInfo();
    numEmpleados++;
    guardarEmpleados();
    printf("Empleado registrado.\n");
}

void agregarCliente(){
    if(numClientes>=MAX_CLIENTES){printf("Limite alcanzado\n");return;}
    registrarPersona(clientes[numClientes].clienPer);
    numClientes++;
    guardarClientes();
    printf("Cliente registrado.\n");
}

void agregarProveedor(){
    if(numProveedores>=MAX_PROVEEDORES){printf("Limite alcanzado\n");return;}
    registrarPersona(proveedores[numProveedores].provePer);
    proveedores[numProveedores].registrarProducto();
    numProveedores++;
    guardarProveedores();
    printf("Proveedor registrado.\n");
}

void mostrarEmpleados(){
    if(numEmpleados==0){printf("No hay empleados.\n");return;}
    for(int i=0;i<numEmpleados;i++)
        printf("#%d  %s | %s | %s | Sueldo mensual: $%d\n",i+1,
               empleados[i].emplePer.nombre,empleados[i].puesto,empleados[i].area,empleados[i].sueldoMensual);
}
void mostrarClientes(){
    if(numClientes==0){printf("No hay clientes.\n");return;}
    for(int i=0;i<numClientes;i++)
        printf("#%d  %s | Tel: %s\n",i+1,clientes[i].clienPer.nombre,clientes[i].clienPer.telefono);
}
void mostrarProveedores(){
    if(numProveedores==0){printf("No hay proveedores.\n");return;}
    for(int i=0;i<numProveedores;i++){
        printf("#%d  %s | ",i+1,proveedores[i].provePer.nombre);
        proveedores[i].mostrarProducto();
    }
}

void submenuPersonal(){
    int opc; char buffer[20]; bool corriendo=true;
    while(corriendo){
        system("cls");
        printf("\n=== GESTION DE PERSONAL ===\n");
        printf("1.Empleados\n2.Clientes\n3.Proveedores\n4.Regresar\nOpcion: ");
        fgets(buffer,20,stdin); sscanf(buffer,"%d",&opc);
        switch(opc){
        case 1:{
            int o2;
            printf("1.Ver\n2.Agregar\n3.Regresar\nOpcion: ");
            fgets(buffer,20,stdin); sscanf(buffer,"%d",&o2);
            if(o2==1)mostrarEmpleados(); else if(o2==2)agregarEmpleado();
            printf("ENTER para continuar..."); getchar(); break;
        }
        case 2:{
            int o2;
            printf("1.Ver\n2.Agregar\n3.Regresar\nOpcion: ");
            fgets(buffer,20,stdin); sscanf(buffer,"%d",&o2);
            if(o2==1)mostrarClientes(); else if(o2==2)agregarCliente();
            printf("ENTER para continuar..."); getchar(); break;
        }
        case 3:{
            int o2;
            printf("1.Ver\n2.Agregar\n3.Regresar\nOpcion: ");
            fgets(buffer,20,stdin); sscanf(buffer,"%d",&o2);
            if(o2==1)mostrarProveedores(); else if(o2==2)agregarProveedor();
            printf("ENTER para continuar..."); getchar(); break;
        }
        case 4: corriendo=false; break;
        default: printf("Invalido\n"); getchar();
        }
    }
}

// ============================================================
//  ===  MODULO 7 - ANIMACION GRAFICA DE HAMBURGUESA  ===
//       Usa WinBGIm (graphics.h)
// ============================================================

void dibujarHamburguesa(int cx, int cy, float escala){
    // Calculamos alturas de cada capa
    int w  = (int)(260 * escala);   // ancho medio
    int h1 = (int)(55  * escala);   // pan superior
    int h2 = (int)(18  * escala);   // lechuga
    int h3 = (int)(22  * escala);   // tomate
    int h4 = (int)(30  * escala);   // carne
    int h5 = (int)(15  * escala);   // queso
    int h6 = (int)(38  * escala);   // pan inferior
    int gap = (int)(4  * escala);

    int y = cy - (h1+h2+h3+h4+h5+h6 + 5*gap)/2;

    setfillstyle(SOLID_FILL, 6);       
    setcolor(DARKGRAY);
    fillellipse(cx, y + h1/3, w, h1/2);
    bar(cx - w, y + h1/3, cx + w, y + h1);
    setfillstyle(SOLID_FILL, 14);        
    for(int i = -2; i <= 2; i++){
        fillellipse(cx + i*45*(int)escala,
                    y + (int)(12*escala), (int)(5*escala), (int)(4*escala));
    }
    y += h1 + gap;

    // ----- LECHUGA -----
    setfillstyle(SOLID_FILL, 2);         // verde
    setcolor(GREEN);
    // ondulado simulado con elipses solapadas
    for(int i = -3; i <= 3; i++){
        fillellipse(cx + i*(int)(40*escala), y + h2/2,
                    (int)(32*escala), h2/2 + (i%2==0 ? (int)(6*escala):0));
    }
    y += h2 + gap;

    // ----- TOMATE -----
    setfillstyle(SOLID_FILL, 4);         // rojo
    setcolor(DARKGRAY);
    bar(cx - w + (int)(10*escala), y, cx + w - (int)(10*escala), y + h3);
    // venas del tomate
    setcolor(12);
    for(int i = -1; i <= 1; i++){
        line(cx + i*(int)(60*escala), y,
             cx + i*(int)(50*escala), y + h3);
    }
    y += h3 + gap;

    // ----- CARNE -----
    setfillstyle(SOLID_FILL, 6);         // cafe/marron
    setcolor(DARKGRAY);
    bar(cx - w, y, cx + w, y + h4);
    // textura de carne asada
    setcolor(BROWN);
    for(int i = 0; i < 5; i++){
        line(cx - w + i*(int)(50*escala), y + (int)(5*escala),
             cx - w + i*(int)(50*escala) + (int)(20*escala), y + h4 - (int)(5*escala));
    }
    y += h4 + gap;

    // ----- QUESO -----
    setfillstyle(SOLID_FILL, 14);        // amarillo
    setcolor(YELLOW);
    // el queso "derramado" sobresale un poco
    int qover = (int)(12*escala);
    bar(cx - w - qover, y, cx + w + qover, y + h5);
    y += h5 + gap;

    // ----- PAN INFERIOR -----
    setfillstyle(SOLID_FILL, 6);
    setcolor(DARKGRAY);
    bar(cx - w, y, cx + w, y + h6 - (int)(8*escala));
    fillellipse(cx, y + h6 - (int)(8*escala), w, (int)(10*escala));
}

// Texto centrado en x
void textoCentrado(int x, int y, const char *texto){
    int tw = textwidth((char*)texto);
    outtextxy(x - tw/2, y, (char*)texto);
}

void animacionHamburguesa(){
    // Abrir ventana grafica
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int W = getmaxx();
    int H = getmaxy();
    int cx = W/2;
    int cy = H/2 - 30;

    // ---- FASE 1: Entrada desde arriba (caida) ----
    for(int frame = 0; frame < 40; frame++){
        cleardevice();

        // Fondo degradado simulado con barras
        for(int y = 0; y < H; y++){
            int r = 255 - y*80/H;
            // BGI no tiene color custom; usar patron alternado oscuro/claro
            if(y%2==0) setcolor(DARKGRAY); else setcolor(BLACK);
            line(0,y,W,y);
        }

        // Calculo de posicion: cae desde arriba
        float t  = frame / 39.0f;
        float cy_anim = -120 + (cy + 120) * t;  // interpolacion lineal
        float esc = 0.4f + 0.6f * t;            // crece de 0.4 a 1.0

        dibujarHamburguesa(cx, (int)cy_anim, esc);

        // Titulo
        setcolor(WHITE);
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        textoCentrado(cx, 20, "MAC BURGUER");

        delay(25);
    }

    // ---- FASE 2: Rebote ----
    for(int bounce = 0; bounce < 3; bounce++){
        // bajar un poco
        for(int f = 0; f < 8; f++){
            cleardevice();
            for(int y=0;y<H;y++){if(y%2==0)setcolor(DARKGRAY);else setcolor(BLACK);line(0,y,W,y);}
            dibujarHamburguesa(cx, cy + (int)(18*(f/7.0f)), 1.0f);
            setcolor(WHITE); settextstyle(BOLD_FONT,HORIZ_DIR,3);
            textoCentrado(cx,20,"MAC BURGUER");
            delay(18);
        }
        // subir
        for(int f = 8; f >= 0; f--){
            cleardevice();
            for(int y=0;y<H;y++){if(y%2==0)setcolor(DARKGRAY);else setcolor(BLACK);line(0,y,W,y);}
            dibujarHamburguesa(cx, cy + (int)(18*(f/7.0f)), 1.0f);
            setcolor(WHITE); settextstyle(BOLD_FONT,HORIZ_DIR,3);
            textoCentrado(cx,20,"MAC BURGUER");
            delay(18);
        }
    }

    // ---- FASE 3: Mostrar mensaje final ----
    for(int frame = 0; frame < 60; frame++){
        cleardevice();
        for(int y=0;y<H;y++){if(y%2==0)setcolor(DARKGRAY);else setcolor(BLACK);line(0,y,W,y);}

        dibujarHamburguesa(cx, cy, 1.0f);

        setcolor(WHITE);
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        textoCentrado(cx, 20, "MAC BURGUER");

        // Texto parpadeante
        if((frame/10)%2==0){
            setcolor(YELLOW);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            textoCentrado(cx, H - 60, "Presiona cualquier tecla para continuar...");
        }

        // Etiquetas de capas (aparecen gradualmente)
        if(frame > 15){
            setcolor(LIGHTCYAN);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
            outtextxy(cx + 150, cy - 100, (char*)"Pan de sesamo");
            outtextxy(cx + 150, cy - 55,  (char*)"Lechuga fresca");
            outtextxy(cx + 150, cy - 20,  (char*)"Tomate");
            outtextxy(cx + 150, cy + 20,  (char*)"Carne a la parrilla");
            outtextxy(cx + 150, cy + 55,  (char*)"Queso americano");
            outtextxy(cx + 150, cy + 85,  (char*)"Pan inferior");
        }

        delay(40);
        if(kbhit()){ getch(); break; }
    }

    // ---- FASE 4: Disolucion (escala hacia arriba) ----
    for(int frame = 0; frame < 20; frame++){
        cleardevice();
        for(int y=0;y<H;y++){if(y%2==0)setcolor(DARKGRAY);else setcolor(BLACK);line(0,y,W,y);}
        float esc = 1.0f + frame * 0.08f;
        dibujarHamburguesa(cx, cy, esc > 1.6f ? 1.6f : esc);
        delay(20);
    }

    closegraph();
}

// ============================================================
//  ===  MENU PRINCIPAL  ===
// ============================================================

void menuPrincipal(){
    int opcion;
    bool corriendo = true;

    while(corriendo){
        system("cls");
        printf("\n");
        printf("  ==========================================\n");
        printf("   __  __    _    ____     ____             \n");
        printf("  |  \\/  |  / \\  / ___|   | __ ) _   _ _ __ \n");
        printf("  | |\\/| | / _ \\| |       |  _ \\| | | | '__|\n");
        printf("  | |  | |/ ___ \\ |___    | |_) | |_| | |   \n");
        printf("  |_|  |_/_/   \\_\\____|   |____/ \\__,_|_|   \n");
        printf("  ==========================================\n");
        printf("         SISTEMA INTEGRAL MAC BURGUER\n");
        printf("  ==========================================\n\n");
        printf("  1. Ventas / Menu de productos\n");
        printf("  2. Promociones del dia\n");
        printf("  3. Auto Burguer (paquetes)\n");
        printf("  4. Reporte de ventas 2 semanas\n");
        printf("  5. Modificar archivo binario\n");
        printf("  6. Gestion de personal\n");
        printf("  7. GRAFICAR (animacion de hamburguesa)\n");
        printf("  8. Salir\n");
        printf("\n  Opcion: ");
        opcion = validacion(1, 8);

        switch(opcion){
        case 1: moduloVentas();           break;
        case 2: moduloPromociones();      break;
        case 3: moduloAutoBurguer();      break;
        case 4: moduloVentasSemanas();    break;
        case 5: moduloModificaBinary();   break;
        case 6: submenuPersonal();        break;
        case 7:
            printf("\nAbriendo ventana de animacion...\n");
            animacionHamburguesa();
            break;
        case 8:
            corriendo = false;
            break;
        }
    }
    printf("\n  Hasta luego! Gracias por usar MAC Burguer.\n");
}

// ============================================================
//  ===  MAIN  ===
// ============================================================

int main(){
    srand((unsigned)time(NULL));

    // Cargar datos persistentes
    cargarProductos();
    cargarPromociones();
    cargarEmpleados();
    cargarClientes();
    cargarProveedores();

    menuPrincipal();
    return 0;
}