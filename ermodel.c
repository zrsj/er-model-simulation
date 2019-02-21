/*
ProgName: ER Model Software
Author:  zrsj
Purpose: Creates an abstract ER model in software
Todo:
	*investigate solutions to buffer overflows
	*variable clearing for deletion/replacement of old/incorrect data
	*clean up identifiers
*/
#include "relmod.h"

int main(){
	Model base;
	Rel* a = malloc(sizeof(*a)); //dynamically allocate so that no random address assignment occurs
	if(!a){
		printf("ERROR: FAILED TO ALLOCATE MEMORY. EXITING PROGRAM\n");
		return -1;
	}
	Rel* adel = a; //Rel* a must be dynamically allocated to function, adel remembers its original address and frees it later
	init_modarr(&base);
	init_relarr(a);
	char rname[MAX_RELNM_SIZE+1];
	char jname[MAX_RELNM_SIZE*2];
	int t = 0;
	while(t != -1){
		printf("\nCURRENT MODEL: base\n");
		printf("CURRENT RELATION: %s\n", a->rel_nm);
		printf("\nWhat would you like to do?\n(1)Append relation to model\n(2)Append attribute to current relation\n(3)Print attributes in relation");
		printf("\n(4)Print relations in model\n(5)Select relation to modify\n(6)Specify a relationship\n(7)Print relationships");
		printf("\n(8)Specify primary key for current relation\n(9)Specify candidate key for current relation\n(-1)Quit\n");
		scanf("%d", &t);
		printf("You entered: %d\n", t);
		switch(t){
			case 1:
				printf("What is this relation's name? [MAX NAME LENGTH: 25 CHARS]\n");
				scanf("%s", rname);
				model_pushrel(&base, adel, rname); //adel will always point to a clean, initalised relation
				a = &base.rel_arr[matchnm(base, rname)];
				strcpy(a->rel_nm, rname);
				printf("Created new relation for base model!\n");
				break;
			case 2:
				if(rleft(a) > 0){
					printf("Attribute name? [MAX NAME LENGTH: 25 CHARS]\n");
					scanf("%s", rname);
					rel_pushnm(a, rname);
					break;
				}
				printf("No more space left...\n");
				break;
			case 3:
				printr(*a);
				break;
			case 4:
				printm(base);
				break;
			case 5:
				printf("Which relation? Enter a number corresponding to its position on the list:\n");
				printm(base);
				scanf("%d", &t);
				if(t < 1 || t > MAX_RELNM_SIZE) break;
				a = &base.rel_arr[(t - 1)];
				printf("Selected relation %d!\n", t);
				break;
			case 6:
				printf("Please enter the relationship you wish to specify: [MAX RELATION NAME LENGTH: 50 CHARS]\n");
				scanf(" %[^\n]s", jname);
				joinspec(&base, jname);
				printf("Relationship %s has been specified!\n", jname);
				break;
			case 7:
				printj(base);
				break;
			case 8:
				printf("Which attribute is a primary key? Enter a number corresponding to its position in the relation:\n");
				printr(*a);
				scanf("%d", &t);
				strcat(a->attr_nms[(t - 1)], " {PK}");
				printf("Specified primary key!\n");
				break;
			case 9:
				printf("Which of these attributes is a candidate key? Enter a number corresponding to its position in the relation:\n");
				printr(*a);
				scanf("%d", &t);
				if(t < 1 || t > MAX_RELNM_SIZE) break;
				strcat(a->attr_nms[(t - 1)], " {AK}");
				printf("Specifed candidate key!\n");
				break;
			case -1:
				printf("Now exiting...\n");
				break;
			default:
				printf("INVALID OPTION\n");
				break;
		}
	}
	free(adel);
	adel = NULL;
	printf("The program has finished.\n");
	return 0;
}