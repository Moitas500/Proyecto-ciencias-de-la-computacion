#ifndef ESTRUCTURA_H     
#define ESTRUCTURA_H 
#include<iostream>
#include<string>

template <class T>
struct duo{ T dato;
		int clave;
        duo *sig;
       };  
#endif

