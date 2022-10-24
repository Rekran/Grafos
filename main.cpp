#include "grafo.h"


int main() {
    std::ifstream text("arquivo.txt");

    Grafo test = Grafo("arquivo.txt");
    test.showAdjacency(0);
    test.bfs(0);
    return 0;
} 