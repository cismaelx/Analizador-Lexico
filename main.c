#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*	
CARLOS ISMAEL ACOSTA DOMÍNGUEZ – 20161005031 
CARLOS NICOLÁS AGUILAR NELSON – 20141000111 
CÉSAR ALEJANDRO AGUILAR BERMUDES – 20161000054 
HADDIEL NAHUM CRUZ RODRÍGUEZ – 20161000374 
JONATHAN JOSUE AMADOR LÓPEZ – 20171004637 
KATHERINE ARELY ESPINO SANTO – 20171001091
*/

FILE *archivo; 			
FILE *output;

bool flag = false;
bool isVar = false;

int main (){
		
	char finalString[1000]="";     
	char rutaFichero[255];
	char variables[100][20]; 	  	
	char word[50]="";
	char currentCharacter;			
	int sizeOfVariables = 0;
	int igualdad;
	int state = 0;
	int i = 0;		

	printf ("\nIngrese el nombre del archivo que desea abrir y pulse INTRO:\n");
  	scanf (" %[^\n]", rutaFichero);
    archivo = fopen(rutaFichero, "r"); 								   
	printf("\n");		
	printf ("\nIngrese el nombre donde desea guardar los el contenido y pulse INTRO:\n");
  	scanf (" %[^\n]", rutaFichero);
    output = fopen(rutaFichero, "w+");       										 	
	printf("\n");	
	 	 	 	 	 		 
	if (archivo == NULL){		
    	printf("\nERROR. No se pudo abrir el archivo. \n\n");       
	}	else{		
        	while((currentCharacter = fgetc(archivo)) != EOF){	 
				if (currentCharacter != ' ' && currentCharacter != '\n'){
					if(isVar == true){
						if(!word[0]){
							memset(variables[sizeOfVariables], 0, 20);
						}	else{
								sizeOfVariables = sizeOfVariables - 1;
							}												
						variables[sizeOfVariables][i] = currentCharacter;						
						sizeOfVariables = sizeOfVariables + 1;						
					}
	    			word[i] = currentCharacter;
            		i++;
        		}        	
				if(currentCharacter >= '0' && currentCharacter <= '9' ){
					if (state == 0 || state == 1){
						state = 1;					
					}						
					else if(state == 2 || state == 3){
						state = 3;
					}
					else if(state == 4 || state == 8){
						state = 8;
					}
				}				
				else if(currentCharacter == '.' && (state == 1)){
					state = 2;		
				}
				else if(currentCharacter >= 'a' && currentCharacter <= 'z'){
					if(state == 0 || state == 4){
						state = 4;
					}
					else if(state == 1 || state == 8){
						state = 8;
					}	
				}
				else if(currentCharacter >= 'A' && currentCharacter <= 'Z'){
					if(state == 0 || state == 4){
						state = 4;
					}
					else if(state == 1 || state == 8){
						state = 8;
					}	
				}				
				else if(currentCharacter >= '0' && currentCharacter <= '9' ){
					strcat(finalString, "<real>");				
				}								
				else if(currentCharacter == '+' || currentCharacter == '-'){
					strcat(finalString, "<operador aditivo>");													
				}
				else if(currentCharacter == '*'|| currentCharacter == '/'){
					strcat(finalString, "<operador multilicativo>");															
				}
				else if(currentCharacter == '<' || currentCharacter == '>'){
					strcat(finalString, "<operador relacional>");
				}
				else if(currentCharacter == '&' || currentCharacter == "|"){
					strcat(finalString, "<operador logico>");
				}																			
				else if(currentCharacter == ' ' || currentCharacter == '\n'){
					isReservedWord(word, finalString, i);	
					if(flag == false){
						if(state == 1){							
							strcat(finalString, "<entero>");							
							state = 0;
							i = 0;
						}
						else if(state == 3){
							strcat(finalString, "<decimal>");							
							state = 0;
							i = 0;
						}
						else if(state == 4 && word[1] && currentCharacter == '\n'){							
							if(isVar == true || (alreadyExist(variables, word, sizeOfVariables) == 0)){
								strcat(finalString, "<variable>");
								isVar = false;
							}	else{
									strcat(finalString, "<cadena>");							
								}							
							state = 0;
							i = 0;
						}
						else if(state == 4 && word[1] && currentCharacter != '\n'){
							if(isVar == true || (alreadyExist(variables, word, sizeOfVariables) == 0)){								
								strcat(finalString, "<variable>");
								isVar = false;
							}	else{
									strcat(finalString, "<cadena>");							
								}
							state = 0;
							i = 0;
						}
						else if(state == 4 && !word[1] && currentCharacter == '\n'){
							if(isVar == true || (alreadyExist(variables, word, sizeOfVariables) == 0)){								
								strcat(finalString, "<variable>");
								isVar = false;
							}	else{
									strcat(finalString, "<letra>");							
								}						
							state = 0;
							i = 0;
						}
						else if(state == 4 && !word[1] && currentCharacter != '\n'){
							if(isVar == true || (alreadyExist(variables, word, sizeOfVariables) == 0)){								
								strcat(finalString, "<variable>");
								isVar = false;
							}	else{
									strcat(finalString, "<letra>");							
								}								
							state = 0;
							i = 0;
						}															
						if(currentCharacter == '\n'){
							strcat(finalString, "\n");							
						}	
						if(currentCharacter == ' '){
							strcat(finalString, "<espacio>");							
						}																										 	
					}	else{							
							state = 0;
						}																									
					memset(word, 0, sizeof word);										
					i = 0;	
				}			 
			}			
			if(currentCharacter == EOF){
				if(state == 1){
					strcat(finalString, "<entero>");
					state = 0;
					i = 0;
				}
				else if(state == 3){
					strcat(finalString, "<decimal>");
					state = 0;
					i = 0;
				}
				else if(state == 4 && word[1]){			
					strcat(finalString, "<cadena>");
					state = 0;
					i = 0;
				}
				else if(state == 4 && !word[1]){			
					strcat(finalString, "<letra>");
					state = 0;
					i = 0;
				}
				else if(state == 8){					
					state = 0;
					i = 0;
				}										
				memset(word, 0, sizeof word);				
				i = 0;
	    	}	    
			fputs(finalString, output);
	    	printf("%s \n", finalString);
        }        
    
	fclose(archivo);
	system("pause");
	return 0;
	
}

int alreadyExist(char variables[100][20], char word[50], int sizeOfVariables){
	int igualdad = -1;
	for(int k = 0; k < sizeOfVariables; k++){
		igualdad = strcmp(variables[k], word);
		if(igualdad == 0){
			return 0;			
		}		
	}
	return -1;			
}

int isReservedWord(word, finalString, i){ 
	int x = 0;
	int igualdad = 1;
	char reservedWords[10][10] =
		{ "programa",
	  	"entero",
	  	"cadena",
	  	"imprimir",
		"leer",
		"si",
		"entonces",
		"sino",
		"mientras",
		"="
		};
	
	for(x = 0; x < 10; x++){				
		igualdad = strcmp(word, reservedWords[x]);				
			if (igualdad == 0){							
				if(x == 9){
					strcat(finalString, "<igualdad>");
					strcat(finalString, "<espacio>");
					flag = true; 				
					i = 0;	
				}	else{
						if(x == 1 || x == 2){							
							isVar = true;							
						}	else{
								isVar = false;
							}			
						strcat(finalString, "<");
						strcat(finalString, reservedWords[x]);
						strcat(finalString, ">");
						if(x== 6 || x == 7){
							strcat(finalString, "\n");
						}	else{
								strcat(finalString, "<espacio>");
							}										
						flag = true;					
						i = 0;
					}
				break;
			}
	}
	if(igualdad != 0){				
		flag = false;
		i = 0;								
	}    

}