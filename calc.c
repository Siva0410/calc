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

int calc(char *op, int arg1, int arg2){
    int result=0;
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
    int i_arg1=0, i_arg2=0, i;
    char c_arg1[MAX_LENGTH], c_arg2[MAX_LENGTH], op[MAX_LENGTH];

//set first argment
    read(0, c_arg1, MAX_LENGTH);
    i_arg1 = myatoi(c_arg1);
    printf("%d\n", i_arg1);

while(1){
    //set operator
        read(0, op, 2);
        op[1] = '\0';
        printf("%d %s\n", i_arg1, op);

    //set second argment
        read(0, c_arg2, MAX_LENGTH);
        i_arg2 = myatoi(c_arg2);
        printf("%d %s %d\n", i_arg1, op, i_arg2);

    //result and set first argment
        i_arg1 = calc(op, i_arg1, i_arg2);    
        printf("= %d\n", i_arg1);
    }  

        return 0;
}