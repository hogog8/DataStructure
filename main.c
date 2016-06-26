#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int count=0;
int user_num=0;
int friendship_num=0;
int total_tweet_num=0;

typedef struct User{
	char ID[12];
	char regDay[40];
	char name[20];
	struct List* friends;
	int friends_num;
	struct tweetList* tweetList;
}User;


void user_init(User* user){
	strcpy(user->ID, "0");
	strcpy(user->name,"(none)");
	strcpy(user->regDay,"(none)");
	user->friends=NULL;
	user->tweetList =NULL;
	user->friends_num=0;
}

typedef struct List{
	User* user;
	struct List* next;
}List;

typedef struct tweetList{
	char tweet[20];
	struct tweetList* next;
	int count;
}tweetList;



void list_init(List* self){
	//self->user.ID=0;
	self->next=NULL;
}

int print_menu();
void read_data_file();
void test();
void add_frinedship(User* user1, User* user2);
struct User* findUserByID(List* list, char newID[]);

int main(){

	int menu=0;
	
	while(menu!=99){
		menu = print_menu();
	}
	
	return 0;
}


int print_menu(){

	int option=0;

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

	scanf("%d", &option);

	switch(option){
	
	case 0:
		read_data_file();
		break;
	default:
		puts("Wrong Input!\n. Select menu again.");
	}

	return option;
}

void read_data_file(){
	
	FILE* fp = fopen("user.txt", "r");
	User* user;
	List* user_list;
	List* temp_list;
	List* root;
	char userID[12];
	char dayInfo[40];
	char userName[20];
	//int user_num=0; make it global variable
	
	char temp[12];
	char temp2[12];
	char userData;

	//friend.txt
	char friendID[12];
	User* user_find;
	User* user_find2;
	User* aaa = (User*)malloc(sizeof(User));
	
	//int friendship_num=0; make it global variable
	
	//

	//tweet.txt
	char tweet_temp[30];
	int tweetcmp=1;

	tweetList* word_list = (tweetList*)malloc(sizeof(tweetList));
	tweetList* temp_tweet_list = (tweetList*)malloc(sizeof(tweetList));
	tweetList* root_tweet_list = (tweetList*)malloc(sizeof(tweetList));
	tweetList* temp_tweet_list2 = (tweetList*)malloc(sizeof(tweetList));
	
	
	//int total_tweet_num=0;// make it global variable

	user_list = (List*)malloc(sizeof(List));
	user = (User*)malloc(sizeof(User));
	list_init(user_list);
	user_init(user);

	user_list->user = user;
	//list initialize.
	root = (List*)malloc(sizeof(List));
	list_init(root);


	//printf("%s, %s, %s \n", user->ID, user->name, user->regDay);
	
	
	
	while(fgets(temp,12,fp) !=NULL){

		user = (User*)malloc(sizeof(User));
		user_init(user);
		temp_list = (List*)malloc(sizeof(List));
		/*
		if((temp=fgetc(fp))==EOF)
		{
			printf("End of file!\n");
			break;
		}
		*/

		//temp2[0]=temp;
		//fgets(user->ID, 12, fp);
		//sprintf(user->ID, "%c%s", temp, user->ID);
		//strcat(temp2, user->ID);
		//strcpy(user->ID, temp2);

		strcpy(user->ID, temp);
		fgets(user->regDay, 40, fp);
		fgets(user->name, 20, fp);
		

		printf("ID : %s", user->ID);
		printf("Day : %s", user->regDay);
		printf("Name : %s", user->name);

		temp_list->user = user;
		temp_list->next = user_list;
		user_list = temp_list;
		
		if(fgetc(fp) == EOF){
			printf("break\n");
			break;
		}
		//user_list->next = user_list;
		//printf("aaaaaaaaID : %s\n", user_list->user->ID);
		//free(user);
		
		
		
		user_num++;	
	}
	fclose(fp);

	root = user_list;
	//store root node.
	

	///* print all user list
	
	while(user_list->next!=NULL){
		printf("ID : %s", user_list->user->ID);
		user_list = user_list->next;
	}
	
	//printf("total user num : %d\n",user_num);
	printf("\n---Read List---\n");


	/*
	while(user_list!=NULL){
		printf("ID : %s", user_list->user->ID);
		user_list->next = user_list;
	}
	*/


	/*
	printf("\n---friends test---\n");
	test();
	*/



	/*
	printf("\n----friend test----\n");
	fgets(userID, 12 ,fp);
	printf("%s", userID);
	//fgets(userID, 12, fp);
	//printf("%s", userID);

	user_find = findUserByID(user_list, userID);
	//find user, then find friend of him.

	printf("find user : %s\n", user_find->ID);	
	user_list = root;
	fgets(userID, 12 ,fp);
	printf("find user2 : %s\n", userID);
	user_find2 = findUserByID(user_list,userID);
	
	add_frinedship(user_find, user_find2);
	
	printf("find friend..\n");
	printf("user 1 : %sfriend : %s\n", user_find->ID, user_find->friends->user->ID);

	user_init(aaa);
	strcpy(aaa->ID, "123123");

	add_frinedship(user_find, aaa);
	printf("kkkkk\n");
	printf("user1 : %s", user_find->ID);
	printf("friend : %s\n",  user_find->friends->user->ID);

	printf("friend2 : %s\n",  user_find->friends->next->user->ID);
	printf("... %s\n", user_find->friends->next->user->name);

	*/

	//read friend.txt
	
	fp = fopen("friend.txt", "r");

	while(fgets(temp, 12, fp)!=NULL){
		
		strcpy(userID, temp);
		user_list = root;
		user_find = findUserByID(user_list, userID);
		//find user, then find friend of him.
		fgets(friendID, 12, fp);
		user_list = root;
		user_find2 = findUserByID(user_list, friendID);
		
		add_frinedship(user_find, user_find2);
		friendship_num++;
		//total friendship num

		user_find->friends_num++;
		//each user's friends num
		fgetc(fp);
	}

	printf("friend read end!\n");
	printf("friend test!\n");

	user_list=root;
	while(user_list->user->friends!=NULL){
		printf("friends of %s", user_list->user->name);
		printf("ID : %s", user_list->user->friends->user->ID);
		printf("name : %s\n", user_list->user->friends->user->name);
		
		user_list->user->friends = user_list->user->friends->next;
	}





	//read tweet.txt//
	fclose(fp);
	fp = fopen("word.txt", "r");



	word_list->next=NULL;
	word_list->count=0;
	//word_list 초기화?
	root_tweet_list = word_list;
	while(fgets(user->ID, 12, fp)!=NULL){

		temp_tweet_list = (tweetList*)malloc(sizeof(tweetList));
		fgets(user->regDay,40,fp);
		fgets(tweet_temp, 30, fp);
		printf("tweet_temp : %s", tweet_temp);
		//트윗을 읽음.
		fgetc(fp);

		//temp_tweet_list
		strcpy(temp_tweet_list->tweet, tweet_temp);
		temp_tweet_list->next=NULL;
		temp_tweet_list->count=0;
		
		word_list = root_tweet_list;
		
		
		//word_list를 처음부터 끝까지 검사해서 중복되는 단어가 있으면 count만 증가.
		//아니면 끝까지 검사만 해서 word_list의 마지막을 가리키기.

		while(word_list!=NULL){
			if( (tweetcmp=strcmp(word_list->tweet, tweet_temp)==0)){
				word_list->count++;
				break;
			}
			temp_tweet_list2=word_list;
			word_list = word_list->next;
		}
		//printf("tweetcmp : %d\n", tweetcmp);
		//비교를 했는데 같은 값이 나오지 않았을 경우(0이 아닌 경우), word_list에 추가.
		//근데 위의 while문에서, word_list는 이미 마지막을 가리키고 있다.
		//따라서 word_list에 바로 temp_tweet을 넣어주기만 하면 됨.
		word_list = temp_tweet_list2;

		if(!tweetcmp){
			
			word_list->next= temp_tweet_list;
			word_list->next->count++;
			word_list = word_list->next;

		}
	}

	//리스트의 저장이 끝났으면 root를 다시 불러옴.
	word_list = root_tweet_list;
	
	while(word_list->next!=NULL){
		//printf("word_list : %s", word_list->tweet);

		//if(word_list->count!=1)
		//	printf("count : %d, word : %s", word_list->count, word_list->tweet);
		word_list = word_list->next;
	}
	
/*
		temp_list->user = user;
		temp_list->next = user_list;
		user_list = temp_list;
	*/
	/*
	while(fgets(user->ID, 12, fp)!=NULL){
		
		user_list = root;
		user = findUserByID(user_list, user->ID);

		fgets(user->regDay,40, fp);
		//writed date of tweet is not important, so just read it.
		
		fgets(tweet_temp,30,fp);
		printf("tweet : %s", tweet_temp);

		//0. 우선 처음 위치를 저장해 두고.
		
		
		//1. 유저의 트윗리스트가 비어있으면 바로 트윗리스트에 추가한다.
		if(user->tweetList==NULL){
			user->tweetList = (tweetList*)malloc(sizeof(tweetList));
			strcpy(user->tweetList->tweet, tweet_temp);
			user->tweetList->count++;
			user->tweetList->next=NULL;
			printf("Null list, added complet!\n");
			continue;
		}

		//2. 비어있는게 아니면, 중복된 단어가 있는지 확인한 후
		//중복된 단어가 있으면 count만 증가, 아니면 리스트의 처음에 추가
		else{
			
			strcpy(temp_tweet_list->tweet, tweet_temp);
			temp_tweet_list->count++;
			temp_tweet_list->next = user->tweetList;
			user->tweetList = temp_tweet_list;

		}

		//printf("tweet of %s.", user->name);
		//printf("%s", user->tweetList->tweet);
		fgetc(fp);
	}

	
	printf("\ntweet test!\n");
	
	user_list=root;

	printf("user ID : %s", user_list->user->ID);
	printf("his first tweet : %s", user_list->user->tweetList->tweet);
	//printf("its count : %d", user_list->user->tweetList->count);
	printf("second tweet : %s", user_list->user->tweetList->next->tweet);
	*/




	printf("Total users : %d\n", user_num);
	printf("Total friendship record : %d\n", friendship_num);

	
	
}

void add_frinedship(User* user1, User* user2){
	

	List* temp = (List*)malloc(sizeof(List));
	List* temp2 = (List*)malloc(sizeof(List));

	
	int num=0;

	temp->user=user2;
	temp->next=NULL; 
	//initialize list 'temp'
	
	//temp2 = user1->friends;
	//root = user1->friends;
	

	/*
	if(count==1){
		if(user1->friends!=NULL)
			printf("count1, not null\n");
	}

	while(user1->friends!=NULL){
		if(count==1)
			printf("1111\n");

		user1->friends = user1->friends->next;
		num++;
	}
	
	if(user1->friends!=NULL)
		printf("friends NULL test, %s\n", user1->friends->user->ID);
	
	temp2 = user1->friends;
	temp2->next=NULL;
	user1->friends = temp;
	user1->friends->next=temp2;
	
	if(user1->friends->next!=NULL)
		printf("F2 test : %s\n", user1->friends->next->user->ID);
	*/

	if(user1->friends==NULL)
		user1->friends=temp;
	else{
		temp2 = user1->friends;
		user1->friends=temp;
		user1->friends->next=temp2;
	}
	//user1->friends=root;


	//printf("friendship added!\n");
	count++;
}

void test(){

	User* user1 = (User*)malloc(sizeof(User));
	User* user2 = (User*)malloc(sizeof(User));
	User* user3 = (User*)malloc(sizeof(User));
	List* list = (List*)malloc(sizeof(List));
	user_init(user1);
	user_init(user2);
	user_init(user3);

	if(user1->friends==NULL)
		printf("NULL!!!\n");

	printf("111\n");
	strcpy(user2->ID, "123");
	strcpy(user3->ID, "456");
	strcpy(user1->ID, "000");
	//user2->ID[0] = 2;
	//user2->ID[1] = 2;
	//user3->ID[0] = 3;

	printf("222\n");
	//user1->friends->user = user2;
	//printf("333\n");
	//user1->friends->next= NULL;
	//printf("444\n");
	list_init(list);
	list->user=user2;
	list->next=NULL;
	printf("333\n");
	user1->friends=list;
	//user1->friends->next=NULL;

	printf("user1's friend : %s\n", user1->friends->user->ID);
	
	list->user=user3;
	list->next=NULL;
	printf("444\n");
	user1->friends->next = list;
	printf("555\n");
	//user1->friends->next->next=NULL;
	printf("666\n");

	printf("friends : %s\n", user1->friends->user);

	add_frinedship(user2, user1);

	printf("user2's friends : %s\n", user2->friends->user->ID);


}

struct User* findUserByID(List* list, char newID[]){
	

	int num=0;
	//printf("newID : %s", newID);
	

	while(list->next!=NULL){
		//printf("user ID : %s", list->user->ID);
		
		if(strcmp(list->user->ID, newID)==0){
			//printf("match!\n");
			return list->user;
		}
		
		list = list->next;
		num++;
	}
	//printf("Does not match!\n");
	//printf("num : %d\n", num);
	return 0;
}
