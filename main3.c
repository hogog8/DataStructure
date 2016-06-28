#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
//#include "BST.h"
#include "term.h"


int total_user_num=0;
int total_friendship_num=0;
int total_tweet_num=0;

void read_data_files(userList* user_list, tweetList* wordList);
void display_stats(userList* userList, tweetList* wordList);
userList* read_user_info(userList* user_list);
tweetList* read_word_info(userList* user_list, tweetList* wordList);

int main() 
{

    int menu=0;

	userList* user_list = NULL;
	tweetList* wordList = NULL;
	userList* copy_user_list = (userList*)malloc(sizeof(userList));
	tweetList* copy_wordLIst = (tweetList*)malloc(sizeof(tweetList));


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
			//read_data_files(user_list, wordList);
			user_list = read_user_info(user_list);
			wordList = read_word_info(user_list, wordList);

			break;
		
		
		case 1:
		
			display_stats(user_list, wordList);
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
	

	//word.txt
	char tempTweet[150];


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

	//read friend.txt//
	fp=fopen("friend.txt", "r");
	
	root = user_list;
	while(fgets(userID, 12, fp) !=NULL){

		fgets(friendID, 12, fp);
		fgetc(fp);
		//printf("userID : %s", userID);
		//printf("friendID : %s", friendID);
		
		user2 = FindUser(user_list, userID);
		user3 = FindUser(user_list, friendID);

		add_friendship(user2, user3);
		total_friendship_num++;

	}

	//read word.txt//
	fp= fopen("word.txt","r");

	
	while(fgets(userID,12,fp)!=NULL){
		fgets(temp, 40, fp);
		fgets(tempTweet, 150, fp);
		fgetc(fp);

		user2 = FindUser(user_list, userID);
		user2->tweetList = tweetInsert(user2->tweetList, tempTweet);
		//사용자 마다의 트윗리스트

		wordList = tweetInsert(wordList, tempTweet);
		//모든 트윗리스트.
		total_tweet_num++;
	}
	
	/*read tweet test.

	printf("user2 : %s", user2->ID);
	printf("tweet : %s", user2->tweetList->tweet);
	printf("%s%s%s", user2->tweetList->right->tweet, user2->tweetList->right->right->tweet, user2->tweetList->right->right->right->tweet);
	
	printf("wordList\n");
	printf("%s%s%s", wordList->tweet, wordList->right->tweet, wordList->right->right->tweet);
	printf("%s%s%s", wordList->left->tweet, wordList->left->left->tweet , wordList->left->left->left->tweet);

	printf("\nwordList2\n");
	printf("%s%d", wordList->tweet, wordList->count);
	*/


	printf("user_list : %s\n", user_list->user->ID);

}


userList* read_user_info(userList* user_list){
	
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
	

	//word.txt
	char tempTweet[150];


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

	//read friend.txt//
	fp=fopen("friend.txt", "r");
	
	root = user_list;
	while(fgets(userID, 12, fp) !=NULL){

		fgets(friendID, 12, fp);
		fgetc(fp);
		//printf("userID : %s", userID);
		//printf("friendID : %s", friendID);
		
		user2 = FindUser(user_list, userID);
		user3 = FindUser(user_list, friendID);

		add_friendship(user2, user3);
		total_friendship_num++;

	}

	return user_list;
}

tweetList* read_word_info(userList* user_list, tweetList* wordList){
	//read word.txt//
	FILE* fp;
	char userID[12];
	char temp[40];
	char tempTweet[150];
	user* user2;

	fp= fopen("word.txt","r");

	
	while(fgets(userID,12,fp)!=NULL){
		fgets(temp, 40, fp);
		fgets(tempTweet, 150, fp);
		fgetc(fp);

		user2 = FindUser(user_list, userID);
		user2->tweetList = tweetInsert(user2->tweetList, tempTweet);
		//사용자 마다의 트윗리스트

		wordList = tweetInsert(wordList, tempTweet);
		//모든 트윗리스트.
		total_tweet_num++;
	}
	return wordList;
}






void display_stats(userList* user_list, tweetList* wordList){

	int min_friend;



	min_friend = user_list->user->friend_num;
	//비교값을 위한 초기화.

	min_friend = find_min(user_list, min_friend);


	printf("average number of friends : %d", total_friendship_num / total_user_num);
	printf("minimum friends : %d", min_friend);

}
