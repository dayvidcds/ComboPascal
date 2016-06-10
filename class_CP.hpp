#ifndef CLASSES_H
#define CLASSES_H

#include <map>
#include <string.h>
#include <iostream>

using namespace std;

class Node {
	public:
		virtual void accept(class Visitor *) = 0;
};

class Programa : public Node{

};

class Command : public Programa{
	
};

class List : public Command{
	
};

class Pgr : public List{
	
};

class Codigo : public List{
	
};

class Var :public Codigo{
	
};

class Beg : public Codigo{
	
};

class Endfim : public Codigo{
	
};

class Dec : public Codigo{
	
};

class Decler: public Dec{
	
};

class Tipo: public Decler{
	
};

class Integer: public Tipo{
	
};

class Real: public Tipo{
	
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

class Value: public ExpUn{
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


class ExpBinPlus: public Exp {
	private:
		Exp *exp;
		Factor *factor;

	public:
		ExpBinPlus(Exp *e, class Factor *f): exp(e), factor(f){} //construtor
		Exp *getExp (){ 
			return this->exp;
		}
		Factor *getFactor(){ 
			return this->factor;
		}
		void accept(Visitor *);
};

class ExpBinMinus: public Exp {
	private:
		Exp *exp;
		Factor *factor;
	public:
		ExpBinMinus(Exp *e,  class Factor *f): exp(e), factor(f){}
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
		ExpUn *expUn;
	public:
		FactorMul(Factor *f, ExpUn *ue): factor(f), expUn(ue){}
		Factor *getFactor(){ 
			return this->factor;
		}
		ExpUn *getExpUn(){ 
			return this->expUn; 
		}
		void accept(Visitor *);
};

class FactorDiv: public Factor {
	private:
		Factor *factor;
		ExpUn *expUn;
	public:
		FactorDiv(Factor *f, ExpUn *ue): factor(f), expUn(ue){}
		Factor *getFactor(){ 
			return this->factor; 
		}
		ExpUn *getExpUn(){	
			return this->expUn; 
		}
		void accept(Visitor *);
};

class ExpUnPlus : public ExpUn {
	private:	
		Value *value;
	public:
		ExpUnPlus(Value *v): value(v){}
		Value *getValue(){ 
			return this->value; 
		}
		void accept(Visitor *);
};

class ExpUnMinus : public ExpUn {
	private:
		Value *value;
	public:
		ExpUnMinus(Value *v): value(v){}
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
		
		void accept(Visitor *v);
		
};

class Identifier : public Value{
	private:
		char *name;
	public:
		
		Identifier( char *name) {
			this->name = strdup(name);
		};
	
	virtual Type getType();//Analizar
	
		char* getName(){
			return this->name;
		}
		
		void accept(Visitor *);
}; 


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


class Context {
	private:
		static Context *instance;
		Programa *program;
		
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

#endif
