// stmt.js



// <top-level-stmt> -> import <identifier-list> <endl> 
function TopLevelStmtA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <identifier-list>
	return;
}


// <top-level-stmt> -> include <string> <endl> 
function TopLevelStmtB(subtree) {
	string1 = subtree.child[1].string;
	return;
}


// <program> -> <top-level-block> 
function Program(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <top-level-block>
	return;
}


// <top-level-block> -> <top-level-stmt> <top-level-block> 
function TopLevelBlockA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <top-level-stmt>
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <top-level-block>
	return;
}


// <top-level-stmt> -> <stmt> 
function TopLevelStmtD(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <stmt>
	return;
}


// <block> -> <stmt> <block> 
function BlockA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <stmt>
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <block>
	return;
}


// <identifier-list> -> <identifier> , <identifier-list> 
function IdentifierListA(subtree) {
	identifier1 = subtree.child[0].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <identifier-list>
	return;
}


// <identifier-list> -> <identifier> 
function IdentifierListB(subtree) {
	identifier1 = subtree.child[0].string;
	return;
}




// <expr-list> -> <expr> , <expr-list> 
function ExprListA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <expr>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <expr-list>
	return;
}


// <expr-list> -> <expr> 
function ExprListB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <expr>
	return;
}


// <value> -> ( <expr> ) 
function ValueE(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <expr>
	return;
}



// <stmt> -> <expr> <endl> 
function StmtA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <expr>
	return;
}


// <stmt> -> <assignment> <endl> 
function StmtB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <assignment>
	return;
}


// <stmt> -> <self-assignment> <endl> 
function StmtC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <self-assignment>
	return;
}


// <stmt> -> <class> <endl> 
function StmtD(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <class>
	return;
}


// <stmt> -> <function> <endl> 
function StmtE(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <function>
	return;
}


// <stmt> -> <if> <endl> 
function StmtF(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <if>
	return;
}


// <stmt> -> <for> <endl> 
function StmtG(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <for>
	return;
}


// <stmt> -> <while> <endl> 
function StmtH(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <while>
	return;
}


// <stmt> -> <let-block> <endl> 
function StmtI(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <let-block>
	return;
}


// <stmt> -> <try-block> <endl> 
function StmtJ(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <try-block>
	return;
}


// <stmt> -> return <endl> 
function StmtK(subtree) {
	return;
}


// <stmt> -> return <expr> <endl> 
function StmtL(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <expr>
	return;
}


// <stmt> -> continue <endl> 
function StmtM(subtree) {
	return;
}


// <stmt> -> break <endl> 
function StmtN(subtree) {
	return;
}


// <stmt> -> throw <expr> <endl> 
function StmtO(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <expr>
	return;
}


