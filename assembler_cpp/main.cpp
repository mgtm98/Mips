#include <string>
#include "assembler.h"

int main (){
    Assembler as;
    as.setInData("addi $s1, $s2, 15\naddi $s1, $s2, 15\nNOP\nsubi\naddi $s44\n\n\n");
    as.generateBinCode("/home/mgtm/Desktop/binary.txt");
}