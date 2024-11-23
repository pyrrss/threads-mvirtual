#ifndef FIFO_H
#define FIFO_H

#include <iostream>
#include <queue>
#include <map>

#include "ReplacementAlgorithm.hpp"

class FIFO : public ReplacementAlgorithm{    
    private:
        std::queue<int> fifo_queue;
    public:
        FIFO() = default;
        int replace_page(std::map<int, int>& page_table) override;
        void handle_page_reference(int virtual_page) override;
};


#endif

