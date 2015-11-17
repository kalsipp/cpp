#include <iostream>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string>
#include <vector>
class Textgrafs{
public:
  Textgrafs();
  ~Textgrafs();
  void add_row(std::string, int, int);
  void add_col(std::string, int, int);
  void print();
  bool next_tick();
private:
  int tick_counter_= 0;
  int framerate_ = 30000000;
  int rows_;
  int cols_;
  //char** grid;
  std::vector<std::string> grid;
};

Textgrafs::Textgrafs(){
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  rows_ = w.ws_row;
  cols_ = w.ws_col;
  std::string s(cols_, ' ');
  grid.resize(rows_,s);
  //  grid = new char*[cols_]; 
  // for(int i = 0; i < cols_; ++i){
  // grid[i] = new char[rows_];
  //  }
}
Textgrafs::~Textgrafs(){
  
  //for(int i = 0; i < rows_; ++i){
  //delete[] grid[i];
  //}
  //delete[] grid;
}
void Textgrafs::print(){
  if(next_tick()){
    for(int i = 0; i < rows_ ; ++i){
      std::cout << grid[i] << std::endl;
    }
  }
}
bool Textgrafs::next_tick(){
  ++tick_counter_;
  if(tick_counter_ > framerate_){
    tick_counter_ = 0;
    return true;
  }
  else{
    return false;
  }
}
void Textgrafs::add_row(std::string text, int px, int py){
  grid[py].replace(px, text.length(), text);
}
void Textgrafs::add_col(std::string text, int px, int py){
  const char * p = text.c_str();
  const char * k = p[0];
  for(int i = 0;  i < text.length(); ++i){
    grid[i].replace(px, 0, k);
  }
}
int main(){
  Textgrafs p;
  p.add_row("hehe", 10, 10);
  p.add_col("huehue", 20, 20);
  while(1){
    //p.add_row("hehe", 10, 10);
    p.print();
  }
}

