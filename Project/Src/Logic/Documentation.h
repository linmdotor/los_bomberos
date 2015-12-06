/**
@file Documentacion.h

Fichero "dummy" sin nada de c�digo, utilizado �nicamente para mantener 
documentaci�n de Doxygen de la parte de la l�gica de juego.

@see logicGroup

@author David Llans�
@date Septiembre, 2010
*/

/**
@defgroup logicGroup L�gica de juego

La l�gica de juego son las reglas del juego que se quiere implementar; 
aqu� es donde se definen conceptos como que tipo de juego se va a 
realizar, sus reglas, que entidades habr�, como se crear�n y organizar�n,
como se comportar�n, etc.
<p>
La l�gica inicialmente planteada corresponde a un juego en tiempo real
en tercera persona. Inicialmente no se ha a�adido ning�n tipo de regla 
de juego extra y puede servir como punto de partida para diferentes 
proyectos de este tipo de juegos o de otro tipo de juegos con alguna 
modificaci�n.
<p>
Las entidades de l�gica propuestas se basan en una arquitectura de
componentes (ver @ref entityGroup) y para su creaci�n y organizaci�n se
tiene un mapa l�gico (ver @ref mapGroup) que carga un mapa de fichero
que contiene todas las entidades con sus atributos.
<p>
El acceso a la l�gica del juego est� centralizada en Logic::CServer, un
singleton de inicializaci�n expl�cita. �ste nos permite cargar un nivel
a partir de un fichero con una definici�n de mapa, que deber� luego 
activarse al comienzo de la partida. Cuando la partida est� activa el
servidor debe ser actualizado periodicamente para que se actualice el 
mapa y por tanto todas las entidades puedan actuar y realizar sus 
acciones. En la implementaci�n que se ha llevado a cabo solo permitimos
tener un mapa o nivel cargado, por lo que si se desea cargar otro nivel
se borrar� el anterior. Esto conlleva a que los m�todos de gesti�n de
mapas que tiene el servidor sean triviales. Si se quisiesen realizar
implementaciones donde se permitan multiples mapas o niveles cargados
al mismo tiempo habr�a que revisar la implementaci�n de los m�todos de
gestion de mapas del servidor.
<p>
Falta comentar que para poder cargar correctamente las entidades
del mapa es necesario que se encuentren cargadas las definiciones 
blueprints de todas las entidades por componentes que se quieren 
permitir.
<p>
El orden cronol�gico de las llamadas a la l�gica vendr�a marcado por
el siguiente marco, aunque obviamente las llamadas reales no se realizan
todas juntas sino que dependen del estado de juego de la aplicaci�n y sus
diferentes m�todos (se puede ver un ejemplo en Application::CGameState):
<p>

\code
if (!Logic::CServer::Init())
    return;

if (!Logic::CEntityFactory::getSingletonPtr()->loadBluePrints("blueprints.txt"))
	return;

Logic::CServer::getSingletonPtr()->loadLevel("map.txt");

...

Logic::CServer::getSingletonPtr()->activateMap();

while(...)
{

...

Logic::CServer::getSingletonPtr()->tick(timeSinceLastFrame);

...

}

Logic::CServer::getSingletonPtr()->deactivateMap();

...

Logic::CServer::getSingletonPtr()->unLoadLevel();

Logic::CEntityFactory::getSingletonPtr()->unloadBluePrints();

Logic::CServer::Release();
\endcode

@author David Llans�
@date Septiembre, 2010
*/