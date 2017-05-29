#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#define LIMIT 500

int main(void){

	FILE *file;
	char fileName[]="shopping.txt",fileOutput[]="shoppingA.txt";
	int guion=0,mayq=0,text;

	if(!(file = fopen(fileName,"r") == NULL)){

		while(( text = fgetc(file) )!= EOF){
			if(text == "-"){
				guion++;
			}
			if(text == ">"){
				mayq++;
			}
			if(guion > 0 && mayq == 0){
				printf("%c",text);
			}
			if(text == "\n"){
				guion = 0;
				mayq = 0;
			}

		}
	}

	return 0;
}