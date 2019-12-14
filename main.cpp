#include "head.h"

int main(int c, char** arg){
    Vector *book = createVector();
    char *input = new char[input_mem];
    if(strcmp(arg[1], "--help") == 0){
        cout << "Usage: contacts [option] <file>\n"
                "Options:\n"
                "create-contact <name> <phone> <group>\n"
                "delete-contact <name>\n"
                "edit-contact-name <name> <new-name>\n"
                "edit-contact-phone <name> <new-phone>\n"
                "edit-contact-group <name> [<new-group>]\n"
                "show-contacts\n"
                "show-contacts-by-name <name>\n"
                "show-contacts-by-phone <phone>\n"
                "show-contacts-by-group <group>\n"
                ;
    }
    fstream file;
    file.open(arg[1], ios_base::out | ios_base::in);
    if(file.is_open()){
        if (c > 2) {
            commandParser(&file, c, arg);
        }
    }
//    else{
//        file.open(arg[c - 1], ios_base::out | ios_base::in);
//    }
//    if(file.is_open()){
//        commandParser(&file, c, arg, c - 1);
//    }
//    else{
//        return 1;
//    }
    loop(book, input, c, arg);
    deleteVector(book);
    delete[](input);
    file.close();
    return 0;
}
