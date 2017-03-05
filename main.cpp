#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int get_index(char *array, size_t len, char element) {
    for (int i = 0; i < len; i++) {
        if (*(array + i) == element) {
            return i;
        }
    }
    return -1;
}

void convert(char *ptrdigit, int charsize, int f_base, int s_base) {
    char letters[] = "0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZ";
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

int main() {
    int charsize = 255;
    char *input = new char[charsize];
    int f_base, s_base;
    cin >> input;
    cin >> f_base;
    cin >> s_base;

    convert(input, charsize, f_base, s_base);

    cout << input << endl;

    delete[] input;
    return 0;
}