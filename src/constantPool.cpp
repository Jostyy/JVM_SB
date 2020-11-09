#include "../include/constantPool.h"

void printConstantPool(cp_info* constantPool, int tamanhoCP) {
	cout << "Constant Pool:" << endl;

	for (int i = 1; i < tamanhoCP; i++) {
		printf("\t [%3d] ", i);
		cout << typeNames[constantPool[i].tag - 1];
		switch (constantPool[i].tag) {
		case UTF8:
			cout << "\t" << showUTF8(constantPool[i].info[1].array, constantPool[i].info[0].u2);
			break;
		case INTEGER:
			cout << "\t" << constantPool[i].info[0].u4;
			break;
		case FLOAT:
			cout << "\t" << u4_to_float(constantPool[i].info[0]) << "f";
			break;
		case LONG:
			cout << "\t" << u4_to_long(constantPool[i].info[0], constantPool[i + 1].info[0]) << "l";
			i++;
			break;
		case DOUBLE:
			cout << "\t" << u4_to_double(constantPool[i].info[0], constantPool[i + 1].info[0]) << "d";
			i++;
			break;
		case CLASS:
		case STRING:
			cout << " " << constantPool[i].info[0].u2 << "\t\t// " << dereferenceIndex(constantPool, i);
			break;
		case NAME_AND_TYPE:
			cout << " cp info #" << constantPool[i].info[0].u2 << "  cp info #" << constantPool[i].info[1].u2;
			cout << "\t\t// " << dereferenceIndex(constantPool, i);
			break;
		case METHOD_REF:
		case INTERFACE_REF:
		case FIELD_REF:
			cout << " cp info #" << constantPool[i].info[0].u2 << "  cp info #" << constantPool[i].info[1].u2;
			cout << "\t\t// " << dereferenceIndex(constantPool, i);
			break;
		}
		cout << endl;
	}
	cout << endl;
}


int loadConstantPool (cp_info *constantPool, int tamanhoCP, FILE* fp){
	int i;

	for (i = 1; i < tamanhoCP; i++){
		constantPool[i].tag = readU1(fp);
		if (!(constantPool[i].tag > 0) && !(constantPool[i].tag <= 12) && !(constantPool[i].tag != 2)){
			return i;
		}
	
		switch (constantPool[i].tag){
			case UTF8:
				constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType) * 2);
				constantPool[i].info[0].u2 = readU2(fp);
				constantPool[i].info[1].array = readUTF8(fp, constantPool[i].info[0].u2);
				break;

			case INTEGER:
			case FLOAT:
				constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
				constantPool[i].info[0].u4 = readU4(fp);
				break;

			case LONG:
			case DOUBLE:
				constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
				constantPool[i].info[0].u4 = readU4(fp);
				constantPool[++i].tag = INVALID;
				constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
				constantPool[i].info[0].u4 = readU4(fp);
				break;

			case CLASS:
			case STRING:
				constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
				constantPool[i].info[0].u2 = readU2(fp);
				break;

			case FIELD_REF:
			case METHOD_REF:
			case INTERFACE_REF:
			case NAME_AND_TYPE:
				constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType) * 2);
				constantPool[i].info[0].u2 = readU2(fp);
				constantPool[i].info[1].u2 = readU2(fp);
				break;
		}
	}
	return i;
}

string dereferenceIndex (cp_info *cp, U2 index){
	switch (cp[index].tag){
		case UTF8:
			return showUTF8(cp[index].info[1].array, cp[index].info[0].u2);

		case CLASS:
		case STRING:
			return dereferenceIndex(cp, cp[index].info[0].u2);

		case NAME_AND_TYPE:
			return (dereferenceIndex(cp, cp[index].info[0].u2) + "  " + dereferenceIndex(cp, cp[index].info[1].u2));

		case METHOD_REF:
		case INTERFACE_REF:
		case FIELD_REF:
			return (dereferenceIndex(cp, cp[index].info[0].u2) + "  " + dereferenceIndex(cp, cp[index].info[1].u2));
	}
	return "";
}
