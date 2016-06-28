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

tweetList* find_most_word(tweetList* wordList);
userList* find_most_user(userList* user_list);

int main() 
{

    int menu=0;

	userList* user_list = NULL;
	tweetList* wordList = NULL;
	
	tweetList* temp_tweet=NULL;

	while(1){

		puts("\t***************\t Menu \t*****************");
		puts("\t0. Read data files");
		puts("\t1. display statistics");
		puts("\t2. Top 5 most tweeted words");
		puts("\t3. Top 5 most tweeted users");
		puts("\t4. Find users who tweeted a word (e.g., �������롯)");
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
			printf("Read data done!\n\n");
			break;
		
		
		case 1:
		
			display_stats(user_list, wordList);
			break;

		case 2:
			find_most_word(wordList);

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
		//����� ������ Ʈ������Ʈ

		wordList = tweetInsert(wordList, tempTweet);
		//��� Ʈ������Ʈ.
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


	fp = fopen("user.txt", "r");
	

	
	while( fgets(userID, 12, fp)!=NULL){
		
		fgets(temp, 40, fp);
		fgets(userName, 20, fp);
		fgetc(fp);


		//printf("\n\nuserID : %s", userID);
		//printf("userName : %s", userName);

		user1 = userInit(userID, userName);
		//printf("user : %s", user1->ID);
	 
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
		user2->tweet_num++;
		//����� ������ Ʈ������Ʈ

		wordList = tweetInsert(wordList, tempTweet);
		//��� Ʈ������Ʈ.
		total_tweet_num++;
	}
	return wordList;
}



void display_stats(userList* user_list, tweetList* wordList){

	int min_friend;
	int max_friend;
	int min_tweet;
	int max_tweet;


	min_friend = user_list->user->friend_num;
	max_friend = user_list->user->friend_num;
	//�񱳰��� ���� �ʱ�ȭ.

	min_friend = find_min(user_list, min_friend);
	max_friend = find_max(user_list, max_friend);

	
	min_tweet = user_list->user->tweet_num;
	max_tweet = user_list->user->tweet_num;
	min_tweet = find_min_user(user_list, min_tweet);
	max_tweet = find_max_user(user_list, max_tweet);


	
	printf("average number of friends : %.2lf\n", (float)total_friendship_num / total_user_num);
	printf("minimum friends : %d\n", min_friend);
	printf("maximum friends : %d\n", max_friend);

	printf("average tweet per user : %.2lf\n", (float)total_tweet_num/total_user_num);
	printf("min tweets : %d\n", min_tweet);
	printf("max tweets : %d\n", max_tweet);
	
}
