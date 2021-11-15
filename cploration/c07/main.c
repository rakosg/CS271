#include <symtable.h>

int main(){        
    struct Symbol* item = (struct Symbol*) malloc(sizeof(struct Symbol));
    item->name = NULL;  
    item->addr = -1; 

    insert("OUTPUT_FIRST", 11);
    printf("Inserting OUTPUT_FIRST at address 11\n");
    insert("OUTPUT_D", 13);
    printf("Inserting OUTPUT_D at address 13\n");
    insert("INFINITE_LOOP", 15);
    printf("Inserting INFINITE_LOOP at address 15\n");
    printf("\n");

    printf("Displaying table:\n");
    display_table();
    printf("\n");
      
    char * label = "OUTPUT_FIRST";
    printf("Looking up %s\n", label);
    item = find(label);

    if(item != NULL) {
      printf("Element %s found: %d\n", item->name, item->addr);
    } else {
      printf("Element %s not found\n", label);
    }
    printf("\n");

    label = "MY_LABEL";
    printf("Looking up %s\n", label);
    item = find(label);

    if(item != NULL) {
      printf("Element %s found: %d\n", item->name, item->addr);
    } else {
      printf("Element %s not found\n", label);
    }
    printf("\n");

    printf("Displaying table:\n");
    display_table();
    printf("\n");

    free(item);   
}