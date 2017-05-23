#include "visitor.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

Interpreter::Interpreter() {
	this->escopoAtual = Context::getContext().getEscopo();
	cout << "ESCOPO GLOBAL: " << this->escopoAtual << "\n";
}

void Interpreter::visit(IntValue *v){ 
	stack_.push_back(v); 
}

void Interpreter::visit(RealValue *v){ 
	stack_.push_back(v); 
}

void Interpreter::visit(Identifier *v){
	SymbolTable *st = this->escopoAtual;
	Value *valor = st->getValue(v->getValue());
	
	cout << "<< Visitando Idetifier " << v->getValue() << endl;
	
	if ((valor == NULL)) {
		stack_.push_back(v);
		cout << "	>>Identifier '" << v->getValue() << "' NULO"  << endl;
		
	} else {
		
		IntValue *v1 = static_cast <IntValue *> (valor);
		cout << "	>>Identifier '" << v->getValue() <<"= " << v1->getValue() << "' NAO NULO"  << endl;

		stack_.push_back(valor);

		IntValue *v2 = static_cast <IntValue *> (stack_.back());
		cout << "valor na pilha !!! " << v->getValue() << " = " << v2->getValue() << endl;	
		
	}
}

void Interpreter::visit(BlockCommands *BlockCommands){
	SymbolTable *escopoAnterior = this->escopoAtual;
	this->escopoAtual = new SymbolTable(escopoAnterior);
	cout << "ESCOPO NOVO: " << this->escopoAtual << "\n";
	
	BlockCommands->BlockCommands::getCommands()->accept(this);
	this->escopoAtual = escopoAnterior;
	cout << "ESCOPO QUE VOLTOU: " << this->escopoAtual << "\n";
}

void Interpreter::visit(FuncDefinitions *fds){
	fds->FuncDefinitions::getFuncDefinitionList()->accept(this);
	fds->FuncDefinitions::getFuncDefinition()->accept(this);
}

void Interpreter::visit(VarVar *vv){
	vv->VarVar::getVarDecls()->accept(this);
	vv->VarVar::getVarDecl()->accept(this);
}

void Interpreter::visit(Vardeclaration *vd){
	vd->VarVar::getIdValue()->accept(this);
}

void Interpreter::visit(If *i){
	i->If::getExp()->accept(this);
	IntValue *v1 = static_cast<IntValue *>(stack_.back());

	if(v1->getValue()){
		i->If::getBlockCommands()->accept(this);
	}
}

void Interpreter::visit(Atribuicao *a){
	a->Atribuicao::getExp()->accept(this);
	a->Atribuicao::getIdValue()->accept(this);
	
	SymbolTable *st = this->escopoAtual;
	
	cout << "tentando atribuir"<<endl;
	
	cout << "TIPO : " << stack_.back()->getType() << endl;
	
	//IntValue *valueId = static_cast <IntValue *> (stack_.back());
	stack_.pop_back();
	this->escopoAtual->addValue(a->Atribuicao::getIdValue()->getValue(), stack_.back());
	stack_.pop_back();
	
	/*
	if(stack_.back()->getType() == Value::INTEGER){
		cout << "Sa porra eh inteiro!!!!" << endl;
		
		IntValue *valueId = static_cast <IntValue *> (stack_.back());
		stack_.pop_back();
		this->escopoAtual->addValue(valueId->getValue(), stack_.back());
		stack_.pop_back();
		
	} else {
		Identifier *valueId = static_cast <Identifier *> (stack_.back());
		stack_.pop_back();
		this->escopoAtual->addValue(valueId->getValue(), stack_.back());
		stack_.pop_back();
	}
	*/
	
	
	cout << "PASSOU FINAL" << endl;;
}

void Interpreter::visit(ExpBinPlus *bep){
	cout << "SOMA NO ESCOPO: " << this->escopoAtual << "\n";
	
	bep->ExpBinPlus::getExp()->accept(this);
	bep->ExpBinPlus::getFactor()->accept(this);
	
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();
	
	if ((value1 == NULL)) {
		cout << "value1 esta NULO\n";
	} else {
		cout << "value1: " << value1 << "\n";
	}
	
	if ((value2 == NULL)) {
		cout << "value2 esta NULO\n";
	} else {
		cout << "value2: " << value2 << "\n";
	}

	if(value1->getType() == Value::INTEGER && value2->getType() == Value::INTEGER){
		// cout << "PASSOU 1?\n";
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		// cout << "PASSOU AQUI 1 = v1: " << v1->getValue() << ", v2; " << v2->getValue() << "\n";
		stack_.push_back(new IntValue(v1->getValue() + v2->getValue()));
		
	}else if(value1->getType() == Value::INTEGER && value2->getType() == Value::REAL){
		IntValue *v1 = static_cast <IntValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		stack_.push_back(new RealValue(v1->getValue() + v2->getValue()));
		
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::INTEGER){
		RealValue *v1 = static_cast <RealValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		stack_.push_back(new RealValue(v1->getValue() + v2->getValue()));
		
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::REAL){
		RealValue *v1 = static_cast <RealValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		stack_.push_back(new RealValue(v1->getValue() + v2->getValue()));
		
	} else {
		cout << "ERRO EM TEMPO DE EXECUCAO! Matando aplicacao...\n";
		exit(EXIT_SUCCESS);
	}
	
	printf("%d\n", static_cast<IntValue*>(stack_.back())->getValue());

	delete value1;
	delete value2;
}

void Interpreter::visit(ExpBinMinus *bem){
	cout << "SOUBTRACAO NO ESCOPO: " << this->escopoAtual << "\n";
	
	bem->ExpBinMinus::getExp()->accept(this);
	bem->ExpBinMinus::getFactor()->accept(this);
	Value *value2 = stack_.back();
	stack_.pop_back();
	Value *value1 = stack_.back();
	stack_.pop_back(); 

	if(value1->getType() == Value::INTEGER && value2->getType() == Value::INTEGER){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		stack_.push_back(new IntValue(v1->getValue() - v2->getValue()));
	
	}else if(value1->getType() == Value::INTEGER && value2->getType() == Value::REAL){
		IntValue *v1 = static_cast <IntValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		stack_.push_back(new RealValue(v1->getValue() - v2->getValue()));
	
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::INTEGER){
		RealValue *v1 = static_cast <RealValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		stack_.push_back(new RealValue(v1->getValue() - v2->getValue()));
		
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::REAL){
		RealValue *v1 = static_cast <RealValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		stack_.push_back(new RealValue(v1->getValue() - v2->getValue()));	
	} else {
		cout << "ERRO EM TEMPO DE EXECUCAO! Matando aplicacao...\n";
		exit(EXIT_SUCCESS);
	}
		
	printf("%d\n", static_cast<IntValue*>(stack_.back())->getValue());
	
	delete value1;
	delete value2;
}

void Interpreter::visit(FactorMul *fm){
	cout << "MULTIPLICACAO NO ESCOPO: " << this->escopoAtual << "\n";
	
	fm->FactorMul::getUnExp()->accept(this);
	fm->FactorMul::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INTEGER && value2->getType() == Value::INTEGER){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		stack_.push_back(new IntValue(v1->getValue() * v2->getValue()));
	
	}else if(value1->getType() == Value::INTEGER && value2->getType() == Value::REAL){
		IntValue *v1 = static_cast <IntValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		stack_.push_back(new RealValue(v1->getValue() * v2->getValue()));
	
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::INTEGER){
		RealValue *v1 = static_cast <RealValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		stack_.push_back(new RealValue(v1->getValue() * v2->getValue()));
	
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::REAL){
		RealValue *v1 = static_cast <RealValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		stack_.push_back(new RealValue(v1->getValue() * v2->getValue()));
	} else {
		cout << "ERRO EM TEMPO DE EXECUCAO! Matando aplicacao...\n";
		exit(EXIT_SUCCESS);
	}
	
	printf("%d\n", static_cast<IntValue*>(stack_.back())->getValue());

	delete value1;
	delete value2;
}

void Interpreter::visit(FactorDiv *fd){
	cout << "DIVISAO NO ESCOPO: " << this->escopoAtual << "\n";
	
	fd->FactorDiv::getUnExp()->accept(this);
	fd->FactorDiv::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INTEGER && value2->getType() == Value::INTEGER){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		stack_.push_back(new IntValue(v1->getValue() / v2->getValue()));
	
	}else if(value1->getType() == Value::INTEGER && value2->getType() == Value::REAL){
		IntValue *v1 = static_cast <IntValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		stack_.push_back(new RealValue(v1->getValue() / v2->getValue()));
	
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::INTEGER){
		RealValue *v1 = static_cast <RealValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		stack_.push_back(new RealValue(v1->getValue() / v2->getValue()));
	
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::REAL){
		RealValue *v1 = static_cast <RealValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		stack_.push_back(new RealValue(v1->getValue() / v2->getValue()));
	} else {
		cout << "ERRO EM TEMPO DE EXECUCAO! Matando aplicacao...\n";
		exit(EXIT_SUCCESS);
	}
	
	printf("%d\n", static_cast<IntValue*>(stack_.back())->getValue());
	delete value1;
	delete value2;
}

void Interpreter::visit(ExpUnPlus *uep){
	uep->ExpUnPlus::getValue()->accept(this);
	Value *value = stack_.back();
	stack_.pop_back();

	if(value->getType() == Value::INTEGER){
		IntValue *v = static_cast <IntValue *> (value);
	} else if(value->getType() == Value::REAL){
		RealValue *v = static_cast <RealValue *> (value);
	} else {
		cout << "ERRO EM TEMPO DE EXECUCAO! Matando aplicacao...\n";
		exit(EXIT_SUCCESS);
	}
		
	delete value;
}
void Interpreter::visit(ExpUnMinus *uem){
	uem->ExpUnMinus::getValue()->accept(this);
	Value*value = stack_.back();
	stack_.pop_back();

	if(value->getType() == Value::INTEGER){
		IntValue *v = static_cast <IntValue *> (value);
	} else if(value->getType() == Value::REAL){
		RealValue *v = static_cast <RealValue *> (value);
	} else {
		cout << "ERRO EM TEMPO DE EXECUCAO! Matando aplicacao...\n";
		exit(EXIT_SUCCESS);
	}

	delete value;
}

void Interpreter::visit(ExpIg *bee){
	bee->ExpIg::getExp()->accept(this);
	bee->ExpIg::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INTEGER && value2->getType() == Value::INTEGER){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() == v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::INTEGER && value2->getType() == Value::REAL){
		IntValue *v1 = static_cast <IntValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		if(v2->getValue() == v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::INTEGER){
		RealValue *v1 = static_cast <RealValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() == v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::REAL){
		RealValue *v1 = static_cast <RealValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		if(v2->getValue() == v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	} else {
		cout << "ERRO EM TEMPO DE EXECUCAO! Matando aplicacao...\n";
		exit(EXIT_SUCCESS);
	}
			
	delete value1;
	delete value2;

}

void Interpreter::visit(ExpDif *bed){
	bed->ExpDif::getExp()->accept(this);
	bed->ExpDif::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INTEGER && value2->getType() == Value::INTEGER){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() != v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::INTEGER && value2->getType() == Value::REAL){
		IntValue *v1 = static_cast <IntValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		if(v2->getValue() != v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::INTEGER){
		RealValue *v1 = static_cast <RealValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() != v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::REAL){
		RealValue *v1 = static_cast <RealValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		if(v2->getValue() != v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	} else {
		cout << "ERRO EM TEMPO DE EXECUCAO! Matando aplicacao...\n";
		exit(EXIT_SUCCESS);
	}
			
	delete value1;
	delete value2;

}

void Interpreter::visit(LessThen *belt){
	belt->LessThen::getExp()->accept(this);
	belt->LessThen::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INTEGER && value2->getType() == Value::INTEGER){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() < v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::INTEGER && value2->getType() == Value::REAL){
		IntValue *v1 = static_cast <IntValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		if(v2->getValue() < v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::INTEGER){
		RealValue *v1 = static_cast <RealValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() < v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::REAL){
		RealValue *v1 = static_cast <RealValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		if(v2->getValue() < v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	} else {
		cout << "ERRO EM TEMPO DE EXECUCAO! Matando aplicacao...\n";
		exit(EXIT_SUCCESS);
	}
			
	delete value1;
	delete value2;

}

void Interpreter::visit(LessEqualThen *belet){
	belet->LessEqualThen::getExp()->accept(this);
	belet->LessEqualThen::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INTEGER && value2->getType() == Value::INTEGER){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() <= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::INTEGER && value2->getType() == Value::REAL){
		IntValue *v1 = static_cast <IntValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		if(v2->getValue() <= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::INTEGER){
		RealValue *v1 = static_cast <RealValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() <= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::REAL){
		RealValue *v1 = static_cast <RealValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		if(v2->getValue() <= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	} else {
		cout << "ERRO EM TEMPO DE EXECUCAO! Matando aplicacao...\n";
		exit(EXIT_SUCCESS);
	}
			
	delete value1;
	delete value2;

}

void Interpreter::visit(GreaterThen *begt){
	begt->GreaterThen::getExp()->accept(this);
	begt->GreaterThen::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INTEGER && value2->getType() == Value::INTEGER){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() > v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::INTEGER && value2->getType() == Value::REAL){
		IntValue *v1 = static_cast <IntValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		if(v2->getValue() > v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::INTEGER){
		RealValue *v1 = static_cast <RealValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() > v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::REAL){
		RealValue *v1 = static_cast <RealValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		if(v2->getValue() > v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	} else {
		cout << "ERRO EM TEMPO DE EXECUCAO! Matando aplicacao...\n";
		exit(EXIT_SUCCESS);
	}
			
	delete value1;
	delete value2;

}

void Interpreter::visit(GreaterEqualThen *beget){
	beget->GreaterEqualThen::getExp()->accept(this);
	beget->GreaterEqualThen::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INTEGER && value2->getType() == Value::INTEGER){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() >= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::INTEGER && value2->getType() == Value::REAL){
		IntValue *v1 = static_cast <IntValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		if(v2->getValue() >= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::INTEGER){
		RealValue *v1 = static_cast <RealValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() >= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::REAL && value2->getType() == Value::REAL){
		RealValue *v1 = static_cast <RealValue *> (value1);
		RealValue *v2 = static_cast <RealValue *> (value2);
		if(v2->getValue() >= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	} else {
		cout << "ERRO EM TEMPO DE EXECUCAO! Matando aplicacao...\n";
		exit(EXIT_SUCCESS);
	}
			
	delete value1;
	delete value2;

}

void ExpBinPlus::accept(Visitor *v){ 
	v->visit(this); 
}

void ExpBinMinus::accept(Visitor *v){ 
	v->visit(this); 
}

void FactorMul::accept(Visitor *v){ 
	v->visit(this); 
}

void FactorDiv::accept(Visitor *v){ 
	v->visit(this); 
}

void ExpUnPlus::accept(Visitor *v){ 
	v->visit(this); 
}

void ExpUnMinus::accept(Visitor *v){ 
	v->visit(this); 
}

void IntValue::accept(Visitor *v){ 
	v->visit(this); 
}

void RealValue::accept(Visitor *v){ 
	v->visit(this); 
}

void Identifier::accept(Visitor *v){ 
	v->visit(this); 
}

void Atribuicao::accept(Visitor *v){ 
	v->visit(this); 
}

void If::accept(Visitor *v){
	v->visit(this);
}

void ExpIg::accept(Visitor *v){
	v->visit(this);
}

void ExpDif::accept(Visitor *v){
	v->visit(this);
}

void LessThen::accept(Visitor *v){
	v->visit(this);
}

void LessEqualThen::accept(Visitor *v){
	v->visit(this);
}

void GreaterThen::accept(Visitor *v){
	v->visit(this);
}

void GreaterEqualThen::accept(Visitor *v){
	v->visit(this);
}

void CommandsCommand::accept(Visitor *v){
	v->visit(this);
} 


void BlockCommands::accept(Visitor *v){
	v->visit(this);
} 

void FuncDefinitions::accept(Visitor *v){
	v->visit(this);
} 

void VarVar::accept(Visitor *v){
	v->visit(this);
} 

void Vardeclaration::accept(Visitor *v){
	v->visit(this);
} 
