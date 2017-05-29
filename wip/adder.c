/********************************************
*											*
* Code Adder it's an easy code to fusion	*
* or add blocks of code in one file,		*
* 											*
*											*
*											*
* By @jatib									*
*											*
********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h> 
#define LIMIT 500

//First declare functions

void error(const char *s);


void leerDirectorio(char *archivo);
char* analytics(char *codigo);
int verificar( char *cadena, char *subcadena );
char* procesador(void);

int main()
{
	DIR *dir;
	struct dirent *ent;
	char path[]=".";

	printf("Give a path:\n");
	//scanf("%s",path);

	dir = opendir(path);
	if(dir == NULL)
		error("Imposible abrir directorio");

	 while ((ent = readdir(dir)) != NULL) 
    {
	    if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
	    {
	      leerDirectorio(ent->d_name);
	      //printf("%s\n", ent->d_name);
	    }
    }

  closedir (dir);

  printf("%s\n",analytics("ABC"));

  return EXIT_SUCCESS;
}

int verificar( char *cadena, char *subcadena )
{
   char *tmp = cadena;
   char *pdest;
  
   pdest = strstr( tmp, subcadena );
   if( pdest ) return 1;

   return 0;
}

void error(const char *s)
{
  perror (s);
  exit(EXIT_FAILURE);
}

void leerDirectorio(char *archivo)
{
  FILE *fich;
  long ftam;

  fich = fopen(archivo, "r");
  if(fich)
    {
      fseek(fich, 0L, SEEK_END);
      ftam=ftell(fich);
      //fclose(fich);
      printf ("%s (%ld bytes)\n", archivo, ftam);
    }
  else
    printf ("%s (No info.)\n", archivo);
}


char* analytics(char *codigo){

	FILE *test;
	
	char script[]="\n<script>\n\t(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){\n\t(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),\n\tm=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)\n\t})(window,document,'script','https://www.google-analytics.com/analytics.js','ga');\n\n\tga('create', '";
	char scriptFin[]="', 'auto');\n\tga('send', 'pageview');\n</script>";
	int limite;

	limite = strlen(script)+strlen(codigo)+strlen(scriptFin);

	//printf("%d\n", limite);
	char cadena[limite];

	strcat(cadena,script);
	//printf("%d\n", sizeof(cadena));
	//printf("%s\n", cadena);

	strcat(cadena,codigo);
	//printf("%d\n", sizeof(cadena));
	//printf("%s\n", cadena);

	strcat(cadena,scriptFin);
	//printf("%d\n", sizeof(cadena));
	//printf("%s\n", cadena);

	//printf("%d\n", sizeof(cadena));

	test = fopen("test.txt","w+");

	for (int i = 0; i < limite; ++i)
	{
		//printf("%c", cadena[i]);
		fwrite(cadena[i],sizeof(char), sizeof(cadena[i]),test);
	}

	//printf("%s%s\n", script,scriptFin);

	return cadena;
}

  



