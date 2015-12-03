/**
@file Documentacion.h

Fichero "dummy" sin nada de c�digo, utilizado �nicamente para mantener 
documentaci�n de Doxygen de la aplicaci�n.

@see applicationGroup

@author David Llans�
@date Septiembre, 2010
*/

/**
@mainpage GALE�N

GALEON es un peque�o juego desarrollado en C++ como ejemplo inicial
de proyecto para el 
<a href="http://www.videojuegos-ucm.es/">M�ster en Desarrollo de Videojuegos UCM</a>.

El objetivo del proyecto es pedag�gico, pues sirve de esqueleto
para la explicaci�n y ejemplificaci�n de los elementos m�s
importantes que componen un videojuego, y donde poner en
pr�ctica los contenidos que se van explicando durante
el M�ster.

Para eso, se ha prestado especial atenci�n a la documentaci�n
del c�digo, accesible desde las p�ginas que est�s leyendo.
De esta forma los contenidos que se ven por encima durante las
clases pueden terminar de entenderse a la vista del propio
c�digo y su documentaci�n.

No obstante, se ha evitado de manera consciente hacer un
esqueleto de juego <em>perfectamente escalable</em>. En este
sentido, GALEON incluye muchos elementos utilizados en
videojuegos m�s grandes, pero su implementaci�n dista mucho
de ser la mejor para proyectos de envergadura.

De esta forma, los alumnos tendr�n al alcance el c�digo que
pone a funcionar las t�cnicas explicadas en clase, pero
se ver�n forzados (en la mayor�a de los casos) a realizar
mejores implementaciones de las mismas si quieren hacer
un uso intensivo de ellas en sus propios proyectos de fin
de master.

En \ref compilando tienes informaci�n sobre c�mo compilar
la aplicaci�n. En \ref directorios se describe la estructura
de directorios del programa. Adem�s, hay explicaciones de su
funcionamiento a alto nivel, que podr�s encontrar en la secci�n
"M�dulos" del �rbol de la izquierda de la p�gina.

*/

/**
@defgroup applicationGroup Aplicaci�n de estados

En GALE�N, la aplicaci�n es una m�quina de estados, que lleva el control del
bucle del juego, especializada para trabajar con el motor gr�fico Ogre. La 
aplicaci�n debe ser inicializada de forma expl�cita antes de ser lanzada; luego 
debe ser tambi�n liberada de manera expl�cita:
<p>

\code
Application::CGaleonApplication miApp;

if (miApp.init())
    miApp.run();

miApp.release();
\endcode

<p>
En su inicializaci�n se encarga de inicializar los diferentes motores o 
servidores: subsistemas, gr�fico, interfaz de usuario y l�gico. Una vez lanzada 
se comienza un bucle infinito que actualiza los citados servidores (salvo el
l�gico por ser dependiente del estado de juego) y el estado activo en la m�quina 
de estados. Durante la ejecuci�n de la aplicaci�n se ir�n haciendo transiciones de
estados, por lo que el estado activo ir� cambiando y as� el comportamiento de la
aplicaci�n.
<p>
Los diferentes estados tienen metodos de inicializaci�n y destrucci�n expl�cita
que se invocan al a�adir el estado a la aplicaci�n o al ser liberado. Pero a su 
vez tambi�n tienen m�todos de activaci�n y desactivaci�n que ser�n invocados cada
vez que el estado pase a ser o deje de ser el estado activo de la aplicaci�n.
Como se ha dicho antes tambi�n implementan un m�todo de actualizaci�n 
(Application::CBaseState::tick()) que se invocar� en cada ciclo siempre que el 
estado est� activo.
<p>
Por otro lado, la aplicaci�n tambi�n escucha eventos del teclado y el rat�n, y los
delega de la misma manera en el estado activo.
<p>
El estado m�s importante es el estado de juego, que se encarga de cargar el nivel
de juego que se va a jugar y de invocar periodicamente al tick() del motor de
l�gica.

@author David Llans�
@date Septiembre, 2010
*/