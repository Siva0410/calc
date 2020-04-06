#include<stdio.h>

/*-------------------------------*/
#define MAX_LENGTH 10

int myatoi(char *s){
    int value=0;
    
    while(*s != '\n'){
        value = value*10 + (*s - '0');
        s++;
    }
    return value;
}

int calc(*c, arg1, arg2){
    int result=0;
    switch(c){
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
    int i_arg1=0, i_arg2=0, i;
    char c_arg1[MAX_LENGTH], c_arg2[MAX_LENGTH], c_op[MAX_LENGTH];

//set first argment
    read(0, c_arg1, MAX_LENGTH);
    i_arg1 = myatoi(c_arg1);
    printf("%d\n", i_arg1);

while(1){
    //set operator
        read(0, c_op, MAX_LENGTH);
        printf("%d %c\n", i_arg1, c_op);

    //set second argment
        read(0, c_arg2, MAX_LENGTH);
        i_arg2 = myatoi(c_arg2);
        printf("%d %c %d\n", i_arg1, c_op, i_arg2);

    //result and set first argment
        i_arg1 = calc(c_op, arg1, arg2);    
        printf("%d\n", i_arg1);
    }  

        return 0;
}