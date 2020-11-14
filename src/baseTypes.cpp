#include "baseTypes.h"


U2 readU2 (FILE *fp) 
{
	unsigned short data = 0;
	unsigned char aux;

	fread(&data, 1, 1, fp);
	fread(&aux, 1, 1, fp);

	data <<= 8;
	data |= aux;

	return data;
}

U1 readU1 (FILE *fp)
{
	unsigned char data;

	fread(&data, 1, 1, fp);

	return data;
}

U1 * readUTF8 (FILE* fp, int size) 
{
	

	std::vector<unsigned char> *data = new std::vector<unsigned char>(size);

	for (int i = 0; i < size; i++) {
		data->at(i) = readU1(fp);
	}

	return (U1*) data;
} 

U4 readU4 (FILE *fp)
 {
	unsigned int data = 0;
	unsigned char aux;

	for (int i=0; i<4; i++) {
		data <<= 8;
		fread(&aux, 1, 1, fp);
		data |= aux;
	}

	return data;
}

string showUTF8 (unsigned char * s, int size) 
{
	std::vector<unsigned char> *v = (std::vector<unsigned char> *) s;
	string data = "";
	size = v->size();
	int i = 0;

	while (i < size) {
		if (!(v->at(i) & 0x80)) { //utf8 only with 1 bit
			data.push_back(v->at(i));
		} else {
			unsigned short auxCurrent;
			if (!(v->at(i+1) & 0x20)) { //utf8 of 2 bytes
				auxCurrent = ((v->at(i) & 0x1f) << 6) + (v->at(i+1) & 0x3f);
			} else { //utf8 of 3 bytes
				auxCurrent = ((v->at(i) & 0xf) << 12) + ((v->at(i+1) & 0x3f) << 6) + (v->at(i+2) & 0x3f);
				i++;
			}
			i++;
			data.push_back(auxCurrent);
		}
		i++;
	}

	return data;
}

long u4_to_long (ClassLoaderType high, ClassLoaderType low) 
{
	int64_t data;
	
	data = (((int64_t) high.u4) << 32) | low.u4;
	
	return data;
}

double u4_to_double (ClassLoaderType high, ClassLoaderType low) 
{
	double data;
	uint64_t checkBoundaries = u4_to_long(high, low);
	
	if (checkBoundaries == 0x7ff0000000000000L) {
		//return infinity??
	} else if (checkBoundaries == 0xfff0000000000000L) {
		//return negative infinity??
	} else if ((checkBoundaries >= 0x7ff0000000000001L) && (checkBoundaries <= 0x7ffffffffffffL)) {
		//return NaN??
	} else if ((checkBoundaries >= 0xfff0000000000001L) && (checkBoundaries <= 0xffffffffffffffffL)) {
		//return NaN??
	} else {
		int64_t s = ((checkBoundaries >> 63) == 0) ? 1 : -1;
		int64_t e = ((checkBoundaries >> 52) & 0x7ffL);
		int64_t m = (e == 0) ? (checkBoundaries & 0xfffffffffffffL) << 1 : (checkBoundaries & 0xfffffffffffffL) | 0x10000000000000L;
		
		data = s * m * pow(2, (e-1075));
	}
	
	return data;
}

float u4_to_float (ClassLoaderType in) 
{
	float data;
	
	int s = ((in.u4 >> 31) == 0) ? 1 : -1;
	int e = ((in.u4 >> 23) & 0xff);
	int m = (e == 0) ? (in.u4 & 0x7fffff) << 1 : (in.u4 & 0x7fffff) | 0x800000;

	data = s * m * pow(2, (e-150));
		
	return data;
}

//Muda o valor de double e retorna em formato string
string double_to_string (double d) 
{
	stringstream data;
	switch (checkDouble(d)) {
		case 0:
			data << d;
			break;
		case 1:
			data << "+Inf";
			break;
		case 2:
			data << "-Inf";
			break;
		case 3:
			data << "NaN";
			break;
	}

	return data.str();
}


//Retorna 1 para mais infinito, 2 para menos infinito, 3 para NaN e 0 para numero dentro dos limítes
int checkFloat (float f) 
{
	int data = 0;
	element aux;
	aux.f = f;

	if ((aux.i >= 0x7f800001 && aux.i <= 0x7fffffff) || (aux.i >= 0xff800001 && aux.i <= 0xffffffff)) {
		data = 3;
	} else if (aux.i == 0x7f800000) {
		data = 1;
	} else if (aux.i == 0xff800000) {
		data = 2;
	}

	return data;
}

//Retorna 1 para mais infinito, 2 para menos infinito, 3 para NaN e 0 para numero dentro dos limítes
int checkDouble (double d) 
{
	int data = 0;
	element aux;
	aux.d = d;

	if ((aux.l >= 0x7ff0000000000001L && aux.l <= 0x7ffffffffffffL) || (aux.l >= 0xfff0000000000001L && aux.l <= 0xffffffffffffffffL)) {
		data = 3;
	} else if (aux.l == 0x7ff0000000000000L) {
		data = 1;
	} else if (aux.l == 0xfff0000000000000L) {
		data = 2;
	}

	return data;
}

//Muda o valor de float e retorna em formato string
string float_to_string (float f) 
{
	stringstream data;
	switch (checkFloat(f)) {
		case 0:
			data << f;
			break;
		case 1:
			data << "+Inf";
			break;
		case 2:
			data << "-Inf";
			break;
		case 3:
			data << "NaN";
			break;
	}

	return data.str();
}
