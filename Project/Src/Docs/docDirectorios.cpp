/**

@defgroup directorios Estructura de directorios

@brief <p/>

La estructura de directorios de GALEON es la siguiente:

<ul>
   <li> Dependencies: contiene
   todas las dependencias (librer�as externas) que
   se necesitan para compilar GALEON. En este directorio
   est� por ejemplo Ogre.

   El directorio est� pensado para contener tanto
   las dependencias que <em>se deben compilar</em>
   (como por ejemplo Ogre), como las que no
   (como podr�an ser las librer�as del motor de f�sica).

   Adem�s de un directorio por cada librer�a que
   se debe compilar, tiene los subdirectorios include
   (donde est�n los ficheros de cabecera), lib (donde
   aparecen los ficheros con las librer�as est�ticas
   que pueden/deben usarse en la fase de enlazado)
   y bin (con las DLLs que deben estar accesibles
   a GALEON en el momento de ejecutarse).
   </li>

   <li> Doc: directorio pensado para tener ficheros relacionados
   con la documentaci�n que no est� contenida
   directamente en el c�digo fuente.
   </li>

   <li> Exes: directorio donde el proceso de compilaci�n
   deposita el ejecutable de Galeon. En este directorio
   se guardan todos los recursos (gr�ficos, sonoros, etc.)
   que utiliza el juego.

   Tener un directorio para los ejecutables permite
   compartir los ficheros de los recursos para distintas
   versiones del juego (versi�n Release, Debug).
   </li>

   <li> Projects: contiene los ficheros de proyecto de
   Visual Studio.
   </li>

   <li> Src: c�digo fuente de Galeon.
   </li>

</ul>

En el directorio raiz, adem�s, aparece el fichero con
la soluci�n de Visual Studio de Galeon (se ha preferido
dejar en el directorio ra�z por comodidad a la
hora de abrir el proyecto) y un script para
compilar Galeon desde cero autom�ticamente utilizando
Ant. Puedes ver m�s informaci�n sobre c�mo compilar
Galeon en @ref compilando.




@author Marco Antonio G�mez Mart�n
@date Septiembre, 2010

*/