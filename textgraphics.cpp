#include <iostream>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <chrono>
class Textgrafs{
public:
  Textgrafs();
  ~Textgrafs();
  void add_row(std::string, int, int);
  void add_col(std::string, int, int);
  void print();
  bool next_tick();
  void paint();
  void clear();
  void fun();
  void hide_cursor();
  void cursorpos(int, int);
  void save_old_grid();
private:
  void clear_grid();
  //int tick_counter_= 0;
  //int framerate_ = 30000000;
  std::chrono::system_clock::time_point timer_;
  //std::chrono::steady_clock reftime_;
  bool debug = true;
  float framerate_ = 0;
  double time_between_frames_ = 0;
  int rows_;
  int cols_;
  //char** grid;
  std::vector<std::string> grid;
  std::vector<std::string> old_grid;
};

void Textgrafs::fun(){
  std::cout << "\033[1;1H" <<std::endl;
}

Textgrafs::Textgrafs(){
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  rows_ = w.ws_row;
  cols_ = w.ws_col;
  std::string s(cols_, ' ');
  grid.resize(rows_,s);
  old_grid.resize(rows_,s);
  framerate_ = 100000;
  time_between_frames_ = 0.010;
  timer_ = std::chrono::system_clock::now();
  clear();
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
    //clear();
    for(int i = 0; i < rows_ ; ++i){
      cursorpos(0, i); 
      if(0 != grid[i].compare(old_grid[i])){
	std::cout << grid[i];
      }
  }
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
  int len = 0;
  if(py < 0 || py > cols_){
    return;
  }
  if(px < 0){
    text.erase(0,abs(px));
  }
  if(px > rows_){
    text.erase(text.length()-(px-rows_), text.length());
  }
  grid[py].replace(px, text.length(), text);
}
void Textgrafs::add_col(std::string text, int px, int py){
  //const char * p = text.c_str();
  //const char * k = p[0];
  for(int i = 0;  i < text.length(); ++i){
    //grid[i].replace(px, 0, k);
  }
}
int main(){
  Textgrafs p;
  p.add_row("hehe", 1, 1);
  //p.add_col("huehue", 20, 20);
  //  while(1){
  //p.add_row("hehe", 10, 10);

  //}
  std::cout << "\033[?25l";
  int counter = 0;
  while(1){
    p.add_row("hej", counter, 1);
    counter++;
    //p.add_row(std::chrono::system_clock::now(), 1, 1);
    p.paint();
  }
}

