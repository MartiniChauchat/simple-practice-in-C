(//  dec2Base.c
//  Student ID: 260712639
//  Name: Yudi.Xie
//  Created by Yudi.Xie on 2017/9/25.
//  Copyright © 2017年 Yudi.Xie. All rights reserved.

#include <stdio.h>

int main(int argc, char *argv[]){
    int number, base,rem,i=0,dig[999];
    char base_digits[36] =
    {'0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F','G','H','I','J','K',
        'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    /*set and initialize the variables,
     and use a array to convert integer 
     to ASCII code*/

    if (argc==2){
        argv[2]="2";
        goto MATH;
    }
    /*the number of arguments is 2,
     give argument 2 a value of 2
     and jump to the math part*/
     
    
    if (argc!=3)
        {
        printf("wrong number of arguments!\n");
        return 0;
    }
    /*if the number of arguments is neither 2 or 3,
     then end the function*/
    
MATH:
    sscanf(argv[1],"%d",&number);
    sscanf(argv[2],"%d",&base);
    printf("The Base-%d Form of %d is: ",base,number);
    /*Get the number and base from arguments*/
    
    while(number>0)
    {
        rem=number%base;
        dig[i]=rem;
        i++;
        number=number/base;
    }
    /*In a while loop, divide number 
     by base and take the remainer,
     store the remainers*/
    
    i--;
    for(;i>=0;i--)
    {
        printf("%c",base_digits[dig[i]]);
    }
    printf("\n");
    /*print the result in a reversed order*/
}


