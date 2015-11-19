#include "textgraphics.hpp"
#include <string>
#include <vector>
#include <unistd.h> 
int main(){
  Textgrafs p;
  while(1){
    p.clear_grid();
    p.add_border('e', 5, 5, 10, 10, 2);
    p.add_col("huehue", 20, 20); 
    p.print();
    sleep(1);
  }


}
