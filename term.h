//#include "BST.h"
#include <string.h>
#include <stdlib.h>


typedef struct user{
	char ID[12];
	char name[20];
	int friend_num;
	int tweet_num;
	struct tweetList* tweetList;
	struct userList* friends;
}user;

typedef struct tweetList{
	char tweet[150];
	struct tweetList *left;
	struct tweetList *right;
	int count;
}tweetList;

typedef struct userList{
	struct user* user;
	struct userList* left;
	struct userList* right;
}userList;


//BST의 insert 함수를 userList 형태로 변환.
userList* userInsert(userList *list, user* user)
{

	    if(list==NULL)
        {

			userList* temp;
			temp = (userList*)malloc(sizeof(userList));
			//printf("list is null!\n");

			temp->user=user;
			temp->left=NULL;
			temp->right=NULL;
			return temp;
        }

        if( strcmp(user->ID,list->user->ID) >= 0)
        {
			//printf("insert right\n");
            list->right = userInsert(list->right, user);
        }
        else if( strcmp(user->ID,list->user->ID) < 0)
        {
			//printf("insert left\n");
                list->left = userInsert(list->left, user);
        }
        /* Else there is nothing to do as the data is already in the tree. */
        return list;
}

userList* listInit(userList* list){

	list->user=NULL;
	list->left=NULL;
	list->right=NULL;
	return list;
}

//userID와 userName을 입력받아 user를 선언함.
user* userInit(char ID[], char name[]){

	user* temp = (user*)malloc(sizeof(user));
	strcpy(temp->ID, ID);
	strcpy(temp->name, name);
	temp->friend_num=0;
	temp->tweet_num=0;
	temp->friends=NULL;
	temp->tweetList=NULL;

	return temp;
}



void PrintInorder(userList* list){
        if(list==NULL)
        {
                return;
        }
        PrintInorder(list->left);
        printf("%s ",list->user->ID);
        PrintInorder(list->right);
}

void PrintPreorder(userList* list)
{
        if(list==NULL)
        {
                return;
        }
        printf("%s ",list->user->ID);
        PrintPreorder(list->left);
        PrintPreorder(list->right);
}


user* FindUser(userList* list, char ID[])
{
	//printf("list : %s", list->user->ID);
	//printf("ID : %s", ID);
        if(list->user==NULL)
        {
                /* Element is not found */
                return NULL;
        }

		
        if( strcmp(ID, list->user->ID) > 0 )
        {
                /* Search in the right sub tree. */
                return FindUser(list->right,ID);
        }
		
        else if( strcmp(ID, list->user->ID) < 0)
        {
                /* Search in the left sub tree. */
                return FindUser(list->left,ID);
        }
        else
        {

                /* Element Found */
                return list->user;
        }
}


void add_friendship(user* user1, user* user2){


	//if(user1->friends==NULL)
	//	printf("friends is null!\n");

	user1->friends = userInsert(user1->friends, user2);
	user1->friend_num++;


	//printf("user1->friends : %s", user1->friends->user->ID);
	//printf("friendship added!\n");
}

tweetList* tweetInsert(tweetList *list, char tweet[])
{
	//printf("Inserting tweet.\n");
	    if(list==NULL)
        {

			tweetList* temp;
			temp = (tweetList*)malloc(sizeof(tweetList));
			//printf("list is null!\n");

			strcpy(temp->tweet, tweet);
			temp->left=NULL;
			temp->right=NULL;
			temp->count=1;
			return temp;
        }

        if( strcmp(tweet , list->tweet) > 0)
        {
			//printf("insert right\n");
            list->right = tweetInsert(list->right, tweet);
        }
        else if( strcmp(tweet,list->tweet) < 0)
        {
			//printf("insert left\n");
                list->left = tweetInsert(list->left, tweet);
        }

		//strcmp==0, 즉 트윗리스트의 단어와 트윗이 같은 경우면 카운트만 1 증가시키면 된다.
		else{
			list->count++;
		}
		
        /* Else there is nothing to do as the data is already in the tree. */
        return list;
}



int find_min(userList* list, int min){
	
	
	if(list!=NULL){
		min = find_min(list->left, min);
		
		//printf("user : %s", list->user->ID);
		//printf("friends num : %d\n", list->user->friend_num);
		if(list->user->friend_num < min)
			min = list->user->friend_num;

		min = find_min(list->right, min);
	}
	return min;

}

int find_max(userList* list, int max){
	if(list!=NULL){
		max = find_max(list->left, max);

		if(list->user->friend_num > max)
			max = list->user->friend_num;

		max = find_max(list->right, max);
	}
	return max;
}

int find_min_user(userList* list, int min){
	
	if(list!=NULL){

	min = find_min_user(list->left, min);
		

	//printf("tweet num : %d\n", list->user->tweet_num);
	
	if(list->user->tweet_num < min)
		min = list->user->tweet_num;

	min = find_min_user(list->right, min);
	}
	return min;
}

int find_max_user(userList* list, int max){
	
	if(list!=NULL){

	max = find_max_user(list->left, max);
		

	//printf("tweet num : %d\n", list->user->tweet_num);
	
	if(list->user->tweet_num > max)
		max = list->user->tweet_num;

	max = find_max_user(list->right, max);
	}
	return max;
}