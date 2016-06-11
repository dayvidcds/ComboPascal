#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "class_CP.hpp"
#include <math.h>
#include <vector>
#include <stdio.h>

using std::vector;

class Visitor {
public:
	virtual void visit (Node *) = 0;
	virtual void visit(ExpBinPLUS *) = 0;
	virtual void visit(ExpBinMINUS *) = 0;
	virtual void visit(FactorMul *) = 0;
	virtual void visit(FactorDiv *) = 0;
	virtual void visit(ExpUnPLUS *) = 0;
	virtual void visit(ExpUnMINUS *) = 0;
	//virtual void visit(ExpUnLog *) = 0;
	//virtual void visit(ExpUnExpo *) = 0;
	virtual void visit(IntValue *) = 0;
	virtual void visit(RealValue *) = 0;
	virtual void visit(Identifier *) = 0;
	virtual void visit(Parenteses *) = 0;
	virtual void visit(Atribuicao *) = 0;
};

class Interpreter : public Visitor {
private:
	vector <Value*> stack_;
public:
	
	void visit (Node *n);
	
	void visit(IntValue *v);
	
	void visit(RealValue *v);
	
	void visit(Identifier *v);
	
	void visit(Atribuicao *atrib);
	
	void visit(ExpBinPLUS *expBinPlus);

	void visit(ExpBinMINUS *expBinMinus);

	void visit(FactorMul *factorMul);

	void visit(FactorDiv *factorDiv);

	void visit(ExpUnPLUS *expUnPlus);

	void visit(ExpUnMINUS *expUnMinus);

	//void visit(ExpUnLog *expUnLog);

	//void visit(ExpUnExpo *expUnExpo);

	void visit(Parenteses *lparExpRpar);
};

#endif