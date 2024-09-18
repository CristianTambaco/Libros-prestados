#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Publicacion {
protected:
    string codigo;
    string titulo;
    int anioPublicacion;
    bool prestado;

public:
    Publicacion(string c, string t, int a) : codigo(c), titulo(t), anioPublicacion(a), prestado(false) {}

    virtual string obtenerInformacion() const {
        stringstream ss;
        ss << "Código: " << codigo << "\nTítulo: " << titulo << "\nAño de Publicación: " << anioPublicacion << "\nEstado: " << (prestado ? "Prestado" : "No Prestado") << "\n";
        return ss.str();
    }

    void prestar() {
        prestado = true;
    }

    void devolver() {
        prestado = false;
    }

    bool estaPrestado() const {
        return prestado;
    }
};

class Libro : public Publicacion {
public:
    Libro(string c, string t, int a) : Publicacion(c, t, a) {}
};

class Revista : public Publicacion {
public:
    Revista(string c, string t, int a) : Publicacion(c, t, a) {}
};

void guardarInformacion(const vector<Publicacion*>& publicaciones) {
    ofstream prestados("LibrosPrestados.txt");
    ofstream enStock("LibrosEnStock.txt");

    for (const auto& pub : publicaciones) {
        if (pub->estaPrestado()) {
            prestados << pub->obtenerInformacion() << endl;
        } else {
            enStock << pub->obtenerInformacion() << endl;
        }
    }

    prestados.close();
    enStock.close();
}

int main() {
    vector<Publicacion*> publicaciones;

    publicaciones.push_back(new Libro("001", "Cien Años de Soledad", 1967));
    publicaciones.push_back(new Revista("002", "Time", 2023));
    publicaciones.push_back(new Libro("003", "Matar a un ruiseñor", 1960));

    publicaciones[0]->prestar();
    publicaciones[2]->prestar();

    guardarInformacion(publicaciones);

    for (auto& pub : publicaciones) {
        delete pub;
    }
    
    cout<<"Archivo generado con exito"<<endl;

    return 0;
}

