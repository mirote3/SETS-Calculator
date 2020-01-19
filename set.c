/* This file includes all the functions that the user of myset.c can use*/

#include "set.h"

extern char commandline[];
extern int location;


/*this function recives a pointer to the set we need to read into.
  the function have multiply  input error check and if error fount the corresponding value will return 
  to the caller. If the function didn't found any error in the input the numbers inserted will implement into the set*/
int read_set(set *p)
{
    int i,j,current_num,cell,member;
    unsigned int mask, *q;
    char *num_string;
    set SET_NEW;
    /*initialize all the variables*/
    num_string = (char *)malloc(MAX_NUM_LENGHT * sizeof(char));
    i= location;
    j=current_num=0;
    mask=1;
    q = (unsigned int *)&SET_NEW;
    
    /*initialize the new set*/
    SET_NEW.cell1=0;
    SET_NEW.cell2=0;
    SET_NEW.cell3=0;
    SET_NEW.cell4=0;

    while(current_num!=END_OF_SET )
    {
        cell=0;
        member=0;
        j=0;
       
        while(isspace(commandline[i]))
            i++;
        if(commandline[i]=='\0')
            return BadTerminate;
        if(commandline[i]==EOF){
           printf("THE INPUT IS OVER! -- EOF -- \n");
           exit(0);
        }
        
        
        if(commandline[i]==',')
            return ExtraComma; 
        if (!isdigit(commandline[i]) && commandline[i]!='-')
            return InvaildSetMem;
        
        if(commandline[i]=='-')
        {
          if(isdigit(commandline[i+1]))  
            num_string[j++]=commandline[i++];
          else
            return InvaildSetMem; 
        }
        
        while(isdigit(commandline[i]))
            num_string[j++]=commandline[i++]; /*reading the number from the output */

        num_string[j]='\0';    
        
        current_num= atoi(num_string); /*convert the string into actual integer*/

        if(current_num==END_OF_SET)
            continue;

        if(commandline[i]=='.')
            return FloatNum; 

        while (isspace(commandline[i]))
            i++;
        
        if(commandline[i]=='\0')
            return BadTerminate;
        
        if(commandline[i]==',') /*After a number must come comma*/
            i++;
        else
            return MissedComma;
    
        if(current_num<MIN_SET_MEMBER || current_num>MAX_SET_MEMBER)
            return InvaildSetMem;
        
        cell = current_num/32;
        member = current_num%32; /*calculate which bit to turn on in the set*/
        q[cell]|=(mask<<member);
  
    }

    while (isspace(commandline[i]))
            i++;
        if(commandline[i]!='\0')
            return Garbage;
 

    free(num_string);
    *p=SET_NEW;
    
    return 1;

}

/*This function recive array of three pointers to sets, and union the numbers in the two first set, and implement the result in the third set*/
void union_set(set **p)
{
    set NEW_SET;
    int *p_new, *p_a, *p_b, i;

    p_new =(int *)&NEW_SET;
    p_a = (int *)p[0];
    p_b=(int *)p[1];

    for(i=0; i<CELLS_NUM; i++)
        p_new[i] = p_a[i]|p_b[i];
    
    *(p[2])=NEW_SET;
  
}

/*This function recive array of three pointers to sets,calculate the intersect of the two first set, and implement the result in the third set */
void intersect_set(set **p)
{
    set NEW_SET;
    int *p_new, *p_a, *p_b, i;

    p_new =(int *)&NEW_SET;
    p_a = (int *)p[0];
    p_b=(int *)p[1];

    for(i=0; i<CELLS_NUM; i++)
        p_new[i] = p_a[i]&p_b[i];
    
    *(p[2])=NEW_SET;
}

/*This function recive array of three pointers to sets,calculate the substract of the second set from the first set,and implement the result in the third set */
void sub_set(set **p)
{
    set NEW_SET;
    int *p_new, *p_a, *p_b, i;

    p_new =(int *)&NEW_SET;
    p_a = (int *)p[0];
    p_b=(int *)p[1];

    for(i=0; i<CELLS_NUM; i++)
        p_new[i] = p_a[i]&(~p_b[i]);
    
    *(p[2])=NEW_SET;
}

/*This function recive array of three pointers to sets,calculate the symetric differnce of the two first set, and implement the result in the third set 
  the function uses the function intersect_set,union_set and sub_set*/
void symdiff_set(set **p)
{
    set UNION_SET,INTERSECT_SET,**q;

    q=(set**)malloc(3*sizeof(set *));
    q[0]=p[0];
    q[1]=p[1];
    q[2]=&UNION_SET;
    union_set(q);
    q[2]=&INTERSECT_SET;
    intersect_set(q);
    q[0]=&UNION_SET;
    q[1]=&INTERSECT_SET;
    q[2]=p[2];
    sub_set(q);

    free(q);
} 

/*This function recive pointer to set and print all the numbers exist in this set*/
void print_set(set *p)
{
    unsigned int mask=1, *q;
    int count_prints=0, i,j;

    q = (unsigned int *)p;
    
    printf("The Numbers Are: \n");
    /*This loop passing all the set cells and in each cell checks which bits are on, and prints to the screen the corresponding value*/
    for(i=0; i<CELLS_NUM;i++)
        for(j=0;j<BITS_IN_CELL;j++)
        {
                if(q[i] & (mask<<j) ){
                printf("%d\t",i*BITS_IN_CELL+j);
                count_prints++;
                if(count_prints%MAX_LINE_PRINTS==0)
                    printf("\n");
                }
       }
    if(!count_prints)
        printf("The set is empty\n");   
    else        
        printf("\n");
    
    return;
}