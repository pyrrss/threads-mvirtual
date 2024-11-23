#include <iostream>
#include <algorithm>

#include "LRU.hpp"
#include "tablePageFuncs.hpp"

int LRU::replace_page(std::map<int, int>& page_table)
{
    if(!lru_list.empty())
    {
        int oldest_page = lru_list.back(); 
        lru_list.pop_back(); // -> elimina último elemento (referenciado hace más tiempo)
    
        int freed_frame = page_table[oldest_page];
        remove_page(page_table, oldest_page);

        return freed_frame;
    }

    std::cout << "Lista vacía, esto no debería ocurrir" << "\n";
    return -1;
}

void LRU::handle_page_reference(int virtual_page)
{
    auto lru_virtual_page = std::find(lru_list.begin(), lru_list.end(), virtual_page);

    if(lru_virtual_page != lru_list.end()) // -> si está en lru_list, se elimina para luego colocarla al frente
    {
        lru_list.erase(lru_virtual_page);
    }

    lru_list.push_front(virtual_page); // -> se coloca al frente de lru_list


    std::cout << "Estado actual de lru_list: " << "\n";
    for(const auto& page : lru_list)
    {
        std::cout << page << " ";
    }

    std::cout << "\n";

}