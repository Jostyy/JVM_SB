/*!
 * \file pilhaOperandos.cpp
 * \brief Pilha de Operandos
 */

#include "pilhaOperandos.h"


PilhaOperandos::PilhaOperandos (int maxSize) : realMax(maxSize), max(2*maxSize)
{
	typePushed = false;
}


uint8_t PilhaOperandos::top_type()
{
	return ((!this->empty()) ? (this->tipos.top()) : (-1));
}


element PilhaOperandos::top_value()
{
	element ret;

	ret.i = this->elementos.top();

	if (this->empty())
	{
		printf("Ret error\n");
		return ret;
	}


	ret.i = this->elementos.top();


	if (this->tipos.top() == TYPE_LONG || this->tipos.top() == TYPE_DOUBLE || (this->tipos.top() == TYPE_REFERENCE && bits64))
	{
		uint32_t aux = ret.i;
		this->elementos.pop();
		ret.l = int64_t((int64_t(ret.i)<<32) + this->elementos.top());
		this->elementos.push(aux);
	}

	return ret;
}


element PilhaOperandos::pop()
{
	element ret;

	ret = this->top_value();

	if (this->empty())
	{
		return ret;
	}


	//ret = this->top_value();


	this->elementos.pop();


	if (this->tipos.top() == TYPE_LONG || this->tipos.top() == TYPE_DOUBLE || (this->tipos.top() == TYPE_REFERENCE && bits64))
	{
		this->elementos.pop();
	}


	this->tipos.pop();
	this->tiposReais.pop();

	return ret;
}


typedElement PilhaOperandos::popTyped()
{
	typedElement ret;
	ret.type = this->tipos.top();
	ret.realType = this->tiposReais.top();
	ret.value = this->pop();

	return ret;
}


std::string PilhaOperandos::getString ()
{
	std::stringstream ret;


	switch (this->top_type())
	{
		case TYPE_INT:
			ret << "(int) " << int(this->top_value().i);
			break;
		case TYPE_LONG:
			ret << "(long) " << long(this->top_value().l);
			break;
		case TYPE_FLOAT:
			ret << "(float) " << this->top_value().f;
			break;
		case TYPE_DOUBLE:
			ret << "(double) " << this->top_value().d;
			break;
		case TYPE_BOOL:
			ret << "(bool) " << (int) this->top_value().b;
			break;
		case TYPE_REFERENCE:
			ret << "(reference) " << this->top_value().pi;
			break;
	}

	return ret.str();
}


void PilhaOperandos::push(int x)
{

	if (this->size() == max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}


	this->tipos.push(TYPE_INT);
	if (!typePushed)
	{
		this->tiposReais.push(RT_INT);
	}


	this->elementos.push(x);

	typePushed = false;
}


void PilhaOperandos::push(float x)
{

	if (this->size() == max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	element aux;
	aux.f = x;


	this->tipos.push(TYPE_FLOAT);
	if (!typePushed)
		this->tiposReais.push(RT_FLOAT);


	this->elementos.push(aux.i);

	typePushed = false;
}


void PilhaOperandos::push(double x)
{

	if (this->size()+1 >= max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	element aux;
	aux.d = x;


	this->tipos.push(TYPE_DOUBLE);
	if (!typePushed)
	{
		this->tiposReais.push(RT_DOUBLE);
	}


	this->elementos.push(aux.i);

	aux.l >>= 32;

	this->elementos.push(aux.i);
	

	typePushed = false;
}


void PilhaOperandos::push(int64_t _x)
{
	uint64_t x = _x;

	if (this->size()+1 >= max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}


	this->tipos.push(TYPE_LONG);
	if (!typePushed)
	{
		this->tiposReais.push(RT_LONG);
	}


	this->elementos.push(x);

	x >>= 32;

	this->elementos.push(x);

	typePushed = false;
}


void PilhaOperandos::push(bool x)
{

	if (this->size() == max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	element aux;
	aux.b = x;


	this->tipos.push(TYPE_BOOL);
	if (!typePushed)
	{
		this->tiposReais.push(RT_BOOL);
	}


	this->elementos.push(aux.i);

	typePushed = false;
}


void PilhaOperandos::push(int *x)
{

	if (this->size()+bits64 >= max)
	{
		throw std::out_of_range("Passou do limite maximo da pilha!");
	}

	element aux;
	aux.pi = x;


	this->tipos.push(TYPE_REFERENCE);
	if (!typePushed)
	{
		this->tiposReais.push(RT_REFERENCE);
	}


	this->elementos.push(aux.i);


	if (bits64)
	{
		aux.l >>= 32;
		this->elementos.push(aux.i);
	}

	typePushed = false;
}


void PilhaOperandos::push(typedElement te)
{
	this->tiposReais.push(te.realType);
	typePushed = true;
	this->push(te.value, te.type);
}


void PilhaOperandos::push(element x, uint8_t tipo) {
	switch (tipo)
	{
		case TYPE_DOUBLE:
			this->push(x.d);
			break;
		case TYPE_LONG:
			this->push(int(x.l));
			break;
		case TYPE_FLOAT:
			this->push(x.f);
			break;
		case TYPE_INT:
			this->push(int(x.i));
			break;
		case TYPE_REFERENCE:
			this->push((int*)(x.pi));
			break;
		case TYPE_BOOL:
			this->push(x.b);
			break;
		default:
			break;
	}
}


int PilhaOperandos::getMaxSize()
{
	return this->realMax;
}


int PilhaOperandos::size()
{
	return this->elementos.size();
}


void PilhaOperandos::printALL()
{
	PilhaOperandos aux(this->max);

	while (!this->empty())
	{
		cout << this->getString() << endl;
		aux.push(this->popTyped());
	}

	while (!aux.empty())
	{
		this->push(aux.popTyped());
	}
}



bool PilhaOperandos::empty()
{
	return this->elementos.empty();
}
