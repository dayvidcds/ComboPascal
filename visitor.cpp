#include "visitor.hpp"

void Interpreter::visit(IntValue *v){ 
	stack_.push_back(v); 
}

void Interpreter::visit(RealValue *v){ 
	stack_.push_back(v); 
}

void Interpreter::visit(Identifier *v){
		Context::TypeTable &typeTable = Context::getContext().getTable();

		if(typeTable.find(v->getName()) == typeTable.end()){
			stack_.push_back(v);
		}else{
			stack_.push_back(typeTable[v->getName()]);
		}
}

void Interpreter::visit(Atribuicao *atrib){
		atrib->Atribuicao::getExp()->accept(this);
		atrib->Atribuicao::getIden()->accept(this);
		
		Context::TypeTable &typeTable = Context::getContext().getTable();
		
		Identifier *identifier = static_cast <Identifier *> (stack_.back());
		stack_.pop_back();
		typeTable[identifier->getName()] = stack_.back();
		stack_.pop_back();
}

void Interpreter::visit(ExpBinPLUS *expBinPlus){
	expBinPlus->ExpBinPLUS::getExp()->accept(this);
	expBinPlus->ExpBinPLUS::getFactor()->accept(this);
	Value *firstVal = stack_.back();
	stack_.pop_back();
	Value *secondVal = stack_.back();
	stack_.pop_back();

	printf("entrou");
		
	if(firstVal->getType() == Value::INTEGER && secondVal->getType() == Value::INTEGER){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		IntValue *val2 = static_cast <IntValue *> (secondVal);
		stack_.push_back(new IntValue(val1->getValue() + val2->getValue()));
		
	}else if(firstVal->getType() == Value::INTEGER && secondVal->getType() == Value::REAL){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		RealValue *val2 = static_cast <RealValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() + val2->getValue()));
		
	}else if(firstVal->getType() == Value::REAL && secondVal->getType() == Value::INTEGER){
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

void Interpreter::visit(ExpBinMINUS *expBinMinus){
	expBinMinus->ExpBinMINUS::getExp()->accept(this);
	expBinMinus->ExpBinMINUS::getFactor()->accept(this);
	Value *secondVal = stack_.back();
	stack_.pop_back();
	Value *firstVal = stack_.back();
	stack_.pop_back(); 

	if(firstVal->getType() == Value::INTEGER && secondVal->getType() == Value::INTEGER){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		IntValue *val2 = static_cast <IntValue *> (secondVal);
		stack_.push_back(new IntValue(val1->getValue() - val2->getValue()));
	
	}else if(firstVal->getType() == Value::INTEGER && secondVal->getType() == Value::REAL){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		RealValue *val2 = static_cast <RealValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() - val2->getValue()));
	
	}else if(firstVal->getType() == Value::REAL && secondVal->getType() == Value::INTEGER){
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
	factorMul->FactorMul::getExpUn()->accept(this);
	factorMul->FactorMul::getFactor()->accept(this);
	Value *firstVal = stack_.back();
	stack_.pop_back();
	Value *secondVal = stack_.back();
	stack_.pop_back();

	if(firstVal->getType() == Value::INTEGER && secondVal->getType() == Value::INTEGER){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		IntValue *val2 = static_cast <IntValue *> (secondVal);
		stack_.push_back(new IntValue(val1->getValue() * val2->getValue()));
	
	}else if(firstVal->getType() == Value::INTEGER && secondVal->getType() == Value::REAL){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		RealValue *val2 = static_cast <RealValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() * val2->getValue()));
	
	}else if(firstVal->getType() == Value::REAL && secondVal->getType() == Value::INTEGER){
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
	factorDiv->FactorDiv::getExpUn()->accept(this);
	factorDiv->FactorDiv::getFactor()->accept(this);
	Value *firstVal = stack_.back();
	stack_.pop_back();
	Value *secondVal = stack_.back();
	stack_.pop_back();

	if(firstVal->getType() == Value::INTEGER && secondVal->getType() == Value::INTEGER){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		IntValue *val2 = static_cast <IntValue *> (secondVal);
		stack_.push_back(new IntValue(val1->getValue() / val2->getValue()));
	
	}else if(firstVal->getType() == Value::INTEGER && secondVal->getType() == Value::REAL){
		IntValue *val1 = static_cast <IntValue *> (firstVal);
		RealValue *val2 = static_cast <RealValue *> (secondVal);
		stack_.push_back(new RealValue(val1->getValue() / val2->getValue()));
	
	}else if(firstVal->getType() == Value::REAL && secondVal->getType() == Value::INTEGER){
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

void Interpreter::visit(ExpUnPLUS *expUnPlus){
	expUnPlus->ExpUnPLUS::getValue()->accept(this);
	Value *firstValue = stack_.back();
	stack_.pop_back();

	if(firstValue->getType() == Value::INTEGER){
		IntValue *v = static_cast <IntValue *> (firstValue);
	} else if(firstValue->getType() == Value::REAL){
		RealValue *v = static_cast <RealValue *> (firstValue);
	}
		
	delete firstValue;
}
void Interpreter::visit(ExpUnMINUS *expUnMinus){
	expUnMinus->ExpUnMINUS::getValue()->accept(this);
	Value*firstValue = stack_.back();
	stack_.pop_back();

	if(firstValue->getType() == Value::INTEGER){
		IntValue *v = static_cast <IntValue *> (firstValue);
	} else if(firstValue->getType() == Value::REAL){
		RealValue *v = static_cast <RealValue *> (firstValue);
	}

	delete firstValue;
}

void Interpreter::visit(Parenteses *parenteses){
	parenteses->getExp()->accept(this);
}

void ExpBinPLUS::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void ExpBinMINUS::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void FactorMul::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void FactorDiv::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void ExpUnPLUS::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void ExpUnMINUS::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

/*
void ExpUnLog::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void ExpUnExp::accept(Visitor *visitor){ 
	visitor->visit(this); 
}*/

void IntValue::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void RealValue::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void Identifier::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void Parenteses::accept(Visitor *visitor){ 
	visitor->visit(this); 
}

void Atribuicao::accept(Visitor *visitor){ 
	visitor->visit(this); 
}