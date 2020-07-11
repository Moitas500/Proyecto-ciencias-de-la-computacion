#include <iostream>

#include "Persona.h"

#ifndef ASD
#define ASD

using namespace std;

class Director : public Persona{
	//Atributos
	private:
		string cargo;
	//Metodos
	public:
		Director(string _nombre, string _contrasena, string _usuario, string _cargo);
		string getCargo();
		void setCargo(string _cargo);
};
//Constructor
Director::Director(string _nombre, string _contrasena, string _usuario, string _cargo) : Persona(_nombre, _contrasena, _usuario){
	this->cargo = _cargo;
}
//Setear el cargo del director
void Director::setCargo(string _cargo){
	this->cargo = _cargo;
}
//Devolver el cargo del director
string Director::getCargo(){
	return this->cargo;
}

#endif
