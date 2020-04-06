#include<stdio.h>

/*-------------------------------*/
#define MAX_LENGTH 10

int myatoi(char *s){
    int value=0;
    
    while(*s != '\n'){
        value = value*10 + (*s - '0');
        printf("%d\n",value);
        s++;
    }
    return value;
}

int main(){
    int i_arg1=0, i_arg2=0, i;
    char c_arg1[MAX_LENGTH], c_arg2[MAX_LENGTH], c_op[MAX_LENGTH];

//set first argment
    read(0, c_arg1, MAX_LENGTH);
    i_arg1 = myatoi(c_arg1);
    printf("%d", i_arg1);
/*
//set operator
    read(0, c_op, MAX_LENGTH);
    printf("%c ", c_op);  

//set second argment
    read(0, c_arg2,MAX_LENGTH);
    i_arg2 = myatoi(c_arg2);
    printf("%d ", i_arg2);
    */
}