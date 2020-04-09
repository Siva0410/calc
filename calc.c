#include<stdio.h>

#define MAX_LENGTH 20
#define MAX_NUMBER 10000000
#define SIGNIFICANT_DEGIT 7
typedef struct {
    int input_flag; //1: input number 0: input operator
    int init_flag;  //1: init 0: continue
    int error_flag; //one of ERROR status
} FLAG;

enum INPUT {
    q_cmd,
    c_cmd,
    ce_cmd,
    mp_cmd,
    mm_cmd,
    mi_cmd,
    mc_cmd,
    mr_cmd,
    ac_cmd,
    number,
    operator,
    error_invalid_input,
    error_length,
};

enum ERROR {
    no_error,
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
	      d_value = d_value*10 + (*s - '0');
	      d_cnt++;
	      s++;
	    }
            while(d_cnt > i){
                d_value = d_value*0.1;
		i++;
            }
            value = i_value + d_value;
            return value;
        }
    }
    return i_value;
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

//Calculate +,-,*,/
float calc(char *op, float arg1, float arg2){
    float result = 0;
    switch(*op){
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

//if arg is not number return 0
//else return length of number
int check_num(char *s){
    int i_cnt = 0;
    while(*s != '\0'){
        if(*s == '.' && i_cnt > 0){
            s++;
            while(*s != '\0'){
                if('0' > *s || *s > '9') return 0;
                s++;
            }
            return i_cnt;
        }
        if('0' > *s || *s > '9') return 0;
        i_cnt++;
        s++;
    }
    return i_cnt;
}

//alaysis arg and return CMD TAG
int input_ctrl(char *s, int input_num_len, FLAG flags){
    int int_len = 0, dec_len = 0;

    int_len = check_num(s);
    dec_len = input_num_len - (int_len + 1);
    if (int_len != 0 && flags.input_flag){
        if(int_len > 7 || dec_len > 7) return error_length;
        return number;
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
        return error_invalid_input;
    }

}

//print statements according to flags
void comment_ctrl(FLAG flags, float arg0, float arg1, float arg2, float mem, char *op){
  int int_num = 0, dec_num[4] = {}, i = 0;
  float cnt[4] = {};
    cnt[0] = arg0;
    cnt[1] = arg1;
    cnt[2] = arg2;
    cnt[3] = mem;

    while(i < 4){
      int_num = 0;
      while(cnt[i] >= 1){
	cnt[i] = cnt[i]/10;
	int_num++;
      }
      dec_num[i] = SIGNIFICANT_DEGIT - int_num;
      i++;
    }
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
	  printf("%-8.*f\tmemory : %-8.*f\n", dec_num[1], arg1, dec_num[3], mem);
        } else if(!flags.input_flag){
	  printf("%-8.*f %s %-8.*f\n", dec_num[0], arg0, op, dec_num[2], arg2);
	  printf("= %-8.*f\tmemory : %-8.*f\n", dec_num[1], arg1, dec_num[3], mem);
        } else if(flags.input_flag && flags.init_flag){
	  printf("Please input number.\tmemory : %-8.*f\n", dec_num[3], mem);
        } else{
	  printf("%-8.*f %s\tmemory : %-8.*f\n", dec_num[1], arg1, op, dec_num[3], mem);
        }
}

int main(){
    int input_num_len = 0, input_len = 0;
    float i_arg0 = 0, i_arg1 = 0, i_arg2 = 0, mem = 0, mem0 = 0;
    char arg[MAX_LENGTH+1], op[MAX_LENGTH+1];
    char *cnt;
    FLAG flags = {1, 1, no_error};

    printf("Hello! Please input number.\n");

    while(1){
        //input
        input_num_len = 0;
        input_len = read(0, arg, MAX_LENGTH);
        if(input_len == 0){
            printf("Error: Invalid input EOF\n");
            return -1;
        }
        *(arg+input_len) = '\0';
        cnt = arg;
        while(*cnt != '\n' && *cnt != '\0'){
            input_num_len++;
            cnt++;
        }
        *cnt = '\0';

        switch(input_ctrl(arg, input_num_len, flags)){
            case number:
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
                flags.init_flag = 0;
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
                flags.input_flag = 1;
                flags.init_flag = 1;
                break;

            case c_cmd:
                i_arg0 = 0;
                i_arg1 = 0;
                i_arg2 = 0;
                flags.input_flag = 1;
                flags.init_flag = 1;
                break;
            
            case ce_cmd:
                if(!flags.input_flag){
                    i_arg1=i_arg0;
                    i_arg2 = 0;
                    flags.input_flag = 1;
                } else if(flags.input_flag && flags.init_flag){
                    i_arg0 = 0;
                    i_arg1 = 0;
                    i_arg2 = 0;
                } else if(flags.input_flag){
                    flags.input_flag = 0;
                    flags.init_flag = 1;
                }
                break;

            case q_cmd:
                printf("See you!\n");
                return 0;
            
            case error_invalid_input:
                flags.error_flag = invalid_input;
                flags.init_flag = 1;
                break;

            case error_length:
                flags.input_flag = 1;
                flags.error_flag = long_input;
                break;
        }

        comment_ctrl(flags, i_arg0, i_arg1, i_arg2, mem, op);

        flags.error_flag = no_error;
    }  
}
