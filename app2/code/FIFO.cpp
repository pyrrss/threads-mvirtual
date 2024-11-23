#include <iostream>
#include <queue>
#include <map>

#include "FIFO.hpp"
#include "tablePageFuncs.hpp"


int FIFO::replace_page(std::map<int, int>& page_table) 
{
    if(!fifo_queue.empty())
    {
        int oldest_page = fifo_queue.front();
        fifo_queue.pop();

        int freed_frame = page_table[oldest_page];
        remove_page(page_table, oldest_page);

        return freed_frame;
    }

    std::cout << "Cola vacía, esto no debería pasar jeje" << "\n";
    return -1;
}

void FIFO::handle_page_reference(int virtual_page)
{
    fifo_queue.push(virtual_page);
}