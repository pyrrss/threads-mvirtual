#include <iostream>
#include <map>
#include <algorithm>

#include "LRU_CLOCK.hpp"
#include "tablePageFuncs.hpp"


LRU_CLOCK::LRU_CLOCK()
{
    clock_pointer = clock_list.end();
}



int LRU_CLOCK::replace_page(std::map<int, int>& page_table)
{
    // -> idea es iterar sobre lista circular hasta encontrar página con bit R == 0
    while(true) {

        if(clock_pointer == clock_list.end())
        {
            clock_pointer = clock_list.begin(); // -> si puntero apunta al final, vuelve a inicio
        }

        int current_page = *clock_pointer; // -> página apuntada actualmente
        auto current_page_index = std::distance(clock_list.begin(), clock_pointer); // -> índice de página apuntada
        if(reference_bits[current_page_index] == 1) // -> si bit R == 1, se coloca a 0
        {
            reference_bits[current_page_index] = 0;
            clock_pointer++;
        } else { // -> R == 0, página víctima

            std::cout << "PÁGINA VÍCTIMA: " << current_page << "\n";

            int assigned_frame = page_table[current_page];
            
            clock_pointer = clock_list.erase(clock_pointer);
            reference_bits.erase(reference_bits.begin() + current_page_index);

            if (clock_pointer == clock_list.end())
            {
                clock_pointer = clock_list.begin(); 
            }
            last_victim_index = std::distance(clock_list.begin(), clock_pointer);
            remove_page(page_table, current_page);
            
            std::cout << "last victim index: " << last_victim_index << "\n";
            
            return assigned_frame;

        }
    }


}

void LRU_CLOCK::handle_page_reference(int virtual_page)
{

    auto it = std::find(clock_list.begin(), clock_list.end(), virtual_page);
    if(it != clock_list.end()) // ->  página ya en memoria, R = 1
    {
        auto virtual_page_index = std::distance(clock_list.begin(), it);
        reference_bits[virtual_page_index] = 1; // -> si está en memoria entonces R = 1
    } else { // -> no está en memoria

        if (last_victim_index != -1) // -> != -1 si se eliminó página víctima previamente
        {
            auto insert_it = clock_list.begin();
            std::advance(insert_it, last_victim_index);
            clock_list.insert(insert_it, virtual_page);
            reference_bits.insert(reference_bits.begin() + last_victim_index, 1);

            clock_pointer = clock_list.begin(); // -> clock_pointer apunta a nueva página que reemplaza a víctima
            std::advance(clock_pointer, last_victim_index);
            last_victim_index = -1; 
        } else { // -> no página víctima, luego se inserta al final de lista circular y R = 1
            
            clock_list.push_back(virtual_page);
            reference_bits.push_back(1);

            if (clock_pointer == clock_list.end()) 
            {
                clock_pointer = clock_list.begin();
            }

        }
        
       
    }


    std::cout << "Estado actual cola circular: " << "\n";

    for(const auto& page : clock_list)
    {
        std::cout << page << " ";
    }
    std::cout << "\n";

    std::cout << "Bits de referencia: " << "\n";
    auto print_it = clock_list.begin();
    for (int i = 0; i < reference_bits.size(); i++)
    {
        std::cout << *print_it << ": " << reference_bits[i] << "\n";
        print_it++;
    }

    
    if (clock_pointer != clock_list.end()) {
        std::cout << "Clock Pointer apuntando a: " << *clock_pointer << "\n";
    } else {
        std::cout << "Clock Pointer apuntando al final de la lista.\n";
    }
}
