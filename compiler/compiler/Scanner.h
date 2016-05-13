#ifndef Scanner_h
#define Scanner_h
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TokensSubListSize 3

#define false 0
#define true 1
typedef int bool;

bool _EOF;

typedef enum  TokenType
{
	newLine = 0,
	add,
	multiply,
	leftSmaller,
	leftSmallerOrEquel,
	equel,
	notEquel,
	rightSmaller,
	rightSmallerOrEquel,
	id,
	unsignedNum,
	number,
	openBrackets,
	closeBrackets,
	semiColon,
	colon,
	program,
	end,
	_if,
	_else,
	integer,
	real,
	then,
	end_if,
	end_loop,
	loop,
	until,
	start,
	ID_ERROR_Begining,
	ID_ERROR_End,
	ID_ERROR_Middle,
	ID_ERROR_Number,
	EmptySpaceError,
	comma
}TokenType;

typedef struct Token
{
	TokenType	type;
	const char	*lexeme;
	long		lineNumber;
}Token;

typedef struct TokenSubList
{
	struct TokenSubList  *nextSubList;
	struct TokenSubList  *pervSubList;
	struct Token		 tokensSubList[TokensSubListSize];
}TokenSubList;

enum  _UserOpation
{
		Exit = 0,
		WriteFile,
		WrongFile
};


/*Start region Token Handller*/
void TokenHandeller(const char* lexemeExt, int typeExt);
void ExpendTokensHeader();
void FillHeaderSubTokenList(const Token* token);
void ExpendTokensTail();
void FillTailSubTokenList(const Token* token);
void FreeAllocation();
void Print();
Token NextToken();
Token BackToken();
char* FromTokenTypeEnumToString(int TokenType);
bool IsAlreadyNextSubList(long line);
bool FillTokenData(const char* lexemeExt, int typeExt, Token* token);
bool IsHandelError(const char* tokeType);
/*End region Token Handller*/

/*Start region File Handller*/
bool OpenFile(const char* path);
void CloseFile();
FILE *file;
/*End region File Handller*/

#endif