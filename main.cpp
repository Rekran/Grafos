#include "grafo.h"


int main() {

    Grafo test = Grafo("graph_13.txt");
    
    test.bfstoFile(0);
    test.dfstoFile(0);

    std::cout<< "Raio: "<< test.raio() << std::endl;
    std::cout<< "Diametro: " << test.diametre() << std::endl;
    
    return 0;
} 