#include "textgraphics.hpp"
#include "imgcontainer.hpp"
#include <string>
#include <vector>
#include <unistd.h> 
int main(){
  Textgrafs p;
  p.clear();
  Img_container i("img_output");
  while(1){
    p.clear_grid();
    p.add_border('e', 0, 0, p.cols_, p.rows_);
    p.add_border('e', 2, 2, p.cols_-4, p.rows_-4);
    p.add_row("A god among men.", 54, p.rows_-2);
    //p.add_col("huehue", 20, 20); 
    //p.add_rect_unique(i.get_img_text(), 0, 0);
    p.print();
    p.print_img(i.get_img_text(), 12, 3, 30, 8);
    //i.print_img();
    
    sleep(1); 
  }


}
