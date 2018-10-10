mci: ast.o lex.yy.o parse.o lex.yy.c
	g++ -g ast.o lex.yy.o parse.o -o mci

lex.yy.o: lex.yy.c ast.o parse.cpp.h
	g++ -c -g lex.yy.c -o lex.yy.o
lex.yy.c:	lex.ll
	flex lex.ll
parse.cpp parse.cpp.h: parse.yy
	bison --verbose --debug -d parse.yy -o parse.cpp
parse.o:	parse.cpp ast.h 
ast.o:	ast.h ast.cpp

.cpp.o:
	-g++ -g -c $<

clean: 
	rm -f mci *.o lex.yy.c parse.cpp parse.cpp.h

