// let.js


// <let-block> -> let <bindings> <endl> begin <endl> <block> end 
function LetBlock(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <bindings>
	CMD_SEQUENCE.push([Dispatch, subtree.child[5]]);	// <block>
	return;
}


// <bindings> -> <binding> , <optendl> <bindings> 
function BindingsA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <binding>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <optendl>
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <bindings>
	return;
}


// <bindings> -> <binding> 
function BindingsB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <binding>
	return;
}


// <binding> -> <identifier> = <expr> 
function Binding(subtree) {
	identifier1 = subtree.child[0].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <expr>
	return;
}


