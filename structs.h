/* 
 * File:   structs.h
 * Author: Joel
 *
 * Created on 13 de marzo de 2016, 08:54 AM
 */

#ifndef STRUCTS_H
#define	STRUCTS_H

// Struct para Cabecera de vuelo con typedef
typedef struct CabeceraTag {
    char origen[16];
    char destino[16];
    char avion[32];
    char fec_salida[20];
    char fec_llegada[20];
} Cabecera;

typedef struct VueloTag {
    int filas;
    int columnas;
} Vuelo;

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* STRUCTS_H */

