#include <string.h>
#include <stdlib>
#include <iostream>
#include <string.h>

using namespace std;

struct Persona{
	
    char nombre[20];
	char direccion[20];
	int telefono;

};

struct Empleado {
	
	struct Persona emplePer;
	int edad;
	int sueldoDiario;
	int sueldoMensual = sueldoDiario*20
	char area[20];
	char puesto[20];
	void guardarInfo(){
		
		int opcionArea = 0;
		int opcionPuesto = 0;
		
		printf("\nIndique el Area de trabajo eligiendo una opcion del 1-3:");
		printf("\n1.- Area de cocina");
		printf("\n2.- Area de Servicio y ventas");
		printf("\n3.- Area de Lavaloza");
		scanf("%d",&opcionArea);
		switch (opcionArea){
			case 1:
				printf("\nSeleccione su rol del 1-4: ");
				printf("\n1.- Encargado de cocina (Chef)");
				printf("\n2.- Parrillero");
				printf("\n3.- Ayudante de cocina");
				printf("\n4.- Lavaloza");
				scanf("%d",&opcionPuesto);
				switch (opcionPuesto){
					case 1:
						puesto = "Chef";
						area = "Cocina";
						break;
					case 2:
						puesto = "Parrillero";
						area = "Cocina";
						break;
					case 3:
						puesto = "Ayudante de cocina";
						area = "Cocina";
						break;
					case 4:
						puesto = "Lavaloza";
						area = "Cocina";
						break;
					default:
				 		printf("Indique una opcion valida por favor");	
						break;
				}
	   			
				break;
			case 2: 
		        printf("\nSeleccione su rol del 1-4: ");
				printf("\n1.- Cajero");
				printf("\n2.- Mesero");
				printf("\n3.- Hostess");
				printf("\n4.- Repartidor");
				scanf("%d",&opcionPuesto);
				switch (opcionPuesto){
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					default:
						printf("Indique una opcion valida por favor");
						break;
				}
		        break;
   			case 3:
   				printf("\nSeleccione su rol del 1-2: ");
				printf("\n1.- Gerente de sucursal");
				printf("\n2.- Personal de limpieza");
				scanf("%d",&opcionPuesto);
				switch (opcionPuesto){
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					default:
						printf("Indique una opcion valida por favor");
						break;
				}
			    break;
			default:
				"Ingrese una opcion valida por favor"
				break;	
		}
	}
};

struct Cliente {
	
	struct Persona clienPer;
	int puntos = 0;
	
};

struct Proveedor {
	
	char nombre[20];
	struct Persona provePer;
	
};
