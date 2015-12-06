/**

@defgroup compilando Compilacion de Galeon

@section introCompilando Introducci�n

La compilaci�n de Galeon desde cero requiere la
ejecuci�n de un gran n�mero de pasos. Para evitar
la tarea tediosa de realizarlos manualmente,
Galeon dispone de un script para Ant que
se encarga de hacerlo autom�ticamente.

Antes de poder utilizarlo, no obstante, es
imprescindible comprobar que en la m�quina
donde se pretende compilar Galeon est�n
instalados ciertos prerequisitos.

La secci�n siguiente detalla cu�les son
esos requisitos y c�mo conseguirlos. Posteriormente
se explica c�mo compilar Galeon una vez instalados.
La �ltima secci�n describe c�mo ser�a el proceso
de compilaci�n manual sin la utilizaci�n de Ant.
Aunque est� altamente desaconsejado utilizar
ese m�todo, la secci�n es interesante por s� misma
porque en la pr�ctica lo que hace es describir
todo lo que el script de Ant hace por nosotros,
algo que puede ayudar a entender mejor la estructura
de directorios de Galeon.

@section requisitos Requisitos de Galeon

Para poder trabajar con Galeon es preciso que la m�quina
tenga instalado lo siguiente:

<ul>
   <li>Visual Studio 2010.</li>

   <li>DirectX: es necesario tener instaladas las SDK
   de DirectX, que incluyen los ficheros de cabecera
   y bibliotecas necesarios para poder compilar el
   motor gr�fico. Las SDK se pueden obtener en la p�gina
   de Microsoft. Es importante instalarlas <em>despu�s</em>
   de la instalaci�n de Visual Studio, pues el
   instalador altera (m�nimamente) la configuraci�n
   del IDE para que encuentre los ficheros al compilar.

   Por �ltimo, hay que asegurarse de que tras la
   instalaci�n se queda establecida la variable de
   entorno <tt>DXSDK_DIR</tt> al directorio raiz
   de la instalaci�n.</li>

   <li>Ant: esta herramienta de Apache permite la compilaci�n
   de Galeon en un solo paso. S�lo es necesario si
   se opta por este tipo de generaci�n (�altamente
   recomendable!). Ant se puede descargar de http://ant.apache.org/.

   Como a�adido, para poder llamar a Visual Studio
   desde los script de Ant es necesario extender la
   instalaci�n de Ant. Para eso, hay que descargar
   <a href="http://gaia.fdi.ucm.es/people/marcoa/development/vcTasks">
   vcTask</a> y copiar el .jar al directorio lib
   de la instalaci�n.</li>
</ul>

	Opcionalmente tambi�n puedes instalar:

<ul>
   <li>Doxygen: si planeas generar la documentaci�n de Galeon.
   Est� disponible <a href="http://www.stack.nl/~dimitri/doxygen/">aqu�</a>.

   En ese caso, tambi�n puede que te interese a�adir a Ant la posibilidad
   de generar la documentaci�n directamente, instalando
   la tarea disponible <a href="http://ant-doxygen.blogspot.com/">aqui</a>.</li>

   Puedes encontrar m�s informaci�n en la secci�n \ref generarDocumentacion
</ul>

@section usoDeAnt Compilaci�n autom�tica con Ant

Para compilar Galeon autom�ticamente, basta con ejecutar Ant desde
el directorio ra�z de Galeon.

<pre>
c:\Galeon> ant
Buildfile: build.xml

debug:

llamaBuilds:

debug:

llamaBuilds:

debug:

compilaSln:

windowsbuilder:
      [vc10] Command= C:\...\\IDE\devenv.com /out c:\\Galeon/vslog.txt ...
      [vc10] 
      [vc10] Microsoft (R) Visual Studio 10.0.30319.1.
      [vc10] (C) Microsoft Corp. Reservados todos los derechos.
      [vc10] 1>------ Operaci�n Generar iniciada: proyecto: zlib, configuraci�n: Debug Win32 ------
      [vc10] 2>------ Operaci�n Generar iniciada: proyecto: ZLib-freeImage, configuraci�n: Debug Win32 ------
      [vc10] 2>Compilando...
      [vc10] 1>Compilando...
      [vc10] 2>adler32.c
      [vc10] 1>compress.c
</pre>

Despu�s de mucho rato y m�s de 3GB menos en el disco duro, tanto
la versi�n de Debug como la de Release de Galeon est�n generadas
en el directorio Exes.

@section compilacionManual Compilaci�n manual

Lo primero que se debe hacer es compilar las dependencias adicionales
que tiene Galeon, que se encuentran en el directorio dependencies:

<ol>
   <li>Compilar las dependencias de Ogre: para eso, abrir
   el proyecto en Visual Studio 2010 (<tt>dependencies/OgreDependencies/OgreDependencies.VS2008.sln</tt>),
   y generar las versiones Debug y Release (lo m�s f�cil tanto en
   este como en el resto de proyectos es usar el men� Generar - Compilaci�n por lotes -
   Seleccionar todo - Generar
   </li>

   <li>Generar los proyectos de Ogre: la distribuci�n
   de Ogre NO incluye los proyectos de Visual Studio, sino
   que hay que generarlos con una aplicaci�n aparte (CMake).
   Para evitar complicaciones, la aplicaci�n est� en
   el directorio dependencies, por lo que no hay que instalarla.

   Para generarlos, se debe crear el directorio <tt>build</tt>
   dentro de la distribuci�n de ogre, y luego invocar a
   CMake (el comando de ejecuci�n de CMake es algo largo,
   pues se desactiva la compilaci�n de bastantes componentes
   que Galeon no utiliza):

   <pre>
c:\Galeon\dependencies\Ogre> mkdir build
c:\Galeon\dependencies\Ogre> cd build
c:\Galeon\dependencies\Ogre\build> ..\\CMake\bin\cmake.exe -DOGRE_DEPENDENCIES_DIR=..\.. -DOGRE_BUILD_SAMPLES=FALSE -DOGRE_BUILD_TOOLS=FALSE -DOGRE_BUILD_COMPONENT_PAGING=FALSE -DOGRE_BUILD_COMPONENT_TERRAIN=FALSE -DOGRE_BUILD_PLUGIN_PCZ=FALSE -DOGRE_BUILD_PLUGIN_OCTREE=FALSE -DOGRE_BUILD_PLUGIN_BSP=FALSE -DOGRE_INSTALL_TOOLS=FALSE ..
-- Building for: Visual Studio 10 2010
-- Check for working C compiler: cl
-- Check for working C compiler: cl -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: cl
...
-- Configuring done
-- Generating done
-- Build files have been written to: c:/Galeon/dependencies/Ogre/build
    </pre>
   </li>

   <li>Compilar Ogre. Para eso se abre la soluci�n <tt>OGRE.sln</tt>
   del directorio <tt>build</tt> y se compilan todos los proyectos
   que tienen.
   </li>

   <li>Copiar los ficheros resultantes de la compilaci�n de
   Ogre donde los espera Galeon. Los ficheros de inclusi�n
   de Ogre deben copiarse a <tt>dependencies/include</tt>,
   las bibliotecas est�ticas a <tt>dependencies/lib</tt> y
   las DLLs y otros ficheros utilizados durante la ejecuci�n
   ir�n a <tt>dependencies/bin</tt>. M�s concretamente:
	<ol>
	   <li>Crear el directorio <tt>dependencies/include/OGRE</tt>
	   y copiar en �l el contenido del directorio
	   <tt>dependencies/OGRE/OgreMain/include</tt> y el
	   de <tt>dependencies/OGRE/build/include</tt>.</li>

	   <li>Copiar al directorio <tt>dependencies/lib/Debug</tt> todos
	   los .lib que se hayan generado en <tt>build/lib/Debug</tt>. Hacer
	   lo mismo con los Release.</li>

	   <li>Copiar al directorio <tt>dependencies/bin/Debug</tt>
	   las DLLs que se habr�n generado en <tt>build/bin/Debug</tt>, as�
	   como los ficheros con extensi�n <tt>.cfg</tt> (en la pr�ctica
	   ni resources.cfg ni samples.cfg ni quakemap.cfg son
	   necesarios). Hacer lo mismo con las correspondientes versiones
	   de Release.</li>
	</ol>
   </li>

   <li>Generar la soluci�n de Visual Studio de CEGUI. Para eso, basta
   con ejecutar el fichero <tt>dependencies/CEGUI/projects/premake/build_vs2008.bat</tt>.
   </li>

   <li>Convertir a Visual Studio 2010 abriendo la soluci�n generado con 
   Visual Studio 2010.
   </li>

   <li>Compilar todos los proyectos de la soluci�n CEGUI.sln que
   se habr� creado en ese mismo directorio.
   </li>

   <li>Igual que con Ogre, copiar los resultados de la compilaci�n
   a los directorios include, lib y bin:
	   <ol>
		<li>Crear el directorio <tt>cegui</tt> dentro de
		<tt>dependencies/include</tt> y copiar en �l 
		el directorio <tt>dependencies/cegui/include</tt>
		(en la copia se pueden omitir los ficheros con
		extensi�n *.in y *.am).
		</li>

		<li>Las bibliotecas compiladas habr�n quedado en
		<tt>dependencies/cegui/lib</tt>; las que terminan
		en <tt>_d</tt> son las versiones Debug que habr�
		que copiar a <tt>dependencies/lib/Debug</tt>, mientras
		que las dem�s son las versiones en Release. Copiar
		a cada uno de ellos los ficheros CEGUIBase,
		CEGUIExpatParser, CEGUIFalagardWRBase, CEGUIOgreRenderer
		y CEGUISILLYImageCodec, que son los componentes de CEGUI
		que utiliza Galeon.
		</li>

		<li>Por su parte, las DLLs se habr�n quedado en
		<tt>dependencies/cegui/bin</tt> y siguen la misma
		nomenclatura. Hay que copiar a <tt>dependencies/bin/Debug</tt>
		las DLLs de depuraci�n de las bibliotecas listadas anteriormente
		y a <tt>dependencies/bin/Release</tt> las versiones
		Release. Tambi�n habr� que copiar una �ltima DLL
		que CEGUI tiene de dependencia que se encuentra en
		<tt>dependencies/CEGUI/dependencies/bin</tt> llamada
		SILLY (y la correspondiente SILLY_d).
		</li>
	   </ol>
   </li>

   <li>Compilar el proyecto Visual Leak Detector de la soluci�n vld.sln 
   que se encuentra en <tt>dependencies/VisualLeakDetector/src</tt>.
   </li>

   <li>Igual que con Ogre y CEGUI, hay que copiar los resultados de la compilaci�n
   a los directorios include, lib y bin:
	   <ol>
		<li>Copiar los ficheros <tt>vld.h</tt> y <tt>vld_def.h</tt>, que
		se encuentran en <tt>dependencies/VisualLeakDetector/src</tt>, 
		dentro de <tt>dependencies/include</tt>
		</li>

		<li>Copiar la biblioteca <tt>vld.lib</tt>, que
		se encuentran en <tt>dependencies/VisualLeakDetector/bin</tt>, solo a 
		<tt>dependencies/lib/Debug</tt> ya que en Release no se necesita
		VLD.
		</li>

		<li>Por su parte, la DLL habr� quedado en
		<tt>dependencies/VisualLeakDetector/bin</tt> y se llamar� <tt>vld_x86.dll</tt>
		o <tt>vld_x64.dll</tt> en funci�n de la arquitectura del ordenador 
		(32 o 64 bits). Hay que copiarla a <tt>dependencies/bin/Debug</tt>.
		Tambi�n habr� que copiar una �ltima DLL (<tt>dbghelp.dll</tt>), de la que 
		Visual Leak Detector tiene dependencia, en el mismo directorio. En funci�n 
		de la arquitectura del ordenador (32 o 64 bits) se deber� coger de 
		<tt>dependencies/VisualLeakDetector/bin/Win32</tt> o de
		<tt>dependencies/VisualLeakDetector/bin/Win64</tt>.
		</li>
	   </ol>
   </li>

   <li>El �ltimo paso, compilar Galeon. Para eso se abre la
   soluci�n Galeon.sln del ra�z, y se compilan todos sus
   proyectos. Al final, los ejecutables de la versi�n
   de depuraci�n y release habr�n quedado en el directorio <tt>Exes</tt>.
   No obstante, para que se puedan ejecutar las versiones Release
   y Debug de Gale�n, se deber� mover el contenido de 
   <tt>dependencies/bin/Release</tt> y <tt>dependencies/bin/Debug</tt>
   al directorio <tt>Exes</tt>.
   </li>

</ol>

@section generarDocumentacion Generaci�n de la documentaci�n

Como ya se ha comentado previamente, la generaci�n de la documentaci�n
hace uso de la herramienta <a href="http://www.stack.nl/~dimitri/doxygen/">Doxygen</a>.

Es posible lanzarla directamente desde el directorio de Gale�n:

<pre>
$GALEON\> doxygen
</pre>

La documentaci�n se crear� en el directorio <tt>DocumentacionDoxygen</tt>.

Si se instala en Ant la tarea <a href="http://ant-doxygen.blogspot.com/">ant-doxygen</a>
(copiando el fichero <tt>.jar</tt> en la <tt>$ANT_PATH\lib</tt>), tambi�n ser�
posible generarla mediante:

<pre>
$GALEON\> ant doxygen
</pre>

En este caso, la salida de doxygen no se mostrar�, lo que en ocasiones
puede acelerar el proceso a costa de no ver posibles errores y avisos.

@author Marco Antonio G�mez Mart�n, David Llans�
@date Septiembre, 2010

*/
