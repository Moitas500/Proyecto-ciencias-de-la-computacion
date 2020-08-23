#include "pila.h"
#include <iostream>
#ifndef ARBOLB_H     
#define AEBOLB_H 
using namespace std;
template <class T>
struct Nodo{int info, T dato;
           Nodo *izq, *der;};
template<class T>
class arbolB{Nodo *raiz;
    pila<int> *listInorden;
    pila<int> *listPreorden;
	pila<int> *listPosorden;
	Nodo<T>* buscarNodo(int clave);
    public: arbolB(){raiz = NULL;
    					listInorden = new pila<int>; 
                        listPreorden = new pila<int>;
                        listPosorden = new pila<int>;}

        void insertar(int clave, T dato);
        Nodo<T> *buscarpadre(int clave);
        void eliminar(int clave);
        Nodo<T> *buscar_nodo(int clave);
        void inorden();
        void preorden();
        void posorden();
        void imprimir();
       	~arbolB();
};

template<class T>
void arbolB::insertar(int clave,T dato){
	Nodo<T> *arb,*pre, *aux = new Nodo<T>;
	aux->info=clave;
	aux->dato=dato;
	aux->izq=NULL;
	aux->der=NULL;
	if (raiz==NULL){
		raiz=aux;
	}else {
		arb=raiz;
		while(arb != NULL){
			pre=arb;
			if(dato>arb->info){
				arb=arb->der;
			}else{
				arb=arb->izq;
			}
		}
		arb=aux;
		if(dato>pre->info){
			pre->der=arb;
		}else {
			pre->izq=arb;
		}
	}
}
template<class T>
Nodo<T> * arbolB::buscarpadre(int clave){
	Nodo<T> *aux= raiz;
	pila<Nodo<T> *> p;
	while(aux != NULL && aux->info != dato){
		p.Push(aux);
		if (dato>aux->info){
			aux=aux->der;
		} else {
			aux=aux->izq;
		}
	}
	if(aux == NULL || aux->info != dato){
		cout<<"No se encontro un nodo con ese dato"<<endl;
		aux=NULL;
		return aux;
	} else {
		return p.Pop();
	}
}
template<class T>
void arbolB::imprimir(){
	Nodo<T> *centro,*izquierda= NULL,*derecha=NULL;
	centro=raiz;
	if(centro != NULL){
	izquierda=raiz->izq;
	derecha=raiz->der;
	}
	if (centro != NULL)
	{
		cout<<"Centro "<<centro->info<<endl;
	}
	else {
		cout<<"Centro "<<"Vacio"<<endl;	
	}
	if (izquierda != NULL)
	{
		cout<<"izquierda "<<izquierda->info<<endl;
	}
	else {
		cout<<"izquierda "<<"Vacio"<<endl;	
	}
	if (derecha != NULL)
	{
		cout<<"derecha "<<derecha->info<<endl;
	}
	else {
		cout<<"derecha "<<"Vacio"<<endl;
	}
}
template<class T>
void arbolB::preorden(){
	Nodo<T> *nodo= raiz;
	cout<<"El recorrido en preorden es: "<<endl;
	if(raiz == NULL){
		cout << "El arbol esta vacio";
	}else{
		listPreorden.Push(nodo->info);
		
		while(!listPreorden.PilaVacia()){
			nodo=buscar_nodo(listPreorden.Pop());
			cout<<nodo->info; //imprime el resultado en preorden
			if(nodo->der != NULL){
				listPreorden.Push(nodo->der->info);
			}
			if(nodo->izq != NULL){
				listPreorden.Push(nodo->izq->info);
			}
		}
	}

	cout<<endl;

}
template<class T>
void arbolB::inorden(){
	Nodo<T> *aux;
	aux = raiz;
	cout<<"El recorrido en inorden es:"<<endl;
	while(!listInorden->PilaVacia() || aux != NULL){
		if(aux != NULL){
			listInorden->Push(aux->info);
			aux = aux->izq;
		}else{
			aux= buscar_nodo(listInorden->Pop());
			cout<<aux->info; //imprime el resultado en inorden
			aux = aux->der;
		}
		
	}
	cout<<endl;
}
template<class T>
void arbolB::posorden(){
	cout<<"El recorrido en postorden es:"<<endl;
	Nodo<T> *aux=raiz;
	Nodo<T> *aux2=NULL;
	while(!listPosorden->PilaVacia() || aux != NULL){
		if(aux != NULL){
			listPosorden->Push(aux->info);
			aux = aux->izq;
		}else{
			Nodo *aux3 = buscar_nodo(listPosorden->Pop());
			listPosorden->Push(aux3->info);
			if(aux3->der != NULL && aux2 != aux3->der){
				aux = aux3->der;
			}else{
				cout<<aux3->info;
				aux2= buscar_nodo(listPosorden->Pop());
			}
		}     
	}
	cout<<endl;
}
template<class T>
Nodo<T> *arbolB::buscar_nodo(int clave){
	Nodo<T>  *buscado=NULL;
	if(raiz->info == dato){
		return raiz;
	}else{
		buscado=raiz;
		while(buscado != NULL && buscado->info != dato){
			if(dato>buscado->info){
				buscado=buscado->der;
			}else{
				if(dato<buscado->info){
					buscado=buscado->izq;
				}
			}
		}
	}
	return buscado;
	
}
template<class T>
void arbolB::eliminar(int clave){
	Nodo<T> *eliminado= buscar_nodo(dato);
	Nodo<T> *padre, *padreR, *hijoR =NULL;
	//cout<<eliminado->info<<endl;
	if(eliminado->der == NULL && eliminado->izq == NULL){
		//padre= buscar padre(dato o eliminado);
		if(eliminado->info > padre->info){
			padre->der = NULL;
		}else{
			padre->izq = NULL;
		}
	}else if(eliminado->der != NULL && eliminado->izq == NULL){
		padre->der = eliminado->der;
		delete eliminado;
	} else if(eliminado->der == NULL && eliminado->izq != NULL){
		padre->izq = eliminado->izq;
		delete eliminado;
	}else  if(eliminado->der != NULL && eliminado->izq != NULL){
		
	}
}

#endif
