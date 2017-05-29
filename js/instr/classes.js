// classes.js



// <top-level-stmt> -> module <identifier> <endl> <block> endmodule <endl> 
function TopLevelStmtC(subtree) {
	identifier1 = subtree.child[1].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <block>
	return;
}



// <class> -> class <identifier> <endl> <class-body> 
function ClassA(subtree) {
	identifier1 = subtree.child[1].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <class-body>
	return;
}


// <class> -> class <identifier> extends <identifier-list> <endl> <class-body> 
function ClassB(subtree) {
	identifier1 = subtree.child[1].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <identifier-list>
	CMD_SEQUENCE.push([Dispatch, subtree.child[5]]);	// <class-body>
	return;
}


// <class-body> -> <class-block> endclass 
function ClassBody(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <class-block>
	return;
}


// <class-block> -> <class-stmt> <class-block> 
function ClassBlockA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <class-stmt>
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <class-block>
	return;
}


// <class-stmt> -> static <assignment> <endl> 
function ClassStmtA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <assignment>
	return;
}


// <class-stmt> -> static <function> <endl> 
function ClassStmtB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <function>
	return;
}


// <class-stmt> -> <assignment> <endl> 
function ClassStmtC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <assignment>
	return;
}


// <class-stmt> -> <function> <endl> 
function ClassStmtD(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <function>
	return;
}


