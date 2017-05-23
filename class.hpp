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

class Type : public Node{};

class Program : public Node {};

class StatementList : public Program{};

class VarsAndCode : public StatementList{};

class FuncDefinitionList : public StatementList{};

class VarDeclarationList : public VarsAndCode{};

class VarDeclarations : public VarDeclarationList{};

//Aqui seria o varDeclarations

class FuncDefinition : public FuncDefinitionList{};

class FuncDefinitions : public FuncDefinitionList{
		private:
		FuncDefinitionList *flist;
		FuncDefinition *f;
	public:
		FuncDefinitions(FuncDefinitionList *fulist,FuncDefinition *fd): flist(fulist), f(fd){} ;
		FuncDefinitionList *getFuncDefinitionList();
		FuncDefinition *getFuncDefinition();
		void accept(Visitor *v);
};

class FunctionNonPar : public FuncDefinition{};

class BlockCommands : public VarsAndCode {
	private:
		class Commands *cmds_;
	public:
	
		BlockCommands(class Commands *comms) : cmds_(comms){}
	
		void setCommands(Commands *cmds);
		class Commands *getCommands();
		void accept(Visitor *v);
};

class Commands : public BlockCommands{};

class Command : public Commands {};

class CommandsCommand : public Commands {
	private:
		Commands *cmds;
		Command *cmd;
	public:
		CommandsCommand(Commands *cmms,Command *cmm);
		Commands *getCommands();
		Command *getCommand();
		void accept(Visitor *v);
};

class Iff : public Command{};

class Exp : public Command {};

class ExpIgDif : public Exp {};

class ExpLessGreater : public Exp {};

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
		BlockCommands *blockCommands;
	public:
		If(Exp *e, BlockCommands *bcs): exp(e), blockCommands(bcs){}
		Exp *getExp();
		BlockCommands *getBlockCommands();
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

class LessThen : public ExpLessGreater {
private:
	Exp *exp;
	Factor *factor;
public:
	LessThen(Exp *e, Factor *f): exp(e), factor(f){}
	Exp *getExp();
	Factor *getFactor();
	void accept(Visitor *v);
};

class LessEqualThen : public ExpLessGreater {
private:
	Exp *exp;
	Factor *factor;
public:
	LessEqualThen(Exp *e, Factor *f): exp(e) , factor(f){}
	Exp *getExp();
	Factor *getFactor();
	void accept(Visitor *v);
};

class GreaterThen : public ExpLessGreater {
private:
	Exp *exp;
	Factor *factor;
public:
	GreaterThen(Exp *e, Factor *f): exp(e), factor(f){}
	Exp *getExp();
	Factor *getFactor();
	void accept(Visitor *v);
};

class GreaterEqualThen : public ExpLessGreater {
private:
	Exp *exp;
	Factor *factor;
public:
	GreaterEqualThen(Exp *e, Factor *f): exp(e), factor(f){}
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

class SymbolTable {
	private:
		typedef map<string, Value*> TableType;
		TableType table_;
		SymbolTable *pai_;
	public:
		SymbolTable(SymbolTable *pai);
		Value* getValue(string name);
		void addValue(string name, Value* value);
};


class Vardeclaration : public VarDeclarations{

private:
	int type_;
	Identifier *ident_;
public:
	VarDeclaration(int t, class Identifier *d) : type_(t), ident_(d){}
	int getType();
	Identifier *getIdValue;
	void accept(Visitor *);	
};


class VarVar : public VarDeclarations{
	private:
		VarDeclarations *vds_;
		VarDeclaration *vd_;
	public:
		VarVar(VarDeclarations *vards,VarDeclaration *vard): vds_(vards), vd_(vard){}
		VarDeclarations *getVarDecls();
		VarDeclaration *getVarDecl();
		void accept(Visitor *v);
	
};



class Context {
	private:
		SymbolTable *escopo;
		static Context *instance;
		Program *program;
	public:
		static Context &getContext();
		class SymbolTable *getEscopo();
		void setProgram(Program *);
		Program *getProgram();
};

#endif
