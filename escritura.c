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
#include "colores.h"

int escribirEnTxt(int filas, int cols, Cabecera *cab, char *asientos[], char dir[]) {
    
    int exito = 0;
    
    FILE *archivo = fopen(dir, "w");
    
    if (archivo == NULL)
    {
        printf("\n");
        printf(ANSI_COLOR_RED " ** Error al guardar en archivo ** " 
               ANSI_COLOR_RESET);
        printf("\n");
        exito = 1;
    }

    /* Escribir cabecera */
    fprintf(archivo, "Origen:%s,Destino:%s,Avion:%s,Salida:%s,Llegada:%s", 
            cab->origen,
            cab->destino,
            cab->avion,
            cab->fec_salida,
            cab->fec_llegada);

    /* Guarda los asientos */
    char val[16];
    char check_null[16];
    
    for (int i = 0; i < filas; i++) 
    {
        
        fprintf(archivo, "\r\n");
        
        for (int j = 0; j < cols; j++) 
        {
            /* Almacena los strings del arreglo en arrays temporales */
            strcpy(val, *(asientos + i*cols + j));
            
            if (i != filas - 1 && j != cols - 1) {
                strcpy(check_null, *(asientos + i*cols + j + 1));
            }
            
            if (strcmp(val, "NULL") != 0) 
            {                
                if (j != cols - 1 && strcmp(check_null, "NULL") != 0) 
                {
                    fprintf(archivo, "%s,", val);
                }
                else 
                {
                    fprintf(archivo, "%s", val);
                }
            }
            
        }
    }            
    
    if (exito == 0) 
    {
        printf("\n");
        printf(ANSI_COLOR_GREEN " ** Éxito al guardar los cambios ** " 
               ANSI_COLOR_RESET);
        printf("\n");
    }
    
    fclose(archivo);    
    return 0;
}