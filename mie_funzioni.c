#include "global.h"

//inizializza la grammatica
void start_grammar(Grammar* grammatica){
	grammatica->numprod = 0;
	return;

}

void aggiungi_produzione(Grammar* grammatica){
	
	printf("inserisci la produzione nella forma xx>xxx (invio ctrl+z invio per terminare)\n");
	load_grammar(stdin,grammatica);
	return;
}

//controllo che nella parte sinistra esista almeno un simbolo non terminale   aaBLLLLLx

int left_is_nonterminal (Production* produzione){

	int i=0;
	Word left= produzione->left;
	int status=0;
	while(i<left.length && status==0){
		if(is_nonterminal(left.word[i])){
			status=1;
		}
		i++;
	}

	return status;
}

// Controllo dell'esistenza del carattere di partenza SYMBOL_START

int search_Start_in_production(Production* produzione){

	int status=0;
	
	if(produzione->left.word[0]==SYMBOL_START && produzione->left.length==1)
		status=1;

	return status;
}




int search_Start(Grammar* grammatica){

	int status=0;
	int i,j;
	Production p;
	for(i=0;i<grammatica->numprod && status==0;i++){
		p=grammatica->productions[i];
		if(search_Start_in_production(&p))
			status=1;
	}

	return status;
}


//Controllo della produzione monotona 1=Monotona 0=NON monotona

int is_production_monotona(Production* produzione){
	int status=1;
	int i;

	if(produzione->left.length > produzione->right.length)
		status=0;
	

	return status;
}



//Controllo della grammatica monotona 1=Monotona 0=NON monotona

int is_grammar_monotona(Grammar* grammatica){
	int status=1;
	int i;

	for(i=0; i<grammatica->numprod && status==1 ;i++){
		if(!is_production_monotona(grammatica->productions+i))
			status=0;
	}

	return status;
    }


//Controllo della grammatica libera da contesto 1=CF 0=NON CF

int is_context_free(Grammar* grammatica){
	int status=1;
	int i;

	for(i=0; i<grammatica->numprod;i++){
		if(grammatica->productions[i].left.length !=1)
			status=0;
	}

	return status;
}


//Controllo della grammatica lineare destra 1=lineare destra 0=NON lineare destra  s  aC

int is_lineare_destra(Grammar* grammatica){
	int status=1;
	int i,j;
	int conteggio=0;

	for(i=0; i<grammatica->numprod && status == 1;i++ ){

		switch (grammatica->productions[i].right.length){
			
			case 0:
				status=1;
			break;
			
			case 1:
				if(is_terminal(grammatica->productions[i].right.word[0]))
					status=1;
                else
					status=0;
			break;

			case 2:
				if(is_terminal(grammatica->productions[i].right.word[0]) && is_nonterminal(grammatica->productions[i].right.word[1]))
					status=1;
				else
					status=0;
			break;

        }
	}

	return status;
}

//Inserimento nuova produzione

void add_production_on_file(char* file_name,Production produzione){

	FILE* gram_file = fopen(file_name,"a+");
  		if (gram_file == NULL){
     		printf("nome di file errato\n");
  		}

	fprintf(gram_file, "%s>%s\n",produzione.left.word,produzione.right.word );
	fclose(gram_file);
	return;

}


void add_production_on_grammar(Grammar* grammatica,Production produzione){

	grammatica->productions[grammatica->numprod++]=produzione;
	grammatica->numprod=grammatica->numprod+1;

	return;
}

void aggiunta_produzione(char* file_gram,Grammar* grammatica){

	int i=0;
	int status=0;
	Production produzione_acquisita;
	printf("\n                            AGGIUNTA PRODUZIONE \n");

	do{
		printf("\nParte sinistra della produzione: ");
		scanf("%c", &produzione_acquisita.left.word );
		produzione_acquisita.left.length=strlen(produzione_acquisita.left.word);

		for(i=0;i<produzione_acquisita.left.length ;i++){
			if((is_nonterminal(produzione_acquisita.left.word[i]) || is_terminal(produzione_acquisita.left.word[i]))){
				if(is_nonterminal(produzione_acquisita.left.word[i]))
					status=1;
			}
			else{
				status=0;
				printf("\nHAI INSERITO SIMBOLI ERRATI");
				break;
			}

		}
		if(status==0)
			printf("\nproduzione inserita non valida");
	}while(status==0);


	status=0;

	do{

		printf("\nParte destra della produzione(usa il simbolo \\ per lamda): ");
		scanf("%s", &produzione_acquisita.right.word );
		produzione_acquisita.right.length=strlen(produzione_acquisita.right.word);

		for(i=0;i<produzione_acquisita.right.length ;i++){
			if((is_nonterminal(produzione_acquisita.right.word[i]) || is_terminal(produzione_acquisita.right.word[i]) ||produzione_acquisita.right.word[i]=='\\')){

					status=1;
					if(produzione_acquisita.right.word[i]=='\\'){
						produzione_acquisita.right.word[i]=' ';
						produzione_acquisita.right.length=0;
						break;
					}
			}
			else{
				status=0;
				printf("\nHAI INSERITO SIMBOLI ERRATI");
				break;
			}

		}
		if(status==0)
			printf("\nproduzione inserita non valida");

	}while(status==0);

	add_production_on_grammar(grammatica,produzione_acquisita);
	add_production_on_file(file_gram,produzione_acquisita);

	return;
}


Grammar* delete_prod(Grammar* gram, int posizione){

	int produzioni_totali;
	int i;
	produzioni_totali= gram->numprod;

	for(i=posizione-1; i<produzioni_totali-1; i++){
		gram->productions[i]=gram->productions[i+1];
	}
	gram->productions[produzioni_totali].left.length =0;
	gram->productions[produzioni_totali].right.length = 0;
	gram->numprod=gram->numprod-1;

return gram;
}


void delete_production_from_file(char* filename, Grammar* grammatica){

	int i;
	FILE* gram_file = fopen(filename,"w");
  				if (gram_file == NULL){
     				printf("nome di file errato\n");

  				}
	for(i=0; i<grammatica->numprod; i++){
		fprintf(gram_file, "%s>%s\n",grammatica->productions[i].left.word ,grammatica->productions[i].right.word);
	}
	fclose(gram_file);
	return ;

}

void rimozione_produzione(char* filename, Grammar* grammatica){
	int produzione_delete;
	int i;

	printf("                           RIMOZIONE PRODUZIONE \n\n");
	printf("ELENCO PRODUZIONI:\n\n");
	for(i=0;i<grammatica->numprod;i++){
		printf("%d) ",i+1);
		print_production(&grammatica->productions[i]);
		printf("\n");
	}
	
	do{
		printf("\nInserisci la posizione della produzione da rimuovere: ");
		scanf("%d", &produzione_delete );

		if(produzione_delete>grammatica->numprod)
			printf("\nERRORE --> ULTIMA PRODUZIONE UTILE NUMERO %d <--",grammatica->numprod);
		else{
			grammatica = delete_prod(grammatica, produzione_delete);
			delete_production_from_file(filename,grammatica);
		}
	}while(produzione_delete>grammatica->numprod+1);
	return;
}




void print_error(int code_error){

     switch(code_error){
    
		case 1:
    	      printf("simbolo di produzione mancante");
    	break;
		case 2:
    	      printf("parte destra errata");
    	 break;
    	 case 3:
    	      printf("parte sinistra errata");
    	break;
		case 4:
			printf("Parte sinistra mancante o produzione vuota");
		break;

     }

	return;
}

//Controllo se la produzione è Dipendente da Contesto 1-> CS 0-> NON CS

int is_production_context_sensitive(Production* produzione){

	int status=0;
	int lng_context_sx=0;
	int lng_context_dx=0;
	int i,j;

	i=0;


	while(produzione->left.word[i]==produzione->right.word[i]){
		lng_context_sx++;
		i++;
	}

	i=produzione->left.length-1;
	j=produzione->right.length-1;

	while(produzione->left.word[i]==produzione->right.word[j]){
		lng_context_dx++;
		i--;
		j--;
	}

	if((lng_context_sx+lng_context_dx+1)==produzione->left.length){
		if(((lng_context_sx+lng_context_dx)<produzione->right.length)||(produzione->right.length==0 && produzione->left.length==1&& produzione->left.word[0]==SYMBOL_START)){
			status=1;
		}
	}


	return status;

}

//Controllo se la grammatica è Dipendente da Contesto 1-> CS 0-> NON CS

int is_grammar_context_sensitive(Grammar* grammatica){

	int status=1;
	int i;

	for(i=0;i<grammatica->numprod && status==1;i++ ){
		if(!is_production_context_sensitive(&grammatica->productions[i]))
			status=0;
	}

	return status;
}


//Controllo grammatica errata 1=esatta 0=errata

int grammar_not_valid(Grammar* grammatica){

 int stato=1;
 int i;

 for(i=0;i<grammatica->numprod && stato==1;i++) {

       if(grammatica->productions[i].error>0)
          stato=0;

}

  return stato;
}


void word_report(Word* parola, Symbol_report* report){

	int status=0;
	int j;
	int k;
		for(j=0;j<parola->length;j++){
			if(is_nonterminal(parola->word[j])){
				if(report->length==0){
					report->symbol_used[report->length]=parola->word[j];
					report->length++;
				}
				else{
					for(k=0;k<report->length && status==0;k++){								//1 uguale    0 diverso
						if(parola->word[j]==report->symbol_used[k])
							status=1;
					}
					
					if(!status){
						report->symbol_used[report->length]=parola->word[j];
						report->length++;
					}
				}					
			}
		}
		
	return;
}

//controlla quanti e quali simboli NT vengono utilizzati nella grammatica
void create_symbol_report(Grammar *grammatica, Symbol_report* lista){

	int i;
	
	lista->length=0;
	Production p;
	for(i=0;i<grammatica->numprod;i++){
		p=grammatica->productions[i];
		word_report(&p.left,lista);
		word_report(&p.right,lista);
	}
   return;
}



//genera carattere

Symbol genera_carattere(Symbol_report* report ){
	   Symbol simbolo=65;
	   int i;
	   int status=1;
	   
		do{
			status=1;
			for(i=0; i< report->length && status ==1;i++ ){
				if(simbolo==report->symbol_used[i])
					status=0;
			}
			if(!status)
				simbolo++;
			else{
				report->symbol_used[report->length]=simbolo;
				report->length++;
			}
				
		}while(!status);
		

	   return simbolo;
	   }

int is_only_not_terminal(Production* produzione){
	
	int i;
	int status=1;
	for(i=0;i<produzione->left.length && status == 1;i++){
		if(is_terminal(produzione->left.word[i]))
			status=0;
	}
	
	for(i=0;i<produzione->right.length && status == 1;i++){
		if(is_terminal(produzione->right.word[i]))
			status=0;
	}
		
	
	return status;
}
//trasformazione

int trasformazione_contestuale(Production* produzione,Grammar* grammatica){
	Production prod_work;
	Symbol_report report_symbol_NT;
	Symbol symbol_aux;
	int errore=1;	
	create_symbol_report(grammatica,&report_symbol_NT);
	int i;
	int j;
	Production* new_produzione;
	
	if(((26-report_symbol_NT.length)>=produzione->left.length)&&(is_production_monotona(produzione))&&is_only_not_terminal(produzione)){
		
		//AVVIA TRASFORMAZIONE
		prod_work=*produzione;
		prod_work.right=prod_work.left;
		
		for(i=0; i<produzione->left.length;i++){
			new_produzione=add_new_production(grammatica);
			
			prod_work.right.word[i]=genera_carattere(&report_symbol_NT);
			*new_produzione=prod_work;
			prod_work.left=prod_work.right;
			
		
		}
		
		for(i=0; i<produzione->left.length;i++){
			
			new_produzione=add_new_production(grammatica);
			if(i==prod_work.right.length-1){
				prod_work.right.word[i]=produzione->right.word[i];
				
				for(j=prod_work.right.length; j<produzione->right.length;j++){
					add_symbol(&prod_work.right, produzione->right.word[j]);
				}
			}
			
			else{
				prod_work.right.word[i]=produzione->right.word[i];
			}
			*new_produzione=prod_work;
			prod_work.left=prod_work.right;
			
		}
			
	}
	else
		errore=-1;
	
 return errore;
	 }

//controllo disgiunzione di V1 e V2 1=disgiunti 0=intersezione esistente
int check_is_valid_unione(Symbol_report* report1, Symbol_report* report2){
	
	int status=1;
	int i;
	int j;	
	for(i=0;i<report1->length && status==1;i++){
		for(j=0;j<report2->length && status==1;j++){
			if(report1->symbol_used[i]==report2->symbol_used[j])
				status=0;
		}
	}
	
	
	return status;
}

//concatenazione

void unione(Grammar* g1, Grammar* g2, Grammar* g3){
		
		int i;
		
		
		for(i=0;i<g1->numprod;i++){
			g3->productions[g3->numprod++]=g1->productions[i];			
		}
		for(i=0;i<g2->numprod;i++){
			g3->productions[g3->numprod++]=g2->productions[i];;
		}

	
	return;
}

void symbol_equals(Symbol_report* report1, Symbol_report* report2,Symbol_report* report_intersezione){
	
	int i;
	int j;
	int status=0;
	report_intersezione->length=0;
	for(i=0;i<report1->length;i++){
		status=0;
		for(j=0;j<report2->length && status==0;j++){
			if((report1->symbol_used[i]==report2->symbol_used[j])&&(report1->symbol_used[i]!=SYMBOL_START)){
				report_intersezione->symbol_used[report_intersezione->length++]=report2->symbol_used[j];
				status=1;
			}
		}
	}

	return;
}

//UNIONE di due grammatiche

int unione_double_grammar(Grammar grammatica1, Grammar grammatica2, Grammar* grammatica3){
	
	
	Symbol_report report_gram1;
	Symbol_report report_gram2;
	Symbol_report report_intersezione;
	Symbol_report report_merge;
	Symbol_report report_referenze;
	Production* produzione_start;
	int status;
	
	create_symbol_report(&grammatica1,&report_gram1);
	create_symbol_report(&grammatica2,&report_gram2);
	merge_report(&report_gram1,&report_gram2,&report_merge);
	symbol_equals(&report_gram1,&report_gram2,&report_intersezione);	

	if((report_merge.length+report_intersezione.length)>=25){
		status = 0;
	}
	else{
		status=1;
		int posizione_start1=search_start_position(&grammatica1);
		int posizione_start2=search_start_position(&grammatica2);
		replacement_start(&grammatica1, &report_merge);
		replacement_start(&grammatica2, &report_merge);
		start_grammar(grammatica3);
		
		if(is_lineare_destra(&grammatica1)&&is_lineare_destra(&grammatica2)){
			
		produzione_start=add_new_production(grammatica3);
		add_symbol(&produzione_start->left,SYMBOL_START);

		produzione_start->right=grammatica1.productions[posizione_start1].right;
	
		produzione_start=add_new_production(grammatica3);
		add_symbol(&produzione_start->left,SYMBOL_START);
		produzione_start->right=grammatica2.productions[posizione_start2].right;

			
		}
		
		else{
			
		produzione_start=add_new_production(grammatica3);
		add_symbol(&produzione_start->left,SYMBOL_START);
		produzione_start->right=grammatica1.productions[posizione_start1].right;
	
		produzione_start=add_new_production(grammatica3);
		add_symbol(&produzione_start->left,SYMBOL_START);
		add_symbol(&produzione_start->right,grammatica2.productions[posizione_start2].left.word[0]);
			
		}
		
		if(check_is_valid_unione(&report_gram1,&report_gram2)){
			unione(&grammatica1,&grammatica2,grammatica3);
		}
		else{
			create_reference(&report_intersezione,&report_merge,&report_referenze);
			grammar_replacement(&grammatica2,&report_intersezione,&report_referenze);
			unione(&grammatica1,&grammatica2,grammatica3);
		}
	}
	
	return status;
}

//unione dei report

void merge_report(Symbol_report* report1, Symbol_report* report2, Symbol_report* merge_report){
	int i;
	int j;
	int status=0;
	*merge_report=*report2;

	for(i=0;i<report1->length;i++){
		status=0;
		for(j=0;j<report2->length && status==0;j++){	//0->non presente 1->presente
			if(report1->symbol_used[i]==report2->symbol_used[j]){
				status=1;
			}
			
		}
		if(!status)
			merge_report->symbol_used[merge_report->length++]=report1->symbol_used[i];	
		
	}

	return;
}


void word_replacement(Word* parola,Symbol_report* intersezione,Symbol_report* report_referenze){
	int i=0;
	int j=0;
	for(i=0;i<parola->length;i++){
		for(j=0;j<intersezione->length;j++){
			if(parola->word[i]==intersezione->symbol_used[j]){
				parola->word[i]=report_referenze->symbol_used[j];
			}	
		}
	}
	return;
}

void production_replacement(Production* produzione,Symbol_report* intersezione,Symbol_report* report_referenze){
	
	word_replacement(&produzione->left,intersezione,report_referenze);
	word_replacement(&produzione->right,intersezione,report_referenze);
	
	return;
}

void grammar_replacement(Grammar* grammatica,Symbol_report* intersezione,Symbol_report* report_referenze){
	
	int i;
	for(i=0;i<grammatica->numprod;i++){
		production_replacement(&grammatica->productions[i],intersezione,report_referenze);
	}
	
	return;
}


//Creazione corrispondenze per i NT da sostituire

void create_reference(Symbol_report* report_intersezione, Symbol_report* report_merge, Symbol_report* referenze){
	int i;
	referenze->length=0;
	for(i=0;i<report_intersezione->length;i++){
		referenze->symbol_used[referenze->length++]=genera_carattere(report_merge);
	}
	
	return;
}

//ricerca posizione di START (S)
int search_start_position(Grammar* grammatica){
	int posizione;
	int status=0;
	
	
	for(posizione=0;posizione<grammatica->numprod && status== 0;posizione++){
		
		if(search_Start_in_production(&grammatica->productions[posizione]))
			status=1;
	}
	
	
	return (posizione-1);
}

//funzione generale di concatenazione
int concat_double_grammar(Grammar grammatica1, Grammar grammatica2, Grammar* grammatica3){
	
	int posizione_start1;
	int posizione_start2;
	int status;	
	Symbol_report report_gram1;
	Symbol_report report_gram2;
	Symbol_report report_referenze;
	Symbol_report report_merge;
	Symbol_report report_intersezione;
	Production* start_production;
	
	
	create_symbol_report(&grammatica1,&report_gram1);
	create_symbol_report(&grammatica2,&report_gram2);
	symbol_equals(&report_gram1,&report_gram2,&report_intersezione);	
	merge_report(&report_gram1,&report_gram2,&report_merge);
	
	if((report_merge.length+report_intersezione.length)>=25){
		status = 0;
	}
	else{
		status=1;
		posizione_start1=search_start_position(&grammatica1);
		posizione_start2=search_start_position(&grammatica2);
	
		create_reference(&report_intersezione,&report_merge,&report_referenze);
		grammar_replacement(&grammatica2,&report_intersezione,&report_referenze);
		replacement_start(&grammatica1, &report_merge);
		replacement_start(&grammatica2, &report_merge);
		
		search_and_replace_start(&grammatica1,grammatica1.productions[posizione_start1].left.word[0]);
		search_and_replace_start(&grammatica2,grammatica2.productions[posizione_start2].left.word[0]);
	
		start_production=add_new_production(grammatica3);
		add_symbol(&start_production->left,SYMBOL_START);
	
		add_symbol(&start_production->right,grammatica1.productions[posizione_start1].left.word[0]);
		add_symbol(&start_production->right,grammatica2.productions[posizione_start2].left.word[0]);
	
		unione(&grammatica1,&grammatica2,grammatica3);
	
	}
	return status;
}

void search_and_replace_start(Grammar* grammatica,Symbol carattere){
	
	int i;
	int j;
	for(i=0;i<grammatica->numprod;i++){
		for(j=0;j<grammatica->productions[i].right.length;j++){
			if(grammatica->productions[i].right.word[j]==SYMBOL_START)
				grammatica->productions[i].right.word[j]=carattere;
		}
	}	
	
	return;
}

void replacement_start(Grammar* grammatica,Symbol_report* merge){
	Symbol carattere;
	int i;
	int j;
	carattere=genera_carattere(merge);
	merge->symbol_used[merge->length++]=carattere;

	for(i=0;i<grammatica->numprod;i++){
		for(j=0;j <  grammatica->productions[i].left.length;j++){
			if(grammatica->productions[i].left.word[j]==SYMBOL_START){
				grammatica->productions[i].left.word[j]=carattere;
			}
		}
		
		for(j=0;j<grammatica->productions[i].right.length;j++){
			if(grammatica->productions[i].right.word[j]==SYMBOL_START){
				grammatica->productions[i].right.word[j]=carattere;
			}
		}
		
	}
	return;
}

int iteration_grammar(Grammar grammatica,Grammar* iterazione){
	
	Symbol_report report_gram;
	int posizione_start;
	Production *produzione;
	int i;
	int status;
	
	create_symbol_report(&grammatica,&report_gram);
	
	if(report_gram.length>25){
		status=0;
	}
	else{
		posizione_start=search_start_position(&grammatica);
		replacement_start(&grammatica, &report_gram);
	
		produzione=add_new_production(iterazione);
		add_symbol(&produzione->left,SYMBOL_START);
	
		produzione=add_new_production(iterazione);
		add_symbol(&produzione->left,SYMBOL_START);
		add_symbol(&produzione->right,SYMBOL_START);
		add_symbol(&produzione->right,grammatica.productions[posizione_start].left.word[0]);
	
		for(i=0;i<grammatica.numprod;i++){
			produzione=add_new_production(iterazione);
			*produzione=grammatica.productions[i];
		}
	}
	return status;
}

void delete_grammar(Grammar* grammatica){
	grammatica->numprod=0;
	return;
}

