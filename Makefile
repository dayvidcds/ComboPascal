cbp:flex.l bison.y
	bison.exe -d -o bison.cpp bison.y
	flex.exe -o flex.cpp flex.l
	g++ -o $@ -g main.cpp class.cpp visitor.cpp bison.cpp flex.cpp
