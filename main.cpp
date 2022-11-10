#include "grafo.h"


int main() {

    Grafo test = Grafo("graph_2.txt");
    
   test.bfs(0);

    // test.showAdjacency();

    // test.showMatrix();

   test.dfs(0);

    // test.showMatrix();
   
    return 0;
} 