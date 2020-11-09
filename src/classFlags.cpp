#include "../include/classFlags.h"

void showFlags (U2 acessoFlags){
	bool primeiro = true;

	printf("Flags: ");

	if(acessoFlags & 0x01){
		primeiro = false;
		printf("%s", flagNames[0].c_str());
	}

	if(acessoFlags & 0x010){
		if(primeiro)
		{
			primeiro = false;
			printf(", ");
		}

		printf("%s", flagNames[1].c_str());
	}

	if(acessoFlags & 0x020){
		if(primeiro){
			primeiro = false;
			printf(", ");
		}

		printf("%s", flagNames[2].c_str());
	}

	if(acessoFlags & 0x0200){
		if(primeiro)
		{
			primeiro = false;
			printf(", ");
		}
		
		printf("%s", flagNames[3].c_str());
	}

	if(acessoFlags & 0x0400){
		if(primeiro)
		{
			primeiro = false;

			printf(", ");
		}

		printf("%s", flagNames[4].c_str());
	}
	
	cout << " (0x" << hex << acessoFlags << dec << ")" << endl;
}