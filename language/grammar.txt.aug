; abstract syntax tree root
<program> ::= <stmt list>

; left recursive list of statements
<stmt list> ::= <stmt list> <stmt>
<stmt list> ::= <epsilon>

; valid statments
<stmt> ::= <endl>
<stmt> ::= <expr> <endl>
<stmt> ::= <function def> <endl>
<stmt> ::= <if> <endl>
<stmt> ::= <if else> <endl>
<stmt> ::= <for loop> <endl>
<stmt> ::= <while loop> <endl>
<stmt> ::= return <expr> <endl>

; function prototype
<function def> ::= function <identifier> <parameters> <endl> <stmt list> end
<parameters> ::= <epsilon>
<parameters> ::= ( )
<parameters> ::= (<param decl>)

; left associative parameter declarations
<param decl> ::= <identifier>
<param decl> ::= <param decl>, <identifier>

; if or if else declaration
<if> ::= if <expr> then <endl> <stmt list> end
<if else> ::= if <expr> then <endl> <stmt list> else <endl> <stmt list> end

; loops
<for loop> ::= for <identifier> = <expr> to <expr> do <endl> <stmt list> loop
<while loop> ::= while <expr> do <endl> <stmt list> loop

; assignment
<expr> ::= <lvalue> = <expr>
<lvalue> ::= <identifier>
<lvalue> ::= <array index>

;;;;;;;;;;;;;;;;;;;;;;;;;; ASSOCIATIVITY ;;;;;;;;;;;;;;;;;;;;;;;;;;

<expr> ::= <logic>
<expr> ::= <comparison>
<expr> ::= <arithmetic>
<expr> ::= <term>
<expr> ::= <factor>
<expr> ::= <final>

; left associative boolean arithmetic
<logic> ::= <logic> and <comparison>
<logic> ::= <logic> or <comparison>
<logic> ::= <logic> nor <comparison>
<logic> ::= <logic> xor <comparison>
<logic> ::= not <logic>
; highest precedent not
<logic> ::= <comparison>

; higher precedence comparison operators
<comparison> ::= <comparison> == <arithmetic>
<comparison> ::= <comparison> != <arithmetic>
<comparison> ::= <comparison> \< <arithmetic>
<comparison> ::= <comparison> > <arithmetic>
<comparison> ::= <comparison> \<= <arithmetic>
<comparison> ::= <comparison> >= <arithmetic>
<comparison> ::= <arithmetic>

; left associative addition & subtraction
<arithmetic> ::= <arithmetic> + <term>
<arithmetic> ::= <arithmetic> - <term>
<arithmetic> ::= <arithmetic> & <term>
<arithmetic> ::= <arithmetic> | <term>
<arithmetic> ::= <term>

; higher precedence multiplication & division
<term> ::= <term> * <factor>
<term> ::= <term> / <factor>
<term> ::= <factor>

; highest precedence negation
<factor> ::= -<factor>
<factor> ::= !<factor>
<factor> ::= <final>

; base terms
<final> ::= ( <expr> )
<final> ::= <boolean>
<final> ::= <integer>
<final> ::= <string>
<final> ::= <object>
<final> ::= <identifier>
<final> ::= <array index>

; object indexing
<array index> ::= <expr> . <identifier>
<array index> ::= <expr> [ <expr> ]

; function call
<call> ::= <expr> ( )
<call> ::= <expr> ( <param eval> )
<param eval> ::= <param eval>, <expr>
<param eval> ::= <expr>

; array type
<object> ::= [ ]
<object> ::= [ <array init> ]
<object> ::= [ <dictionary init> ]
<array init> ::= <object init>, <expr>
<array init> ::= <expr>

; associative array type
<dictionary init> ::= <dictionary init>, <identifier> : <expr>
<dictionary init> ::= <identifier> : <expr>

; boolean type
<boolean> ::= true
<boolean> ::= false
<boolean> ::= tralse
