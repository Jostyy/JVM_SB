
#ifndef FRAME_H
#define FRAME_H

class FrameStack;

#include "classeLeitor.h"
#include "pilhaOperandos.h"
#include "localVariables.h"
#include "baseTypes.h"
#include "operacoes.h"
#include "attributes.h"
#include "methodArea.h"

typedef struct frame_s{
	unsigned char *pc;
	cp_info *cp;	
	PilhaOperandos *operandos;
	LocalVariables *locals;
	method_info m;
} frame;


class FrameStack {
private:
	std::stack<frame*> threads;

	bool nextInstruction();
	int opcode;

	void startPC(frame*);
public:

	FrameStack (Leitor*);

	void setArguments(std::vector<typedElement>);

	void execute();
	
	void addFrame(method_info, cp_info*);

	void addFrame(method_info*, cp_info*);

	void pop();
};

#endif
