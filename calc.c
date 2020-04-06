#include<stdio.h>

#define MAX_LENGTH 10

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

//コマンド呼び出し
void call_cmd(char* s){
    switch(s[1]){
        case 'q':
        case 'c':
            break;
    }
}

//入力管理
int input_cntl(char *s, int i_flg, int op_flg, int cmd_flg){
    read(0, s, MAX_LENGTH);
    if('0' <= s[0] && s[0] <= '9' && i_flg){
        return 0;
    } else if(s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/' || s[0] == 'r' && op_flg){
        return 0;
    } else if (s[0] == ':' && cmd_flg){
        call_cmd(s);
        return 0;
    } else {
        printf("error\n");
        return 1;
    }

}

int main(){
    int i;
    float i_arg1=0, i_arg2=0;
    char c_arg1[MAX_LENGTH], c_arg2[MAX_LENGTH], op[MAX_LENGTH];

//set first argment
    while(input_cntl(c_arg1, 1, 0, 1));
    //read(0, c_arg1, MAX_LENGTH);
    i_arg1 = myatoi(c_arg1);
    printf("%f\n", i_arg1);

    while(1){
    //set operator
        while(input_cntl(op, 0, 1, 1));
        op[1] = '\0';
        printf("%f %s\n", i_arg1, op);

    //set second argment
        while(input_cntl(c_arg2, 1, 0, 1));
        i_arg2 = myatoi(c_arg2);
        printf("%f %s %f\n", i_arg1, op, i_arg2);

    //result and set first argment
        i_arg1 = calc(op, i_arg1, i_arg2);    
        printf("= %f\n", i_arg1);
    }  

        return 0;
}