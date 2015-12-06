/**
@file Documentacion.h

Fichero "dummy" sin nada de c�digo, utilizado �nicamente para mantener 
documentaci�n de Doxygen de la parte de las entidades de la l�gica de 
juego.

@see entityGroup

@author David Llans�
@date Septiembre, 2010
*/

/**
@defgroup entityGroup Entidades en la l�gica de juego

La gesti�n de entidades realizada en la capa l�gica (ver @ref logicGroup) utiliza
una arquitectura de componentes. Gracias a esto, hay �nicamente una clase
que implementa el concepto de "entidad", la clase Logic::CEntity que no
es m�s que un contenedor de componentes (Logic::IComponent) que son los que definen
el comportamiento total de la entidad.

La construcci�n de entidades se basa en la existencia de lo que se llaman
ficheros de "blueprint" que contienen, para cada entidad, qu� componentes
definen su comportamiento. Por ejemplo la entidad "Player", que representa
al jugador, est� definida como:

\code
Player CAvatarController CAnimatedGraphics
\endcode

Lo que viene a indicar que la entidad es simplemente un componente de control
(para que pueda ser controlado) y uno gr�fico (para que se dibuje).

El mapa despu�s lo �nico que tiene que hacer es declarar la lista de
entidades que contiene y sus propiedades. En la carga del mapa se van creando
los componentes e inicializ�ndolos con esas propiedades le�das del mapa (como
la posici�n inicial, o el modelo gr�fico a dibujar).

Los componentes se intentan hacer lo m�s general posible, para que sirvan
para definir el comportamiento de distintos tipos de entidades. En muchas
ocasiones el comportamiento final se termina de configurar gracias a esos
atributos. Por ejemplo, el componente gr�fico sirve para dotar a las
entidades de cuerpo en el mundo gr�fico, ya sea este est�tico o din�mico.
Las distintas propiedades o atributos le�dos del mapa configurar�n el 
componente para que refleje el tipo de entidad gr�fica que se desea.

El funcionamiento de los componentes se basa en la existencia del m�todo
Logic::IComponent::tick(), donde los componentes particulares pueden
ejecutar sus operaciones. Normalmente las operaciones consistir�n en el
procesado de mensajes recibidos y/o alguna otra operaci�n necesaria.

@section grupoComponentesRegistro Registrando un componente nuevo

Para que el juego sea capaz de crear cada componente particular a partir
de su nombre se necesita una factor�a de componentes y que cada clase
que implementa uno de ellos se registre en la misma.

La clase Logic::ComponentFactory es la responsable de esa creaci�n. Es un 
singleton donde se registran todos los componentes utilizando el m�todo 
Logic::ComponentFactory::add. Ese m�todo recibe el nombre del componente y 
una funci�n global (o est�tica) para crear un objeto de ese tipo. En el 
momento de crear una entidad, se utiliza el fichero de blueprints para saber 
qu� componentes se necesitan y se utiliza la factor�a para crearlos. 

Sin embargo, para facilitar el desarrollo de nuevos componentes, el fichero 
Logic/Entity/IComponent.h define una serie de macros del preprocesador que 
pueden/deben utilizarse. En conreto, para tener un componente funcionando 
basta con:

<ul>
	<li>Utilizar la macro DEC_FACTORY en la parte de declaraci�n de la nueva
		clase para que se a�adan ciertas funciones est�ticas �tiles para el registro
		en la factor�a.
	<li>Utilizar la macro IMP_FACTORY en la parte de implementaci�n para
		definir el c�digo de esas funciones.
	<li>Utilizar la macro REG_FACTORY tras la declaraci�n de la nueva clase
		para que se registre el componente en la factor�a utilizando los m�todos
		declarados y definidos con las macros anteriores.
	<li>Hacer una inclusi�n del archivo cabecera del nuevo componente en alg�n
		fichero .cpp del proyecto que sepamos que va a ser procesado para que la 
		macro REG_FACTORY registre el nuevo componente en la factor�a.
</ul>

Como ejemplo, si queremos construir un nuevo componente <code>CMyComponent</code>, 
el inicio del fichero de cabecera ser�a algo as�:

\code
// File MyComponent.h
#include "Logic/Entity/IComponent.h"

class CMyComponent : public Logic::IComponent 
{
   DEC_FACTORY();

public:
   ...
};
REG_FACTORY(CMyComponent);
\endcode

y en el fichero de implementaci�n:

\code
// File MyComponent.cpp
#include "MyComponent.h"

IMP_FACTORY(IComponent);
...
\endcode

Por �ltimo, para poder utilizar el componente (mejor dicho para que durante
la carga de un mapa el motor sea capaz de crearlo), se debe registrar
en la factor�a. Hacemos la inclusi�n de la cabecera en cualquier fichero .cpp 
del proyecto que sepamos que va a ser procesado. Las inclusiones de los 
componentes iniciales se han realizado en Logic/ComponentFactory.cpp:

\code
// Fichero XXX.cpp
#include "MyComponent.h"
...
\endcode

@section grupoComponentesImplementacion Implementando un componente nuevo

Una vez que se tiene claro c�mo crear un nuevo componente para que pueda
ser utilizado dentro de una entidad, podemos pasar a implementar la
funcionalidad que deseemos que realice.

El componente m�s sencillo (e in�til) es el implementado en la
secci�n anterior: aquel que simplemente hereda de Logic::IComponent.
No sirve para mucho, pero es un comienzo: el motor del juego lo reconoce
como componente y se puede utilizar dentro de las entidades.

A continuaci�n iremos extendiendo ese componente para ejemplificar las
caracter�sticas b�sicas que deben conocerse para implementar un componente
serio. Por comodidad el c�digo presentado asume que se est� en el fichero
de cabecera, aunque en un desarrollo serio tendr�amos la mayor parte
de la implementaci�n en un fichero .cpp.

@subsection noLabel1 Leyendo propiedades

Nuestro componente ser� creado cuando en el mapa se tenga una entidad
que lo necesite. Esa entidad tendr� a buen seguro una lista de atributos
que podr�n ser le�dos por los componentes para terminar de definir
sus comportamientos.

En el momento de la creaci�n del componente, el motor invoca al m�todo
Logic::IComponent::spawn() al que le pasa, entre otras cosas, un objeto
de donde leer todos los atributos de la entidad.

El m�todo devuelve un booleano para poder notificar condiciones de error;
en caso de ser imposible la inicializaci�n del componente, se devuelve
<code>false</code> y el motor anula la carga del mapa.

Es <em>importante</em> invocar al m�todo spawn de la clase padre al
principio del m�todo, para que la inicializaci�n sea completa. El
siguiente ejemplo comprueba si existe el atributo "activateMsg" en el mapa
y si existe lo guarda en una variable. Para poder acceder a los atributos 
le�dos del mapa se debe incluir el fichero Map/MapEntity.h.

\code
class CMyComponent : public Logic::IComponent 
{
   DEC_FACTORIA();

public:

   CTestComponent() : _activateMsg("Map activated or deactivated") {}

   virtual bool spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
   {
      if( !IComponent::spawn(entity,map,entityInfo) )
         return false;

      if (entity->existsKey("activateMsg"))
         _activateMsg = entity->getStringAtributo("activateMsg");

      return true;
   }

protected:

   std::string _activateMsg;
};
REG_FACTORY(CMyComponent);
\endcode

@subsection noLabel2 Activaci�n y desactivaci�n

Una entidad pertenece siempre a un mapa (o nivel) del juego. Un mapa al
cargarse se encuentra inactivo, no recibe atenci�n por parte del motor
de juego y por tanto no se renderizan sus objetos ni se actualiza su l�gica.

Cuando un mapa es activado y desactivado, todas sus entidades son informadas 
para que puedan realizar las tareas oportunas (como por ejemplo la entidad 
del jugador debe registrarse en el servidor l�gico para que quien lo requiera 
pueda tener acceso al jugador).

Los componentes pueden tambi�n ser conscientes de esta activaci�n/desactivaci�n
sobreescribiendo los m�todos Logic::IComponent::activate() y 
Logic::IComponent::deactivate() ya que la entidad invocar� esos m�todos de 
todos sus componentes. Por ejemplo Logic::CAvatarController se registra 
en los eventos de teclado para manejar al jugador si el componente pertenece
a la entidad del jugador.

El siguiente c�digo muestra como el componente que vamos definiendo escribe la 
cadena leida en el m�todo Logic::IComponent::spawn() cuando el mapa en el que 
se encuentra su entidad es activado y desactivado.

\code
class CMyComponent : public Logic::IComponent 
{
   DEC_FACTORIA();

public:
   ...
   
   virtual bool activate() 
   {
      std::cout << _activateMsg << std::endl;
      return true;
   }

   virtual void deactivate() 
   {
      std::cout << _activateMsg << std::endl;
   }
   ...
};
REG_FACTORY(CMyComponent);
\endcode

@subsection noLabel3 Recibiendo mensajes

El funcionamiento b�sico de un componente es recibir mensajes de
otros componentes y reaccionar ante ellos. Para eso el motor proporciona
al Logic::IComponent un mecanismo de recepci�n de mensajes para poder
hacer cosas con ellos.

La recepci�n est� separada en dos fases. Primero el motor <em>pregunta</em>
al componente si acepta el mensaje enviado, es decir, si para �l ese
mensaje tiene alg�n tipo de informaci�n �til. En caso afirmativo,
el motor invocar� en un momento posterior al m�todo para procesar el mensaje
y que el componente ejecute las acciones que considere oportunas en base
a la informaci�n recibida.

Por lo tanto, para ser capaces de recibir mensajes, los IComponent deben 
sobreescribir dos m�todos: el Logic::IComponent::acept y 
Logic::IComponent::process.
En ambos casos se recibe como par�metro el mensaje. Para saber de qu� tipo es
habr� que consultar el atributo Logic::TMessage::_type.

Para la implementaci�n de los mensajes se ha optado conscientemente por una 
implementaci�n sencilla que con un tipo de mensaje gen�rico Logic::TMessage
que tiene una serie de atributos tambi�n gen�ricos y en funci�n del tipo 
(Logic::TMessage::_type) de mensaje se usar�n unos u otros. Esta aproximaci�n 
es sencilla, pero no es �ptima desde el punto de vista de rendimiento.
Para llevar a cabo un proyecto serio esta implementaci�n <b>debe</b> ser 
reconsiderada.

El siguiente c�digo muestra la implementaci�n de los dos m�todos en
el componente CTestComponent que nos est� sirviendo de prueba,
para que interprete los mensajes enviados a la entidad cuando �sta
cambia de posici�n, y escribe por pantalla la nueva posici�n (para que
funcione habr� que incluir el fichero Logic/Entity/Message.h).

\code
class CMyComponent : public Logic::IComponent 
{
   DEC_FACTORIA();

public:
   ...

   bool accept(const TMessage &message)
   {
      return message._type == Message::SET_POSITION;
   }

   void process(const TMessage &message)
   {
      switch(message._type)
      {
      case Message::SET_POSITION:
         std::cout << "Moved to(" << message._position.x << ", " 
                   << message._position.y << ", " 
                   << message._position.z << ")\n";
         break;
      }
   }
   ...
};
REG_FACTORY(CMyComponent);
\endcode

El funcionamiento interno del motor ayudar� a entender los siguientes
apartados. En alg�n momento una entidad externa puede enviar un
mensaje a la entidad a la que pertenecemos. La entidad al recibirlos
lo que hace es preguntar uno a uno a todos sus componentes para averiguar
cu�les de ellos est�n interesados en el mensaje, o lo que es lo mismo,
para qu� componentes el mensaje resulta �til. Si un componente <em>acepta</em>
un mensaje, �ste se <em>encola</em> en la lista de mensajes a procesar
del componente.

Posteriormente, en la fase de simulaci�n de la l�gica, se conceder�
tiempo de CPU al componente para que procese todos los mensajes encolados.
Eso es realizado por el m�todo Logic::IComponent::processMessages() que
recorre la cola y va llamando sucesivamente al m�todo Logic::IComponent::process()
sobreescrito en las implementaciones concretas de cada componente.

@subsection noLabel4 Ejecutando l�gica

En general las entidades de un juego implementan la l�gica usando peque�as 
ejecuciones de un m�todo que suele llamarse algo as� como "tick()" o "update()". 
El motor del juego llama regularmente a ese m�todo (por ejemplo en cada frame), 
y espera que ejecute una m�nima parte de su comportamiento. En una arquitectura 
de componentes, la entidad lo que hace es llamar al m�todo "tick()" o "update()"
de todos sus componentes, y estos ejecutar�n ah� la parte de su comportamiento.

Aunque en el componente que hemos implementado hasta ahora no ha aparecido ning�n 
m�todo de este tipo, en realidad s� existe, declarado en Logic::IComponent::tick(). 
La implementaci�n por defecto de ese m�todo lo que hace es invocar al m�todo
Logic::IComponent::processMessages() que terminar� llamando al sobreescrito 
Logic::IComponent::process() con todos los mensajes aceptados por 
Logic::IComponent::accept().

\code
class IComponent 
{
public:
   ...

   bool IComponent::tick()
   {
      processMessages();
      return false;
   }
   ...
};
\endcode

Si nuestro componente ejecuta otro tipo de l�gica de manera aut�noma,
sobreescribremos el m�todo Logic::IComponent::tick() con la implementaci�n 
de nuestro nuevo comportamiento. De la explicaci�n anterior se deduce 
que si un componente sobreescribe el m�todo es <em>indispensable</em>
que llame a la implementaci�n del m�todo de la clase padre (o al menos
al m�todo Logic::IComponent::processMessages()). Si se olvida hacer esto,
el componente <em>nunca</em> procesar� los mensajes recibidos.

El siguiente podr�a ser un tick() que presenta un simple texto en pantalla.
Si se devuelve true implica que todo ha ido bien:

\code
class CMyComponent : public Logic::IComponent 
{
   DEC_FACTORIA();

public:
   ...

   virtual bool tick() 
   {
      // Importante no olvidar esto...
      IComponent::tick();

      std::cout << "I'm alive!" << std::endl;
      return true;
   }
   ...
};
REG_FACTORY(CMyComponent);
\endcode

\code
\endcode

Habitualmente, las entidades de los motores de juegos (y sus componentes)
tienen la posibilidad de "dormirse" de forma que el motor no pierde el 
tiempo en la invocaci�n a su m�todo de actualizaci�n para no consumir 
ciclos innecesarios cuando la entidad y los componentes no tienen tar�as
que realizar en los siguiente ciclos. En esta aproximaci�n no ha sido 
incluida esta habilidad de manera intencionada, pero quien pretenda 
reutilizar esta arquitectura deber�a plantearse incluir esta cualidad.

@author David Llans�, Marco Antonio G�mez Mart�n
@date Septiembre, 2010
*/