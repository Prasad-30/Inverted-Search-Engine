/* update_db.c
 * Updates the existing database using a backup file.
 * Restores hash table entries from saved data.
 */

#include"header.h"

/*Function to update data in a database from backup file*/
int update_database(Main_t **hash_table, FList_t *f_head, FList_t **new_head){
    while(1){
        //read a file name from user
        char fName[50];
        printf(MAGENTA"Enter the file name to update the database: "RESET);
        scanf(" %s",fName);
        //validate recieved file
        if(bkp_file_validation(fName) == FAILURE)
            return FAILURE;
        
        int check = check_backup(fName);
        if(check == FAILURE){     //check file is exists or not
            printf(RED"ERROR:   File %s does not exists!\n\n"RESET,fName);
            return FAILURE;
        }
        //if it's a backup file
        else if(check == BACKUP){
            FILE *fptr = fopen(fName,"r"); //open it in read mode
            //skip the magic string
            char skip[50];
            fgets(skip, sizeof(skip),fptr);
            int index, fcount, wcount;
            char word[100], fname[50];

            //read main nodes data from backup file
            while(fscanf(fptr, "#%d;%[^;];%d;", &index, word, &fcount)==3){
                Main_t *m_node = malloc(sizeof(Main_t));
                //store in main node
                strcpy(m_node->word , word);
                m_node->file_count = fcount;
                m_node->s_link = NULL;
                m_node->m_link = NULL;

                //handle the linking part
                if (hash_table[index] == NULL){  //first node
                    hash_table[index] = m_node;
                }
                else{ //for other nodes, traverse
                    Main_t *temp = hash_table[index];

                    while (temp->m_link != NULL)
                        temp = temp->m_link;

                    temp->m_link = m_node;
                }

                //read the sub nodes data from backup file
                Sub_t *prev = NULL;
                for(int i=1;i<=fcount;i++){
                    fscanf(fptr, "%[^;];%d;", fname, &wcount);

                    Sub_t *s_node = malloc(sizeof(Sub_t));
                    strcpy(s_node->f_name, fname);

                    insert_last(new_head, s_node->f_name); //list to store backup file names
                    //handle the data and linking part
                    s_node->word_count = wcount;
                    s_node->s_link = NULL;

                    if(prev==NULL) // for first node
                        m_node->s_link = s_node;
                    else
                        prev->s_link = s_node;

                    prev = s_node;
                }
                fscanf(fptr, "#\n");   // consume last #
            }
            fclose(fptr);
            return SUCCESS;
        }
        //if not backup file, then check if it is already exists in database
        else{
            printf(RED"ERROR:   File %s is not a backup file!\n         Please give backup file only.\n\n"RESET,fName);
            return FAILURE;
        }
    }
}