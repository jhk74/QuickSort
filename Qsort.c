// Jason Kim jhk74

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/c/cs223/Hwk4/Deque.h"
#include <stddef.h>
//#include "Deque.h"
#include <limits.h>

char * removeEOL(char * str);
bool compareStringsByKey(char * str1, char * str2, int pos, unsigned len, int * result);
bool quickSort(Deque * d, int pos, int len, int n);

int main(int argc, char * argv[])
{
    int POS = 0;
    unsigned LEN = INT_MAX;
    char * endPtr = NULL;
    int index = 1;

    // Create deque to hold the lines from files
    Deque D = NULL;
    if (!createD(&D))
    {
        exit(1);
    }

    // parse arguments
    if (argc > 1)
    {
        if (argv[1][0] == '-')
        {
            (argv[1])++;
            POS = strtol(argv[1], &endPtr, 10);
            if (*endPtr == ',')
            {
                while (argv[1][0] != ',')
                {
                    (argv[1])++;
                }
                (argv[1])++;
                LEN = strtol(argv[1], &endPtr, 10);
            }
            index++;
        }

        // Read all files into deque
        while (index < argc)
        {
            FILE * f = fopen(argv[index], "r");
            if (!f)
            {
                printf("Error reading file %s\n", argv[index]);
                return 1;
            }
            else {
                char *line = NULL;
                size_t len = 0;
                while (getline(&line, &len, f) != -1) {
                    line = removeEOL(line);
                    if(!(addD(&D, line))) {
                        printf("incorrect use\n");
                        return 1;
                    }
                    line = NULL;
                    len = 0;
                }
                free(line);
            }
            index++;
            fclose(f);
            f = NULL;
        }
        // Sort deque
        int n = 0;
        quickSort(&D, POS, LEN, n);

        // Print sorted deque
        char * l;
        while (!isEmptyD(&D))
        {
            remD(&D, &l);
            printf("%s\n", l);
            free(l);
        }
        l = NULL;
        destroyD(&D);
    }
    exit(0);
}

// Removes end of line from string and replaces it with '\0'
char * removeEOL(char * str)
{
    int i = 0;
    bool found = false;
    while ((!found) && (i < strlen(str)))
    {
        if (str[i] == '\n')
        {
            found = true;
            str[i] = '\000';
        }
        i++;
    }
    return str;
}


// Sort the deque using quicksort algorithm
bool quickSort(Deque *d, int pos, int len, int n)
{
    bool isOK = true;
    int result = 0;
    //char * pivot[MAXSTRINGLENGTH];
    char * pivot;

    // Create 2 stacks for smaller and greater than pivot
    Deque smaller = NULL;
    Deque greater = NULL;
    char * element;
    if ((createD(&smaller)) && (createD(&greater)))
    {

        // Take first element as a pivot
        if (remD(d, &pivot))
        {

            // remove all elemengts from deque
            while ((isOK) && (!isEmptyD(d)))
            {
                // remove next element from deque
                isOK = remD(d, &element);

                // compare with pivot and push it to smaller or greater stack
                if (compareStringsByKey(element, pivot, pos, len, &result))
                {
                    if (result < 0)
                    {
                        isOK = pushD(&smaller, element);
                    }
                    else if (result == 0)
                    {
                        if ((n % 2) == 0)
                        {
                            isOK = pushD(&greater, element);
                        }
                        else
                        {
                            isOK = pushD(&smaller, element);
                        }
                    }
                    else
                    {
                        isOK = pushD(&greater, element);
                    }
                }
            }
            // Call quicksort recursively for smaller and greater stacks
            if ((quickSort(&smaller, pos, len, n + 1)) && (quickSort(&greater, pos, len, n + 1)))
            {
                // Add strings from smaller stack back to queue
                while ((isOK) && (!isEmptyD(&smaller)))
                {
                    isOK &= (popD(&smaller, &element) && addD(d, element));
                }
                // Add pivot back to queu
                isOK = addD(d, pivot);

                // Add strings from larger stack back to queue
                while ((isOK) && (!isEmptyD(&greater)))
                {
                    isOK &= (popD(&greater, &element) && addD(d, element));
                }
            }
            else
            {
                isOK = false;
            }
        }
    }
    else
    {
        isOK = false;
    }
    if ((!destroyD(&smaller)) || (!destroyD(&greater)))
    {
        isOK = false;
    }
    pivot = NULL;
    element = NULL;
    return isOK;
}

// Compare 2 strings using a key
bool compareStringsByKey(char * str1, char * str2, int pos, unsigned len, int * result)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Create keys from strings
    if (len1 > pos + len)
    {
        len1 = pos + len;
    }
    if (len2 > pos + len)
    {
        len2 = pos + len;
    }
    bool isOK = false;
    int length = len2;
    if (len1 < len2)
    {
        length = len1;
    }
    *result = 0;
    while ((*result == 0) && (pos < length))
    {
        if (str1[pos] < str2[pos])
        {
            *result = -1;
        }
        else if (str1[pos] == str2[pos])
        {
            *result = 0;
        }
        else
        {
            *result = 1;
        }
        pos++;
    }
    if ((*result == 0) && ((len1 > length) || (len2 > length)))
    {
        if (len1 < len2)
        {
            *result = -1;
        }
        else
        {
            *result = 1;
        }
    }
    isOK = true;
    return isOK;
}