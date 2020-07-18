//Lectura de archivos 
#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include "listaD.h"

using namespace std;

class Archivo{
		ifstream archivo;
		ofstream archivoS;
		string linea;
		public:Archivo(){
				}	
		void leerTemas(listaD<string> &lista);
		void escribirTemas(listaD<string> lista);

};

void Archivo::leerTemas(listaD<string> &lista){
	archivo.open("Topics.txt",ios::in);	//Se abre el archivo en modo lectura
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo"<<endl;
		//Falta crearlo en caso de que no lo encuentre
		exit(1);
	}
	string clave="";
	linea="";
	while(!archivo.eof()){
			getline(archivo,clave);
			getline(archivo,linea);
			lista.insertar(atoi(clave.c_str()),linea);	
	}
	archivo.close();	
}
void Archivo::escribirTemas(listaD<string> lista){
	archivoS.open("Topics.txt",ios::out);
	duo<string> aux;
	if(archivoS.fail()){
		cout<<"No se pudo abrir el archivo"<<endl;
		//Falta crearlo en caso de que no lo encuentre
		exit(1);
	}
	while(lista.obtener(aux)){
		archivoS<<aux.clave<<endl;;
		archivoS<<aux.dato<<endl;;
	}
	archivoS.close();
}
#endif
