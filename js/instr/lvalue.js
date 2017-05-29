// lvalue.js



// <l-value> -> <identifier> 
function LValueA(subtree) {
	identifier1 = subtree.child[0].string;
	return;
}




// <l-value> -> <l-value> [ <arithmetic> ] 
function LValueB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <l-value>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <arithmetic>
	return;
}


// <l-value> -> <l-value> . <identifier> 
function LValueC(subtree) {
	identifier1 = subtree.child[2].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <l-value>
	return;
}



// <value> -> <l-value> 
function ValueB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <l-value>
	return;
}


// <value> -> <l-value> ( <arguments> ) 
function ValueC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <l-value>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <arguments>
	return;
}


// <value> -> new <l-value> ( <arguments> ) 
function ValueD(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <l-value>
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <arguments>
	return;
}


