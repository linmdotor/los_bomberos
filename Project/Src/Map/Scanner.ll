/** 
@file Scanner.ll 

Contiene el codigo autogenerado del scanner l�xico de Flex.

@author David Llans�
@date Agosto, 2010
*/

%{ /*** Declaraciones C++ ***/

#include <string>

#include "Scanner.h"

#include <stdio.h>
#include "Parser.h"

/* importamos el tipo de los tokens del parser a un tipo local */
typedef Map::CParser::token token;
typedef Map::CParser::token_type token_type;

/* Redefinimos yyterminate para que devuelva el token END. */
#define yyterminate() return token::END

/* Desabilitamos la inclusi�n de unistd.h, no disponible bajo Visual C++
   en Win32. A cambio se usan STL streams. */
#define YY_NO_UNISTD_H

%}

/*** Declaraciones y opciones de Flex ***/

/* Habilitamos la generaci�n de la clase C++ para el scanner*/
%option c++

/* Cambiamos el prefijo de la clase generada. El resultado ser� "CMapFlexLexer" */
%option prefix="CMap"

/* Una optimizaci�n */
%option batch

/* A�ade salida de depuraci�n. Para la versi�n definitiva deber�a eliminarse esta opci�n. */
%option debug

/* No permitimos inclusiones de ficheros */
%option yywrap nounput 

%option stack

%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

_STRING \"[^\"]*\"
_ID [[:alpha:]_][[:alnum:]_]*
_NUMBER "-"?[0-9]+"."?[0-9]*

%% /*** Parte de las expresiones regulares ***/

 /* C�digo a�adido al principio de yylex() */
%{
    // reset location
    yylloc->step();
%}

 /*** EMPIECE de las reglas l�xicas ***/

"Map"        {return(token::MAPBEGIN);}
"true"       {yylval->string = new std::string(yytext, yyleng);return(token::TRUE);}
"false"       {yylval->string = new std::string(yytext, yyleng);return(token::FALSE);}
"="          {return(token::EQUAL);}
";"          {return(token::SEMICOLON);}
","          {return(token::COMMA);}
"{"          {return(token::LEFT_PAR);}
"}"          {return(token::RIGHT_PAR);}
{_NUMBER}    {yylval->string = new std::string(yytext, yyleng); return(token::NUMBER);}
{_ID}      {yylval->string = new std::string(yytext, yyleng); return(token::ID);}
{_STRING}    {yylval->string = new std::string(yytext+1, yyleng-2); return(token::STRING);} /* Quitamos las comillas */

 /*** FIN de las reglas l�xicas ***/

%% /*** C�digo adicional ***/

namespace Map {

	CScanner::CScanner(std::istream* in,
			 std::ostream* out)
		: CMapFlexLexer(in, out)
	{
	}

	CScanner::~CScanner()
	{
	}

	void CScanner::set_debug(bool b)
	{
		yy_flex_debug = b;
	}

}

/**
Debemos reimplementar CMapFlexLexer::yylex() para completar la vtable de
CMapFlexLexer. Esta nueva definici�n sin embargo reporta un error ya que
lo que haremos es definir la funcionalidad de esta funci�n en la clase
CScanner que heredar� de CMapFlexLexer y es la que se usar�. 
*/

#ifdef yylex
#undef yylex
#endif

int CMapFlexLexer::yylex()
{
    std::cerr << "in CMapFlexLexer::yylex() !" << std::endl;
    return 0;
}

int CMapFlexLexer::yywrap()
{
    return 1;
}
