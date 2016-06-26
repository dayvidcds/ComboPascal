cbp:flex.l bison.y
	win_bison.exe -d -o bison.cpp bison.y
	win_flex.exe -o flex.cpp flex.l
	g++ -o $@ main.cpp class.cpp visitor.cpp bison.cpp flex.cpp
