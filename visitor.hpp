#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "class.hpp"
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
		virtual void visit(IntValue *) = 0;
		virtual void visit(RealValue *) = 0;
		virtual void visit(Identifier *) = 0;
		virtual void visit(Atribuicao *) = 0;
		virtual void visit(If *) = 0;
		virtual void visit(ExpIg *) = 0;
		virtual void visit(ExpDif *) = 0;
		virtual void visit(CommandsCommand *) = 0;
};

class Interpreter : public Visitor {

	private:
		vector<Value *> stack_;

	public:
		
		void visit(IntValue *);
		
		void visit(RealValue *);
		
		void visit(Identifier *);
		
		void visit(Atribuicao *);

		void visit(ExpBinPlus *);

		void visit(ExpBinMinus *);
		
		void visit(If *i);

		void visit(FactorMul *);

		void visit(FactorDiv *);

		void visit(ExpUnPlus *);

		void visit(ExpUnMinus *);
		
		void visit(ExpIg *bee);

		void visit(ExpDif *bed);
		
		void visit(CommandsCommand *cmd);
};

#endif
