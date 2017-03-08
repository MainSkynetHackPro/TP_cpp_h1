#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

char letters[] = "0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZ";

int get_index(char *array, size_t len, char element);

void convert(char *ptrdigit, int charsize, int f_base, int s_base);

int find_word_len(char *ptr_pointer);

int main() {
    char *input = NULL;
    int f_base, s_base;
    scanf("%1024s %d %d",input, &f_base, &s_base );

    convert(input, 1024, f_base, s_base);

    printf("%s", input);

    free(input);
    return 0;
}

int get_index(char *array, size_t len, char element) {
    for (int i = 0; i < len; i++) {
        if (*(array + i) == element) {
            return i;
        }
    }
    return -1;
}

void convert(char *ptrdigit, int charsize, int f_base, int s_base) {
    char *ptrbegin_digit = ptrdigit;
    int digit = 0, remain, counter = 0;

    ptrdigit += strlen(ptrdigit) - 1;
    while (ptrdigit >= ptrbegin_digit) {
        digit += get_index(letters, 36, *ptrdigit) * pow((double) f_base, (double) counter);
        counter++;
        ptrdigit--;
    }

    ptrdigit = ptrbegin_digit;

    for (int i = 0; i < charsize; i++)
        *(ptrdigit + i) = '\0';

    while (digit > 0) {
        remain = digit % s_base;
        digit -= remain;
        digit = digit / s_base;
        *ptrdigit = letters[remain];
        ptrdigit++;
    }

    //rotate array
    ptrdigit--;
    char tmp;
    char *ptrleft = ptrbegin_digit;
    while (ptrleft < ptrdigit) {
        tmp = *ptrleft;
        *ptrleft = *ptrdigit;
        *ptrdigit = tmp;
        ptrdigit--;
        ptrleft++;
    }
}