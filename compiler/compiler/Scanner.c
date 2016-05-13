#include "Scanner.h"
extern int 	yylex();
extern int 	yylineno;
extern char	*yytext;
extern FILE *yyin;


/*Start member declaration ---stageOne---*/
TokenSubList   *_tokenSubListHead = NULL;
TokenSubList   *_tokenSubListTail = NULL;
bool			_IsHeaderCreated = false;
bool			_IsHeaderHandled = false;
bool			_IsStartHandelTail = false;
long			_LineCounter = 0;
bool			_EOF = false;
bool			_IsLastToken = true;
/*End member declaration ---stageOne---*/


/*Start region TokenHandller*/
Token NextToken()
{
	Token t;
	if (_IsLastToken)
	{
		if (yylex() == -1)
		{
			_EOF = true;
		}
	}
	else
	{
		_IsLastToken = true;
	}
	return _tokenSubListTail->tokensSubList[_LineCounter];
}
Token BackToken()
{
	TokenSubList* prev;
	Token t;
	_IsLastToken = false;
	if (_tokenSubListTail == NULL)
		return;

	if (_LineCounter == 0)
	{
		if (_tokenSubListTail->pervSubList != NULL)
		{
			prev = _tokenSubListTail->pervSubList;
			return prev->tokensSubList[TokensSubListSize - 1];
		}
	}
	return _tokenSubListTail->tokensSubList[TokensSubListSize - 1];
}
void TokenHandeller(const char* lexemeExt, int typeExt)
{
	Token token;
	if (!FillTokenData(lexemeExt, typeExt, &token))
		return;

	if (!_IsHeaderCreated)
		ExpendTokensHeader();

	if (!_IsHeaderHandled)
		FillHeaderSubTokenList(&token);

	if (!_IsStartHandelTail)
		return;

	if (IsAlreadyNextSubList(_LineCounter))
		ExpendTokensTail();

	FillTailSubTokenList(&token);
}
/*End region TokenHandller*/

/*Start region header*/
void ExpendTokensHeader()
{
	TokenSubList *curr = (TokenSubList*)calloc(1, sizeof(TokenSubList));
	curr->nextSubList = NULL;

	if (_tokenSubListHead == NULL)
	{
		_tokenSubListHead = curr;
		_tokenSubListHead->nextSubList = _tokenSubListHead->pervSubList = NULL;
		_tokenSubListTail = _tokenSubListHead;

		_IsHeaderCreated = true;
	}

	_LineCounter = 0;
}
void FillHeaderSubTokenList(const Token* token)
{
	if (IsAlreadyNextSubList(_LineCounter))
	{
		_IsStartHandelTail = true;
		_IsHeaderHandled = true;
		ExpendTokensTail();
		return;
	}

	_tokenSubListHead->tokensSubList[_LineCounter] = *token;
	_LineCounter++;
}
/*End region header*/


/*Start region tail*/
void ExpendTokensTail()
{
	TokenSubList *curr = (TokenSubList*)calloc(1, sizeof(TokenSubList));
	TokenSubList *prev = _tokenSubListTail;

	curr->nextSubList = NULL;
	curr->pervSubList = prev;
	_tokenSubListTail->nextSubList = curr;
	_tokenSubListTail = curr;

	_LineCounter = 0;
}
void FillTailSubTokenList(const Token* token)
{
	_tokenSubListTail->tokensSubList[_LineCounter] = *token;
	_LineCounter++;
}

char* FromTokenTypeEnumToString(int TokenType)
{
	switch (TokenType)
	{
	case newLine:				return "Token type newLine";
	case add:					return "Token type add";
	case multiply:				return "Token type multiply";
	case leftSmaller:			return "Token type leftSmaller";
	case leftSmallerOrEquel:	return "Token type leftSmallerOrEquel";
	case equel:					return "Token type equel";
	case notEquel:				return "Token type notEquel";
	case rightSmaller:			return "Token type rightSmaller";
	case rightSmallerOrEquel:	return "Token type rightSmallerOrEquel";
	case id:					return "Token type id";
	case unsignedNum:			return "Token type unsignedNum";
	case number:				return "Token type number";
	case openBrackets:			return "Token type openBrackets";
	case closeBrackets:			return "Token type closeBrackets";
	case semiColon:				return "Token type semiColon";
	case colon:					return "Token type colon";
	case program:				return "Token type program";
	case end:					return "Token type end";
	case _if:					return "Token type if";
	case _else:					return "Token type else";
	case integer:				return "Token type integer";
	case real:					return "Token type real";
	case then:					return "Token type then";
	case end_if:				return "Token type end_if";
	case end_loop:				return "Token type end_loop";
	case loop:					return "Token type loop";
	case until:					return "Token type until";
	case start:					return "Token type start";
	case ID_ERROR_Begining:		return "ID_ERROR_Begining";
	case ID_ERROR_End:			return "ID_ERROR_End";
	case ID_ERROR_Middle:		return "ID_ERROR_Middle";
	case ID_ERROR_Number:		return "ID_ERROR_Number";
	case EmptySpaceError:		return "EmptySpaceError";
	case comma:					return "Token type comma";

	default:
		return "Token type not exist";
	}
}
/*End region tail*/


/*Start region utills*/
bool FillTokenData(const char* lexemeExt, int typeExt, Token* token)
{
	if (typeExt == 0)
		return false;

	char *newLexeme = (char*)calloc(strlen(lexemeExt) + 1, sizeof(char));
	strcpy(newLexeme, lexemeExt);
	char* tokeType = FromTokenTypeEnumToString(typeExt);
	if (!IsHandelError(typeExt))
	{
		printf("Token --> type: Token type: %s , lexeme: %s , lineNumber: %d\n", tokeType, newLexeme, yylineno);
		return false;
	}

	token->type = typeExt;
	token->lexeme = newLexeme;
	token->lineNumber = yylineno;

	return true;
}
bool IsHandelError(const int tokeType)
{
	if (tokeType != ID_ERROR_Begining || tokeType != ID_ERROR_End
		|| tokeType!= ID_ERROR_Middle || tokeType != ID_ERROR_Number
		|| tokeType != EmptySpaceError)

	{
		return false;
	}

	return true;
}
bool IsAlreadyNextSubList(long line)
{
	return line == TokensSubListSize;
}
void Print()
{
	printf("\n\n----------------------------StartPrintingAll-------------------------------\n\n");
	TokenSubList *curr = _tokenSubListHead;
	Token token;
	int i = 0;
	while (curr != NULL)
	{
		for (i = 0; i < TokensSubListSize; i++)
		{
			token = curr->tokensSubList[i];
			if (token.lexeme == NULL)
				break;

			printf("Token --> type: %s , lexeme: %s , lineNumber: %d\n", token.type, token.lexeme, token.lineNumber);
			printf("---------------------------------------------------------------------\n");
		}
		curr = curr->nextSubList;
	}
	printf("\n\n----------------------------EndPrintingAll-------------------------------\n\n");
}
void FreeAllocation()
{
	TokenSubList *curr = _tokenSubListHead;
	TokenSubList *next;
	while (curr != NULL)
	{
		next = curr->nextSubList;
		if(next == NULL)
			break;
		
		free(curr);
		curr = next;
	}
}
bool OpenFileIn(const char* path)
{
	file = fopen(path, "r");
	if (file == NULL)
	{
		printf("Error open file\n");
		return false;
	}
	else
	{
		printf("File was open\n");
		yyin = file;
		return true;
	}
}
void CloseFile()
{
	if(file == NULL)
		return;
	
	fclose(file);
	printf("File was close\n");
}
void InputFromUser()
{
	printf("Please enter your chooise according to the following rules\n");
	printf("For Write file press 1\n");
	printf("For Wrong file press 2\n");
	printf("For Exit  file press 0\n");
}
/*End region utills*/