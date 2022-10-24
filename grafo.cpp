#include "grafo.h"
#include <queue>

Grafo::Grafo( void ) {

}

Grafo::Grafo( const string& file ) {
   std::ifstream text("arquivo.txt");

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
  

  cout<< this->size_<<std::endl;

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

  f_out << "nodedef>name VARCHAR,label VARCHAR"<< std::endl;
  for (int i = 0; i < this->size_; i++){
    f_out << i+1 <<','<<  i+1 <<std::endl;
  }
  

  f_out << "edgedef>node1 VARCHAR,node2 VARCHAR,directed BOOLEAN,color VARCHAR"<< std::endl;

  while (!fila.empty()){
    v = fila.front();
    fila.pop();

    for ( int edges : this->adj_[v] ) {
      if (Times[edges] == 0){
        Pai[edges] = v;
        Nivel[edges] = Nivel[v] + 1;
        time = time + 1;
        Times[edges] = time;
        fila.push(edges);
        f_out << v+1 <<','<< edges+1 <<",false"<<",'0,0,255'"<< std::endl;
      }else{
        if (Nivel[v]== Nivel[edges] ){
          if (Pai[v] == Pai[edges]){
            f_out << v+1 <<','<< edges+1 <<",false"<<",'255,0,0'"<< std::endl;
          }else{
            f_out << v+1 <<','<< edges+1 <<",false"<<",'0,255,255'"<< std::endl;
          }
        }else{
          if (Nivel[v] == Nivel[edge]+1 ){
            f_out << v+1 <<','<< edges+1 <<",false"<<",'0,255,0'"<< std::endl;
          }
        }
      }
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
