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


Vector* contactParsing(fstream *file){
    Vector *v = createVector();

    Contact tmp_contact;

    char buf[mem_block];
    char tmp_data[mem_block];
    char tmp_str[mem_block];

    long name = -1;
    long tel = -1;
    long group_num = -1;
    const short len_group_name = 2;
    int i = 0;
    return_in_pos(file, true);
    while(!file->eof()){
        file->getline(buf, mem_block,'\n');
        if(i % 4 == 0){
            if(i != 0){
                append(v, tmp_contact);
                cout << getSize(v) << endl;
            }
            memcpy(tmp_data, buf, sizeof(char) * strlen(buf));
        }
        if(i % 4 == 1){
            name = atoi(buf);
            memcpy(tmp_contact.name, tmp_data, sizeof(char) * name);
        }
        if(i % 4 == 2){
            tel = atoi(buf);
            strcpy(tmp_str, tmp_data + name);
            memcpy(tmp_contact.telephone, tmp_str, (strlen(tmp_str) - 1)* sizeof(char));
            //cout << *(tmp_data + name + sizeof(char) * tel - 1) << endl;
        }
        if(i % 4 == 3){
            group_num = atoi(buf);
            char group_name[2];
            memcpy(group_name, tmp_data + name + tel, sizeof(char) * group_num);
            group_num = atoi(group_name);
            switch (group_num){
                case (0):
                    tmp_contact.group = Contact::NO_GROUP;
                    break;
                case (1):
                    tmp_contact.group = Contact::FAMILY;
                    break;
                case (2):
                    tmp_contact.group = Contact::FRIENDS;
                    break;
                case (3):
                    tmp_contact.group = Contact::COLLEAGUES;
                    break;
            }
        }
        ++i;
    }
    return v;
}

void save(fstream *file, Vector *v){
    cout << getSize(v) << endl;
    for(int i = 0; i < getSize(v); ++i){
        cout << "here";
        *file << v->data[i].name << v->data[i].telephone << v->data[i].group << '\n';
        *file << strlen(v->data[i].name) << '\n';
        *file << strlen(v->data[i].telephone) << '\n';
        *file << 1 << '\n';
    }
}


//void delByHand(fstream *file, char *str){
//    return_in_pos(file, true);
//    int i = 0;
//    int file_len = file_lenght(file);
//    cout << file_len << endl;
//    char buf[mem_block];
//    char tmp_data[mem_block];
//    char tmp_name[mem_block];
//    long name = -1;
//    long tel = -1;
//    long group = -1;
//    int pos = -1;
//    bool f = true;
//    return_in_pos(file, true);
//    while(!file->eof() && i < file_len && f){
//        file->getline(buf, mem_block,'\n');
//        if(i % 4 == 0){
//            memcpy(tmp_data, buf, sizeof(char) * strlen(buf));
//        }
//        if(i % 4 == 1){
//            name = atoi(buf);
//            memcpy(tmp_name, tmp_data, name);
//            if(strcmp(tmp_name, str) == 0){
//                pos = file->tellp();
//                f = false;
//            }
//        }
//        if(i % 4 == 2){
//            tel = atoi(buf);
//        }
//        if(i % 4 == 3){
//            group = atoi(buf);
//        }
//        ++i;
//    }
//
//}