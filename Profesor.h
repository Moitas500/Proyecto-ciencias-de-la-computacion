#include <iostream>
#include "Persona.h"
#include "CortesNotas.h"

#ifndef AS
#define AS

using namespace std;

struct maestro{
	string nombre;
	string contrasena;
	string usuario;
	string apellidos;
	int cedula;
	int numClases;
	int cortes;
	listaD<string> nombresClases;
};

class Profesor : public Persona{
	//Atributos
	private:
		int cedula;
		string apellidos;
		int numClases;
		int cortes;
		listaD<string> nombresClases;
		listaD<cortesN> cortesNotas;
	//Metodos:
	public:
		Profesor(string _nombre, string _contrasena, string _usuario, int _cedula, string _apellidos, int _numClases, int _cortes);
		listaD<string> getNombresClases();
		listaD<cortesN> getCortesNotas();
		int getCortes();
		int getCedula();
		string getApellidos();
		int getNumClases();
		void setCedula(int _cedula);
		void setApellido(string _apellido);
		void setNumClases(int _numClases);
		void setCortes(int _cortes);
		void setCortesNotas(listaD<cortesN> _cort);
		void setNombresClases(listaD<string> _nombres);
};

//Contructor
Profesor::Profesor(string _nombre, string _contrasena, string _usuario, int _cedula, string _apellidos, int _numClases, int _cortes) : Persona(_nombre, _contrasena, _usuario){
	this->apellidos = _apellidos;
	this->cedula = _cedula;
	this->numClases = _numClases;
	this->cortes = _cortes;
}
//Set de la lista de los nombres de clases
void Profesor::setNombresClases(listaD<string> _nombres){
	this->nombresClases = _nombres;
}
//Get de la lista de los nombres de clases
listaD<string> Profesor::getNombresClases(){
	return this->nombresClases;
}
//Get de la lista de los cortes de notas
listaD<cortesN> Profesor::getCortesNotas(){
	return this->cortesNotas;
}
//Set de la lista de los cortes de notas
void Profesor::setCortesNotas(listaD<cortesN>_cort){
	this->cortesNotas = _cort;
}
//Get los cortes del profesor
int Profesor::getCortes(){
	return this->cortes;
}
//Setear los cortes del profesor
void Profesor::setCortes(int _cortes){
	this->cortes = _cortes;
}
//Setear los apellidos del profesor
void Profesor::setApellido(string _apellido){
	this->apellidos = _apellido;
}
//Setear el numero de clases del profesor
void Profesor::setNumClases(int _numClases){
	this->numClases = _numClases;
}
//Setear la cedula de el profesor
void Profesor::setCedula(int _cedula){
	this->cedula = _cedula;
}
//Obtener la cedula de el profesor
int Profesor::getCedula(){
	return this->cedula;	
}
//Obtener el apellido de el profesor
string Profesor::getApellidos(){
	return this->apellidos;
}
//Obtener el numero de clases de el profesor
int Profesor::getNumClases(){
	return this->numClases;
}

#endif
