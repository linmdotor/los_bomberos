//---------------------------------------------------------------------------
// Galeon.cpp
//---------------------------------------------------------------------------

/**
@file Configure.cpp
Configura las opciones gr�ficas del programa Galeon. Seg�n la configuraci�n
de las opciones del precompilador (_VISUALLEAKDETECTOR) se comprueba existencia de 
leaks. En funci�n de la configuraci�n y plataforma se usa un main o un WinMain.

@see applicationGroup

@author David Llans�
@date Octubre, 2010
*/

#ifdef _DEBUG
// VLD: Completa biblioteca para detectar leaks y donde se produjeron en modo de
// depuraci�n. Ralentiza moderadamente el lanzamiento de la aplicaci�n aunque no 
// en exceso su ejecuci�n. Si se desea anular la comprobaci�n basta con comentar 
// la siguiente l�nea.
//#define _VISUALLEAKDETECTOR

#ifdef _VISUALLEAKDETECTOR
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <vld.h> 
#endif // _VISUALLEAKDETECTOR

#endif // _DEBUG

#include <OgreRoot.h>

/**
Main que lanza una ventana de configuraci�n de Ogre para poder
modificar las opciones gr�ficas sin tener que editar a mano el
fichero ogre.cfg.
*/
#if (defined _DEBUG) || !(defined _WIN32)
int main(int argc, char **argv) 
{
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
#endif // (defined _DEBUG) || !(defined _WIN32)

	// Aqui llegamos a lo que verdaderamente importa.
	{
		// Inicializamos el punto de acceso a Ogre con una definici�n
		// diferente de los plugins si estamos en release o en debug.
#ifdef _DEBUG
		Ogre::Root *root = new Ogre::Root("plugins_d.cfg");
#else
		Ogre::Root *root = new Ogre::Root("plugins.cfg");
#endif
		// Lanzamos la ventana de depuraci�n
		root->showConfigDialog();
			
		delete root;
	}

	return 0;

} // main
