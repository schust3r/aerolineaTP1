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
 * Funcion para reservar asientos, uno a uno, 
 * 
 * @param cols
 * @param asientos
 * @param num_asientos
 * Salidas: valor entero no utilizado
 * Restricciones: array de asientos y columnas deben ser validas y
 *                congruentes, todos los asientos elegidos deben estar libres.
 */
int reservarAsientos(int cols, char *asientos[], int num_asientos) {

    printf("\n");
    printf(ANSI_COLOR_BLUE " ** Sistema de reservaciones ** "
           ANSI_COLOR_RESET);
    printf("\n");
    
    char asiento[2];
    char val[16];
    
    // Almacena los espacios reservados hasta comprobar que todos sean validos
    char reservados[num_asientos * 2];
    
    // Bandera para comprobar que todos los asientos esten libres
    int valido = 1;

    /* Generar codigo de reserva random */
    int i;
    for (i = 0; i < num_asientos * 2; i += 2)
    {
        printf("Ingrese el identificador del asiento deseado: ");
        scanf("%s", &asiento);
        
        int fila = asiento[0] - '1';
        int col = asiento[1] - 'A';

        strcpy(val, *(asientos + fila*cols + col));
        
        if (val[1] != 'L')
        {
            printf("Error. Se ha encontrado un asiento ocupado.\n");
            valido = 0;
            break;
        }
        reservados[i] = fila + '0';
        reservados[i + 1] = col + '0';
    }
    
    /* Ejecuta este bloque if si todos los asientos estan libres */

    int tam_buffer = 16;
    char temp_res[16] = "XO:R_XXX";
    gen_random(&temp_res);
    
    if (valido == 1) {

        for (i = 0; i < num_asientos * 2; i += 2)
        {
            char* ind_reserva = malloc(tam_buffer);

            
            /* Leer fila y columna a cambiar en la matriz */
            int fila = reservados[i] - '0';
            int col  = reservados[i + 1] - '0';
            
            temp_res[0] = *(asientos + fila*cols + col)[0];
            
            strncpy(ind_reserva, temp_res, tam_buffer);
            
            /* Muestra el valor */
            *(asientos + fila*cols + col) = ind_reserva; 
        }
        printf("\n");
        printf(ANSI_COLOR_GREEN " ** Su reservación ha sido exitosa ** "
               ANSI_COLOR_RESET);
        printf("\n");
    }
    else {
        printf("\n");
        printf(ANSI_COLOR_RED " ** Su reservación ha fracasado ** "
               ANSI_COLOR_RESET);
        printf("\n");
    }
    return 0;
}

/**
 * Cancelar la reserva a partir de un identificador dado por el usuario
 * para todos los asientos con ese id.
 * 
 * @param filas
 * @param cols
 * @param asientos
 * @param id - identificador de asiento(s) a cancelar
 * @return valor entero
 * Restricciones: array de asientos y columnas deben ser validas y
 *                congruentes, todos los asientos elegidos deben estar libres.
 */
int cancelarReserva(int filas, int cols, char *asientos[], char id[]) {
    
    // Arrays de caracteres para manipular datos
    char cat[16];
    char val[16];
    
    // Indicador para marcar si se generan cambios
    int cambioEfectuado = 0;
    
    for (int i = 0; i < filas; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            /* Almacena los strings del arreglo en arrays temporales */
            strcpy(cat, *(asientos + i*cols + j));
            strcpy(val, *(asientos + i*cols + j));
            
            if (strlen(val) > 2) 
            {                
                memmove(val, val + 3, strlen(val + 1) + 3);
                
                /* Compara si el identificador dado por el usuario
                 * y el identificador de la posicion son iguales */
                if (strcmp(id, val) == 0) 
                {
                    // Indica que se ha realizado un cambio
                    cambioEfectuado = 1;
                    
                    // Verificar la clase (B, S o E)
                    switch (cat[0]) 
                    {
                        case 'B':
                            *(asientos + i*cols + j) = "BL";
                            break;

                        case 'S':
                            *(asientos + i*cols + j) = "SL";
                            break;

                        case 'E':
                            *(asientos + i*cols + j) = "EL";
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }        
    
    if (cambioEfectuado == 1)
    {
        printf("\n");
        printf(ANSI_COLOR_GREEN " ** Se han cancelado las reservaciones ** " 
               ANSI_COLOR_RESET);
        printf("\n");       
    }
    else 
    {
        printf("\n");
        printf(ANSI_COLOR_RED " ** No se han realizado cambios ** "
               ANSI_COLOR_RESET);
        printf("\n");           
    }
    return 0;
}

/**
 * Mostrar informacion de la reserva para un identificador dado por el
 * usuario.
 * 
 * @param filas
 * @param cols
 * @param asientos
 * @param id - el identificador de reserva del usuario
 * @return valor entero
 * Restricciones: array de asientos y columnas deben ser validas y
 *                congruentes, todos los asientos elegidos deben estar libres.
 */
int mostrarInfoReserva(int filas, int cols, char *asientos[], char id[]) {
    
    printf("\n");         
    printf(ANSI_COLOR_RED " == Lista de reservaciones == "
           ANSI_COLOR_RESET);
    printf("\n");       
    printf("%-15s | Asiento\n", "Clase");
     
    // Arrays de caracteres para manipular datos
    char cat[16];
    char val[16];
    
    for (int i = 0; i < filas; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            /* Almacena los strings del arreglo en arrays temporales */
            strcpy(cat, *(asientos + i*cols + j));
            strcpy(val, *(asientos + i*cols + j));
            
            if (strlen(val) > 2) 
            {                
                memmove(val, val + 3, strlen(val + 1) + 3);
                
                /* Compara si el identificador dado por el usuario
                 * y el identificador de la posicion son iguales */
                if (strcmp(id, val) == 0) 
                {
                    // Verificar la clase (B, S o E)
                    switch (cat[0]) 
                    {
                        case 'B':
                            printf(" %-15s |  %d%c\n", "Business", 
                                    i + 1, j + 'A');
                            break;

                        case 'S':
                            printf(" %-15s |  %d%c\n", "Premium Economy", 
                                    i + 1, j + 'A');
                            break;

                        case 'E':
                            printf(" %-15s |  %d%c", "Economy", 
                                    i + 1, j + 'A');
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }        
    printf("\n");
    printf(ANSI_COLOR_RED " ============================ "
           ANSI_COLOR_RESET);
    printf("\n");           
    return 0;
}

/**
 * 
 * @param s
 */
void gen_random(char *s) {
    static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 5; i < 8; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
}

/**
 * Muestra informacion sobre la disponibilidad de asientos de una categoria
 * elegida por el usuario, de forma tabular
 * 
 * @param filas
 * @param cols
 * @param asientos
 * @param cat
 * Salidas: valor entero, consola
* Restricciones: array de asientos y columnas deben ser validas y
 *                congruentes, todos los asientos elegidos deben estar libres.
 */
int mostrarAsientosDispCategoria(int filas, int cols, char *asientos[], char cat) {
    
    char val[16];
    printf(ANSI_COLOR_BLUE "================================" ANSI_COLOR_RESET);
    printf("\nLa categoría seleccionada es: %c", cat);
    
    // Imprimir cambio de linea y tabulacion
    printf("\n\t");
    for (char c = 'A'; c < 'A' + cols; c++ ) 
    {
        printf(ANSI_COLOR_RED "%-12c" ANSI_COLOR_RESET, c);
    }
    
    for (int i = 0; i < filas; i++) 
    {
        
        printf("\n");
        printf(ANSI_COLOR_BLUE " %-2d " ANSI_COLOR_RESET, i + 1);
        
        for (int j = 0; j < cols; j++) 
        {
            strcpy(val, *(asientos + i*cols + j));
            
            if (val[0] == cat && strlen(val) == 2) {
                printf( "| %-9s ", "Libre");
            }
            else 
            {
                printf( "| %-9s ", "--");
            }
        }
    }        
    printf("\n");
    printf(ANSI_COLOR_BLUE "================================" ANSI_COLOR_RESET);
    return 0;
}
