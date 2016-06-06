#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "class_CP.hpp"
#include <math.h>
#include <vector>
#include <stdio.h>

using std::vector;

class Visitor {
public:

	virtual void visit(ExpBinPlus *) = 0;
	virtual void visit(ExpBinMinus *) = 0;
	virtual void visit(FactorMul *) = 0;
	virtual void visit(FactorDiv *) = 0;
	virtual void visit(ExpUnPlus *) = 0;
	virtual void visit(ExpUnMinus *) = 0;
	//virtual void visit(ExpUnLog *) = 0;
	//virtual void visit(ExpUnExpo *) = 0;
	virtual void visit(IntValue *) = 0;
	virtual void visit(RealValue *) = 0;
	virtual void visit(Identifier *) = 0;
	//virtual void visit(LparExpRpar *) = 0;
	virtual void visit(Atribuicao *) = 0;
};

class Interpreter : public Visitor {
private:
	vector<Value *> stack_;
public:
	
	void visit(IntValue *v);
	
	void visit(RealValue *v);
	
	void visit(Identifier *v);
	
	void visit(Atribuicao *atrib);
	
	void visit(ExpBinPlus *expBinPlus);

	void visit(ExpBinMinus *expBinMinus);

	void visit(FactorMul *factorMul);

	void visit(FactorDiv *factorDiv);

	void visit(ExpUnPlus *expUnPlus);

	void visit(ExpUnMinus *expUnMinus);

	//void visit(ExpUnLog *expUnLog);

	//void visit(ExpUnExpo *expUnExpo);

	//void visit(LparExpRpar *lparExpRpar);
};

#endif