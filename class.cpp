#include "class.hpp"
#include "visitor.hpp"
#include <iostream>
using namespace std;

Commands *BlockCommands::getCommands(){
	return this->cmds_;
}

void BlockCommands::setCommands(Commands *cmds) {
	this->cmds_ = cmds;
}

CommandsCommand::CommandsCommand(Commands *cmms,Command *cmm): cmds(cmms),cmd(cmm){}

BlockCommands:: BlockCommands(Commands *cmds): cmds_(cmds) {}

Commands *CommandsCommand::getCommands(){
	return this->cmds;
};

Command *CommandsCommand::getCommand(){
	return this->cmd;
};

int Vardeclaration :: getType(){
	return type_;
}

Identifier *Vardeclaration :: getIdValue{
	return ident_;
}

VarDeclarations *VarVar:: getVarDecls();
	return vds_;	
}

VarDeclaration *VarVar:: getVarDecl();		
	return vd_;
}

FuncDefinitionList *FuncDefinitions :: getFuncDefinitionList(){
	return flist; 
}

FuncDefinition *FuncDefinitions :: getFuncDefinition(){
	return f;
}

Commands *BlockCommands::getCommands(){
	return cmds_;
}

void BlockCommands::setCommands(Commands *cmds){
	cmms_ = cmds;
}








Exp *If::getExp(){
	return this->exp;
}

BlockCommands *If::getExpList(){
	return this->expList;
}

ExpBinPlus::ExpBinPlus(Exp *e, class Factor *f): exp(e), factor(f){
	
} 

Exp *ExpBinPlus::getExp(){
	return this->exp;
}

Factor *ExpBinPlus::getFactor(){
	return this->factor;
}

ExpBinMinus::ExpBinMinus(Exp *e,  class Factor *f): exp(e), factor(f){} 
Exp *ExpBinMinus::getExp (){
	return this->exp; 
}

Factor *ExpBinMinus::getFactor(){ 
	return this->factor; 
}
FactorMul::FactorMul(Factor *f, ExpUn *ue): factor(f), unExp(ue){} 

Factor *FactorMul::getFactor(){ 
	return this->factor; 
}

ExpUn *FactorMul::getUnExp(){ 
	return this->unExp; 
}

FactorDiv:: FactorDiv(Factor *f, ExpUn *ue): factor(f), unExp(ue){} 

Exp *ExpIg::getExp(){
	return this->exp;
}

Factor *ExpIg::getFactor(){
	return this->factor;
}

Exp *ExpDif::getExp(){
	return this->exp;
}

Factor *ExpDif::getFactor(){
	return this->factor;
}

Exp *LessThen::getExp(){
	return this->exp;
}

Factor *LessThen::getFactor(){
	return this->factor;
}


Exp *LessEqualThen::getExp(){
	return this->exp;
}

Factor *LessEqualThen::getFactor(){
	return this->factor;
}


Exp *GreaterThen::getExp(){
	return this->exp;
}

Factor *GreaterThen::getFactor(){
	return this->factor;
}


Exp *GreaterEqualThen::getExp(){
	return this->exp;
}

Factor *GreaterEqualThen::getFactor(){
	return this->factor;
}

Factor *FactorDiv::getFactor(){ 
	return this->factor; 
}

ExpUn *FactorDiv::getUnExp(){	
	return this->unExp; 
}

ExpUnPlus:: ExpUnPlus(Value *v): value(v){} 

Value *ExpUnPlus::getValue(){ 
	return this->value;
}

ExpUnMinus:: ExpUnMinus(Value *v): value(v){} 

Value *ExpUnMinus::getValue(){ 
	return this->value;
}

IntValue::IntValue(int value):value(value){} 

int IntValue::getValue(){
	return this->value; 
}

Value::Type IntValue::getType(){ 
	return INTEGER; 
}

RealValue:: RealValue(double value):value(value){} 

double RealValue::getValue(){ 
	return this->value; 
}

Value::Type RealValue::getType(){ 
	return REAL; 
}

Identifier:: Identifier(char *idvalue){ ident = strdup(idvalue); } 

char *Identifier::getValue(){ 
	return this->ident; 
}

Value::Type Identifier::getType(){ 
	return IDENTIFIER; 
}

Atribuicao::Atribuicao(Identifier *id, Exp *e) : ident(id), exp(e){} 
	Exp *Atribuicao::getExp(){ 
	return this->exp; 
}

Identifier	*Atribuicao::getIdValue(){ 
	return this->ident; 
}

SymbolTable::SymbolTable(SymbolTable *pai) : pai_(pai) {}

Value* SymbolTable::getValue(string name) {
	TableType::iterator it = table_.find(name);
	if ((it == table_.end())) {
		if ((pai_ == NULL)) {
			return NULL;
		}
		
		return pai_->getValue(name);
	}
	
	return it->second;
}

void SymbolTable::addValue(string name, Value* value) {
	table_[name] = value;
}

Context &Context::getContext(){
		if (instance == NULL){ 
			instance = new Context(); 
			instance->escopo = new SymbolTable(NULL);
		}
		return *instance;
}

SymbolTable *Context::getEscopo() {
	return this->escopo;
}

void Context::setProgram(Program *prog){ 
	program = prog; 
}

Program *Context::getProgram(){
	return this->program;
}

Context *Context::instance = NULL;