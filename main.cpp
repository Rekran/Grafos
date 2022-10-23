#include "grafo.h"


int main() {
    std::ifstream text("arquivo.txt");
    std::vector<int> visited;

    Grafo test = Grafo("arquivo.txt");
    test.showMatrix();

    test.dfs(0, visited);
    return 0;
} 