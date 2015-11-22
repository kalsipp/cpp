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


void Img_container::img_to_str_vector(std::string filename, std::vector<std::string> & im_text_ref){
    std::ifstream file(filename.c_str());
    //std::vector<std::string> img_text;
    std::string tempstr;
    while(std::getline(file, tempstr)){
      im_text_ref.push_back(tempstr);
    } 
    file.close();
  }
