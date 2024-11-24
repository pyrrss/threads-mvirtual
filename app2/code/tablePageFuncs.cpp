#include <iostream>
#include <map>

#include "tablePageFuncs.hpp"
#include "LRU.hpp"
#include "LRU_CLOCK.hpp"
#include "OPTIMAL.hpp"

bool is_page_present(std::map<int, int>& page_table, int virtual_page)
{
    return page_table.find(virtual_page) != page_table.end();
} 

void insert_page(std::map<int, int>& page_table, int virtual_page, int physical_frame, ReplacementAlgorithm& replacement_algorithm)
{
    page_table[virtual_page] = physical_frame; 
    replacement_algorithm.handle_page_reference(virtual_page);
}

void remove_page(std::map<int, int>& page_table, int virtual_page)
{
    page_table.erase(virtual_page);
}

void handle_page_access(std::map<int, int>& page_table, int virtual_page, ReplacementAlgorithm& replacement_algorithm, int total_frames, int& page_faults)
{
    if(!is_page_present(page_table, virtual_page))
    {
        page_faults++;

        int assigned_frame = -1;
        if(page_table.size() >= total_frames)
        {
            assigned_frame = replacement_algorithm.replace_page(page_table);
            if(assigned_frame == -1)
            {
                std::cout << "Error, no se pudo reemplazar una pagina" << "\n";
                return;
            }
        } else {
            // -> esto es para asignar marcos físicos distintos a cada pv, quizá se debería cambiar aunque está bien
            assigned_frame = page_table.size() + 1;
        }

        insert_page(page_table, virtual_page, assigned_frame, replacement_algorithm);
        std::cout << "pagina " << virtual_page << " cargada en marco " << assigned_frame
                  << " (fallo de página)" << "\n";
    
    
    } else {
        std::cout << "La página ya está en memoria" << "\n";
    
        // DEBO COLOCAR BIT DE REFERENCIA EN 1 CUANDO PAGINA YA ESTÁ EN MEMORIA

        // -> si se está usando LRU/LRU_CLOCK y la página ya está en memoria, es necesario colocar la página al frente de lru_list
        if(auto lru_algorithm = dynamic_cast<LRU*>(&replacement_algorithm))
        {
            lru_algorithm->handle_page_reference(virtual_page);
        }

        if(auto lru_clock_algorithm = dynamic_cast<LRU_CLOCK*>(&replacement_algorithm))
        {
            lru_clock_algorithm->handle_page_reference(virtual_page);
        }
        if(auto optimal_algorithm = dynamic_cast<OPTIMAL*>(&replacement_algorithm))
        {
            optimal_algorithm->handle_page_reference(virtual_page);
        }
    }

}

void print_page_table(std::map<int, int>& page_table)
{
    for(const auto& entry : page_table)
    {
        std::cout << "virtual page: " << entry.first
                  << " -> physical frame: " << entry.second << "\n";
    }
}