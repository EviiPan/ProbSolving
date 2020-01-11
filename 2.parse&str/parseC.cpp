//
//  main.cpp
//  parseC
//
//  Created by Evii Pan on 10/12/19.
//  Copyright © 2019 Evii Pan. All rights reserved.
//

#include <iostream>

/* peekc
 returns the next character (byte) in the regular expression.
 */
int peekc(){
    int ch = getchar();
    ungetc(ch, stdin);
    return ch;
}

void parseNumber(char ch){
    printf("%c", ch);
    while(isdigit(peekc()) || peekc()=='.'){
        printf("%c", getchar());
    }
    printf("\n");
}

void parseWord(char ch){
    printf("%c", ch);
    while (isalpha(peekc()) || peekc() == '_'){
        printf("%c", getchar());
    }
    printf("\n");
}

void parseOperator(char inch){
    int ch = peekc();
    switch (ch) {
        case '+':
            if(ch == inch)
                printf("%c", getchar());
            break;
        case '-':
            if(ch == inch)
                printf("%c", getchar());
            break;
        case '>':
            if(ch == inch)
                printf("%c", getchar());
            break;
        case '<':
            if(ch == inch)
                printf("%c", getchar());
            break;
        case '=':
            printf("%c", getchar());
            break;
        case '|':
            if(ch == inch)
                printf("%c", getchar());
            break;
        case '&':
            if(ch == inch)
                printf("%c", getchar());
            break;
        default:
            break;
    }
}

int endCommend(){
    if(getchar() == '*' && getchar() == '/')
        return 1;
    return 0;
}

void parseCommend(char ch){
    switch (peekc()) {
        case '/':
            while(getchar() != '\n');
            break;
        case '*':
            while(!endCommend());
            break;
        default:
            parseOperator(ch);
            break;
    }
}

void parseDouQuote(char ch){
    while((ch = getchar()) != '"'){
        switch (ch) {
            case '\\':
                printf("%c%c", ch, getchar());
                break;
            default:
                printf("%c", ch);
                break;
	}
    }
    printf("\n");
}

void parseSinQuote(char ch){
    while((ch = getchar()) != '\'')
        printf("%c", ch);
    printf("\n");
}

void parse_error(const char *msg, char ch){
    fprintf(stderr, "ERROR: %s: %c\n", msg, ch);
}

void getToken(char inch){
        switch (inch) {
            case ' ':
            case '\t':
            case '\n':
                break;//skip white space
	    case '/':
		parseCommend(inch);
		break;
            case '&':
            case '|':
            case '<':
            case '>':
            case '+':
            case '-':
            case '*':
	    case '=':
                printf("%c", inch);
                parseOperator(inch);
                printf("\n");
                break;//Operators
            case '?':
            case '!':
            case '#':
            case ';':
            case ':':
            case ',':
            case '.':
            case '{':
            case '}':
            case '(':
            case ')':
	    case '[':
	    case ']':
//	    case '"':
//	    case '\'':
                printf("%c\n", inch);
                break;

            case '"':
                printf("%c\n", inch);
                parseDouQuote(inch);
                printf("%c\n", inch);
                break;
            case '\'':
                printf("%c\n", inch);
                parseSinQuote(inch);
                printf("%c\n", inch);
                break;
  
            default:
                if(isdigit(inch))
                    parseNumber(inch);
                else if (isalpha(inch))
                    parseWord(inch);
                else
                    parse_error("illegal character!",inch);
                break;
        }
}

int main(int argc, const char * argv[]) {
    int ch;
    while((ch = getchar()) != EOF){
        getToken(ch);
    }
    printf("\n");
    return 0;
}
