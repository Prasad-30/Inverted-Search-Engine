/*  
  *Name : Prasad Kumbhar
  *Project Name : Inverted Search
  *Date : 15-02-2026

  * Description:
    * This project implements an Inverted Search Engine that indexes multiple textfiles and enables 
    * fast word-based searching. The program builds a hash table–based inverted index where each unique word 
    * is mapped to the files it appears in along with their frequency count.

    * The system supports operations such as creating the database, displaying the
    * indexed data, searching for specific words, saving the database to a backup
    * file, and restoring data from the backup file. Linked lists are used to manage
    * word nodes and file details efficiently.

  * Concepts Used:
    * hash Table
    * linked list
    * file handling
*/

#include "header.h"
/*Collect CLA's*/
int main(int argc, char *argv[]){
    /*declare the pointers*/
    FList_t *f_head = NULL;
    FList_t *new_head = NULL;
    /*array of pointers to store main-node addresses*/
    Main_t *hash_table[28]={NULL};

    //validate the CLA arguments
    if(argc==1 || validate_args(argc, argv, &f_head) == FAILURE){
        printf(MAGENTA"INFO:    Input Files are not provided or valid!\n         You can only perform \"Update Database\" operation.\n\n"RESET);
    }
    else{
        //print the message
        printf(MAGENTA "\nINFO:    Successful: inserting file names: " RESET);
        print_list(f_head);
        printf(MAGENTA "into the file linked list:)\n\n" RESET);
    }
    //run a loop till user press exit
    while(1){
        int choice;
        //display menu and read choice from user
        printf(CYAN"Select your choice among following options:\n1. Create Database\n2. Display Database\n3. Update Database\n4. Search in Database\n5. Save Database\n6. Exit from program\n"RESET);
        printf(CYAN"Enter your choice: "RESET);
        if(scanf(" %d",&choice) != 1){
            printf(RED"\nERROR:   Inavlid input! Please enter a number only.\n\n"RESET);
            while(getchar()!='\n');
            continue;
        }

        /*Call the function according to the users choice*/
        switch (choice)
        {
        //to create the database
        case 1:
            if(argc==1){  //if files are not provided or all are invalid
                printf(RED"ERROR:    You can't perform \"Create database\" operation since input files are not provided or are invalid.\n\n"RESET);
                break;
            }
            //to perform operation only once
            static int create_count=0;
            if(create_count==0){
                if(new_head!=NULL){  //after updating database
                    remove_common(&f_head, new_head);
                }
                //function call to create the database
                if(create_database(f_head, hash_table)==SUCCESS){
                    printf(MAGENTA "\nINFO:    Successful: Creation of DATABASE for files: " RESET);
                    create_count=1;
                    print_list(f_head);printf("\n\n");
                }
                else
                    printf(RED"Error:   Failed to create DATABASE!\n"RESET);
            }
            else
                printf(RED"\nINFO:   Database is already created!\n\n"RESET);
            break;
        case 2:
            //function call to display the database
            if(display_database(hash_table)==LIST_EMPTY)
                printf(RED"\nERROR:   Database is empty!\n\n"RESET);
            break;
        case 3:
            //function call to update the database
            static int update_count=0;  //to ensure perform update only once
            if(create_count==1){
                printf(RED"\nERROR:   Cannot update database after creating!\n\n"RESET);
                break;
            }
            if(update_count==1){
                printf(RED"\nERROR:   Cannot update database again after updating!\n\n"RESET);
                break;
            }
            if(update_database(hash_table, f_head, &new_head)==SUCCESS){
                printf(GREEN"INFO:   Database updated successfully!\n"RESET);
                update_count=1;
            }
            else{
                printf(RED"ERROR:   Update failed!\n\n"RESET);
            }
            break;
        case 4:
            //function call to search data in database
            int check = search_database(hash_table);
            if(check == DATA_NOT_FOUND){
                printf(RED"\nINFO:    Word not found in database\n\n"RESET);
            }
            else if(check == LIST_EMPTY){
                 printf(RED"\nERROR:   Database is empty!\n         Cannot perform search operation\n\n"RESET);
            }
            break;
        case 5:
            //function call to save database in a file
            int ret = save_database(hash_table);
            if(ret  == SUCCESS)
                printf(GREEN"INFO:  Database saved successfully in File!\n"RESET);
            else if(ret == LIST_EMPTY)
                printf(RED"\nERROR:  Database is empty!\n        First create or update the database\n\n"RESET);
            break; 
        case 6:
            printf(MAGENTA"INFO:    Exiting...\n"RESET);
            return 0; //to exit
        default:
            printf(RED"ERROR:   Invalid choice! Try Again\n"RESET);
            break;
        }
        //ask user whether they want to continue or not
        again:
        char option;
        printf("Do you want to continue?\nEnter y/Y to continue and n/N to discontinue: ");
        scanf(" %c",&option);
        while(getchar()!='\n');
        if((option=='n' || option=='N')){
            printf(MAGENTA"INFO:    Exiting...\n"RESET);
            return 0;
        }
        else if ((option=='y' || option=='Y'))
        {
            continue;
        }
        else{
            printf(RED"ERROR:   Invalid choice! Try again\n"RESET);
            goto again;
        }
        
    }
}