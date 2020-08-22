#include "Persona.h"

#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

using namespace std;

class Estudiante : public Persona{
	//Atributos
	private:
		string apellido;
		listaD<float> notas;
	//Metodos
	public:
		Estudiante();
		Estudiante(string _nombre, string _contrasena, string _usuario, string _apellido, listaD<float> _notas);
		string getApellidos();
		listaD<float> getNotas();
		void setApeliidos(string _apellido);
		void setNotas(listaD<float> _notas);
};
Estudiante::Estudiante() : Persona(){
}
Estudiante::Estudiante(string _nombre, string _contrasena, string _usuario, string _apellido, listaD<float> _notas) : Persona(_nombre,_contrasena,_usuario){
	this->apellido = _apellido;
	this->notas = _notas;
}
//Metodo para obtener el apellido del estudiante
string Estudiante::getApellidos(){
	return this->apellido;
}
//Metodo para obtener las notas del estudiante
listaD<float> Estudiante::getNotas(){
	return this->notas;
}
//Metodo para setear el apellido del estudiante
void Estudiante::setApeliidos(string _apellido){
	this->apellido = _apellido;
}
//Metodo para setear las notas del estudiante
void Estudiante::setNotas(listaD<float> _notas){
	this->notas = _notas;
}
#endif
