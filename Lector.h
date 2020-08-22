#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include "listaD.h"
#ifndef LECTOR_H     
#define LECTOR_H

using namespace std;

class lector{
  		/* Función para devolver un error en caso de que ocurra */	
  		public: lector(){
  			
		  }
		  listaD<string>leerArchivos(string nombreDir);
};


listaD<string>lector::leerArchivos(string nombreDir){

  	struct dirent *ent;
  	string linea;
//	Se convierte el string a un arreglo de carcateres
	string aux="./clases/"+nombreDir;
 	char p[aux.length()];
	for(int i=0;i<sizeof(p);i++){
		p[i]=aux[i];
	}	
	listaD<string> archivos;
	int clave=0;
	/* Con un puntero a DIR abriremos el directorio */
  	DIR *dir;
	dir = opendir (p);

  /* Miramos que no haya error */
  if (dir != NULL)
 {
	  /* Una vez nos aseguramos de que no hay error, ¡vamos a jugar! */
	  /* Leyendo uno a uno todos los archivos que hay */
	  while ((ent = readdir (dir)) != NULL)
	    {
	      /* Nos devolverá el directorio actual (.) y el anterior (..), como hace ls */
	      if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
		    {
		      archivos.insertar(clave,ent->d_name);
		      clave++;
		    }
	    }
	    closedir (dir);
	}
    //Si el tamaño es cero, significa que hubo un error en la lectura del archivo
    return archivos;
}
#endif
