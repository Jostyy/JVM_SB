/*!
 * \file main.cpp
 * \brief Funcao principal do projeto, opção de escolha entre interpretador e exibidor
 */

#include "../include/classeLeitor.h"
#include "../include/frame.h"
#include "../include/methodArea.h"


/**
 * @param argc, *argv[]
 * @section Alunos:
 * Caio Calixto Fasolak Alves 		  15/0078676
 * Jean Rodrigues Magalhães			  15/0079923
 * Jonatas Rocha de Paiva			  14/0177043
 * Marcelo Áxel Chiapinotto de Nazaré 15/0080727
 * Rafael Oliveira de Souza			  15/0081537
 */

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Parametros invalidos, o programa deve ser executado com: %s [-e ou -i] caminho_arquivo\n", argv[0]);
		return 1;
	}

	Leitor leitor(argv[2]);
	if (argv[1][1] == 'e')
	{
		leitor.run();
	}
	else if (argv[1][1] == 'i'){
		leitor.load();
		int status = leitor.getStatus();

		if(leitor.verifyStatus(status)){
			if (!leitor.hasMain()) {
				printf("O arquivo %s nao possui metodo main\n", argv[2]);
				return -1;
			}
			else if (status){
				return status;
			}
		}else{
			return status;
		}

		string pathC = leitor.getPath();
		MethodArea::path = pathC;
		MethodArea::addClass(&leitor);

		FrameStack frames(&leitor);
		frames.execute();
	}
	else
	{
		printf("Parametros invalidos, o programa deve ser executado com: %s [-e ou -i] caminho_arquivo\n", argv[0]);

		return 0;
	}

	return 0;
}
