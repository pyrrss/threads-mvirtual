#ifndef LRUCLOCK_H
#define LRUCLOCK_H

#include <iostream>
#include <vector>
#include <list>
#include <map>

#include "ReplacementAlgorithm.hpp"

class LRU_CLOCK : public ReplacementAlgorithm{
    private:
        std::vector<int> reference_bits; // -> bits de referencia asociados a cada página virtual (0 ó 1)
        std::list<int> clock_list; // -> lista circular de páginas virtuales
        std::list<int>::iterator clock_pointer; // -> puntero que recorre clock_list
        int last_victim_index = -1; // -> indice de última página víctima
    public:
        LRU_CLOCK();
        int replace_page(std::map<int, int>& page_table) override;
        void handle_page_reference(int virtual_page) override;

};



#endif 