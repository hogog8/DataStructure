//#include "BST.h"
#include <string.h>
#include <stdlib.h>


typedef struct user{
	char ID[12];
	char name[20];
	int friend_num;
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
	printf("222\n");
	strcpy(temp->ID, ID);
	strcpy(temp->name, name);
	temp->friend_num=0;
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