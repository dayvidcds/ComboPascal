#include "class.hpp"

Commands *CommandsCommand::getCommands(){
	return this->cmds;
};

Command *CommandsCommand::getCommand(){
	return this->cmd;
};

Exp *If::getExp(){
	return this->exp;
}

ExpList *If::getExpList(){
	return this->expList;
}

ExpBinPlus::ExpBinPlus(Exp *e, class Factor *f): exp(e), factor(f){} 
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

Context &Context::getContext(){
		if (instance == NULL){ 
			instance = new Context(); 
		}
		return *instance;
}

Context::TypeTable &Context::getTable(){ 
	return this->table; 
}

void Context::setProgram(Program *prog){ 
	program = prog; 
}

Program *Context::getProgram(){
	return this->program;
}

Context *Context::instance = NULL;