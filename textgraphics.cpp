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
  void add_rect(char, int, int, int, int);
  void add_ellipse(char, int, int, int, int);
  void print();
  bool next_tick();
  void paint();
  void clear();
  void fun();
  void hide_cursor();
  void cursorpos(int, int);
  void save_old_grid();
  int rows_;
  int cols_;
private:
  void clear_grid();
  //int tick_counter_= 0;
  //int framerate_ = 30000000;
  std::chrono::system_clock::time_point timer_;
  //std::chrono::steady_clock reftime_;
  bool debug = false;
  float framerate_ = 0;
  double time_between_frames_ = 0;
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
  time_between_frames_ = 0.001;//0.010;
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
  //std::string s;
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
  grid[py].replace(px, text.length(), text);
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
int main(){
  Textgrafs p;
  p.add_row("hehe", 1, 1);
  //p.add_col("huehue", 20, 20);
  //  while(1){
  //p.add_row("hehe", 10, 10);

  //}
  std::cout << "\033[?25l"; //Hide cursor
  int counter = 0;
  float px = 0;
  float py = 0;
  int sizex = 10;
  int sizey = 6;
  float speedx = 0.0005f;
  float speedy = 0.0004f;
  std::string borderx(p.cols_, '0');
  std::string bordery(p.rows_, '0');
  std::string k;
  k.assign(borderx, 6, 1);
  //borderx.copy(k,1, 6);
  while(1){
    // p.add_row(k, 10, 10);
    //p.add_row(borderx, 0, 0);
    //p.add_row(borderx, 0, p.rows_-1);
    //p.add_col(bordery, 0, 0);
    //p.add_col(bordery, p.cols_-1, 0);
    p.add_rect('e', px, py, sizex, sizey);
    px += speedx;
    py += speedy;
    if(px + sizex -1 > p.cols_){
      px = p.cols_-sizex-1;
      speedx = speedx*-1;
    }
    else if(px < 0){
      px = 0;
      speedx = speedx*-1;
    }
    if(py + sizey -1> p.rows_){
      py = p.rows_ - sizey-1;
      speedy = speedy*-1;
    }
    else if(py < 1){
      py = 1;
      speedy = speedy*-1;
    }
    //p.add_row("hej", 1, counter);
    //counter++;
    //p.add_ellipse('e', 10, 10, 7, 7);
    //if(counter > 100) counter = 0;
    //p.add_row(std::chrono::system_clock::now(), 1, 1);
    p.paint();
  }
}

