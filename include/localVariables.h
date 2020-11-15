/*! \file localVariables.h
	\brief Local Variables

	Armazena as variaveis locais para o metodo atual
*/

/*! \def LOCALVARIABLES_H
	\brief Macro

	Define uso para evitar a inclusão múltipla de arquivos.
*/

#ifndef LOCALVARIABLES_H
#define LOCALVARIABLES_H

#include <cstdint>
#include <stack>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "baseTypes.h"

//Testar se endereco e 32 ou 64 bits
#define BITS (sizeof(int*) == 8)

#define INVALID 99
#define TYPE_NOT_SET 0
#define TYPE_INT 1
#define TYPE_FLOAT 2
#define TYPE_LONG 3
#define TYPE_DOUBLE 4
#define TYPE_BOOL 5
#define TYPE_REFERENCE 6


/*! \class LocalVariables
	\brief Local variables Class

	Responsible for all operations that envolves the local variables
*/
class LocalVariables 
{
private:
	//vetor de valor
	uint32_t *elements;
	//vetor tipos
	uint8_t *types;
	//maxima quantidade
	const uint16_t max;
	const uint16_t realMax;
	//diz se ocupa 2 espa�os
	const bool dois;
public:
	/*! \fn LocalVariables(uint16_t maxSize)
		\brief Construtor da classe LocalVariables

		\param maxSize Tamanho maximo da variavel local a ser armazenada
	*/
	LocalVariables(uint16_t);

	
	/*! \fn LocalVariables(uint16_t maxSize, bool slots)
		\brief Construtor da classe LocalVariables

		\param maxSize Tamanho maximo da variavel local a ser armazenada
		\param slots Se precisa utilizar 2 slots para todos os elementos
	*/
	LocalVariables(uint16_t, bool);
	

	/*! \fn ~LocalVariables()
		\brief Destrutor
	*/
	~LocalVariables();

	
	/*! \fn void printall() const
		\brief Funcao para mostrar todos os valores
	*/
	void printall() const;

	
	/*! \fn void set(int index, typedElement x)
		\brief Recebe o elemento tipado e insere no indice passado

		\param index Indice onde será inserido o elemento
		\param x Elemento tipado a ser inserido
	*/
	void set(int, typedElement);

	
	/*! \fn typedElement get(int index) const
		\brief Retorna o elemento tipado no indice passado.

		\param index Indice onde será pego o elemento
	*/
	typedElement get(int) const;

	
	/*! \fn int getMax() const
		\brief Funcao para saber o tamanho maximo
	*/
	int getMax() const;

	
	/*! \fn const typedElement operator[] (const int index) const
		\brief Funcao para usar classe como um vetor de struct

		\param index Indice que será acessado para obter o elemento tipado
	*/
	const typedElement operator[] (const int) const;

};

#endif