/*
Mert MUSLU 150120027
Gülsüm Ece GÜNAY 150121539
Erkut DÖNMEZ 150120051
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 1010001
#define MAX_PAT 1000


void bruteForce(char *input, char *output, char *pattern, int* ptr);
int controlAgain(char *input, char *output, char *pattern, int i, int* pointer);
int controlAgainForHorspool(char *input, char *output, char *pattern, int i, int* pointer);
int controlAgainForBoyerMoore(char *input, char *output, char *pattern, int i, int* pointer);
void badSymbolTable(char *pattern);
int shiftingToBad(char *pattern,char inputLastLetter);
int max(int num1, int num2);
int find_shift_value(char *pattern, int given_k);
void goodSuffixTable(char *pattern);
void BoyerMoore(char *pattern, char *output, char *input,int length,int* ptrBoyer);
void HorsPool(char *pattern, char *output, char *input,int length, int* ptrHors);

int main() {

    // we tried the get input line by line but we failed. Our attempt is below.:
    /*
    char input[MAX_LEN][MAX_LEN];
    char str[100];

    FILE input_file;
    printf("Enter the name of the file:\n");
    gets(str);
    input_file = fopen(str, "r");
    if (input_file == NULL) {
        printf("Dosya açýlamadý.\n");
        return 1;
    }

    int row = 0;
    int col = 0;

    while (row < MAX_LEN && fgets(input[row], MAX_LEN, input_file) != NULL) {

        int len = strlen(input[row]);
        if (len > 0 && input[row][len - 1] == '\n') {
            input[row][len - 1] = '\0';
        }

        row++;
    }

    fclose(input_file);
    char output[MAX_LEN];
    char pattern[MAX_PAT];
    printf("Enter pattern to search: ");
    scanf("%s", pattern);
    badSymbolTable(pattern);
    goodSuffixTable(pattern);


    FILEoutput_file;
    char output_file_name[] = "output.html";
    int ComparisonsForBruteForce = 0;
    int ComparisonsForHorsPool = 0;
    int ComparisonsForBoyerMoore = 0;
    for(int i = 0; i<=row;i++) {
        bruteForce(data[i],output,pattern,&ComparisonsForBruteForce);
    }
    for(int i = 0; i<=row;i++) {
        int length = strlen(output);
        HorsPool(pattern,output,data[i],length,&ComparisonsForHorsPool);
    }
    for(int i = 0; i<=row;i++) {
        int length2 = strlen(output);
        BoyerMoore(pattern,output,data[i],length2,&ComparisonsForBoyerMoore);
    }




    printf(" -> Comparison Number of Brute Force Algortihm = %d \n -> Comparison Number of HorsPool Algortihm    = %d \n -> Comparison Number of Boyer-Moore Algortihm = %d",ComparisonsForBruteForce,ComparisonsForHorsPool,ComparisonsForBoyerMoore);


    output_file = fopen(output_file_name, "w");
    fputs(output, output_file);

    fclose(output_file);



    return 0;
    */


    char input_file_name[] = "";
    char output_file_name[] = "output.html";
    char input[MAX_LEN];
    char output[MAX_LEN];
    char pattern[MAX_PAT];

    FILE *input_file, *output_file;
    int ComparisonsForBruteForce = 0;
    int ComparisonsForHorsPool = 0;
    int ComparisonsForBoyerMoore = 0;
    printf("Enter the name of the file: ");
    scanf("%s",input_file_name);
    input_file = fopen(input_file_name, "r");




    fgets(input, MAX_LEN, input_file);
    fclose(input_file);



    printf("Enter pattern to search: ");
    scanf("%s", pattern);


    badSymbolTable(pattern);
    goodSuffixTable(pattern);

    bruteForce(input,output,pattern,&ComparisonsForBruteForce);
    int length = strlen(output);
    HorsPool(pattern,output,input,length,&ComparisonsForHorsPool);
    int length2 = strlen(output);
    BoyerMoore(pattern,output,input,length2,&ComparisonsForBoyerMoore);

    printf(" -> Comparison Number of Brute Force Algortihm = %d \n -> Comparison Number of HorsPool Algortihm    = %d \n -> Comparison Number of Boyer-Moore Algortihm = %d",ComparisonsForBruteForce,ComparisonsForHorsPool,ComparisonsForBoyerMoore);


    output_file = fopen(output_file_name, "w");
    fputs(output, output_file);

    fclose(output_file);



    return 0;
}
void bruteForce(char *input, char *output, char *pattern, int *ptr) {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    int len, pat_len, i, j, match;

    pat_len = strlen(pattern);
    len = strlen(input);

    j = 0;
    output[0] = '\0';

    for (i = 0; i < len; i++) {
        match = 1;
        if(i+pat_len-1 >= len) {
            strncat(output,&input[i],len-i);
            match = 2;
            i = len+1;
        }
        for (j = 0; j <= pat_len-1 && (i+pat_len-1 < len); j++) {
            if (input[i+j] != pattern[j]) {
                (*ptr)++;
                match = 0;
                break;
            }
            else {
                (*ptr)++;
                match = 1;
            }
        }

        if (match == 1) {
            strcat(output, "<mark>");
            i+= controlAgain(input, output, pattern, i+1, ptr)+1;
            strcat(output,pattern);
            strcat(output, "</mark>");
            strncat(output,&input[i],1);


        }
        else if(match == 0) {
            strncat(output, &input[i], 1);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double execution_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf(" -> Execution Time For Brute Force Algorithm   = %.6f milliseconds\n", execution_time*1000);
}
int controlAgain(char *input, char *output, char *pattern, int i, int *pointer) {
    int len, pat_len, j, match;
    pat_len = strlen(pattern);
    len = strlen(input);
    int za = 0;
    j = 0;
    int count = 0;
    int mamba = 0;
    int result = 0;
    int howmanytimes = 0;
    for (; i < len && count < pat_len-1 && mamba == 0; i++) {
        howmanytimes++;
        match = 1;

        for (j = 0; j <= pat_len-1; j++) {
            if (input[i+j] != pattern[j]) {
                (*pointer)++;
                match = 0;
                count++;
                result++;
                break;
            }
            else {
                match = 1;
                (*pointer)++;
            }
        }
        if (match == 1) {
            strncat(output, &input[i-count-1],count+1);
            count = 0;
            mamba = 1;
            result += controlAgain(input, output, pattern, i+1, pointer)+1;
        }
    }
    if(howmanytimes == 0 ) {
        return result+pat_len;
    }
    else {
        return result;
    }

}
int controlAgainForHorspool(char *input, char *output, char *pattern, int i, int *pointer) {

    int len, pat_len, j, match;
    pat_len = strlen(pattern);
    len = strlen(input);
    int za = 0;
    j = 0;
    int count = 0;
    int mamba = 0;
    int k = 0;
    int result = 0;
    int howmanytimes = 0;
    for (i ; i+pat_len-1 < len && count < pat_len && mamba == 0; count++) {
        howmanytimes++;
        match = 1;
        k = 0;
        for (j = pat_len-1; j >= 0 && (i+j < len); j--) {
            if (input[i+j] != pattern[j]) {
                (*pointer)++;
                    result+= shiftingToBad(pattern,input[i+pat_len-1]);
                    count+= shiftingToBad(pattern,input[i+pat_len-1]);
                    i+= shiftingToBad(pattern,input[i+pat_len-1]);

                match = 0;
                break;
            }
            else {

                match = 1;
                (*pointer)++;
                k++;
            }
        }
        if (match == 0 && shiftingToBad(pattern,input[i+pat_len-1]) == pat_len) {

        }
        else if (match == 1 && i+pat_len-1 < len) {
            strncat(output, &input[i-count],count);
            count = 0;
            mamba = 1;
            result += controlAgainForHorspool(input, output, pattern, i+1, pointer)+1;
            break;
        }
    }
    if(howmanytimes == 0) {
        return result + pat_len;
    }
    else {
        return result;
    }
}
int controlAgainForBoyerMoore(char *input, char *output, char *pattern, int i, int *pointers) {
    int len, pat_len, j, match;
    pat_len = strlen(pattern);
    len = strlen(input);
    int za = 0;
    j = 0;
    int count = 0;
    int mamba = 0;
    int k = 0;
    int result = 0;
    int howmanytimes = 0;
    for (i ; i+pat_len-1 < len && count < pat_len && mamba == 0; count++) {
        howmanytimes++;
        match = 1;
        k = 0;
        for (j = pat_len-1; j >= 0 && (i+j < len); j--) {
            if (input[i+j] != pattern[j]) {
                (*pointers)++;
                if(k == 0) {
                    result+= shiftingToBad(pattern,input[i+pat_len-1]);
                    count+= shiftingToBad(pattern,input[i+pat_len-1]);
                    i+= shiftingToBad(pattern,input[i+pat_len-1]);
                }
                else {
                    result += max(abs(shiftingToBad(pattern,input[i+pat_len-1])-k),find_shift_value(pattern,k));
                    count += max(abs(shiftingToBad(pattern,input[i+pat_len-1])-k),find_shift_value(pattern,k));
                    i += max(abs(shiftingToBad(pattern,input[i+pat_len-1])-k),find_shift_value(pattern,k));
                }
                match = 0;
                break;
            }
            else {

                match = 1;
                (*pointers)++;
                k++;
            }
        }
        if (match == 0 && shiftingToBad(pattern,input[i+pat_len-1]) == pat_len) {

        }
        else if (match == 1 && i+pat_len-1 < len) {
            strncat(output, &input[i-count],count);
            count = 0;
            mamba = 1;
            result += controlAgainForBoyerMoore(input, output, pattern, i+1, pointers)+1;
            break;
        }
    }
    if(howmanytimes == 0) {
        return result + pat_len;
    }
    else {
        return result;
    }

}
void badSymbolTable(char *pattern) {
    int pat_len = strlen(pattern);
    printf("--------------------------------------------------\n");
    printf("|              BAD SYMBOL TABLE                  |\n");
    printf("--------------------------------------------------\n");
    printf("|           Char              Shift              |\n");
    printf("--------------------------------------------------\n");


    int counter = 0;
    for(int z = pat_len-2; z >= 0; z--){
        for(int k = 1; z+k < pat_len-1;k++)  {
            if(pattern[z] == pattern[z+k]) {
                counter = 1;
            }
        }
        if (counter == 0) {
            printf("|            %c                  %d                |\n",pattern[z],pat_len-z-1);
       }
       counter = 0;
    }
    printf("|         Others                %d                |\n",pat_len);
    printf("---------------------------------------------------\n\n");
}
int shiftingToBad(char *pattern,char inputLastLetter) {

    int pat_len = strlen(pattern);
    int counter = 0;
    for(int i = pat_len-2; i>= 0;i--) {
        if(pattern[i] == inputLastLetter) {
            return (pat_len-i-1);
        }
    }
    return pat_len;
}
int max(int num1, int num2) {
    return (num1 > num2) ? num1 : num2;
}
int find_shift_value(char *pattern, int given_k) {
    int pat_len = strlen(pattern);
    int match = 1;
    int leng = pat_len-1;
    int just_1_time = 1;

    for(int k = given_k ; just_1_time == 1; just_1_time = 0)   {
        int shiftNum = 0;
            for(int i = 1; i <= leng;i++) {
                if(leng-i-k >= 0) {
                    if(pattern[leng] == pattern[leng-i] && pattern[leng-k] != pattern[leng-i-k]) {

                        if(k == 1) {
                            match = 1;
                            shiftNum = i;
                            break;
                        }
                        for(int j = 1; j <= k-1 ;j++) {
                            if(pattern[leng-j] != pattern[leng-i-j]) {
                                match = 0;
                                break;
                            }
                            else {
                                match = 1;
                                shiftNum = i;

                            }
                        }
                        if(match == 1) {

                            break;
                        }
                    }
                }
                else {
                    if(pattern[leng] == pattern[leng-i]) {

                        if(k==1) {
                            match = 1;
                            shiftNum = i;

                            break;
                        }
                        for(int j = 1; j <= k-1 ;j++) {
                            if(leng-i-j < 0) {
                                match = 1;
                                shiftNum = i;
                            }
                            else if(pattern[leng-j] != pattern[leng-i-j]) {

                                match = 0;
                                break;
                            }
                            else {
                                match = 1;
                                shiftNum = i;

                            }
                        }
                        if(match == 1) {

                            break;
                        }
                    }
                }
            }

        if(match == 0) {
            shiftNum = pat_len;
        }

        return shiftNum;

    }




}
void goodSuffixTable(char *pattern) {
    int pat_len = strlen(pattern);
    int match = 1;
    int leng = pat_len-1;
    int zero_matches = 1;
    //AT_THAT
    //for k
    printf("--------------------------------------------------\n");
    printf("|              GOOD SUFFIX TABLE                 |\n");
    printf("--------------------------------------------------\n");
    printf("|          k                       Shift         |\n");
    printf("--------------------------------------------------\n");


    for(int k = 1 ; k <= pat_len -1; k++)   {
        int shiftNum = 0;
            for(int i = 1; i <= leng;i++) {
                if(leng-i-k >= 0) {
                    if(pattern[leng] == pattern[leng-i] && pattern[leng-k] != pattern[leng-i-k]) {
                        zero_matches = 0;
                        if(k == 1) {
                            match = 1;
                            shiftNum = i;
                            break;
                        }
                        for(int j = 1; j <= k-1 ;j++) {
                            if(pattern[leng-j] != pattern[leng-i-j]) {
                                match = 0;
                                break;
                            }
                            else {
                                match = 1;
                                shiftNum = i;

                            }
                        }
                        if(match == 1) {

                            break;
                        }
                    }
                }
                else {
                    if(pattern[leng] == pattern[leng-i]) {
                        zero_matches = 0;
                        if(k==1) {
                            match = 1;
                            shiftNum = i;

                            break;
                        }
                        for(int j = 1; j <= k-1 ;j++) {
                            if(leng-i-j < 0) {
                                match = 1;
                                shiftNum = i;
                            }
                            else if(pattern[leng-j] != pattern[leng-i-j]) {

                                match = 0;
                                break;
                            }
                            else {
                                match = 1;
                                shiftNum = i;

                            }
                        }
                        if(match == 1) {

                            break;
                        }
                    }
                }
            }

        if(match == 0) {
            shiftNum = pat_len;
        }
        if(zero_matches == 1) {
            shiftNum = pat_len;
        }
        printf("|        k = %d                        %d          |\n",k,shiftNum);
    }
    printf("--------------------------------------------------\n");

}
void BoyerMoore(char *pattern, char *output, char *input,int length,int *ptrBoyer) {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);


    int len, pat_len, i, j, match;
    pat_len = strlen(pattern);
    len = strlen(input);
    int asd = 0;
    int k = 0;
    j = 0;

   for (i = 0; i < len; ) {
        k = 0;
        asd = 0;
        match = 1;

        if(i+pat_len-1 >= len) {
            strncat(output,&input[i],len-i);
            match = 2;
            //exit status
            i = len+1;
        }
        for (j = pat_len-1; j >= 0 && (i+pat_len-1 < len); j--) {
            if (input[i+j] == pattern[j]) {
                (*ptrBoyer)++;
                k++;
            }
            else {
                (*ptrBoyer)++;
                match = 0;
                break;
            }
        }
        if(match == 0) {
            int shifted = max(find_shift_value(pattern,k),abs(shiftingToBad(pattern,input[i+pat_len-1])-k)) ;
            strncat(output,&input[i], shifted);
            i += shifted;
        }


        else if (match == 1) {
            int k = 0;
            int *myP = &k;
            strcat(output, "<mark>");
            i += controlAgainForBoyerMoore(input, output, pattern, i+1,ptrBoyer) +1;
            strcat(output,pattern);
            strcat(output, "</mark>");
            strncat(output,&input[i-1],1);
            k = 0;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double execution_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf(" -> Execution Time For Bayer-Moore Algortihm   = %.6f milliseconds\n", execution_time*1000);
}
void HorsPool(char *pattern, char *output, char *input,int length, int *ptrHors){
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);



    int len, pat_len, i, j, match;
    pat_len = strlen(pattern);
    len = strlen(input);
    int k = 0;
    j = 0;

    for (i = 0; i < len; ) {
        k = 0;
        match = 1;
        if(i+pat_len-1 >= len) {
            strncat(output,&input[i],len-i);
            match = 2;
            i = len+1;
        }
        for (j = pat_len-1; j >= 0 && (i+pat_len-1 < len); j--) {
            if (input[i+j] != pattern[j]) {
                (*ptrHors)++;
                match = 0;
                break;
            }
            else {
                (*ptrHors)++;
            }
        }

        if (match == 0) {
            k = shiftingToBad(pattern,input[i+pat_len-1]);
            strncat(output, &input[i] , k);
            i += k;
        }
        else if (match == 1) {
            strcat(output, "<mark>");
            i += controlAgainForHorspool(input, output, pattern, i+1,ptrHors)+1;
            strcat(output,pattern);

            strcat(output, "</mark>");
            strncat(output,&input[i-1],1);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double execution_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf(" -> Execution Time For Horspool Algortihm      = %.6f milliseconds\n", execution_time*1000);
}
