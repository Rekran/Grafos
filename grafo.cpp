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
        this->size_ = int(value[0]) - 48;
        this->adj_ = new std::list<int>[this->size_];
        continue;
      };

      std::vector<char> line;

      for ( int i = 0; i < value.length(); ++i ) {
        if ( value[i] == ' ') continue;
        line.push_back(value[i]);
      }

      this->matrix_.push_back(line);
    }


    for ( int i = 0; i < this->getSize(); ++ i ) {
      for ( int j = 0; j < this->getSize(); ++j ) {
        if ( this->matrix_[i][j] == '1') {
          this->adj_[i].push_back(j+1);
        }
      }
    }

  }
}

void Grafo::dfs( const int& edge ) {
  std::cout << "entrou aqui" << this->adj_[edge].size() << std::endl;

  for ( int edges : this->adj_[edge] ) {
    std::cout << "vertices: " << edges << std::endl;
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
