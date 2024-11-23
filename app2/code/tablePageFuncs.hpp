#ifndef TABLEPAGE_H
#define TABLEPAGE_H

#include <iostream>
#include <map>

#include "FIFO.hpp"

// -> Verifica si la página virtual está o no en memoria
bool is_page_present(std::map<int, int>& table_page, int virtual_page); 

// -> Inserta página virtual en tabla de páginas y asigna un marco de pagina, usar con algoritmo de reemplazo
void insert_page(std::map<int, int>& table_page, int virtual_page, int physical_frame, ReplacementAlgorithm& replacement_algorithm);

// -> Eliminar página virtual de tabla, usar con algoritmo de reemplazo
void remove_page(std::map<int, int>& table_page, int virtual_page);

void handle_page_access(std::map<int, int>& table_page, int virtual_page, ReplacementAlgorithm& replacement_algorithm, int total_frames, int& page_faults);

void print_page_table(std::map<int, int>& table_page);


#endif