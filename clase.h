#ifndef CLASE_H     
#define CLASE_H   
#include <iostream>
#include <stdlib.h>
#include "listaD.h"

struct notas {string codigo;
             listaD<string> *archivos;
			 };
struct clasesArray {int cedula;
             notas *clases[];
			 };

class clase{
	
	clasesArray *arregloClases[3]; //¿Puede ser un doble aputador?
	public: clase(){
		//pruebas
		// se crea una lista de archivos que ha subido el profesor
		listaD<string> *archivos= new listaD<string>;
		archivos->insertar(1,"notassegundoCorte.txt"); //se insertan algunos datos de prueba
		archivos->insertar(0,"notasprimerCorte.txt");
		//se crea una estructura la cual es un un codigo y la lista de archivos
		notas *notasProf1 = new notas;
		notasProf1->codigo ="CCI82";
		notasProf1->archivos = archivos;
		// se crea una estructura la cual tiene la cedula y un arreglo que es el que guarda las clases de cada profesor
		clasesArray *profesor1= new clasesArray;
		profesor1->cedula = 79458124;
		profesor1->clases[0] = notasProf1;
		//arreglo de clases principal el que guarda la cedula de cada profesor y su arreglo de clases qque apunta a la lista de archivos
		arregloClases[0]=profesor1;
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
	arregloClases[0]->clases[0]->archivos->obtenerTodos();
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

