#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#define stringInput 1
#define fileInput 2

class Assembler{
public:
    void setInFile(std::string);
    void setInData(std::string);
    void generateBinCode(std::string);

private:
    int mode ;
    std::string    inputStr;
    std::ifstream *inputFile;
    std::ofstream *outputFile;
    std::vector<std::string>  *outputData;
    std::vector<std::vector<std::string>> processData();
    std::vector<std::string> getWords(std::string);
    void assembleStr();
};

#endif