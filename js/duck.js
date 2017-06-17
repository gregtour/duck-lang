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


// <program> -> <top-level-block> 
function Program(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <top-level-block>
	return;
}


// <top-level-block> -> <top-level-stmt> <top-level-block> 
function TopLevelBlockA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <top-level-stmt>
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <top-level-block>
	return;
}


// <identifier-list> -> <identifier> , <identifier-list> 
function IdentifierListA(subtree) {
	identifier1 = subtree.child[0].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <identifier-list>
	return;
}


// <identifier-list> -> <identifier> 
function IdentifierListB(subtree) {
	identifier1 = subtree.child[0].string;
	return;
}


// <top-level-stmt> -> import <identifier-list> <endl> 
function TopLevelStmtA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <identifier-list>
	return;
}


// <top-level-stmt> -> include <string> <endl> 
function TopLevelStmtB(subtree) {
	string1 = subtree.child[1].string;
	return;
}


// <top-level-stmt> -> module <identifier> <endl> <block> endmodule <endl> 
function TopLevelStmtC(subtree) {
	identifier1 = subtree.child[1].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <block>
	return;
}


// <top-level-stmt> -> <stmt> 
function TopLevelStmtD(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <stmt>
	return;
}


// <block> -> <stmt> <block> 
function BlockA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <stmt>
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <block>
	return;
}


// <stmt> -> <expr> <endl> 
function StmtA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <expr>
	return;
}


// <stmt> -> <assignment> <endl> 
function StmtB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <assignment>
	return;
}


// <stmt> -> <self-assignment> <endl> 
function StmtC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <self-assignment>
	return;
}


// <stmt> -> <class> <endl> 
function StmtD(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <class>
	return;
}


// <stmt> -> <function> <endl> 
function StmtE(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <function>
	return;
}


// <stmt> -> <if> <endl> 
function StmtF(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <if>
	return;
}


// <stmt> -> <for> <endl> 
function StmtG(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <for>
	return;
}


// <stmt> -> <while> <endl> 
function StmtH(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <while>
	return;
}


// <stmt> -> <let-block> <endl> 
function StmtI(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <let-block>
	return;
}


// <stmt> -> <try-block> <endl> 
function StmtJ(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <try-block>
	return;
}


// <stmt> -> return <endl> 
function StmtK(subtree) {
	return;
}


// <stmt> -> return <expr> <endl> 
function StmtL(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <expr>
	return;
}


// <stmt> -> continue <endl> 
function StmtM(subtree) {
	return;
}


// <stmt> -> break <endl> 
function StmtN(subtree) {
	return;
}


// <stmt> -> throw <expr> <endl> 
function StmtO(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <expr>
	return;
}


// <class> -> class <identifier> <parameters> <class-ext> 
function Class(subtree) {
	identifier1 = subtree.child[1].string;
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <parameters>
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <class-ext>
	return;
}


// <class-ext> -> extends <identifier-list> <endl> <class-body> 
function ClassExtA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <identifier-list>
	CMD_SEQUENCE.push([Dispatch, subtree.child[3]]);	// <class-body>
	return;
}


// <class-ext> -> <endl> <class-body> 
function ClassExtB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <class-body>
	return;
}


// <class-body> -> <block> endclass 
function ClassBody(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <block>
	return;
}


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


// <expr-list> -> <expr> , <expr-list> 
function ExprListA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <expr>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <expr-list>
	return;
}


// <expr-list> -> <expr> 
function ExprListB(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <expr>
	return;
}


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


// <for-start> -> in <value> do <endl> <loop-end> 
function ForStartC(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <value>
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


// <comparison> -> <value> is <l-value> 
function ComparisonG(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <value>
	CMD_SEQUENCE.push([Dispatch, subtree.child[2]]);	// <l-value>
	return;
}


// <comparison> -> <value> is not <l-value> 
function ComparisonH(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <value>
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


// <value> -> <primitive> 
function ValueA(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[0]]);	// <primitive>
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


// <value> -> ( <expr> ) 
function ValueD(subtree) {
	CMD_SEQUENCE.push([Dispatch, subtree.child[1]]);	// <expr>
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


/* function table */
_DISPATCH = [null, Program, TopLevelBlockA, null, IdentifierListA, IdentifierListB, null, null, TopLevelStmtA, TopLevelStmtB, TopLevelStmtC, TopLevelStmtD, BlockA, null, StmtA, StmtB, StmtC, StmtD, StmtE, StmtF, StmtG, StmtH, StmtI, StmtJ, StmtK, StmtL, StmtM, StmtN, StmtO, null, Class, ClassExtA, ClassExtB, ClassBody, FunctionA, FunctionB, FunctionDef, ParametersA, ParametersB, null, null, ArgumentsB, ExprListA, ExprListB, If, ElseifA, ElseifB, ElseifC, For, ForStartA, ForStartB, ForStartC, WhileA, WhileB, LoopEnd, LetBlock, BindingsA, BindingsB, Binding, TryBlock, CatchBlockA, CatchBlockB, AssignmentA, AssignmentB, SelfAssignmentA, SelfAssignmentB, SelfAssignmentC, SelfAssignmentD, SelfAssignmentE, SelfAssignmentF, LValueA, LValueB, LValueC, Expr, ConditionA, ConditionB, ConditionC, LogicA, LogicB, ComparisonA, ComparisonB, ComparisonC, ComparisonD, ComparisonE, ComparisonF, ComparisonG, ComparisonH, ComparisonI, ArithmeticA, ArithmeticB, ArithmeticC, TermA, TermB, TermC, TermD, FactorA, FactorB, FactorC, ValueA, ValueB, ValueC, ValueD, PrimitiveA, PrimitiveB, PrimitiveC, PrimitiveD, PrimitiveE, ObjectA, ObjectB, ObjectC, ArrayInitA, ArrayInitB, DictionaryInitA, DictionaryInitB, DictionaryEntry];

