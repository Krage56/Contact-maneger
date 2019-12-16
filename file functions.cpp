#include "head.h"

bool is_empty_file(fstream *file){
    long file_size;
    file->seekg(0, ios::end);
    file_size = file->tellg();
    if(file_size == 0){
        return true;
    }
    else{
        return false;
    }
}

void return_in_pos(fstream *file, bool pos){
    file->clear();
    pos ? file->seekg(0, ios_base::beg): file->seekg(0, ios_base::end);
}

void return_in_pos(fstream *file, int pos){
    file->clear();
    file->seekg(pos, ios_base::beg);
}

void filePrint(fstream *file){
    if(!is_empty_file(file)){
        return_in_pos(file, true);
        size_t i = 0;
        char buf[mem_block];
        do{
            ++i;
            file->getline(buf, mem_block, '\n');
            cout << i << " " << buf << endl;
        }while(!file->eof());
    }
}

void fileAppend(fstream *file, char *str){
    return_in_pos(file, false);
    if(!(is_empty_file(file))){
        *file << endl;
    }
    while(*str) {
        *file << *(str);
        ++str;
    }
}

int commandParser(fstream *file, int c, char** args, size_t ignore_pose){
    const short options = 9;
    char menu[options][mem_block] = {
            "create-contact",
            "delete-contact",
            "edit-contact-name",
            "edit-contact-phone",
            "edit-contact-group",
            "show-contacts",
            "show-contacts-by-name",
            "show-contacts-by-phone",
            "show-contacts-by-group"
    };
        int mem = -1;
        int opt_pos = -1;
        if(ignore_pose == c - 1){
            opt_pos = 1;
            //cout << "Here" << endl;
            for(int i = 0; i < options; i++){
                if(strcmp(menu[i], args[opt_pos]) == 0){
                    mem = i;
                    //cout << menu[i] << " " << i << endl;
                    break;
                }
                //cout << menu[i] << " " << args[opt_pos] << " "
               // << strcmp(menu[i], args[opt_pos]) << endl;
            }
        }
        if(ignore_pose == 1){
            opt_pos = 2;
            for(int i = 0; i < options; i++){
                if(strcmp(menu[i], args[opt_pos]) == 0){
                    mem = i;
                    break;
                }
            }
        }
    return mem;
}

void addByHand(fstream *file, char **args){
    //cout << *(args+0) << " " << *(args+1) << " " << *(args+2) << endl;
    fileAppend(file, *(args + 0));
    *file << *(args + 1) /*<< *(args + 2)*/;
    if(strcmp(*(args + 2), "COLLEAGUES")  == 0){
        *file << 3;
    }
    else if(strcmp(*(args + 2), "FAMILY")  == 0){
        *file << 1;
    }
    else if(strcmp(*(args + 2), "FRIENDS")  == 0){
        *file << 2;
    }
    else{
        *file << 0;
    }
    *file << '\n';
    *file << strlen(*(args + 0)) << '\n'
    << strlen(*(args + 1)) << '\n'
    << 1;
}

int file_lenght(fstream *file){
    if(is_empty_file(file)){
        return 0;
    }
    else{
        return_in_pos(file, true);
        int count = 0;
        char buf[mem_block];
        while (!file->eof()){
            ++count;
            file->getline(buf, mem_block, '\n');
        }
        return count;
    }
}

void delByHand(fstream *file, char *str){
    return_in_pos(file, true);
    int i = 0;
    int file_len = file_lenght(file);
    cout << file_len << endl;
//    while(!file->eof() && ){
//
//    }
}