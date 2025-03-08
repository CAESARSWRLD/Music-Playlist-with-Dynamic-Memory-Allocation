#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>





typedef enum boolean
{
    FALSE, TRUE
} Boolean;



typedef struct duration
{
    int minutes;
    int seconds;
} Duration;



typedef struct
{
    char artist[100];
    char album[100];
    char song[100];
    char genre[50];
    struct {
        int minutes;
        int seconds;
    } duration;
    int times_played;
    int rating;
} Record;





typedef struct node///for doubly linked list
{
    Record data;
    struct node* pNext;
    struct node* pPrev;
} Node;




int countNodes(Node* pHead);

void shuffle_list(Node* pHead);

void shuffle(Node* pHead);

int randon_num_generator(Node* pHead);

int caseInsensitiveCompare(const char* str1, const char* str2);

void bubbleSort(Node* pHead, int choice);

void swapNodes(Node* a, Node* b);

void sort_method(int choice_of_method, Node* pHead);

void sort_list(Node** pHead);

int insert_new_record(FILE* f1, Node** pHead, bool test, char newTitle[50], char newArtist[50], char newAlbum[50], char newGenre[50], int newMinutes, int newSeconds, int newTimesPlayed, int newRating);

void printTimeDuration(int sec);

void sleep(int ms);

int time_out(int sec);//not needed

void play(Node* pHead, int rate);

void clear_the_screen();

void printListReverse(Node* pTail);

int insertFront(Node** pList, Record newData);

void menuChoice(Node** pHead);

void initList(Node** pList); // set the list to empty

Record parse_line(char* line);

void loadList(FILE* file, char* line, Node* pHead);

void loadList_print(FILE* file, char* line, Node** pHead);

void insertEnd(Node** pList, Record newRecord);

void storeList(FILE* file, Node* pHead);

void displayList(FILE* file, Node* pHead);

void edit_record(FILE* file, Node* pHead, int rate);//allows the editing of records, also can be used for the rate function based on the integer input.
//Input 1 for the rate parameter if using this function as a rate function

int random_num_generator();

void delete_record(Node* pHead);


// Description: Prints all contact information in the list
// Returns: Nothing
void printList(Node* pHead);

// Description: Allocates space for a Node on the heap and initializes
//the Node with the information found in newData.
// Returns: The address of the start of the block of memory on the heap
//or NULL if no memory was allocated
Node* makeNode(Record newData);


// Description: Uses makeNode () to allocate space for a new Node and
//inserts the new Node into the list in alphabetic order('a' - 'z')
// based on the name field
// Returns: TRUE if memory was allocated for a Node; FALSE otherwise
Boolean insertContactInOrder(Node** pList, Record newData);


// Description: Deletes a Contact in the list based on the name field;
//deletes the first occurence of the name
// Returns: TRUE if the Contact was found; FALSE otherwise
Boolean deleteContact(Node** pList, Record searchContact);


// Description: Edits a Contact in the list based on the name field;
//edits the first occurence of the name
// Returns: TRUE if the Contact was found; FALSE otherwise
Boolean editContact(Node* pList, Record searchContact);


// Description: Loads all Contact information from the given file, in
//alphabetic order, based on the name, into the list
// Returns: TRUE if all Contacts were loaded; FALSE otherwise
Boolean loadContacts(FILE* infile, Node** pList);


// Description: Stores all Contact information from the list into the
//given file
// Returns: TRUE if all Contacts were stored; FALSE otherwise
Boolean storeContacts(FILE* infile, Node* pList);





void press_any_key_to_continue();







#endif