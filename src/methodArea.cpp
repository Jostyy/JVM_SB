#include "../include/methodArea.h"

map<string, ClasseEstatica*> MethodArea::classes;
string MethodArea::path = "";
FrameStack *MethodArea::fs = nullptr;

ClasseEstatica *MethodArea::getClass(string s){    
    for (map<string, ClasseEstatica*>::const_iterator i = classes.begin(); i != classes.end(); i++)
        if (i->first == s)
            return i->second;

    return nullptr;
}

bool MethodArea::addClass(Leitor *l){
    if (l->getStatus() == -1)
        l->load();

    switch (l->getStatus()){
        case 0:
            break;
        default:
            return false;
    }

    ClasseEstatica *add = new ClasseEstatica(l);
    classes.insert(pair<string, ClasseEstatica*>(dereferenceIndex(l->getCP(), l->getThis_class()), add));

    if (l->hasClinit())
        fs->addFrame(l->getClinit(), l->getCP());

    return true;
}

bool MethodArea::addClass(string s){
    for(map<string, ClasseEstatica*>::const_iterator i = classes.begin(); i != classes.end(); i++)
       if(i->first == s)
            return false;

    Leitor *l = new Leitor(string(path+s));


    if(!l->validExtension()){
        delete l;
        l = new Leitor(string(path+s+".class"));
    }

    if(l->load())
        return false;

    ClasseEstatica *add = new ClasseEstatica(l);
    classes.insert(pair<string, ClasseEstatica*>(s, add));

    if (l->hasClinit())
        fs->addFrame(l->getClinit(), l->getCP());

    return true;
}

void MethodArea::setFrameStack(FrameStack *newFS){
    fs = newFS;
}