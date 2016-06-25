#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>





typedef struct User{
	char ID[12];
	char regDay[40];
	char name[20];
	struct List* friends;
}User;


void user_init(User* user){
	strcpy(user->ID, "0");
	strcpy(user->name,"(none)");
	strcpy(user->regDay,"(none)");
	user->friends=NULL;
}

typedef struct List{
	User* user;
	struct List* next;
}List;



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
	int user_num=0;
	char temp[12];
	char temp2[12];
	char userData;

	//friend.txt
	char friendID[12];
	User* user_find;
	User* user_find2;
	User* aaa = (User*)malloc(sizeof(User));


	//

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


	//read friend.txt
	user_list = root;
	fp = fopen("friend.txt", "r");

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
	printf("friend : %s",  user_find->friends->user->ID);

	//printf("friend2 : %s\n",  user_find->friends->next->user->ID);
	/*
	while(!feof(fp)){
		
		fgets(userID, 12, fp);
		fgets(friendID, 12, fp);

	}
	*/
	
}

void add_frinedship(User* user1, User* user2){
	

	
	List* temp = (List*)malloc(sizeof(List));
	
	temp->user=user2;
	temp->next=NULL; 
	
	
	while(user1->friends!=NULL){
		user1->friends = user1->friends->next;
	}
	if(user1->friends!=NULL)
		printf("friends NULL test, %s\n", user1->friends->user->ID);

	user1->friends = temp;
	printf("friendship added!\n");

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
	printf("newID : %s", newID);
	

	while(list->next!=NULL){
		printf("user ID : %s", list->user->ID);
		
		if(strcmp(list->user->ID, newID)==0){
			printf("match!\n");
			return list->user;
		}
		
		list = list->next;
		num++;
	}
	printf("Does not match!\n");
	printf("num : %d\n", num);
	return 0;
}
