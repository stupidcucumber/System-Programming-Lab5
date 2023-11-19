%{
    #include "calculator.tab.h"
    #include "string.h"
    #include "src/tree.h"
    int yyerror (const char *);

    size_t offset;
    #define ACTION yylval = create_node(strdup(yytext));
%}

%%
[0-9]+ {
    ACTION
    yylval->value = atoi(yytext);
    return NUM;
}

[0-9]+\.[0-9]+ {
    ACTION
    yylval->value = atof(yytext);
    return NUM;
}

abs|log|sin|cos|tan {
    ACTION
    return UNARY_FUNC;
}

[a-zA-Z]+ {
    ACTION
    return VAR;
}

[\n]    { 
    ACTION
    return *yytext; 
}

[-+()=/*^%] { 
    ACTION
    return *yytext; 
}

[ \t]   ;

.   yyerror("invalid character");
%%

int yywrap(void) {
    return 1;
}