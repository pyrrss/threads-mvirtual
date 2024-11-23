#ifndef LRU_H
#define LRU_H

#include <iostream>
#include <map>
#include <list>

#include "ReplacementAlgorithm.hpp"

class LRU : public ReplacementAlgorithm{
    private:
        std::list<int> lru_list; 
    public:
        LRU() = default;
        int replace_page(std::map<int, int>& page_table) override;
        void handle_page_reference(int virtual_page) override;

};



#endif 