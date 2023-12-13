#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define the struct for the fitness data
typedef struct
{
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps)
{
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL)
    {
        if (strlen(ptr)!=10){
            printf("Error: invalid file\n");
            exit(1);
        }
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL)
        {
            if (strlen(ptr)!=5){
                printf("Error: invalid file\n");
                exit(1);
            }
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL)
            {
                if(atoi(ptr)<=0){
                    printf("Error: invalid file\n");
                    exit(1);
                }
                *steps = atoi(ptr);
            }else{
                printf("Error: invalid file\n");
                exit(1);
            }
        }else{
            printf("Error: invalid file\n");
            exit(1);
        }
    }else{
        printf("Error: invalid file\n");
        exit(1);
    }
}
void swap(FitnessData* xp, FitnessData* yp)
{
    FitnessData temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
void bubbleSort(FitnessData arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].steps < arr[j + 1].steps) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
} 

FILE *open_file(char fileName[], char mode[])
{
    FILE *file = fopen(fileName, mode);
    if (file == NULL)
    {
        printf("Error: invalid file\n");
        exit(1);
    }
    return file;
}

int main(){
    FitnessData data[200];
    char fileName[50];
    printf("Enter filename: ");
    scanf("%s", fileName);
    FILE *file = open_file(fileName, "r");
    int noRec = 0;
    char line_buffer[200];
    int buffer_size = 200;
    char delimeter = ',';
    while (fgets(line_buffer, buffer_size, file) != NULL){
        int stepsTemp;
        char *dateTemp = (char *)malloc(11);
        char *timeTemp = (char *)malloc(6);
        tokeniseRecord(line_buffer, delimeter, dateTemp, timeTemp, &stepsTemp);

        strcpy(data[noRec].date, dateTemp);
        strcpy(data[noRec].time, timeTemp);
        data[noRec].steps = stepsTemp;

        noRec++;
    }
    bubbleSort(data, noRec);
    FILE *newFile = open_file(strcat(fileName, ".tsv"), "w");
    fclose(file);
    for (int j = 0; j<noRec; j++){
        fprintf(newFile, "%s\t%s\t%d\n", data[j].date, data[j].time, data[j].steps);
    }
}
    


