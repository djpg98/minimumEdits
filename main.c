#include <stdio.h>
#include "minimumEdits.h"

//Pasar los strings como argumento del shell
int main(int args, char* argv[]){
    returnSolution(minimumEdits(argv[1], argv[2]), argv[1], argv[2]);
}