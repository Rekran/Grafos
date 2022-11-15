#include "grafo.h"
#include <queue>
#include <stack>

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

    for ( int i = 0; i < this->getSize(); ++ i ){
      this->eccentricity_.push_back(-1);
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

void Grafo::busca( const int& v, int* PE, int* PS, int* Pai ) {
  static int time = 1;
  PE[v] = time;

  for ( int edges : this->adj_[v] ) {
    if ( PE[edges] == 0 ) {
      if ( this->matrix_[v][edges] == 1 ) {
        this->matrix_[v][edges] = 2;
        this->matrix_[edges][v] = 2;
      }
      Pai[edges] = v;
      busca( edges, PE, PS, Pai );
    }else {
      if ( PS[edges] == 0 && edges != Pai[v] ) {
        if ( this->matrix_[v][edges] == 1 ) {
          this->matrix_[v][edges] = 3;
          this->matrix_[edges][v] = 3;
        }
      }
    }
  }

  time = time + 1;
  PS[v] = time;
}

void Grafo::dfstoFile( const int& edge ) {
  std::stack<int> pilha;

  int Profunidade_entrada[this->size_];
  int Profunidade_saida[this->size_];
  int Pai[this->size_];

  for ( int i = 0; i < this->size_; ++i ) {
    Profunidade_entrada[i] = 0;
  }

  for ( int i = 0; i < this->size_; ++i ) {
    Profunidade_saida[i] = 0;
  }

  for ( int i = 0; i < this->size_; ++i ) {
    Pai[i] = 0;
  }

  int v = 0;
  int time = 0;

  pilha.push(edge);

  std::ofstream f_out;
  f_out.open("teste_dfs.gdf");
  //if(! f_out.good())
  //  cout << "Falha ao criar o arquivo!"<< std::endl;
  //else 
  //  cout << "Arquivo criado!"<< std::endl;

  this->busca( edge, Profunidade_entrada, Profunidade_saida, Pai );

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
    }
  }
}

void Grafo::bfstoFile( const int& edge ) {
  
  std::queue<int> fila;
  int Times[this->size_];
  int Nivel[this->size_];
  int Pai[this->size_];

  for ( int i = 0; i < this->size_; ++i ) {
    Times[i] = 0;
  }

  for ( int i = 0; i < this->size_; ++i ) {
    Nivel[i] = 0;
  }

  for ( int i = 0; i < this->size_; ++i ) {
    Pai[i] = 0;
  }

  int time = 1;
  fila.push(edge);
  
  Times[edge] = time;

  int v = 0 ;

  std::ofstream f_out;
  f_out.open("teste_bfs.gdf");
  //if(! f_out.good())
  //  cout << "Falha ao criar o arquivo!"<< std::endl;
  //else 
  //  cout << "Arquivo criado!"<< std::endl;

  while (!fila.empty()){
    v = fila.front();

    fila.pop();

    for ( int edges : this->adj_[v] ) {
      if (Times[edges] == 0){
        if (this->matrix_[v][edges] == 1){
          this->matrix_[v][edges] = 2;
          this->matrix_[edges][v] = 2;
        }
        
        time = time + 1;
        Times[edges] = time;
        Pai[edges] = v;
        Nivel[edges] = Nivel[v] + 1;
        fila.push(edges);
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
              this->matrix_[v][edges] =    5;
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
        f_out << i+1 <<','<< j+1 <<",false"<<",'255,255,0'"<< std::endl;
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
  if (this->eccentricity_[edge] == -1){
    int max = 0;
    for ( int i : Nivel ){
      if (i> max){
        max = i;
      }
    }
    this->eccentricity_[edge] = max;
  }
  

}  

void Grafo::bfs( const int& edge ) {
  
  std::queue<int> fila;
  int Times[this->size_];
  int Nivel[this->size_];
  int Pai[this->size_];

  for ( int i = 0; i < this->size_; ++i ) {
    Times[i] = 0;
  }

  for ( int i = 0; i < this->size_; ++i ) {
    Nivel[i] = 0;
  }

  for ( int i = 0; i < this->size_; ++i ) {
    Pai[i] = 0;
  }

  int time = 1;
  fila.push(edge);
  
  Times[edge] = time;

  int v = 0 ;

  while (!fila.empty()){
    v = fila.front();

    fila.pop();

    for ( int edges : this->adj_[v] ) {
      if (Times[edges] == 0){
        if (this->matrix_[v][edges] == 1){
          this->matrix_[v][edges] = 2;
          this->matrix_[edges][v] = 2;
        }
        
        time = time + 1;
        Times[edges] = time;
        Pai[edges] = v;
        Nivel[edges] = Nivel[v] + 1;
        fila.push(edges);
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
              this->matrix_[v][edges] =    5;
              this->matrix_[edges][v] = 5;
            }
          }
        }
      }
    }
  }

  if (this->eccentricity_[edge] == -1){
    int max = 0;
    for ( int i : Nivel ){
      if (i> max){
        max = i;
      }
    }
    this->eccentricity_[edge] = max;
  }
}

void Grafo::calcEccentricity( void ){
  for (int i = 0; i < this->getSize(); i++){
    if (this->eccentricity_[i] == -1){
      this->bfs(i);
    }
  }
}

int Grafo::diametre( void ){
  this->calcEccentricity();
  return *std::max_element(this->eccentricity_.begin(),this->eccentricity_.end());
}

int Grafo::raio( void ){
  this->calcEccentricity();
  return *std::min_element(this->eccentricity_.begin(),this->eccentricity_.end());
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
