/* 
 * File:   lectura.c
 * Created on 12 de marzo de 2016, 09:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "colores.h"

/**
 * Muestra informacion de origen, destino, avion, salida y llegada de un
 * vuelo
 * 
 * @param cab - cabecera de vuelo
 * Restricciones: cabecera debe estar correctamente formada.
 */
int mostrarInfoVuelo(Cabecera *cab) {
    
    printf("\n");
    printf(ANSI_COLOR_RED "----- Información de vuelo -----" ANSI_COLOR_RESET);
    printf("\n");
    printf("| Origen  | %s\n", (*cab).origen);
    printf("| Destino | %s\n", (*cab).destino);
    printf("| Avión   | %s\n", (*cab).avion);
    printf("| Salida  | %s\n", (*cab).fec_salida);
    printf("| Llegada | %s\n", (*cab).fec_llegada);
    printf(ANSI_COLOR_RED "--------------------------------" ANSI_COLOR_RESET);
    
    return 0;
}

/**
 * Muestra en forma tabular como estan organizados los asientos del vuelo
 * 
 * @param vuelo, fila, columna
 * Restricciones: array, filas y columnas correctas.
 */
int mostrarOcupacion(int fila, int columna, char *asiento[]) {
      
    // Imprimir cambio de linea y tabulacion
    printf("\n\t");
    for (char c = 'A'; c < 'A' + columna; c++ ) 
    {
        printf(ANSI_COLOR_RED "%-12c" ANSI_COLOR_RESET, c);
    }
    
    for (int i = 0; i < fila; i++) 
    {
        printf("\n");
        printf(ANSI_COLOR_BLUE " %-2d " ANSI_COLOR_RESET, i + 1);
        for (int j = 0; j < columna; j++) 
        {
            printf( "| %-9s ", *(asiento + i*columna + j) );
        }
    }        
    return 0;
}

/**
 * Muestra la cantidad de asientos (suma total) y omite espacios con NULL.
 * 
 * @param fila
 * @param columna
 * @param asiento
 * @return entero, consola
 * Restricciones: array, filas y columnas deben ser correctos.
 */
int mostrarCantidadAsientos(int fila, int columna, char *asiento[]) {
    
    char val[16];
    int contador = 0;
    
    for (int i = 0; i < fila; i++) 
    {
        for (int j = 0; j < columna; j++) 
        {
            strcpy(val, *(asiento + i*columna + j));
            if ( strcmp(val, "NULL") ) 
            {
                ++contador;
            }
        }
    }         
    printf("\n\nLa cantidad total de asientos es de: %d\n", contador);
    return 0;
}

/**
 * Imprime filas y columnas de forma estilizada y agradable
 * 
 * @param filas
 * @param columnas
 * Restricciones: ninguna
 */
int mostrarFilasColumnas(int filas, int columnas) {
    printf("\n");
    printf(ANSI_COLOR_RED "-----------------------------" ANSI_COLOR_RESET);
    printf("\n| Filas de asientos    | %-2d |\n", filas);
    printf("| Columnas de asientos | %-2d |\n", columnas);
    printf(ANSI_COLOR_RED "-----------------------------" ANSI_COLOR_RESET);
    return 0;
}

/**
 * Muestra categoria de asientos por rango
 * 
 * @param fila
 * @param columna
 * @param asiento
 * @return int
 * Restricciones: array, filas y columnas deben ser correctos.
 */
int mostrarRangosColumnas(int fila, int columna, char *asiento[]) {
    
    char val[16];
    int j = 0;
    
    printf("\n\n");
    printf(ANSI_COLOR_BLUE " | %-16s | Rango fila" ANSI_COLOR_RESET, "Clase");
    printf("\n");
    
    for (int i = 0; i < fila; i++) 
    {
        strcpy(val, *(asiento + i*columna));
        
        while (j < columna) 
        {
            if (*(asiento + i*columna + j)[0] != val[0])
            {
                break;
            }
            j++;
        }
        
        switch (val[0]) 
        {
            case 'B':
                printf(" | %-16s | %d%c - %d%c\n", 
                        "Business", i + 1, 'A', i + 1, 'A' + j - 1);
                break;

            case 'S':
                printf(" | %-16s | %d%c - %d%c\n", 
                        "Premium Economy", i + 1, 'A', i + 1, 'A' + j - 1);
                break;

            case 'E':
                printf(" | %-16s | %d%c - %d%c\n", 
                        "Economy", i + 1, 'A', i + 1, 'A' + j - 1);
                break;
        }
        j = 0;
    }         
    return 0;
}

/**
 * Obtiene la cantidad de asientos que estan ocupados o libres por categoria
 * 
 * @param fila
 * @param columna
 * @param asiento
 * Restricciones: array, filas y columnas deben ser correctos.
 */
int obtenerAsientosLibresCategoria(int fila, int columna, char *asiento[]) {
    
    /* Char array para almacenamiento temporal de strings */
    char val[16];
    
    /* Contadores para los asientos ocupados por clase */
    int b_ocup = 0;
    int s_ocup = 0;
    int e_ocup = 0;
    
    /* Contadores para los asientos libres por clase */
    int b_libre = 0;
    int s_libre = 0;
    int e_libre = 0;
    
    /* Imprimir la cabecera de la tabla*/
    printf("\n");
    printf(ANSI_COLOR_BLUE " | %-16s | %-10s | Disponibles" ANSI_COLOR_RESET, 
            "Clase", "Ocupados");
    printf("\n");      
    
    /* Escanear el arreglo de asientos para contar cantidad de Bs, Ss, Es */
    for (int i = 0; i < fila; i++) 
    {
        for (int j = 0; j < columna; j++) 
        {
            strcpy(val, *(asiento + i*columna + j));
            if ( strcmp(val, "NULL") ) 
            {
                if (strlen(val) != 2 ) 
                {
                    switch (val[0]) 
                    {
                        case 'B':
                            b_ocup++;
                            break;
                        case 'S':
                            s_ocup++;
                            break;
                        case 'E':
                            e_ocup++;
                            break;
                    }
                }
                else 
                {
                    switch (val[0]) 
                    {
                        case 'B':
                            b_libre++;
                            break;
                        case 'S':
                            s_libre++;
                            break;
                        case 'E':
                            e_libre++;
                            break;
                    }    
                }
            }
        }
    }

    /* Mostrar asientos disponibles por categoria */
    printf(" | %-16s | %-10d | %d \n", "Business", b_ocup, b_libre);
    printf(" | %-16s | %-10d | %d \n", "Premium Economy", s_ocup, s_libre);
    printf(" | %-16s | %-10d | %d \n", "Economy", e_ocup, e_libre);
    
    return 0;
}

