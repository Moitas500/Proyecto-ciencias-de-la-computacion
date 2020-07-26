#ifndef LISTAD_H
#define LISTAD_H
#include <iostream>
#include "estructura.h"

using namespace std;

template <class T>
class listaD{
	duo <T> *inicio, *final, *puntero;
	int tam;		
	public: listaD(){
		tam=0;
		inicio = new duo <T>;
		final = new duo <T>;
		inicio->clave= -1;
		final->clave=50505050505050;
		inicio->sig=final;
		puntero=inicio;
	}
	bool lista_vacia();
	void insertar(int clave, T dato);
	void borrar(int clave);
	void cambiar(int clave, T dato);
	void obtenerTodos();	
	duo<T> obtener(int clave);
	bool isIN(int clave);
	bool obtener(duo<T> &estructura);		//Usar solo al momento de guardar el archivo;
	void reiniciarPuntero();
	int getTam();	
};

template <class T>
bool listaD<T>::lista_vacia(){
	if(tam==0){
		return true;
	}
	else {
		return false;
	}
}

template <class T>
void listaD<T>::insertar(int clave,T dato)
{
	duo <T> *aux,*nuevo = new duo <T>;
	nuevo->clave = clave;
	nuevo->dato = dato;
	aux=inicio;
	while(clave>aux->sig->clave){
		aux=aux->sig;
	}
	nuevo->sig=aux->sig;
	aux->sig= nuevo;
	tam++;
}

template <class T>
void listaD<T>::borrar(int clave)
{	duo <T> *temp,*anterior;
	temp = inicio;
	if(inicio->sig == final){
		cout << "No hay nada para borrar" << endl;
	}
	else{
		while((clave != temp->clave && temp->sig != final) || temp->clave>clave ){
			anterior=temp;
			temp=temp->sig;
		}
		if(temp->clave==clave){
			//Toca borrar la clave
			anterior->sig=temp->sig;
			delete temp;
			tam--;
		}
		else {
			cout<<"No se encontró la clave"<<endl;
		}
		
	}
}
template <class T>
void listaD<T>::cambiar(int clave, T dato){
	duo <T> *aux= inicio;
	if (lista_vacia() != true){
		while(aux->clave<clave )
		{
			aux = aux->sig;
		}
		if(aux->clave == clave){
			aux->dato= dato;
		}
	}
		
}

template<class T>
void listaD<T>::obtenerTodos(){
	duo<T> *aux;
	if(lista_vacia() != true){
		aux= inicio->sig;
		while(aux != final){
			cout<<aux->clave<<"   "<<aux->dato<<endl;
			aux=aux->sig;
		}
	} else {
		cout<<"La lista esta vacia"<<endl;
	}
}

template<class T>
duo<T> listaD<T>::obtener(int clave){
	duo<T> *aux= inicio->sig;
	while(clave>aux->clave){
		aux=aux->sig;
	}
	if( aux->clave==clave){
		return *aux;
	} else {
		cout<<"No se encontró la clave"<<endl;
		aux->clave=-1;
		return *aux;
	}
}

template<class T>
bool listaD<T>::obtener(duo<T> &estructura){
	puntero=puntero->sig;
	if(puntero != final){
		estructura= *puntero;
		return true;
	} else {
		puntero=inicio;
		return false;
	}
	
}

template<class T>
bool listaD<T>::isIN(int clave){
		duo<T> *aux= inicio->sig;
	while(clave>aux->clave){
		aux=aux->sig;
	}
	if( aux->clave==clave){
		return true;
	} else {
		return false;
	}
}
template <class T>
int listaD<T>::getTam(){
	return tam;
}
template <class T>
void listaD<T>:: reiniciarPuntero(){
	puntero=inicio;
}
#endif
