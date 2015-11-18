#include <iostream>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <chrono>
#include <ios>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include "textgraphics.hpp"
void Textgrafs::fun(){
  std::cout << "\033[1;1H" <<std::endl;
}

Textgrafs::Textgrafs(){
  std::cout << std::unitbuf; //Turns off the buffer
  std::ios_base::sync_with_stdio(false); //Turn off sync with in stream

  //Get size of window
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  rows_ = w.ws_row;
  cols_ = w.ws_col;
  //Prepare grid
  std::string s(cols_, ' ');
  grid.resize(rows_,s);
  old_grid.resize(rows_,s);
  //settings
  framerate_ = 100000;
  time_between_frames_ = 0.050;//0.010;
  timer_ = std::chrono::system_clock::now(); //First timepoint
  clear(); //and clear screen
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

void Textgrafs::paint(){
  //add_row(std::to_string(timer_), 1, 1);
  if(next_tick()){
    print();
    save_old_grid();
  }
  clear_grid();
}
void Textgrafs::cursorpos(int px, int py){
  ++px; //escape is 1 base
  ++py;
  std::cout << "\033[" << py << ";" << px << "H";
}
void Textgrafs::hide_cursor(){
}
void Textgrafs::clear(){
  std::cout << "\033[2J";
}
void Textgrafs::save_old_grid(){
  for(int i = 0; i < grid.size() ; ++i){
    if(0!=grid[i].compare(old_grid[i])){
      old_grid[i] = grid[i];
    }
  }
}
void Textgrafs::print(){
    std::string s;
    //cursorpos(0,0);
    s+= "\033[1;1H";
    for(int y = 0; y < rows_ ; ++y){
      s+= grid[y];
      s+= "\n";
    }
    s.pop_back();
    //puts(s.c_str());
    write(1, s.c_str(), s.length());
    //std::cout << s;
    
}
void Textgrafs::clear_grid(){
  std::string s(cols_, ' ');
  for(int i = 0; i < rows_ ; ++i){
    grid[i] = s;
  }
}
bool Textgrafs::next_tick(){
  std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::system_clock::now()-timer_);
  if(debug)add_row(std::to_string(time_span.count()), 0, 0);
//std::cout<< time_span.count();
  if(time_span.count() > time_between_frames_){
    timer_ = std::chrono::system_clock::now();
    return true;
  }
  return false;
  
}
void Textgrafs::add_row(std::string text, int px, int py){
  
  if(py < 0 || py >= rows_){
    return;
  }
  if(px < 0){
    if(abs(px) < text.length()){
      text.erase(0,abs(px));
    }
  }
  if(px >=cols_){
    return;
  }
  if(px + text.length() >= cols_){
    text.erase((cols_-px), text.length());
  }
  if(px >= 0)  grid[py].replace(px, text.length(), text);
  if(px < 0) grid[py].replace(0, text.length(), text);
}
void Textgrafs::add_col(std::string text, int px, int py){
  if(px < 0 || px >= cols_ || py >= rows_){
    return;
  }
  if(py < 0){
    if(abs(py) < text.length()){
      text.erase(0, abs(py)); 
    }
  }
  if(py + text.length() >= rows_){
    text.erase((rows_-py), text.length());
  }
  std::string s;
  for(int i = 0;  i < text.length(); ++i){
    s.assign(text, i, 1);
    grid[i].replace(px, 1, s);
    //TODO fix char * to char error
    //grid[i].replace(px, 1, text[i]);
  }
}
void Textgrafs::add_rect(char letter, int px, int py, int sizex, int sizey){
  std::string s(sizex, letter);
  for(int i = 0; i < sizey; ++i){
    add_row(s, px, py+i);
  }
}

void Textgrafs::add_ellipse(char letter, int px,int py, int rx, int ry){
  //x^2/a^2 + y^2/b^2 = 1
  //TODO make work
  std::vector<std::string> s;
  std::vector<int> starts (ry, -1);
  std::vector<int> ends (rx, -1);
  for(int y = 0; y < ry; ++y){
    for(int x = 0; x < rx; ++x){
      float rad = (x*x)/(rx*rx) + (y*y)/(ry*ry);
      std::cout << "rad " << rad << std::endl;
      if(starts[y] == -1 && rad <= 1){
	starts[y] = x;
      }
      else if(starts[y] != -1 &&  rad > 1){
	ends[y] = x;
      }
    }
  }
  for(int i = 0; i < ry; ++i){
    std::cout << "ends " << ends[i] << " starts " << starts[i] << std::endl;
    std::string p(ends[i]-starts[i], letter);
    std::cout << "p " << p <<std::endl;
    std::cout << "px + starts[i] " << px+starts[i] <<std::endl;
    std::cout << "py+i " << py+i << std::endl;
    
    add_row(p, px + starts[i], py + i);
  }
}

