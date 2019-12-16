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
            if(ignore_pos == 1){
                addByHand(&file, arg + 3, book);
            }
            else if(ignore_pos == c - 1){
                addByHand(&file, arg + 2, book);
            }
            goto end;
            break;
        case 1:
            if(ignore_pos == 1){
                deleteContact(book, arg[3]);
            }
            else if(ignore_pos == c - 1){
                deleteContact(book, arg[2]);
            }
            goto end;
            break;
        case 2:
            if(ignore_pos == 1){
                editContactName(book, arg[3], arg[4]);
            }
            else if(ignore_pos == c - 1){
                editContactName(book, arg[2], arg[3]);
            }
            goto end;
            break;
        case 3:
            if(ignore_pos == 1){
                editContactPhone(book, arg[3], arg[4]);
            }
            else if(ignore_pos == c - 1){
                editContactPhone(book, arg[2], arg[3]);
            }
            goto end;
            break;
        case 4:
            if(ignore_pos == 1){
                editContactGroup(book, arg[3], arg[4]);
            }
            else if(ignore_pos == c - 1){
                editContactGroup(book, arg[2], arg[3]);
            }
            goto end;
            break;
        case 5:
            for(int i = 0; i < getSize(book); ++i){
                print(book->data, i);
            }
            goto end;
            break;
        case 6:
            if(ignore_pos == 1){
                if(findName(book, arg[3]) != -1){
                    print(book->data, findName(book,arg[3]));
                }
            }
            else if(ignore_pos == c - 1){
                if(findName(book, arg[2]) != -1){
                    print(book->data, findName(book,arg[2]));
                }
            }
            goto end;
            break;
        case 7:
            char tmp_str[mem_block];
            if(ignore_pos == 1){
                strcpy(tmp_str, arg[3]);
            }
            else if(ignore_pos == c - 1){
                strcpy(tmp_str, arg[2]);
            }
            if(findTelephone(book, tmp_str) != -1){
                for(int i = 0; i < getSize(book); ++i){
                    if(strcmp(book->data[i].telephone, tmp_str) == 0){
                        print(book->data, i);
                    }
                }
            }
            goto end;
            break;
        case 8:
            char tmp_str1[mem_block];
            if(ignore_pos == 1){
                strcpy(tmp_str1, arg[3]);
            }
            else if(ignore_pos == c - 1){
                strcpy(tmp_str1, arg[2]);
            }
            for(int i = 0; i < getSize(book); ++i){
                if((book->data[i].group == Contact::FRIENDS) && (strcmp(tmp_str1, "FRIENDS") == 0)){
                    print(book->data, i);
                }
                if((book->data[i].group == Contact::COLLEAGUES) && (strcmp(tmp_str1, "COLLEAGUES") == 0)){
                    print(book->data, i);
                }
                if((book->data[i].group == Contact::FAMILY) && (strcmp(tmp_str1, "FAMILY") == 0)){
                    print(book->data, i);
                }
                if((book->data[i].group == Contact::NO_GROUP) && (strcmp(tmp_str1, "NO_GROUP") == 0)){
                    print(book->data, i);
                }
            }
            goto end;
            break;
        default:
            cout << "Incorrect command" << endl;
            goto end;
            break;
    }
    loc_loop:

        loop(book, input, c, arg);

    end:
        file.close();

        fstream fileIn;
        fileIn.open(file_name, std::ofstream::out | std::ofstream::trunc);

        save(&fileIn, book);

        deleteVector(book);
        delete[](input);
        fileIn.close();
    return 0;
}
