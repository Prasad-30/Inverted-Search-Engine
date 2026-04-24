/* display_db.c
 * Displays the complete contents of the inverted search database
 * including index, words, file names, and their occurrence counts.
 */

#include "header.h"

/*Function to Display the database*/
int display_database(Main_t **hash_table){

    /*First check database is empty or not*/
    int j;
    for(j=0; j<=27; j++){
        if(hash_table[j]!=NULL)
            break;
    }
    if(j==28)
        return LIST_EMPTY;

    printf("\n");
    printf("------------------------------------------------------------\n");
    printf(MAGENTA"| Index | Word       | FileCount | FileName   | WordCount  |\n"RESET);
    printf("------------------------------------------------------------\n");
    /*loop through the all indices of hash_table*/
    for(int i=0; i<=27 ;i++){
        if(hash_table[i]==NULL){
            continue; //skip the index if it's link part is null
        }

        //if not NULL means
        Main_t *temp = hash_table[i];
        //traverse through the main_node
        while(temp){
        
            Sub_t *temp2 = temp->s_link;
            int first = 1;//to check first iteration to print in table
            
            //traverse through the sub_nodes
            while(temp2){
                if(first){ //for first iteration, print main and sub_node details
                    printf(BLUE"| %-5d | %-10s | %-9d | %-10s | %-10d |\n"RESET,i, temp->word, temp->file_count,temp2->f_name, temp2->word_count);
                    first = 0;
                }
                else{ //from 2nd iter, print sub_node details if present
                    printf(BLUE"| %-5s | %-10s | %-9s | %-10s | %-10d |\n"RESET,"", "", "", temp2->f_name, temp2->word_count);
                }
                temp2 = temp2->s_link;
            }
            printf("------------------------------------------------------------\n");
            temp = temp->m_link;
        }
    }
    return SUCCESS;
}
