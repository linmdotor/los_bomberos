/**
@file Documentacion.h

Fichero "dummy" sin nada de c�digo, utilizado �nicamente para mantener 
documentaci�n de Doxygen de la parte gr�fica.

@see graphicsGroup

@author David Llans�
@date Septiembre, 2010
*/

/**
@defgroup graphicsGroup Gr�ficos

Grupo de clases que sirven para pintar las entidades gr�ficas en la ventana
de reenderizado y sirven como interfaz de Ogre para el resto de los 
proyectos.
<p>
Adem�s de ocultar el motor gr�fico usado al resto de proyectos, sus clases
ofrecen un uso de m�s alto nivel, de manera que solucionan parte de la gesti�n
necesaria cuando se crean entidades, c�maras o escenas.
<p>
El eje central es el servidor, que se trata de un singleton de inicializaci�n 
y destrucci�n expl�cita por lo que habr� que llamar a 
<code>Graphics::CServer::Init()</code> y <code>Graphics::CServer::Release()</code>
para su inicializaci�n y liberaci�n.
<p>
Los diferentes elementos gr�ficos se organizan en escenas (CScene), que contiene
listas con las entidades gr�ficas que se pintar�n y una c�mara que refleja desde
donde se desea visualizar la escena. Las entidades gr�ficas deben estar asociadas 
a una escena y de hecho, los recursos Ogre no se cargan hasta que la entidad no se
asocia a una escena. Diferenciamos las entidades gr�ficas en tres grupos distintos:
din�micas, est�ticas y animadas.
<p>
Las entidades din�micas (<code>Graphics::CEntity</code>) son aquellas que representan
objetos que pueden cambiar de posici�n, orientaci�n, escala, etc. Las est�ticas
(<code>Graphics::CStaticEntity</code>) son aquellas que no van a ser alteradas 
durante toda la partida (suelos, paredes, etc.) y no pueden ser modificadas una
vez que se ha activado la escena por primera vez. El beneficio de estas entidades 
es que consumen menos recursos para ser pintadas, por lo que si se sabe que una 
entidad no va a ser alterada conviene que sea est�tica. Por �ltimo, las entidaes
animadas (<code>Graphics::CAnimatedEntity</code>) son entidades din�micas que adem�s
pueden reproducir animaciones.
<p>
El orden de uso de los diferentes elementos viene definido en el siguiente marco:
<p>

\code
if (!Graphics::CServer::Init())
    return;
...

Graphics::CScene scene = Graphics::CServer::getSingletonPtr()->createScene("escena");

...

Graphics::CEntity entity = new Graphics::CEntity("entidad","modelo.mesh");
if(!scene->addEntity(entity))
	return;

entity->setPosition(Vector3::ZERO);
entity->setYaw(Math::PI);

...

scene->removeEntity(entity);
delete entity;

...

Graphics::CServer::getSingletonPtr()->removeScene(scene);

...

Graphics::CServer::Release();
\endcode

@author David Llans�
@date Septiembre, 2010
*/