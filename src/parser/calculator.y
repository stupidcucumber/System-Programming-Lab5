%code top{
  #include <stdio.h> 
  #include <math.h>   
  #include "src/actions.h" 
  #include "src/tree.h"
  #include <stdio.h>

  int yylex(void);
  void yyerror(char const *);
  extern FILE* yyin;

  int cli = 1;
}

%locations
%define api.value.type { struct node* }
%token NUM VAR UNARY_FUNC

%precedence '='
%left '-' '+'
%left '*' '/' '%'
%precedence NEG
%right '^'


%% /* The grammar follows. */
input:
  %empty
| input line {
    if (cli)
    {
        printf("$ ");
    }
}
;

line:
  '\n'
| exp '\n'   { 
    printf ("%.10g\n", $1->value); 
    print_syntax_tree($1);
    if (cli)
    {
        printf(" Write your input: \n");
    }
}
| statement '\n'
| error '\n' { 
    yyerrok; 
}
;

statement:
  VAR '=' exp { 
    append_var_node($1->name, $3->value); 
}

exp:
  NUM               
{
    $$ = create_node_value("num", $1->value);
    append_node($$, $1);
}
| VAR               {
    var_node* var = get_var_node($1->name);
    if(var == NULL) {
        yyerror("Referencing undefined variable");
        YYERROR;
    }
    $$ = create_node("var");
    append_node($$, $1);
    $$->value = var->value;
}
| UNARY_FUNC '(' exp ')' {
    $$ = create_node_list_binary("exp", $1, $2, $3);
    append_node($$, $4);
    if(!process_unary_function($1->name, $3->value, &$$->value)) {
        YYERROR;
    } 
}
| exp '+' exp        { 
    $$ = create_node_list_binary("exp", $1, $2, $3); 
    $$->value = $1->value + $3->value;
}
| exp '-' exp        { 
    $$ = create_node_list_binary("exp", $1, $2, $3); 
    $$->value = $1->value - $3->value;
}
| exp '*' exp        { 
    $$ = create_node_list_binary("exp", $1, $2, $3); 
    $$->value = $1->value * $3->value;
}
| exp '/' exp        { 
    $$ = create_node_list_binary("exp", $1, $2, $3); 
    $$->value = $1->value / $3->value;
}
| exp '%' exp        { 
    $$ = create_node_list_binary("exp", $1, $2, $3); 
    $$->value = (int)$1->value % (int)$3->value;
}
| '-' exp  %prec NEG { 
    $$ = create_node_list_unary("exp", $1, $2); 
    $$->value = -$2->value;
}
| exp '^' exp        { 
    $$ = create_node_list_binary("exp", $1, $2, $3); 
    $$->value = pow ($1->value, $3->value);
}
| '(' exp ')'        { 
    $$ = create_node_list_binary("exp", $1, $2, $3); 
    $$->value = $2->value;
};

/* End of grammar. */
%%


void yyerror(char const *s)
{
    fprintf (stderr, "%s\n", s);
}

int main(int argc, char const* argv[])
{
    init_variable_table();
    if (argc > 1)
    {
        printf("Start processing text file %s ...\n", argv[1]);
        yyin = fopen(argv[1], "r");
        cli = 0;
    }
    else
    {
        printf("Starting an interactive session!\n");

        printf("Write your input: \n$ ");
    }

    return yyparse();
}