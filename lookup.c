//  lookup.c
//  Student ID: 260712639
//  Name: Yudi.Xie
//  Created by Yudi.Xie on 2017/9/25.
//  Copyright © 2017 Yudi.Xie. All rights reserved.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXRECORDS 100
#define MAXNAMELENGTH 50

struct StudentRecord                                                    //define the structure body
{
    char FirstNames[MAXNAMELENGTH];                                     //define the members of the structure
    char LastNames[MAXNAMELENGTH];
    int IDNums;
    int Marks;
};

void swap(struct StudentRecord *pSRecords[], int a, int b)              /*swap: interchange array[a] and array[b]*/
{
    struct StudentRecord *holder;                                       //instructmental variable
    holder=pSRecords[a];
    pSRecords[a]=pSRecords[b];
    pSRecords[b]=holder;                                                //array[a] and array[b] swapped
}

void quicksort(struct StudentRecord *pSRecords[], int bottom, int top)  /*quicksort: sort the array in increasing order*/
{
    int i, last;
    struct StudentRecord *point;
    if (bottom>=top)                                                    //do nothing if the array has less than 2 elements
        return;
    swap(pSRecords, bottom, (bottom+top)/2);                            //pick a midpoint as pivot
    point=pSRecords[last=bottom];                                       //and separate into side<pivot and side>=pivot
    for (i=bottom+1;i<=top;i++)
        if((strcmp(pSRecords[i]->LastNames,point ->LastNames))<0)
        swap(pSRecords,++last,i);
    swap(pSRecords, bottom, last);                                      //put the pivot back
    if (last>bottom)
        quicksort(pSRecords, bottom, last-1);                           //sort both side with recursion
    if (last<top)
        quicksort(pSRecords, last+1, top);
}

void binarysearch(struct StudentRecord *pSRecords[], int size, char target[])   /*binarysearch: search for a keyword in a array*/
{
    int bottom= 0;
    int mid;
    int top = size - 1;
    int find;
    find = 0;
    
    while(bottom <= top)
    {
        mid = (bottom + top)/2;                                         //half the array
        if (strcmp(pSRecords[mid]->LastNames, target) == 0)             //if the mid element is equal to the target
        {                                                               //print the infomation
            find = 1;
            printf("The following record was found:\n");
            printf("Name: %s %s\n",pSRecords[mid]->FirstNames, target);
            printf("Student ID: %d\n",pSRecords[mid]->IDNums);
            printf("Student Grade: %d\n",pSRecords[mid]->Marks);
            return;
        }
        else if (strcmp(pSRecords[mid]->LastNames, target) > 0)         //if not, search the other half
        {
            top    = mid - 1;
        }
        else
        {
            bottom = mid + 1;
        }
    }
        if(find==0)
        {
        printf("No Record found for student with Last name %s\n",target);
        }
}




int main(int argc, char * argv[])
{
    struct StudentRecord *pSRecords[MAXRECORDS];
    struct StudentRecord  SRecords[MAXRECORDS];
    int numrecords, nummarks;
    int i;
    char Input[50];
    
    for (i=0;i<50;i++)
    {
        pSRecords[i]=&SRecords[i];
    }
    
    FILE * NamesIDsDataFile;                                                     //read the file
    if((NamesIDsDataFile = fopen(argv[1], "r")) == NULL){
        printf("Can't read from file %s\n", argv[1]);
        exit(1);
    }
    numrecords=0;
    while (fscanf(NamesIDsDataFile,"%s%s%d",&(pSRecords[numrecords]->FirstNames[0]),  //scan file and store in array
                  &(pSRecords[numrecords]->LastNames[0]),
                  &(pSRecords[numrecords]->IDNums)) != EOF) {
        numrecords++;
    }
    fclose(NamesIDsDataFile);
    
    //Read in marks data
    FILE * MarksDataFile;
    if((MarksDataFile = fopen(argv[2], "r")) == NULL){
        printf("Can't read from file %s\n", argv[2]);
        exit(1);
    }
    nummarks=0;
    while(fscanf(MarksDataFile,"%d",&(pSRecords[nummarks]->Marks)) != EOF) {
        nummarks++;
    }
    fclose(MarksDataFile);
    
    sscanf(argv[3],"%s",Input);
    quicksort(&pSRecords, 0, numrecords-1);                                 //perform the quicksort function
    binarysearch(&pSRecords, numrecords, Input);
    
    return EXIT_SUCCESS;
}


