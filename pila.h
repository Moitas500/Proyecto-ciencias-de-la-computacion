#ifndef PILA_H     
#define PILA_H
#include "estructura.h"    
#include<iostream>

using namespace std;


template <class T>
class pila{nodo<T> *cab;
      public: pila(){cab= new nodo<T>;
                     //cab->dato=NULL;
                     cab->sig = NULL; }
             void Push(T v);
             void recorrer();
             T Pop();
             bool PilaVacia();
             ~pila();
      };
template <class T>   
void pila<T>::Push(T v){
     nodo<T> *t = new nodo<T>;
     t->dato=v; 
     t->sig=cab->sig;
     cab->sig= t;
     }
template <class T>
T pila<T>::Pop(){
     T x;
     nodo<T> *t= cab->sig;
     cab->sig= t->sig; 
     x=t->dato;
     delete t;
     return x;
     }

template <class T>   
void pila<T>::recorrer(){
	nodo<T> *t=cab->sig;
	if(t!= NULL)
		cout<<"Dato "<<t->dato<<endl;
	while(t!=NULL){
		//cab=t;
		cout<<"Dato :"<<t->dato << endl;
		t=t->sig;
	}
}
 
template <class T>    
bool pila<T>::PilaVacia(){
      return cab->sig== NULL;
      }
template <class T>
 pila<T>::~pila(){
      nodo<T> *t=cab;
     while (t!=NULL){
           cab=t;
           t=t->sig;
           delete cab;
           }
     }
     
#endif

