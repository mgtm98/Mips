#include "assembler.h"

void Assembler::setInData(std::string inputData){
    inputStr = inputData;
    mode = stringInput;
}

void Assembler::setInFile(std::string inputFilePath){
    inputFile = new std::ifstream();
    inputFile->open(inputFilePath.c_str(),std::ios::in);
    mode = fileInput;
}

void Assembler::generateBinCode(std::string outFilePath){
    outputFile = new std::ofstream();
    outputFile->open(outFilePath.c_str(),std::ios::in);
    if(mode == stringInput){
        assembleStr();
    }else if(mode == fileInput){

    }else{
        std::cout << "uninsalized Data source" << std::endl;
    }
}

void Assembler::assembleStr(){
    for(auto line : processData()){
        for(auto word : line){
            std::cout << word;
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<std::string>> Assembler::processData(){
    std::vector<std::vector<std::string>> lines;
    size_t currentPos = 0;
    size_t nextPos = inputStr.find('\n');
    std::string line ;
    while(nextPos != std::string::npos){
        line = inputStr.substr(currentPos,nextPos-currentPos);
        if(line.length())
            lines.push_back(getWords(line));
        currentPos = nextPos+1;
        nextPos = inputStr.find('\n',currentPos);
    }
    line = inputStr.substr(currentPos,inputStr.length()-currentPos);
    if(line.length())
        lines.push_back(getWords(line));
    return lines;
}

std::vector<std::string> Assembler::getWords(std::string line){
    std::vector<std::string> words;
    size_t currentPos = 0;
    size_t nextPos = line.find(' ');
    std::string word ;
    while(nextPos != std::string::npos){
        word = line.substr(currentPos,nextPos-currentPos);
        if(word.length()){
            if(!word.substr(word.length()-1,1).compare(",")){
                word.pop_back();
            }
            words.push_back(word);
        }        
        currentPos = nextPos+1;
        nextPos = line.find(' ',currentPos);
    }
    word = line.substr(currentPos,line.length()-currentPos);
    if(word.length()){
        if(!word.substr(word.length()-1,1).compare(",")){
            word.pop_back();
        }
        words.push_back(word);
    }        
    return words;
}