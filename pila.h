#ifndef PILA_H     
#define PILA_H    
#include "estructura.h"

using namespace std;

template <class T>
class pila{ 
		duo<T> *cab;
      public: pila(T info){cab= new duo<T>;
                     cab->dato=info;
                     cab->sig=NULL;}
             void Push(T v);
             T Pop();
             bool PilaVacia();
             
             ~pila();
      };
template <class T>
void pila<T>::Push(T v){
     duo<T> *t = new duo<T>;
     t->dato=v; 
     t->sig=cab->sig;
     cab->sig= t;
     
     }
template <class T>
T pila<T>::Pop(){
     T x;
     duo<T> *t= cab->sig;
     cab->sig= t->sig; 
     x=t->dato;
     delete t;
     return x;
     }
template <class T>    
bool pila<T>::PilaVacia(){
      return cab->sig== NULL;
      }
template <class T>
pila<T>::~pila(){
      duo<T> *t=cab;
     while (t!=NULL){
           cab=t;
           t=t->sig;
           delete cab;
           }
     }
     
#endif

