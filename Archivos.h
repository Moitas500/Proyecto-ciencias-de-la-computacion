//Lectura de archivos 
#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<string>
#include<fstream>
#include "listaD.h"
#include "Director.h"
#include "Profesor.h"
#include "estructura.h"
#include "Trio.h"
#include <sstream>
using namespace std;

class Archivo{
		ifstream archivo;
		ofstream archivoS;
		string linea;
		public:Archivo(){
				}	
		listaD<string> leerTemas();
		void escribirTemas(listaD<string> lista);
		listaD<cortesN> leerNotasCorte(int cedula);
		void escribirNotasCortes(listaD<cortesN> cortesNotas, string ruta, int cedula);
		listaD<maestro>  leerArchivoProfesor(string ruta);
		Director leerArchivoDirector(string ruta);
		bool crearArchivo(string ruta);
		bool eliminarArchivo(string ruta);
		void escribirArchivo(string ruta, string texto);
		void modificarCortes(Profesor profe,int cortes);
		void saltoDeLinea(string ruta);
};

void Archivo::modificarCortes(Profesor profe,int cortes){
	listaD<maestro> maest = Archivo::leerArchivoProfesor("Profesores/listaProfesores.txt");
	
	maestro mast;
	mast.apellidos = profe.getApellidos();
	mast.cedula = profe.getCedula();
	mast.contrasena = profe.getContrasena();
	mast.cortes = cortes;
	mast.nombre = profe.getNombre();
	mast.numClases = profe.getNumClases();
	mast.usuario = profe.getUsuario();
	
	maest.cambiar(profe.getCedula(), mast);
	
	Archivo::eliminarArchivo("Profesores/listaProfesores.txt");
	Archivo::crearArchivo("Profesores/listaProfesores.txt");
	
	duo<maestro> m;
	
	for(int i=1; i<maest.getTam(); i++){
		maest.obtener(m);
		mast = m.dato;
		
		stringstream ss;
		stringstream sa;
		stringstream sd;
		
		ss << mast.cedula;		
		string cedula = ss.str();
		sa << mast.numClases;
		string numClases = sa.str();
		sd << mast.cortes << endl;
		string cortes = sd.str();
		
		ofstream archivo;
		archivo.open("Profesores/listaProfesores.txt",ios::app);
		
		archivo << mast.nombre << " " << mast.apellidos << " " << mast.contrasena << " " << cedula << " " << numClases << " " << mast.usuario << " " << cortes << endl;
	}
	
	maest.reiniciarPuntero();
}

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

listaD<cortesN> Archivo::leerNotasCorte(int cedula){
	string cadena;
	stringstream ss;
	ss<<cedula;
	cadena="Profesores/Cortes-"+ss.str()+".txt";
	archivo.open(cadena.c_str(),ios::in);	//Se abre el archivo en modo lectura
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo"<<endl;
		//Falta crearlo en caso de que no lo encuentre
		exit(1);
	}
	int numCortes,numActividadesCorte,porcentajeActividad,numAct,numPuntosActividad,tema,valor;
	string nombre;
	string linea;
	listaD<cortesN> lista;
	getline(archivo,linea);	//Lee cedula
	getline(archivo,linea);	//lee el numero de cortes del profesor
	numCortes=atoi(linea.c_str());
	for(int i=0;i<numCortes;i++){
		getline(archivo,linea);	//lee el numero de actividades del corte
		numActividadesCorte=atoi(linea.c_str());
		cortesN corte(numActividadesCorte);
		for(int x=0;x<numActividadesCorte;x++){
			getline(archivo,nombre);	//Lee el nombre de la actividad
			getline(archivo,linea);		//Lee el porcentaje de la actividad
			porcentajeActividad=atoi(linea.c_str());
			getline(archivo,linea);		//Lee el numero de esas actividades que se realizaron en el corte
			numAct=atoi(linea.c_str());
			listaD<listaD<int> > notas;//La lista de listas de parejas de la primera actividad
			for(int z=0; z<numAct;z++){
				getline(archivo,linea);		//Lee el numero de puntos que tiene esa activida
				numPuntosActividad=atoi(linea.c_str());
				listaD<int> parejas;
				for(int w=0;w<numPuntosActividad;w++){
					getline(archivo,linea);		//Lee el codigo del tema de ese punto
					tema=atoi(linea.c_str());
					getline(archivo,linea);		//Lee el porcentaje de ese punto
					valor=atoi(linea.c_str());
					parejas.insertar(tema,valor); 
				}
				notas.insertar(z,parejas);
			}
			corte.insertarActividad(nombre,porcentajeActividad,notas);
		}
		lista.insertar(i,corte);
	}
	archivo.close();		
	return lista;	
	
}

void Archivo::escribirNotasCortes(listaD<cortesN> cortesNotas, string ruta, int cedula){

	archivoS.open(ruta.c_str(),ios::out);
	if(archivoS.fail()){
		cout<<"No se pudo abrir el archivo"<<endl;
		//Falta crearlo en caso de que no lo encuentre
		exit(1);
	}
	trio elemento;	//Objeto de tipo trio que resivira las actividades en el arreglo cortesNotas
	duo<cortesN> corte;
	duo<int> pr;	//Elemento de tipo duo que obtendra cada una de las parejas
	duo<listaD<int> > lista;//Elemento de tipo duo que obtendra la lista de parejas (de la lista de listas de parejas);
	archivoS<<cedula<<endl;	
	archivoS<<cortesNotas.getTam()<<endl;
	for(int i=0;i<cortesNotas.getTam();i++){	//El for recorre la lista cortesNotas
		corte=cortesNotas.obtener(i);
		archivoS<<corte.dato.getTam()<<endl;
			for(int i=0;i<(corte.dato.getTam());i++){	//For que recorre el arreglo obteniendo las actividades
				elemento=corte.dato.getElemento(i);	//Se obtiene la actividad de la posición i
				if(elemento.tipo!="NN"){		//Se hace la verificación que le comente
					archivoS<<elemento.tipo<<endl;
					archivoS<<elemento.porcentaje<<endl;
					archivoS<<elemento.puntos.getTam()<<endl;		 
					while(elemento.puntos.obtener(lista)){	//While que recorera la lista de listas de parejas para obtener cada lista de parejas
						archivoS<<lista.dato.getTam()<<endl;
						while(lista.dato.obtener(pr)){		//While que recorre la lista de parejas para obtener cada parejas
							archivoS<<pr.clave<<endl;
							archivoS<<pr.dato<<endl;
						}
					}
				}					
			}
		}
}

listaD<maestro> Archivo::leerArchivoProfesor(string ruta){
	string nombre, usuario, contrasena, apellidos, cedula, numClases, cortes;
	ifstream archivo(ruta.c_str());
	listaD<maestro> profes;
	
	while(!archivo.eof()){
		archivo >> nombre;
		archivo >> apellidos;
		archivo >> contrasena;
		archivo >> cedula;
		archivo >> numClases;
		archivo >> usuario;
		archivo >> cortes;
		
		maestro maest;
		maest.nombre = nombre;
		maest.apellidos = apellidos;
		maest.contrasena = contrasena;
		maest.cedula = atoi(cedula.c_str());
		maest.numClases = atoi(numClases.c_str());
		maest.usuario = usuario;
		maest.cortes = atoi(cortes.c_str());
		
		int clases = atoi(numClases.c_str());
		
		for(int i=0; i < clases;i++){
			string nombreClase;
			archivo >> nombreClase;
		
			maest.nombresClases.insertar(i,nombreClase);
		}
		
		maest.nombresClases.obtenerTodos();
		system("pause");
		profes.insertar(maest.cedula,maest);
		
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
void Archivo::saltoDeLinea(string ruta){
	ofstream archivo;
	archivo.open(ruta.c_str(), ios::app);
	
	if(archivo.fail()){
		system("cls");
		cout << "No se pudo abrir el archivo" << endl;
		system("pause");
	}else{
		archivo << " " << endl;
		archivo.close();
	}
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
