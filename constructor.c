/* 
 * File:   lectura.c
 * Created on 12 de marzo de 2016, 09:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Construye una matriz con tamano suficiente para almacenar todos
 * los strings identificadores de los asientos
 * 
 * @param filas
 * @param cols
 * @param arr
 * @return int
 * Restricciones: ninguna, filas y columnas deben ser positivas
 */
int construirMatriz(int filas, int cols, char *arr[]) 
{
    arr = (char *)malloc(filas * cols * 16);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            *(arr + i*cols + j) = "NULL";
        }
    }    
    return 0;
}

/**
 * Carga la matriz con los valores respectivos de asientos por posicion,
 * de acuerdo con el archivo de texto.
 * 
 * @param filas
 * @param cols
 * @param arr
 * @param dir
 * @return int
 * Restricciones: direccion debe ser valida
 */
int cargarMatriz(int filas, int cols, char *arr[], char dir[]) {
      
    construirMatriz(filas, cols, arr);
    
    // Array para almacenar las lineas de texto temporalmente
    char *buffer = NULL;
    size_t tamano = 0;
    
    // Definir FILE para cargar a partir de directorio
    FILE* fp = fopen(dir, "r");
    
    // Obtener tamano del buffer
    fseek(fp, 0, SEEK_END); // Ir a EOF
    tamano = ftell(fp); // Obtener la cantidad de bytes que se pasaron

    // Colocar carrete al inicio del fichero
    rewind(fp);

    // Alocar memoria para el buffer
    buffer = malloc((tamano + 1) * sizeof(*buffer)); // tamano mas 1 para el '\0'

    // Leer el archivo en el buffer
    fread(buffer, tamano, 1, fp); // Leer 1 trozo de bytes e ingresar al buffer

    // Terminar el buffer en '\0' 
    // El archivo de texto completo ya esta en memoria
    buffer[tamano] = '\0';

    /* Fragmentar partes con strtok_r y empezar a leer */
    char *str_final;
    char *token = strtok_r(buffer, "\n", &str_final);
    token = strtok_r(NULL, "\n", &str_final);

    // Contadores de matriz
    int i = 0;
    int j = 0;
    
    while (token != NULL)
    {
        char *token_final;
        char *token2 = strtok_r(token, ",", &token_final);
        
        while (j < cols)
        {
            if (token2 != NULL) 
            {
                if (token2[strlen(token2) - 1] == '\r') 
                {
                    token2[strlen(token2) - 1] = '\0';
                }
                *(arr + i*cols + j) = token2;
                token2 = strtok_r(NULL, ",", &token_final);
            }
            else 
            {
                *(arr + i*cols + j) = "NULL\0";
            }
            j++;
        }
        token = strtok_r(NULL, "\n", &str_final);
        j = 0; i++;
    }
}

