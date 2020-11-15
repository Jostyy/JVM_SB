/*! \file methodArea.h
	\brief Area de Metodo
*/

/*! \def METHOD_AREA_H
	\brief Macro

	Define uso para evitar a inclusão múltipla de arquivos.
*/
#ifndef METHOD_AREA_H
#define METHOD_AREA_H

class MethodArea;

#include "classeLeitor.h"
#include "baseTypes.h"
#include "constantPool.h"
#include "frame.h"
#include "classe.h"
#include <map>
#include <algorithm>
#include <string.h>

using namespace std;

class MethodArea{
private:
	static map<string, ClasseEstatica*> classes;
	static FrameStack *fs;


public:
	static string path;


	/*! \fn getClass(string s)
	  	\brief Retorna referência para classe estática
			  
		\param s Nome da classe
	 */
	static ClasseEstatica *getClass(string);


	/*! \fn addClass(Leitor* s)
		\brief Carrega a classe na memória
		
		\param s Nome da classe
	 */
	static bool addClass(Leitor*);


	/*! \fn addClass(string l)
	 	\brief Carrega classe na memória
	 	\param l informação do arquivo .class na memória
	 */
    static bool addClass(string);


	/*! \fn setFrameStack(FrameStack* newFS)
		\brief Atualiza a referência da pilha de frames para o próximo frame
		\param newFS próximo frame
	 */
    static void setFrameStack(FrameStack*);
};

#endif