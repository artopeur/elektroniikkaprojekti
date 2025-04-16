#include <stdio.h>

typedef struct {
    char part1[20];
    char part2[20];
} SplitResult;
SplitResult split(char* s, int number);
char *combine(char*, char*,char*);
int strlenCustom(char*);

int main() {
    char one[] = "1234567890";
    char two[] = "12345678901111";
    char combinedd[20];
     combine(one, two,combinedd);

       printf("%s\n", combinedd);
     SplitResult result = split(combinedd, 10);

     printf("First part: %s\n", result.part1);
     printf("Second part: %s\n", result.part2);

    return 0;
}


char* combine(char* x, char* y, char* combined)
{
    int length_x = strlenCustom(x);
    int length_y = strlenCustom(y);

    int total = length_x+length_y ;

    if (total >= 20) {
        total=20;
    }

    int i = 0 ;


    while (i < length_x&&i<total) {
        combined[i] = x[i];
        i++;
    }
    int j = 0;

    while (j < length_y&&i<total) {
        combined[i] = y[j];
        i++;
        j++;
    }

    combined[i] = '\0';

    return combined;
}

int strlenCustom(char* z) {
    int length = 0;
    while (z[length] != '\0') {
        length++;
    }
    return length;
}

SplitResult split(char*s, int number)
{
    SplitResult result;


    int i = 0;
    int length = 0;


    while (s[length] != '\0') {
        length++;
    }

    if (number > length) {
        number = length;
    }


    while (i < number) {
        result.part1[i] = s[i];
        i++;
    }
    result.part1[i] = '\0';


    int j = 0;
    while (i < length) {
        result.part2[j] = s[i];
        i++;
        j++;
    }
    result.part2[j] = '\0';

    return result;



}