// ops.js -- operations



// <expr> -> <condition> 
function Expr(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <condition>
	return;
}


// <condition> -> <condition> and <logic> 
function ConditionA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <condition>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <logic>
	return;
}


// <condition> -> <condition> or <logic> 
function ConditionB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <condition>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <logic>
	return;
}


// <condition> -> <logic> 
function ConditionC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <logic>
	return;
}


// <logic> -> not <comparison> 
function LogicA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <comparison>
	return;
}


// <logic> -> <comparison> 
function LogicB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <comparison>
	return;
}


// <comparison> -> <comparison> == <arithmetic> 
function ComparisonA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <comparison>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <arithmetic>
	return;
}


// <comparison> -> <comparison> != <arithmetic> 
function ComparisonB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <comparison>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <arithmetic>
	return;
}


// <comparison> -> <comparison> < <arithmetic> 
function ComparisonC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <comparison>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <arithmetic>
	return;
}


// <comparison> -> <comparison> > <arithmetic> 
function ComparisonD(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <comparison>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <arithmetic>
	return;
}


// <comparison> -> <comparison> <= <arithmetic> 
function ComparisonE(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <comparison>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <arithmetic>
	return;
}


// <comparison> -> <comparison> >= <arithmetic> 
function ComparisonF(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <comparison>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <arithmetic>
	return;
}


// <comparison> -> <final> is <l-value> 
function ComparisonG(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <final>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <l-value>
	return;
}


// <comparison> -> <final> is not <l-value> 
function ComparisonH(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <final>
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <l-value>
	return;
}


// <comparison> -> <arithmetic> 
function ComparisonI(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <arithmetic>
	return;
}


// <arithmetic> -> <arithmetic> + <term> 
function ArithmeticA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <arithmetic>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <term>
	return;
}


// <arithmetic> -> <arithmetic> - <term> 
function ArithmeticB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <arithmetic>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <term>
	return;
}


// <arithmetic> -> <term> 
function ArithmeticC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <term>
	return;
}


// <term> -> <term> * <factor> 
function TermA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <term>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <factor>
	return;
}


// <term> -> <term> / <factor> 
function TermB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <term>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <factor>
	return;
}


// <term> -> <term> mod <factor> 
function TermC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <term>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <factor>
	return;
}


// <term> -> <factor> 
function TermD(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <factor>
	return;
}


// <factor> -> - <value> 
function FactorA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <value>
	return;
}


// <factor> -> ! <value> 
function FactorB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <value>
	return;
}



// <factor> -> <value> 
function FactorC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <value>
	return;
}
