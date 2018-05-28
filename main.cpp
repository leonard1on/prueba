#include "Persona.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
int menu();
Persona* agregar();
void list(string);
void check(string);
void modifyavail(string, int);
void escribirArchivo(string, int);



int main() {
  vector<Persona*> buffer;
  int opcion=0;
  int lastDeleted=-1;
  string archivo = "./Registro.sota";
  vector<string> availList;
  check(archivo);

  while (opcion!=4) {
    opcion=menu();

    if (opcion==1) {
      //Autofill
      for (int i = 0; i < 10; i++) {
        Persona* temp = new Persona("Leonardo"+to_string(i),"Borjas","0801199804812","Colonia America","50495105400",'M','B');
        temp->fill();
        buffer.push_back(temp);
      }

      //Agregar Persona
      //buffer.push_back(agregar());


      if (buffer.size()==10) {

        //Escribir a Espacio eliminado
        fstream output(archivo, ios::in | ios::out);
        vector<int> availlist;
        // MODIFICAR LA CREACION DEL AVAILLIST
        if (output) {
          string line;
          int cont=0;
          int inicio=0;

          sort(availlist.begin(), availlist.end());

          //Overwrite
          while (availlist.size()!=0 && buffer.size()!=0) {
            int position = availlist.at(0);
            output.seekp(0,ios::beg);
            output.seekp(position,ios::cur);
            output.write(buffer.at(0)->toString().c_str(),113);
            buffer.erase(buffer.begin());
            availlist.erase(availlist.begin());
          }
          output.close();
        }

        //Modificar meta
        string temp = "";
        ofstream rewrite("Meta.data", ios::out | ios::trunc);
        if (rewrite.is_open()) {
          for (size_t i = 0; i < availlist.size(); i++) {
            temp += to_string(availlist.at(i))+"\n";
          }
          rewrite<<temp;
          rewrite.close();
        }


        //Append al archivo
        ofstream file(archivo, ios::out | ios::app);
        if (file.is_open()) {
          for (size_t i = 0; i < buffer.size(); i++) {
            file<<buffer.at(i)->toString();
          }
          file.close();
        }
        buffer.clear();
      }
    }

    if (opcion==2) {
      int index;
      if (lastDeleted != -1){
        // Se inserta el índice del registro eliminado al principio de la lista
        availList.push_back(to_string(index));
      }
      cout <<"Cual registro desea eliminar: ";
      cin >> index;
      string temp = "*" + to_string(lastDeleted) + "*";
      lastDeleted = index;

      index*=113;
      fstream file;
      char c;
      file.open(archivo, ios::out | ios::in);
      if (file) {
        file.seekp(0, ios::beg);
        file.seekp(index+5, ios::cur);
        file.write(temp.c_str(), temp.length());
        escribirArchivo(archivo, lastDeleted); //escribe los cambios y actualiza el meta
      }
      file.close();
      /*if (file) {
        file.seekp(0,ios::beg);
        file.seekp(position,ios::cur);
        file.get(c);
        while (c=='*') {
          position+=113;
          file.seekp(0,ios::beg);
          file.seekp(position,ios::cur);
          file.get(c);

        }
        file.seekp(0,ios::beg);
        file.seekp(position,ios::cur);
        file.write("*",1);
        file.close();
      }*/

    }

    if (opcion==3) {
      list(archivo);
    }

    if (opcion==4) {

      //Escribir a Espacio eliminado
      fstream input("Meta.data", ios::in | ios::out);
      fstream output(archivo, ios::in | ios::out);
      vector<int> availlist;
      if (input && output) {
        string line;
        int cont=0;
        int inicio=0;
        //Avail list a RAM
        while (getline(input,line)) {
          availlist.push_back(atoi(line.c_str()));
        }
        sort(availlist.begin(), availlist.end());

        //Overwrite
        while (availlist.size()!=0 && buffer.size()!=0) {
          int position = availlist.at(0);
          output.seekp(0,ios::beg);
          output.seekp(position,ios::cur);
          output.write(buffer.at(0)->toString().c_str(),113);
          buffer.erase(buffer.begin());
          availlist.erase(availlist.begin());
        }
        input.close();
        output.close();
      }

      //Modificar meta
      string temp = "";
      ofstream rewrite("Meta.data", ios::out | ios::trunc);
      if (rewrite.is_open()) {
        for (size_t i = 0; i < availlist.size(); i++) {
          temp += to_string(availlist.at(i))+"\n";
        }
        rewrite<<temp;
        rewrite.close();
      }
      //Guarda lo que esta en el buffer y sale del programa
      if (buffer.size()>0) {
        ofstream file(archivo, ios::out | ios::app);
        if (file.is_open()) {
          for (size_t i = 0; i < buffer.size(); i++) {
            file<<buffer.at(i)->toString();
          }
          file.close();
        }
        buffer.clear();
      }
    }

    if (opcion==5) {
      int position;
      list(archivo);
      cout<<"Cual registro desea Modificar: ";
      cin>>position;
      position*=113;

      //Marca el archivo eliminado
      string line;
      char c;
      fstream file;
      file.open(archivo, ios::in | ios::out);
      if (file) {
        file.seekp(0,ios::beg);
        file.seekp(position,ios::cur);
        file.get(c);
        while (c=='*') {
          position+=113;
          file.seekp(0,ios::beg);
          file.seekp(position,ios::cur);
          file.get(c);
        }
        file.seekp(0,ios::beg);
        file.seekp(position,ios::cur);
        Persona* temp = agregar();
        temp->fill();
        string s = temp->toString();
        file.write(s.c_str(),113);
        /*getline(file,line);
        while (line[0]=='*') {
          getline(file,line);
        }
        istringstream ss(line);
        string token;
        vector<string> partes;
        while (getline(ss,token,'|')) {
          partes.push_back(token);
        }*/


        file.close();
      }
    }

    if (opcion==6) {
      fstream input("Meta.data", ios::in | ios::out);
      string line;
      vector<int> availlist;
      if (input) {
        while (getline(input,line)) {
          availlist.push_back(atoi(line.c_str()));
        }
        sort(availlist.begin(), availlist.end());
      }
      cout<<"----Available Positions----" <<endl;
      for (size_t i = 0; i < availlist.size(); i++) {
        cout<< to_string(i)+") "+to_string(availlist.at(i)) <<endl;
      }

    }

  }
  return 0;
}

int menu(){
  cout<<"\n1)Agregar \n2)Eliminar \n3)Listar\n4)Guardar y Salir\n5)Modificar\n6)Available Positions\n";
  int opcion;
  cin>>opcion;
  return opcion;
}

Persona* agregar(){
  string nombre, apellido, identidad, direccion, telefono;
  char sexo, raza;
  cout<<"Nombre: ";
  cin.get();
  getline(cin,nombre);
  cout<<"\nApellido: ";
  getline(cin,apellido);
  cout<<"\nIdentidad: ";
  getline(cin,identidad);
  cout<<"\nDireccion: ";
  getline(cin,direccion);
  cout<<"\nTelefono: ";
  getline(cin,telefono);
  cout<<"\nSexo (M/F): ";
  cin>>sexo;
  cout<<"\nRaza: ";
  cin>>raza;
  Persona* temp = new Persona(nombre,apellido,identidad,direccion,telefono,sexo,raza);
  temp->fill();
  return temp;
}

void list(string archivo){
  ifstream file(archivo, ios::in);
  if (file.is_open()) {
    string line;
    int cont=0;
    while (getline(file, line)) {
      if (line[0]!='*') {
        cout << to_string(cont)+")" + line +"\n";
        cont++;
      }
    }
    cout<<endl;
  }
  file.close();
}

void check(string archivo){
  ifstream ifile(archivo);
  if (!ifile) {
    ofstream file(archivo, ios::out);
    if (file.is_open()) {
      file << to_string(0)+"***\n";
      file.close();
    }
  }

}

void escribirArchivo(string ruta, int lastDeleted){
  fstream file;
  file.open(ruta, ios::out | ios::in );
  if (file.is_open()) {
    file.seekp(0, ios::beg);
    string temp = to_string(lastDeleted);

    for (int i = temp.length(); i < 4; i++){
      temp += "*";
    }
    file.write(temp.c_str(), temp.length());
    file.close();
  }
  file.close();
}

vector<int> construirAvailList(int posicion, string ruta){
  if (posicion != -1)​ {
    availList.push_back(posicion) //Añadir la posición actual al availList
    string buffer = "";
    string nextPos = "";
    //Toma el registro en índice “posición”
    fstream archivo;
    archivo.open(ruta, ios::in | ios::out);
    archivo.seekp(0, ios::beg);
    getline(archivo, buffer);
    for (int i = 1; i < buffer.size() ; i++){
      if(buffer[i] != '*'){
            nextPos += buffer[i];
      }
    }
  }
}

void metodo(string ruta){
  fstream archivo;
  buffer="";
  archivo.open(ruta, ios::in | ios::out);
  archivo.seekp(0, ios::beg);
  getline(archivo, buffer);
  if ( buffer != "-1**" )​ {
    string firstPos = "";
    //Quitar los espacios del Meta
    for (int i = 1; i < buffer.size() ; i++){
      if(buffer[i] != '*'){
        firstPos += buffer[i];
      }
    }
    vector<int> temp = construirAvailList(firstPos.toInteger());
  }
}
