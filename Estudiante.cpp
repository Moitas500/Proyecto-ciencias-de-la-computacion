#include "Persona.h"

#ifndef AUTO
#define AUTO

using namespace std;

class Estudiante : public Persona{
	//Atributos
	private:
		string apellidos;
		int notas[];
		int promedio;
	//Metodos
	public:
		Estudiante(string _apellidos, int _notas[]);
		void setApellidos(string _apellidos);
		string getApellidos();
		void setNotas(int notas[]);
		int* getNotas();
		int getPromedio();
};
//Contructor
Estudiante::Estudiante(string _apellidos, int_notas[]) : Persona(_nombre, _contrasena, _usuario){
	this->apellidos = _apellidos;
	this->notas = _notas;
}

//Setear el apellido del estudiante
void Estudiante::setApellidos(string _apellidos){
	this->apellidos = _apellidos;
}

//Setear las notas del estudiante
void Estudiante::setNotas(int notas[]){
	this->notas = _notas;
}

//Obtener el apellido del estudante
string Estudiante::getApellidos(){
	return this->apellidos;
}

//Obtener las notas del estudiante
int* Estudiante::getNotas(){
	return this->notas;
}

//Obtener el promedio del estudiante
int Estudiante::getPromedio(){
	int prom = 0;
	int longitud = sizeof(this->notas)/sizeof(*this->notas);
	
	for(int i=0; i<longitud; i++){
		prom += this->notas[i];
	}
	
	prom = prom/longitud;
	
	this->promedio = prom;
	
	return this->promedio;
}

#endif
