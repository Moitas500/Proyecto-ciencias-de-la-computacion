//Lectura de archivos 
#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include "listaD.h"
#include "Director.h"
#include "Profesor.h"

using namespace std;

class Archivo{
		ifstream archivo;
		ofstream archivoS;
		string linea;
		public:Archivo(){
				}	
		listaD<string> leerTemas();
		void escribirTemas(listaD<string> lista);
		listaD<maestro>  leerArchivoProfesor(string ruta);
		Director leerArchivoDirector(string ruta);
		bool crearArchivo(string ruta);
		bool eliminarArchivo(string ruta);
		void escribirArchivo(string ruta, string texto);

};

listaD<string> Archivo::leerTemas(){
	listaD<string> temas;
	archivo.open("Temas/Topics.txt",ios::in);	//Se abre el archivo en modo lectura
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
			temas.insertar(atoi(clave.c_str()),linea);	
	}
	archivo.close();
	return temas;
	
}
void Archivo::escribirTemas(listaD<string> lista){
	int i=1;
	archivoS.open("Temas/Topics.txt",ios::out);
	duo<string> aux;
	if(archivoS.fail()){
		cout<<"No se pudo abrir el archivo"<<endl;
		//Falta crearlo en caso de que no lo encuentre
		exit(1);
	}
	while(lista.obtener(aux)){
		if(i!=1){
			archivoS<<endl;
		}
		archivoS<<aux.clave<<endl;
		archivoS<<aux.dato;
		i++;
	}	
	archivoS.close();
}
listaD<maestro> Archivo::leerArchivoProfesor(string ruta){
	string nombre, usuario, contrasena, apellidos, cedula, numClases;
	int i = 1;
	ifstream archivo(ruta.c_str());
	listaD<maestro> profes;
	
	while(!archivo.eof()){
		archivo >> nombre;
		archivo >> apellidos;
		archivo >> contrasena;
		archivo >> cedula;
		archivo >> numClases;
		archivo >> usuario;
		
		maestro maest;
		maest.apellidos = apellidos;
		maest.cedula = atoi(cedula.c_str());
		maest.contrasena = contrasena;
		maest.nombre = nombre;
		maest.numClases = atoi(numClases.c_str());
		maest.usuario = usuario;
		
		profes.insertar(maest.cedula,maest);
		
		i++;
	}
	
	archivo.close();
	
	return profes;
}
Director Archivo::leerArchivoDirector(string ruta){
	string nombre, usuario, contrasena, cargo;
	ifstream archivo(ruta.c_str());
	
	archivo >> nombre;
	archivo >> contrasena;
	archivo >> usuario;
	archivo >> cargo;
	
	Director dir(nombre, contrasena, usuario, cargo);
	
	archivo.close();
	
	return dir;
}
bool Archivo:: crearArchivo(string ruta){
	ifstream archivo;
	archivo.open(ruta.c_str());
	if(archivo.fail()){
		archivo.close();
		ofstream crear;
		crear.open(ruta.c_str());
		crear.close();
		return true;
	}else{
		return false;
	}
	return false;
}
bool  Archivo::eliminarArchivo(string ruta){
	if(remove(ruta.c_str())){
		return true;
	}
	return false;
}
void  Archivo::escribirArchivo(string ruta, string texto){
	ofstream archivo;
	archivo.open(ruta.c_str(),ios::app);	
	
	if(archivo.fail()){
		system("cls");
		cout << "No se pudo abrir el archivo" << endl;
		system("pause");
	}else{
		archivo << texto + " ";
		archivo.close();
	}
}
#endif
