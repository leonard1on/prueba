#pragma once
#include <string>
using namespace std;

class Persona {
private:
  string nombre;
  string apellido;
  string identidad;
  string direccion;
  string telefono;
  char sexo;
  char raza;

public:
  Persona (string, string, string, string, string, char, char);
  void fill();
  string toString();

  //Getters & Setters
  string getNombre();
  string getApellido();
  string getIdentidad();
  string getDireccion();
  string getTelefono();
  char getSexo();
  char getRaza();
  void setNombre(string);
  void setApellido(string);
  void setIdentidad(string);
  void setDireccion(string);
  void setTelefono(string);
  void setSexo(char);
  void setRaza(char);

  virtual ~Persona ();

};
