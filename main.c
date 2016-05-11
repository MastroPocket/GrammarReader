#include "global.h"

int main(int argc, char *argv[]){
	int scelta;
	int scelta_sub_menu;
	int i;
	int status;
	char* filename1 = argv[1];
	char* filename2 = argv[2];
  	FILE* gram_file1;
  	FILE* gram_file2;
  	Grammar grammar;
  	Grammar grammar2;
  	Grammar g3;
  
  	// controlla se è stato inserito il nome del file
  
 	 if (filename1 == 0){
     	printf("nome file non specificato \n");
     	return -1;
  	}
  	
  
  
  	// apertura del file contenente la grammatica
  
  	gram_file1 = fopen(filename1,"r");
  	if (gram_file1 == NULL){
     	printf("nome di file errato\n");
     	return -1;
  	}
  	
  	Symbol parola [MAX_WORD_LENGTH];
  	start_grammar(&grammar);
  	load_grammar(gram_file1,&grammar);
  	
  	
  	fclose(gram_file1); 
  	
  	do{
    	printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
  		printf("                                      MENU'\n");
  		printf("\n1  - Stampa grammatica");
  		printf("\n2  - Controllare che nella parte sinistra delle produzione esista almeno un          simbolo NT");
  		printf("\n3  - Controllare che la grammatica contenga il simbolo iniziale");
  		printf("\n4  - Controllare che la grammatica sia libera da contesto");
  		printf("\n5  - Controllare che la grammatica caricata sia lineare destra");
  		printf("\n6  - Controllare che la grammatica sia monotona");
  		printf("\n7  - Controllare che la grammatica caricata sia dipendente da contesto");
  		printf("\n8  - Aggiungere nuove produzioni tramite tastiera ad una grammatica gia caricata");
  		printf("9  - Cancellare produzioni da una grammatica gia' caricata");
  		printf("\n10 - Trasformare le produzioni monotone un una serie di produzioni contestuali");
  		printf("\n11 - Ottenere la grammatica unionedi due grammatiche date in input");
  		printf("\n12 - Ottenere la grammatica unione, concatenazione e iterazione di 2 grammatiche     non contestuali");
  		
  		printf("\n0  - Esci");
  
		printf("\n\nScegli l'operazione da svolgere: ");
		scanf("%d",&scelta);  
  		
  		switch(scelta){
  			case 0:
  				break;
  			
  			case 1:
  				system("cls");
  				printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    	printf("                                  PUNTO 1\n");
  				
				print_grammar(&grammar);
				
  				printf("\n");
  				system("pause");
  				system("cls");
  			break;
  			
  			case 2:
  				system("cls");
  				printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    	printf("                                  PUNTO 2\n");
		    	status=1;
		    	for(i=0; i < grammar.numprod && status== 1;i++){
		    		
		    		if(left_is_nonterminal (grammar.productions)== 0)
		    			status=0;
		    	}
		    	
		    	if (status==1)
		    		printf("\nEsiste almeno un carattere NON TERMINALE nella parte sinistra");
		    	else
		    		printf("\nNon esiste almeno un carattere NON TERMINALE nella parte sinistra");
  				printf("\n");
  				system("pause");
  				system("cls");
  			break;
  			
  			case 3:
  				system("cls");
  				printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    	printf("                                  PUNTO 3\n");
		    	
  				if(search_Start(&grammar))
  					printf("Il carattere iniziale %c e' presente",SYMBOL_START);
  				else
  					printf("Il carattere iniziale %c NON e' presente",SYMBOL_START);
  				
				printf("\n");
  				system("pause");
  				system("cls");
  			break;
  			  			
  			case 4:
  				system("cls");
		    	printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    	printf("                                  PUNTO 4\n");
		    	
		    	
		    	if(grammar_not_valid(&grammar)){
		    	
				   if(is_context_free(&grammar))
  					printf("\nGRAMMATICA CONTEXT FREE");
  				   else
					printf("\nGRAMMATICA NON CONTEXT FREE");
					
                }
                else
                  printf("La grammatica non e' valida");
                
  				printf("\n");
  				system("pause");
  				system("cls");
  			break;
  			
  			case 5:
  				system("cls");
  				printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    	printf("                                  PUNTO 5");
		    	
		    	
		    	if(grammar_not_valid(&grammar)){
                                               
  				if(is_lineare_destra(&grammar) && is_context_free(&grammar))
  					printf("\nGRAMMATICA LINEARE DESTRA");
  				else
  					printf("\nGRAMMATICA NON LINEARE DESTRA");
                }
  				else 
  				printf("\nLa grammatica non e' valida");
  				
  				printf("\n");
  				system("pause");
  				system("cls");
  			break;
  			
  			case 6:
  				system("cls");
  				printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    	printf("                                  PUNTO 6");
		    	
		    	if(grammar_not_valid(&grammar)){
                                               
		    	if(is_grammar_monotona(&grammar))
  					printf("\nGRAMMATICA MONOTONA");
				else
					printf("\n\nGRAMMATICA NON MONOTONA");
                }
                else
                  printf("\nLa grammatica non e' valida");
		    	
  				printf("\n");
  				system("pause");
  				system("cls");
  			break;
  			
  			case 7:
  				system("cls");
  				printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    	printf("                                  PUNTO 7");
		    	 
  	            if(grammar_not_valid(&grammar)){
                    if(is_grammar_context_sensitive(&grammar))
  						printf("\nLa grammatica e' Dipendente da contesto");
  					else
  						printf("\nLa grammatica non e' dipendente da contesto");
                }
                else
                	printf("\nLa grammatica non e' valida");	  	    	
                	
  				printf("\n");
  				system("pause");
  				system("cls");
  			break;
  			
  			default:
  				printf("Inserimento NON VALIDO\n");
  				system("pause");
  				system("cls");
  			break;
  			
  			case 8:
  				system("cls");
  				printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    	printf("                                  PUNTO 8");
		    	
		    	aggiungi_produzione(&grammar);
		    	
  						    	
  				printf("\n");
  				system("pause");
  				system("cls");
  			break;
  			
  			case 9:
  				system("cls");
  				printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    	
		    	 
  				rimozione_produzione(filename1,&grammar);
  			  	  	    	
  				printf("\n");
  				system("pause");
  				system("cls");
  			break;
  			
  			case 10:
  				system("cls");
  				printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    	printf("                                  PUNTO 10\n");
		    	
		    	if(grammar_not_valid(&grammar)){
					int produzioni;
					produzioni =grammar.numprod;
			
					for(i=0;i<produzioni;i++){
						if(trasformazione_contestuale(&grammar.productions[i],&grammar)==-1){
							printf("ERRORE TRASFORMAZIONE NON POSSIBILE\n");
							break;
						}
					}
  					print_grammar(&grammar);
  			   }
  			  	else
  			  		printf("ERRORE GRAMMATICA NON VALIDA\n");
  			  		
  				printf("\n");
  				system("pause");
  				system("cls");
			  	
  			
  			break;
  			
  			case 11:
  				system("cls");
  				printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    	printf("                                  PUNTO 11\n");
	
				if (filename2 == 0){
     				printf("ERRORE Secondo file non specificato \n");
     			}
     			else{
     				gram_file2 = fopen(filename2,"r");
  					if (gram_file2 == NULL)
     					printf("nome di file errato\n");
  					else{
  						load_grammar(gram_file2,&grammar2);
  						
  						if(unione_double_grammar(grammar,grammar2,&g3)&&grammar_not_valid(&grammar)&&grammar_not_valid(&grammar2))
  										print_grammar(&g3);
  									else
  										printf("\nERRORE UNIONE NON POSSIBILE\n\n");
  									
  					}		
     			}
  			  	  	    	
  				printf("\n");
  				system("pause");
  				system("cls");
  				
  			break;
  			
  			case 12:
  				system("cls");
  				printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    	printf("                                  PUNTO 12\n");
	
				if (filename2 == 0){
     				printf("ERRORE Secondo file non specificato \n");
     				system("pause");
     				system("cls");
     			}
     			else{
     				gram_file2 = fopen(filename2,"r");
  						if (gram_file2 == NULL){
     					printf("nome di file errato\n");
     					system("pause");
     					system("cls");
  					}
  					else{
  						
  							start_grammar(&grammar2);
  							load_grammar(gram_file2,&grammar2);
  							
  						
  						do{
  							printf("1- UNIONE\n");
  							printf("2- CONCATENAZIONE\n");
  							printf("3- ITERAZIONE GRAMMATICA 1\n");
  							printf("4- ITERAZIONE GRAMMATICA 2\n");
  							printf("0- ESCI\n\n");
  							printf("Inserisci la scelta: ");
  							scanf("%d",&scelta_sub_menu);
  							
  							switch(scelta_sub_menu){
  								
  								case 1:
  									
  									if(unione_double_grammar(grammar,grammar2,&g3)&&grammar_not_valid(&grammar)&&grammar_not_valid(&grammar2))
  										print_grammar(&g3);
  									else
  										printf("\nERRORE UNIONE NON POSSIBILE\n\n");
  									
									system("pause");
  								break;
  								
  								case 2:
  									
  									if(concat_double_grammar(grammar,grammar2,&g3)&&grammar_not_valid(&grammar)&&grammar_not_valid(&grammar2))
  										print_grammar(&g3);
  									else
  										printf("\nERRORE CONCATENAZIONE NON POSSIBILE\n\n");
  								
									system("pause");
								break;
								
								case 3:
									
									if(iteration_grammar(grammar,&g3)&&grammar_not_valid(&grammar))
  										print_grammar(&g3);
  									else
  										printf("\nERRORE ITERAZIONE NON POSSIBILE\n\n");
  								
									system("pause");
								break;
								
								case 4:
									if(iteration_grammar(grammar2,&g3)&&grammar_not_valid(&grammar2))
  										print_grammar(&g3);
  									else
  										printf("\nERRORE ITERAZIONE NON POSSIBILE\n\n");
									system("pause");				
								break;
								
								case 0:
									system("cls");
								break;
								
								default:
									printf("scelta non valida");
									system("pause");
								break;
  							}
  						
  							delete_grammar(&g3);
  							if(scelta_sub_menu){
  								system("cls");
  								printf("                   LABORATORIO DI LINGUAGGI DI PROGRAMMAZIONE\n");
		    					printf("                                  PUNTO 12\n");
		    				}
  						}while(scelta_sub_menu!=0);
				  	}	
     			}
  			
  			break;
  			
  		}
  	
  	}while(scelta!=0);
	
  	printf("\n");
  	system("PAUSE");	
  	return 0;
}


