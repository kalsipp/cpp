#ifndef TEXTGRAPHICS_HPP
#define TEXTGRAPHICS_HPP
#include <vector>
#include <string>
#include <chrono>


class Textgrafs{
public:
  Textgrafs();
  ~Textgrafs();
  void add_row(std::string text, int px, int py); //Add row of text. Show with print or paint
  void add_col(std::string text, int px , int py);
  void add_rect(char letter, int px, int py, int sizex, int sizey);
  void add_border(char letter, int px, int py, int sizex, int sizey);
  void add_rect_unique(std::vector<std::string> shape, int px, int py);
  void add_ellipse(char letter, int px, int py, int rx, int ry); //Broken
  void print(); //Prints one grid
  bool next_tick(); //Should be private
  void paint(); //For continuous animation
  void clear(); //Empty screen
  void hide_cursor();
  void cursorpos(int, int); //Set cursorpos on screen
  std::string cursorpos_str(int, int);
  void clear_grid(); 
  int rows_;
  int cols_;
private:

  void save_old_grid();
  std::chrono::system_clock::time_point timer_;
  bool debug = false;
  double time_between_frames_ = 0.005;
  std::vector<std::string> grid;
  std::vector<std::string> old_grid;
};

#endif
