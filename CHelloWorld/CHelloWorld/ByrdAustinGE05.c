/*
Austin Byrd
CS 2060 C Programming
GE05 Linked Lists and Files

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//pet structure
typedef struct{
    char name[80];//name of pet
    int age;//age of pet
}pet;

// linked list structure                  
typedef struct{
	pet data; // each listNode contains a pet
	struct listNode* nextPtr; // pointer to next node
}ListNode;
typedef ListNode* ListNodePtr; // synonym for ListNode*

// prototypes
int strcmp1(char* name1, char* name2);
void display(const ListNode* const list);
int isEmpty(const pet* const list);
void insertPets(ListNodePtr list);
void fgetsRemoveNewLine(char* str);
void deletePets(ListNodePtr list);
void fileWrite(const char* filename, const char mode, ListNodePtr list);
void clearList(ListNodePtr list);

int main()
{
    //list and head ptr to it
    ListNode myPets;
    ListNodePtr startPtr = &myPets;

    //insert pets
    char answer;
    do
    {
        printf("%s", "Another Pet? (y/n): ");
        answer = getchar();
        while (getchar() != '\n');
        if (answer == 'y')
        {
            insertPets(startPtr);
        }
        else if  (answer != 'y' && answer != 'n')
        {
            printf("%s", "Error enter either y or n:\n");
            answer = 'y';
        }
    } while (answer != 'n');

    //prints data
    display(startPtr);

    //write data to file
    fileWrite("file.txt", 'w', startPtr);

    //delete pets
    do
    {
        printf("%s", "Delete a Pet? (y/n): ");
        answer = getchar();
        while (getchar() != '\n');
        if (answer == 'y')
        {
            deletePets(startPtr);
        }
        else if (answer != 'y' && answer != 'n')
        {
            printf("%s", "Error enter either y or n:\n");
        }
    } while (answer != 'n');
    //prints data
    display(startPtr);

    //empty list contents
    clearList(startPtr);

    //print empty list
    display(startPtr);



}


//insert pets function
void insertPets(ListNodePtr list)
{
    char currentPetName[80];
    char petAgeTemp[80];
    int currentPetAge;

    printf("%s", "Enter pet name: ");
    fgetsRemoveNewLine(currentPetName);

    printf("\n%s", "Enter pet age: ");
    fgetsRemoveNewLine(petAgeTemp);
    currentPetAge = atoi(petAgeTemp);

    ListNode* currentPtr = list;
    currentPtr->nextPtr = NULL;
    ListNode* newPtr = malloc(sizeof(ListNode)); // create node
    currentPtr = newPtr;
    if (currentPtr != NULL)
    { // is space available
        ListNode* previousPtr = NULL;

        // loop to find the correct location in the list       
        while (currentPtr != NULL && strcmp1(newPtr->data.name, currentPtr->data.name))
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;

            // insert new node at beginning of list
            if (previousPtr == NULL)
            {
                newPtr->nextPtr = list;
                list = newPtr;
            }
            else
            { // insert new node between previousPtr and currentPtr
                previousPtr->nextPtr = newPtr;
                newPtr->nextPtr = currentPtr;
            }
        }
        *(currentPtr)->data.name = currentPetName; // place value in node
        currentPtr->data.age = currentPetAge; // place value in node
        currentPtr->nextPtr = NULL; // node does not link to another node

    }//else could not allocate memory returns 

}

// delete a list element
void deletePets(ListNodePtr list)
{
    char tempPetName[80];
    printf("%s", "Enter name of pet to delete: ");
    fgetsRemoveNewLine(tempPetName);

    ListNodePtr currentPtr = list;
    // delete first node if a match is found
    if (tempPetName == list->data.name)
    {
        ListNodePtr tempPtr = list;
        list = list->nextPtr;
        free(tempPtr);
    }
    else 
    {
        ListNodePtr previousPtr = list;
        ListNodePtr currentPtr = list->nextPtr;

        // loop to find the correctname in the list
        while (currentPtr != NULL && currentPtr->data.name != tempPetName) 
        {
            previousPtr = currentPtr; 
            currentPtr = currentPtr->nextPtr; 
        }

        // delete node at currentPtr
        if (currentPtr != NULL) 
        {
            ListNodePtr tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
        }
    }

}

void fileWrite(const char* filename, const char mode, ListNodePtr list)
{
    FILE* fptr = fopen(filename, &mode);
    ListNode* currentPtr = list;

    if (isEmpty(&(list->data)))
    {
        printf("%s", "No pets :(");
    }
    else
        fprintf(fptr, "%s", "Name:\tAge:");

    while (currentPtr != NULL)
    {
        fprintf(fptr, "%s\t%d", list->data.name, list->data.age);
        currentPtr = list->nextPtr;
    }
}

void clearList(ListNodePtr list)
{
    ListNodePtr currentPtr = list;
    ListNodePtr tempPtr = list; 
    while(currentPtr->nextPtr != NULL)
    {
        tempPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
        free(tempPtr);
    }
}


//if first name is greater than second return 1 else 0
int strcmp1(char* name1, char* name2)
{
    //if new name is > last checked name return true
    if (tolower(name1[0]) > tolower(name2[0]))
    {
        return 1;
    }
    else return 0;
}

void display(const ListNode* const list)
{
    ListNode *currentPtr = list;

    if (isEmpty(&(list->data)))
    {
        printf("%s", "No pets :(");
    }
    else  
        printf("%s\t%s", "Name:", "Age:");

    while (currentPtr->nextPtr != NULL)
    {
       printf("%s\t%d", list->data.name, list->data.age);
       currentPtr = (list->nextPtr);
    }
}

int isEmpty(const pet* const list)
{
    return list == NULL;
}

void fgetsRemoveNewLine(char* str)
{
    fgets(str, 80, stdin);
    int x = strlen(str);
    *(str + (x - 1)) = '\0';
}//end of fgetsRemoveNewLine

