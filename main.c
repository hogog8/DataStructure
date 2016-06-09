#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int print_menu();
void read_data_file();

typedef struct user{
	char ID[12];
	char regDay[40];
	char name[20];
}User;

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
	puts("\t4. Find users who tweeted a word (e.g., ¡¯¿¬¼¼´ë¡¯)");
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
	char userID[12];
	char dayInfo[40];
	char userName[20];
	int user_num=0;
	char temp;
	char userData;

	//fscanf(fp, "%s %s %s", userID, dayInfo, userName);
	while(!feof(fp)){
		user = (User*)malloc(sizeof(User));
		
		fgets(user->ID, 12, fp);
		fgets(user->regDay, 40, fp);
		fgets(user->name, 20, fp);
		temp = fgetc(fp);

		printf("ID : %s", user->ID);
		printf("Day : %s", user->regDay);
		printf("Name : %s", user->name);
		free(user);
		user_num++;	
	}
	printf("total user num : %d\n",user_num);

}