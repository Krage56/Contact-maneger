#include "head.h"

int main(int c, char** arg){
    Vector *book;
    char *input = new char[input_mem];
    char *file_name;

/*    fstream file;
    file.open("./ex.txt", ios_base::out | ios_base::in);
    if(!file.is_open()){
        cout << "error" << endl;
    }*/

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
    int d = -1;
    int ignore_pos = -1;
    if(file.is_open()){
        ignore_pos = 1;
        file_name = arg[1];
        if (c > 2) {
            d = commandParser(&file, c, arg);
        }
        else{
            //cout << is_empty_file(&file) << endl;
            book = contactParsing(&file);
            goto loc_loop;
        }
    }
    else if(!file.is_open()){
        file.open(arg[c - 1], ios_base::out | ios_base::in);
        if(file.is_open()){
            ignore_pos = c - 1;
            file_name = arg[c - 1];
            if (c > 2) {
                d = commandParser(&file, c, arg, c - 1);
            }
            else{
                //cout << is_empty_file(&file) << endl;
                book = contactParsing(&file);
                goto loc_loop;
            }
        }
    }
    else if (!file.is_open()){
        return 1;
    }

    book = contactParsing(&file);

    switch (d){
        case 0:
            //cout <<"create-contact"<<endl;
            //cout << is_empty_file(&file) << endl;
            if(ignore_pos == 1){
                addByHand(&file, arg + 3, book);
            }
            else if(ignore_pos == c - 1){
                addByHand(&file, arg + 2, book);
            }
            break;
        case 1:
            cout << "delete-contact" << endl;
//            if(ignore_pos == 1){
//                delByHand(&file, *(arg + 3));
//            }
            break;
        case 2:
            cout <<"edit-contact-name"<<endl;
            break;
        case 3:
            cout <<"edit-contact-phone"<<endl;
            break;
        case 4:
            cout <<"edit-contact-group"<<endl;
            break;
        case 5:
            cout <<"show-contacts"<<endl;
            break;
        case 6:
            cout <<"show-contacts-by-name"<<endl;
            break;
        case 7:
            cout <<"show-contacts-by-phone"<<endl;
            break;
        case 8:
            cout << "show-contacts-by-group"<<endl;
            break;
        default:
            cout << "Incorrect command" << endl;
            break;
    }
    loc_loop:
        //loop(book, input, c, arg);

        loop(book, input, c, arg);
        //deleteVector(book);
        //delete[](input);

        file.close();

        fstream fileIn;
        fileIn.open(file_name, std::ofstream::out | std::ofstream::trunc);

        //filePrint(&fileIn);
        save(&fileIn, book);

        deleteVector(book);
        delete[](input);
        fileIn.close();
    return 0;
}
