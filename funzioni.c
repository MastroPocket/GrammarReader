#include "global.h"
// Procedure di riconoscimento dei simboli -----------------------------------*/

int is_terminal(Symbol s){
    
	return (islower(s));
}

int is_nonterminal(Symbol s){
    
	return (isupper(s));
}

int is_prodsym(Symbol s){
    return (s == '>');
}

int is_prodsep(Symbol s){
    return (s == '\n');
}

/* Lettura di simboli da file ------------------------------------------------*/

Symbol read_sym(FILE* file){
	
	Symbol s;
    do 
		s = getc(file);
	while (s==' ');
       
    return s;
}

Production* add_new_production(Grammar *g){
  	Production* p;
  	p = &(g->productions[g->numprod++]);
  	p->left.length = 0;
  	p->right.length = 0;
  
 	 return p;
}
                       

void add_symbol(Word *w, Symbol s){
  	w->word[w->length++] = s;  
}


// Procedura di acquisizione di una grammatica da un file --------------------*/
                       
Grammar* load_grammar(FILE* file, Grammar* g){
	enum States {START,LEFT,RIGHT,ERROR};
    /*   START  = Scansione di una nuova produzione [F]
         LEFT   = Scansione della parte sinistra
         RIGHT  = Scansione della parte destra [F]
         ERROR  = Errore di scansione
    */
	enum States current_state = START;  // Stato iniziale
	Symbol s;
	Production* p;
int contatore=0;
         
	while ( !feof(file)) {
    
		s = read_sym(file);
		if (feof(file)) 
			break;
               
		switch(current_state){
			case START:
				if (is_terminal(s) || is_nonterminal(s)||is_prodsym(s)){
					current_state = LEFT;
					p = add_new_production(g);
							
					if (is_prodsym(s)){
						current_state = RIGHT;
						p->error=4;
						add_symbol(&p->left,' ');
                    }
                    else
                    	add_symbol(&p->left,s);
                }
                else 
					if (is_prodsep(s)){
                       current_state = START;
                    }
                    else {
                    	 current_state = LEFT;
                    	 add_symbol(&p->left,s);
                         p->error=3;          
                         }
						
            break;
            
			case LEFT:
				if (is_terminal(s) || is_nonterminal(s)){
					current_state = LEFT;
					add_symbol(&p->left,s);
                }
                else 
					if (is_prodsym(s)){
						current_state = RIGHT;
                    }
                    else{
                    	if(is_prodsep(s)){
                    		p->error=1;
                    		current_state=START;
                    	}
                    	else{
                        	current_state = LEFT;
                        	add_symbol(&p->left,s);
                        	p->error=3;          
                    	}
					}
                         
            break;
            
            case RIGHT:
					if (is_terminal(s) || is_nonterminal(s)){
						current_state = RIGHT;
                   		add_symbol(&p->right,s);
				   }
					else if(is_prodsep(s)){
							current_state = START;
                    	 }
                    	 else{
                             current_state = RIGHT;
                             p->error=2;   
                             add_symbol(&p->right,s);
                         }
            break;
        }
	}
         
		return g;
}    


// Procedure di stampa

void print_sym (Symbol s){
	
     printf("%c ",s);
}


void print_word (Word* w){
     int i;
     
     for (i=0; i<w->length; i++)
         print_sym(w->word[i]);
}

void print_production (Production* p){
	
     print_word(&p->left);
     printf (" --> ");
     print_word(&p->right);
     print_error(p->error);
}

void print_grammar(Grammar* g){
	
     int i;
     
     if (g == NULL)
        printf ("Errore! Grammatica non valida! \n");
     else
     {
        printf ("Numero di produzioni: %d\n", g->numprod);
        for (i=0; i<g->numprod; i++)
        {
            print_production(&g->productions[i]);
            printf ("\n");
        }
     }
}
