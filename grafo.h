#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class Grafo {
  public:
    Grafo( void );
    Grafo( const string& file );
    
    inline int getSize( void ) const;

    void dfs( const int& vertice, std::vector<int>& visited );
    void showMatrix( void );
    void showAdjacency( const int& edge );

    int changeCharToInt( const char& ch );

  private:
    int size_;
    std::vector<std::vector<int>> matrix_;
    std::list<int>* adj_;
};