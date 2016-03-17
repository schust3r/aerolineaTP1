/* 
 * File:   lectura.c
 * Created on 12 de marzo de 2016, 09:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "constructor.h"

/**
 * Permite al usuario seleccionar el archivo de texto donde esta la 
 * informacion de los asientos. Se ejecuta al inicio
 * 
 * @param dir
 * @return valor entero
 * Restricciones: el directorio debe ser valido
 */
int seleccionarDir(char dir[]) {
    // Obtener direccion en disco donde se ubica el archivo a cargar
    printf("\n ** Inicializando programa... **\n");
    printf("%s", "Ingrese el directorio del archivo de texto: ");
    scanf("%s", dir);
    return 0;
}

/**
 * Guarda la informacion de cabecera en un struct global
 * 
 * @param directorio
 * @param cabecera - encabezado de vuelo
 * @return entero
 * Restricciones: direccion debe contener un archivo de texto
 */
int cargarCabecera(char directorio[], Cabecera *cab) 
{
    // Definir FILE para cargar a partir de directorio
    FILE* archivo = fopen(directorio, "r");
    
    // Array para almacenar las lineas de texto temporalmente
    char linea[256];
    
    char origen[16];
    char destino[16];
    char avion[32];
    char salida[20];
    char llegada[20];
    
    fgets(linea, sizeof(linea), archivo);

    sscanf(linea, "Origen:%[^,\n],Destino:%[^,\n],Avion:%[^,\n],Salida:%[^,\n],Llegada:%[^,\n]", 
           origen, destino, avion, salida, llegada);
    
    strcpy((*cab).origen, origen);
    strcpy((*cab).destino, destino);
    strcpy((*cab).avion, avion);
    strcpy((*cab).fec_salida, salida);
    strcpy((*cab).fec_llegada, llegada);
    
    return 0;
}

/**
 * Carga los asientos en una matriz tridimensional para almacenar
 * los identificadores de cada uno.
 * 
 * @param directorio
 * @param vuelo
 * @return int
 * Restricciones: direccion debe contener un txts
 */
int cargarAsientos(char directorio[], char *asiento[], Vuelo *vuelo) 
{
    // Array para almacenar las lineas de texto temporalmente
    char linea[256];
    
    // Definir FILE para cargar a partir de directorio
    FILE* archivo = fopen(directorio, "r");
    fgets(linea, 256, archivo); // Omitir la primera linea
    
    // Crear punteros a archivo similares a archivo
    FILE* p_arc_1 = fopen(directorio, "r");
    fgets(linea, 256, p_arc_1);
    
    FILE* p_arc_2 = fopen(directorio, "r");
    fgets(linea, 256, p_arc_2);
    
    // Contar filas y columnas del cuerpo
    int cant_filas, cant_cols = 0;
    cant_filas = contarFilas(p_arc_1);
    cant_cols  = contarCols(p_arc_2);    
    
    (*vuelo).filas = cant_filas;
    (*vuelo).columnas = cant_cols;

    // Inicializar la matriz y cargar los datos
    cargarMatriz(cant_filas, cant_cols, asiento, directorio);
       
    fclose(archivo);
    return 0;
}

/**
 * Cuenta columnas del archivo
 * @param n
 * @return numero de columnas
 */
int contarCols(FILE *n) 
{
    char c; 
    int temp_comas = 0;
    int max_comas = 0;
    
    while ((c = fgetc(n)) != EOF) 
    {
        if (c == ',') 
        {
            temp_comas++; 
        }
        
        if (c == '\n') 
        {
            if (temp_comas > max_comas) 
            {
                max_comas = temp_comas;
            }
            temp_comas = 0;              
        }
    }
    return max_comas + 1;
}

/**
 * Cuenta filas del archivo
 * @param n
 * @return numero de filas
 */
int contarFilas(FILE *n) 
{
    char c; 
    int filas = 0;

    while ((c = fgetc(n)) != EOF) 
    {
        if (c == '\n') { 
            filas++; 
        }
    }
    return filas + 1;
}