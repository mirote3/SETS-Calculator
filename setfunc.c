/*This file contains all the auxiliary functions to read and analyze the input*/
#include  "set.h"

extern char commandline[];
extern int location;
extern set *sets[];
char *commands[]= {"read_set","print_set","union_set","intersect_set","sub_set","symdiff_set","stop"};
char *sets_name[] = {"SETA","SETB","SETC","SETD","SETE","SETF"};


/*This function recives a pointer to array of pointers to sets, and initialize all cells of all the sets to zero.*/
void initialize_set(set **p)
{
    int i;
    for(i=0; i<NUM_OF_SETS ; i++){
        p[i]->cell1=0;
        p[i]->cell2=0;
        p[i]->cell3=0;
        p[i]->cell4=0;
    }
    return;
}

/*This function read the command from the command line, analyze the command requested, and return the index of the command (By enum functions).
if an error found, the value of this error will return (By enum errors)  */
int read_command()
{
    int i,j,command_index= UndefinedCommand;
    char command[MAX_COMMAND];
    
    get_line();   
    location = 0;  /*the variable 'location' shows us where are stand at the char array that contain the command line*/
    j=0;
    i=0;
    
    while(isspace(commandline[i]))
        ++i;
    
    /*isolate the command name into new character array*/
    while(!isspace(commandline[i]) && commandline[i]!=',')
    {
        if(commandline[i]==EOF){
           printf("THE INPUT IS OVER! -- EOF -- \n");
           exit(0);
        }
        command[j]=commandline[i];
        ++i;
        ++j;
        
    }
    command[j]='\0';  
 
    location = i;
    
    
    while(isspace(commandline[i]))
        i++;
    if(commandline[i]==',')
        return IllegalComma;    

    /*comare the isolated command with all the possible commands.*/
    for(i=0;i<NUM_OF_COMMANDS ;i++)
        if(strcmp(command,commands[i])==0)
            command_index=i;

     
    return command_index;
}


/*This function read name of one set drom the input, she recive a flag that signifies if a comma needs to appear after the set name.
if error found, the function return the value of this error (from the enum errors), else it return the index of the requested set.*/
int read_one_set(int flag)
{
    int i,j,set_index =UndefinedSet; 
    char *s;

    j=0;
    i=location;
    s=(char *)malloc(MAX_COMMAND * sizeof(char));
    
    if(commandline[i]=='\0')
        return MissedPar;
    
    while(isspace(commandline[i]))
        i++; 
    
    if(commandline[i]==',')
        return IllegalComma;
    
    if(commandline[i]=='\0')
        return MissedPar;
    
    /*isolate the set name into new array*/
   while(!isspace(commandline[i]) && commandline[i]!=',' && commandline[i]!='\0')
    {
        
        if(commandline[i]==EOF){
           printf("THE INPUT IS OVER! -- EOF -- \n");
           exit(0);
        }
        s[j]=commandline[i];
        i++;
        j++;
    }
    if(j==0)
        return UndefinedSet;
    
    s[j]='\0';    

    if(flag){ /*if the flag is 'WITHCOMMA' this if block will check if there is a comma after the set name.*/
        while(isspace(commandline[i]))  
            i++;
        
        if(commandline[i]==EOF){
            printf("THE INPUT IS OVER! -- EOF -- \n");
            exit(0);
          }

        if(commandline[i]=='\0')
            return MissedPar; 

        if(commandline[i]!=',')
            return MissedComma; 
        i++;    
        
    }


    location =i;
    /*comparing the set from the input to all the possible set names. */
    for(j=0;j<NUM_OF_SETS ;j++)  
        if(strcmp(s,sets_name[j])==0)
            set_index=j;

    /*If after the set name nothing needs to come, this block check if a garbage data inserted*/
    if((!flag) && set_index>=0) 
    {
        while (isspace(commandline[i]))
            i++;

        if(commandline[i]==EOF){
            printf("THE INPUT IS OVER! -- EOF -- \n");
            exit(0);
        }

        if(commandline[i]!='\0')
            return Garbage;  
    }        

    free(s);
    return set_index;   
}

/*This function recives a pointer to array of 3 pointers to sets, and implement there the pointers to sets according to the input.
The function uses the function 'read_one_set' three times, with different flags. If an error found, the function will return the corresponding value.*/
int read_three_set(set **p)
{
    int set_ind1,set_ind2,set_ind3;

    set_ind1 = read_one_set(WithComma); 
    if(set_ind1<0)
        return set_ind1;
    set_ind2= read_one_set(WithComma);
    if(set_ind2<0)
        return set_ind2;
    set_ind3= read_one_set(WithoutComma);
    if(set_ind3<0)
        return set_ind3;

    p[0]= sets[set_ind1];
    p[1]= sets[set_ind2];
    p[2]= sets[set_ind3];

    return 0;
}

/*This function read the command line from the input and implement the string in global character array*/
int get_line()
{
    char c;
    int i=0;
    
    while((c=getchar())!='\n' && c!=EOF){
        commandline[i]=c;
        i++;
    }

    if(c == EOF)
        commandline[i++]=EOF;
    
    commandline[i]='\0';

    printf("\nCommand Line Inserted:  %s\n",commandline);
    
    
    return 1;

}
