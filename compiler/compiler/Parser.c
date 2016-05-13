#include "Scanner.h"
#include "Parser.h"
void match(TokenType tType)
{
	Token t = NextToken();

	if (t.type != tType)
	{
		printf("syntax error! expected:%s received:%s line:%d",
			FromTokenTypeEnumToString(tType), 
			FromTokenTypeEnumToString(t.type), t.lineNumber);

		fprintf(errorsFile, "syntax error! expected:%s received:%s line:%d",
			FromTokenTypeEnumToString(tType),
			FromTokenTypeEnumToString(t.type), t.lineNumber);
	}
}
void match_rel_op()
{
	Token t = NextToken();

	if (t.type != leftSmaller || t.type != leftSmallerOrEquel
		|| t.type != equel || t.type != notEquel
		|| t.type != rightSmaller || t.type != rightSmallerOrEquel)
	{
		printf("syntax error! expected rel_op received:%s line:%d",
			FromTokenTypeEnumToString(t.type), t.lineNumber);

		fprintf(errorsFile, "syntax error! expected rel_op received:%s line:%d",
			FromTokenTypeEnumToString(t.type), t.lineNumber);
	}
}
void parse_PROGRAM()
{
	Token t = NextToken();
	switch (t.type)
	{
	case program:
	{
		printResult("Correct", "PROGRAM", t.lineNumber);
		parse_DECLARATIONS();
		match(semiColon);
		parse_STATEMENTS();
		match(end);
		break;
	}
	default:
	{
		while (follow_PROGRAM(t.type) != false)
		{
			t = NextToken();
		}
		printResult("Error", "PROGRAM", t.lineNumber);
		t = BackToken();
		break;
	}
	}
}

void parse_DECLARATIONS()
{
	printResult("Correct", "DECLARATIONS", getLineNumberAnyway());
	parse_DECLARATION();
	parse_DECLARATIONS_A();
}
void parse_DECLARATIONS_A()
{
	Token t = NextToken();
	switch (t.type)
	{
	case semiColon:{
		printResult("Correct", "DECLARATIONS_A", t.lineNumber);
		parse_DECLARATIONS();
		break;
	}
	default:
	{
		if (follow_DECLARATIONS_A(t.type) != false)//epsilon
		{
			t = BackToken();
			return;
		}
		while (follow_DECLARATIONS_A(t.type) != false)
		{
			t = NextToken();
		}
		printResult("Error", "DECLARATIONS_A", t.lineNumber);
		t = BackToken();
		break;
	}
	}
}
void parse_DECLARATION()
{
	printResult("Correct", "DECLARATIONS", getLineNumberAnyway());
	parse_VARIABLES_LIST();
	parse_TYPE();
}
void parse_VARIABLES_LIST()
{
	printResult("Correct", "VARIABLES_LIST", getLineNumberAnyway());
	parse_VARIABLE();
	parse_VARIABLES_LIST_A();

}
void parse_VARIABLES_LIST_A()
{
	Token t = NextToken();
	switch (t.type)
	{
	case comma:
	{
		printResult("Correct", "VARIABLES_LIST_A", t.lineNumber);
		parse_VARIABLES_LIST();
		break;
	}
	default:
	{
		if (follow_VARIABLES_LIST_A(t.type) != false)//epsilon
		{
			t = BackToken();
			return;
		}
		while (follow_VARIABLES_LIST_A(t.type) != false)
		{
			t = NextToken();
		}
		printResult("Error", "VARIABLES_LIST_A", t.lineNumber);
		t = BackToken();
		break;
	}
	}
}


void parse_VARIABLE()
{
	Token t = NextToken();
	switch (t.type)
	{
	case id:
	{
		printResult("Correct", "VARIABLE", t.lineNumber);
		parse_VARIABLE_A();
		break;
	}
	default:
	{
		if (follow_VARIABLE(t.type) != false)//epsilon
		{
			t = BackToken();
			return;
		}
		while (follow_VARIABLE(t.type) != false)
		{
			t = NextToken();
		}
		printResult("Error", "VARIABLE", t.lineNumber);
		t = BackToken();
		break;
	}
	}
}

void parse_VARIABLE_A()
{
	Token t = NextToken();
	switch (t.type)
	{
	case openBrackets:
	{
		printResult("Correct", "VARIABLE_A", t.lineNumber);
		match(unsignedNum);
		match(closeBrackets);
		break;
	}
	default:
	{
		if (follow_VARIABLE_A(t.type) != false)//epsilon
		{
			t = BackToken();
			return;
		}
		while (follow_VARIABLE_A(t.type) != false)
		{
			t = NextToken();
		}
		printResult("Error", "VARIABLE_A", t.lineNumber);
		t = BackToken();
		break;
	}
	}
}

void parse_TYPE()
{
	Token t = NextToken();
	switch (t.type)
	{
	case integer:
	{
		printResult("Correct", "TYPE", t.lineNumber);
		break;
	}
	case real:
	{
		printResult("Correct", "TYPE", t.lineNumber);
		break;
	}
	default:
	{
		while (follow_TYPE(t.type) != false)
		{
			t = NextToken();
		}
		printResult("Error", "TYPE", t.lineNumber);
		t = BackToken();
		break;
	}
	}
}


void parse_STATEMENTS()
{
	printResult("Correct", "STATEMENTS", getLineNumberAnyway());
	parse_STATEMENT();
	parse_STATEMENTS_A();
}
void parse_STATEMENTS_A()
{
	Token t = NextToken();
	switch (t.type)
	{
	case semiColon:
	{
		printResult("Correct", "STATEMENTS_A", t.lineNumber);
		parse_STATEMENTS();
		break;
	}
	default:
	{
		if (follow_VARIABLE_A(t.type) != false)//epsilon
		{
			t = BackToken();
			return;
		}
		while (follow_STATEMENTS_A(t.type) != false)
		{
			t = NextToken();
		}
		printResult("Error", "STATEMENTS_A", t.lineNumber);
		t = BackToken();
		break;
	}
	}
}
void parse_STATEMENT()
{
	Token t = NextToken();
	switch (t.type)
	{
	case _if:
	{
		printResult("Correct", "STATEMENT", t.lineNumber);
		parse_CONDITION();
		match(then);
		parse_STATEMENTS();
		match(_else);
		parse_STATEMENTS();
		match(end_if);
		break;
	}
	case loop:
	{
		printResult("Correct", "STATEMENT", t.lineNumber);
		parse_STATEMENTS();
		match(until);
		parse_CONDITION();
		match(end_loop);
		break;
	}
	case start:
	{
		printResult("Correct", "STATEMENT", t.lineNumber);
		parse_DECLARATIONS();
		match(semiColon);
		parse_STATEMENTS();
		match(end);
		break;
	}
	default:
	{
		parse_RECEIVER();
		match(equel);
		parse_EXPRESSION();
		break;
	}
	}
}

void parse_CONDITION()
{
	printResult("Correct", "CONDITION", getLineNumberAnyway());
	parse_EXPRESSION();
	match_rel_op();
	parse_EXPRESSION();
}

void parse_EXPRESSION()
{
	Token t = NextToken();
	switch (t.type)
	{
	case number:
	{
		printResult("Correct", "EXPRESSION", t.lineNumber);
		break;
	}
	case id:
	{
		printResult("Correct", "EXPRESSION", t.lineNumber);
		parse_EXPRESSION_A();
		break;
	}
	default:
	{
		while (follow_EXPRESSION(t.type) != false)
		{
			t = NextToken();
		}
		printResult("Error", "EXPRESSION", t.lineNumber);
		t = BackToken();
		break;
	}
	}
}
void parse_EXPRESSION_A()
{
	Token t = NextToken();
	switch (t.type)
	{
	case openBrackets:
	{
		printResult("Correct", "EXPRESSION_A", t.lineNumber);
		parse_EXPRESSION();
		match(closeBrackets);
		break;
	}
	//ar_op
	case add:
	case multiply:
	{
		printResult("Correct", "EXPRESSION_A", t.lineNumber);
		parse_EXPRESSION();
		break;
	}
	default:
	{
		if (follow_EXPRESSION_A(t.type) != false)//epsilon
		{
			t = BackToken();
			return;
		}
		while (follow_EXPRESSION_A(t.type) != false)
		{
			t = NextToken();
		}
		printResult("Error", "EXPRESSION_A", t.lineNumber);
		t = BackToken();
		break;
	}
	}
}

void parse_RECEIVER()
{
	printResult("Correct", "RECEIVER", getLineNumberAnyway());
	match(id);
	parse_RECEIVER_A();
}
void parse_RECEIVER_A()
{
	Token t = NextToken();
	switch (t.type)
	{
	case openBrackets:
	{
		printResult("Correct", "RECEIVER_A", t.lineNumber);
		parse_EXPRESSION();
		match(closeBrackets);
		break;
	}
	default:
	{
		if (follow_RECEIVER_A(t.type) != false)//epsilon
		{
			t = BackToken();
			return;
		}
		while (follow_RECEIVER_A(t.type) != false)
		{
			t = NextToken();
		}
		printResult("Error", "RECEIVER_A", t.lineNumber);
		t = BackToken();
		break;
	}
	}
}

//TODO: add to h file
bool follow_PROGRAM(TokenType type)
{
	switch (type)
	{
	case EOF:
		return true;
	default:
		return false;
	}
}
bool follow_DECLARATIONS_A(TokenType type)
{
	switch (type)
	{
	case semiColon:
		return true;
	default:
		return false;
	}
}
bool follow_VARIABLES_LIST_A(TokenType type)
{
	switch (type)
	{
	case colon:
		return true;
	default:
		return false;
	}
}
bool follow_VARIABLE(TokenType type)
{
	switch (type)
	{
	case colon:
		return true;
	case comma:
		return true;
	case openBrackets:
		return true;
	default:
		return false;
	}
}
bool follow_VARIABLE_A(TokenType type)
{
	switch (type)
	{
	case colon:
		return true;
	case comma:
		return true;
	default:
		return false;
	}
}
bool follow_TYPE(TokenType type)
{
	switch (type)
	{
	case semiColon:
		return true;
	default:
		return false;
	}
}
bool follow_STATEMENTS_A(TokenType type)
{
	switch (type)
	{
	case end:
		return true;
	case end_if:
		return true;
	case _else:
		return true;
	case until:
		return true;
	case id:
		return true;
	default:
		return false;
	}
}
bool follow_EXPRESSION(TokenType type)
{
	switch (type)
	{
	case closeBrackets:
		return true;
	case then:
		return true;
	case end_loop:
		return true;
	case end:
		return true;
	case _else:
		return true;
	case end_if:
		return true;
	case until:
		return true;
		//rel_op
	case leftSmaller:
		return true;
	case leftSmallerOrEquel:
		return true;
	case equel:
		return true;
	case notEquel:
		return true;
	case rightSmaller:
		return true;
	case rightSmallerOrEquel:
		return true;
	default:
		return false;
	}
}
bool follow_EXPRESSION_A(TokenType type)
{
	switch (type)
	{
	case closeBrackets:
		return true;
	case semiColon:
		return true;
	case then:
		return true;
	case end_loop:
		return true;
	case end:
		return true;
	case _else:
		return true;
	case end_if:
		return true;
	case until:
		return true;
		//ar_op
	case add:
		return true;
	case multiply:
		return true;
	default:
		return false;
	}
}
bool follow_RECEIVER_A(TokenType type)
{
	switch (type)
	{
	case equel:
		return true;
	default:
		return false;
	}
}


int getLineNumberAnyway()
{
	Token t = NextToken();
	t = BackToken();
	return t.lineNumber;
}
void printResult(const char* result, const char* rule, int line)
{
	printf("result:%s rule:%s line:%d", result, rule, line);
	fprintf(errorsFile, "result:%s rule:%s line:%d", result, rule, line);
}
bool OpenFileOut(const char* path)
{
	file = fopen(path, "wt");
	if (file == NULL)
	{
		printf("Error open file\n");
		return false;
	}
	else
	{
		printf("File was open\n");
		errorsFile = file;
		return true;
	}
}
void main()
{
	int userChooise;
	char FilePathInput[100];
	char FilePathOutput[100];
	InputFromUser();
	scanf("%d", &userChooise);

	while (true)
	{
		switch (userChooise)
		{
		case WriteFile:
			printf("Please enter path for your input write file\n");
			scanf("%s", &FilePathInput);
			break;

		case WrongFile:
			printf("Please enter path for your input wrong file\n");
			scanf("%s", &FilePathInput);
			break;

		case Exit:
			break;

		default:
			userChooise = 0;
			break;
		}

		if (!userChooise)		 //Exit
			break;

		if (!OpenFileIn(FilePathInput)) //Cannot open file
			break;

		printf("Please enter path for your output file\n");
		scanf("%s", &FilePathOutput);
		if (!OpenFileOut(FilePathOutput)) //Cannot open file
			break;

		parse_PROGRAM();
		match(EOF);

		Print();
		//start syntax analyzer


		break;
	}
	CloseFile();
	FreeAllocation();
	system("pause");
}