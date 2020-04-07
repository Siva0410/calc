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
float myatoi(char *s){
    int dec_cnt=0, i=0;
    float value=0, i_value=0, d_value=0;
    
    while(*s != '\n'){
        i_value = i_value*10 + (*s - '0');
        s++;
        if(*s == '.'){
            s++;
            while(*s != '\n'){
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
    read(0, s, MAX_LENGTH);
    if(!(flags.i_flag) && !(flags.op_flag) && !(flags.cmd_flag)){
        return init;
    } else if('0' <= s[0] && s[0] <= '9' && flags.i_flag){
        return integer;
    } else if(s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/' || s[0] == 'r' && flags.op_flag){
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
                i_arg1 = myatoi(arg);
                printf("%f\n", i_arg1);
                flags.i_flag = 0;
                flags.op_flag = 1;
                flags.cmd_flag = 1;
                break;

            case integer:
                i_arg2 = myatoi(arg);
                printf("%f %s %f\n", i_arg1, op, i_arg2);
                i_arg1 = calc(op, i_arg1, i_arg2);    
                printf("= %f\n", i_arg1);
                flags.i_flag = 0;
                flags.op_flag = 1;
                flags.cmd_flag = 1;
                break;

            case operator:
                op[0] = arg[0];
                op[1] = '\0';
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