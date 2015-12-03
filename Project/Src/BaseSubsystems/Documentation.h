/**
@file Documentacion.h

Fichero "dummy" sin nada de c�digo, utilizado �nicamente para mantener 
documentaci�n de Doxygen de los subsistemas base.

@see baseSubsystemsGroup

@author David Llans�
@date Septiembre, 2010
*/

/**
@defgroup baseSubsystemsGroup Subsistemas base

Dentro del grupo de subsistemas base se encuentran la inicializaci�n y 
gesti�n de los diferentes motores necesarios para correr la aplicaci�n as�
como una ser�e de herramientas auxiliares usadas por el proyecto. 
<p>
Su misi�n principal es la de inicializar los subsistemas de Ogre, OIS, etc. 
y hacerlos accesibles al resto de proyectos de la soluci�n. De esta manera
se ocultan los detalles engorrosos de la creaci�n y destrucci�n de los 
recursos necesarios para que luego el resto de proyectos de la soluci�n 
puedan acceder a ellos de forma limpia. Su otra funci�n es la de ofrecer
una ser�e de funciones y estructuras con las que trabajar por el resto de 
proyectos.
<p>
Para activar su funcionalidad basta con inicializar el servidor central del
grupo. Se trata de un servidor de inicializaci�n y destrucci�n expl�cita por 
lo que habr� que llamar a <code>BaseSubsystems::CServer::Init()</code> y
<code>BaseSubsystems::CServer::Release()</code>.
<p>
Es importante recalcar que este servidor debe de ser inicializado <b>antes</b>
que el resto ya que varios de ellos necesitan pedir recursos a �ste en sus
inicializaciones.
<p>
En la cabecera Server.h se puede definir o no definir la directiva 
NON_EXCLUSIVE_MODE_IN_WINDOW_MODE que indica si se quiere que la aplicaci�n 
se haga con el control del rat�n y dibuje su propio cursor o por el contrario
se quiere usar el del sistema operativo, de manera que se pueda acceder a 
otras aplicaciones mientras corre el juego. Por defecto est� activa s�lo en 
DEBUG.

@author David Llans�
@date Septiembre, 2010
*/