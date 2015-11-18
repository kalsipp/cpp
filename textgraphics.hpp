#ifndef TEXTGRAPHICS_HPP
#define TEXTGRAPHICS_HPP
#include <vector>
#include <string>
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

#endif
