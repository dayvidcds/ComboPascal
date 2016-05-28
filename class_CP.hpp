#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class Pai{};

class Visitor{
	public:
		virtual void visit(Pai *) = 0;
		
};

class Node: public Pai{
	public:
		virtual void accept(Visitor *) = 0;
};

class Programa : public Node{

};

class Comandos : public Programa{

};

class PGR : public Comandos{

};

class Escopo : public Comandos{

};

class Pgr{};

class Value{
	public:
		enum Type{
			INT,
			DOUBLE,
			ID_VALUE
		};
		virtual Type getType() = 0; 
	private:
		Type type;
};

class Identifier: public Value{
	private:
		char *id;
	public:
		char *getValue(){
			return this->id;
		}

		Identifier(char *id) : id(id){}

		Type getType(){
			return ID_VALUE;
		}
}; 

#endif
