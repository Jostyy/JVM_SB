// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// SB_prototipo.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//


#include <iostream>
#include <string>


void cmdInput(int argc, char** argv) {

	switch (argc) {
		case 3:
		{
			std::string arg(argv[1]);
			if (arg == "-e") {
				std::cout << "Leitor_Exibidor" << std::endl;
				std::string arg(argv[2]);
				if (arg.size() > 6) {
					if (arg.compare(arg.size() - 6, 6, ".class") == 0) {
						//Ler arquivo .class,
						
					}
					else {
						std::cout << "Formato de arquivo incorreto" << std::endl;
					}
				}
			}
			else if (arg == "-c") {
				std::cout << "JVM completa ainda nao implementada" << std::endl;
			}
			else {
				std::cout << "Flag nao reconhecida" << std::endl;
			}
			break;
		}
		default:
		{
			std::cout << "Numero incorreto de argumentos" << std::endl;
			break;
		}
	}
}



int main(int argc, char** argv)
{
	cmdInput(argc, argv);

    std::cout << "Hello World!\n";

	return 0;
}

