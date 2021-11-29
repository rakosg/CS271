#include "parser.h"
#include "error.h"
#include "symtable.h"
#include "hack.h"

void parse(FILE * file){
    char line[MAX_LINE_LENGTH] = "";

    unsigned int line_num = 0;
    unsigned int instr_num = 0;

    add_predefined_symbols();
    symtable_display_table();

    instruction instr;

    while(fgets(line, sizeof(line), file)){
        ++line_num;
        if(instr_num > MAX_INSTRUCTION) {
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTION + 1);
        }
        
        strip(line);

        if(*line == '\0'){
            continue;
        }

        else{
            char inst_type = '\0';

            if(is_Atype(line)){
                inst_type = 'A';
                printf("%c  %s\n", inst_type, line);

            }else if(is_label(line)){
                char line_type = 'L';
                char label[MAX_LABEL_LENGTH + 1] = "";
                extract_label(line, label);

                if (!isalpha(label[0])){
                    exit_program(EXIT_INVALID_LABEL, line_num, line);
                }

                if (symtable_find(label) == NULL){
                    exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
                }

                else {
                    symtable_insert(line, instr_num);
                }
                continue;
                printf("%c  %s\n", line_type, label);
            }
            else{
                inst_type = 'C';
            }
            
        }
        ++instr_num;
    }
}

char *strip(char *s){
    char s_new[strlen(s) + 1];
    int i = 0;

    for(char *s2 = s; *s2; s2++){
        if(*s2 == '/' && *(s2 + 1) == '/'){
            break;
        }

        else if (!isspace(*s2)){
            s_new[i++] = *s2;
        }
    }

    s_new[i] = '\0';

    stpcpy(s, s_new);
    
    return s;
}

void add_predefined_symbols(){
    for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
        predefined_symbol symbol = predefined_symbols[i];
        symtable_insert(symbol.name, symbol.address);
    }
}

char *extract_label(char *line){
    memmove(line, line+1, strlen(line));
    line[strlen(line)- 1] = 0;
    return line;
}


bool is_Atype(const char *line){
    return line[0] == '@'; 
}

bool is_label(const char *line){
    return line == '(' && strlen(line) - 1;
}

bool is_Ctype(const char *line){
    return !is_Atype(line) && !is_label(line);
}

bool parse_A_instruction(const char *line, a_instruction *instr){
    char *s = (char*) malloc(strlen(line));
    s = line + 1;
    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);
    if (s == s_end){
        inster->label = char(*)malloc(strlen(line));
        strcpy(instr->label, s);
        instr->is_addr = false;
    }

    else if (*s_end != 0){
        return false;
    }
    else {
        instr->address = result;
        instr->is_addr = true;
    }
    return true;
}