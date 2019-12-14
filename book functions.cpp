#include "head.h"

int findName(Vector *v, char a[]){
    for(int i = 0; i < getSize(v); i++){
        if(strcmp(v->data[i].name, a) == 0){
            return i;
        }
    }
    return -1;
}

int findTelephone(Vector *v, char a[]){
    for(int i = 0; i < getSize(v); i++){
        if(strcmp(v->data[i].telephone, a) == 0){
            return i;
        }
    }
    return -1;
}

void addContact(Vector *v){
    const int words = 80 + 1;
    const int num = 12 + 1;
    const int gr = 30 + 1;
    char group[gr];
    Contact tmp;
/*    cout << "Enter name: ";
    char name[words];
    bool f = true;
    cin.getline(name, words);
    f = findName(v->data, getSize(v), name);
    while(!(f)){
        cout << "Enter correct name: ";
        cin.getline(name, words);
        f = findName(v->data, getSize(v), name);
    }
    memcpy(tmp.name, name, sizeof(char) * words);
*/
    char* name = nullptr;
    name = nameParser(v, false);
    memcpy(tmp.name, name, sizeof(char) * words);
    delete[](name);
    cout << "Enter phone number: ";
    cin.getline(tmp.telephone, num);
    cout << "Enter group: ";
    cin.getline(group, gr);
    if(strcmp(group, "COLLEAGUES")  == 0){
        tmp.group = Contact::COLLEAGUES;
    }
    else if(strcmp(group, "FAMILY")  == 0){
        tmp.group = Contact::FAMILY;
    }
    else if(strcmp(group, "FRIENDS")  == 0){
        tmp.group = Contact::FRIENDS;
    }
    else{
        tmp.group = Contact::NO_GROUP;
    }
    append(v, tmp);
}

void deleteContact(Vector *v){
    char* name = nullptr;
    name = nameParser(v, true);
    int f = findName(v, name);
    if(f != -1){
        erase(v, f);
    }
    delete[](name);
}

char* nameParser(Vector *v, bool find, bool new_n/*default parametr false*/){
    new_n ? cout << "Enter new name: " : cout << "Enter name: ";
    char* in = new char[input_mem];
    cin.getline(in, input_mem);
    while(((findName(v, in) == -1) == find) && (getSize(v) != 0)) {
        cout << "Enter correct name: ";
        cin.getline(in, input_mem);
    }
    return in;
}

bool EditContact(Vector *v){
    if(getSize(v) == 0){
        cout << "It`s nothing to edit." << endl;
        return false;
    }
    cout << "Edit contact\n";

    char* name = nullptr;
    name = nameParser(v, true);
    int index_name = findName(v, name);

    cout << "Edit contact field\n"
            "1. Edit name\n"
            "2. Edit phone number\n"
            "3. Edit group\n"
            "4. Back\n"
            "Command: ";

    char in[input_mem];
    goto loc_loop1;

    loc_loop1:
    cin.getline(in, input_mem);
    if(strcmp(in, "1") == 0){
        const int words = 80 + 1;
        name = nameParser(v, false, true);
        memcpy(v->data[index_name].name, name, sizeof(char) * (words));
        return true;
    }
    else if(strcmp(in, "2") == 0){
        const int num = 12 + 1;
        cout << "Enter new phone number: ";
        cin.getline(v->data[index_name].telephone, num);
        return true;
    }
    else if(strcmp(in, "3") == 0){
        const int gr = 30 + 1;
        char group[gr];
        cout << "Enter new group`s name: ";
        cin.getline(group, gr);
        if(strcmp(group, "COLLEAGUES")  == 0){
            v->data[index_name].group = Contact::COLLEAGUES;
        }
        else if(strcmp(group, "FAMILY")  == 0){
            v->data[index_name].group = Contact::FAMILY;
        }
        else if(strcmp(group, "FRIENDS")  == 0){
            v->data[index_name].group = Contact::FRIENDS;
        }
        else{
            v->data[index_name].group = Contact::NO_GROUP;
        }
    }
    else if(strcmp(in, "4") == 0){
        return true;
    }
    else{
        cout << "Enter the correct command, please: ";
        goto loc_loop1;
    }

    delete[]name;
    return false;
}

bool loop(Vector *v, char *input, int c, char** arg){
    do{
        cout << "List of available commands:\n"
                "1. Create contact\n"
                "2. Delete contact\n"
                "3. Edit contact\n"
                "4. Show contact(s)\n"
                "5. Exit\n"
                "Command: " << endl;
        cin.getline(input, input_mem);
        if(strcmp(input, "1") == 0){
            addContact(v);
        }
        if(strcmp(input, "2") == 0){
            deleteContact(v);
        }
        if(strcmp(input, "3") == 0){
            EditContact(v);
        }
        if(strcmp(input, "4") == 0){
            print(v);
        }
//        printAll(v);
    }while(strcmp(input, "5") != 0);


    return false;
}

bool print(Vector *v){
    cout << "Print contact(s):\n"
            "1. By name\n"
            "2. By phone number\n"
            "3. By group\n"
            "4. All contacts\n"
            "5. Back\n"
            "Comand: ";
    char *input = new char[input_mem];
    goto loc_loop1;
    loc_loop1:
    cin.getline(input, input_mem);
    if(strcmp(input, "1") == 0){
        cout << "Enter the name: ";
        cin.getline(input, input_mem);
        int index = findName(v, input);
        if(index != -1){
            print(v->data, index);
        }
        else{
            cout << "It`s no such contact\n";
        }
    }
    else if(strcmp(input, "2") == 0){
        cout << "Enter the telephone: ";
        cin.getline(input, input_mem);
        int index = findTelephone(v, input);
        if(index != -1){
            print(v->data, index);
        }
        else{
            cout << "It`s no such contact\n";
        }
    }
    else if(strcmp(input, "3") == 0){
        loc_loop2:
        cout << "Enter group`s name: ";
        cin.getline(input, input_mem);
        int obj = -1;
        if(strcmp(input, "NO_GROUP") == 0){
            obj = Contact::NO_GROUP;
        }
        else if (strcmp(input, "FAMILY") == 0) {
            obj = Contact::FAMILY;
        }
        else if(strcmp(input, "FRIENDS") == 0){
            obj = Contact::FRIENDS;
        }
        else if(strcmp(input, "COLLEAGUES") == 0){
            obj = Contact::COLLEAGUES;
        }
        else{
            cout << "Incorrect group`s name\n";
            goto loc_loop2;
        }
        for(int i = 0; i < getSize(v); i++){
            if(v->data[i].group == obj){
                print(v->data, i);
            }
        }
    }
    else if(strcmp(input, "4") == 0){
        for(int i = 0; i < getSize(v); i++){
            print(v->data, i);
        }
    }
    else if(strcmp(input, "5") == 0){
        return true;
    }
    else{
        goto loc_loop1;
    }
    delete[]input;
    return false;
}

void print(Contact *arr, int i){
    cout << "* [";
    switch (arr[i].group){
        case (Contact::NO_GROUP):{
            cout << "NO_GROUP";
            break;
        }
        case (Contact::FAMILY):{
            cout << "FAMILY";
            break;
        }
        case (Contact::FRIENDS):{
            cout << "FRIENDS";
            break;
        }
        case (Contact::COLLEAGUES):{
            cout << "COLLEAGUES";
            break;
        }
    }
    cout << "] ";
    cout << arr[i].name;
    cout << " --- ";
    cout << arr[i].telephone << endl;
}