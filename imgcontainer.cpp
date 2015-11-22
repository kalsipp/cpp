//A class container for ascii images
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <streambuf>
#include "imgcontainer.hpp"  
Img_container::Img_container(std::string filename){
    //std::ifstream f(filename.c_str());
    
    img_to_str_vector(filename, image_text);
}

std::vector<std::string> & Img_container::get_img_text(){
    return image_text;
}
void Img_container::print_img(){
  //Debug purposes
  for(int i = 0; i< image_text.size() ; ++i){
    std::cout << image_text[i] << std::endl;
  }
}

//img_txt
void Img_container::img_to_str_vector(std::string filename, std::vector<std::string> & im_text_ref){
    std::ifstream file(filename.c_str());
    //std::vector<std::string> img_text;
    std::string tempstr;
    int c = 0;
    while(std::getline(file, tempstr)){
      
      //pixels are 15 letters
      //end of every row is 9, ie every getline
      //so size is 15*pixels + 9
      std::cout << (tempstr.length()-9)%15;
      //At the end of the whole thing is 2
      //Does /033 count as 1?
      im_text_ref.push_back(tempstr);
    } 
    file.close();
  }
