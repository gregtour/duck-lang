// exception.js



// <try-block> -> try <endl> <block> <catch-block> 
function TryBlock(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <block>
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <catch-block>
	return;
}


// <catch-block> -> catch <l-value> <endl> <block> done 
function CatchBlockA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <l-value>
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <block>
	return;
}


// <catch-block> -> done 
function CatchBlockB(subtree) {
	return;
}


