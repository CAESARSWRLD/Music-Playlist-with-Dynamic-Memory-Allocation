#include "musicplayer.h"


void menuChoice(Node** pHead)
{



	bool loop_running = true;

	char line[500];



	initList(pHead);


	while (loop_running)
	{

		FILE* f1 = fopen("playlist.csv", "r");

		if (f1 == NULL)
		{
			printf("Error opening file");
		}

		int choice = 0;
		printf("Selection:\n(1) load (load must be selected before any other options can be used)\n(2) store\n(3) display\n(4) insert\n(5) delete\n(6) edit\n(7) sort\n(8) rate\n(9) play\n(10) shuffle\n(11) exit (this option also stores changes before exiting)\n");
		scanf("%d", &choice);




		if (choice == 1)//LOAD
		{

			clear_the_screen();

			loadList(f1, line, pHead);

			printf("\nList successfully created\n");

		}
		else if (choice == 2)//STORE
		{

			clear_the_screen();

			fclose(f1);

			f1 = fopen("musicPlayList.csv", "w");//re-open the file in write mode

			storeList(f1, *pHead);

			fclose(f1);

		}
		else if (choice == 3)//DISPLAY  /  PRINTLIST
		{

			clear_the_screen();

			displayList(f1, *pHead);

		}
		else if (choice == 4)//INSERT
		{
			if (insert_new_record(f1, pHead, false, "none", "none", "none", "none", 0, 0, 0, 0) == 1)
			{
				printf("Song successsfully added\n");
			}
		}
		else if (choice == 5)//DELETE
		{
			delete_record(pHead);
		}
		else if (choice == 6)//EDIT
		{
			edit_record(f1, *pHead, 0);

		}
		else if (choice == 7)//SORT
		{
			sort_list(pHead);
		}
		else if (choice == 8)//RATE
		{
			edit_record(f1, *pHead, 1);
		}
		else if (choice == 9)//PLAY
		{
			play(*pHead, 0);
		}
		else if (choice == 10)//SHUFFLE
		{
			shuffle(*pHead);
		}
		else if (choice == 11)//EXIT   this option is similar to the store option however it exits the program after storing
		{

			fclose(f1);

			f1 = fopen("musicPlayList.csv", "w");//re-open the file in write mode

			storeList(f1, *pHead);
			fclose(f1);
			loop_running = false;

			printf("\nchanges saved\n");
		}
		fclose(f1);
	}


	clear_the_screen();
}

//self explanatory
int countNodes(Node* pHead)
{
	Node* temp = pHead;
	int count = 0;


	while (temp != NULL)
	{
		count++;
		temp = temp->pNext;
	}
	return count;


}

//shuffles, prints and plays songs in the shuffled order
void shuffle(Node* pHead)
{
	if (!pHead)
	{
		printf("empty list!");
	}

	int size = countNodes(pHead);

	Node** nodeArray = (Node**)malloc(size * sizeof(Node*));///set pointers to each node

	if (!nodeArray)
	{
		printf("malloc faliure\n");
	}

	Node* temp = pHead;
	for (int i = 0; i < size; i++)
	{
		nodeArray[i] = temp;
		temp = temp->pNext;
	}

	srand(time(NULL));//seed random numbers

	for (int i = size - 1; i > 0; i--) //'fisher-yates' randomization
	{
		int j = rand() % (i + 1);
		Node* tempNode = nodeArray[i];
		nodeArray[i] = nodeArray[j];
		nodeArray[j] = tempNode;
	}


	clear_the_screen();


	for (int i = 0; i < size; i++)
	{
		clear_the_screen();

		printf("Playing shuffled playlist:\n");

		printf("(%d) %s, %s, %d:%02d, %d plays, rated %d/5\n",
			i + 1,
			nodeArray[i]->data.artist,
			nodeArray[i]->data.song,
			nodeArray[i]->data.duration.minutes,
			nodeArray[i]->data.duration.seconds,
			nodeArray[i]->data.times_played,
			nodeArray[i]->data.rating);

		printf("\nCountdown to next track:\n");
		printTimeDuration(((nodeArray[i]->data.duration.minutes) * 60) + nodeArray[i]->data.duration.seconds);//prints time based on minute and seconds data

	}



	// Free allocated memory
	free(nodeArray);
}

int get_length_of_list(Node* pHead)
{
	int length = 0;
	Node* current = pHead;
	while (current != NULL)
	{
		length++;
		current = current->pNext;

	}
	return length;
}

void bubbleSort(Node* pHead, int choice)
{
	if (pHead == NULL || pHead->pNext == NULL)
	{
		printf("List is empty or has only one node; no sorting needed.\n");
		return;
	}

	int swapped;
	Node* ptr1;
	Node* lptr = NULL;
	switch (choice)
	{
	case 1:///sorting by artist
		do
		{
			swapped = 0;
			ptr1 = pHead;

			while (ptr1->pNext != lptr)
			{
				if (ptr1->data.artist != NULL && ptr1->pNext->data.artist != NULL &&
					strcmp(ptr1->data.artist, ptr1->pNext->data.artist) > 0)
				{
					swapNodes(ptr1, ptr1->pNext);
					swapped = 1;
				}
				ptr1 = ptr1->pNext;
			}
			lptr = ptr1;
		} while (swapped);
		break;
	case 2:///by album
		do
		{
			swapped = 0;
			ptr1 = pHead;

			while (ptr1->pNext != lptr)
			{
				if (ptr1->data.album != NULL && ptr1->pNext->data.album != NULL &&
					strcmp(ptr1->data.album, ptr1->pNext->data.album) > 0)
				{
					swapNodes(ptr1, ptr1->pNext);
					swapped = 1;
				}
				ptr1 = ptr1->pNext;
			}
			lptr = ptr1;
		} while (swapped);
		break;
	case 3:///by rating
		do
		{
			swapped = 0;
			ptr1 = pHead;

			while (ptr1->pNext != lptr)
			{
				if (ptr1->data.rating != NULL && ptr1->pNext->data.rating != NULL &&
					ptr1->data.rating > ptr1->pNext->data.rating)
				{
					swapNodes(ptr1, ptr1->pNext);
					swapped = 1;
				}

				ptr1 = ptr1->pNext;
			}
			lptr = ptr1;
		} while (swapped);
		break;
	case 4:///by times played
		do
		{
			swapped = 0;
			ptr1 = pHead;

			while (ptr1->pNext != lptr)
			{

				if (ptr1->data.times_played != NULL && ptr1->pNext->data.times_played != NULL &&
					ptr1->data.times_played > ptr1->pNext->data.times_played)

				{
					swapNodes(ptr1, ptr1->pNext);
					swapped = 1;
				}
				ptr1 = ptr1->pNext;
			}
			lptr = ptr1;
		} while (swapped);
		break;
	default:
		printf("Invalid input");
		break;
	}



}

///like strcmp but ignores differences in letter case
int caseInsensitiveCompare(const char* str1, const char* str2)
{
	while (*str1 && *str2)
	{
		if (tolower(*str1) != tolower(*str2))
		{
			return tolower(*str1) - tolower(*str2);
		}
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

void swapNodes(Node* a, Node* b)
{
	Record temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void sort_method(int choice_of_method, Node* pHead)
{

	switch (choice_of_method)
	{
	case 1:
		//////by artist

		printf("SORTING BY ARTIST\n");

		bubbleSort(pHead, 1);

		break;
	case 2:
		///////by albumn title

		printf("SORTING BY TITLE\n");

		bubbleSort(pHead, 2);

		break;
	case 3:
		//////by rating

		printf("SORTING BY RATING\n");

		bubbleSort(pHead, 3);

		break;
	case 4:
		///////by times played

		printf("SORTING BY TIMES PLAYED\n");

		bubbleSort(pHead, 4);

		break;
	default:
		printf("Invalid input");
		break;
	}
}

void sort_list(Node** pHead)
{

	clear_the_screen();
	Node* current = *pHead;

	int selection = 0;
	printf("How would you like to sort the list?\n(1) by artist (A-Z)\n(2) By title (A-Z)\n(3) By rating (1-5)\n(4) By times played (largest to smallest)");
	scanf("%d", &selection);



	sort_method(selection, *pHead);



	printf("%s", current->data.album);

}

void delete_record(Node** pHead)
{


	if (*pHead == NULL)
	{
		printf("The list is empty\n");
		return;
	}

	getchar();

	char song_to_delete[50];
	printf("Which record would you like to delete?\n");
	fgets(song_to_delete, sizeof(song_to_delete), stdin);


	///////
	size_t len = strlen(song_to_delete);
	if (len > 0 && song_to_delete[len - 1] == '\n')
	{
		song_to_delete[len - 1] = '\0';///remove newline char
	}
	////////

	Node* current = *pHead;
	Node* previous = NULL;




	while (current != NULL)
	{





		printf("starting out this compares the following: %s and %s", current->data.song, song_to_delete);





		if (strcmp(current->data.song, song_to_delete) == 0)
		{


			printf("%s%s%s,%s,%s,%s,%d:%02d,%d,%d\n",
				(strchr(current->data.artist, ',') ? "\"" : ""), current->data.artist,
				(strchr(current->data.artist, ',') ? "\"" : ""),//correctly formats the quotations in the artist name
				current->data.album,
				current->data.song,
				current->data.genre,
				current->data.duration.minutes,
				current->data.duration.seconds,
				current->data.times_played,
				current->data.rating);


			if (previous == NULL)
			{
				*pHead = current->pNext;
			}
			else
			{
				previous->pNext = current->pNext;
			}

			free(current);
			printf("Record deleted!\n");
			return;
		}
		else
		{
			printf("song not found\n");
		}

		previous = current;
		current = current->pNext;//next node


	}
}

int insert_new_record(FILE* f1, Node** pHead, bool test, char newTitle[50], char newArtist[50], char newAlbum[50], char newGenre[50], int newMinutes, int newSeconds, int newTimesPlayed, int newRating)
{


	Record record;


	getchar();/////clear character


	/// IMPORTANT: fgets places a newline character at the end of the string. This ruins the csv format
	/// the newline needs to be removed with strtok





	if (test)
	{

		printf("Song title: %s\n", newTitle);
		strcpy(record.song, newTitle);


		printf("Artist name: %s\n", newArtist);
		strcpy(record.artist, newArtist);


		printf("Album name: %s\n", newAlbum);
		strcpy(record.album, newAlbum);


		printf("Genre: %s\n", newGenre);
		strcpy(record.genre, newGenre);


		printf("Minutes: %d\n\n", newMinutes);
		record.duration.minutes = newMinutes;


		printf("Seconds: %d\n\n", newSeconds);
		record.duration.seconds = newSeconds;


		printf("Times played: %d\n\n", newTimesPlayed);
		record.times_played = newTimesPlayed;


		printf("Rating: %d\n\n", newRating);
		record.rating = newRating;

	}
	else
	{



		char newTitle[50], newArtist[50], newAlbum[50], newGenre[50];
		int newMinutes, newSeconds, newTimesPlayed, newRating;





		printf("What is the song title of the new record?:\n");
		fgets(newTitle, sizeof(newTitle), stdin);
		strtok(newTitle, "\n");////THIS removes the newline character at the end of the string
		printf("Song title: %s\n", newTitle);
		strcpy(record.song, newTitle);

		printf("What is the artist name for the new record?:\n");
		fgets(newArtist, sizeof(newArtist), stdin);
		strtok(newArtist, "\n");
		printf("Artist name: %s\n", newArtist);
		strcpy(record.artist, newArtist);

		printf("What is the album name for the new record?:\n");
		fgets(newAlbum, sizeof(newAlbum), stdin);
		strtok(newAlbum, "\n");
		printf("Album name: %s\n", newAlbum);
		strcpy(record.album, newAlbum);

		printf("What is the genre for the new record?:\n");
		fgets(newGenre, sizeof(newGenre), stdin);
		strtok(newGenre, "\n");
		printf("Genre: %s\n", newGenre);
		strcpy(record.genre, newGenre);

		printf("What is the duration of minutes for the new record?:\n");
		scanf("%d", &newMinutes);
		printf("Minutes: %d\n\n", newMinutes);
		record.duration.minutes = newMinutes;
		printf("%d\n", record.duration.minutes);

		printf("What is the duration of seconds for the new record?:\n");
		scanf("%d", &newSeconds);
		printf("Seconds: %d\n\n", newSeconds);
		record.duration.seconds = newSeconds;

		printf("How many times has the new record been played?:\n");
		scanf("%d", &newTimesPlayed);
		printf("Times played: %d\n\n", newTimesPlayed);
		record.times_played = newTimesPlayed;

		printf("What is the rating of the new record?:\n");
		scanf("%d", &newRating);
		printf("Rating: %d\n\n", newRating);
		record.rating = newRating;
	}




	////debug
	/*printf("%s\n", record.song);
	printf("%s\n", record.artist);
	printf("%s\n", record.album);
	printf("%s\n", record.genre);
	printf("%d\n", record.duration.minutes);
	printf("%d\n", record.duration.seconds);
	printf("%d\n", record.times_played);
	printf("%d\n", record.rating);*/




	insertFront(pHead, record);//insertFront returns 1 if it successfully inserts to front

	Node* current = pHead;

	record = current->data;

	fprintf(f1, "%s%s%s,%s,%s,%s,%d:%02d,%d,%d\n",
		(strchr(record.artist, ',') ? "\"" : ""), record.artist, (strchr(record.artist, ',') ? "\"" : ""),//correctly formats the quotations in the artist name
		record.album,
		record.song,
		record.genre,
		record.duration.minutes,
		record.duration.seconds,
		record.times_played,
		record.rating);


	//after this function runs, the store function should be used to save changes to the csv file

}

///timer
void sleep(int ms)
{
	clock_t start = clock();
	while (clock() < start + ms * (CLOCKS_PER_SEC / 1000));
}

///prints the time on a timer
void printTimeDuration(int sec)
{
	int i = sec;
	time_t start = time(NULL);
	while (difftime(time(NULL), start) < sec)
	{
		printf("%d", i);
		fflush(stdout);
		sleep(500);

		printf(".", i);
		fflush(stdout);
		sleep(500);


		--i;
	}
}

void play(Node* pHead, int rate)
{

	char song_chosen[50];


	getchar();/////clear character


	printf("\nWhat song would you like to start playing a song from?\n");
	fgets(song_chosen, sizeof(song_chosen), stdin);////was having lots of trouble reading user input before include the getchar() above this line



	Node* current = pHead;

	printf("SONG: %s\n", song_chosen);

	while (current != NULL)
	{
		Record record = current->data;

		printf("starting out this compares the following: %s and %s", current->data.song, song_chosen);




		//////The following correctly formats the song_chosen to be compared to the song within the database
		size_t len = strlen(song_chosen);
		if (len > 0 && song_chosen[len - 1] == '\n')
		{
			song_chosen[len - 1] = '\0';
		}
		////////


		if (strcmp(current->data.song, song_chosen) == 0)
		{


			printf("%s%s%s,%s,%s,%s,%d:%02d,%d,%d\n",
				(strchr(record.artist, ',') ? "\"" : ""), record.artist,
				(strchr(record.artist, ',') ? "\"" : ""),//correctly formats the quotations in the artist name
				record.album,
				record.song,
				record.genre,
				record.duration.minutes,
				record.duration.seconds,
				record.times_played,
				record.rating);


			break;
		}
		else
		{
			printf("song not found\n");
		}


		current = current->pNext;//next node


	}






	//////////now the song that was chosen must be found
	current = pHead;

	while (current != NULL)
	{
		Record record = current->data;

		if (strcmp(record.song, song_chosen) == 0)
		{


			bool playlist = true;

			while (playlist)
			{

				///this following if statement must go before everything else or else the program would crash after the
				//end of the playlist has been reached


				if (current == NULL)//check if the end of the playlist has been reached
				{
					printf("END OF PLAYLIST\n");
					return;
				}

				Record record = current->data;

				clear_the_screen();



				printf("\n***Song playing***\n");


				printf("%s%s%s,%s,%s,%s,%d:%02d,%d,%d\n",
					(strchr(record.artist, ',') ? "\"" : ""), record.artist,
					(strchr(record.artist, ',') ? "\"" : ""),//correctly formats the quotations in the artist name
					record.album,
					record.song,
					record.genre,
					record.duration.minutes,
					record.duration.seconds,
					record.times_played,
					record.rating);


				printTimeDuration(5);





				current = current->pNext;



			}






		}


		current = current->pNext;//next node
	}
}

void clear_the_screen()
{
	system("cls");
}

void initList(Node** pList)
{
	*pList = NULL;
}

Node* makeNode(Record newData)
{
	Node* pMem = malloc(sizeof(Node));

	if (pMem != NULL)
	{
		pMem->data = newData;
		pMem->pNext = NULL;
		pMem->pPrev = NULL;
	}

	return pMem;
}

Boolean insertContactInOrder(Node** pList, Record newData)
{

}

void printList(Node* pHead)
{
	if (pHead == NULL)
	{
		printf("The list is empty.\n");
		return;
	}

	Node* temp = pHead;
	int nodeIndex = 0;
	while (temp != NULL) {
		printf("\nNode %d:\n", nodeIndex++);
		printf("Artist: %s\nAlbum: %s\nSong: %s\nGenre: %s\nDuration: %d:%02d\nTimes Played: %d\nRating: %d\n",
			temp->data.artist,
			temp->data.album,
			temp->data.song,
			temp->data.genre,
			temp->data.duration.minutes,
			temp->data.duration.seconds,
			temp->data.times_played,
			temp->data.rating);

		temp = temp->pNext;
	}
}

void printListReverse(Node* pTail)
{
	Node* temp = pTail;

	while (temp != NULL)
	{
		printf("Artist: %s\n", temp->data.artist);
		printf("Album: %s\n", temp->data.album);
		temp = temp->pPrev;
	}
}

int insertFront(Node** pList, Record newData)//sienote: pList is the same as pHead
{
	Node* pMem = (Node*)malloc(sizeof(Node));///pMem is the new node

	if (pMem == NULL)  //check for null
	{
		printf("Error: Memory allocation failed in makeNode.\n");
		return 0;
	}

	pMem->data = newData;//copy record ino new node


	pMem->pNext = *pList;//insert it at the fron of the list
	*pList = pMem;


	return 1;//for successful insertion
}

Record parse_line(char* line)
{
	Record record;
	char* token;

	/////artist name
	if (line[0] == '\"')
	{
		token = strtok(line, "\"");
		strcpy(record.artist, token);
		strtok(NULL, ","); //skip comma
	}
	else
	{
		token = strtok(line, ",");
		strcpy(record.artist, token);
	}

	/////album
	token = strtok(NULL, ",");
	strcpy(record.album, token);

	////title
	token = strtok(NULL, ",");
	strcpy(record.song, token);

	/////genre
	token = strtok(NULL, ",");
	strcpy(record.genre, token);

	/////duration
	token = strtok(NULL, ":");
	record.duration.minutes = atoi(token);
	token = strtok(NULL, ",");
	record.duration.seconds = atoi(token);

	/////times played
	token = strtok(NULL, ",");
	record.times_played = atoi(token);

	/////rating
	token = strtok(NULL, ",");
	record.rating = atoi(token);

	return record;
}

void loadList_print(FILE* file, char* line, Node** pHead)
{

	Record record;


	while (fgets(line, 500, file) != NULL)
	{


		line[strcspn(line, "\n")] = '\0';

		char starting_char = line[0];



		//////READING ARTIST NAME
		//////and saving it to struct
		char* token;
		if (starting_char == '\"')//LINE STARTS WITH A QUOTE
		{



			//create a token for the name. I'm using a double quote as the delimiter 
			//because it allows me to disregard the comma in between the two 
			//names if there are two
			// 
			//this following strtok with the double quote only happens because the artsit 
			//name starts with a double quote and has two names
			token = strtok(line, "\"");//this reads the artist name
			strcpy(record.artist, token);//saves the name to the struct




			token = strtok(NULL, ",");//skips the comman after the artist name quote

		}
		else//LINE STARTS WITHOUT A QUOTE
		{
			token = strtok(line, ",");
			strcpy(record.artist, token);
			token = strtok(NULL, ",");//skips the comman after the artist name quote


		}





		///////reading the album name
		strcpy(record.album, token);



		////////reding the song title
		token = strtok(NULL, ",");
		strcpy(record.song, token);


		////////reding the song genre
		token = strtok(NULL, ",");
		strcpy(record.genre, token);



		/////reading the duration/length of the song
		token = strtok(NULL, ":");//this reads the artist name
		record.duration.minutes = atoi(token);

		token = strtok(NULL, ",");//skips the comman after the artist name quote
		record.duration.seconds = atoi(token);//atoi returns the integer value of the string




		///////times played
		token = strtok(NULL, ",");
		record.times_played = atoi(token);


		//////rating
		token = strtok(NULL, ",");
		record.rating = atoi(token);




		fprintf(file, "%s, %s, %s, %s, %d:%02d, %d, %d\n",
			record.artist, record.album, record.song, record.genre,
			record.duration.minutes, record.duration.seconds,
			record.times_played, record.rating);

		// Insert into list
		insertEnd(pHead, record);



	}

};

void loadList(FILE* file, char* line, Node** pHead)
{

	Record record;


	while (fgets(line, 500, file) != NULL)
	{


		line[strcspn(line, "\n")] = '\0';//removes newline character

		char starting_char = line[0];



		//////READING ARTIST NAME
		//////and saving it to struct
		char* token;
		if (starting_char == '\"')//LINE STARTS WITH A QUOTE

		{



			//create a token for the name. I'm using a double quote as the delimiter 
			//because it allows me to disregard the comma in between the two 
			//names if there are two
			// 
			//this following strtok with the double quote only happens because the artsit 
			//name starts with a double quote and has two names
			token = strtok(line, "\"");//this reads the artist name
			strcpy(record.artist, token);//saves the name to the struct




			token = strtok(NULL, ",");//skips the comman after the artist name quote

		}
		else//LINE STARTS WITHOUT A QUOTE
		{
			token = strtok(line, ",");
			strcpy(record.artist, token);
			token = strtok(NULL, ",");//skips the comman after the artist name


		}





		///////reading the album name
		strcpy(record.album, token);



		////////reding the song title
		token = strtok(NULL, ",");
		strcpy(record.song, token);


		////////reding the song genre
		token = strtok(NULL, ",");
		strcpy(record.genre, token);



		/////reading the duration/length of the song
		token = strtok(NULL, ":");//this reads the artist name
		record.duration.minutes = atoi(token);

		token = strtok(NULL, ",");//skips the comman after the artist name quote
		record.duration.seconds = atoi(token);//atoi returns the integer value of the string




		///////times played
		token = strtok(NULL, ",");
		record.times_played = atoi(token);


		//////rating
		token = strtok(NULL, ",");
		record.rating = atoi(token);




		printf("%s, %s, %s, %s, %d:%02d, %d, %d\n",
			record.artist, record.album, record.song, record.genre,
			record.duration.minutes, record.duration.seconds,
			record.times_played, record.rating);

		////// Insert into the list
		insertEnd(pHead, record);

	}
}

void insertEnd(Node** pHead, Record newRecord)
{
	Node* pNew = (Node*)malloc(sizeof(Node));


	// copy record into the new node
	pNew->data = newRecord;
	pNew->pNext = NULL;

	if (*pHead == NULL)//if list is empty
	{

		*pHead = pNew;
	}
	else
	{
		// find the end of the list and add the new node
		Node* temp = *pHead;
		while (temp->pNext != NULL)
		{
			temp = temp->pNext;
		}
		temp->pNext = pNew;
	}
}

void press_any_key_to_continue()
{
	printf("Press any key to continue\n");
	getchar();
}

void storeList(FILE* file, Node* pHead)
{
	FILE* outfile = fopen("playlist.csv", "w");
	Node* current = pHead;
	while (current != NULL)
	{
		Record record = current->data;
		char* str = "hello";
		//fprintf(outfile, "%s", str);
		fprintf(outfile, "%s%s%s,%s,%s,%s,%d:%02d,%d,%d\n",
			(strchr(record.artist, ',') ? "\"" : ""), record.artist, (strchr(record.artist, ',') ? "\"" : ""),//correctly formats the quotations in the artist name
			record.album,
			record.song,
			record.genre,
			record.duration.minutes,
			record.duration.seconds,
			record.times_played,
			record.rating);

		current = current->pNext;//next node
	}
}

void displayList(FILE* file, Node* pHead)
{



	Node* current = pHead;



	printf("DISPLAYING LIST\n");
	while (current != NULL)
	{
		Record record = current->data;

		printf("%s%s%s,%s,%s,%s,%d:%02d,%d,%d\n",
			(strchr(record.artist, ',') ? "\"" : ""), record.artist, (strchr(record.artist, ',') ? "\"" : ""),//correctly formats the quotations in the artist name
			record.album,
			record.song,
			record.genre,
			record.duration.minutes,
			record.duration.seconds,
			record.times_played,
			record.rating);

		current = current->pNext;//next node
	}
}

int time_out(int sec)
{
	clock_t end;
	end = clock() + sec * CLOCKS_PER_SEC;
	while (clock() < end) {}
	return 1;
}

void edit_record(FILE* file, Node* pHead, int rate)////STILL NEED TO ALLOW USERS TO SEARCH FOR ARTIST WITH A FIRST AND LAST NAME
{



	int c;
	while ((c = getchar()) != '\n' && c != EOF);//i was having issues with having fgets process user input so this line clears the input buffer

	///first ask the user for the artist
	char artistname[50];
	printf("Enter the name of the artist \n(if the name has quotes, don't include them when searching for names,\nalso stick to the last name, first name format\n");
	fgets(artistname, sizeof(artistname), stdin);


	size_t len = strlen(artistname);//this removes a trailing newline char if there is one
	if (len > 0 && artistname[len - 1] == '\n')
	{
		artistname[len - 1] = '\0';
	}


	printf("\nSONGS BY %s:\n\n", artistname);






	char formatted_artist[52];
	sprintf(formatted_artist, "\"%s\"", artistname);

	Node* current = pHead;
	int found = 0;

	bool change_made = false;
	while (!change_made)//this loop will run until a change has been made to the record
	{
		while (current != NULL)
		{
			Record record = current->data;

			if (strcmp(record.artist, artistname) == 0 || strcmp(record.artist, formatted_artist) == 0)
			{
				{

					printf("%s%s%s,%s,%s,%s,%d:%02d,%d,%d\n",
						(strchr(record.artist, ',') ? "\"" : ""), record.artist,
						(strchr(record.artist, ',') ? "\"" : ""),//correctly formats the quotations in the artist name
						record.album,
						record.song,
						record.genre,
						record.duration.minutes,
						record.duration.seconds,
						record.times_played,
						record.rating);

				}


				found++;
			}


			current = current->pNext;//next node


		}


		if (found == 0)
		{
			printf("No songs found by %s\n", artistname);
			return;
		}




		///the rate paramter is set to 1 if this function is being used for the rate option
		if (rate == 1)/////If this function is being used as a way to rate a record the program enters this block and then exits the function once the user rates a track
		{
			char song_to_edit[50];
			printf("\nWhat %s song would you like to rate?\n", artistname);
			fgets(song_to_edit, sizeof(song_to_edit), stdin);

			printf("THIS song will be edited: %s", song_to_edit);


			//////////
			len = strlen(song_to_edit);////ensures that the user input will be valid
			if (len > 0 && song_to_edit[len - 1] == '\n')
			{
				song_to_edit[len - 1] = '\0';
			}
			/////////



			///////FIND SONG
			bool songfound = false;
			current = pHead;

			while (current != NULL)
			{
				Record record = current->data;

				if (strcmp(current->data.song, song_to_edit) == 0)
				{
					printf("\nsong found! WHICH IS %s\n\n", current->data.song);
					songfound = true;
					break;
				}


				current = current->pNext;//next node

			}
			/////////









			if (current->data.song != NULL)
			{
				printf("This is the value stored within record.song: %s\n", current->data.song);
			}


			int r;

			clear_the_screen();


			printf("what would you like to change the rating to?\n");
			scanf("%d", &r);

			printf("Rating updated to %d\n\n", r);

			current->data.rating = r;

















			change_made = true;



			current = current->pNext;//next node


			return;
		}
		//////end of rate






		char song_to_edit[50];
		printf("\nWhat %s song would you like to make a change to?\n", artistname);
		fgets(song_to_edit, sizeof(song_to_edit), stdin);



		len = strlen(song_to_edit);////ensures that the user input will be valid
		if (len > 0 && song_to_edit[len - 1] == '\n')
		{
			song_to_edit[len - 1] = '\0';
		}


		bool songfound = false;



		current = pHead;

		while (current != NULL)
		{
			Record record = current->data;

			if (strcmp(record.song, song_to_edit) == 0)
			{
				printf("\nsong found!\n\n");
				songfound = true;
				break;
			}


			current = current->pNext;//next node

		}




		current = pHead;

		while (current != NULL)
		{

			Record record = current->data;


			if (strcmp(record.song, song_to_edit) == 0)
			{

				int record_to_change = 0;
				printf("Which part of the record would you like to edit?\nArtist name (1)\nAlbum name (2)\nSong name (3)\nGenre (4)\nDuration(minutes) (5)\nDuration(seconds) (6)\nTimes played (7)\nRating (8)\n");
				scanf("%d", &record_to_change);


				char newly_edited[50];
				int newly_edited_int = 0;


				switch (record_to_change)
				{
				case 1:

					printf("what would you like to change the artist name to?");
					scanf("%s", newly_edited);


					strcpy(record.artist, newly_edited);
					printf("\n\nCHANGED %s", record.artist);




					break;
				case 2:
					printf("what would you like to change the album title to?");
					scanf("%s", newly_edited);


					strcpy(record.album, newly_edited);
					printf("\n\nCHANGED %s", record.album);
					break;
				case 3:
					printf("what would you like to change the song title to?");
					scanf("%s", newly_edited);


					strcpy(record.song, newly_edited);
					printf("\n\nCHANGED %s", record.song);
					break;
				case 4:
					printf("what would you like to change the genre to?");
					scanf("%s", newly_edited);


					strcpy(record.genre, newly_edited);
					printf("\n\nCHANGED %s", record.genre);
					break;
				case 5:
					printf("what would you like to change the duration(minutes) to?");
					scanf("%d", &newly_edited_int);


					record.duration.minutes = newly_edited_int;
					printf("\n\nCHANGED to %d\n", record.duration.minutes);

					printf("DURATION IN MINUTES: %d", record.duration.minutes);
					break;
				case 6:
					printf("what would you like to change the duration(seconds) to?");
					scanf("%d", &newly_edited_int);


					record.duration.seconds = newly_edited_int;
					printf("\n\nCHANGED to %d\n", record.duration.seconds);
					break;
				case 7:
					printf("what would you like to change the times played to?");
					scanf("%d", &newly_edited_int);


					record.times_played = newly_edited_int;
					printf("\n\nCHANGED to %d\n", record.times_played);
					break;
				case 8:
					printf("what would you like to change the rating to?");
					scanf("%d", &newly_edited_int);


					record.rating = newly_edited_int;
					printf("\n\nCHANGED to %d\n", record.rating);
					break;
				default:
					printf("\n\nInvalid input");
				}

				current->data = record;

				change_made = true;

				//printf("%s%s%s,%s,%s,%s,%d:%02d,%d,%d\n",
				//	(strchr(record.artist, ',') ? "\"" : ""), record.artist,
				//	(strchr(record.artist, ',') ? "\"" : ""),//correctly formats the quotations in the artist name
				//	record.album,
				//	record.song,
				//	record.genre,
				//	record.duration.minutes,
				//	record.duration.seconds,
				//	record.times_played,
				//	record.rating);




			}


			current = current->pNext;//next node


		}
	}



}

int random_num_generator(Node* pHead)
{
	srand(time(NULL));
	int r = rand() % sizeof(pHead) + 1;
	return r;
}
