#include <iostream>
#include <cstring>
#include <cmath>
#include <stdio.h>

using namespace std;

char letters[] = "0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZ";

class Multiread {
public:
    void parse_base(char *data, size_t len);

    int get_f_base() { return f_base; }

    int get_s_base() { return s_base; }

    void clean_data(char * ptrdata, size_t len);

private:
    int f_base = 0;
    int s_base = 0;
};

int get_index(char *array, size_t len, char element);

void convert(char *ptrdigit, int charsize, int f_base, int s_base);

int find_word_len(char *ptr_pointer);

int main() {
    Multiread read;

    int charsize = 255;
    char *input = new char[charsize];
    int f_base, s_base;

    cin.getline(input, 255);
    read.parse_base(input, 255);


    f_base = read.get_f_base();
    s_base = read.get_s_base();

    read.clean_data(input, 255);

    convert(input, charsize, f_base, s_base);

    cout << input << endl;

    delete[] input;
    return 0;
}

void Multiread::clean_data(char * ptrdata, size_t len){
    bool flag = false;
    for(int i =0; i< len; i++){
        if(*ptrdata == ' ' or *ptrdata == '\0')
            flag = true;
        if(flag){
            *ptrdata = '\0';
        }
        ptrdata++;
    }
}

void Multiread::parse_base(char *ptrdata, size_t len) {
    char *ptrstart_data = ptrdata;
    int flag = 0;
    int mult = 1;
    int *ptr_base = &this->f_base;
    for (int i = 0; i < len; i++, ptrdata++) {
        if (*ptrdata == '\0')
            break;
        if (*ptrdata == ' ') {
            mult = 1;
            flag++;
            continue;
        }
        if (flag > 0 and flag < 3) {
            if (mult == 1)
                mult = (int) pow(10.0, (double) (find_word_len(ptrdata) - 1));
            if (flag == 2) {
                ptr_base = &this->s_base;
            }
            *ptr_base += get_index(letters, 36, *ptrdata) * mult;
            mult /= 10;
        }
    }
}

int find_word_len(char *ptr_pointer) {
    int len = 0;
    for (;;) {
        if (*ptr_pointer == ' ' or *ptr_pointer == '\0')
            return len;
        len++;
        ptr_pointer++;
    }
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