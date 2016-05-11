/************************************
 *  GrammarReader					*
 * v. 1.2.2							*
 * Corrado Mencar, Pasquale Lops	*
 * Implementazioni:					*
 * Mirko Mastronardi  mat.618560	*
 ************************************/

#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_PRODUCTIONS 100
#define SYMBOL_START 83 //83=S
#define MAX_SYMBOL 26
// Definizione dei tipi ------------------------------------------------------*/

typedef char Symbol;

typedef struct{
	Symbol word [MAX_WORD_LENGTH];
	unsigned length;
} Word;

typedef struct{
	Word left;
	Word right;
	int error;
} Production;

typedef struct{
	Production productions[MAX_PRODUCTIONS];
	unsigned numprod;
        
} Grammar;

typedef struct{
    Symbol symbol_used [MAX_WORD_LENGTH];
    unsigned length;
} Symbol_report;

//PROTOTIPI BASE
int is_terminal(Symbol s);
int is_nonterminal(Symbol s);
int is_prodsym(Symbol s);
int is_prodsep(Symbol s);

void add_symbol(Word *w, Symbol s);
void print_sym (Symbol s);
void print_word (Word* w);
void print_production (Production* p);
void print_grammar(Grammar* g);

Grammar* load_grammar(FILE* file, Grammar* g);

Symbol read_sym(FILE* file);

Production* add_new_production(Grammar *g);

//PROTOTIPI PERSONALI

int left_is_nonterminal (Production* produzione);
int search_Start(Grammar* grammatica);
int search_Start_in_production(Production* produzione);
int is_production_monotona(Production* produzione);
int is_grammar_monotona(Grammar* grammatica);
int is_context_free(Grammar* grammatica);
int is_lineare_destra(Grammar* grammatica);
int is_production_context_sensitive(Production* produzione);
int is_grammar_context_sensitive(Grammar* grammatica);
int grammar_not_valid(Grammar* grammatica);
int check_is_valid_unione(Symbol_report* report1, Symbol_report* report2);
int iteration_grammar(Grammar grammatica,Grammar* iterazione);
int concat_double_grammar(Grammar grammatica1, Grammar grammatica2, Grammar* grammatica3);
int unione_double_grammar(Grammar grammatica1, Grammar grammatica2, Grammar* grammatica3);
int search_start_position(Grammar* grammatica);
int trasformazione_contestuale(Production* produzione,Grammar* grammatica);
int is_only_not_terminal(Production* produzione);

void aggiungi_produzione(Grammar* grammatica);
void start_grammar(Grammar* grammatica);
void delete_production_from_file(char* filename, Grammar* grammatica);
void rimozione_produzione(char* filename, Grammar* grammatica);
void search_and_replace_start(Grammar* grammatica,Symbol carattere);
void print_error(int code_error);
void word_report(Word* parola, Symbol_report* report);
void create_symbol_report(Grammar *grammatica, Symbol_report* lista);
void merge_report(Symbol_report* report1, Symbol_report* report2, Symbol_report* merge_report);
void word_replacement(Word* parola,Symbol_report* intersezione,Symbol_report* report_merge);
void production_replacement(Production* produzione,Symbol_report* intersezione,Symbol_report* report_merge);
void grammar_replacement(Grammar* grammatica,Symbol_report* intersezione,Symbol_report* report_merge);
void create_reference(Symbol_report* report_intersezione, Symbol_report* report_merge, Symbol_report* referenze);
void unione(Grammar* g1, Grammar* g2, Grammar* g3);
void symbol_equals(Symbol_report* report1, Symbol_report* report2,Symbol_report* report_intersezione);
void delete_grammar(Grammar* grammatica);
void create_reference(Symbol_report* report_intersezione, Symbol_report* report_merge, Symbol_report* referenze);
void replacement_start(Grammar* grammatica,Symbol_report* merge);

Symbol genera_carattere(Symbol_report* report );

Grammar* delete_prod(Grammar* gram, int posizione);

Production* add_new_production(Grammar *g);

//void add_production_on_grammar(Grammar* grammatica,Production produzione);
//void aggiunta_produzione(char* file_gram,Grammar* grammatica);
//void add_production_on_file(char* file_name,Production produzione);
