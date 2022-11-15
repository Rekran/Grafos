#include "grafo.h"

/*
    Universidade Federal da Paraíba
    Trabalho da disciplina de Grafos
    Tema: Busca em Grafos
    Linguagem Utilizada: C++.
    Desenvolvido por:
    
        Arthur Ricardo, 20170033039
        Danilo Henrique, 20170140478
*/

int main( void ) {

    Grafo test = Grafo("graph_13.txt");
    
    test.bfstoFile(0);
    test.dfstoFile(0);

    std::cout<< "Raio: "<< test.raio() << std::endl;
    std::cout<< "Diametro: " << test.diametre() << std::endl;
    
    return 0;
} 