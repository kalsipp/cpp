#include <iostream>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string>
#include <vector>
class Textgrafs{
public:
  Textgrafs();
  ~Textgrafs();
  void add_row(std::string, int);
  void add_col(std::string, int);
  void print();
private:
  int rows_;
  int cols_;
  char** grid;
};

Textgrafs::Textgrafs(){
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  rows_ = w.ws_row;
  cols_ = w.ws_col;
  grid = new char*[cols_]; 
  for(int i = 0; i < cols_; ++i){
    grid[i] = new char[rows_];
  }
}
Textgrafs::~Textgrafs(){
  for(int i = 0; i < rows_; ++i){
    delete[] grid[i];
  }
  delete[] grid;
}
void Textgrafs::print(){
  for(int i = 0; i < cols_ ; ++i){
    std::cout << grid[i] << std::endl;
  }
}
int main(){
  Textgrafs p;
  p.print();
}

