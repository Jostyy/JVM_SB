# Software Básico

#### PROJETO JVM - GRUPO 7 - 2020/1

###### Caio Calixto Fasolak Alves 		    15/0078676
###### Jean Rodrigues Magalhães			    15/0079923
###### Jônatas Rocha de Paiva 			    14/0177043
###### Marcelo Axel Chiapinotto de Nazaré   15/0080727
###### Rafael Oliveira de Souza 			15/0081537
 
#### USING MAKE ##################################################################################################

Execute: 
    make clean 

    Mode deploy: make debug
    Mode execution: make all

#### Linux:

Comandos Para usar o exibidor: ./jvm -e "nomeArquivo.class"
Comandos Para usar a jvm: ./jvm -i "nomeArquivo.class"

#### Windows:

Comandos Para usar o exibidor: ./jvm -e "${CAMINHO_DO_ARQUIVO}/nomeArquivo.class"
Comandos Para usar a jvm: ./jvm -i "${CAMINHO_DO_ARQUIVO}/nomeArquivo.class"

#### USING COMMAND LINE #########################################################################################
g++ -std=c++11 -Wall constantPool.h frame.h classeLeitor.h classFlags.h pilhaOperandos.h operacoes.h methods.h methodArea.h localVariables.h interfaces.h fields.h attributes.h baseTypes.h classe.h constantPool.cpp frame.cpp classeLeitor.cpp classFlags.cpp pilhaOperandos.cpp operacoes.cpp methods.cpp methodArea.cpp localVariables.cpp interfaces.cpp fields.cpp attributes.cpp baseTypes.cpp classe.cpp main.cpp -lm -o jvm

#### Linux:

Comandos Para usar o exibidor: ./jvm -e "nomeArquivo.class"
Comandos Para usar a jvm: ./jvm -i "nomeArquivo.class"

#### Windows:

Comandos Para usar o exibidor: ./jvm -e "${CAMINHO_DO_ARQUIVO}/nomeArquivo.class"
Comandos Para usar a jvm: ./jvm -i "${CAMINHO_DO_ARQUIVO}/nomeArquivo.class"
#### ######################################################################################################



#### SITE DO PROJETO ##################################################################################################
Execute:
    make docs

Vá para a pasta doc >> html
Abra o arquivo index.html