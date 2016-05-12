#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Visitor {
	virtual void visit(Comandos *) = 0;
	virtual void visit(ExpBinPlus *) = 0;
	virtual void visit(ExpBinMinus *) = 0;
	virtual void visit(FactorMul *) = 0;
	virtual void visit(FactorDiv *) = 0;
	virtual void visit(ExpUnPlus *) = 0;
	virtual void visit(ExpUnMinus *) = 0;
	virtual void visit(ExpUnLog *) = 0;
	virtual void visit(ExpUnExp *) = 0;
	virtual void visit(IntValue *) = 0;
	virtual void visit(DoubleValue *) = 0;
	virtual void visit(Identifier *) = 0;
	virtual void visit(Parenteses *) = 0;
	virtual void visit(Atribuicao *) = 0;
	virtual void visit(Programa *) = 0;
};

class Node{
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Programa : public Node{
	void accept(Visitor *v){
		v->visit(this);
	}
};

class ListaExp : public Programa{
	void accept(Visitor *v){
		v->visit(this);
	}
};

class comando : public ListaExp{
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Exp : public comando{
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Atrib : public comando{
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Factor : public Exp{
	void accept(Visitor *v){
		v->visit(this);
	}
};

class ExpUn : public Factor{
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Valor : public ExpUn{
	/*public:
		enum Tipo{
			NONE,
			INT,
			DOUBLE,
		};
	private:	
		Tipo tipo;
	*/

	void accept(Visitor *v){
		v->visit(this);
	}
};

class Context {
	private:
		static Context *instancia;
		static Programa *programa;
		Context(){};
	public:
		typedef map<string, Valor*> TipoTabela;
		static Context &getContext() {
			if (instancia==NULL){
				instancia = new Context();
			}
			return *instancia;
		}
		TipoTabela &getTabela(){
			return this->tabela;
		}
		void setPrograma(Programa *prog){
			programa = prog;
		}
};

class INT_VALUE : public Valor{
	private:
		int value;
	public:
		INT_VALUE(int value) : value(value){}
		
		int getValue()const{
			return this->value;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class DOUBLE_VAL : public Valor{
	private:
		double value;
	public:
		DOUBLE_VAL(double value):value(value){}
		
		double getValue()const{
			return this->value;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class Identifier : public Valor{
	private:
		char *value;
	public:
		Identifier(char *value) : value(value){};
		
		char *getValue()const{
			return this->value;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class Atribuicao : public Atrib{
	private:
		Identifier *ident;
		Exp *exp;
	public:
		Atribuicao(Identifier *id,Exp *xp) : ident(id),exp(xp){};
		
		Identifier *getIdentifier(){
			return this->ident;
		}
		
		Exp *getExp(){
			return this->exp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class ExpBinPLUS : public Exp{
	private:
		Exp *exp;
		Factor *fac;
	public:
		ExpBinPLUS(Exp *xp,Factor *f) : exp(xp),fac(f){};
		
		Exp *getExp(){
			return this->exp;
		}
		
		Factor *getFactor(){
			return this->fac;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class ExpBinMINUS : public Exp{
	private:
		Exp *exp;
		Factor *fac;
	public:
		ExpBinMINUS(Exp *xp,Factor *f) : exp(xp),fac(f){};
		
		Exp *getExp(){
			return this->exp;
		}
		
		Factor *getFactor(){
			return this->fac;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class FactorMul : public Factor{
	private:
		Factor *fac;
		ExpUn *unexp;
	public:	
		FactorMul(Factor *f,ExpUn *Uxp) : fac(f),unexp(Uxp){};
		
		Factor *getFactor(){
			return this->fac;
		}
		
		ExpUn *getExpUn(){
			return this->unexp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class FactorDiv : public Factor{
	private:
		Factor *fac;
		ExpUn *unexp;
	public:
		FactorDiv(Factor *f,ExpUn *Uxp) : fac(f),unexp(Uxp){};
		
		Factor *getFactor(){
			return this->fac;
		}
		
		ExpUn *getExpUn(){
			return this->unexp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class PlusValor : public ExpUn{
	private:
		Valor *val;
	public:
		PlusValor(Valor *v) : val(v){};
		
		Valor *getValor(){
			return this->val;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class MinusValor : public ExpUn{
	private:
		Valor *val;	
	public:
		MinusValor(Valor *v) : val(v){};
		
		Valor *getValor(){
			return this->val;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class Log2 : public ExpUn{
	private:
		Exp *exp;
	public:
		Log2(Exp *xp) : exp(xp){};
		
		Exp *getExp(){
			return this->exp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}	
};

class EXPO : public ExpUn{
	private:
		Exp *exp;
	public:	
		EXPO(Exp *xp) : exp(xp){};
		
		Exp *getExp(){
			return this->exp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class Parenteses : public Valor{
 	private:
		Exp *exp;
	public:
		Parenteses(Exp *xp) : exp(xp){};
		
		Exp *getExp(){
			return this->exp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

#endif
