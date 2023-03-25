#include <iostream>
#include <vector>
#include <llvm/IR/Value.h>

class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NVariableDeclaration*> VariableList;

class Node {
public:
	virtual ~Node() {}
	virtual llvm::Value* codeGen(CodeGenContext& context) { return NULL; }
};

class NExpression : public Node {
};

class NStatement : public Node {
};

class NInteger : public NExpression {
public:
	long long value;
	NInteger(long long value) : value(value) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NDouble : public NExpression {
public:
	double value;
	NDouble(double value) : value(value) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NString : public NExpression {
public:
	std::string value;
	NString(const std::string& value) : value(value) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NBool : public NExpression {
public:
	bool value;
	NBool(bool value) : value(value) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NIdentifier : public NExpression {
public:
	std::string name;
	NIdentifier(const std::string& name) : name(name) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NMethodCall : public NExpression {
public:
	const NIdentifier& id;
	ExpressionList arguments;
	NMethodCall(const NIdentifier& id, ExpressionList& arguments) :
		id(id), arguments(arguments) { }
	NMethodCall(const NIdentifier& id) : id(id) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NArray : public NExpression {
public:
	ExpressionList items;
	NArray(ExpressionList& items) : items(items) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NArrayRead : public NExpression {
public:
	std::string arr;
	NExpression& index;
	NArrayRead(const std::string& arr, NExpression& index) : 
		arr(arr), index(index) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NArrayWrite : public NExpression {
public:
	std::string arr;
	NExpression& index;
	NExpression& assignment;
	int op;
	NArrayWrite(const std::string& arr, NExpression& index, NExpression& assignment) : 
		arr(arr), index(index), assignment(assignment) { }
	NArrayWrite(const std::string& arr, NExpression& index, int op, NExpression& assignment) : 
		arr(arr), index(index), assignment(assignment), op(op) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NBinaryOperator : public NExpression {
public:
	int op;
	NExpression& lhs;
	NExpression& rhs;
	NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
		lhs(lhs), rhs(rhs), op(op) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NUnaryOperator : public NExpression {
public:
	int op;
	NExpression& expr;
	NUnaryOperator(int op, NExpression& expr) :
		op(op), expr(expr) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NAssignment : public NExpression {
public:
	int op;
	NIdentifier& lhs;
	NExpression& rhs;
	NAssignment(NIdentifier& lhs, NExpression& rhs) : 
		lhs(lhs), rhs(rhs) { }
	NAssignment(NIdentifier& lhs, int op, NExpression& rhs) : 
		lhs(lhs), rhs(rhs), op(op) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NBlock : public NExpression {
public:
	StatementList statements;
	NBlock() { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NExpressionStatement : public NStatement {
public:
	NExpression& expression;
	NExpressionStatement(NExpression& expression) : 
		expression(expression) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NReturnStatement : public NStatement {
public:
	NExpression& expression;
	NReturnStatement(NExpression& expression) : 
		expression(expression) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NVariableDeclaration : public NStatement {
public:
	const NIdentifier& type;
	NIdentifier& id;
	NExpression *assignmentExpr;
	NVariableDeclaration(const NIdentifier& type, NIdentifier& id) :
		type(type), id(id) { assignmentExpr = NULL; }
	NVariableDeclaration(const NIdentifier& type, NIdentifier& id, NExpression *assignmentExpr) :
		type(type), id(id), assignmentExpr(assignmentExpr) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NArrayDeclaration : public NStatement {
public:
	const NIdentifier& type;
	NIdentifier& id;
	NExpression *assignmentExpr;
	NArrayDeclaration(const NIdentifier& type, NIdentifier& id) :
		type(type), id(id) { assignmentExpr = NULL; }
	NArrayDeclaration(const NIdentifier& type, NIdentifier& id, NExpression *assignmentExpr) :
		type(type), id(id), assignmentExpr(assignmentExpr) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NExternDeclaration : public NStatement {
public:
    const NIdentifier& type;
    const NIdentifier& id;
    VariableList arguments;
    NExternDeclaration(const NIdentifier& type, const NIdentifier& id,
            const VariableList& arguments) :
        type(type), id(id), arguments(arguments) {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NFunctionDeclaration : public NStatement {
public:
	const NIdentifier& type;
	const NIdentifier& id;
	VariableList arguments;
	NBlock& block;
	NFunctionDeclaration(const NIdentifier& type, const NIdentifier& id, 
			const VariableList& arguments, NBlock& block) :
		type(type), id(id), arguments(arguments), block(block) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NConditional : public NStatement {
public:
	NExpression& condition;
	NBlock& thenblock;
	NBlock& elseblock;
	NConditional(NExpression& condition, NBlock& thenblock, NBlock& elseblock) :
		condition(condition), thenblock(thenblock), elseblock(elseblock) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NLoop : public NStatement {
public:
	NExpression& condition;
	NBlock& block;
	NLoop(NExpression& condition, NBlock& block) :
		condition(condition), block(block) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};