#ifndef CLASE_H     
#define CLASE_H   
#include <iostream>
#include <stdlib.h>
#include "listaD.h"
#include "pila.h"
#include "Archivos.h"
#include "Profesor.h"
#include "estructura.h"

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
		Archivo file;	
		profes= file.leerArchivoProfesor("Profesores/listaProfesores.txt");
		arregloClases= new clasesArray[profes.getTam()];
		// se crea una lista de archivos que ha subido el profesor
		listaD<string> archivos;
		archivos.insertar(1,"notassegundoCorte.txt"); //se insertan algunos datos de prueba
		archivos.insertar(0,"notasprimerCorte.txt");
		//se crea una estructura la cual es un un codigo y la lista de archivos
		duo<maestro> aux;
		int i=0;
		clasesArray clasesAux;
		notas clase;
		while(profes.obtener(aux)){
			maesAux= aux.dato;
			clasesAux.cedula=maesAux.cedula;
			clasesAux.clases=  new notas[maesAux.numClases];
			for(int j=0;j<maesAux.numClases;j++){
				clase.codigo="CCI82";
				clase.archivos = archivos;
				clasesAux.clases[j]=clase;
				//cout<<"funcionaa"<<endl;
			}
			arregloClases[i]=clasesAux;	
			i++;
		}
		profes.reiniciarPuntero();
		/*for(int i=0;i<file.getPilaTam();i++){
			
			maesAux= profes.Pop();
			cout<<maesAux.cedula<<endl;//************************************ERROR*******************
			arregloClases[i] = new clasesArray;
			arregloClases[i]->cedula = maesAux.cedula;
			for(int j=0;j<maesAux.numClases;j++){
				notas *clase = new notas();
				clase->codigo="CCI82";
				clase->archivos = archivos;
				arregloClases[i]->clases[i]=clase;
			}
				
		}*/

		// se crea una estructura la cual tiene la cedula y un arreglo que es el que guarda las clases de cada profesor
		/*clasesArray *profesor1= new clasesArray;
		profesor1->cedula = 79458124;
		profesor1->clases[0] = notasProf1;*/
		//arreglo de clases principal el que guarda la cedula de cada profesor y su arreglo de clases qque apunta a la lista de archivos
		/*arregloClases[0]=profesor1;*/
	};
	void imprimir();
	void anadirClase(int cedula);
	void actualizar();
	void actualizarArchivos();
	string buscarArchivos();
	~clase();
};

void clase::imprimir(){
	//funcion de prueba pero se puede cambiar para que imprima los archivos de cada profesor segun su cedula y codigo de clase (tambien se puede pensar en usar sobrecarga)
	arregloClases[0].clases[0].archivos.obtenerTodos();
	cout<<arregloClases[4].cedula<<endl;
	//arregloClases[0]->clases[0]->archivos->obtenerTodos();
}
void clase::anadirClase(int cedula){
 //pensar en usar algoritmos de busqueda en arreglos	
}

void clase::actualizar(){
	//consulta en la lista  profesores si hay un nuevo profesor o si un profesor existente tiene más cursos asignados
}

void clase::actualizarArchivos(){
	//discutir parametros a pasar
}

string clase::buscarArchivos(){
	//posibles parametros cedula, codclasse, nombrearchivo
	//se puede utilizar la funcion de leer los archivos txt
}
#endif

