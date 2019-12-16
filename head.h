#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <typeinfo>
using namespace std;

struct Contact{
    char name[80 + 1];/*80 symbols*/
    char telephone[12 + 1];/*12 numbers*/
    enum Groups{
        NO_GROUP,
        FAMILY,
        FRIENDS,
        COLLEAGUES
    };
    Groups group;
};

typedef struct {
    Contact *data;
    size_t size;
    size_t capacity;
} Vector;

const size_t input_mem = 1024 + 1;
const size_t mem_block = 1024 + 1;

Vector *createVector();

void deleteVector(Vector *v);

Vector *copyVector(Vector *v);

void swapVector(Vector *lh, Vector *rh);

Contact getValue(Vector *v, size_t index);

size_t getSize(Vector *v);

size_t getCapacity(Vector *v);

void append(Vector *v, Contact value);

void append(Vector *v, Contact *array, size_t count);

void insert(Vector *v, size_t index, Contact value);

void erase(Vector *v, size_t index);

size_t indexOf(Vector *v, Contact value);

void reserve(Vector *v, size_t newCap);

void squeeze(Vector *v);

void clear(Vector *v);

//void print(Vector *v);


void addContact(Vector *v);

void deleteContact(Vector *v);

char* nameParser(Vector *v, bool find, bool new_n = false);

bool loop(Vector *v, char *input, int c, char** arg);

bool print(Vector *v);

void print(Contact *arr, int pos);

bool EditContact(Vector *v);



void filePrint(fstream *file);

void fileAppend(fstream *file, char *str);

void return_in_pos(fstream *file, bool pos);

int commandParser(fstream *file, int c, char** args, size_t ignore_pose = 1);

bool is_empty_file(fstream *file);

void addByHand(fstream *file, char **args, Vector *v);

void delByHand(fstream *file, char *str);

Vector* contactParsing(fstream *file);

void save(fstream *file, Vector *v);