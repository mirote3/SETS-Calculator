/*This is the header file which includes all the defines, enums, typedef and functions prototypes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_COMMAND_LINE 1000
#define MAX_COMMAND 50
#define CELLS_NUM 4
#define BITS_IN_CELL 32
#define MAX_LINE_PRINTS 16
#define NUM_OF_SETS 6
#define NUM_OF_COMMANDS 7
#define MAX_SET_MEMBER 127
#define MIN_SET_MEMBER 0
#define MAX_NUM_LENGHT 20
#define END_OF_SET -1

/*enums for error - if an input error detected the corresponding value will return to the caller*/
enum error{IllegalComma=-10,MissedPar,Garbage,InvaildSetMem,FloatNum,BadTerminate,ExtraComma,UndefinedSet,UndefinedCommand,MissedComma};
/*flags for the function read_one_set*/
enum flags{WithoutComma,WithComma};
/*enum for commands name*/
enum functions{Read,Print,Union,Intersect,Sub,Symdiff,Stop};

typedef struct {
    unsigned int cell1: 32;
    unsigned int cell2: 32;
    unsigned int cell3: 32;
    unsigned int cell4: 32;
}set;

/*'read_one_set': this function read from the input one set name and return the index of the set (0-5) or negative value that indicates on error */
int read_one_set();
/*'read_three_set: this function recive an array of pointers to sets. it reads from the input three set names, and implement the pointers to this sets in the array.
    the function returns zero if every thing is ok, or negative value that indicates on error*/
int read_three_set(set **);
/*'read_command': this function reads from the input command name and return the index od the command (0-6) or negative value that indicates on error*/
int read_command();
/*'initialize_set': this function recives an array of pointers to sets and initialize all the sets in the array to zero*/
void initialize_set(set **);
/*'print_set': this function recives a pointer to set and print all the members in this set*/
void print_set(set *);
/*'read_set': this function recives a pointer to set, and read from the input number, and adding them to the set. the function return 1 if everything is ok 
   or negative value that indicates on error*/
int read_set(set *);
/*'union_set': this function recives an array of pointers to sets and union all the member in the first two sets, and implement the result in the third set.*/
void union_set(set **);
/*'intersect_set': this function recives an array of pointers to sets and implement the intersect of the two first sets in the third set.*/
void intersect_set(set **);
/*'sub_set': this function recives an array of pointers to sets and subs the second set from the first set and implement the result in the third set*/
void sub_set(set **);
/*'symdiff_set': this function recives an array of pointers to sets and implement in the third set the simmetric differnce of the two first sets*/
void symdiff_set(set **);
/*'get_line': this function read from the input one line and implement it in a global array*/
int get_line();





