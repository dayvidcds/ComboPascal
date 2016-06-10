#include "visitor.hpp"

void Interpreter::visit(IntValue *v){ 
	stack_.push_back(v); 
}

void Interpreter::visit(RealValue *v){ 
	stack_.push_back(v); 
}

void Interpreter::visit(Identifier *v){
		Context::TypeTable &typeTable = Context::getContext().getTable();

		if(typeTable.find(v->getValue()) == typeTable.end()){
			stack_.push_back(v);
		}else{
			stack_.push_back(typeTable[v->getValue()]);
		}
}

void Interpreter::visit(Atribuicao *atrib){
		atrib->Atribuicao::getExp()->accept(this);
		atrib->Atribuicao::getIdValue()->accept(this);
		
		Context::TypeTable &typeTable = Context::getContext().getTable();
		
		Identifier *identifier = static_cast <Identifier *> (stack_.back());
		stack_.pop_back();
		typeTable[identifier->getValue()] = stack_.back();
		stack_.pop_back();
}

void Interpreter::visit(ExpBinPlus *expBinPlus){
	expBinPlus->ExpBinPlus::getExp()->accept(this);
	expBinPlus->ExpBinPlus::getFactor()->accept(this);
	Value *firstVal = stack_.back();
	stack_.pop_back();
	Value *secondVal = stack_.back();
	stack_.pop_back();

	printf("entrou");
		
	if(firstVal->getType() == Value::INT && secondVal->getType() == Value::INT){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		IntValue *val2 = static_cast <IntValue *> (secondVal);
		stack_.push_back(new IntValue(val1->getValue() + val2->getValue()));
		printf("%d", val1+val2);
		
	}else if(firstVal->getType() == Value::INT && secondVal->getType() == Value::DOUBLE){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		RealValue *val2 = static_cast <RealValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() + val2->getValue()));
		
	}else if(firstVal->getType() == Value::REAL && secondVal->getType() == Value::INT){
		RealValue *val1 = static_cast <RealValue *> (firstVal);
		IntValue *val2 = static_cast <IntValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() + val2->getValue()));
			
	}else if(firstVal->getType() == Value::REAL && secondVal->getType() == Value::REAL){
		RealValue *val1 = static_cast <RealValue *> (firstVal);
		RealValue *val2 = static_cast <RealValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() + val2->getValue()));
	}
	
	delete firstVal;
	delete secondVal;
}

void Interpreter::visit(ExpBinMinus *expBinMinus){
	expBinMinus->ExpBinMinus::getExp()->accept(this);
	expBinMinus->ExpBinMinus::getFactor()->accept(this);
	Value *secondVal = stack_.back();
	stack_.pop_back();
	Value *firstVal = stack_.back();
	stack_.pop_back(); 

	if(firstVal->getType() == Value::INT && secondVal->getType() == Value::INT){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		IntValue *val2 = static_cast <IntValue *> (secondVal);
		stack_.push_back(new IntValue(val1->getValue() - val2->getValue()));
	
	}else if(firstVal->getType() == Value::INT && secondVal->getType() == Value::REAL){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		RealValue *val2 = static_cast <RealValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() - val2->getValue()));
	
	}else if(firstVal->getType() == Value::REAL && secondVal->getType() == Value::INT){
		RealValue *val1 = static_cast <RealValue *> (firstVal);
		IntValue *val2 = static_cast <IntValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() - val2->getValue()));
		
	}else if(firstVal->getType() == Value::REAL && secondVal->getType() == Value::REAL){
		RealValue *val1 = static_cast <RealValue *> (firstVal);
		RealValue *val2 = static_cast <RealValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() - val2->getValue()));	
	}
		
	delete firstVal;
	delete secondVal;
}

void Interpreter::visit(FactorMul *factorMul){
	factorMul->FactorMul::getUnExp()->accept(this);
	factorMul->FactorMul::getFactor()->accept(this);
	Value *firstVal = stack_.back();
	stack_.pop_back();
	Value *secondVal = stack_.back();
	stack_.pop_back();

	if(firstVal->getType() == Value::INT && secondVal->getType() == Value::INT){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		IntValue *val2 = static_cast <IntValue *> (secondVal);
		stack_.push_back(new IntValue(val1->getValue() * val2->getValue()));
	
	}else if(firstVal->getType() == Value::INT && secondVal->getType() == Value::REAL){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		RealValue *val2 = static_cast <RealValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() * val2->getValue()));
	
	}else if(firstVal->getType() == Value::REAL && secondVal->getType() == Value::INT){
		RealValue *val1 = static_cast <RealValue *> (firstVal);
		IntValue *val2 = static_cast <IntValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() * val2->getValue()));
	
	}else if(firstVal->getType() == Value::REAL && secondVal->getType() == Value::REAL){
		RealValue *val1 = static_cast <RealValue *> (firstVal);
		RealValue *val2 = static_cast <RealValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() * val2->getValue()));
	}

	delete firstVal;
	delete secondVal;
}

void Interpreter::visit(FactorDiv *factorDiv){
	factorDiv->FactorDiv::getUnExp()->accept(this);
	factorDiv->FactorDiv::getFactor()->accept(this);
	Value *firstVal = stack_.back();
	stack_.pop_back();
	Value *secondVal = stack_.back();
	stack_.pop_back();

	if(firstVal->getType() == Value::INT && secondVal->getType() == Value::INT){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		IntValue *val2 = static_cast <IntValue *> (secondVal);
		stack_.push_back(new IntValue(val1->getValue() / val2->getValue()));
	
	}else if(firstVal->getType() == Value::INT && secondVal->getType() == Value::REAL){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		RealValue *val2 = static_cast <RealValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() / val2->getValue()));
	
	}else if(firstVal->getType() == Value::REAL && secondVal->getType() == Value::INT){
		RealValue *val1 = static_cast <RealValue *> (firstVal);
		IntValue *val2 = static_cast <IntValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() / val2->getValue()));
	
	}else if(firstVal->getType() == Value::REAL && secondVal->getType() == Value::REAL){
		RealValue *val1 = static_cast <RealValue *> (firstVal);
		RealValue *val2 = static_cast <RealValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() / val2->getValue()));
	}
		
	delete firstVal;
	delete secondVal;
}

void Interpreter::visit(ExpUnPlus *expUnPlus){
	expUnPlus->ExpUnPlus::getValue()->accept(this);
	Value *firstValue = stack_.back();
	stack_.pop_back();

	if(firstValue->getType() == Value::INT){
		IntValue *v = static_cast <IntValue *> (firstValue);
	} else if(firstValue->getType() == Value::REAL){
		RealValue *v = static_cast <RealValue *> (firstValue);
	}
		
	delete firstValue;
}
void Interpreter::visit(ExpUnMinus *expUnMinus){
	expUnMinus->ExpUnMinus::getValue()->accept(this);
	Value*firstValue = stack_.back();
	stack_.pop_back();

	if(firstValue->getType() == Value::INT){
		IntValue *v = static_cast <IntValue *> (firstValue);
	} else if(firstValue->getType() == Value::REAL){
		RealValue *v = static_cast <RealValue *> (firstValue);
	}

	delete firstValue;
}

void Interpreter::visit(LparExpRpar *lparExpRpar){
	lparExpRpar->getExp()->accept(this);
}


void ExpBinPlus::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void ExpBinMinus::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void FactorMul::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void FactorDiv::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void ExpUnPlus::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void ExpUnMinus::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

/*
void ExpUnLog::accept(Visitor *visitor){ 
	visitor->visit(this); 
}
*/
void ExpUnExp::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void IntValue::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void RealValue::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void Identifier::accept(Visitor *visitor){ 
	visitor->visit(this); 
}
/*
void LparExpRpar::accept(Visitor *visitor){ 
	visitor->visit(this); 
}
*/
void Atribuicao::accept(Visitor *visitor){ 
	visitor->visit(this); 
}