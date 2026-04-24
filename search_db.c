/* search_db.c
 * Searches for a given word in the hash table and displays the files in which it appears
 * along with frequency information.
 */

#include "header.h"

/*Function to Search in a database*/
int search_database(Main_t **hash_table){

    /*First check database is empty or not*/
    int j;
    for(j=0; j<=27; j++){
        if(hash_table[j]!=NULL)
            break;
    }
    if(j==28)
        return LIST_EMPTY;

    char searchWord[50];
    printf(CYAN"Enter the word you want to search: "RESET);
    //read data from user
    scanf("%s",searchWord);
    //find the index
    char ch = searchWord[0];
    int index = find_index(ch);

    //check the link part of that index
    if(hash_table[index]==NULL){
        return DATA_NOT_FOUND; //index is empty, data not found
    }

    Main_t *temp = hash_table[index];
    while(temp){ //traverse through the main node
        if(strcmp(temp->word, searchWord)==0){
            //if word found, then print the main_node details
            printf(GREEN"\nWord \"%s\" is present in %d file/s\n"RESET,searchWord, temp->file_count);

            printf("---------------------------------------\n");
            printf(MAGENTA"| FileCount | FileName   | WordCount  |\n"RESET);
            printf("---------------------------------------\n");

            Sub_t *temp2 = temp->s_link;
            int first = 1;
            while(temp2){ //now traverse the sub_node
                //and print sub_node details
                if(first){
                     printf(BLUE"| %-9d | %-10s | %-10d |\n"RESET,temp->file_count, temp2->f_name,temp2->word_count);
                    first = 0;
                }
                else{//for 2nd iteration print details excluding count
                    printf(BLUE"| %-9s | %-10s | %-10d |\n"RESET,"",temp2->f_name,temp2->word_count);
                }
                temp2 = temp2->s_link;
            }
            printf("---------------------------------------\n\n");
            return SUCCESS;
        }
        temp = temp->m_link;
    }
    return DATA_NOT_FOUND;
}