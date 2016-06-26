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
	char tweet[150];
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
	char tweet_temp[150];
	char userID_word[12];
	int tweetcmp=1;

	tweetList* word_list = (tweetList*)malloc(sizeof(tweetList));
	tweetList* temp_word_list = (tweetList*)malloc(sizeof(tweetList));
	tweetList* temp_word_list2 = (tweetList*)malloc(sizeof(tweetList));
	tweetList* root_word_list = (tweetList*)malloc(sizeof(tweetList));
	
	tweetList* temp_tweet_list = (tweetList*)malloc(sizeof(tweetList));
	tweetList* root_tweet_list = (tweetList*)malloc(sizeof(tweetList));
	
	User* tweet_user = (User*)malloc(sizeof(User));
	
	
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
	root_word_list = word_list;
	

	while(fgets(userID_word, 12, fp)!=NULL){
	
		temp_word_list = (tweetList*)malloc(sizeof(tweetList));
		fgets(user->regDay,40,fp);
		fgets(tweet_temp, 150, fp);
		//printf("tweet_temp : %s", tweet_temp);
		//트윗을 읽음.
		fgetc(fp);

		
		//temp_word_list
		strcpy(temp_word_list->tweet, tweet_temp);
		temp_word_list->next=NULL;
		temp_word_list->count=0;
		
		word_list = root_word_list;
		
		
		//word_list를 처음부터 끝까지 검사해서 중복되는 단어가 있으면 count만 증가.
		//아니면 끝까지 검사만 해서 word_list의 마지막을 가리키기.

		while(word_list!=NULL){
			if( (tweetcmp=strcmp(word_list->tweet, tweet_temp)==0)){
				word_list->count++;
				break;
			}
			temp_word_list2=word_list;
			word_list = word_list->next;
		}
		//printf("tweetcmp : %d\n", tweetcmp);
		//비교를 했는데 같은 값이 나오지 않았을 경우(0이 아닌 경우), word_list에 추가.
		//근데 위의 while문에서, word_list는 이미 마지막을 가리키고 있다.
		//따라서 word_list에 바로 temp_tweet을 넣어주기만 하면 됨.
		word_list = temp_word_list2;

		if(!tweetcmp){
			
			word_list->next= temp_word_list;
			word_list->next->count++;
			word_list = word_list->next;

		}
		//요기까지가 word_list에 저장을 한 것.

		
		
		//이제 각 사용자들별로 tweet_list를 정리해야 함.
		
		user_list=root;
		//printf("user : %s", userID_word);
		tweet_user = findUserByID(user_list, userID_word);
		printf("tweet_user ID : %s", tweet_user->ID);
		//printf("tweet_user name : %s", tweet_user->name);
		
		
		strcpy(temp_tweet_list->tweet, tweet_temp);
		temp_tweet_list->next=NULL;


		root_tweet_list = tweet_user->tweetList;

		if(tweet_user->tweetList==NULL){
			printf("tweetList is NULL!\n\n");
			tweet_user->tweetList = temp_tweet_list;
			tweet_user->tweetList->count=1;
			
			continue;
		}
		//if문에 안걸렸으면, 즉 tweet_user->tweetList가 null이 아니면.
		//while문을 돌리면서 tweetList의 마지막을 찾는다.
		//그전에, 같은 단어가 있으면 count만 증가시키고 break.
		

		while(tweet_user->tweetList!=NULL){
			printf("tweetList : %s", tweet_user->tweetList->tweet);
			printf("temp_tweet : %s", tweet_temp);
			if((tweetcmp=strcmp(tweet_user->tweetList->tweet, tweet_temp))==0){
				tweet_user->tweetList->count++;
				break;
			}
			//여기서도 if문에 안걸린 경우. 그냥 next를 확인
			printf("11111111 : %s", tweet_user->tweetList->tweet);
			tweet_user->tweetList = tweet_user->tweetList->next;
		}
		//while문의 끝까지 돌았는데 일치하는 tweet이 없었으면, 리스트의 마지막을 가리키고 있다.
		//거기에 temp_tweet_list를 넣어주면 됨.
		if(!tweetcmp){
			tweet_user->tweetList = temp_tweet_list;
			tweet_user->tweetList->count=1;
		}

		//while문의 끝까지 돌았기 때문에 tweetList를 다시 root에 설정.
		tweet_user->tweetList = root_tweet_list;
		
		
		/*
		//printf("user : %s", user);
		strcpy(temp_tweet_list->tweet , tweet_temp);
		temp_tweet_list->next=NULL;

		root_tweet_list = user->tweetList;
		//우선 root를 저장해두고

		//사용자를 찾고, 사용자의 tweetList를 확인
		//1. 트윗리스트가 비어있으면 바로 추가시키면 됨.
		if(user->tweetList==NULL){
			user->tweetList = (tweetList*)malloc(sizeof(tweetList));

			//user->tweetList->tweet;
			temp_tweet_list->count=1;
			temp_tweet_list->next=NULL;
			user->tweetList = temp_tweet_list;
			user->tweetList->next = NULL;

			continue;
		}

		//2. 트윗리스트가 비어있지 않으면 트윗리스트의 처음부터 끝까지 확인을 한 후, 같은 단어가 있었는지 없었는지 확인해야함.
		else{
			
			user->tweetList=root_tweet_list;

			while(user->tweetList!=NULL){
				//2.1. 같은 단어가 있었으면 카운트만 증가시키고 다음 tweet으로 넘어가기.
				if((tweetcmp = strcmp(user->tweetList->tweet, tweet_temp))==0){
					user->tweetList->count++;
					break;
				}
				//2.2 아니면 다음 단어를 확인, 다음 단어가 null이 나오면 while문을 빠져나감.
				temp_word_list2 = user->tweetList;
				user->tweetList = user->tweetList->next;
			}
		}
		//3. 위와 비슷한 방식으로 한다.
		user->tweetList = temp_word_list2;

		if(!tweetcmp){
			printf("11\n");

			
			user->tweetList ->next = temp_tweet_list;
			user->tweetList->next->count=1;
			user->tweetList = user->tweetList->next;

			//user->tweetList = user->tweetList->next;
		}
		*/

	}





	//리스트의 저장이 끝났으면 root를 다시 불러옴.
	word_list = root_word_list;
	
	//word_list 출력 테스트.
	while(word_list->next!=NULL){
		//printf("word_list : %s", word_list->tweet);
		
		//if(word_list->count!=1)
		//	printf("count : %d, word : %s", word_list->count, word_list->tweet);
		word_list = word_list->next;
	}

	//user->tweetList 출력 테스트.
	user->tweetList = root_tweet_list;
	printf("22\n");
	printf("user : %s", user->ID);
	printf("bbb: %s", user->tweetList->next->tweet);
	/*
	while(user->tweetList->next!=NULL){
		printf("tweet_list : %s", user->tweetList->tweet);
		user->tweetList = user->tweetList->next;
	}
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
			
			strcpy(temp_word_list->tweet, tweet_temp);
			temp_word_list->count++;
			temp_word_list->next = user->tweetList;
			user->tweetList = temp_word_list;

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
