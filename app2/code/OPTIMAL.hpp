#ifndef OPTIMAL_H
#define OPTIMAL_H

#include <iostream>
#include <map>
#include <list>

#include "ReplacementAlgorithm.hpp"

class OPTIMAL : public ReplacementAlgorithm{
    private:
        
    public:
        OPTIMAL() = default;
        int replace_page(std::map<int, int>& page_table) override;
        void handle_page_reference(int virtual_page) override;
};



#endif 