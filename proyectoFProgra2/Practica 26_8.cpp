#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_DIAS     8
#define NUM_PAQUETES 8

static const char *DIAS[NUM_DIAS] = {
    "lun", "mar", "mier", "jue",
    "vie", "sab", "dom", "fes"
};


typedef struct {
    char   *nombre;
    double  precio_base;
    int     ventas[NUM_DIAS];
} Paquete;

typedef struct {
    Paquete *paquetes;
    int     *descuentos;
    int      n;
} Menu;


Menu *menu_crear(int n) {
    Menu *m = (Menu*)malloc(sizeof(Menu));
    if (!m) return NULL;

    m->n          = n;
    m->paquetes   = (Paquete *)calloc(n,        sizeof(Paquete));
    m->descuentos = (int *)calloc(NUM_DIAS, sizeof(int));

    if (!m->paquetes || !m->descuentos) {
        free(m->paquetes);
        free(m->descuentos);
        free(m);
        return NULL;
    }
    return m;
}


void menu_destruir(Menu *m) {
    if (!m) return;
    for (int i = 0; i < m->n; i++)
        free(m->paquetes[i].nombre);
    free(m->paquetes);
    free(m->descuentos);
    free(m);
}


int menu_agregar(Menu *m, int idx,
                  const char *nombre, double precio) {
    if (!m || idx < 0 || idx >= m->n) return -1;

    m->paquetes[idx].nombre = (char *)malloc(strlen(nombre) + 1);
    if (!m->paquetes[idx].nombre) return -1;

    strcpy(m->paquetes[idx].nombre, nombre);
    m->paquetes[idx].precio_base = precio;
    memset(m->paquetes[idx].ventas, 0,
           sizeof(m->paquetes[idx].ventas));
    return 0;
}


double precio_con_descuento(const Menu *m,
                             int idx_paq, int dia) {
    double base = m->paquetes[idx_paq].precio_base;
    int    desc = m->descuentos[dia];
    return base * (1.0 - desc / 100.0);
}


void menu_imprimir(const Menu *m) {
    printf("%-36s", "Paquete");
    for (int d = 0; d < NUM_DIAS; d++)
        printf("%7s", DIAS[d]);
    printf("\n");

    for (int i = 0; i < m->n; i++) {
        printf("%-36s", m->paquetes[i].nombre);
        for (int d = 0; d < NUM_DIAS; d++)
            printf("%7.2f",
                precio_con_descuento(m, i, d));
        printf("\n");
    }

    printf("%-36s", "Descuento por dia");
    for (int d = 0; d < NUM_DIAS; d++)
        printf("%6d%%", m->descuentos[d]);
    printf("\n");
}


int main(void) {
    Menu *m = menu_crear(NUM_PAQUETES);
    if (!m) { perror("malloc"); return 1; }

    int desc[NUM_DIAS] = { 10, 15, 12, 10, 20, 5, 5, 0 };
    memcpy(m->descuentos, desc, NUM_DIAS * sizeof(int));

    menu_agregar(m, 0, "Hamburguesa con queso",        89.0);
    menu_agregar(m, 1, "Combo parejas",                159.0);
    menu_agregar(m, 2, "Combo Whopper con cono",        139.0);
    menu_agregar(m, 3, "Combo clasic Crispy King+cono", 149.0);
    menu_agregar(m, 4, "Combo Whopper con cono+papas",  169.0);
    menu_agregar(m, 5, "Auto King 3 hamburguesas",      199.0);
    menu_agregar(m, 6, "Long rodeo (hamburguesa grande)",129.0);
    menu_agregar(m, 7, "Nuggets 9 piezas + papas",      119.0);

    menu_imprimir(m);

    printf("\nWhopper el jueves (20%% off): $%.2f MXN\n",
           precio_con_descuento(m, 2, 4));

    menu_destruir(m);
    return 0;
}
