int verificar( char *cadena, char *subcadena );
void codeConstruct(char userID[13], char code[500]);
void crearArbol(struct dirent *this,int rows,char fileName[500][500]);
int leerArbol(int rows,char fileName[500][500],char directorioTXT[500][500],char code[500]);
void volcarFichero(int rows,int limit,char fileName[500][500],char directorioTXT[500][500]);
void arbol(int rows,char fileName[500][500],char directorioTXT[500][500]);

void codeConstruct(char userID[13], char code[500]){
	char script[]="\n<script>\n\t(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){\n\t\t(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),\n\t\tm=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)\n\t\t})(window,document,'script','https://www.google-analytics.com/analytics.js','ga');\n\n\tga('create', '";
	char scriptEnd[]="', 'auto');\n\tga('send', 'pageview');\n\n</script>\n";
	strcat(code,script);
	strcat(code,userID);
	strcat(code,scriptEnd);
}

/*********************************************************/
void arbol(int rows,char fileName[500][500],char directorioTXT[500][500]){
	for (int z = 0; z < rows; ++z)
	{
		if(verificar(fileName[z],".html") && !verificar(fileName[z],".txt")){

			/*directorioTXT[z] = strcat(directorioTXT[z],fileName[z]);
			directorioTXT[z] = strcat(directorioTXT[z],".txt");*/
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

			s++;

			int characters,lines=0;
			int elefanteRosa = 0;
			int limite;
			char nombreArchivoDeVolcado[500];

			//nombreArchivoDeVolcado[0] = "\0";

			strcat(directorioTXT[z],fileName[z]);
			strcat(directorioTXT[z],".txt");

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
				//if(n==lastNotNuLLIndex)printf("Find the query \"%s\", on archvio: %s\nAt line:%d\nCounted characters: %d\n\n\n",query,fileName[z],lines,k-strlen(query));
				/*************************************************************/
			}

		}
	}

	fclose(archvio);
	fclose(archivoDeVolcado);

	return s;
}
/*********************************************************/
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
/*********************************************************/
int verificar( char *cadena, char *subcadena )
{
   char *tmp = cadena;
   char *pdest;
  
   pdest = strstr( tmp, subcadena );
   if( pdest )return 1;

   return 0;
}
/*********************************************************/

