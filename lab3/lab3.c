#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printIDs()
{
    printf("Real ID = %d\n", getuid());
    printf("Effective ID = %d\n", geteuid());
}

void AttemptOpenFile()
{
    FILE *file = fopen("test.txt", "r");

    if (file == NULL)
    {
        perror("Failed to open test file!");
    }
    else
    {
        printf("Test file opened successfully!\n");
        fclose(file);
    }
}

int main(int argc, char **argv)
{
    printIDs();
    AttemptOpenFile();
    printf("\n");

    if (seteuid(getuid()) == -1)
    {
        perror("Failed to set ID!");
        return 1;
    }

    printIDs();
    AttemptOpenFile();

    return 0;
}
