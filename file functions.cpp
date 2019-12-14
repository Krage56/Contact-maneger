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
//    if(strcmp(args[1], "--help") == 0){
//
//    }
//    else {
        int mem = -1;
        int opt_pos = -1;
        if(ignore_pose == c - 1){
            opt_pos = 1;

            for(int i = 0; i < options; i++){
                if(strcmp(menu[i], args[opt_pos]) == 0){
                    mem = i;
                    cout << menu[i] << " " << i << endl;
                    break;
                }
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
        switch (mem){
            case 0:
                fileAppend(file, args[opt_pos + 1]);
                *file << " " << args[opt_pos + 2] << " " << args[opt_pos + 3];

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:

                break;
            case 7:

                break;
            case 8:

                break;
        }

  //  }

//    for(int i = 0; i < options; ++i){
//        cout << menu[i] << endl;
//    }
    return 0;
}