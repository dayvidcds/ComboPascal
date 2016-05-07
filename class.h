#include <iostream>

class Node{
};

class programa : public Node{
};

class ListaExp : public programa{
};

class comando : public ListaExp {	
};

class Exp : public comando{	
};

class Atrib : public comando{
};

class Factor : public Exp{
};

class ExpUn : public Factor{
};

class Valor : public ExpUn{
	public:
		enum Tipo{
			NONE,
			INT,
			DOUBLE,
		};
	private:	
		Tipo tipo;
};

class INT_VALUE : public Valor{
	private:
		int value;
	public:
		INT_VALUE(int value):value(value){}
		
		int getValue()const{
			return this->value;
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
};

class Identifier : public Valor{
	private:
		char *value;
	public:
		Identifier(char *value):value(value){};
		
		char *getValue()const{
			return this->value;
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
};

class PlusValor : public ExpUn{
	private:
		Valor *val;
	public:
		PlusValor(Valor *v) : val(v){};
		
		Valor *getValor(){
			return this->val;
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
};

class Log2 : public ExpUn{
	private:
		Exp *exp;
	public:
		Log2(Exp *xp) : exp(xp){};
		
		Exp *getExp(){
			return this->exp;
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
};

class parenteses : public Valor{
 	private:
		Exp *exp;
	public:
		parenteses(Exp *xp) : exp(xp){};
		
		Exp *getExp(){
			return this->exp;
		}
};























