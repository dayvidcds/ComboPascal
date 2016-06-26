#ifndef CLASS_HPP
#define CLASS_HPP

#include <map>
#include <string.h>
#include <string>

using namespace std;

class Node {
	public:
		virtual void accept(class Visitor *) = 0;
};

class Program : public Node {};

class ExpList : public Program {};

class Commands : public ExpList{};

class Command : public Commands {};

class CommandsCommand : public Commands {
	private:
		Commands *cmds;
		Command *cmd;
	public:
		CommandsCommand(Commands *cmms,Command *cmm): cmds(cmms),cmd(cmm){};
		Commands *getCommands();
		Command *getCommand();
		void accept(Visitor *v);
};

class Iff : public Command{};

class Exp : public Command {};

class ExpIgDif : public Exp {};

class ExpPlusMinusBin : public Exp {};

class Factor: public Exp {};

class ExpUn: public Factor {};

class Value : public ExpUn {
	public:
		enum Type {
			INTEGER,
			REAL,
			IDENTIFIER
		};
		
		virtual Type getType() = 0;		 
	private:
		Type type;
};

class If: public Iff{
	private:
		Exp *exp;
		ExpList *expList;
	public:
		If(Exp *e, ExpList *eList): exp(e), expList(eList){}
		Exp *getExp();
		ExpList *getExpList();
		void accept(Visitor *);
};

class ExpBinPlus: public ExpPlusMinusBin {
	private:
		Exp *exp;
		Factor *factor;

	public:
		ExpBinPlus(Exp *, class Factor *);
		Exp *getExp();
		Factor *getFactor();
		void accept(Visitor *);
};

class ExpBinMinus: public ExpPlusMinusBin {
	private:
		Exp *exp;
		Factor *factor;
	public:
		ExpBinMinus(Exp *,  class Factor *);
		Exp *getExp ();
		Factor *getFactor();
		void accept(Visitor *);
};

class FactorMul: public Factor {
	private:
		Factor *factor;
		ExpUn *unExp;
	public:
		FactorMul(Factor *, ExpUn *);
		Factor *getFactor();
		ExpUn *getUnExp();
		void accept(Visitor *);
};

class FactorDiv: public Factor {
	private:
		Factor *factor;
		ExpUn *unExp;
	public:
		FactorDiv(Factor *, ExpUn *);
		Factor *getFactor();
		ExpUn *getUnExp();
		void accept(Visitor *);
};

class ExpUnPlus : public ExpUn {
	private:	
		Value *value;
	public:
		ExpUnPlus(Value *);
		Value *getValue();
		void accept(Visitor *);
};

class ExpUnMinus : public ExpUn {
	private:
		Value *value;
	public:
		ExpUnMinus(Value *);
		Value *getValue();
		void accept(Visitor *);
};

class ExpIg : public ExpIgDif {
	private:
		Exp *exp;
		Factor *factor;
	public:
		ExpIg(Exp *e, class Factor *f): exp(e), factor(f){}
		Exp *getExp();
		Factor *getFactor();
		void accept(Visitor *v);
};

class ExpDif : public ExpIgDif {
	private:
		Exp *exp;
		Factor *factor;
	public:
		ExpDif(Exp *e, class Factor *f): exp(e), factor(f){}
		Exp *getExp();
		Factor *getFactor();
		void accept(Visitor *v);
};

class IntValue: public Value {
	private:
		int value;
	public:
		IntValue(int);
		int getValue();
		virtual Type getType();
		void accept(Visitor *);
};

class RealValue: public Value {
	private:
		double value;
	public:
		RealValue(double);
		double getValue();
		virtual Type getType();
		void accept(Visitor *);
};


class Identifier: public Value {
	private:
		char *ident;
	public:
		Identifier(char *);
		char *getValue();
		virtual Type getType();
		void accept(Visitor *);
};

class Atribuicao : public Command {
	private:
		Exp *exp;
		Identifier *ident;
	public:
		Atribuicao(Identifier *, Exp *);
		Exp *getExp();
		Identifier	*getIdValue();
		void accept(Visitor *);
}; 


class Context {
	private:
		static Context *instance;
		Program *program;
	public:
		typedef map<string, Value *> TypeTable;
		static Context &getContext();
		
		TypeTable &getTable();
		void setProgram(Program *);
		Program *getProgram();
	private:
		TypeTable table;	
};

#endif
