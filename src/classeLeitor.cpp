#include "../include/classeLeitor.h"


Leitor::Leitor(char *in) {
	if (in) {	
		fileName = in;
	}
	status = -1;
}

Leitor::Leitor(std::string in) {
	if (!in.empty()) {
		fileName = new char[in.size() + 1];
		std::copy(in.begin(), in.end(), fileName);
		fileName[in.size()] = 0; 
	}
	status = -1;
}

int Leitor::run() {	
	if(load() == 0) {
		show();
	}
	return this->status;
}

int Leitor::load() {
	int checkCP;

	if (!fileName) {
		printf("%s\n", getError(MISSING_ARGUMENT).c_str());
		return (status = MISSING_ARGUMENT);
	}

	if (!validExtension()) {
		printf("%s\n", getError(INVALID_EXTENSION).c_str());
		return (status = INVALID_EXTENSION);
	}

	fp = fopen(fileName, "rb");
	if (fp == NULL) {
		printf("%s\n", getError(CANT_OPEN).c_str());
		return (status = CANT_OPEN);
	}

	if (readU4(fp) != 0xcafebabe)	{
		printf("%s\n", getError(INVALID_FILE).c_str());
		return (status = INVALID_FILE);
	}

	minVersion = readU2(fp);
	majVersion = readU2(fp);
	lengthCP = readU2(fp);
	constantPool = (cp_info *) malloc(sizeof(cp_info) * lengthCP);
	checkCP = loadConstantPool(constantPool, lengthCP, fp);

	if (checkCP != lengthCP) {
		cerr << getError(UNKNOWN_TYPE);
		return (status = UNKNOWN_TYPE);
	}

	accessFlags = readU2(fp);
	this_class = readU2(fp);

	if (!checkClass()) {
		cerr << getError(INVALID_NAME);
		return (status = INVALID_NAME);
	}

	super_class = readU2(fp);
	interfacesCount = readU2(fp);
	interfaces = readInterfaces(fp, interfacesCount);
	fieldsCount = readU2(fp);
	fields = readFields(fp, fieldsCount,constantPool);
	methodsCount = readU2(fp);
	methods = read_Methods(fp, methodsCount,constantPool);
	attributesCount = readU2(fp);
	attributes = readAttributes(fp, constantPool, attributesCount);
	foundMain = findMain();
	foundClinit = findClinit();

	fclose(fp);
	fp = NULL;
	return (status = 0);
}

bool Leitor::show() {
	if (status != 0) {
		return false;
	}
	printGeneralInformation();
	printConstantPool(constantPool, lengthCP);
	printInterfaces(interfaces, constantPool, interfacesCount);
	printFields(fields, constantPool, fieldsCount);
	printMethods(methods, constantPool, methodsCount);
	printAttributes(attributes, constantPool, attributesCount);

	return true;
}

bool Leitor::findMain () {
	bool encontrou = false;

	for (int i = 0; i < methodsCount; i++) {
		int name = methods[i].name_index, desc = methods[i].descriptor_index, flags = methods[i].access_flags;
		if ("main" == dereferenceIndex(constantPool, name)) {
			if ("([Ljava/lang/String;)V" == dereferenceIndex(constantPool, desc)) {
				if ((flags & 0x09) == 0x09) {
					mainMethod = i;
					encontrou = true;
					break;
				}
			}
		}
	}

	//se encontrou a main retorna true
	return encontrou;
}

void Leitor::printGeneralInformation (){
	cout << "" << endl;
	cout << "Minor version:\t\t " << minVersion << endl;
	cout << "Major version:\t\t " << majVersion << endl;
	cout << "Constant pool count:\t " << lengthCP << endl;
	showFlags(accessFlags);
	cout << "This class:\t\t cp info #" << this_class << " <" << dereferenceIndex(constantPool, this_class) << ">" << endl;
	cout << "Super class:\t\t cp info #" << super_class << " <" << dereferenceIndex(constantPool, super_class) << ">" << endl;	
	cout << "Interfaces count:\t " << interfacesCount << endl;
	cout << "Fields count:\t\t " << fieldsCount << endl;
	cout << "Methods count:\t\t " << methodsCount << endl;
	cout << "Attributes count:\t " << attributesCount << endl;
	cout << "" << endl;
}

bool Leitor::validExtension () {
	string aux = "", auxFilename(this->fileName);
	int size = auxFilename.size();

	if (size > 7) {
		for (int i = size-6; i < size; i++) {
			aux += auxFilename[i];
		}
	}

	return aux == ".class";
}

bool Leitor::findClinit() {
	bool encontrou = false;

	for (int i = 0; i < methodsCount; i++) {
		int name = methods[i].name_index;
		if ("<clinit>" == dereferenceIndex(constantPool, name)) {
			clinit = i;
			encontrou = true;
			break;
		}
	}

	return encontrou;
}

bool Leitor::hasMain () {
	return foundMain;
}

bool Leitor::hasClinit () {
	return foundClinit;
}

method_info Leitor::getMain() {
	if (foundMain) {
		return methods[mainMethod];
	} 
	else {
		throw runtime_error("Metodo main nao encontrado!\n");
	}
}

method_info Leitor::getClinit() 
{
	return methods[clinit];
}

bool Leitor::checkClass () {
	int auxPos;
	
	string auxFilename(this->fileName);
	string auxClass = dereferenceIndex(this->constantPool, this->this_class);
	
	auxFilename = auxFilename.substr(0, auxFilename.size()-6);
	auxPos = auxFilename.find("\\");
	while(auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) 	{
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("\\");
	}

	auxPos = auxFilename.find("/");
	while(auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) 	{
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("/");
	}

	return (auxClass == auxFilename);
}

int Leitor::getStatus () {
	return status;
}

string Leitor::getError (int error) {
	string ret = "";
	switch (error) 
	{
		case MISSING_ARGUMENT:
				ret = "Argumento invalido!\n";
				break;
			case CANT_OPEN:
				ret = "Nao foi possivel abrir o arquivo \"" + string(fileName) + "\"!\n";
				break;
			case INVALID_FILE:
				ret = "Arquivo invalido!\nAssinatura \"cafe babe\" nao encontrada.\n";
				break;
			case UNKNOWN_TYPE:
				ret = "Tipo nao reconhecido para o pool de constantes!\n";
				break;
			case INVALID_NAME:
				ret = "O nome da classe definida nao bate com o do arquivo!\n";
				break;
			case INVALID_EXTENSION:
				ret = "O arquivo deve ter a extensao .class!\n";
				break;
			default:
				break;
	}
	return ret;
}

cp_info* Leitor::getCP () const {
	return constantPool;
}

U2 Leitor::getLengthCP () {
	return lengthCP;
}

char *Leitor::getPath () {
	string path= "", auxFilename(this->fileName);
	char *caminho_arquivo;
	int auxPos;

	//navega pelas pastas do windows
	auxPos = path.find("\\");
	while(auxPos >= 0 && (unsigned int) auxPos <= path.size()) 
	{
		path += auxFilename.substr(0, auxPos+1);
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("\\");
	}

	//navega pelas pastas do linux
	auxPos = auxFilename.find("/");
	while(auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) 
	{
		path += auxFilename.substr(0, auxPos+1);
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("/");
	}

	//copia o resulta para a string caminho_arquivo
	caminho_arquivo = (char *) malloc(sizeof(char) * (path.size() + 1));
	for (unsigned int i = 0; i < path.size(); i++) 
	{
		caminho_arquivo[i] = path[i];
	}
	caminho_arquivo[path.size()] = '\0';

	return caminho_arquivo;
}

method_info *Leitor::getMethods() {
	return methods;
}

U2 Leitor::getMethodsCount() 
{
	return methodsCount;
}

U2 Leitor::getThis_class() {
	return this_class;
}

U2 Leitor::getSuper_class() {
	return super_class;
}

U2 Leitor::getFieldsCount() {
	return fieldsCount;
}

field_info *Leitor::getFields() {
	return fields;
}

field_info* Leitor::getField(string field_name) {
	for(int i = 0; i < getFieldsCount(); i++) 	{
		if(dereferenceIndex(constantPool, fields[i].name_index) == field_name )
		{
			return fields+i; 
		}
	}
	return NULL;

}

method_info* Leitor::getMethod(string name, string descriptor){
	method_info method;

	for(int i = 0; i < this->methodsCount; i++)
	{
		method = this->methods[i];
		string method_name = dereferenceIndex(this->constantPool, method.name_index);
		string method_desc = dereferenceIndex(this->constantPool, method.descriptor_index);

		if(descriptor == method_desc && name == method_name) 
		{
			return methods+i;
		}
	}

	if(getSuper_class() == 0) 
	{
		return NULL;
	}
	else 
	{
		ClasseEstatica* a = MethodArea::getClass(dereferenceIndex(this->constantPool, getSuper_class()));
		Leitor* l = a->getDef();
		
		return l->getMethod(name, descriptor);
	}
}

Leitor* Leitor::getClassThatHasSerachedMethod(string name, string descriptor){
	method_info* method;

	for(int i = 0; i < this->methodsCount; i++)
	{
		method = (this->methods)+i;

		string method_name = dereferenceIndex(this->constantPool, method->name_index);
		string method_desc = dereferenceIndex(this->constantPool, method->descriptor_index);

		if(descriptor == method_desc && name == method_name) 
		{
			return this;
		}
	}

	if(getSuper_class() == 0) {
		return NULL;
	}
	else {
		Leitor* l = MethodArea::getClass(dereferenceIndex(this->constantPool, getSuper_class()))->getDef();
		return l->getClassThatHasSerachedMethod(name, descriptor);
	}
}
