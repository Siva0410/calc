#include<stdio.h>

/*-------------------------------*/
#define MAX_LENGTH 10

float myatoi(char *s){
    int dec_cnt=0;
    float value=0;
    
    while(*s != '\n'){
        if(*s != '.'){
            value = value*10 + (*s - '0');
        } else {
            dec_cnt = -1;
        }
        s++;
        dec_cnt++;
    }
    value = value*dec_cnt*0.1;
    return value;
}

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

int main(){
    int i;
    float i_arg1=0, i_arg2=0;
    char c_arg1[MAX_LENGTH], c_arg2[MAX_LENGTH], op[MAX_LENGTH];

//set first argment
    read(0, c_arg1, MAX_LENGTH);
    i_arg1 = myatoi(c_arg1);
    printf("%f\n", i_arg1);

while(1){
    //set operator
        read(0, op, 2);
        op[1] = '\0';
        printf("%f %s\n", i_arg1, op);

    //set second argment
        read(0, c_arg2, MAX_LENGTH);
        i_arg2 = myatoi(c_arg2);
        printf("%f %s %f\n", i_arg1, op, i_arg2);

    //result and set first argment
        i_arg1 = calc(op, i_arg1, i_arg2);    
        printf("= %f\n", i_arg1);
    }  

        return 0;
}