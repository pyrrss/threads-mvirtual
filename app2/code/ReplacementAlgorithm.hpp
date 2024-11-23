#ifndef REPLACEMENT_H
#define REPLACEMENT_H

#include <map>

class ReplacementAlgorithm{
    public:
        virtual int replace_page(std::map<int, int>& page_table) = 0; // -> decide página víctima y devuelve marco de página que tenía asignado
        virtual void handle_page_reference(int virtual_page) = 0; // -> maneja referencia a página virtual
};


#endif