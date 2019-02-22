#ifndef RELMOD_C
#define RELMOD_C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_RELNM_SIZE 25
#define MAX_REL_NO 8
#define LENARR(x) (sizeof(x)/sizeof(x[0]))
/*STRUCT SECTION*/
typedef struct{
	char rel_nm[MAX_RELNM_SIZE+1];
	char attr_nms[MAX_REL_NO][MAX_RELNM_SIZE+1];
	char c_keys[MAX_REL_NO][MAX_RELNM_SIZE+1];
	char p_key[MAX_RELNM_SIZE+1];
} Rel;

typedef struct{
	Rel rel_arr[MAX_REL_NO];
	char rel_nms[MAX_REL_NO][MAX_RELNM_SIZE+1];
	char join_list[MAX_REL_NO][MAX_RELNM_SIZE*2];
} Model;
/*CONSTRUCTOR SECTION*/
void init_relarr(Rel* r){
	for(int i = 0; i < MAX_REL_NO; i++){
		strcpy(r->attr_nms[i], "-No Name-");
		strcpy(r->c_keys[i], "-");
	}
	strcpy(r->rel_nm, "-");
	strcpy(r->p_key, "-");
}

void init_modarr(Model* m){
	for(int i = 0; i < MAX_REL_NO; i++){
		strcpy(m->rel_nms[i], "-No Name-");
	}
	for(int i = 0; i < LENARR(m->join_list); i++){
		strcpy(m->join_list[i], "-No Join-");
	}
}

/*PRINTING FUNCTIONS*/
void printr(Rel r){
	printf("%s(", r.rel_nm);
	for(int i = 0; i < MAX_REL_NO; i++){
		if(strcmp(r.attr_nms[i], "-No Name-") == 0){continue;}
		else if(strcmp(r.attr_nms[i+1], "-No Name-") == 0 || i+1 == MAX_REL_NO){
			printf("%s", r.attr_nms[i]);
			break;
		}
		printf("%s, ", r.attr_nms[i]);
	}
	printf(")\n");
}

void printm(Model m){
	for(int i = 0; i < MAX_REL_NO; i++){
		//if(strcmp(m.rel_nms[i], "-No Name-") == 0){continue;}
		//printf("%s\n", m.rel_nms[i]);
		printf("%s\n", (strcmp(m.rel_nms[i], "-No Name-") == 0)?"-":m.rel_nms[i]);
	}
}

void fprintm(Model* m, Rel* r, FILE* fp){
	fprintf(fp, "MODEL: base\nRELATIONS:\n");
	for(int i = 0; i < MAX_REL_NO; i++){
		if(strcmp(m->rel_nms[i], "-No Name-") == 0) continue;
		r = &m->rel_arr[i];
		fprintf(fp, "%s(", r->rel_nm);
		for(int j = 0; j < MAX_REL_NO; j++){
			if(strcmp(r->attr_nms[j], "-No Name-") == 0){continue;}
			else if(strcmp(r->attr_nms[j+1], "-No Name-") == 0 || j+1 == MAX_REL_NO){
				fprintf(fp, "%s", r->attr_nms[j]);
				break;
			}
			fprintf(fp, "%s, ", r->attr_nms[j]);
		}
		fprintf(fp, ")\n");
	}
}

void printj(Model m){
	for(int i = 0; i < MAX_REL_NO; i++){
		printf("%s\n", (strcmp(m.join_list[i], "-No Join-") == 0)?"-":m.join_list[i]);
	}
}
/*ARRAY PUSHING FUNCTIONS*/
void rel_pushnm(Rel* r, char relnm[]){
	for(int i = 0; i < MAX_REL_NO; i++){
		if(strcmp(r->attr_nms[i], "-No Name-") != 0) continue;
		else{
			strcpy(r->attr_nms[i], relnm);
			break;
		}
	}
}

void model_pushrel(Model* m, Rel* r, char relnm[]){
	for(int i = 0; i < MAX_REL_NO; i++){
		if(strcmp(m->rel_nms[i], "-No Name-") == 0){
			m->rel_arr[i] = *r;
			strcpy(m->rel_nms[i], relnm);
			break;
		}
		else continue;
	}
}
/*SPECIFICATION FUNCTIONS*/
void joinspec(Model* m, char join_prop[]){
	for(int i = 0; i < LENARR(m->join_list); i++){
		if(strcmp(m->join_list[i], "-No Join-")) continue;
		else{
			strcpy(m->join_list[i], join_prop);
			break;
		}
	}
}
/*MISCELLANEOUS FUNCTIONS*/
int matchnm(Model m, char relnm[]){
	for(int i = 0; i < MAX_REL_NO; i++){
		if(strcmp(m.rel_nms[i], relnm) == 0){return i;}
		else continue;
	}
	printf("No matches found.\n");
}

int rleft(Rel* r){
	int count = 0;
	for(int i = 0; i < MAX_REL_NO; i++){
		if(strcmp(r->attr_nms[i], "-No Name-") == 0)
			count++;
	}
	return count;
}
#endif