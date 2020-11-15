/*! \file method.h
	\brief Metodos
*/

/*! \def METHOD_H
	\brief Macro

	Define uso para evitar a inclusão múltipla de arquivos.
*/
#ifndef METHOD_H
#define METHOD_H

#include "baseTypes.h"
#include "constantPool.h"
#include "attributes.h"

using namespace std;

typedef struct 
{
	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	attribute_info *attributes;
} method_info;


/*! \fn get_Method_Flags (uint16_t flags)
	\brief Obtém as access flags dos métodos para print
	\param flags dos métodos dado method_info.access_flags
 */
string get_Method_Flags (uint16_t flags);


/*! \fn read_Method(FILE* fp, cp_info *cp)
	\brief Lê um método do arquivo .class
	\param *fp ponteiro para o arquivo .class
	\param *cp ponteiro para as informações do pool de constantes
*/
method_info read_Method (FILE* fp,cp_info *cp);


/*! \fn read_Methods(FILE* fp, int length, cp_info *cp)
 	\brief Lê os métodos do arquivo .class
	\param *fp ponteiro para o arquivo .class
	\param *cp ponteiro para as informações do pool de constantes
	\param length quantidade de métodos presente
 */
method_info *read_Methods (FILE* fp, int length,cp_info *cp);


/*! \fn printMethod(method_info f, cp_info *cp)
 	\brief Mostra um método do arquivo .class
	\param f contém as informações do método
	\param *cp ponteiro para as informações do pool de constantes
 */
void printMethod (method_info f, cp_info *cp);


/*! \fn printMethods(method_info *f, cp_info *cp. int length)
	\brief Mostra todos os métodos do arquivo .class
	\param *f ponteiro para as informações do método
	\param *cp ponteiro para as informações do pool de constantes
	\param length quantidade de métodos a serem mostrados
 */
void printMethods (method_info *f, cp_info *cp, int length);

#endif 