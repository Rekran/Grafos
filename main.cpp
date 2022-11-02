#include "grafo.h"


int main() {

    Grafo test = Grafo("arquivo.txt");
    
   test.bfs(0);

    test.showMatrix();
   
    return 0;
} 