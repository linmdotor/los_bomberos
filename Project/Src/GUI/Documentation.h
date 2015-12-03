/**
@file Documentacion.h

Fichero "dummy" sin nada de c�digo, utilizado �nicamente para mantener 
documentaci�n de Doxygen de la parte de interfaz de usuario.

@see GUIGroup

@author David Llans�
@date Septiembre, 2010
*/

/**
@defgroup GUIGroup Interfaz de usuario

Como interfaz de usuario englobamos todo aquello que sirve para informar 
de manera expl�cita al usuario y las herramientas con las que el usuario
se comunica con el juego.
<p>
Para mostrar al usuario informaci�n que va m�s all� de la partida en si
nos apoyamos en CEGui. CEGui nos permite mostrar gr�ficos 2D sobre el 
reenderizado de la partida y no est� atado a Ogre. CEGui nos permitir�
crear men�s o mostar cuadros con informaci�n necesaria para el usuario
durante la partida (vida, siguiente misi�n, etc.). En este m�dulo se 
gestionar� CEGUI para que la interfaz gr�fica de usuario sea correcta.
<p>
Para la comunicaci�n del usuario con el juego usamos OIS que nos permite
gestionar la entrada de perif�ricos tradicionales (rat�n y teclado). Se 
ha creado un gestor de perif�ricos de entrada que controla y captura los 
eventos que se producen en teclado y rat�n basado en OIS, pero que a su
vez nos sirve para independizar al resto de la aplicaci�n de esta 
biblioteca en concreto.
<p>
El gestor permite registrar oyentes que ser�n informados de los eventos 
de entrada producidos, as� cualquier clase que necesite tener acceso a
los eventos deber� implementar los m�todos de las clases oyentes 
(GUI::CKeyboardListener o GUI::CMouseListener) y registrarse en el gestor.
Este gestor debe ser inicializado al principio de la aplicaci�n ya que
hasta la propia aplicaci�n debe registrarse para escuchar eventos de
entrada.
<p>
Para la comunicaci�n del resto de los proyectos con la parte de interfaz
de usuario hay un servidor (GUI::CServer). Adem�s, hay una clase espec�fica
(GUI::PlayerController) para el control del jugador mediante teclado y 
rat�n. Esta clase transformar� las pulsaciones de teclas y movimiento del 
rat�n en acciones concretas de movimiento o giro y se comunicar�n 
directamente a una instancia de Logic::CAvatarController que debe 
registrarse mediante el servidor.

@author David Llans�
@date Septiembre, 2010
*/