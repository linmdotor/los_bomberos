/**
@file Documentacion.h

Fichero "dummy" sin nada de c�digo, utilizado �nicamente para mantener 
documentaci�n de Doxygen de la parte del parseador de ficheros de mapas.

@see mapParserGroup

@author David Llans�
@date Septiembre, 2010
*/

/**
@defgroup mapParserGroup Parseador de ficheros de mapas

Para la tar�a del parseo de ficheros con definiciones de mapas se tiene el 
proyecto Map en el que se analizan l�xica y sint�cticamente los mapas descritos 
en ficheros para extraer de ellos la lista de descripciones de las entidades.
<p>
El grueso del proyecto se trata de c�digo autogenerado por Flex y Bison 
(predecesores de Lex y Yacc), por lo que ese c�digo <em>no</em> deber� ser
modificado y si se desea cambiar la gram�tica se deber�n modificar los ficheros
con las descripciones de las gram�ticas l�xica y sint�ctica (Map/Scanner.ll y 
Map/Parser.yy) y generar de nuevo a partir de ellos los ficheros. Para este fin
se encuentra informaci�n extra en Map/Readme.txt.
<p>
Los mapas leidos por este parseador deber�n seguir la siguiente estructura:

\code
Map = {
   [
   EntityName = {
	  [AttributeName = AttributeValue,]*
   },
   ]*
}
\endcode

Por ejemplo:

\code
Map = {
   gobling1 = {
      type = "Gobling",
      position = {1.4,0,2.66},
      life = 100.0,
      ...
   },
   orc1 = {
      type = "Orc"
      modelname = "orc.mesh",
      ...
   }
   ...
}
\endcode

Donde los nombres de los atributos deben empezar por una letra o '_' y contener
letras, n�meros o '_' y los valores de los atriburos pueden ser cadenas encerradas
entre dobles comillas '"', numeros enteros o reales, "true", "false" o posiciones tipo 
"{x,y,z}". No obstante todos los valores de atributos ser�n almacenados como strings y 
ser� luego, durante el spawn de las entidaes cuando los componentes deban 
saber que tipo de datos esperan de cada atributo concreto para recuperar los atributos
con su tipo correcto mediante los m�todos getXXXAttribute() de Map::CEntity. Los tipos  
de las entidades deben coincidir con las declaradas en los archivos de blueprints, 
aunque no se har� ning�n tipo de comprobaci�n aqu�. Eso si, toda entidad declarada 
deber� como m�nimo tener el atributo de nombre "type" y los nombres de las entidades
deber�n ser diferentes entre s�. Estas comprobaciones solo se realizan en modo Debug,
por optimizaci�n del c�digo Release. Como curiosidad cabe decir que
los saltos de l�nea, espacios y tabulaciones son opcionales y que puede usarse ';' 
en vez de ',' como separador si se prefiere.
<p>
La clase CMapParser reune todos los componentes necesarios para el parseo
de un mapa. Es un singleton de inicializaci�n expl�cita que permite parseo
de streams. No obstante incluye m�todos que facilitan el parseo de un 
archivo dado su nombre, o de un string. Su uso m�s com�n ser� mediante la lectura
de un fichero con Map::CMapParser::parseFile() que leer� el fichero de nombre 
especificado que se encuentre en la ruta <code>Exes/media/maps</code> y crear� 
una lista de Map::CEntity's con las descripciones de las entidades.
<p>
Map::CEntity no es m�s que una clase contenedora de atributos tipo par
<std::string,std::string> donde el primer elemento es el nombre del atributo es el
nombre del atributo y el segundo elemento es su valor codificado en un string. Adem�s 
contiene una serie de m�todos que permiten recuperar los valores de los atributos ya
transformados a un tipo concreto (int, float, double, bool, string o Vector3).
<p>
El parseador de mapas es usado por la funci�n est�tica Logic::CMap::createMapFromFile(),
all� se puede ver m�s claramente como generar un mapa l�gico a partir de las 
definiciones de entidades (Map::CEntity) devueltas por este m�dulo.

@author David Llans�
@date Septiembre, 2010
*/