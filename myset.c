/*This program is calculator for sets. the user insert commands about set and the program make the actions.
This file contains all the interaction with the user: guide massages, reading input, and print to output massages about errors.
The main function uses auxiliary functions to analyze the input,and active the requested commands or send error massage if found one.*/


#include  "set.h" 

char commandline[MAX_COMMAND_LINE];  /*array for the inserted command line*/
int location=0;
set SETA,SETB,SETC,SETD,SETE,SETF, **p; 
set *sets[]={&SETA,&SETB,&SETC,&SETD,&SETE,&SETF};


/* main: read commands from the stdin until the command 'stop' inserted or EOF. if there is a syntax error, main will print massage
and won't make the command. main uses auxiliary functions to read the input, analyze it, and behave according to the returned value of
the functionss */

int main()
{
    int command_ind,set_ind,flag;
    
    initialize_set(sets);
    p=(set **)malloc(3*sizeof(set *));    
    
    /*----------INTRUCTIONS----------*/
    printf("\tHELLO,\n\tThis program is calcultor for sets.\n ");
    printf("\n------------------Instrucrions-------------------\n");
    printf("\tThe Available commands are:\n\n");
    printf("\t1.read_set - Recive One Parameter\n\t2.print_set - Recive One Parameter\n\t");
    printf("3.union_set - Recive 3 Parametres\n\t4.intersect_set - Recive 3 Parametres\n\t5.sub_set - Recive 3 Parametres\n\t6.stmdiff_set - Recive 3 Parametres\n\n");
    printf("\tTo stop the program, Enter the command 'stop' \n");
    printf("\tIf you use 'read_set',the final parameter MUST be -1\n");
    printf("\n\tThe Available Sets ARE :\n\t-SETA\n\t-SETB\n\t-SETC\n\t-SETD\n\t-SETE\n\t-SETF\n");
    printf("\tEach Set Can Contain The Numbers Between 0 To 127\n");
    printf("\n\tNotice! The Parameter Name MUST Be in Uppercase, There Must Be A Comma Between The Parameters.\n");

    printf("\n\n\tPlease enter command:\n");

    
    /* The main start the read commands using the function 'read_command' until 'stop' entered or EOF*/
    
    while((command_ind=read_command())!=Stop)
    {

        switch (command_ind)
        {
        case UndefinedCommand:
                printf("Undefined command name !\n");
                break;
        case IllegalComma:
            printf("Illegal comma\n");
            break;
        case Read:
                set_ind=read_one_set(WithComma); 
                switch (set_ind)
                {
                case IllegalComma:
                    printf("Illegal comma\n");
                    break;
                case MissedPar:
                    printf("Missing Parameter\n");
                    break;
                case MissedComma: 
                    printf("read_one_set:Missed comma\n");
                    break;
                case UndefinedSet: 
                    printf("Undefined set name\n");
                    break;
                case ExtraComma: 
                    printf("Extra comma\n");  
                    break; 
                case BadTerminate:
                    printf("Command Line didn't terminated correctly\n");
                    break;    
                default: 
                        flag=read_set(sets[set_ind]); 
                        switch(flag)
                        {
                            case MissedComma: 
                                printf("Missed comma\n");
                                break;
                            case InvaildSetMem: 
                                printf("Invaild set member inserted\n");
                                break;
                            case ExtraComma: 
                                printf("Extra comma\n");  
                                break; 
                            case FloatNum:
                                printf("Float number inserted, Please insert only integers.\n");
                                break;
                            case BadTerminate:
                                printf("List of numbers didn't terminated correctly\n");
                                break; 
                            case Garbage:
                                printf("Extraneous text after end of command\n");
                                break;              
                            default:
                                break;
                        }
                        break;
                    
                }
                break;
        case Print: 
                set_ind=read_one_set(WithoutComma); 
                switch (set_ind)
                {
                case IllegalComma:
                    printf("Illegal comma\n");
                    break;
                case MissedPar:
                    printf("Missing Parameter\n");
                    break; 
                case MissedComma: 
                    printf("Missed comma\n");
                    break;
                case UndefinedSet: 
                    printf("Undefined set name\n");
                    break;
                case ExtraComma:
                    printf("Extra comma\n");  
                    break; 
                case BadTerminate:
                    printf("Command Line didn't terminated correctly\n");
                    break;
                case Garbage:
                    printf("Extraneous text after end of command\n");
                    break;         
                default: 
                        print_set(sets[set_ind]);
                        break;
                    
                }
                break;
        case Union:
                set_ind=read_three_set(p);
                switch (set_ind)
                {
                case IllegalComma:
                    printf("Illegal comma\n");
                    break;
                case MissedPar:
                    printf("Missing Parameter\n");
                    break;
                case MissedComma: 
                    printf("Missed comma\n");
                    break;
                case UndefinedSet: 
                    printf("Undefined set name\n");
                    break;
                case ExtraComma: 
                    printf("Extra comma\n");  
                    break; 
                case BadTerminate:
                    printf("Command Line didn't terminated correctly\n");
                    break;
                case Garbage:
                    printf("Extraneous text after end of command\n");
                    break;
                default:
                    union_set(p);
                    break;
                }
                break;
        case Intersect:
                set_ind=read_three_set(p);
                switch (set_ind)
                {
                case IllegalComma:
                    printf("Illegal comma\n");
                    break;
                case MissedPar:
                    printf("Missing Parameter\n");
                    break;
                case MissedComma: 
                    printf("Missed comma\n");
                    break;
                case UndefinedSet: 
                    printf("Undefined set name\n");
                    break;
                case ExtraComma: 
                    printf("Extra comma\n");  
                    break; 
                case BadTerminate:
                    printf("Command Line didn't terminated correctly\n");
                    break;
                case Garbage:
                    printf("Extraneous text after end of command\n"); 
                    break;   
                default:
                   intersect_set(p);
                    break;
                }
                break;
        case Sub:
                set_ind=read_three_set(p);
                switch (set_ind)
                {
                case IllegalComma:
                    printf("Illegal comma\n");
                    break;
                case MissedPar:
                    printf("Missing Parameter\n");
                    break;
                case MissedComma: 
                    printf("Missed comma\n");
                    break;
                case UndefinedSet: 
                    printf("Undefined set name\n");
                    break;
                case ExtraComma: 
                    printf("Extra comma\n");  
                    break; 
                case BadTerminate:
                    printf("Command Line didn't terminated correctly\n");
                    break;
                case Garbage:
                   printf("Extraneous text after end of command\n");
                   break;  
                default:
                    sub_set(p);
                    break;
                }
                break;
        case Symdiff:
                set_ind=read_three_set(p);
                switch (set_ind)
                {
                case IllegalComma:
                    printf("Illegal comma\n");
                    break;
                case MissedPar:
                    printf("Missing Parameter\n");
                    break;
                case MissedComma: 
                    printf("Missed comma\n");
                    break;
                case UndefinedSet: 
                    printf("Undefined set name\n");
                    break;
                case ExtraComma: 
                    printf("Extra comma\n");  
                    break; 
                case BadTerminate:
                    printf("Command Line didn't terminated correctly\n");
                    break;
                case Garbage:
                    printf("Extraneous text after end of command\n");
                    break;   
                default:
                    symdiff_set(p);
                    break;
                }
                break;
            default:
                break;    
         
        }
        
        printf("\nPlease enter command:\n");
    }    
    
    
    free(p);   
    return 0;
}



