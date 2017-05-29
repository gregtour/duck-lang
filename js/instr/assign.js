// assign.js


// <assignment> -> <l-value> = <expr> 
function AssignmentA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <l-value>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <expr>
	return;
}


// <assignment> -> <l-value> = <object> 
function AssignmentB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <l-value>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <object>
	return;
}


// <self-assignment> -> <l-value> += <arithmetic> 
function SelfAssignmentA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <l-value>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <arithmetic>
	return;
}


// <self-assignment> -> <l-value> -= <arithmetic> 
function SelfAssignmentB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <l-value>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <arithmetic>
	return;
}


// <self-assignment> -> <l-value> *= <arithmetic> 
function SelfAssignmentC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <l-value>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <arithmetic>
	return;
}


// <self-assignment> -> <l-value> /= <arithmetic> 
function SelfAssignmentD(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <l-value>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <arithmetic>
	return;
}


// <self-assignment> -> <l-value> ++ 
function SelfAssignmentE(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <l-value>
	return;
}


// <self-assignment> -> <l-value> -- 
function SelfAssignmentF(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <l-value>
	return;
}


