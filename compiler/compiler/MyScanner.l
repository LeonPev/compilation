%option yylineno
%{
#include "Scanner.h"
%}

numberHelper		[0-9]+
suffix              (","|";"|":"|\r|\n|" "|"]")
comma 				","
newLine 			"\n"
add 				"+"
multiply 			"*"
openBrackets 		"["
closeBrackets 		"]"
semiColon 			";"
colon 				":"
EmptySpaceError     "_"
leftSmaller 		<
leftSmallerOrEquel 	<=
equel 				==  
notEquel 			!=
rightSmaller 		>
rightSmallerOrEquel >=
unsignedNum 		[0-9]+{suffix}
number   			{numberHelper}"."{numberHelper}
Program 			program
End 				end
_if 				if
_else 				else
integer 			integer 
real	 			real
then 				then
end_if 				end_if 
end_loop 			end_loop
loop 				loop
until 				until
start 				start
ID_ERROR_Begining	^_[_]*{ID}
ID_ERROR_End		{ID}_[_]*
ID_ERROR_Middle     {ID}?_[_]+{ID}?
ID_ERROR_Number     {numberHelper}{ID}
ID 					[a-zA-Z]([a-zA-Z0-9]|_[a-zA-Z0-9])*
Generic_ERROR_Number .*
%%

{newLine}   	 		{ TokenHandeller(yytext, 0) ; return;}
{add}       	 		{ TokenHandeller(yytext, 1) ; return;}
{multiply}				{ TokenHandeller(yytext, 2) ; return;}
{leftSmaller}			{ TokenHandeller(yytext, 3) ; return;}
{leftSmallerOrEquel}	{ TokenHandeller(yytext, 4) ; return;} 
{equel}			 		{ TokenHandeller(yytext, 5) ; return;}
{notEquel}			 	{ TokenHandeller(yytext, 6) ; return;}
{rightSmaller}		    { TokenHandeller(yytext, 7) ; return;}
{rightSmallerOrEquel}	{ TokenHandeller(yytext, 8) ; return;}
{unsignedNum}			{ TokenHandeller(yytext, 10) ; return;}
{number}				{ TokenHandeller(yytext, 11) ; return;}
{openBrackets}			{ TokenHandeller(yytext, 12) ; return;}
{closeBrackets}  		{ TokenHandeller(yytext, 13) ; return;}
{semiColon} 			{ TokenHandeller(yytext, 14) ; return;}
{colon}     			{ TokenHandeller(yytext, 15) ; return;}
{Program}          		{ TokenHandeller(yytext, 16) ; return;}
{End}          			{ TokenHandeller(yytext, 17) ; return;}
{_if}       		 	{ TokenHandeller(yytext, 18) ; return;}
{_else}		 	 		{ TokenHandeller(yytext, 19) ; return;}
{integer}           	{ TokenHandeller(yytext, 20) ; return;}
{real}	 	 			{ TokenHandeller(yytext, 21) ; return;}
{then}		 	 		{ TokenHandeller(yytext, 22) ; return;}
{end_if}	 	 		{ TokenHandeller(yytext, 23) ; return;}
{end_loop}	 	 		{ TokenHandeller(yytext, 24) ; return;}
{loop}		 	 		{ TokenHandeller(yytext, 25) ; return;}
{until}		 	 		{ TokenHandeller(yytext, 26) ; return;}
{start}		 	 		{ TokenHandeller(yytext, 27) ; return;}
{ID_ERROR_Begining}		{ TokenHandeller(yytext, 28) ; return;}
{ID_ERROR_End}			{ TokenHandeller(yytext, 29) ; return;}
{ID_ERROR_Middle}       { TokenHandeller(yytext, 30) ; return;}
{ID_ERROR_Number}		{ TokenHandeller(yytext, 31) ; return;}
{EmptySpaceError}		{ TokenHandeller(yytext, 32) ; return;}
{comma}					{ TokenHandeller(yytext, 33) ; return;}
{ID}			 		{ TokenHandeller(yytext, 9)  ;return ;}
<<EOF>>			 		{ return -1;}
%%

int yywrap(void)
{
 return 1;
}