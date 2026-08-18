#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE  1

char *read_file(char *fname)
{
    FILE *fp = fopen(fname, "rb");
    if (fp == NULL) 
    {
        printf("File doesn't exists.\n");
        fclose(fp);
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (len < 0) 
    {
        printf("There is nothing in file.\n");
        fclose(fp);
        exit(1);
    }

    char *buffer = malloc(len + 1);
    if (buffer == NULL)
    {
        printf("Cannot allocate memory.\n");
        fclose(fp);
        exit(1);
    }

    size_t last_index = fread(buffer, 1, len, fp);
    buffer[last_index] = '\0';

    fclose(fp);
    return buffer;
}

void naive_matching(char *text, char *pattern)
{
    for (int i = 0; i < (strlen(text) - strlen(pattern) + 1); i++) 
    {
        int mismatch = FALSE;
        for (int j = 0; j < strlen(pattern); j++)
        {
            if (pattern[j] != text[i + j])
            {   
                mismatch = TRUE;
                break;
            }
        }
        if (!mismatch)
        {
            printf("Found at %i\n", i);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc > 3 || argc < 3)
    {
        printf("Insufficient arguments.\n");
        return 1;
    }

    char *text = read_file(argv[1]);
    naive_matching(text, argv[2]);

    free(text);

    return 0;
}