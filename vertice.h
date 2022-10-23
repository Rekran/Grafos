#include <string>

class Vertice {
  public:
    Vertice() {};
    Vertice( int father, int level, std::string type );
  private:
    int father;
    int level;
    std::string type;
};