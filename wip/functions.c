#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#define LIMIT 500
/*********************************************************/
//For verify regularities on a chain
int verificar( char *cadena, char *subcadena );
//For construct de analytics code from ID
void codeConstruct(int interruptor, char code[500]);
//
void crearArbol(struct dirent *this,int rows,char fileName[500][500]);
//
int leerArbol(int rows,char fileName[500][500],char directorioTXT[500][500],char code[500]);
//
void volcarFichero(int rows,char fileName[500][500]);
//void volcarFichero(int rows,int limit,char fileName[500][500],char directorioTXT[500][500]);
//
void arbol(int rows,char fileName[500][500],char directorioTXT[500][500]);
/***************************************************************/

int main()
{
	DIR *dir;
	struct dirent *ent;
	char path[] = ".";
	char directorio[LIMIT][LIMIT],query[LIMIT],fileName[LIMIT][LIMIT];
	char directorioTXT[LIMIT][LIMIT],code[LIMIT],userID[13];
	struct dirent *entite;
	int rows=0,s=0;

	codeConstruct(0,code);

	dir = opendir(path);
		if(dir == NULL);
			//error("Imposible abrir directorio");

		//proceso leer directorio y construir arbol
		while ((entite = readdir (dir)) != NULL)
	    {
	    	crearArbol(entite,rows,fileName);
	    	rows++;
	    }

	    
	    //arbol(rows,fileName,directorioTXT);

	    s = leerArbol(rows,fileName,directorioTXT,code);
	    volcarFichero(rows,fileName);
	    
	    /*if(s != 0){
		    for (int i = 0; i < s; ++i)
		    {
		    	if(directorioTXT[i] != NULL)
		    		printf("ciclo:%d\n%s\n",i,directorioTXT[i]);
		    }
		    volcarFichero(s,rows,fileName,directorioTXT);
		}else printf("No hay archivos HTML\n");*/
	    

	closedir (dir);

    return EXIT_SUCCESS;
}

/***************************************************************/

void codeConstruct(int interruptor,char code[500]){
	
	char script[]="\n<script>\n\t(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){\n\t\t(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),\n\t\tm=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)\n\t\t})(window,document,'script','https://www.google-analytics.com/analytics.js','ga');\n\n\tga('create', '";
	char scriptEnd[]="', 'auto');\n\tga('send', 'pageview');\n\n</script>\n";

	if(interruptor){
		char userID[13];

		printf("Give a User ID:\n");
		scanf("%s",userID);	

		strcat(code,script);
		strcat(code,userID);
		strcat(code,scriptEnd);
	}else{
		char userID[]="UA-77977334-1";

		strcat(code,script);
		strcat(code,userID);
		strcat(code,scriptEnd);
	}
}

/*********************************************************/
void arbol(int rows,char fileName[500][500],char directorioTXT[500][500]){
	for (int z = 0; z < rows; ++z)
	{
		if(verificar(fileName[z],".html") && !verificar(fileName[z],".txt")){

			strcat(directorioTXT[z],fileName[z]);
			strcat(directorioTXT[z],".txt");
		}
	}

}
/*********************************************************/
void crearArbol(struct dirent *this,int rows,char fileName[500][500]){
		if( (strcmp(this->d_name, ".")!=0) && (strcmp(this->d_name, "..")!=0) )
			for (int i = 0; i < strlen(this->d_name); ++i)
				fileName[rows][i]=this->d_name[i];
	}

/*********************************************************/
int leerArbol(int rows,char fileName[500][500],char directorioTXT[500][500],char code[500]){

	FILE *archvio;
	FILE *archivoDeVolcado;
	int s = 0;
	char query[]="</script>";
	printf("\n\n");

	for (int z = 0; z < rows; ++z)
	{
		if(verificar(fileName[z],".html") && !verificar(fileName[z],".txt")){

			int characters,lines=0;
			int elefanteRosa = 0;
			int limite;
			char nombreArchivoDeVolcado[500];

			strcat(directorioTXT[s],fileName[z]);
			strcat(directorioTXT[s],".txt");

			archvio = fopen(fileName[z],"r+");
			archivoDeVolcado = fopen(directorioTXT[s],"w+");

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
				//if(n==lastNotNuLLIndex)printf("Find the query \"%s\", on archvio: %s\nAt line:%d\nCounted characters: %d\n\n\n",query,fileName[z],lines,k-strlen(query));
				/*************************************************************/
			}

			s++;

		}
	}

	fclose(archvio);
	fclose(archivoDeVolcado);

	return s;
}
/********************************************ESTAS TRABAJANDO EN ESTA FUNCION
EL PROBLEMA RESIDE EN EL NOMBRE DE VUELTA DEL ARCHIVO DE VOLCADO*/
void volcarFichero(int rows,char fileName[500][500]){

	FILE *archvio;
	FILE *archivoDeVolcado;

	for (int z = 0; z < rows; ++z)
	{
		if(verificar(fileName[z],".html.txt")){

			printf("%s\n",fileName[z]);

			int characters;
			//int limite;
			char nombre[500];

			for (int i = 0; i < strlen(fileName[z])-3; ++i)
			{
				if(i<strlen(fileName[z])-4){
					nombre[i] = fileName[z][i];
					printf("%c",fileName[z][i] );	
				}else{

					nombre[i]=0;
					//printf("%c",fileName[z][i] );
				}	
			}

			//strcpy(nombre,fileName[z]);

			//printf("\n%s\n",nombre);

			archvio = fopen(fileName[z],"r+");
			archivoDeVolcado = fopen(nombre,"w+");

			if (archivoDeVolcado != NULL)
			{
				/*************************************************************/
				while( (characters = fgetc(archvio)) != EOF){

					fputc(characters,archivoDeVolcado);

				}
				/*************************************************************/
			}

		}
	}

	fclose(archvio);
	fclose(archivoDeVolcado);
}
/****

/*********************************************************
void volcarFichero(int rows,int limit,char fileName[500][500],char directorioTXT[500][500]){
	
	FILE *archivo;
	FILE *archivoDeVolcado;

	for (int z = 0; z < rows; ++z)
	{
		printf("ciclo:%d\n%s\n",z,directorioTXT[z]);

		for (int i = 0; i < limit; ++i)
		{
			if((verificar(directorioTXT[z],fileName[i])) && !(verificar(fileName[i],".txt")) ){

				int characters;
				int limite;

				//printf("ciclo:%d\n%s\n%s\n",i,fileName[i],directorioTXT[z] );

				archivo = fopen(fileName[z],"r+");
				archivoDeVolcado = fopen(directorioTXT[i],"w+");

				if (archivoDeVolcado != NULL)
				{
					while( (characters = fgetc(archivoDeVolcado)) != EOF){
						fputc(characters,archivo);
					}
				}
			}
		}
		
	}
}
*********************************************************/
int verificar( char *cadena, char *subcadena )
{
   char *tmp = cadena;
   char *pdest;
  
   pdest = strstr( tmp, subcadena );
   if( pdest )return 1;

   return 0;
}
/*********************************************************/

