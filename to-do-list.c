#include <stdio.h> //input output - printf() scanf()
#include <stdbool.h> //bool data type
#include <stdlib.h> //malloc() calloc() realloc() and free()
#include <string.h> //strlen and strcopy

void view_tasks(char*** list, int* size)
{
    int list_length = *size; //The size is the list_length

    printf("\n");
    for (int i=0; i<list_length; i++)
    {
        printf("Task %d: %s\n", i+1, (*list)[i]); //iterates through the list and prints all the tasks
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

    char temp_task[100]; //Gives the user 100 characters to enter thei task name
    scanf("%s", temp_task); //Saves the input to temp_task


    (*list)[(*size) - 1] = (char*)malloc((strlen(temp_task)+1) * sizeof(char)); //In the last index of the array, allocate enough char memory for the task

    strcpy(((*list)[(*size)-1]), temp_task); //Copy the task into the array

    view_tasks(list, size); 

    return 0; //Everything is okay

}

int delete_task(char*** list, int* size)
{
    view_tasks(list, size);

    printf("Please enter the number of the task you wish to delete.\n");
    int index;
    scanf("%d", &index);

    if ((*size)<=0) //If there is more than 0 tasks
    {
        if(index <= 0 || index > (*size)) //And the task number is 0 or greater than the list size+1 (index shown to user is +1)
        {
            printf("\nInvalid task number.\n");
            return 1; //Returns to main() if there is an error
        }
        printf("\nNo tasks in the list.\n");
        return 2; //Returns to main() if there is an error
    }
    

    printf("\nTask deleted: Task%d: %s\n", index, (*list)[index-1]); //Tell the user the task being deleted

    //Move all the elements in the array up one so the task the user wants to delete is gone,
    //And all the other elements move up the list, filling up the gap.
    for(int i=(index-1); i<((*size)-1); i++)
    {
        (*list)[i] = (*list)[i+1];
    }

    (*list)[(*size)] = 0 ; //Assign the last index in the list 0
    ((*size)--); //Reduce the size of the list by 1

    view_tasks(list, size);

    return 0; //Everything is okay

}

bool starting_screen(bool* exit_p_now, char*** list, int* size) 
{
    bool exit_p = *exit_p_now;

    printf("\n 1 - Add a task.\n 2 - Delete a task. \n 3 - View all tasks. \n 4 - Exit the program. \n"); 

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
            view_tasks(list, size);
            return exit_p;
        case 4:
            printf("Exiting program...\n");
            exit_p = true;
            return exit_p;
        default:
            printf("Invalid input");
            return exit_p;
    }
    return exit_p;
}

int main()
{
    bool exit_program = false;
    bool* exitP = &exit_program; //Pointer for exit program

    int size = 0; //Beginning size of array
    char** tasks = NULL; //Array is a list of pointers pointing to a memory location of array elements
    
    
    while (exit_program == false)
    {
        //Passing everything by reference so it gets updated for the whole code
        //instead of just the copy getting updated.
        exit_program = starting_screen(exitP, &tasks, &size);
    }

    for(int i=0; i<(size); i++)
    {
        free((tasks)[i]); //Free each element space in the array
    }

    free(tasks); //Free the array itself
    printf("Program exited.\n");

}