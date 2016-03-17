/* 
 * File:   reservacion.h
 * Author: Joel
 *
 * Created on 15 de marzo de 2016, 08:15 AM
 */

#ifndef RESERVACION_H
#define	RESERVACION_H

#ifdef	__cplusplus
extern "C" {
#endif

int reservarAsientos(int cols, char *asientos[], int num_asientos);
int cancelarReserva(int filas, int cols, char *asientos[], char id[]);
int mostrarInfoReserva(int filas, int cols, char *asientos[], char id[]);
int mostrarAsientosDispCategoria(int filas, int cols, char *asientos[], char cat);

#ifdef	__cplusplus
}
#endif

#endif	/* RESERVACION_H */

