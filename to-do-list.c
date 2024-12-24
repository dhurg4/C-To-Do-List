#include <stdio.h> //input output - printf() scanf()
#include <stdbool.h> //bool data type
#include <stdlib.h> //malloc() calloc() realloc() and free()
#include <string.h> //strlen and strcopy

void view_tasks(char*** list, int* size)
{
    int list_length = *size;

    printf("\n");
    for (int i=0; i<list_length; i++)
    {
        printf("Task %d: %s\n", i+1, (*list)[i]);
    }
    printf("\n");
}

int add_task(char*** list, int* size) //* is an array of strings, ** is a pointer to the array, *** is a pointer to the pointer
                                    // Allowing us to change the list through dynamic memory allocation.
{
    (*size)++;

    (*list) = realloc((*list), (*size)*sizeof(char*));

    if (*list == NULL)
    {
        printf("Reallocation failed.\n");  
        return 1;  
    }

    printf("Enter your task here:\n");

    char temp_task[100]; 
    scanf("%s", temp_task);


    (*list)[(*size) - 1] = (char*)malloc((strlen(temp_task)+1) * sizeof(char));

    strcpy(((*list)[(*size)-1]), temp_task);

    view_tasks(list, size);

    return 0;

}

int delete_task(char*** list, int* size)
{
    view_tasks(list, size);

    printf("Please enter the number of the task you wish to delete.\n");
    int index;
    scanf("%d", &index);

    if ((*size)<=0)
    {
        if(index < 0 || index > (*size))
        {
            printf("\nInvalid task number.\n");
            return 1;
        }
        printf("\nNo tasks in the list.\n");
        return 2;
    }
    

    printf("\nTask deleted: Task%d: %s\n", index, (*list)[index-1]);

    char** temp_list = (char**)malloc(((*size)-1)*(sizeof(char*)));

    //Move all the elements in the array up one so the task the user wants to delete is gone,
    //And all the other elements move up the list, filling up the gap.
    for(int i=(index-1); i<((*size)-1); i++)
    {
        (*list)[i] = (*list)[i+1];
    }

    (*list)[(*size)] = 0 ;
    ((*size)--);

    view_tasks(list, size);

    return 0;

}

bool starting_screen(bool* exit_p_now, char*** list, int* size) 
{
    bool exit_p = *exit_p_now;

    printf("3,5,6,7 don't do anything right now\n 1 - Add a task.\n 2 - Delete a task. \n 5 - View all tasks. \n 8 - Exit the program. \n"); 

    int choice;
    printf("Please enter your choice of task here:\n");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            add_task(list, size);
            return exit_p;
        case 2:
            delete_task(list, size);
            return exit_p;
        case 3:
            //edit_task_name();
            return exit_p;
        case 4:
            //mark_as_done();
            return exit_p;
        case 5:
            view_tasks(list, size);
            return exit_p;
        case 6: 
            //view_pending();
            return exit_p;
        case 7:
            //view_done();
            return exit_p;
        case 8:
            printf("Exiting program...\n");
            exit_p = true;
            return exit_p;
    }
    return exit_p;

}

int main()
{
    bool exit_program = false;
    bool* exitP = &exit_program;

    int size = 0;
    char** tasks = NULL;
    
    
    while (exit_program == false)
    {
        //Passing everything by reference so it gets updated for the whole code
        //instead of just the copy getting updated.
        exit_program = starting_screen(exitP, &tasks, &size);
    }

    for(int i=0; i<(size); i++)
    {
        free((tasks)[i]);
    }

    free(tasks);
    printf("Program exited.\n");

}