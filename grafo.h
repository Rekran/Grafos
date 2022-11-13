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
    void dfstoFile( const int& vertice );
    void bfstoFile( const int& vertice );
    void bfs( const int& vertice );
    void showMatrix( void );
    void showAdjacency( void );
    void showAdjacency( const int& edge );
    void busca( const int& edge, int* PE, int* PS, int* Pai );
    void calcEccentricity( void );
    int diametre( void );
    int raio( void );

  private:
    int size_;
    std::vector<std::vector<int>> matrix_;
    std::vector<int> eccentricity_;
    std::list<int>* adj_;
};