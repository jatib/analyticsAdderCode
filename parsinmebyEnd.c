#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#define LIMIT 500

int main()
{
	FILE *file;
	DIR *dir;

	char fileName[LIMIT][LIMIT],query[LIMIT];
	struct dirent *entite;
	int rows=0;

	dir = opendir (".");

	while ((entite = readdir (dir)) != NULL)
    {
      if( (strcmp(entite->d_name, ".")!=0) )for (int i = 0; i < strlen(entite->d_name); ++i)
      	fileName[rows][i]=entite->d_name[i];
      rows++;
    }

	printf("Make a query on the body of files on a dir\nInsert string to query:\n");
	scanf("%s",query);
	printf("\n\n");

	if (dir == NULL)
    printf("can't open file");

	for (int z = 0; z < rows; ++z)
	{
		int characters,lines=0;
		int elefanteRosa = 0;
		//int strangeNoUsedVar=0;

		file = fopen(fileName[z],"r");

		if (file != NULL)
		{
			int n = 0,lastNotNuLLIndex,k=0;
			
			lastNotNuLLIndex = strlen(query);

			while( n != lastNotNuLLIndex)
			{
				characters = fgetc(file);
				if(characters == query[n])n++;
					else if(n!=0)n=0;
				if(characters == EOF)break;
				k++;
				if(characters=='\n' || characters=='\00')
					lines++;
			}
			if(n==lastNotNuLLIndex)printf("Find the query \"%s\", on file: %s\nAt line:%d\nCounted characters: %d\n\n\n",query,fileName[z],lines,k);
		}
	}
  	return EXIT_SUCCESS;
}
