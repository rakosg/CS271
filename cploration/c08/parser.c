#include "parser.h"
#include "error.h"
#include "symtable.h"

void parse(FILE * file){
    char line[MAX_LINE_LENGTH] = "";

    unsigned int line_num = 0;
    unsigned int instr_num = 0;

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

            }else if(is_label(line)){
                extract_label(line);
                
                if(!isalpha(line[0])){
                    exit_program(EXIT_INVALID_LABEL, line_num, line);
                }

                if(symtable_find(line) != NULL){
                    exit_program(EXIT_LABEL_ALREADY_EXISTS, line_num, line);
                }

                else{
                    symtable_insert(line, instr_num);
                }
                
                inst_type = 'L';

            }
            else{
                inst_type = 'C';
            }
            printf("%c  %s\n", inst_type, line);
        }
        ++instr_num;
    }
}

char *strip(char *s){
    char s_new[MAX_LINE_LENGTH] = "";
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

bool is_Atype(const char *line){
    return line[0] == '@'; 
}

bool is_label(const char *line){
    return line[0] == '(' && line[sizeof(line) - 1] == ')';
}

bool is_Ctype(const char *line){
    return !is_Atype(line) && !is_label(line);
}
