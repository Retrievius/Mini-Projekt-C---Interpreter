grammar cpp;

// Parser

start
    : (topLevelDecl | stmt)* EOF
    ;

topLevelDecl
    : classDecl
    | fnDecl
    ;

//  Klassen

classDecl
    : 'class' ID (':' 'public' ID)? classBody
    ;

classBody
    : '{' accessSpec? classMember* '}'
    ;

accessSpec
    : 'public' ':'
    ;

classMember
    : fieldDecl
    | methodDecl
    | ctorDecl
    ;

fieldDecl
    : type ID ';'
    ;

ctorDecl
    : ID '(' params? ')' block
    ;

methodDecl
    : ('virtual')? type ID '(' params? ')' block
    ;

//  Funktionen

fnDecl
    : type ID '(' params? ')' block
    ;

params
    : param (',' param)*
    ;

param
    : type AMP? ID
    ;

//  Statements

stmt
    : vardecl
    | assign
    | exprStmt
    | block
    | whileStmt
    | ifStmt
    | returnStmt
    ;

vardecl
    : type AMP? ID ('=' expr)? ';'
    ;

assign
    : postfixExpr '=' expr ';'
    ;

exprStmt
    : expr ';'
    ;

block
    : '{' stmt* '}'
    ;

whileStmt
    : 'while' '(' expr ')' stmt
    ;

ifStmt
    : 'if' '(' expr ')' stmt ('else' stmt)?
    ;

returnStmt
    : 'return' expr? ';'
    ;
//  Ausdrücke

expr
    : assignExpr
    ;

assignExpr
    : logicalOrExpr
    ;

logicalOrExpr
    : logicalAndExpr ('||' logicalAndExpr)*
    ;

logicalAndExpr
    : equalityExpr ('&&' equalityExpr)*
    ;

equalityExpr
    : relationalExpr (('==' | '!=') relationalExpr)*
    ;

relationalExpr
    : additiveExpr (('<' | '>' | '<=' | '>=') additiveExpr)*
    ;

additiveExpr
    : multiplicativeExpr (('+' | '-') multiplicativeExpr)*
    ;

multiplicativeExpr
    : unaryExpr (('*' | '/' | '%') unaryExpr)*
    ;


unaryExpr
    : '!' unaryExpr
    | ('+'|'-') unaryExpr
    | postfixExpr
    ;

postfixExpr
    : primaryExpr (memberAccess | call)*
    ;

memberAccess
    : '.' ID
    ;

call
    : '(' args? ')'
    ;

args
    : expr (',' expr)*
    ;

primaryExpr
    : literal
    | ID
    | '(' expr ')'
    ;

//  Literale

literal
    : NUMBER
    | STRING
    | CHAR
    | 'true'
    | 'false'
    ;
//  Typen

type
    : baseType
    ;

baseType
    : 'int'
    | 'bool'
    | 'char'
    | 'string'
    | 'void'
    | ID
    ;

//  Lexer-Regeln

ID      : [a-zA-Z_][a-zA-Z0-9_]* ;
NUMBER  : [0-9]+ ;

AMP     : '&' ;

CHAR
    : '\'' ( ~['\\] | '\\' . ) '\''
    ;

STRING
    : '"' ( ~["\\] | '\\' . )* '"'
    ;

// Kommentare + Präprozessor wie Kommentar
COMMENT_LINE : '//' ~[\r\n]* -> skip ;
COMMENT_BLOCK: '/*' .*? '*/' -> skip ;
PREPROC      : '#' ~[\r\n]* -> skip ;

WS : [ \t\r\n]+ -> skip ;
