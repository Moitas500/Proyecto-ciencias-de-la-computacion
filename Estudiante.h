#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

using namespace std;

class Estudiante : public Persona{
	//Atributos
	private:
		string apellido;
		listaD<int> notas;
	//Metodos
	public:
		Estudiante(string _apellido, listaD<int> _notas) : Persona(_nombre,_contrasena,_usuario);
		string getApellidos();
		listaD<int> getNotas();
		void setApeliidos(string _apellido);
		void setNotas(listaD<int> _notas);
};

Estudiante::Estudiante(string _apellido, listaD<int> _notas) : Persona(_nombres,_contrasena,_usuario){
	this->apellido = _apellido;
	this->notas = _notas;
}
//Metodo para obtener el apellido del estudiante
string Estudiante::getApellidos(){
	return this->apellido;
}
//Metodo para obtener las notas del estudiante
listaD<int> Estudiante::getNotas(){
	return this->notas;
}
//Metodo para setear el apellido del estudiante
void Estudiante::setApeliidos(string _apellido){
	this->apellido = _apellido;
}
//Metodo para setear las notas del estudiante
void Estudiante::setNotas(listaD<int> _notas){
	this->notas = _notas;
}
#endif
