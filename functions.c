#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h> 
#define LIMIT 500

int verificar( char *cadena, char *subcadena );
void crearArbol(struct dirent *this,int rows,char fileName[500][500]);
void leerArbol(int rows,char fileName[500][500],char directorioTXT[500][500]);

/***************************************************************/

int main()
{
	DIR *dir;
	struct dirent *ent;
	char path[] = ".";
	char directorio[LIMIT][LIMIT],query[LIMIT],fileName[LIMIT][LIMIT];
	char directorioTXT[LIMIT][LIMIT];
	struct dirent *entite;
	int rows=0;

	printf("Give a path:\n");
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

	    for (int i = 0; i < rows; ++i)
	    {
	    	printf("%s\n",fileName[i] );
	    }

	    leerArbol(rows,fileName,directorioTXT);

	    //entite = readdir (dir);

	    //crearArbol(entite,rows,fileName);

	closedir (dir);

    return EXIT_SUCCESS;
}

/***************************************************************/

void crearArbol(struct dirent *this,int rows,char fileName[500][500]){
		if( (strcmp(this->d_name, ".")!=0) && (strcmp(this->d_name, "..")!=0) )
			for (int i = 0; i < strlen(this->d_name); ++i)
				fileName[rows][i]=this->d_name[i];
	}


void leerArbol(int rows,char fileName[500][500],char directorioTXT[500][500]){

	FILE *archvio;
	FILE *archivoDeVolcado;
	char query[]="</script>";
	printf("\n\n");

	for (int z = 0; z < rows; ++z)
	{
		if(verificar(fileName[z],".html") && !verificar(fileName[z],".txt")){

			int characters,lines=0;
			int elefanteRosa = 0;
			int limite;
			char nombreArchivoDeVolcado[500];

			//nombreArchivoDeVolcado[0] = "\0";

			strcat(directorioTXT[z],fileName[z]);
			strcat(directorioTXT[z],".txt");

			printf("%s\n",directorioTXT[z] );
			//int strangeNoUsedVar=0;


			archvio = fopen(fileName[z],"r");
			archivoDeVolcado = fopen(directorioTXT[z],"w+");

			if (archvio != NULL)
			{
				int n = 0,lastNotNuLLIndex,k=0;
				
				lastNotNuLLIndex = strlen(query);

				
				while( (characters = fgetc(archvio)) != EOF){

					while( n != lastNotNuLLIndex)
					{
						characters = fgetc(archvio);
						fputc(characters,archivoDeVolcado);
						if(characters == query[n]){
							//fputc(characters,archivoDeVolcado);
							n++;
						}
							else if(n!=0){
								//fputc(characters,archivoDeVolcado);
								n=0;
							}
						if(characters == EOF){
							printf("PASO LO QUE DEBÍA PASAR\n");
							break;
						}
						k++;
						if(characters=='\n' || characters=='\00')
							lines++;
					}
					
					printf("%c",characters);
				}
				if(n==lastNotNuLLIndex)printf("Find the query \"%s\", on archvio: %s\nAt line:%d\nCounted characters: %d\n\n\n",query,fileName[z],lines,k-strlen(query));
			}
		}
	}
}

int verificar( char *cadena, char *subcadena )
{
   char *tmp = cadena;
   char *pdest;
  
   pdest = strstr( tmp, subcadena );
   if( pdest )return 1;

   return 0;
}


