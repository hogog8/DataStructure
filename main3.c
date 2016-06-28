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

	user* user1;
	userList* root;

	//user.txt
	char userID[12];
	char userName[20];
	char temp[40];

	
	//friend.txt
	user* user2;
	user* user3;
	char friendID[12];



	fp = fopen("user.txt", "r");
	

	
	while( fgets(userID, 12, fp)!=NULL){
		
		fgets(temp, 40, fp);
		fgets(userName, 20, fp);
		fgetc(fp);


		printf("\n\nuserID : %s", userID);
		printf("userName : %s", userName);

		user1 = userInit(userID, userName);
		printf("user : %s", user1->ID);
	 
		user_list = userInsert(user_list, user1);
		total_user_num++;

	}
	fclose(fp);

	PrintInorder(user_list);
	



	//read friend.txt//
	fp=fopen("friend.txt", "r");


	/*
	root = user_list;
	while(fgets(userID, 12, fp) !=NULL){

		fgets(friendID, 12, fp);
		fgetc(fp);

		printf("userID : %s", userID);
		printf("friendID : %s", friendID);

		user2 = FindUser(user_list, userID);
		user3 = FindUser(user_list, userID);

		add_friendship(user2, user3);
		
	}
	
	
	user1 = user_list->user;
	printf("user : %s", user_list->user);

	printf("friend : %s", user1->friends);
	printf("%s%s%s", user1->friends->right->user->ID, user1->friends->right->right->user->ID, user1->friends->right->right->right->user->ID);
	*/



	
	
	fgets(userID, 12, fp);
	fgets(friendID, 12, fp);
	fgetc(fp);
	printf("userid : %s", userID);
	printf("friendid : %s", friendID);

	//user_list=root;
	//user2 = (user*)malloc(sizeof(user));

	user2 = FindUser(user_list, userID);
	//user_list=root;
	user3 = FindUser(user_list, friendID);
	printf("user2 : %s", user2->ID);
	printf("user2 : %s", user2->name);
	printf("user3 : %s", user3->ID);
	printf("user3 : %s", user3->name);

	add_friendship(user2, user3);


	fgets(userID, 12, fp);
	fgets(friendID, 12, fp);
	fgetc(fp);

	user3 = FindUser(user_list, friendID);

	printf("user3 : %s", user3->ID);
	add_friendship(user2, user3);

	
	fgets(userID, 12, fp);
	fgets(friendID, 12, fp);
	fgetc(fp);

	user3 = FindUser(user_list, friendID);
	printf("user3 : %s", user3->ID);
	add_friendship(user2, user3);

	printf("user2 friend.\n");
	printf("%s", user2->friends->user->ID);
	printf("%s", user2->friends->right->user->ID);
	printf("%s", user2->friends->right->right->user->ID);
	
	


}

