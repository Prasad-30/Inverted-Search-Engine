/* header.h
 * Contains all structure definitions, macrosand function prototypes used across the project.
 * Acts as a common interface between all source files.
 */

#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

/*Macros for return the status of operation*/
#define SUCCESS 0
#define FAILURE -1
#define BACKUP 1
#define LIST_EMPTY -2
#define DATA_NOT_FOUND -3
#define TABLE_SIZE 28

// Text colors to use
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

// Reset
#define RESET   "\033[0m"

/*structure for node to store file names in SLL*/
typedef struct node
{
    char file_name[50];
    struct node *link;
}FList_t;

/*structure to store the subnodes*/
typedef struct s_node
{
    char f_name[50];
    int word_count;
    struct s_node *s_link;
}Sub_t;

/*structure to store the main nodes*/
typedef struct m_node
{
    char word[50];
    int file_count;
    struct m_node *m_link;
    struct s_node *s_link;
}Main_t;



/*Function Prototype to validate arguments*/
int validate_args(int, char**,FList_t **);

/*Function Prototype to validate backup file*/
int bkp_file_validation(char*);

/*Function Prototype to inser last in file LL*/
int insert_last(FList_t **, char argv[]);

/*Function Prototype to print filename LL*/
int print_list(FList_t *);

/*Function prototype to create database*/
int create_database(FList_t *, Main_t **);

/*Function prototype to Display database*/
int display_database(Main_t **);

/*Function prototype to Search in a database*/
int search_database(Main_t **);

/*Function prototype to update data in a database*/
int update_database(Main_t **,FList_t *, FList_t **);

/*Function prototype to remove dup from file list*/
void remove_common(FList_t **, FList_t *);

/*to check file name is present or not*/
int is_present(FList_t *head2, char *name);

/*Function prototype to save the database in a file*/
int save_database(Main_t **);

/*Function prototype to insert in main node*/
int insert_at_main(Main_t **, int , char *, char *);

/*Function prototype to insert in sub node*/
int insert_at_sub(Main_t *, char *);

/*Function prototype to find the index*/
int find_index(char );

/*To check backup file while updating*/
int check_backup(char *);
#endif