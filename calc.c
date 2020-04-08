#include<stdio.h>

#define MAX_LENGTH 20
#define MAX_NUMBER 99999999
typedef struct {
    int i_flag;
    int op_flag;
    //int cmd_flag;
} FLAG;

enum CMD {
    init,
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

//入力管理
int input_ctrl(char *s, FLAG flags){
    int check_len = 0, i = 0;

    read(0, s, MAX_LENGTH);

    while(s[i] != '\n'){
        i++;
    }
    s[i] = '\0';

    if((check_len=check_num(s)) && !(flags.i_flag) && !(flags.op_flag)){
        if(check_len == error_len) return error_len;
        return init;
    } else if((check_len=check_num(s)) && flags.i_flag){
        if(check_len == error_len) return error_len;
        return integer;
    } else if (!mystrcmp(s, ":mr") && flags.i_flag){
        return mr_cmd;
    } else if(!mystrcmp(s, "+") || !mystrcmp(s, "-") || !mystrcmp(s, "*") || !mystrcmp(s, "/") && flags.op_flag){
        return operator;
    } else if (!mystrcmp(s, ":m+") && flags.op_flag){
        return mp_cmd;
    } else if (!mystrcmp(s, ":m-") && flags.op_flag){
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
        printf("%d\n",check_len);
        return error;
    }

}

int main(){
    int i;
    float i_arg0 = 0, i_arg1 = 0, i_arg2 = 0, mem = 0, mem0 = 0;
    char arg[MAX_LENGTH],op[MAX_LENGTH];
    FLAG flags = {0,0};

    printf("Hello! Please input number.\n");

    while(1){
        switch(input_ctrl(arg, flags)){
            case init:
                i_arg1 = myatof(arg);
                printf("%f\tmemory : %f\n", i_arg1, mem);
                flags.i_flag = 0;
                flags.op_flag = 1;
                break;

            case integer:
                i_arg2 = myatof(arg);
                printf("%f %s %f\n", i_arg1, op, i_arg2);
                if(i_arg2 == 0 && !mystrcmp(op, "/")){
                    printf("Error:Zero division\n");
                    printf("%f %s\tmemory : %f\n", i_arg1, op, mem);
                    flags.i_flag = 1;
                    flags.op_flag = 0;
                    break;
                }
                i_arg0 = i_arg1;
                i_arg1 = calc(op, i_arg1, i_arg2);
                if(i_arg1 > MAX_NUMBER){
                    printf("Error:Too long output\n");
                    printf("%f %s\tmemory : %f\n", i_arg0, op, mem);
                    i_arg1 = i_arg0;
                    flags.i_flag = 1;
                    flags.op_flag = 0;
                    break;
                }
                printf("= %f\tmemory : %f\n", i_arg1, mem);
                flags.i_flag = 0;
                flags.op_flag = 1;
                break;

            case operator:
                mystrcpy(op, arg);
                printf("%f %s\tmemory : %f\n", i_arg1, op, mem);
                flags.i_flag = 1;
                flags.op_flag = 0;
                break;

            case mp_cmd:
                printf("\t\tmemory : %f + %f\n", mem, i_arg1);
                mem0 = mem;
                mem = calc("+", mem, i_arg1); 
                if(mem > MAX_NUMBER){
                    printf("Error:Too long output\n");
                    printf("%f\tmemory : %f\n", i_arg1, mem0);
                    mem = mem0;
                    break;
                }   
                printf("%f\tmemory : %f\n", i_arg1, mem);
                break;

            case mm_cmd:
                printf("\t\tmemory : %f - %f\n", mem, i_arg1);
                mem0 = mem;
                mem = calc("-", mem, i_arg1);
                if(mem > MAX_NUMBER){
                    printf("Error:Too long output\n");
                    printf("%f\tmemory : %f\n", i_arg1, mem0);
                    mem = mem0;
                    break;
                }
                printf("%f\tmemory : %f\n", i_arg1, mem);
                break;

            case mr_cmd:
                i_arg2 = mem;
                printf("%f %s %f\n", i_arg1, op, i_arg2);
                if(i_arg2 == 0 && !mystrcmp(op, "/")){
                    printf("Error:Zero division\n");
                    printf("%f %s\tmemory : %f\n", i_arg1, op, mem);
                    flags.i_flag = 1;
                    flags.op_flag = 0;
                    break;
                }
                i_arg0 = i_arg1;
                i_arg1 = calc(op, i_arg1, i_arg2);
                if(i_arg1 > MAX_NUMBER){
                    printf("Error:Too long output\n");
                    printf("%f %s\tmemory : %f\n", i_arg0, op, mem);
                    i_arg1 = i_arg0;
                    flags.i_flag = 1;
                    flags.op_flag = 0;
                    break;
                } 
                printf("= %f\tmemory : %f\n", i_arg1, mem);
                flags.i_flag = 0;
                flags.op_flag = 1;
                break;

            case mc_cmd:
                mem = 0;    
                printf("\t\tmemory : %f\n", mem);
                break;

            case ac_cmd:
                i_arg0 = 0;
                i_arg1 = 0;
                i_arg2 = 0;
                mem = 0;
                flags.i_flag = 0;
                flags.op_flag = 0;
                break;

            case c_cmd:
                i_arg0 = 0;
                i_arg1 = 0;
                i_arg2 = 0;
                flags.i_flag = 0;
                flags.op_flag = 0;
                break;
            
            case ce_cmd:
                if(flags.op_flag == 1){
                    i_arg1=i_arg0;
                    i_arg2 = 0;
                    printf("%f %s\tmemory : %f\n", i_arg1, op, mem);
                    flags.i_flag = 1;
                    flags.op_flag = 0;
                } else if(flags.i_flag == 1){
                    printf("%f \tmemory : %f\n", i_arg1, mem);
                    flags.i_flag = 0;
                    flags.op_flag = 1;
                }
                break;

            case q_cmd:
                printf("See you!\n");
                return 0;
            
            case error:
                printf("Error:Invalid input\n");
                if(flags.i_flag == 0 && flags.op_flag == 0){
                    printf("Please input fist term or available commands.\n");
                } else if(flags.i_flag == 0 && flags.op_flag == 1){
                    printf("Please input any operator or available commands.\n");
                    printf("%f\tmemory : %f\n", i_arg1, mem);
                } else if(flags.i_flag == 1 && flags.op_flag == 0){
                    printf("Please input second term or available commands.\n");
                    printf("%f %s\tmemory : %f\n", i_arg1, op, mem);
                }
                break;

            case error_len:
                printf("Error:Too long input\n");
                if(flags.i_flag == 0 && flags.op_flag == 0){
                    printf("Please input appropriate length number.\n");
                } else if(flags.i_flag == 1 && flags.op_flag == 0){
                    printf("Please input appropriate length number.\n");
                    printf("%f %s\tmemory : %f\n", i_arg1, op, mem);
                }
                break;
        }
    }  
}