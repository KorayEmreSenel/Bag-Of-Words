//KORAY EMRE ÞENEL 150117037 
//"dataset" file and this file must be in same library
#include <stdio.h>
#include <dirent.h> 
#include <string.h>
#include <math.h>
#define LENGTH 57
struct wordNode { 
    char word[LENGTH]; 
    struct wordNode* next; 
    struct first  * forder;
    struct second* sorder;
    struct third* torder;
	struct dirNode *dirNODE;
}; 

typedef struct first{
	struct wordNode *node;
	struct first *next;
}first;

typedef struct second{
	struct wordNode *node;
	struct second *next;
}second;

typedef struct third{
	struct wordNode *node;
	struct third *next;
}third;

typedef struct dirNode{
	char dirName[LENGTH];
	struct dirNode* next;
	int count;
	struct txtNode* txtNODE;
	int txtCount;
}dirNode;

typedef struct txtNode{
	char txtName[LENGTH];
	struct txtNode* next;
}txtNode;

typedef struct commonWord{
	char Name[LENGTH];
	int Count;
	int txtC;
	int docC;
}commonWord;

typedef struct wordNode wordNode;
typedef struct wordNode* wordNodePtr;
typedef struct wordNode** wordNodePtrPtr;

int insert(wordNodePtrPtr header , char *word,char *dirName ,char* txtName){	
	wordNodePtr newwordNode, temp, prev;
	newwordNode=(wordNode*)malloc(sizeof(wordNode));
	strcpy(newwordNode->word, word);
	newwordNode->next = NULL;
	newwordNode->forder = NULL;
	newwordNode->sorder = NULL;
	newwordNode->torder = NULL;
	newwordNode->dirNODE = NULL;
	//LL empty.
	if(*header == NULL){
	*header=newwordNode;
	return 1;
	}
	else{
		temp=*header;
		if(temp != NULL && strcmp(temp->word,newwordNode->word) > 0 ){
			newwordNode->next = temp;
			*header = newwordNode;
		}
		temp=*header;
		while(temp != NULL && strcmp(temp->word,newwordNode->word) != 0){
			prev = temp;
			temp = temp->next; 
		if (temp!=NULL && strcmp(newwordNode->word,temp->word) < 0){	
		prev->next = newwordNode;
		newwordNode->next = temp;
		return 1 ;
		}
		else if(temp == NULL){
		prev->next = newwordNode;
		return 1;
		}
	}
	
			return 0;
}
}

int contain(wordNodePtrPtr header,char *buf,char *dirName ,char* txtName,int dirTxtCount){
	wordNodePtr word= *header;
	
	while(word!=NULL){
		if(strcmp(buf,word->word)==0){
			break;
		}word=word->next;
	}
	if(word->dirNODE==NULL){
		word->dirNODE=(dirNode*)malloc(sizeof(dirNode));
		strcpy(word->dirNODE->dirName,dirName);
		word->dirNODE->count =1;
		word->dirNODE->next = NULL;
		word->dirNODE->txtCount = dirTxtCount;
		word->dirNODE->txtNODE=(txtNode*)malloc(sizeof(txtNode));
		strcpy(word->dirNODE->txtNODE->txtName,txtName);
		word->dirNODE->txtNODE->next=NULL; return 1;
	}
	else {
		dirNode *tempdir = word->dirNODE;
		while(tempdir!= NULL){
		if(strcmp(tempdir->dirName,dirName)==0){
			tempdir->count=tempdir->count+1;
			txtNode *txttemp =tempdir->txtNODE;
				while(txttemp != NULL){
					if(strcmp(txttemp->txtName,txtName)==0)
					break;
					else if (txttemp->next == NULL){	
						txttemp->next=(txtNode*)malloc(sizeof(txtNode));
						strcpy(txttemp->next->txtName,txtName);
						txttemp->next->next = NULL;
					}
					txttemp = txttemp->next;
					}
		}
		else if (tempdir->next==NULL){
		tempdir->next=(dirNode*)malloc(sizeof(dirNode));
		strcpy(tempdir->next->dirName,dirName);
		tempdir->next->count = 1;
		tempdir->next->txtCount = dirTxtCount;
		tempdir->next->next = NULL;
		tempdir->next->txtNODE=(txtNode*)malloc(sizeof(txtNode));
		strcpy(tempdir->next->txtNODE->txtName,txtName);
		tempdir->next->txtNODE->next=NULL;
		break;
		}
		tempdir=tempdir->next;
		}
}
}

void txtRead(char *txtName,char *dirName,wordNodePtrPtr header,int dirTxtCount){
	FILE *fp;
    char str[150];
    strcpy(str,"dataset////");
    strcat(str,dirName);
    strcat(str,"////");
  	strcat(str,txtName);
    fp = fopen(str, "r");
    if (fp == NULL){
        printf("Could not open file %s",txtName);
    }
    char buf[76];
 
        while( fscanf(fp, "%s", buf) == 1 )
        {
 			
            insert(header,buf,dirName,txtName);
            contain(header,buf,dirName,txtName,dirTxtCount);
    }
    fclose(fp);
}

int dirRead(wordNodePtrPtr header){
	struct dirent *de,*dex,*dek; 
    char txtName[LENGTH];
    char dirName[LENGTH];
    FILE *fp;
    int k = 0;
	  
    DIR *dr = opendir("dataset");
  
    if (dr == NULL)  
    { 
        printf("Could not open current directory" ); 
        return 0;
    } 
  
  	int a = 250;
  	for(a;a>0;a--){
    if((de = readdir(dr)) != NULL){
    	
        strcpy(dirName,de->d_name);
    	
		if ( !strcmp(de->d_name, ".") || !strcmp(de->d_name, "..") );
		else {
            strcpy(dirName,de->d_name);
		   	char str[150];
   			strcpy(str,"dataset////");
    		strcat(str,dirName);
    		strcat(str,"////");
    		DIR *drink = opendir(str);
			DIR *drin = opendir(str);
			while((dek = readdir(drink)) != NULL) {
			k++;
			if ( !strcmp(dek->d_name, ".") || !strcmp(dek->d_name, "..") ){
				k--;
			}
			}
			while((dex = readdir(drin)) != NULL) {
			if ( !strcmp(dex->d_name, ".") || !strcmp(dex->d_name, "..") );
			else{
			strcpy(txtName,dex->d_name);
			txtRead(dex->d_name,de->d_name,header,k);  
 
}
}
	strcpy(str,"");
}
}
			k=0; 
}
    closedir(dr);
	return 1;
	}

void firstOrder(wordNodePtrPtr header){
	wordNodePtr temp = *header;
	wordNodePtr tempNext;
	while(temp!=NULL){
		tempNext=temp->next;
		while(tempNext != NULL){
			dirNode *dirTemp = temp->dirNODE;
			dirNode *dirTempNext;
			while(dirTemp !=NULL){
				dirTempNext = tempNext->dirNODE;
				while(dirTempNext != NULL){
				if(strcmp(dirTemp->dirName,dirTempNext->dirName)==0){
					txtNode *txtTemp = dirTemp->txtNODE;
					txtNode *txtTempNext= dirTempNext->txtNODE;
					while(txtTemp!=NULL){
						while(txtTempNext!=NULL){
							if(strcmp(txtTemp->txtName,txtTempNext->txtName)==0){
								if(temp->forder == NULL){
									temp->forder=(first*)malloc(sizeof(first));
									temp->forder->node=tempNext;
									temp->forder->next =NULL;
								}
									else{
										first *tempForder=temp->forder;
									while(tempForder!=NULL){
										if(tempForder->node == tempNext) {
										break;	
										}
										if(tempForder->next == NULL){
										first* tempForderNext;
										tempForder->next=(first*)malloc(sizeof(first));
										tempForderNext=tempForder->next;
										tempForderNext->node = tempNext;
										tempForderNext->next =NULL;
											}
										tempForder= tempForder->next;
										}
									}
							if(tempNext->forder == NULL){
								tempNext->forder=(first*)malloc(sizeof(first));
								tempNext->forder->node=temp;
								tempNext->forder->next =NULL;
							}
							else{
								first *tempNextForder=tempNext->forder;
								while(tempNextForder!=NULL){
									if(tempNextForder->node == temp)
									break;
									if(tempNextForder->next == NULL){
									first* tempNextForderNext;
									tempNextForder->next=(first*)malloc(sizeof(first));
									tempNextForderNext=tempNextForder->next;
									tempNextForderNext->node=temp;
									tempNextForderNext->next=NULL;
									}
									tempNextForder = tempNextForder->next;
								}
							}
							}
							txtTempNext=txtTempNext->next;
						}
						if(txtTemp->next != NULL);
						txtTemp=txtTemp->next;
						txtTempNext= dirTempNext->txtNODE;
					}
					}
					dirTempNext = dirTempNext->next;
				}
			dirTemp = dirTemp->next;
			}
			tempNext=tempNext->next;
		}
		temp = temp->next;
	}
}

void secondOrder(wordNodePtrPtr header){
	wordNodePtr temp = *header;
	wordNodePtr tempHeader,tempNext;
	int x = 1;
		while(temp!=NULL){
		tempHeader= *header;
		while(tempHeader != NULL){
			first* foTemp = temp->forder;
			if(strcmp(temp->word,tempHeader->word)==0){
			tempHeader = tempHeader->next;
			continue;
			} 
			while(foTemp!=NULL){
				tempNext = tempHeader;
			if(strcmp(foTemp->node->word,tempNext->word)==0){
				first* foTempNext = tempNext->forder;
				while(foTempNext != NULL){
					first* foTemp2 = temp->forder;
					while(foTemp2 !=NULL){
						if(strcmp(foTempNext->node->word,foTemp2->node->word) == 0){
							x=0;
						}
					foTemp2=foTemp2->next;
				}
					if(strcmp(temp->word,foTempNext->node->word)==0){
						x=0;
					}
				if(x == 1){
					if(temp->sorder == NULL){
						temp->sorder=(second*)malloc(sizeof(second));
						temp->sorder->node=foTempNext->node;
						temp->sorder->next=NULL;
			}
			else{
						second *tempSorder=temp->sorder;
					while(tempSorder!=NULL){
						if(strcmp(tempSorder->node->word,foTempNext->node->word)==0)
						break; 
							if(tempSorder->next == NULL){
							second* newtempSorderNext;
							tempSorder->next=(second*)malloc(sizeof(second));
							newtempSorderNext=tempSorder->next;
							newtempSorderNext->node=foTempNext->node;
							newtempSorderNext->next=NULL;
							break;
						}
								tempSorder=tempSorder->next;
							}
								}
									}	
			foTemp2=temp->forder;
			x=1;
			foTempNext=foTempNext->next;
			}
				}
		foTemp = foTemp->next;
			}
		tempHeader = tempHeader->next;
		}
		temp=temp->next;
	}
}

void thirdOrder(wordNodePtrPtr header){
	wordNodePtr temp = *header;
	wordNodePtr tempNext , tempHeader ;
	int x = 1;
		while(temp!=NULL){
			tempHeader = *header;
			while(tempHeader != NULL){
			second* soTemp = temp->sorder;
			if(strcmp(temp->word,tempHeader->word)==0){
			tempHeader = tempHeader->next;
			continue;
			}
				while(soTemp!=NULL){
					tempNext = tempHeader;
				if(strcmp(soTemp->node->word,tempNext->word)==0){
				second* soTempNext = tempNext->sorder;
					while(soTempNext != NULL){
					second* soTemp2 = temp->sorder;
						while(soTemp2 != NULL){
							if(strcmp(soTempNext->node->word,soTemp2->node->word)  == 0)
							x = 0;
							first* foTemp = temp->forder;
								while(foTemp != NULL){
									if(strcmp(foTemp->node->word,soTempNext->node->word) == 0)
									x=0;
									foTemp=foTemp->next;
								}
								if(strcmp(temp->word,soTempNext->node->word)==0) {
									x=0;
								}
								soTemp2=soTemp2->next;
						}
						if(x==1){
							if(temp->torder == NULL){
						temp->torder=(third*)malloc(sizeof(third));
						temp->torder->node=soTempNext->node;
						temp->torder->next=NULL;
										}
						else{
							third *tempTorder=temp->torder;
							while(tempTorder != NULL){
								if(strcmp(tempTorder->node->word,soTempNext->node->word)==0)
							break;
								if(tempTorder->next==NULL){
							third* newtempTorderNext;
							tempTorder->next=(third*)malloc(sizeof(third));
							newtempTorderNext=tempTorder->next;
							newtempTorderNext->node=soTempNext->node;
							newtempTorderNext->next=NULL;
							break;
										}
								tempTorder=tempTorder->next;
							
									}
								}
							}
			soTemp2=temp->sorder;
			x=1;
			soTempNext=soTempNext->next;
						}
					}
			soTemp=soTemp->next;
				}
		tempHeader = tempHeader->next;
		}
			temp =temp->next;
	}
}

void printFirstOrder(wordNodePtr header){
	wordNodePtr temp = header;
	first *firstTemp;
	printf("First orders =\n");
	while(temp!=NULL){
		firstTemp = temp->forder;
		if(temp->forder ==NULL);
		while(firstTemp!=NULL){
		printf("{%s,%s},",temp->word,firstTemp->node->word);
		firstTemp=firstTemp->next;
		}
		temp=temp->next;
	}
	printf("\n");
}

void printSecondOrder(wordNodePtr header){
	wordNodePtr temp = header;
	second *secondTemp;
	printf("Second orders =\n");
	while(temp!=NULL){
		secondTemp = temp->sorder;
		if(temp->sorder ==NULL);
		while(secondTemp!=NULL){
		printf("{%s,%s},",temp->word,secondTemp->node->word);
		secondTemp=secondTemp->next;
		}
		temp=temp->next;
	}
	printf("\n");
}

void printThirdOrder(wordNodePtr header){
	wordNodePtr temp = header;
	third *thirdTemp;
	printf("Third orders =\n");
	while(temp!=NULL){
		thirdTemp = temp->torder;
		if(temp->torder==NULL);
		while(thirdTemp!=NULL){
		printf("{%s,%s},",temp->word,thirdTemp->node->word);
		thirdTemp=thirdTemp->next;			
		} 
	temp=temp->next;
	}
	printf("\n");
}

void printMostCommon(wordNodePtr header){
	wordNodePtr temp;
	temp = header;
	commonWord mostCommon [5];
	txtNode *txtTemp;
	int n=5;
	for (n;n>0;n--)
	mostCommon[n-1].Count = 0;
	int x = 0;
	char dirNames[3][57]={"","",""};
	while(temp!=NULL){
		dirNode *dirNodeTemp = temp->dirNODE;
		if(strcmp(dirNames[0],"")==0)
		strcpy(dirNames[0],temp->dirNODE->dirName);
		while(dirNodeTemp != NULL){
			if(x==0){
		if(strcmp(dirNames[0],dirNodeTemp->dirName)!=0){
		strcpy(dirNames[1],dirNodeTemp->dirName);
		x=1;
		}
	}
	else if (x==1){
		if(strcmp(dirNames[0],dirNodeTemp->dirName)!=0){
			if(strcmp(dirNames[1],dirNodeTemp->dirName)!=0){
			strcpy(dirNames[2],dirNodeTemp->dirName);
				}
		}
	}
			dirNodeTemp=dirNodeTemp->next;
	}
		temp = temp->next;
	}
	for(x=0;x<3;x++){
		printf("   Directory = %s :\n Most frequent 5 words\n",dirNames[x]);
		temp = header;
		while(temp != NULL){
			dirNode *tempDir=temp->dirNODE;
			while(tempDir!=NULL){
				if(strcmp(dirNames[x],tempDir->dirName)==0){
				for(n = 5;n>0;n--){
					if(tempDir->count > mostCommon[n-1].Count){
						strcpy(mostCommon[n-1].Name,temp->word);
						mostCommon[n-1].Count=tempDir->count;
						mostCommon[n-1].txtC=0;
						mostCommon[n-1].docC=tempDir->txtCount;
						txtTemp = tempDir->txtNODE;
						while(txtTemp!=NULL){
							mostCommon[n-1].txtC = mostCommon[n-1].txtC+1;
							txtTemp =txtTemp->next;
						}
						break;
					}
				}
				}
				tempDir=tempDir->next;
			}
			temp=temp->next;
		}
		for(n=5;n>0;n--){
		printf("     %s -> %d\n",mostCommon[n-1].Name,mostCommon[n-1].Count);
	}
		printf("****************************\n");
		printf(" Term frequency of the most frequent 5 words\n");
		double idf = 0;
		int doc = 0;
		int txt = 0;
		double doctxt = 0;
		for(n=0;n<5;n++){
		doc = mostCommon[n].docC;
		txt = mostCommon[n].txtC;
		doctxt=(double)doc/(double)txt;
		idf = log(doctxt);
		printf("     %s -> %.4f\n",mostCommon[n].Name,idf);
		}
		for (n=5;n>0;n--)
		mostCommon[n-1].Count = 0;
		printf("----------------------------\n");
	}
}

int main(){
	wordNodePtr header = NULL;
	dirRead(&header);
	firstOrder(&header);
	secondOrder(&header);
	thirdOrder(&header);
	printFirstOrder(header);
	printSecondOrder(header);
	printThirdOrder(header);
	printMostCommon(header);
	return 0;
}

