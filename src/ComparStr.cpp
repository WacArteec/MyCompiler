#include <ctype.h>

#include "ComparStr.h"

int StrCmp(char* str1, const char* str2)
{
    int i = 0, j = 0;

    while (isalpha(str1[i]) == 0 && str1[i] != '\0')     i++;

    while (isalpha(str2[j]) == 0 && str2[j] != '\0')     j++;

    while (str1[i] == str2[j] && str1[i] != '\0')
    {
        i++;
        j++;
    }

    return (str1[i] - str2[j]);
}
