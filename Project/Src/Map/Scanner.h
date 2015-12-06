/**
@file Scanner.h

Contiene la declaraci�n de un scanner flex con funcionalidades extra.

@see Map::CScanner

@author David Llans� Garc�a
@date Agosto, 2010
*/

#ifndef __Scanner_H
#define __Scanner_H

#ifndef YY_DECL

// Macro para la declaraci�n de la funci�n principal usada en el an�lisis l�xico
#define	YY_DECL						\
    Map::CParser::token_type Map::CScanner::lex(		\
				Map::CParser::semantic_type* yylval,	\
				Map::CParser::location_type* yylloc		\
				)
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer CMapFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

#include "Parser.h"

namespace Map {

	/** 
	CScanner es una clase que dota de funcionalidades extra a la clase
	autom�ticamente generada por Flex CMapFlexLexer.

	@ingroup mapParserGroup

	@author David Llans�
	@date Agosto, 2010
	*/
	class CScanner : public CMapFlexLexer
	{
	public:
		/** 
		Crea un nuevo objeto scanner. Los streams arg_yyin y arg_yyout
		est�n por defecto puestos a cin y cout.

		@param arg_yyin Entrada de donde se leer�n los tokens.
		@param arg_yyout Salida donde se escribir�n los errores, etc.
		*/
		CScanner(std::istream* arg_yyin = 0,
			std::ostream* arg_yyout = 0);

		/** 
		Destructor.
		*/
		virtual ~CScanner();

		/**
		Esta es la funci�n principal usada en el an�lisis l�xico. Es 
		generada por Flex acorde a la declaraci�n de la macro YY_DECL.
		El parser bison generado llamar� a esta funci�n virtual para
		ir obteniendo los nuevos tokens.
		*/
		virtual CParser::token_type lex(
						CParser::semantic_type* yylval,
						CParser::location_type* yylloc
						);

		/**
		Habilita la salida de depuraci�n (via arg_yyout).
		*/
		void set_debug(bool b);
	};

} // namespace Map

#endif // __Scanner_H
