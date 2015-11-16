#include <iostream>
#include <sys/ioctl.h>
#include <string>

void print_row(std::string, int, int);
static int ROWS;
static int COLS;
int main(){
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  ROWS = w.ws_row;
  COLS = w.ws_col;
  std::cout << w.ws_row << std::endl;
  std::cout << w.ws_col << std::endl;
  print_row("he", 0, 0);
}

void print_row(std::string text, int px, int py){
  std::string s;
  s.resize(ROWS);
  std::cout << s << std::endl;
  //std::cout << "ssssssssssssssssssssssss" << std::endl;
}
