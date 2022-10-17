#include "grafo.h"


int main() {
    std::ifstream text("arquivo.txt");

    Grafo test = Grafo("arquivo.txt");
    test.showMatrix();

    test.dfs(0);
    return 0;
} 