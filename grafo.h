#include <iostream>
using namespace std;

class grafo {

  private:
    int size;
    int **matrix;  
  
  public:
    int getSize();


    grafo(int size);
    void print();

    grafo();
    ~grafo();
};