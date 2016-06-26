#include "visitor.hpp"

void Interpreter::visit(IntValue *v){ 
	stack_.push_back(v); 
}

void Interpreter::visit(RealValue *v){ 
	stack_.push_back(v); 
}

void Interpreter::visit(CommandsCommand *cmd){
	cmd->CommandsCommand::getCommands()->accept(this);
	cmd->CommandsCommand::getCommand()->accept(this);
}

void Interpreter::visit(Identifier *v){
		Context::TypeTable &t = Context::getContext().getTable();

		if(t.find(v->getValue()) == t.end()){
			stack_.push_back(v);
		}else{
			stack_.push_back(t[v->getValue()]);
		}
}


void Interpreter::visit(If *i){
	i->If::getExp()->accept(this);

	IntValue *v1 = static_cast<IntValue *>(stack_.back());

	if(v1->getValue()){
		i->If::getExpList()->accept(this);
	}

}

void Interpreter::visit(Atribuicao *a){
		a->Atribuicao::getExp()->accept(this);
		a->Atribuicao::getIdValue()->accept(this);
		
		Context::TypeTable &t = Context::getContext().getTable();
		
		Identifier *valueId = static_cast <Identifier *> (stack_.back());
		stack_.pop_back();
		t[valueId->getValue()] = stack_.back();
		stack_.pop_back();
}

void Interpreter::visit(ExpBinPlus *bep){
	bep->ExpBinPlus::getExp()->accept(this);
	bep->ExpBinPlus::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INTEGER && value2->getType() == Value::INTEGER){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
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
	}
	
	printf("%d\n", static_cast<IntValue*>(stack_.back())->getValue());

	delete value1;
	delete value2;
}

void Interpreter::visit(ExpBinMinus *bem){
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
	}
		
	printf("%d\n", static_cast<IntValue*>(stack_.back())->getValue());
	
	delete value1;
	delete value2;
}

void Interpreter::visit(FactorMul *fm){
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
	}
	
	printf("%d\n", static_cast<IntValue*>(stack_.back())->getValue());

	delete value1;
	delete value2;
}

void Interpreter::visit(FactorDiv *fd){
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

void CommandsCommand::accept(Visitor *v){
	v->visit(this);
} 