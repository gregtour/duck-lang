// datastruct.js


// <value> -> <primitive> 
function ValueA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <primitive>
	return;
}


// <primitive> -> true 
function PrimitiveA(subtree) {
	return;
}


// <primitive> -> false 
function PrimitiveB(subtree) {
	return;
}


// <primitive> -> <integer> 
function PrimitiveC(subtree) {
	integer1 = parseInt(subtree.child[0].string);
	return;
}


// <primitive> -> <float> 
function PrimitiveD(subtree) {
	float1 = parseFloat(subtree.child[0].string);
	return;
}


// <primitive> -> <string> 
function PrimitiveE(subtree) {
	string1 = subtree.child[0].string;
	return;
}


// <object> -> [ <optendl> ] 
function ObjectA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <optendl>
	return;
}


// <object> -> [ <optendl> <array-init> 
function ObjectB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <optendl>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <array-init>
	return;
}


// <object> -> [ <optendl> <dictionary-init> 
function ObjectC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <optendl>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <dictionary-init>
	return;
}


// <array-init> -> <expr> , <optendl> <array-init> 
function ArrayInitA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <expr>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <optendl>
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <array-init>
	return;
}


// <array-init> -> <expr> <optendl> ] 
function ArrayInitB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <expr>
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <optendl>
	return;
}


// <dictionary-init> -> <dictionary-entry> , <optendl> <dictionary-init> 
function DictionaryInitA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <dictionary-entry>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <optendl>
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <dictionary-init>
	return;
}


// <dictionary-init> -> <dictionary-entry> ] 
function DictionaryInitB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <dictionary-entry>
	return;
}


// <dictionary-entry> -> <identifier> : <optendl> <expr> 
function DictionaryEntry(subtree) {
	identifier1 = subtree.child[0].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <optendl>
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <expr>
	return;
}
