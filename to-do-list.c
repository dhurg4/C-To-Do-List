#include <stdio.h>
#include <stdbool.h>

void add_task(char* list, int* size)
{
    (*size)++;

}

bool starting_screen(bool* exit_p_now, char* list, int* size) 
{
    bool exit_p = *exit_p_now;

    printf("1,2,3,4,5,6,7 don't do anything right now \n 8 - Exit the program. \n"); 

    int choice;
    printf("Please enter your choice of task here:");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            add_task(list, size);
            return exit_p;
        case 2:
            //delete_task();
            return exit_p;
        case 3:
            //edit_task_name();
            return exit_p;
        case 4:
            //mark_as_done();
            return exit_p;
        case 5:
            //view_all();
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
    char* tasks = (char*) malloc(size * sizeof(char));
    
    
    while (exit_program == false)
    {
        //Passing everything by reference so it gets updated for the whole code
        //instead of just the copy getting updated.
        exit_program = starting_screen(exitP, &tasks, &size);
    }

    free(tasks);
    printf("Program exited.\n");

}