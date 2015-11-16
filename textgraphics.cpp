#include <iostream>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string>
#include <vector>
class Textgrafs{
public:
  Textgrafs();
  ~Textgrafs();
  void print_row(std::string, int);
  void print_col(std::string, int);
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
    grid = new char*[rows_]; 
    for(int i = 0; i < rows_; ++i){
      grid[i] = new char[cols_];
    }
  }
Textgrafs::~Textgrafs(){
  for(int i = 0; i < rows_; ++i){
    delete[] grid[i];
  }
  delete[] grid;
}

int main(){
  Textgrafs p();
}
