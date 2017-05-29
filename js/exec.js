/* asynchronous function evaluator */
var RUN_STEPS = 1000;
var CMD_SEQUENCE = [];

function RunProgram(AST) {
    CMD_SEQUENCE.push([Dispatch, AST])
    RunAsync();
}

function ProgramTerm() {
    console.log("Program is complete.");
}

function RunAsync() {
    var steps = RUN_STEPS;
    while (steps-- && CMD_SEQUENCE.length > 0) {
        var command = CMD_SEQUENCE.unshift();
        var fun = command[0];
        var args = command.slice(1);
        fun.call(this, args);
    }
    if (CMD_SEQUENCE.length > 0) {
        setTimeout(RunAsync, 0);
    } else {
        ProgramTerm();
    }
}

/* parser generator ast walk */
var _DISPATCH;
function Dispatch(subtree) {
	var rule = subtree.rule;
	if (_DISPATCH[rule]) {
		return _DISPATCH[rule](subtree);
	}
}


/* function table */
_DISPATCH = [null, Program, TopLevelBlockA, null, IdentifierListA, IdentifierListB, null, null, TopLevelStmtA, TopLevelStmtB, TopLevelStmtC, TopLevelStmtD, BlockA, null, StmtA, StmtB, StmtC, StmtD, StmtE, StmtF, StmtG, StmtH, StmtI, StmtJ, StmtK, StmtL, StmtM, StmtN, StmtO, null, ClassA, ClassB, ClassBody, ClassBlockA, null, ClassStmtA, ClassStmtB, ClassStmtC, ClassStmtD, null, FunctionA, FunctionB, FunctionDef, ParametersA, ParametersB, null, null, ArgumentsB, ExprListA, ExprListB, If, ElseifA, ElseifB, ElseifC, For, ForStartA, ForStartB, ForStartC, WhileA, WhileB, LoopEnd, LetBlock, BindingsA, BindingsB, Binding, TryBlock, CatchBlockA, CatchBlockB, AssignmentA, AssignmentB, SelfAssignmentA, SelfAssignmentB, SelfAssignmentC, SelfAssignmentD, SelfAssignmentE, SelfAssignmentF, LValueA, LValueB, LValueC, Expr, ConditionA, ConditionB, ConditionC, LogicA, LogicB, ComparisonA, ComparisonB, ComparisonC, ComparisonD, ComparisonE, ComparisonF, ComparisonG, ComparisonH, ComparisonI, ArithmeticA, ArithmeticB, ArithmeticC, TermA, TermB, TermC, TermD, FactorA, FactorB, FactorC, ValueA, ValueB, ValueC, ValueD, ValueE, PrimitiveA, PrimitiveB, PrimitiveC, PrimitiveD, PrimitiveE, ObjectA, ObjectB, ObjectC, ArrayInitA, ArrayInitB, DictionaryInitA, DictionaryInitB, DictionaryEntry];

