#include "head.h"

int main(){
    Vector *book = createVector();
    char *input = new char[input_mem];
    loop(book, input);
    deleteVector(book);
    delete[](input);
    return 0;
}
