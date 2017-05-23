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
		
		virtual void visit(VarVar *vv) = 0;
		virtual void visit(Vardeclaration *) = 0;
		virtual void visit(FuncDefinitions *) = 0;
        virtual void visit(BlockCommands *) = 0;		
		virtual void visit(IfElse *) = 0;
		virtual void visit(While *) = 0;	
		
		virtual void visit(ExpIg *) = 0;
		virtual void visit(ExpDif *) = 0;
		virtual void visit(ExpList *) = 0;
		virtual void visit(CommandsCommand *) = 0;
		virtual void visit(LessThen *) = 0;
		virtual void visit(LessEqualThen *) = 0;
		virtual void visit(GreaterThen *) = 0;
		virtual void visit(GreaterEqualThen *) = 0;
		
		
};

class Interpreter : public Visitor {

	private:
		SymbolTable *escopoAtual;
		vector<Value *> stack_;

	public:
		Interpreter();
		
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
		
		void visit(ExpList *explist);

		void visit(LessThen *lt);
		
		void visit(LessEqualThen *let);
		
		void visit(GreaterThen *gt); 
		
		void visit(GreaterEqualThen *get);
		
		void visit(BlockCommands *bcs);
		
		void visit(FuncDefinitions *fdfs);
		
		void visit(VarVar *vv);
		
		void visit(Vardeclaration *vd);
		
};

#endif
