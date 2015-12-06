/**
@file Documentacion.h

Fichero "dummy" sin nada de c�digo, utilizado �nicamente para mantener 
documentaci�n de Doxygen de la parte de mapas de entidades l�gicas.

@see mapGroup

@author David Llans�
@date Septiembre, 2010
*/

/**
@defgroup mapGroup Mapas de entidades l�gicas

Las entidades de la capa l�gica (ver @ref entityGroup) se organizan en 
mapas l�gicos. As� pues, la clase Logic::CMap se encarga de almacenar 
todas las entidades del mapa, tanto aquellas que tienen representaci�n 
gr�fica y se ven como entidades puramente l�gicas. 
<p>
El mapa de entidades es el responsable de gestionar la activaci�n y
desactivaci�n de �stas. Tiene un m�todo de actualizaci�n Logic::CMap::tick()
que se encarga de actualizar todas las entidades y tiene tambi�n m�todos 
para recuperar entidades, tanto por su nombre como por su tipo y por su 
identificador.
<p>
Para la generaci�n y adici�n de entidades a un mapa se dispone de una
factor�a de entidades Logic::CEntityFactory que es la �nica instancia que
puede crear o destruir entidades. Para poder crear entidades, en esta
factor�a se cargan las definiciones blueprints de las entidades. El fichero 
que contiene la definici�n es muy simple. Cada l�nea corresponde a una 
entidad que viene definida por una serie de palabras separadas por espacios 
donde la primera palabra es el tipo de la entidad y el resto son los 
componentes que conforman dicha entidad:

\code
...
Player CAvatarController CAnimatedGraphics
...
\endcode

En la l�nea anterior estar�amos definiendo la entidad tipo <code>Player</code>
que consta de dos componentes <code>CAvatarController</code> y 
<code>CAnimatedGraphics</code>. 
<p>
Una vez se han cargado las definiciones de entidades del fichero o ficheros 
blueprints, se pueden crear entidades en un mapa. Para el ensamblaje de la 
entidad se usa la factor�a de componentes Logic::CComponentFactory y tras 
a�adir la entidad al mapa se inicializa.
<p>
Logic::CEntityFactory es tambi�n responsable de la destrucci�n de entidades
de un mapa, pero la destrucci�n de una entidad en medio de un tick() del
mapa l�gico es potencialmente peligrosa, ya que no se sabe si otras entidades
tendr�n acceso a la entidad, si la propia entidad se encuentra en medio de su
actualizaci�n, etc. Es por ello que se recomienda hacer uso de la funci�n 
Logic::CEntityFactory::deferredDeleteEntity() que en vez de destruir la entidad
al instante espera a que se invoque Logic::CEntityFactory::deleteDefferedEntities()
antes del siguiente tick() del mapa para destruir todas las entidades pendientes 
de destruir.
<p>
Para simplificar la tar�a de generar un nivel a partir de un fichero con una 
descripci�n de mapa existe la funci�n est�tica Logic::CMap::createMapFromFile(). 
Para ello se ayuda del parseador de mapas (ver @ref mapParserGroup) que parsea 
un fichero generando una estructura tipo lista con la descripci�n de todas
las entidades del mapa. Una vez se tienen todas las descripciones de 
entidades se usa la factor�a de entidaes para generar e inicializar todas las
a�adi�ndolas al mapa que devuelve la funci�n.

@author David Llans�
@date Septiembre, 2010
*/