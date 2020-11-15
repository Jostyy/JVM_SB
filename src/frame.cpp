/*!
 * \file frame.cpp
 * \brief frame
 */

#include "frame.h"

FrameStack::FrameStack (Leitor *l){
	frame *aux = (frame*) malloc(sizeof(frame));
	
	aux->m = l->getMain();
	aux->cp = l->getCP();
	aux->operandos = new PilhaOperandos(aux->m.attributes->info->code.max_stack);
	aux->locals = new LocalVariables(aux->m.attributes->info->code.max_locals);
	startPC(aux);
	threads.push(aux);
	Operacoes::setFrame(threads.top());
	Operacoes::setThreads(&threads);
	Operacoes::setFrameStack(this);
	MethodArea::setFrameStack(this);
	opcode = 0;
}

void FrameStack::execute(){
	while (nextInstruction())
	{
		Operacoes::run(opcode);
	}
}

bool FrameStack::nextInstruction(){
	if (threads.empty())
	{
		return false;
	}

	if ((threads.top()->pc - threads.top()->m.attributes->info->code.code) < threads.top()->m.attributes->info->code.code_length)
	{
		opcode = *threads.top()->pc;
		threads.top()->pc++;
		return true;
	}

	this->pop();
	if (threads.empty())
	{
		return false;
	}

	return true;
}

void FrameStack::pop(){
	
	if (!threads.empty()){
		
		delete threads.top()->operandos;
		delete threads.top()->locals;
		threads.pop();
	}
	if (threads.empty()) {
		Operacoes::setFrame(nullptr);
		Operacoes::setThreads(nullptr);
		exit(0);
	}
	Operacoes::setFrame(threads.top());
	Operacoes::setThreads(&threads);
}

void FrameStack::startPC(frame *f){
	f->pc = f->m.attributes->info->code.code;
}

void FrameStack::addFrame(method_info m, cp_info *cp){
	
	frame *aux = (frame*) malloc(sizeof(frame));

	aux->m = m;
	aux->cp = cp;
	aux->operandos = new PilhaOperandos(aux->m.attributes->info->code.max_stack);
	aux->locals = new LocalVariables(aux->m.attributes->info->code.max_locals);
	startPC(aux);
	
	Operacoes::setFrame(aux);
	Operacoes::setThreads(&threads);
	Operacoes::setFrameStack(this);

	MethodArea::setFrameStack(this);
	threads.push(aux);
}

void FrameStack::addFrame(method_info *m, cp_info *cp){
	
	this->addFrame(*m, cp);
}

void FrameStack::setArguments(std::vector<typedElement> param){
	
	for (int i = 0, j=0; (unsigned int) i < param.size(); i++, j++){
		
		
		threads.top()->locals->set(j, param[i]);

		if (threads.top()->locals->get(j).type == TYPE_LONG || threads.top()->locals->get(j).type == TYPE_DOUBLE){
			j++;
		}
	}
}
