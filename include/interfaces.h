/*! \file interfaces.h
	\brief Interfaces

	Manipula as informacoes de interface do .class
*/

/** @def INTERFACES_H
	@brief Macro
*/
#ifndef INTERFACES_H
#define INTERFACES_H

#include <iostream>
#include "constantPool.h"
#include "baseTypes.h"


/** @fn unsigned short *readInterfaces (FILE *fp, int length)
	@brief Carrega as interfaces na memoria a partir do arquivo class.
	@param flags Flags em haxadecimal que serao convertidas para string.
	@param fp Ponteiro para o arquivo class.
	@param length Numero de interfaces a serem lidas.
*/
unsigned short *readInterfaces (FILE *fp, int length);


/** @fn void printInterfaces (unsigned short *interfaces, cp_info *cp, int length)
	@brief Mostra todas as interfaces do arquivo.

	@param interfaces Array de interfaces.
	@param cp Ponteiro para a constantpool.
	@param length Numero de interfaces.
*/
void printInterfaces (unsigned short *interfaces, cp_info *cp, int length);


/** @fn printInterface (unsigned short interface, cp_info *cp)
	@brief Mostra informacoes de uma interface especifica.

	@param interface Indice do constantpool.
	@param cp Ponteiro para a constantpool.
*/
void printInterface (unsigned short interface, cp_info *cp);


/** @fn printInterface (unsigned short interface, cp_info *cp, int index)
	@brief Mostra informacao de uma interface especifica com o indice da interface.

	@param interface Indice do constantpool.
	@param cp Ponteiro para o constantpool.
	@param index Indice da interface especifica.
*/
void printInterface (unsigned short interface, cp_info *cp, int index);


#endif
