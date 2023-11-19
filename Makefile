yacc: src/parser/calculator.y
	@/opt/homebrew/Cellar/bison/3.8.2/bin/bison -H src/parser/calculator.y

lex: src/parser/calculator.l
	@lex src/parser/calculator.l

calculator: yacc lex src/actions.c src/actions.h src/tree.c src/tree.h
	@gcc lex.yy.c calculator.tab.c src/actions.c src/tree.c -ocalculator -lm

preclean:
	@rm lex.yy.c calculator.tab.c calculator.tab.h

build: calculator preclean
	@echo "Application has been build!"

clean: 
	@rm calculator
	@echo "Finished cleaning!"