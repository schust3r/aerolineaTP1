/* 
 * File:   main.c
 * Author: Joel
 *
 * Created on 12 de marzo de 2016, 09:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "lectura.h"
#include "informacion.h"
#include "reservacion.h"
#include "colores.h"
#include "validacion.h"

// Array para almacenar directorio del archivo txt
char dir[256];

// Structs de informacion de vuelo
Cabecera cabecera;

// Dimensiones de vuelo y disposicion de los asientos
Vuelo vuelo; 
char asientos[16];

/*
 * Funcion main del programa
 */
int main(int argc, char** argv) {
    cargarDatos();
    mostrarInformacion();
    menu();
    return (EXIT_SUCCESS);
}

/**
 * Menu principal del programa
 * Recursivo hasta que el usuario seleccione el caracter de salida
 * Restricciones: se debe ingresar un caracter valido
 */
int menu() {

    // Definir el caracter para opcion y control de menu
    char op;

    // Imprime todas las opciones de menu
    printf("\n\n");
    printf(ANSI_COLOR_BLUE " *** Menú de opciones *** " ANSI_COLOR_RESET);
    printf("\n");

    printf(" a. Reservar asientos \n");
    printf(" b. Cancelar reserva \n");
    printf(" c. Mostrar información de reserva \n");
    printf(" d. Mostrar asientos disponibles por categoría \n");
    printf(" e. Mostrar ocupación \n");
    printf(" f. Mostrar estadísticas \n");
    printf(" g. Empezar de nuevo \n");
    printf(" x. Salir del programa \n\n");

    // Leer el caracter de opcion
    printf("%s", " Digite el caracter de su opción: ");

    // Obtener char de opcion (aplicando limpieza de búfer)
    clearBuffer(op);
    op = getchar();

    if (  op == 'a') {
        // Leer el caracter de opcion
        printf(" Digite la cantidad de asientos a reservar: ");

        // Caracter para almacenar categoria
        int cant;
        
        // Obtener char de categoria (aplicando limpieza de búfer)
        scanf("%d", &cant);
        
        reservarAsientos(vuelo.columnas, &asientos, cant);

    } if (op == 'b') {
        printf(" Digite el identificador de su reserva: ");

        // Caracter para almacenar categoria
        char id_res[8];
        
        // Obtener identificador de reserva
        scanf("%s", id_res);
        
        // Verificar si el string ingresado no es vacio
        cancelarReserva(vuelo.filas, vuelo.columnas, &asientos, id_res);       
       

    } if (op == 'c') {
        printf(" Digite el identificador de su reserva: ");

        // Caracter para almacenar categoria
        char id_res[8];
        
        // Obtener identificador de reserva
        scanf("%s", id_res);
        
        // Verificar si el string ingresado no es vacio
        mostrarInfoReserva(vuelo.filas, vuelo.columnas, &asientos, id_res);
       

    } if (op == 'd') {
        // Leer el caracter de opcion
        printf(" Digite el caracter de la categoría (B, S o E): ");

        // Caracter para almacenar categoria
        char cat;
        
        // Obtener char de categoria (aplicando limpieza de búfer)
        clearBuffer(cat);
        cat = getchar();
        
        mostrarAsientosDispCategoria(vuelo.filas, vuelo.columnas, &asientos, cat);

    } if (op == 'e') {
        mostrarOcupacion(vuelo.filas, vuelo.columnas, &asientos);

    } if (op == 'f') {
        mostrarInformacion();

    } if (op == 'g') {
        cargarDatos();
        mostrarInformacion();
        
    } if (op != 'x') {
        menu();
    }
}

/**
 * Limpiar retorno de carrete y caracter de nueva linea
 * para evitar duplicado de menu durante ciclo while
 * @param c - char leido
 * Sin salidas, ni restricciones
 */
void clearBuffer(char c) {
    while(c != '\n') 
    {
        scanf("%c", &c);
    }
}

/**
 * Recopilacion de funciones que muestran informacion
 * Mas detalles en la implementacion de cada una
 */
int mostrarInformacion() {
    mostrarInfoVuelo(&cabecera);
    mostrarCantidadAsientos(vuelo.filas, vuelo.columnas, &asientos);
    mostrarFilasColumnas(vuelo.filas, vuelo.columnas);
    mostrarRangosColumnas(vuelo.filas, vuelo.columnas, &asientos);
    obtenerAsientosLibresCategoria(vuelo.filas, vuelo.columnas, &asientos);
    return 0;
}

/**
 * Leer direccion, cargar cabecera del texto y cargar asientos
 * Valida que las categorias de asientos no esten mezcladas
 * Mas detalles en la implementacion de cada una
 */
int cargarDatos() {
    seleccionarDir(dir);
    cargarCabecera(dir, &cabecera);
    cargarAsientos(dir, asientos, &vuelo);
    
    // funcion retorna 0 si los asientos son validos
    if (validarFilasAsientos(vuelo.filas, vuelo.columnas, &asientos) != 0)
    {
        cargarDatos();
    }
    
    return 0;
}


