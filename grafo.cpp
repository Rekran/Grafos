#include "grafo.h"

grafo::grafo(int size){

  this->size = size;

  this->matrix = new int* [10];
    
  for (int i=0; i < 10; i++)
    this->matrix[i] = new int[10];
  
  for (int i=0; i < 10; i++){
    for (int j=0; j < 10; j++){
            
      this->matrix[i][j] = 0;
    }
  }
}
int grafo::getSize(){

  return this->size;
}

void grafo::print(){
  for (int i=0; i < 10; i++){
    for (int j=0; j < 10; j++){

      cout << this->matrix[i][j] << " ";
    }
        cout << endl;
  }
}

grafo::grafo(){

}

grafo::~grafo(){
  for (int i=0; i < 10; i++)
    delete(this->matrix[i]);
  
  delete(this->matrix);
}