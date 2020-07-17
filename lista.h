#ifndef LISTA_H
#define LISTA_H
#include <iostream>

using namespace std;

template <class T>
struct nodo {T Dato;
             nodo<T> * sig;};


template <class T>
class lista{nodo <T> *cab;
			int tam;
			
	public: lista(){cab=NULL; tam=0;}
			bool lista_vacia();
			void insertar(T info, int pos);
			void insertar_final(T info);
			void insertar_inicio(T info);
			bool borrar(int pos);
			bool buscar (int pos, T *infoRet);
			bool cambiar(int pos, T infoNueva);	
			int get_tam(){
				return tam;
			}
			
			
			
};

template <class T>
bool lista<T>::lista_vacia()
{if(cab==NULL)
    return true;
 else
 	return false;
}

template <class T>
void lista <T>::insertar(T info, int pos)
{int p;
 if (pos>tam)
	insertar_final(info);
 else if (pos == 1)
 		insertar_inicio(info);
 	else{nodo <T> *nuevo, *Aux;
 	     nuevo = new nodo <T>;
 	     nuevo->Dato = info;
 	     Aux=cab;
 	     p=1;
 	     while(p<pos-1 && Aux!= NULL)
 	     {Aux=Aux->sig;
 	      p++;
		  }
		 nuevo->sig = Aux->sig;
		 Aux->sig= nuevo;
		 tam++; 
	 }	
}

template <class T>
void lista<T>::insertar_final(T infoNueva)
{ nodo <T> *nuevo;
  nuevo = new nodo <T>;
  nuevo->Dato = infoNueva;
  nuevo->sig = NULL;
  if(tam == 0)
    {cab = nuevo;}
  else
    {nodo <T> *aux;
     aux = cab;
     while(aux->sig != NULL)
        {aux = aux->sig;}
     aux->sig = nuevo;
    }
  tam++;
}

template <class T>
void lista<T>::insertar_inicio(T infoNueva)
{ nodo <T> *nuevo;
  nuevo = new nodo <T>;
  nuevo->Dato = infoNueva;
  nuevo->sig = cab;
  cab = nuevo;
  tam++;
}

template <class T>
bool lista<T>::borrar(int pos)
{ if(tam >= pos)
     { nodo <T> *temp;
       temp = cab;
       if(pos == 1)
         {cab = temp->sig;
          delete temp;
         }
       else
         {for(int i=1;i<pos-1;i++)
             {temp = temp->sig;}          
          nodo <T> *aux;
          aux = temp->sig;
          temp->sig = aux->sig;
          delete aux;
         }
        tam--;
        return true;          
     }
 else
     return false;
}

template <class T>
bool lista<T>::buscar(int pos, T *infoRet)
{   nodo <T> *aux=cab;
    int p = 1;
    if (pos<=tam)
	   { while(p<pos && aux != NULL)
    		{aux = aux->sig;
           	 p++;
    		}
    	*infoRet = aux->Dato;	
    	return true;
		}
	return false;
}

template <class T>
bool lista<T>::cambiar(int pos, T infoNueva)
{ nodo <T> *aux=cab;
  int p = 1;
  if (pos<=tam)
   { while(p<pos && aux != NULL)
   		{aux = aux->sig;
         p++;
    	}
     aux->Dato = infoNueva; 
     return true;
	}
  return false;	
}	

#endif
