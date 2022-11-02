#include "grafo.h"
#include <queue>

Grafo::Grafo( void ) {

}

Grafo::Grafo( const string& file ) {
   std::ifstream text(file);

  if ( text.is_open() ) {
    std::string value;
    text >> this->size_;
    while( !text.eof() ) {
      std::getline(text, value);

      bool resultado = value[0] == '0' || value[0] == '1';

      if ( !resultado ) {
        this->adj_ = new std::list<int>[this->size_];
        continue;
      };

      std::vector<int> line;

      for ( int i = 0; i < value.length(); ++i ) {
        if ( value[i] == ' ') continue;
        line.push_back(value[i]-48);
      }

      this->matrix_.push_back(line);
    }


    for ( int i = 0; i < this->getSize(); ++ i ) {
      for ( int j = 0; j < this->getSize(); ++j ) {
        if ( this->matrix_[i][j] == 1) {
          this->adj_[i].push_back(j);
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

void Grafo::bfs( const int& edge ) {
  
  std::queue<int> fila;
  int Times[this->size_] = {0};
  int Nivel[this->size_] = {0};
  int Pai[this->size_] = {0};

  int time = 1;
  fila.push(edge);
  
  Times[edge] = time;

  int v = 0 ;

  std::ofstream f_out;
  f_out.open("teste.gdf");
  if(! f_out.good())
    cout << "Falha ao criar o arquivo!"<< std::endl;
  else 
    cout << "Arquivo criado!"<< std::endl;

  while (!fila.empty()){
    v = fila.front();
    fila.pop();

    for ( int edges : this->adj_[v] ) {
      if (Times[edges] == 0){
        if (this->matrix_[v][edges] == 1){
          this->matrix_[v][edges] = 2;
          this->matrix_[edges][v] = 2;
        }
        
        fila.push(edges);
        time = time + 1;
        Times[edges] = time;
      }else{
        if (Nivel[v] == Nivel[edges]){
          if(Pai[v] == Pai[edges]){
            if (this->matrix_[v][edges] == 1){
              this->matrix_[v][edges] = 3;
              this->matrix_[edges][v] = 3;
            }
          }else{
            if (this->matrix_[v][edges] == 1){
              this->matrix_[v][edges] = 4;
              this->matrix_[edges][v] = 4;
            }
          }
          
        }else{
          if (Nivel[edges] == Nivel[v]+1){
            if (this->matrix_[v][edges] == 1){
              this->matrix_[v][edges] = 5;
              this->matrix_[edges][v] = 5;
            }
          }
        }
      }
    }
  }
  f_out << "nodedef>name VARCHAR,label VARCHAR"<< std::endl;

  for (int i = 0; i < this->size_; i++){
   f_out << i+1 <<','<<  i+1 <<std::endl;
  }
  f_out << "edgedef>node1 VARCHAR,node2 VARCHAR,directed BOOLEAN,color VARCHAR"<< std::endl;


  for (int i = 0; i < this->getSize(); i++){
    for (int j = i; j < this->getSize(); j++){
      if (this->matrix_[i][j] == 2){
        f_out << i+1 <<','<< j+1 <<",false"<<",'0,0,255'"<< std::endl;
        this->matrix_[i][j] = 1;
        this->matrix_[j][i] = 1;
      }
      if (this->matrix_[i][j] == 3){
        f_out << i+1 <<','<< j+1 <<",false"<<",'255,0,0'"<< std::endl;
        this->matrix_[i][j] = 1;
        this->matrix_[j][i] = 1;
      }
      if (this->matrix_[i][j] == 4){
        f_out << i+1 <<','<< j+1 <<",false"<<",'0,255,255'"<< std::endl;
        this->matrix_[i][j] = 1;
        this->matrix_[j][i] = 1;
      }
      if (this->matrix_[i][j] == 5){
        f_out << i+1 <<','<< j+1 <<",false"<<",'0,255,0'"<< std::endl;
        this->matrix_[i][j] = 1;
        this->matrix_[j][i] = 1;
      }
    }
  }
  

}  


void Grafo::showAdjacency( const int& edge ) {
  
  std::cout << "vertice: " << edge << " => ";
    for ( int edges : this->adj_[edge] ) {
    std::cout << edges << " ";
    }
  std::cout << std::endl;

}

void Grafo::showAdjacency( void ) {
  for (int i = 0; i < this->getSize(); i++){
    std::cout << "vertice: " << i << " => ";
    for ( int edges : this->adj_[i] ) {
    std::cout << edges << " ";
    }
  std::cout << std::endl;
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
