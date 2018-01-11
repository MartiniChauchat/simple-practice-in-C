//  Tlookup.c
//  Student ID: 260712639
//  Name: Yudi.Xie
//  Created by Yudi.Xie on 2017/10/20.
//  Copyright © 2017 Yudi.Xie. All rights reserved.

#define MAXRECORDS 100
#define MAXNAMELENGTH 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentRecord                                                                       //define the struct body and
{                                                                                          //its members
    char FirstNames[MAXNAMELENGTH];
    char LastNames[MAXNAMELENGTH];
    int IDNums;
    int Marks;
    struct StudentRecord* left;                                                            //left child tree
    struct StudentRecord* right;                                                           //right child tree
};
int recordnum=0;                                                                               //set a counter as a global variable


struct StudentRecord* insert(struct StudentRecord *root, struct StudentRecord SRecords)    //function to insert node
{
    if(root==NULL){                                                                        //determine if the node exist, if not
        root=(struct StudentRecord*)malloc(sizeof(struct StudentRecord));                  //then do a inserting operation
        strcpy(root->FirstNames, SRecords.FirstNames);
        strcpy(root->LastNames, SRecords.LastNames);
        root->IDNums=SRecords.IDNums;
        root->Marks=SRecords.Marks;
        root->left = NULL;
        root->right = NULL;
    }
    else{                                                                                 //If the node exists
        if(strcmp(SRecords.LastNames, root->LastNames)<0)                                 //if the insert string smaller
        {                                                                                 //than the root, then left child
            root->left = insert(root->left, SRecords);
        }
        else if(strcmp(SRecords.LastNames, root->LastNames)>0)                            //if larger than the root, then
        {                                                                                 //right child
            root->right = insert(root->right, SRecords);
        }
    }
    return root;                                                                          //return if insert fails.
}

void inorder_traversal(struct StudentRecord *root, struct StudentRecord **pSRecords)      //Inorder traversal function
{
    extern int recordnum;                                                                     //use the extern variable to keep it
    if (root->left!=NULL) inorder_traversal(root->left, pSRecords);                       //consistent
    *(pSRecords +(recordnum++))=root;                                                         //read the BST in left-root-right order
    if (root->right!=NULL) inorder_traversal(root->right, pSRecords);
}

void binarysearch(struct StudentRecord *pSRecords[], int size, char target[])             //Binary search function
{
    int bottom= 0;
    int mid;
    int top = size - 1;
    int find;
    find = 0;
    
    while(bottom <= top)
    {
        mid = (bottom + top)/2;                                                                 //half the array
        if (strcasecmp(pSRecords[mid]->LastNames, target)==0)                                   //Use strcasecmp to
        {                                                                                       //eliminate case sensitivity
            find = 1;
            printf("The following record was found:\n");                                        //output the information if
            printf("Name: %s %s\n", pSRecords[mid]->FirstNames, pSRecords[mid]->LastNames);     //target is found
            printf("Student ID:%d\n",pSRecords[mid]->IDNums);
            printf("Student Grade: %d\n", pSRecords[mid]->Marks);
            return;
    }
        else if (strcasecmp(pSRecords[mid]->LastNames, target)>0)                           //search the other half
        {
            top = mid -1;
        }
        else
        {
            bottom = mid + 1;
        }
    }
    if(find==0)                                                                            //if search fails, return error message
    {
        printf("No Record found for student with Last name %s\n", target);
    }
}



int main(int argc, char *argv[]){
    struct StudentRecord *root;                                                             //pointer to struct body for BSTree
    struct StudentRecord SRecords;                                                          //struct body for read in array
    struct StudentRecord **pSRecords;                                                       //pointer to pointer for readin array
    int number=0;
    char Input[50];
    root=NULL;                                                                              //initialize the BSTree and root
    
    
    FILE * NamesIDs,* MarksData;                                                                        //Open files
    if((NamesIDs = fopen(argv[1], "r"))==NULL){
        printf("Cant't read from file %s\n", argv[1]);                                      //return error message if not found
        exit(1);
    }
    if((MarksData = fopen(argv[2], "r"))==NULL){
        printf("Cant't read from file %s\n", argv[2]);
        exit(1);
    }
    
    while(fscanf(NamesIDs,"%s%s%d", &(SRecords.FirstNames[0]),&(SRecords.LastNames[0]),&(SRecords.IDNums))!= EOF &&
          fscanf(MarksData,"%d",&(SRecords.Marks))!=EOF){
        number++;                                                                           //read in two txt files once
        root=insert(root, SRecords);                                                        //assign the read-in data to the BSTree
    }
    
    fclose(NamesIDs);                                                                       //to be safe, Close the filestream
    fclose(MarksData);
    
    pSRecords =(struct StudentRecord**)malloc(number*sizeof(struct StudentRecord*));        //allocate a pointerarray to store the
    inorder_traversal(root, pSRecords);                                                     //results for traversal.
    sscanf(argv[3],"%s",Input);
    binarysearch(pSRecords,number, Input);                                                  //Search the Inputed name, Done!
    return EXIT_SUCCESS;
}



















