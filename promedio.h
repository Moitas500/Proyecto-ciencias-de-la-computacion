#ifndef CLASE_H     
#define PROMEDIO_H   
#include <iostream>
#include <stdlib.h>
#include "listaD.h"
#include "clase.h"
#include "Archivos.h"
#include "Profesor.h"
#include "estructura.h"
#include "Lector.h"


class promedio{
	Archivo  file;
	clase clases;
	public: promedio(){
	
	};
	float promedioEstudiante(int cedula, string nombreClase,string nombreEstudiante,string apellidoEstudiante);
	
};

float  promedio::promedioEstudiante(int cedula, string nombreClase,string nombreEstudiante, string apellidoEstudiante){
	float promedio;
	int i;
	int puntos=0;
	int auxlsTam;
	float porcentajeAct,promActividad=0,promperAct=0;
	int posListaCorte=0,posAct=0,posNumAct=0;
	listaD<cortesN> cortes;
	listaD<string> aux;
	listaD<Estudiante> estudiantes;
	listaD<float> notasAux;
	duo<string> nombreA;
	duo<Estudiante> estudiante;
	duo<cortesN> corte;
	duo<listaD<int> > lsactPuntos;
	duo<int> percent;
	duo<float> nota;
	trio trioAux;
	string archivo;
	Estudiante e;
	e.setApeliidos("NN");
	trio actividad; //esta estructura va a guardar, según el archivo y a qué actividad corresponda la informacion de la actividad que se encuentra en el esquema de cortes
	cortes= file.leerNotasCorte(nombreClase); //buscar el archivo de cortes de notas de la clase n.codigo
	aux=clases.getArchivosCurso(cedula,nombreClase); //se obtiene la  lista de archivs de  la clase
	while(aux.obtener(nombreA)){
	listaD<listaD<int> > auxls;
		////////////////////////////////////////////////////////////////////////
		if(posListaCorte!=0){
				
			if(posNumAct==auxlsTam){	//Revisa si ya se llego a la ultuma actividad de la actividad del corte en el que se va
				posNumAct=0;
				posAct++;
				if(posAct==corte.dato.getTam()-1){//Revisa si ya se llegó a la ultima actividad del corte
					posAct=0;
					cortes.obtener(corte);		//Se cambia de corte
					posListaCorte++;
				}
			}
		}else {				//Solo se ejcuta la primera vez
			cortes.obtener(corte);	
			posListaCorte++;
		}
		listaD<int> lspuntos;	//Esto es la lista de temas y puntos 
		trioAux=corte.dato.getElemento(posAct);
		porcentajeAct= (float) trioAux.porcentaje/100;	//Guarda el porcentaje de la activdad (Parcial,quicez...etc)
		auxls=trioAux.puntos;
		auxlsTam=auxls.getTam();
		auxls.obtener(lsactPuntos);
		lspuntos=lsactPuntos.dato;
		puntos=lspuntos.getTam();
		posNumAct++;		//Como ya se leyó la actividad, se pasa a la siguiente
		/////////////////////////////////////////////////////////////////////////////
		archivo=nombreA.dato;
		estudiantes=file.getEstudiantesCurso(nombreClase,archivo,puntos);
		for(i=0; i<estudiantes.getTam();i++){
			estudiantes.obtener(estudiante);
			e=estudiante.dato;
			if(e.getNombre() == nombreEstudiante && e.getApellidos()==apellidoEstudiante){   //revisar es linea
				i=estudiantes.getTam();
			}
		}
		if(e.getApellidos() != "NN"){
			notasAux= e.getNotas();
			for(i=0; i<notasAux.getTam();i++){
				 lspuntos.obtener(percent);
				 notasAux.obtener(nota);
				 promActividad+= nota.dato*((float) percent.dato/100);
			}
			promperAct+=promActividad;
			promActividad=0;
				if(posNumAct==auxlsTam){	//Revisa si ya se llego a la ultuma actividad de la actividad del corte en el que se va
				promedio+=(promperAct/auxlsTam)*porcentajeAct;
				promperAct=0;
			}
		}else{
			cout<<"no se encontro  estudiante para  este archivo "<<endl;
		}
	//Buscar el estudiante en e;
	//Comparar el estudiante obtenido con el cortes de notas para asi sacar el promedio
	}
	return promedio;
}	
#endif
