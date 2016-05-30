#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;
using std::vector;

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

class Codigo : public Programa{
	
};

class Dec : public Codigo{
	
};

class ListaExp : public Codigo{
	
};
 
class Exp : public ListaExp{

};

class Factor: public Exp {
	
};

class ExpUn: public Factor {
	
};

class Atrib : public ListaExp{
	
};

class ExpBinPLUS: public Exp {
	private:
		Exp *exp;
		Factor *factor;

	public:
		ExpBinPLUS(Exp *e, class Factor *f): exp(e), factor(f){} //construtor
		Exp *getExp (){ 
			return this->exp;
		}
		Factor *getFactor(){ 
			return this->factor;
		}
		void accept(Visitor *);
};

class ExpBinMINUS: public Exp {
	private:
		Exp *exp;
		Factor *factor;
	public:
		ExpBinMINUS(Exp *e,  class Factor *f): exp(e), factor(f){}
		Exp *getExp (){ 
			return this->exp;
		}
		Factor *getFactor(){ 
			return this->factor; 
		}
		void accept(Visitor *);
};

class FactorMul: public Factor {
	private:
		Factor *factor;
		ExpUn *EU;
	public:
		FactorMul(Factor *f, ExpUn *ue): factor(f), EU(ue){}
		Factor *getFactor(){ 
			return this->factor;
		}
		ExpUn *getExpUn(){ 
			return this->EU; 
		}
		void accept(Visitor *);
};

class FactorDiv: public Factor {
	private:
		Factor *factor;
		ExpUn *EU;
	public:
		FactorDiv(Factor *f, ExpUn *ue): factor(f), EU(ue){}
		Factor *getFactor(){ 
			return this->factor; 
		}
		ExpUn *getExpUn(){	
			return this->EU; 
		}
		void accept(Visitor *);
};

class ExpUnPLUS : public ExpUn {
	private:	
		Value *value;
	public:
		ExpUnPLUS(Value *v): value(v){}
		Value *getValue(){ 
			return this->value; 
		}
		void accept(Visitor *);
};

class ExpUnMINUS : public ExpUn {
	private:
		Value *value;
	public:
		ExpUnMINUS(Value *v): value(v){}
		Value *getValue(){ 
			return this->value;
		}
		void accept(Visitor *);
};


class Value{
	public:
		enum Type{
			INTEGER,
			REAL,
			NO_VALUE
		};
		virtual Type getType() = 0; 
	protected:
		Type type;
};

class IntValue: Value{
	private:
		int valor;
		
	public:
		
		IntValue(int valor):valor(valor){}
		
		Type getType(){
			return this->INTEGER;
		}
		
		int getValue(){
			return this->valor;
		}
		
};

class DoubleValue: public Value {
	private:
		double valor;
	public:
		DoubleValue(double valor):valor(valor){}
		
		Type getType(){ 
			return REAL; 
		}
		
		double getValue(){
			return this->valor;
		}
};

class Identifier : Value{
	private:
		char *name;
	public:
		
		Identifier( char *name) {
			this->name = strdup(name);
		};
	
		char* getName(){
			return this->name;
		}
}; 

class Context {
	private:
		static Context *instance;
		static Programa *program;
		Context(){}
	public:
		typedef map<string, Value *> TypeTable;
		static Context &getContext() {
			if (instance == NULL){ instance = new Context(); }
			return *instance;
		}
		
		TypeTable &getTable(){ return this->table; }
		void setProgram(Programa *prog){ program = prog; }
	private:
		TypeTable table;	
};

Context *Context::instance = NULL;

class Atribuicao : public Atrib{
	private:
		Exp *exp;
		Identifier *iden;
	public:
		Atribuicao(Identifier *id, Exp *e) : iden(id), exp(e){}
		Exp *getExp(){ return this->exp; }
		Identifier	*getIden(){ return this->iden; }
		void accept(Visitor *);
}; 

#endif
