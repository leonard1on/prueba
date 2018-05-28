#include "Persona.h"

Persona::Persona(string pnombre, string papellido, string pidentidad, string pdireccion, string ptelefono, char psexo, char praza){
  nombre = pnombre;
  apellido = papellido;
  identidad = pidentidad;
  direccion = pdireccion;
  telefono = ptelefono;
  sexo = psexo;
  raza = praza;
}

void Persona::fill(){
  while (nombre.size() != 20) {
    nombre+=" ";
  }
  while (apellido.size() != 25) {
    apellido+=" ";
  }
  while (direccion.size() != 35) {
    direccion+=" ";
  }
  while (telefono.size() != 11) {
    telefono+=" ";
  }
  while (identidad.size() != 13) {
    identidad+=" ";
  }
}

string Persona::toString(){
  return this->nombre+"|"+this->apellido+"|"+this->identidad+"|"+this->direccion+"|"+this->telefono+"|"+this->sexo+"|"+this->raza+"\n";
}

string Persona::getNombre(){
  return nombre;
}

string Persona::getApellido(){
  return apellido;
}

string Persona::getIdentidad(){
  return identidad;
}

string Persona::getDireccion(){
  return direccion;
}

string Persona::getTelefono(){
  return telefono;
}

char Persona::getSexo(){
  return sexo;
}

char Persona::getRaza(){
  return raza;
}

void Persona::setNombre(string pnombre){
  nombre = pnombre;
}

void Persona::setApellido(string papellido){
  apellido = papellido;
}

void Persona::setIdentidad(string pidentidad){
  identidad = pidentidad;
}

void Persona::setDireccion(string pdireccion){
  direccion = pdireccion;
}

void Persona::setTelefono(string ptelefono){
  telefono = ptelefono;
}

void Persona::setSexo(char psexo){
  sexo = psexo;
}

void Persona::setRaza(char praza){
  raza = praza;
}

Persona::~Persona(){
}
