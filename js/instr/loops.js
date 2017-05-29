// loops.js


// <for> -> for <identifier> <for-start> 
function For(subtree) {
	identifier1 = subtree.child[1].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <for-start>
	return;
}


// <for-start> -> = <arithmetic> to <arithmetic> do <endl> <loop-end> 
function ForStartA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <arithmetic>
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <arithmetic>
	CMD_SEQUENCE.push([Dispatch, subtree.child[6]]);	// <loop-end>
	return;
}


// <for-start> -> = <arithmetic> to <arithmetic> step <arithmetic> do <endl> <loop-end> 
function ForStartB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <arithmetic>
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <arithmetic>
	CMD_SEQUENCE.push([Dispatch, subtree.child[5]]);	// <arithmetic>
	CMD_SEQUENCE.push([Dispatch, subtree.child[8]]);	// <loop-end>
	return;
}


// <for-start> -> in <final> do <endl> <loop-end> 
function ForStartC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <final>
	CMD_SEQUENCE.push([Dispatch, subtree.child[4]]);	// <loop-end>
	return;
}


// <while> -> while <condition> do <endl> <loop-end> 
function WhileA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <condition>
	CMD_SEQUENCE.push([Dispatch, subtree.child[4]]);	// <loop-end>
	return;
}


// <while> -> do <endl> <block> loop while <condition> 
function WhileB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <block>
	CMD_SEQUENCE.push([Dispatch, subtree.child[5]]);	// <condition>
	return;
}


// <loop-end> -> <block> loop 
function LoopEnd(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <block>
	return;
}

