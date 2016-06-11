#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <map>
#include <vector>
#include <string.h>

using namespace std;
using std::vector;

class Node{
	public:
		virtual void accept(class Visitor *) = 0;
};

class Programa : public Node{

};

class ListaExp : public Programa{
	
};

class Command : public ListaExp{
	
};
 
class Exp : public Command{

};

class Factor: public Exp {
	
};

class ExpUn : public Factor {
	
};

class Value : public ExpUn{
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

class ExpBinPLUS: public Exp {
	private:
		Exp *exp;
		Factor *factor;

	public:
		ExpBinPLUS(Exp *e,Factor *f): exp(e), factor(f){} //construtor
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
		ExpBinMINUS(Exp *e,Factor *f): exp(e), factor(f){}
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



class IntValue: public Value{
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
		void accept(Visitor *);
		
};

class RealValue: public Value {
	private:
		double valor;
	public:
		RealValue(double valor):valor(valor){}
		
		Type getType(){ 
			return REAL; 
		}
		
		double getValue(){
			return this->valor;
		}
		void accept(Visitor *);
};

class Identifier : public Value{
	private:
		char *name;
	public:
		
		Identifier( char *name) {
			this->name = strdup(name);
		};
		
		Type getType(){};
		
		char* getName(){
			return this->name;
		}
		void accept(Visitor *);
}; 

class Atribuicao : public Command{
	private:
		Exp *exp;
		Identifier *iden;
	public:
		Atribuicao(Identifier *id, Exp *e) : iden(id), exp(e){}
		Exp *getExp(){ return this->exp; }
		Identifier	*getIden(){ return this->iden; }
		void accept(Visitor *);
}; 

class Parenteses : public ExpUn{
	private:
		Exp *exp;
	public:
		Parenteses(Exp *xp) : exp(xp){}
		Exp *getExp(){
			return this->exp;
		}	
		void accept(Visitor *);
};		

class Context {
	private:
		static Context *instance;
		static Programa *program;
		Context(){}
	public:
		typedef map<string, Value *> TypeTable;
		static Context &getContext() {
			if (instance == NULL){
				instance = new Context();
				}
			return *instance;
		}
		
		TypeTable &getTable(){ return this->table;}
		
		void setProgram(Programa *prog){ program = prog; }
		
		Programa *getProgram(){
			return this->program;
		};
	private:
		TypeTable table;	
};

Context *Context::instance = NULL;

#endif
