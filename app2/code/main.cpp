#include <iostream>
#include <map>
#include <queue>
#include <fstream>
#include <vector>
#include <memory>
#include <unistd.h>

#include "tablePageFuncs.hpp"
#include "FIFO.hpp"
#include "LRU.hpp"
#include "LRU_CLOCK.hpp"
#include "OPTIMAL.hpp"

std::vector<int> read_references(const std::string& file_name)
{
    std::ifstream file(file_name);
    std::vector<int> references;

    if(!file.is_open())
    {
        std::cout << "Error leyendo archivo " << file_name << "\n";
        return {};
    }

    int page_number;
    while(file >> page_number)
    {
        references.push_back(page_number);
    }

    file.close();
    return references;
}

std::unique_ptr<ReplacementAlgorithm> create_algorithm(const std::string& algorithm_name)
{
    if(algorithm_name == "FIFO")
    {
        std::cout << "Se seleccionó algoritmo FIFO" << "\n";
        return std::make_unique<FIFO>();
    } else if(algorithm_name == "Optimo") {
        std::cout << "Se seleccionó algoritmo Optimo" << "\n";
        return std::make_unique<OPTIMAL>();
    } else if(algorithm_name == "LRU") {
        std::cout << "Se seleccionó algoritmo LRU" << "\n";
        return std::make_unique<LRU>();
    } else if(algorithm_name == "LRU_Reloj_Simple") {
        std::cout << "Se seleccionó algoritmo LRU Reloj Simple" << "\n";
        return std::make_unique<LRU_CLOCK>();
    } else {
        throw std::invalid_argument("Algoritmo no soportado: " + algorithm_name);
    }

}

int main(int argc, char* argv[])
{
    int opt;
    int total_frames = 0;
    std::string algorithm;
    std::string references_file;

    while ((opt = getopt(argc, argv, "m:a:f:")) != -1)
    {
        switch (opt)
        {
            case 'm': 
                total_frames = std::stoi(optarg);
                break;
            case 'a': 
                algorithm = optarg;
                break;
            case 'f': 
                references_file = optarg;
                break;
            default:
                std::cout << "Uso correcto: ./mvirtual -m <marcos> -a <algoritmo> -f <referencias>\n";
                return 1;
        }
    }

    if (total_frames == 0 || algorithm.empty() || references_file.empty())
    {
        std::cout << "Faltan parámetros requeridos. Uso correcto: ./mvirtual -m <marcos> -a <algoritmo> -f <referencias>\n";
        return 1;
    }

    std::map<int, int> page_table; // -> tabla vacía y sin mapeos npv -> nmp, luego fallo de pagina para cada 1er acceso
    auto replacement_algorithm = create_algorithm(algorithm);
    std::vector<int> references = read_references(references_file);


    int page_faults = 0;
    for(int page_number : references)
    {
        handle_page_access(page_table, page_number, *replacement_algorithm, total_frames, page_faults);
    }

    std::cout << "\n";
    std::cout << "Estado final de la tabla de páginas: " << "\n";
    std::cout << "\n";
    print_page_table(page_table);
    std::cout << "\n";
    std::cout << "TOTAL DE FALLOS DE PÁGINA: " << page_faults << "\n";
    
    return 0;
}