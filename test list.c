#include <stdio.h>
#include <stdlib.h>

int main()
{
    int input;

    printf("Enter size of array: \n");
    scanf("%d", &input);

    int* list = (int*)malloc((input) * sizeof(int));

    if (list == NULL)
    {
        printf("Memory allocation failed");
        return 1;
    }

    for(int i = 0; i <=(input) ; i++)
    {
        list[i] = i;
        printf("%d\n", list[i]);
    }
free(list);
}