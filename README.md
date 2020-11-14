HOW TO?

g++ -std=c++11 -Wall constantPool.h frame.h classeLeitor.h classFlags.h pilhaOperandos.h operacoes.h methods.h methodArea.h localVariables.h interfaces.h fields.h attributes.h baseTypes.h classe.h constantPool.cpp frame.cpp classeLeitor.cpp classFlags.cpp pilhaOperandos.cpp operacoes.cpp methods.cpp methodArea.cpp localVariables.cpp interfaces.cpp fields.cpp attributes.cpp baseTypes.cpp classe.cpp SB_test.cpp -lm -o jvm

Comandos Para usar o exibidor: ./jvm -e "nomeArquivo.class"
Comandos Para usar a jvm: ./jvm -i "nomeArquivo.class"
