#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class Grafo {
  public:
    Grafo( void );
    Grafo( const string& file );
    
    inline int getSize( void ) const;

    void dfs( const int& vertice );
    void showMatrix( void );
    void showAdjacency( const int& edge );

  private:
    int size_;
    std::vector<std::vector<char>> matrix_;
    std::list<int>* adj_;
};