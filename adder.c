#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <addcode.h>
#define LIMIT 500

int main()
{
	DIR *dir;
	struct dirent *ent;
	char path[] = ".";
	char directorio[LIMIT][LIMIT],query[LIMIT],fileName[LIMIT][LIMIT];
	char directorioTXT[LIMIT][LIMIT],code[LIMIT],userID[13];
	struct dirent *entite;
	int rows=0,s=0;

	printf("Give a User ID:\n");
	scanf("%s",userID);

	codeConstruct(userID,code);
	//UA-77977334-1
	//scanf("%s",path);

	dir = opendir(path);
		if(dir == NULL);
			//error("Imposible abrir directorio");

		//proceso leer directorio y construir arbol
		while ((entite = readdir (dir)) != NULL)
	    {
	    	crearArbol(entite,rows,fileName);
	    	rows++;
	    }

	    
	    arbol(rows,fileName,directorioTXT);

	    s = leerArbol(rows,fileName,directorioTXT,code);
	    
	    
	    for (int i = 0; i < s; ++i)
	    {
	    	printf("ciclo:%d\n%s\n",i,directorioTXT[i]);
	    }
	    volcarFichero(s,rows,fileName,directorioTXT);
	    //entite = readdir (dir);

	    //crearArbol(entite,rows,fileName);

	closedir (dir);

    return EXIT_SUCCESS;
}