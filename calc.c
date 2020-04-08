#include<stdio.h>

#define MAX_LENGTH 20
#define MAX_NUMBER 99999999
typedef struct {
    int input_flag; //1: input number 0: input operator
    int init_flag;  //1: init 
    int error_flag;
} FLAG;

enum CMD {
    q_cmd,
    c_cmd,
    ce_cmd,
    mp_cmd,
    mm_cmd,
    mi_cmd,
    mc_cmd,
    mr_cmd,
    ac_cmd,
    loop,
    integer,
    operator,
    error,
    error_len,
};

enum ERROR {
    no_error = 0,
    invalid_input,
    zero_division,
    long_input,
    long_output,
};

//Char -> Float
float myatof(char *s){
    int d_cnt = 0, i = 0;
    float value = 0, i_value = 0, d_value = 0;
    
    while(*s != '\0'){
        i_value = i_value*10 + (*s - '0');
        s++;
        if(*s == '.'){
            s++;
            while(*s != '\0'){
            //一番大きい桁から10倍して足していく
                d_value = d_value*10 + (*s - '0');
                s++;
                d_cnt++;
            }
            //最後に小数点分ずらす
            while(i<d_cnt){
                d_value = d_value*0.1;
                i++; 
            }
            
        }
    }
    value = i_value + d_value;
    return value;
}

int mystrcmp(char *s1, char *s2){
    while(*s1 == *s2){
        if(*s1 == '\0')
            return 0;
        s1++;
        s2++;
    }
    return 1;
}

void mystrcpy(char *s1, char *s2){
    char *s = s1;
    while((*s++ = *s2++) != 0);
    return ;
}

//Calculate +,-,*,/,root
float calc(char *op, float arg1, float arg2){
    float result = 0;
    switch(op[0]){
        case '+':
            result = arg1 + arg2;
            break;
        case '-':
            result = arg1 - arg2;
            break;
        case '*':
            result = arg1 * arg2;
            break;
        case '/':
            result = arg1 / arg2;
            break;
    }
    return result;
}

int check_num(char *s){
    int i_cnt = 0, d_cnt = 0;
    while(*s != '\0'){
        if(*s == '.'){
            s++;
            while(*s != '\0'){
                if('0' > *s || *s > '9') return 0;
                if(d_cnt > 6) return error_len;
                d_cnt++;
                s++;
            }
            return 1;
        }
        if('0' > *s || *s > '9') return 0;
        if(i_cnt > 7) return error_len;
        i_cnt++;
        s++;
    }
    return 1;
}

//入力管理
int input_ctrl(char *s, FLAG flags){
    int check_len = 0, i = 0;
    char *s0;

    read(0, s, MAX_LENGTH);
    s0 = s;
    while(*s != '\n' && *s != EOF){
        s++;
    }
    *s = '\0';
    s = s0;
    if ((check_len=check_num(s)) && flags.input_flag){
        if(check_len == error_len) return error_len;
        return integer;
    } else if (!mystrcmp(s, ":mr") && flags.input_flag){
        return mr_cmd;
    } else if (!mystrcmp(s, "+") || !mystrcmp(s, "-") || !mystrcmp(s, "*") || !mystrcmp(s, "/") && !flags.input_flag){
        return operator;
    } else if (!mystrcmp(s, ":m+") && !flags.input_flag){
        return mp_cmd;
    } else if (!mystrcmp(s, ":m-") && !flags.input_flag){
        return mm_cmd;
    } else if (!mystrcmp(s, ":mc")){
        return mc_cmd;
    } else if (!mystrcmp(s, ":ac")){
        return ac_cmd;
    } else if (!mystrcmp(s, ":c")){
        return c_cmd;
    } else if (!mystrcmp(s, ":ce")){
        return ce_cmd;
    } else if (!mystrcmp(s, ":q")){
        return q_cmd;
    } else {
        return error;
    }

}

void comment_ctrl(FLAG flags, float arg0, float arg1, float arg2, float mem, char *op){

    switch(flags.error_flag){
        case no_error:
            break;
        case invalid_input:
            printf("Error : Invalid input\n");
            break;
        case zero_division:
            printf("Error : Zero division\n");
            break;
        case long_input:
            printf("Error : Too long input\n");
            break;
        case long_output:
            printf("Error : Too long output\n");
            break;
    }

        if(!flags.input_flag && flags.init_flag){
            printf("%f\tmemory : %f\n", arg1, mem);
        } else if(!flags.input_flag){
            printf("%f %s %f\n", arg0, op, arg2);
            printf("= %f\tmemory : %f\n", arg1, mem);
        } else{
            printf("%f %s\tmemory : %f\n", arg1, op, mem);
        }
}

int main(){
    float i_arg0 = 0, i_arg1 = 0, i_arg2 = 0, mem = 0, mem0 = 0;
    char arg[MAX_LENGTH], op[MAX_LENGTH];
    FLAG flags = {1, 1, no_error};

    printf("Hello! Please input number.\n");

    while(1){
        mystrcpy(arg,"");

        switch(input_ctrl(arg, flags)){
            case integer:
                if(flags.init_flag){
                    i_arg1 = myatof(arg);
                    flags.input_flag = 0;
                } else{
                    i_arg2 = myatof(arg);
                    if(i_arg2 == 0 && !mystrcmp(op, "/")){
                        flags.error_flag = zero_division;
                        flags.input_flag = 1;
                        break;
                    }
                    i_arg0 = i_arg1;
                    i_arg1 = calc(op, i_arg1, i_arg2);
                    if(i_arg1 > MAX_NUMBER){
                        i_arg1 = i_arg0;
                        flags.error_flag = long_output;
                        flags.input_flag = 1;
                        break;
                    }
                    flags.input_flag = 0;
                }
                break;

            case operator:
                mystrcpy(op, arg);
                flags.input_flag = 1;
                break;

            case mp_cmd:
                mem0 = mem;
                mem = calc("+", mem, i_arg1); 
                if(mem > MAX_NUMBER){
                    mem = mem0;
                    flags.error_flag = long_output;
                } 
                flags.init_flag = 1;
                break;

            case mm_cmd:
                mem0 = mem;
                mem = calc("-", mem, i_arg1);
                if(mem > MAX_NUMBER){
                    mem = mem0;
                    flags.error_flag = long_output;
                }
                flags.init_flag = 1;
                break;

            case mr_cmd:
                i_arg2 = mem;
                if(i_arg2 == 0 && !mystrcmp(op, "/")){
                    flags.error_flag = zero_division;
                    flags.input_flag = 1;
                    break;
                }
                i_arg0 = i_arg1;
                i_arg1 = calc(op, i_arg1, i_arg2);
                if(i_arg1 > MAX_NUMBER){
                    i_arg1 = i_arg0;
                    flags.error_flag = long_output;
                    flags.input_flag = 1;
                    break;
                } 
                flags.input_flag = 0;
                break;

            case mc_cmd:
                mem = 0;    
                flags.init_flag = 1;
                break;

            case ac_cmd:
                i_arg0 = 0;
                i_arg1 = 0;
                i_arg2 = 0;
                mem = 0;
                flags.input_flag = 0;
                flags.init_flag = 1;
                break;

            case c_cmd:
                i_arg0 = 0;
                i_arg1 = 0;
                i_arg2 = 0;
                flags.input_flag = 0;
                flags.init_flag = 1;
                break;
            
            case ce_cmd:
                if(!flags.input_flag){
                    i_arg1=i_arg0;
                    i_arg2 = 0;
                    flags.input_flag = 1;
                } else if(flags.input_flag){
                    flags.input_flag = 0;
                    flags.init_flag = 1;
                }
                break;

            case q_cmd:
                printf("See you!\n");
                return 0;
            
            case error:
                flags.error_flag = invalid_input;
                flags.init_flag = 1;
                break;

            case error_len:
                flags.input_flag = 0;
                flags.error_flag = long_input;
                flags.init_flag = 1;
                break;
        }

        comment_ctrl(flags, i_arg0, i_arg1, i_arg2, mem, op);

        flags.error_flag = no_error;
        flags.init_flag = 0;
    }  
}