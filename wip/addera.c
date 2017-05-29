int verificar( char *cadena, char *subcadena );
void crearArbol(struct dirent *this,int rows,char fileName[500][500]);
void leerArbol(int rows,char fileName[500][500]);

void crearArbol(struct dirent *this,int rows,char fileName[500][500]){
		if( (strcmp(this->d_name, ".")!=0) && (strcmp(this->d_name, "..")!=0) )
			for (int i = 0; i < strlen(this->d_name); ++i)
				fileName[rows][i]=this->d_name[i];
	}


void leerArbol(int rows,char fileName[500][500]){

	FILE *archvio;
	FILE *archivoDeVolcado;
	char query[500];

	printf("Make a query on the body of files on a dir\nInsert string to query:\n");
	scanf("%s",query);
	printf("\n\n");

	for (int z = 0; z < rows; ++z)
	{
		int characters,lines=0;
		int elefanteRosa = 0;
		int limite;

		limite = strlen(fileName[z]) + 4;

		char nombreArchivoDeVolcado[limite];

		nombreArchivoDeVolcado = fileName[z]+".txt";
		//int strangeNoUsedVar=0;


		archvio = fopen(fileName[z],"r");

		if (archvio != NULL)
		{
			int n = 0,lastNotNuLLIndex,k=0;
			
			lastNotNuLLIndex = strlen(query);

			while( n != lastNotNuLLIndex)
			{
				characters = fgetc(archvio);
				if(characters == query[n])n++;
					else if(n!=0)n=0;
				if(characters == EOF)break;
				k++;
				if(characters=='\n' || characters=='\00')
					lines++;
			}
			if(n==lastNotNuLLIndex)printf("Find the query \"%s\", on archvio: %s\nAt line:%d\nCounted characters: %d\n\n\n",query,fileName[z],lines,k);
		}
	}
}

int verificar( char *cadena, char *subcadena )
{
   char *tmp = cadena;
   char *pdest;
  
   pdest = strstr( tmp, subcadena );
   if( pdest ) return 1;

   return 0;
}