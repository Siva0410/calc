#include<stdio.h>

#define MAX_LENGTH 10

typedef struct {
    int i_flag;
    int op_flag;
    int cmd_flag;
} FLAG;

enum CMD {
    init,
    q_cmd,
    c_cmd,
    loop,
    integer,
    operator,
    error,
};

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

    if(!(flags.i_flag) && !(flags.op_flag) && !(flags.cmd_flag)){
        return init;
    } else if('0' <= s[0] && s[0] <= '9' && flags.i_flag){
        return integer;
    } else if(!mystrcmp(s, "+") || !mystrcmp(s, "-") || !mystrcmp(s, "*") || !mystrcmp(s, "/") || !mystrcmp(s, "r") && flags.op_flag){
        return operator;
    } else if (s[0] == ':' && flags.cmd_flag){
        switch(s[1]){
            case 'q':
                return q_cmd;
            case 'c':
                return c_cmd;
        }
    } else {
        printf("error\n");
        return error;
    }

}

int main(){
    int i;
    float i_arg1=0, i_arg2=0;
    char arg[MAX_LENGTH],op[MAX_LENGTH];
    FLAG flags = {0,0,0};

    while(1){
        switch(input_ctrl(arg, flags)){
            case init:
                i_arg1 = myatof(arg);
                printf("%f\n", i_arg1);
                flags.i_flag = 0;
                flags.op_flag = 1;
                flags.cmd_flag = 1;
                break;

            case integer:
                i_arg2 = myatof(arg);
                printf("%f %s %f\n", i_arg1, op, i_arg2);
                i_arg1 = calc(op, i_arg1, i_arg2);    
                printf("= %f\n", i_arg1);
                flags.i_flag = 0;
                flags.op_flag = 1;
                flags.cmd_flag = 1;
                break;

            case operator:
                mystrcpy(op, arg);
                printf("%f %s\n", i_arg1, op);
                flags.i_flag = 1;
                flags.op_flag = 0;
                flags.cmd_flag = 1;
                break;

            case c_cmd:
                i_arg1=0;
                i_arg2=0;
                flags.i_flag = 0;
                flags.op_flag = 0;
                flags.cmd_flag = 0;
                continue;
            
            case q_cmd:
                return 0;
        }
    }  
}