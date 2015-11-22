#ifndef IMGCONTAINER_HPP
#define IMGCONTAINER_HPP

#include <string>
#include <vector>

class Img_container{
 public:
  Img_container(std::string filename);
  std::vector<std::string> & get_img_text();
  void print_img();
 private:
  std::vector<std::string> image_text;
  //std::vector<std::vector<std::string>> image_text_new;
  void img_to_str_vector(std::string filename, std::vector<std::string> & im_text_ref);
  
};


#endif
