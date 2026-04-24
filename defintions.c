/* definitions.c
 * Contains common functions and shared logicused by multiple modules such as validations,
 * list operations, and helper functions.
 */

#include "header.h"

/*Function to validate the CLA*/
int validate_args(int argc, char **argv, FList_t **f_head)
{   
    //run a loop to validate every files
    for (int i = 1; i < argc; i++)
    {   
        char *extn = strstr(argv[i], ".txt");
        if(strlen(argv[i])<=4){
            printf(RED"ERROR:   File \"%s\" is not a valid file name.\n         So we are not reading it.\n" RESET, argv[i]);
            continue;
        }
        // check valid .txt extension
        if (extn != NULL && strcmp(extn, ".txt") == 0)
        {
            FILE *fptr = fopen(argv[i], "r");
            //check file exists or not
            if (fptr == NULL)
            {
                //perror("fopen");
                printf(RED"ERROR:   File \"%s\" does not exists.\n         So we are not reading it.\n" RESET, argv[i]);
                continue;
            }

            // check empty file
            int ch = fgetc(fptr);
            if (ch != EOF)
            {
                //insert file name in a list
                if(insert_last(f_head, argv[i])==SUCCESS)
                    printf(YELLOW"INFO:    File \"%s\" is inserted successfully!\n"RESET,argv[i]);
                else
                    printf(RED"ERROR:   File \"%s\" is repeated.\n         So we are not reading it.\n" RESET, argv[i]);
                rewind(fptr);
            }
            else{
                printf(RED"ERROR:   File \"%s\" is empty.\n         So we are not reading it.\n" RESET, argv[i]);
            }
            fclose(fptr);
        }
        else{
            printf(RED"ERROR:   File \"%s\" is not .txt file.\n         So we are not reading it.\n" RESET, argv[i]);
        }
    }
    //if all the files provided are invalid
    if(*f_head == NULL)
        return FAILURE;

    return SUCCESS;
}


/*function for inserting element at last in SLL*/
int insert_last(FList_t **f_head, char argv[]){
    //First check for duplicate
    FList_t *temp = *f_head;
    while(temp){
        if(strcmp(temp->file_name,argv)==0){
            return FAILURE;
        }
        temp = temp->link;
    }

    //create a newnode if duplicate not found
    FList_t *newnode = malloc(sizeof(FList_t));
    //check memory allocation
    if(!newnode){
        return FAILURE;
    }
    //handle data and linking part
    strcpy(newnode->file_name,argv);
    newnode->link = NULL;
    //if list is empty
    if(*f_head == NULL){
        //point head to new node
        *f_head = newnode;
        return SUCCESS;
    }
    //if list is not empty
    temp = *f_head;
    while(temp->link != NULL){
        temp = temp->link;
    }
    temp->link = newnode;
    return SUCCESS;
}

/*Function to print the list*/
int print_list(FList_t *head)
{
	if (head == NULL)
	{
		printf(YELLOW"None\n"RESET);
        return LIST_EMPTY;
	}
    else
    {   //traverse upto the NULL, and print the data
	    while (head)		
	    {
		    printf(GREEN"%s " RESET, head ->file_name);
		    head = head -> link;
	    }

    }
    return SUCCESS;
}

/*Function to insert in main node*/
int insert_at_main(Main_t **hash_table, int index, char *word, char *fname){
    Main_t *temp = hash_table[index];

    //if hash table link part is NULL
    if (temp == NULL)
    {   //create main and it's 1 sub node
        Main_t *new_m = malloc(sizeof(Main_t));
        Sub_t *new_s = malloc(sizeof(Sub_t));

        //insert word into the main_node
        strcpy(new_m->word, word);
        new_m->file_count = 1; 
        new_m->s_link = new_s; //handle the linking part
        new_m->m_link = NULL;

        //in sub_node, insert the file name
        strcpy(new_s->f_name, fname);
        new_s->word_count = 1;
        new_s->s_link = NULL;

        //update the link part of hash_table with new_node
        hash_table[index] = new_m;
        return SUCCESS;
    }

    //if not null, traverse main_node list
    while (temp)
    {
        if (strcmp(temp->word, word) == 0)
        {
            //if word already exists then perform sub_node operation
            insert_at_sub(temp, fname);
            return SUCCESS;
        }
        //if word is not present then to stop at last node
        if (temp->m_link == NULL)
            break;
        temp = temp->m_link;
    }

    // if word not found ,then create new main node and insert last
    Main_t *new_m = malloc(sizeof(Main_t));
    Sub_t *new_s = malloc(sizeof(Sub_t));

    strcpy(new_m->word, word);
    new_m->file_count = 1;
    new_m->s_link = new_s;
    new_m->m_link = NULL;

    strcpy(new_s->f_name, fname);
    new_s->word_count = 1;
    new_s->s_link = NULL;

    //update the last main_node m_link part
    temp->m_link = new_m;

    return SUCCESS;

}

/*Function to insert in sub node*/
int insert_at_sub(Main_t *head, char *fname){
    Sub_t *temp = head->s_link;
    //traverse through the subnode list
    while (temp)
    {   
        if (strcmp(temp->f_name, fname) == 0)
        {   //if file name already exists
            temp->word_count++; //increment word count in that subnode
            return SUCCESS;
        }
        //to stop at last subnode if filename is not present
        if (temp->s_link == NULL)
            break;
        temp = temp->s_link;
    }

    //if filename is not present, then create new sub node
    //and insert last in sub_node
    Sub_t *new_s = malloc(sizeof(Sub_t));
    strcpy(new_s->f_name, fname);
    new_s->word_count = 1;
    new_s->s_link = NULL;

    //update the last sub_node link part
    temp->s_link = new_s;
    //increment the file count in mainnode
    head->file_count++;

    return SUCCESS;
}

/*Function to find the index*/
int find_index(char ch){
    //find the index using first letter of a word
    if(islower(ch) || isupper(ch)){
        //if it's a alphabet, indices are between 0 to 25
        ch = toupper(ch);
        return ch - 'A';
    }
    //if ch is digit, then index is fixed i.e 26
    else if(ch>='0' && ch<='9'){
        return 26;
    }
    //if ch is any special character, then index is fixed i.e 27
    return 27;
}


/*Function to validate backup file*/
int bkp_file_validation(char* bkp_fname){
    char *extn = strstr(bkp_fname, ".txt");
    if(strlen(bkp_fname)<=4){
        printf(RED"ERROR:   File \"%s\" is not a valid file name.\n         Enter a valid file name.\n" RESET, bkp_fname);
        return FAILURE;
    }
    // check valid .txt extension
    if ( !(extn != NULL && strcmp(extn, ".txt") == 0)){
        printf(RED"ERROR:   File \"%s\" is not a .txt file\n         Enter a file with \".txt\" extension.\n" RESET, bkp_fname);
        return FAILURE;
    }

    return SUCCESS;
}

/*Function to check file is backup or normal file*/
int check_backup(char *fname){
    FILE *fptr = fopen(fname, "r");
    if (fptr == NULL)
    {
        //perror("fopen");
        return FAILURE; //file does not exists
    }
    char magic[40];
    fscanf(fptr,"%[^\n]",magic);
    fclose(fptr);
    if(strcmp(magic, "*BACKUP-FILE*")==0){
        return BACKUP;   //it's a backup file
    }
    return SUCCESS;  //normal file
}

//Check if filename exists in List2
int is_present(FList_t *head2, char *name)
{
    while (head2){
        if (strcmp(head2->file_name, name) == 0){
            printf(RED"INFO:    \"%s\" file is already present in database!\n          so we are not reading it\n"RESET,name);
            return 1;
        }
        head2 = head2->link;
    }
    printf(GREEN"INFO:    \"%s\" file is not present in database!\n          so we are reading it\n"RESET,name);
    return 0;
}

//Remove file_names from list1 if they are present in list2
void remove_common(FList_t **head1, FList_t *head2)
{
    FList_t *curr = *head1;
    FList_t *prev = NULL;

    while (curr)
    {
        if (is_present(head2, curr->file_name)){
            // delete curr
            if (prev == NULL){   // first node
                *head1 = curr->link;
                free(curr);
                curr = *head1;
            }
            else{  //for other nodes
                prev->link = curr->link;
                free(curr);
                curr = prev->link;
            }
        }
        else{
            prev = curr;
            curr = curr->link;
        }
    }
}