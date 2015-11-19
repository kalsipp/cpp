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

//#### Special member functions ####
//#### Constructor
Textgrafs::Textgrafs(){ 
  std::cout << std::unitbuf; //Turns off the buffer
  std::ios_base::sync_with_stdio(false); //Turn off sync with in stream

  struct winsize w; //Get size of window
  ioctl(0, TIOCGWINSZ, &w);
  rows_ = w.ws_row;
  cols_ = w.ws_col;

  //Prepare grid
  std::string s(cols_, ' ');
  grid.resize(rows_,s);
  old_grid.resize(rows_,s);

  timer_ = std::chrono::system_clock::now(); //First timepoint
  clear(); //and clear screen
}
//#### Destructor
Textgrafs::~Textgrafs(){
  //Actually don't need one right now
}

//#### Member functions
void Textgrafs::paint(){
  //Used for continuous update
  //Refer to print for manual control
  if(next_tick()){ //Limit framerate
    print(); //Print out the current grid
    //save_old_grid();
  }
  clear_grid(); //This empties the grid. You need to enter what you painted every frame
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
    //s+= "\033[1;1H"; //set cursor to 0,0
    cursorpos(0,0);
    for(int y = 0; y < rows_ ; ++y){ //Generate the full grid
      s+= grid[y];
      s+= "\n";
    }
    s.pop_back(); //Remove last \n
    write(1, s.c_str(), s.length()); //works 
    //std::cout << s; //works
    //printf(s.c_str()); //bad
    
}
void Textgrafs::clear_grid(){
  //Fills the grid with space
  std::string s(cols_, ' ');
  for(int i = 0; i < rows_ ; ++i){
    grid[i] = s;
  }
}
bool Textgrafs::next_tick(){
  //Calculate next frame
  std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::system_clock::now()-timer_);
  if(debug)add_row(std::to_string(time_span.count()), 0, 0);
  if(time_span.count() > time_between_frames_){
    timer_ = std::chrono::system_clock::now();
    return true;
  }
  return false;
  
}
void Textgrafs::add_row(std::string text, int px, int py){
  //User adds a row of text to the grid. 
  //if outside the screen the text will be truncated (or ignored if nothing is on screen)
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
  //User adds a row of text to the grid. 
  //if outside the screen the text will be truncated (or ignored if nothing is on screen)
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
  for(int i = py;  i < py+text.length(); ++i){
    std::cout << "i " << i << std::endl;
    s.assign(text, i-py, 1);
    add_row(s, px, i);
  }
}
void Textgrafs::add_rect(char letter, int px, int py, int sizex, int sizey){
  //User adds a full rext to the grid. 
  //if outside the screen the text will be truncated (or ignored if nothing is on screen)
  std::string s(sizex, letter);
  for(int i = 0; i < sizey; ++i){
    add_row(s, px, py+i); //Truncation will be handled by add_row
  }
}

void Textgrafs::add_rect_unique(std::vector<std::string> shape, int px, int py){
  for(int i = 0; i<shape.size();++i){
    add_row(shape[i], px, py+i);
  }
}

void Textgrafs::add_border(char letter, int px, int py, int sizex, int sizey, int thickness){
  if(thickness == 0)return;
  std::string obx(sizex+1, letter); //outer border x
  std::string oby(sizey, letter); //outer border y
  if(thickness > 0){

    //Create outer borders
    add_row(obx, px, py);
    add_row(obx, px, py+sizey);
    add_col(oby, px, py);
    add_col(oby, px+sizex, py);
    //Create inner borders
    //Setup distances
    int dx = sizex-2*thickness;
    if(dx < 0) dx = 1; //Come on use add_rect then
    std::string ibx(dx-1, letter);
    int dy = sizey-2*thickness;
    if(dy < 0 ) dy = 1;
    std::string iby(dy, letter);
    //add borders with modified values
    add_row(ibx, px+thickness+1, py+thickness);
    add_row(ibx, px+thickness+1, py+sizey-thickness);
    add_col(iby, px+thickness+1, py+thickness);
    add_col(iby, px+sizex-thickness-1, py+thickness);
  }
  else if(thickness < 0){
      
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

