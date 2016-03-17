/* 
 * File:   lectura.h
 * Author: Joel
 *
 * Created on 12 de marzo de 2016, 10:50 PM
 */

#ifndef LECTURA_H
#define	LECTURA_H

int seleccionarDir(char dir[]);
int cargarCabecera(char directorio[], Cabecera *cab);
int cargarAsientos(char directorio[], char *asientos[], Vuelo *vuelo);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LECTURA_H */

