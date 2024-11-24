#ifndef OPTIMAL_H
#define OPTIMAL_H

#include <vector>
#include <map>
#include "ReplacementAlgorithm.hpp"

class OPTIMAL : public ReplacementAlgorithm {
    private:
        std::vector<int> page_references;
        int current_reference;

    public:
        OPTIMAL() = default;
        void set_references(const std::vector<int>& references);
        int replace_page(std::map<int, int>& page_table) override;
        void handle_page_reference(int virtual_page) override;
};

#endif
