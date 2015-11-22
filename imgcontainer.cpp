//A class container for ascii images
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <streambuf>
class Ascii_img{
public:
  
  std::vector<std::string> image_text;
  Ascii_img(std::string filename){
    //std::ifstream f(filename.c_str());
    
    img_to_str_vector(filename, image_text);
    
  }
  std::vector<std::string> & get_img_text(){
    return image_text;
  }
private:
  void img_to_str_vector(std::string filename, std::vector<std::string> & im_text_ref){
    std::ifstream file(filename.c_str());
    //std::vector<std::string> img_text;
    std::string tempstr;
    while(std::getline(file, tempstr)){
      im_text_ref.push_back(tempstr);
    } 
    file.close();
  }
  

};

int main(){
  Ascii_img helo("img_output");
}
