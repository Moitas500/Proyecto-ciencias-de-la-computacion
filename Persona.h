#include <iostream>

#ifndef AUTO
#define AUTO

using namespace std;

class Persona{
	//Atributos
	private:
		string nombre;
		string contrasena;
		string usuario;
	//Metodos
	public:
		Persona(string _nombre,string _contrasena,string _usuario);
		Persona();
		void setNombre(string _nombre);
		void setContrasena(string _contrasena);
		void setUsuario(string _usuario);
		string getNombre();
		string getContrasena();
		string getUsuario();
};
Persona::Persona(){
}
//Contructor
Persona::Persona(string _nombre, string _contrasena, string _usuario){
	this->nombre = _nombre;
	this->contrasena = _contrasena;
	this->usuario = _usuario;
}
//setear la contraseña de la persona
void Persona::setContrasena(string _contrasena){
	this->contrasena = _contrasena;
}
//setear el nombre de la persona
void Persona::setNombre(string _nombre){
	this->nombre = _nombre;
}
//setear el usuario de la persona
void Persona::setUsuario(string _usuario){
	this->usuario = _usuario;
}
//obtener la contraseña de la persona
string Persona::getContrasena(){
	return this->contrasena;
}
//obtener el nombre de la persona
string Persona::getNombre(){
	return this->nombre;
}
//obtener el usuario de la persona
string Persona::getUsuario(){
	return this->usuario;
}

#endif
