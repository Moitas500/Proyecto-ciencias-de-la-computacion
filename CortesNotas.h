#ifndef CORTESNOTAS_H
#define CORTESNOTAS_H
#include<iostream>
#include<string>
#include "estructura.h"
#include "Trio.h"
using namespace std;

struct cortesNotas{
	trio *notas;
};

class cortesN {
	trio *notas;
	int tam, posActual;
	int getPosActual();
	public: cortesN(int tamanio){
		notas = new trio[tamanio];
		tam=tamanio;
		trio aux;
		aux.tipo="NN";
		for(int i=0;i<tamanio;i++){
			notas[i]=aux;
		}
		posActual=0;
	}
	void insertarActividad(string tipoE,int porcentajeP, listaD<listaD<int> > puntosP );
	void eliminarActividad(int posicion);
	void cambiarActividad(int posicion, trio actividad);
	trio getElemento(int clave);
	int getTam();
	
	
	
};
int cortesN::getPosActual(){
	int valor=0;
	while(valor<tam){
		if(notas[valor].tipo=="NN")
			break;
		else 
			valor++;
	}
	return valor;
	
} 
void cortesN::insertarActividad(string tipoE,int porcentajeP, listaD<listaD<int> > puntosP ){
		posActual=getPosActual();		
		if(posActual<tam){
			trio aux;
			aux.tipo=tipoE;
			aux.porcentaje=porcentajeP;
			aux.puntos=puntosP;
			notas[posActual]=aux;
		} else {
			cout<<"El arreglo esta lleno"<<endl;
		}
}
void cortesN:: eliminarActividad(int posicion){
	//Como no se puede eliminar, cambio el objeto de la posicion del arreglo para que no se muestre
	trio aux;
	aux.tipo="NN";
	if(posicion<tam && posicion>=0){
		notas[posicion]=aux;
	} else {
		cout<<"La clave no se encuentra en el arreglo"<<endl;
	}
}
void cortesN::cambiarActividad(int posicion, trio actividad){
	if(posicion<tam && posicion >=0)
	{
		notas[posicion]=actividad;
	}
}
trio cortesN::getElemento(int clave){
	//Recordar solo imprimir los que aux.tipo no sean igual a NN
	return notas[clave];
}
int cortesN::getTam(){
	return tam;
}

#endif
