#include "grafo.h"

Grafo::Grafo( void ) {

}

Grafo::Grafo( const string& file ) {
   std::ifstream text("arquivo.txt");

  if ( text.is_open() ) {
    std::string value;

    while( !text.eof() ) {
      std::getline(text, value);

      bool resultado = value[0] == '0' || value[0] == '1';

      if ( !resultado ) {
        int sizeFormatted = 
        this->size_ = this->changeCharToInt(value[0]);
        this->adj_ = new std::list<int>[this->size_];
        continue;
      };

      std::vector<int> line;

      for ( int i = 0; i < value.length(); ++i ) {
        if ( value[i] == ' ') continue;
        line.push_back( this->changeCharToInt(value[i]) );
      }

      this->matrix_.push_back( line );
    }


    for ( int i = 0; i < this->getSize(); ++ i ) {
      for ( int j = 0; j < this->getSize(); ++j ) {
        if ( this->matrix_[i][j] == 1) {
          this->adj_[i].push_back( j );
        }
      }
    }

  }
}

void Grafo::dfs( const int& vertice, std::vector<int>& visited ) {
  visited.push_back( vertice );

  std::cout << "visitado: " << vertice << std::endl;

  for ( int edges : this->adj_[vertice] ) {
    if ( !(std::find(visited.begin(), visited.end(), edges) != visited.end()) ) {
      this->dfs(edges, visited);
    }
  }
}

void Grafo::showAdjacency( const int& edge ) {
  for ( int edges : this->adj_[edge] ) {
    std::cout << "vertices: " << edges << std::endl;
  }
}


void Grafo::showMatrix( void ) {
  for ( int i = 0; i < this->size_; i++ ) {
    for ( int j = 0; j < this->size_; j++ ) {
      std::cout << this->matrix_[i][j] << " ";
    }
    std::cout << endl;
  }
}


inline int Grafo::getSize( void ) const {
  return this->size_;
}

int Grafo::changeCharToInt( const char& ch ) {
  return int(ch) - 48;
}
