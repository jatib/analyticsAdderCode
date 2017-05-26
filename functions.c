#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h> 
#define LIMIT 500

int verificar( char *cadena, char *subcadena );
void codeConstruct(char userID[13], char code[500]);
void crearArbol(struct dirent *this,int rows,char fileName[500][500]);
void leerArbol(int rows,char fileName[500][500],char directorioTXT[500][500],char code[500]);
void volcarFichero(int rows,char fileName[500][500],char directorioTXT[500][500]);

/***************************************************************/

int main()
{
	DIR *dir;
	struct dirent *ent;
	char path[] = ".";
	char directorio[LIMIT][LIMIT],query[LIMIT],fileName[LIMIT][LIMIT];
	char directorioTXT[LIMIT][LIMIT],code[LIMIT],userID[13];
	struct dirent *entite;
	int rows=0;

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

	    for (int i = 0; i < rows; ++i)
	    {
	    	printf("%s\n",fileName[i] );
	    }

	    leerArbol(rows,fileName,directorioTXT,code);
	    volcarFichero(rows,fileName,directorioTXT);
	    //entite = readdir (dir);

	    //crearArbol(entite,rows,fileName);

	closedir (dir);

    return EXIT_SUCCESS;
}

/***************************************************************/

void codeConstruct(char userID[13], char code[500]){
	char script[]="\n<script>\n\t(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){\n\t\t(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),\n\t\tm=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)\n\t\t})(window,document,'script','https://www.google-analytics.com/analytics.js','ga');\n\n\tga('create', '";
	char scriptEnd[]="', 'auto');\n\tga('send', 'pageview');\n\n</script>\n";
	strcat(code,script);
	strcat(code,userID);
	strcat(code,scriptEnd);
}

void crearArbol(struct dirent *this,int rows,char fileName[500][500]){
		if( (strcmp(this->d_name, ".")!=0) && (strcmp(this->d_name, "..")!=0) )
			for (int i = 0; i < strlen(this->d_name); ++i)
				fileName[rows][i]=this->d_name[i];
	}


void leerArbol(int rows,char fileName[500][500],char directorioTXT[500][500],char code[500]){

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
				/*************************************************************/
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
						if(characters == EOF)break;
						k++;
						if(characters=='\n' || characters=='\00')
							lines++;
					}

					if(n == lastNotNuLLIndex){
						for (int i = 0; i < strlen(code); ++i)
						{
							fputc(code[i],archivoDeVolcado);	
						}
						n++;
					}

					//printf("%c",characters);
				}
				if(n==lastNotNuLLIndex)printf("Find the query \"%s\", on archvio: %s\nAt line:%d\nCounted characters: %d\n\n\n",query,fileName[z],lines,k-strlen(query));
				/*************************************************************/
			}

		}
	}
}

void volcarFichero(int rows,char fileName[500][500],char directorioTXT[500][500]){
	
	FILE *archivo;
	FILE *archivoDeVolcado;

	for (int z = 0; z < rows; ++z)
	{
		if(verificar(fileName[z],".html") && !verificar(fileName[z],".txt")){

			int characters,lines=0;
			//int elefanteRosa = 0;
			int limite;
			//nombreArchivoDeVolcado[0] = "\0";
			//int strangeNoUsedVar=0;


			archivo = fopen(fileName[z],"r");
			archivoDeVolcado = fopen(directorioTXT[z],"w+");

			if (archivo != NULL)
			{
				while( (characters = fgetc(archivoDeVolcado)) != EOF){
					fputc(characters,archivo);
				}
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


