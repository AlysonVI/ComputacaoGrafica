#include "DisplayFile.h"

DisplayFile::~DisplayFile(){
    for(auto obj : objects) delete obj;
}

void DisplayFile::add(Drawable* obj) {
    objects.append(obj);
}

void DisplayFile::drawAll(QPainter& painter) const {
    for(auto obj : objects)
        obj->draw(painter);
}

void DisplayFile::printAll() const{
    for(auto obj : objects)
        std::cout << "Objeto " << obj->getNome().toStdString() << "\n";
}
