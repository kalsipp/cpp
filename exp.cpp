#include <iostream>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string>

void print_row(std::string, int);
void print_col(std::string, int);
static int ROWS;
static int COLS;
int main(){
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  ROWS = w.ws_row;
  COLS = w.ws_col;
  std::cout << w.ws_row << std::endl;
  std::cout << w.ws_col << std::endl;
  print_row("heeeeeeeeeeee", -5);
}

void print_row(std::string text, int px){
  int len = 0;
  if(px < 0){
    text.erase(0,abs(px));
    px = 0;
  }
  if(px + text.length() > ROWS){
    len = ROWS-px-1;
  }
  else{
    len = text.length();
  }
  std::cout << len << std::endl;
  std::string s(ROWS, ' ');
  if(len > 0){
    s.replace(px, text.length(),text);
  }
  std::cout << s << std::endl;
}
void print_col(std::string text, int py){
  int len = 0;
  if(py+text.length() > COLS){
    len = ROWS-py-1;
    if(len < 0){
      len = 0;
    }
    std::cout << "too big " << len << std::endl;
  }
  else{
    len = text.length();
    std::cout << "good enough " << std::endl;
  }
  std::string s(COLS, ' ');
  s.replace(py, len, text);
  std::cout << s << std::endl;
}
