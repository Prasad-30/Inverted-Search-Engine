/* save_db.c
 * Saves the current hash table database into a backup file
 * using a predefined format to be used while reading.
 */

#include"header.h"

/*Function to save the database in a file*/
int save_database(Main_t **hash_table)
{   
    /*First check database is empty or not*/
    int j;
    for(j=0; j<=27; j++){
        if(hash_table[j]!=NULL)
            break;
    }
    if(j==28)
        return LIST_EMPTY;

    while (1)
    {   /*read a file_name from user to save database in it*/
        char bkp_fname[50];
        printf(MAGENTA"Enter the file name to save database: "RESET);
        getchar();
        scanf(" %s", bkp_fname);
        /*validate file name*/
        if (bkp_file_validation(bkp_fname) == FAILURE)
            continue;

        /*First open file in read mode to check empty or not*/
        FILE *fptr = fopen(bkp_fname, "r");
        if (fptr != NULL)
        {
            int ch = fgetc(fptr);
            fclose(fptr);

            if (ch != EOF) //if file is not empty
            {   menu:
                int choice;
                /*ask user for a choice*/
                printf(BLUE"INFO: File %s already exists.\n"
                       "Do you want to:\n"
                       "1. Overwrite the file content\n"
                       "2. Enter a new file name\n"
                       "3. Cancel\nEnter your choice: "RESET, bkp_fname);
                       
                if(scanf(" %d",&choice) != 1){
                    printf(RED"\nERROR:  Inavlid input! Please enter a number only.\n\n"RESET);
                    while(getchar()!='\n')
                        continue;

                    goto menu;
                }
                
                if (choice == 2) //to get new file name
                    continue;
                else if (choice == 3)//to cancel the save operation
                    return FAILURE;
                else if(choice<=0 || choice>3){
                    printf(RED"\nERROR:   Enter valid choice!\n\n"RESET);
                    goto menu;
                }
                
                /* if choice == 1 , overwrite the file contents*/
            }
        }

        /* Open file in write mode to write or overwrite contents in a file */
        fptr = fopen(bkp_fname, "w");
        if (fptr == NULL)
        {
            perror("fopen");
            return FAILURE;
        }

        /* Writing in a file using fprintf() */
        fprintf(fptr, "*BACKUP-FILE*\n");//magic string

        for (int i = 0; i < 28; i++)
        {   /*skip empty indices*/
            if (hash_table[i] == NULL)
                continue;

            Main_t *m_temp = hash_table[i];
            //traverse the main node
            while (m_temp)
            {   //write main node data
                fprintf(fptr, "#%d;%s;%d;",i,m_temp->word,m_temp->file_count);
                //now traverse the sub node
                Sub_t *s_temp = m_temp->s_link;
                while (s_temp)
                {   //then write in a file
                    fprintf(fptr, "%s;%d;",s_temp->f_name,s_temp->word_count);
                    s_temp = s_temp->s_link;
                }
                fprintf(fptr, "#\n");
                m_temp = m_temp->m_link;
            }
        }
        //close file pointer
        fclose(fptr);
        break;
    }

    return SUCCESS;
}
