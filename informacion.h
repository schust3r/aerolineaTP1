/* 
 * File:   informacion.h
 * Author: Joel
 *
 * Created on 13 de marzo de 2016, 09:15 PM
 */

#ifndef INFORMACION_H
#define	INFORMACION_H

#ifdef	__cplusplus
extern "C" {
#endif

int mostrarInfoVuelo(Cabecera *cab);
int mostrarOcupacion(int fila, int columna, char *asiento[]);    
int mostrarCantidadAsientos(int filas, int columnas, char *asiento[]);
int mostrarFilasColumnas(int filas, int columnas);
int mostrarRangosColumnas(int fila, int columna, char *asiento[]);
int obtenerAsientosLibresCategoria(int fila, int columna, char *asiento[]);

#ifdef	__cplusplus
}
#endif

#endif	/* INFORMACION_H */

