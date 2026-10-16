#include <iostream>
#include <fstream>

int main(int argc, char *argv[]){
    std::string input_file1 = "";
    std::string input_file2 = "";

    if(argc > 3){
        std::cerr << "Too many arguments!" << std::endl;
        return 1;
    }else if(argc <= 2){
        std::cerr << "Too few arguments!" << std::endl;
        return 1;
    }else{
        input_file1 = argv[1];
        input_file2 = argv[2];
    }

    std::ifstream f(input_file1);
    if(!f.is_open()){
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }



    return 0;
}