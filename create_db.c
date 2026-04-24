/* create_db.c
 * Creates the inverted index database by reading input files,extracting words, and storing them into the hash table
 * along with file and word count information.
 */

#include "header.h"

/*Function to create database*/
int create_database(FList_t *f_head, Main_t **hash_table){
    FList_t *temp = f_head;
    //traverse into the file_names list
    while(temp){
        //open the files one by one
        FILE *fptr = fopen(temp->file_name, "r");

        char buffer[50];
        //store word in a string
        while (fscanf(fptr, "%s", buffer)!=EOF)
        {   char ch = buffer[0];
            //find the index
            int index = find_index(ch);
            
            //insert into hash table at calculated index 
            insert_at_main(hash_table, index, buffer, temp->file_name);
        }
        fclose(fptr);
        //traverse to the next file_name
        temp = temp->link; 
    }
    return SUCCESS;
}