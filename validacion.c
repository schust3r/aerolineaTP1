/* 
 * File:   lectura.c
 * Author: Joel
 * Created on 12 de marzo de 2016, 09:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "colores.h"

/**
 * Funcion para validar si los asientos son todos de una misma clase
 * en cada fila, y ademas que todas las filas de la misma categoria
 * tengan igual cantidad de asientos.
 * 
 * @param cols
 * @param asientos
 * @param num_asientos
 * Salidas: entero que valida si las filas son correctas.
 * Restricciones: array de asientos, filas y columnas deben ser validas y
 *                congruentes.
 */
int validarFilasAsientos(int filas, int cols, char *asientos[]) {
    
    // Arrays de caracteres para manipular datos
    char cat[16];
    
    /* Contadores y temporales para verificar que todas las 
     * categorias tengan el mismo numero de asientos */
    int cant_B = 0;
    int temp_B = 0;
    int tengo_B = 0;
    
    int cant_S = 0;
    int temp_S = 0;
    int tengo_S = 0;
    
    int cant_E = 0;
    int temp_E = 0;
    int tengo_E = 0;
    
    int as_validos = 1;
    
    // Array para guardar la clase del asiento anterior contiguo
    char cat_anterior;
    
    for (int i = 0; i < filas; i++) 
    {
        
        if (cat_anterior == 'B') {
            
            if (tengo_B == 1) {
                if (cant_B != temp_B) { as_validos = 0; }
            }
            
            tengo_B = 1;
        }
        if (cat_anterior == 'S') {
            if (tengo_S == 1) {
                if (cant_S != temp_S) { as_validos = 0; }
            }
            tengo_S = 1;
        }
        if (cat_anterior == 'E') {
            if (tengo_E == 1) {
                if (cant_E != temp_E) { as_validos = 0; }
            }
            tengo_E = 1;
        }
        
        for (int j = 0; j < cols; j++) 
        {
            /* Almacena los strings del arreglo en arrays temporales */
            strcpy(cat, *(asientos + i*cols + j));
            
            if (j == 0) {
                cat_anterior = cat[0];
            }

            if   (cat[0] == 'B') {
                if (tengo_B == 0) 
                {
                    cant_B++;
                }
                else 
                {
                    temp_B++;
                }
                
            } if (cat[0] == 'S') {
                if (tengo_S == 0) 
                {
                    cant_S++;
                }
                else 
                {
                    temp_S++;
                }                
                
                
            } if (cat[0] == 'E') {
                if (tengo_E == 0) 
                {
                    cant_E++;
                }
                else 
                {
                    temp_E++;
                }                
            }
        }
    }            
    
    for (int i = 0; i < filas; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            /* Almacena los strings del arreglo en arrays temporales */
            strcpy(cat, *(asientos + i*cols + j));
            
            if (j == 0) {
                cat_anterior = cat[0];
            }
            
            if   (tengo_B != 0) {
                
            } if (tengo_S != 0) {
                
            }
            
            
            if (strcmp(cat, "NULL") != 0 && cat[0] != cat_anterior)
            {
                as_validos = 0;
                break;
            }
            
        }
    }        
    
    if (as_validos == 1)
    {
        printf("\n");
        printf(ANSI_COLOR_GREEN " ** La distribución de asientos es válida ** " 
               ANSI_COLOR_RESET);
        printf("\n");       
        return 0;
    }
    else 
    {
        printf("\n");
        printf(ANSI_COLOR_RED " ** La distribución de asientos no es válida ** " 
               ANSI_COLOR_RESET);
        printf("\n");           
        return 1;
    }
}
