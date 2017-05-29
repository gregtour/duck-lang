// function.js

// <function> -> func <identifier> <function-def> 
function FunctionA(subtree) {
	identifier1 = subtree.child[1].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <function-def>
	return;
}


// <function> -> func <string> <function-def> 
function FunctionB(subtree) {
	string1 = subtree.child[1].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <function-def>
	return;
}


// <function-def> -> <parameters> <endl> <block> endfunc 
function FunctionDef(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <parameters>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <block>
	return;
}


// <parameters> -> ( <identifier-list> ) 
function ParametersA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <identifier-list>
	return;
}


// <parameters> -> ( ) 
function ParametersB(subtree) {
	return;
}


// <arguments> -> <expr-list> 
function ArgumentsB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <expr-list>
	return;
}


