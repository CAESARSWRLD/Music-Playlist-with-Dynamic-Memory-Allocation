#include "testFunctions.h"
#include "musicplayer.h"

void test_insert_new_record()
{
    FILE* testFile = fopen("testOutput.csv", "w");
    if (!testFile)
    {
        printf("error opening file to write\n");
        return;
    }

    Node* head = NULL;

    char newTitle[50] = "Chained to the Rhythm";
    char newArtist[50] = "Perry, Katy";
    char newAlbum[50] = "Witness";
    char newGenre[50] = "Pop";
    int newMinutes = 4;
    int newSeconds = 36;
    int newTimesPlayed = -1;
    int newRating = 6;



    ///calling insert_new_record
    insert_new_record(testFile, &head, true, newTitle, newArtist, newAlbum, newGenre, newMinutes, newSeconds, newTimesPlayed, newRating);

    if (head == NULL)
    {
        printf("test failed\n");
    }
    else
    {
        printf("test passed\n");
    }

    // check inserted values
    if (head != NULL)
    {
        printf("Song: %s\n", head->data.song);
        printf("Artist: %s\n", head->data.artist);
        printf("Album: %s\n", head->data.album);
        printf("Genre: %s\n", head->data.genre);
        printf("Duration: %d:%02d\n", head->data.duration.minutes, head->data.duration.seconds);
        printf("Times Played: %d\n", head->data.times_played);
        printf("Rating: %d\n", head->data.rating);

        if (head->data.times_played < 0) ///if invalid value
        {
            printf("times played is negative. this is invalid\n");
        }

        if (head->data.rating > 5 || head->data.rating < 1) ///if invalid value
        {
            printf("Invalid rating input\n");
        }
    }

    fclose(testFile);
}

void test_delete_record()
{
    ///create linked list
    Node* pHead = (Node*)malloc(sizeof(Node));
    if (!pHead)
    {
        printf("Memory allocation failed\n");
        return;
    }

    strcpy(pHead->data.artist, "Perry, Katy");
    strcpy(pHead->data.album, "Witness");
    strcpy(pHead->data.song, "Chained to the Rhythm");
    strcpy(pHead->data.genre, "pop");
    pHead->data.duration.minutes = 4;
    pHead->data.duration.seconds = 36;
    pHead->data.times_played = 3;
    pHead->data.rating = 5;
    pHead->pNext = NULL;


    ////calling delete_record
    printf("Before deleting the record: %s\n", pHead->data.song);
    delete_record(&pHead);



    if (pHead == NULL)
    {
        printf("Test passed\n");
    }
    else
    {
        printf("Test failed\n");
    }
}

void testShuffleFunction()
{
    Node* song1 = (Node*)malloc(sizeof(Node));
    Node* song2 = (Node*)malloc(sizeof(Node));
    Node* song3 = (Node*)malloc(sizeof(Node));

    if (!song1 || !song2 || !song3)
    {
        printf("malloc failure\n");
        return;
    }

    strcpy(song1->data.song, "Song 1");
    song1->pNext = song2;

    strcpy(song2->data.song, "Song 2");
    song2->pNext = song3;

    strcpy(song3->data.song, "Song 3");
    song3->pNext = NULL;

    Node* pHead = song1;

    int call_count = 0;
    int values[] = { 2, 0, 1 };

    printf("pre shuffle:\n");
    Node* temp = pHead;
    int i = 1;
    while (temp)
    {
        printf("(%d) %s\n", i++, temp->data.song);
        temp = temp->pNext;
    }



    int size = 3;///3 songs

    Node* nodes[3] = { song1, song2, song3 };

    for (int i = size - 1; i > 0; i--)
    {
        int j = values[call_count++ % 3];
        Node* tempNode = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = tempNode;
    }

    printf("\post shuffle:\n");
    for (int i = 0; i < size; i++) {
        printf("(%d) %s\n", i + 1, nodes[i]->data.song);
    }

    free(song1);
    free(song2);
    free(song3);
}
