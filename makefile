
LIB=-ldl -lmysqlpp
INCLUDELIB=-I/usr/include/mysql

a.out : main.cpp 
	g++ $< -o $@ -std=c++2a $(LIB) $(INCLUDELIB)

clear:
	rm -f a.out
