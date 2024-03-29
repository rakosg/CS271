#include "symtable.h"

int hash(char *str){
    unsigned long hash = 5381;
    int c;
    while (c = *str++){
        hash = ((hash << 5) + hash) + c;
    }
    return hash % SYMBOL_TABLE_SIZE;
}

void symtable_insert(char *key, hack_addr addr) {
    struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
    item->addr = addr;
    item->name = key;
    int hashIndex = hash(key);
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->name != NULL){
        ++hashIndex;
        hashIndex %= SYMBOL_TABLE_SIZE;
    }
    hashArray[hashIndex] = item;
}

struct Symbol *symtable_find(char * name) {
    int hashIndex = hash(name);

    while(hashArray[hashIndex] != NULL){
        if(hashArray[hashIndex]->name == name){
            return hashArray[hashIndex];
        }
        ++hashIndex;
        hashIndex %= SYMBOL_TABLE_SIZE;
    }
    return NULL;
}

void symtable_display_table() {
    for(int i = 0; i < SYMBOL_TABLE_SIZE; i++){
        if(hashArray[i] != NULL){
            printf(" {%s, %d},", hashArray[i]->name, hashArray[i]->addr);
        }else{
            printf(" {~~, ~~},");
        }
    }
}