Para modificar la gram�tica del mapa modificar los archivos scanner.ll y parser.yy
y a partir de ah�, mediante flex y bison en Linux o con CygWin, generar los archivos 
Parser.h, Parser.cpp y Scanner.cpp con:

bison --defines=Parser.h -o Parser.cpp Parser.yy
flex -oScanner.cpp Scanner.ll

Tambi�n se generar�n location.hh, position.hh y stack.hh. Mover los 6 ficheros
generados a ./Src y volver a generar el proyecto.