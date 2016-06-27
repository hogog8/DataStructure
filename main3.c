#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
//#include "BST.h"
#include "term.h"


int total_user_num=0;


void read_data_files(userList* userList, tweetList* wordList);


int main()
{

    int menu=0;

	userList* user_list = NULL;
	tweetList* wordList = (tweetList*)malloc(sizeof(tweetList));

	if(user_list==NULL)
		printf("제발제발");


	while(1){

		puts("\t***************\t Menu \t*****************");
		puts("\t0. Read data files");
		puts("\t1. display statistics");
		puts("\t2. Top 5 most tweeted words");
		puts("\t3. Top 5 most tweeted users");
		puts("\t4. Find users who tweeted a word (e.g., ’연세대’)");
		puts("\t5. Find all people who are friends of the above users");
		puts("\t6. Delete all mentions of a word");
		puts("\t7. Delete all users who mentioned a word");
		puts("\t8. Find strongly connected components");
		puts("\t9. Find shortest path from a given user");
		printf("\t99. Quit\n");
		puts("\t********************************************");
		printf("Select menu : ");

		scanf("%d", &menu);

		switch(menu){
	
		case 0:
			read_data_files(user_list, wordList);
			break;

		case 99:
			printf("Quit this program.\n");
			return;

		default:
			puts("Wrong Input!\n. Select menu again.");
		}
	}

	return 0;
}


void read_data_files(userList* user_list, tweetList* wordList){

	FILE* fp;
	user* user;
	char userID[12];
	char userName[20];
	char temp[40];
	
	fp = fopen("user.txt", "r");
	
	while( fgets(userID, 12, fp)!=NULL){
		
		fgets(temp, 40, fp);
		fgets(userName, 20, fp);
		fgetc(fp);


		printf("\n\nuserID : %s", userID);
		printf("userName : %s", userName);

		user = userInit(userID, userName);
		printf("user : %s", user->ID);
	 
		user_list = userInsert(user_list, user);
		total_user_num++;

	}

	PrintInorder(user_list);
	printf("\n\n");
	PrintPreorder(user_list);

	/*
	fgets(userID, 12, fp);
	fgets(temp, 40, fp);
	fgets(userName,20, fp);
	fgetc(fp);
	printf("%s%s%s", userID, temp, userName);

	user = userInit(userID, userName);

	printf("user\n");
	printf("%s%s", user->ID, user->name);

	user_list = userInsert(user_list, user);

	printf("user_list->user\n %s%s\n", user_list->user->ID, user_list->user->name);
	//free(user);
	
	fgets(userID, 12, fp);
	fgets(temp, 40, fp);
	fgets(userName,20, fp);
	fgetc(fp);
	//printf("%s%s%s", userID, temp, userName);

	user = userInit(userID, userName);
	//printf("user\n");
	//printf("%s%s", user->ID, user->name);

	user_list = userInsert(user_list, user);
	
	printf("user_list->user\n%s%s\n", user_list->right->user->ID, user_list->right->user->name);

	fgets(userID, 12, fp);
	fgets(temp, 40, fp);
	fgets(userName,20, fp);
	fgetc(fp);
	printf("%s%s%s", userID, temp, userName);

	user = userInit(userID, userName);

	user_list = userInsert(user_list, user);
	*/
	

}

