#include<stdio.h>

#define MAX_LENGTH 10

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
};

int check_num(char *s){
    while(*s != '\0'){
        if('0' > *s || *s > '9' && *s != '.')
        return 0;
        if(*s == '.'){
            while(*s != '\0'){
                if('0' > *s || *s > '9')
                return 0;
                s++;
            }
        }
        s++;
    }
    return 1;
}

//Char -> Float
float myatof(char *s){
    int dec_cnt=0, i=0;
    float value=0, i_value=0, d_value=0;
    
    while(*s != '\0'){
        i_value = i_value*10 + (*s - '0');
        s++;
        if(*s == '.'){
            s++;
            while(*s != '\0'){
            //一番大きい桁から10倍して足していく
                d_value = d_value*10 + (*s - '0');
                s++;
                dec_cnt++;
            }
            //最後に小数点分ずらす
            while(i<dec_cnt){
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
    float result=0;
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
        case 'r':
            result = arg1;
            break;
        default:
            printf("error\n");
    }
    return result;
}

//入力管理
int input_ctrl(char *s, FLAG flags){
    int i=0;
    read(0, s, MAX_LENGTH);

    while(s[i] != '\n'){
        i++;
    }
    s[i] = '\0';

    if(check_num(s) && !(flags.i_flag) && !(flags.op_flag)){
        return init;
    } else if(check_num(s) && flags.i_flag){
        return integer;
    } else if (!mystrcmp(s, ":mi") && flags.i_flag){
        return mi_cmd;
    } else if(!mystrcmp(s, "+") || !mystrcmp(s, "-") || !mystrcmp(s, "*") || !mystrcmp(s, "/") || !mystrcmp(s, "r") && flags.op_flag){
        return operator;
    } else if (!mystrcmp(s, ":m+") && flags.op_flag){
        return mp_cmd;
    } else if (!mystrcmp(s, ":m-") && flags.op_flag){
        return mm_cmd;
    } else if (!mystrcmp(s, ":mr") && flags.op_flag){
        return mr_cmd;
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
        printf("error\n");
        return error;
    }

}

int main(){
    int i;
    float i_arg0=0, i_arg1=0, i_arg2=0, mem=0;
    char arg[MAX_LENGTH],op[MAX_LENGTH];
    FLAG flags = {0,0};

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
                i_arg0 = i_arg1;
                i_arg1 = calc(op, i_arg1, i_arg2);    
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
                printf("%f + %f\n", i_arg1, mem);
                i_arg0 = i_arg1;
                i_arg1 = calc("+", i_arg1, mem);    
                printf("= %f\tmemory : %f\n", i_arg1, mem);
                flags.i_flag = 0;
                flags.op_flag = 1;
                break;

            case mm_cmd:
                printf("%f - %f\n", i_arg1, mem);
                i_arg0 = i_arg1;
                i_arg1 = calc("-", i_arg1, mem);    
                printf("= %f\tmemory : %f\n", i_arg1, mem);
                flags.i_flag = 0;
                flags.op_flag = 1;
                break;

            case mi_cmd:
                i_arg2 = mem;
                printf("%f %s %f\n", i_arg1, op, i_arg2);
                i_arg0 = i_arg1;
                i_arg1 = calc(op, i_arg1, i_arg2);    
                printf("= %f\tmemory : %f\n", i_arg1, mem);
                flags.i_flag = 0;
                flags.op_flag = 1;
                break;

            case mr_cmd:
                mem = i_arg1;    
                printf("\t\tmemory : %f\n", mem);
                break;

            case mc_cmd:
                mem = 0;    
                printf("\t\tmemory : %f\n", mem);
                break;

            case ac_cmd:
                i_arg0=0;
                i_arg1=0;
                i_arg2=0;
                mem=0;
                flags.i_flag = 0;
                flags.op_flag = 0;
                continue;

            case c_cmd:
                i_arg0=0;
                i_arg1=0;
                i_arg2=0;
                flags.i_flag = 0;
                flags.op_flag = 0;
                continue;
            
            case ce_cmd:
                if(flags.op_flag == 1){
                    i_arg1=i_arg0;
                    i_arg2=0;
                    printf("%f %s\tmemory : %f\n", i_arg1, op, mem);
                    flags.i_flag = 1;
                    flags.op_flag = 0;
                } else if(flags.i_flag == 1){
                    printf("%f \tmemory : %f\n", i_arg1, mem);
                    flags.i_flag = 0;
                    flags.op_flag = 1;
                }
                continue;

            case q_cmd:
                return 0;
            
        }
    }  
}