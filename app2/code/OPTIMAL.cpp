#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <strings.h>

#include "OPTIMAL.hpp"
#include "tablePageFuncs.hpp"

// Función que establece el vector de referencias de páginas
void OPTIMAL::set_references(const std::vector<int>& references) {
    page_references = references;  // Asigna el vector de referencias
    current_reference = 0;
}

int OPTIMAL::replace_page(std::map<int, int>& page_table) 
{
    int page_to_replace = -1;
    int freed_frame = -1;
    int equal_pages = 0;
    int in_major_distance = -1;

    //std::cout<<current_reference<<std::endl;
    //itera sobre las paginas de los marcos y revisa si a futuro aparece una pagina de un marco, si ocurre guarda el subindice de la pagina futura
    for (const auto& entry : page_table) {
        for(int i = current_reference+1; i < page_references.size(); i++){
            if(page_references[i] == entry.first){
                if(in_major_distance < i){
                    in_major_distance=i;
                    //std::cout<<in_major_distance<<std::endl;
                }
                ++equal_pages;
                break;
            }
            else if(i == page_references.size()-1){
                page_to_replace = entry.first;
            }
        }
    }

    //si pasa por todos los marcos guarda la pagina a reemplazar
    if(equal_pages == page_table.size()){
        page_to_replace = page_references[in_major_distance];
    }
    //si no pasa por todos los marcos entonces considera los marcos que no tienen pagina que se referencian a futuro, para guardar la pagina en cualquiera que cumplan no estar referenciada a futuro
    //else{}

    //std::cout<<page_to_replace<<std::endl;
    //guarda el marco de pagina
    freed_frame = page_table[page_to_replace];
    //std::cout<<freed_frame<<std::endl;
    remove_page(page_table, page_to_replace);

    return freed_frame;  // Retorna el marco de memoria liberado
}

// Función para manejar la referencia a la página virtual
void OPTIMAL::handle_page_reference(int virtual_page) {
    ++current_reference;
}