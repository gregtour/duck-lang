// cond.js


// <if> -> if <condition> then <endl> <block> <elseif> 
function If(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <condition>
	CMD_SEQUENCE.push([Dispatch, subtree.child[4]]);	// <block>
	CMD_SEQUENCE.push([Dispatch, subtree.child[5]]);	// <elseif>
	return;
}


// <elseif> -> else <endl> <block> endif 
function ElseifA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <block>
	return;
}


// <elseif> -> else <if> 
function ElseifB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <if>
	return;
}


// <elseif> -> endif 
function ElseifC(subtree) {
	return;
}

