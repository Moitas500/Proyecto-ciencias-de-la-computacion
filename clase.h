#ifndef CLASE_H     
#define CLASE_H   
#include <iostream>
#include <stdlib.h>
#include "listaD.h"
#include "Archivos.h"
#include "Profesor.h"
#include "estructura.h"
#include "Lector.h"

using namespace std;

struct notas {string codigo;
             listaD<string> archivos;
			 };
struct clasesArray {int cedula;
             notas *clases;
			 };

class clase{
	listaD<maestro> profes;
	clasesArray *arregloClases;
	maestro maesAux; //¿Puede ser un doble aputador?
	
	public: clase(){
		lector l;
		Archivo file;
		duo<maestro> maestAux;
		maestro maest;
		string clase;
		profes= file.leerArchivoProfesor("Profesores/listaProfesores.txt");
		arregloClases= new clasesArray[profes.getTam()-1];
		profes.obtener(maestAux);//->El primer dato no sirve
		for(int z=0;z<profes.getTam()-1;z++){
			clasesArray aux1;
			notas aux2;
			profes.obtener(maestAux);
			maest = maestAux.dato;
			aux1.cedula=maest.cedula;
			aux1.clases= new notas[maest.nombresClases.getTam()];
			duo<string> clasesAux;
			for(int j=0;j<maest.nombresClases.getTam();j++){
				maest.nombresClases.obtener(clasesAux);
				aux2.codigo=clasesAux.dato;
				listaD<string> archivosA;
				archivosA= l.leerArchivos(clasesAux.dato);
				aux2.archivos=archivosA;
				aux1.clases[j]=aux2;
			}
			arregloClases[z]=aux1;
		}
	}
			listaD<string> getArchivosCurso(int cedula, string nombreCurso);
	//~clase();
};
	listaD<string> clase::getArchivosCurso(int cedula, string nombreCurso){
		int primero=0;
	    int ultimo=profes.getTam()-2;
	    int medio=(primero+ultimo)/2;
	    listaD<string> nArchivos;
	    int pos=-1;
	    
	    while (primero<=ultimo)			//Busqueda Binaria de la cedula
	    {
	        if (arregloClases[medio].cedula< cedula)
	        {
	            primero=medio+1;
	        }else if (arregloClases[medio].cedula== cedula) {
	            //Se encontro la posición 
	            pos=medio;
	            break;
	        }
	        else {
	            ultimo = medio - 1;
	        }
	
	        medio = (primero+ultimo)/2;
	    }
	    if (primero>ultimo)
	    {
	        cout<<cedula<<" no se encontro"<<endl;;
	    }
	    
	    if(pos!=-1){
	    	int posAux=-1;
	    	int tam= sizeof arregloClases[pos].clases / (sizeof (*arregloClases[pos].clases)/10);	//Ese 10 es machetazo
	    	for(int i=0;i<tam;i++){
	    		if(arregloClases[pos].clases[i].codigo==nombreCurso){
	    			posAux=i;
				}
			}
			if(posAux!=-1){
				nArchivos= arregloClases[pos].clases[posAux].archivos;
			} 
		}
		return nArchivos;	//Revisar si el tamaño es cero, si es así es por que no se encontró
}

#endif
