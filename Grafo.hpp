//
//  Grafo.hpp
//  Carreteras
//
//  Created by Rodri on 02/06/23.
//


#ifndef Grafo_hpp
#define Grafo_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "Arbol.hpp"


using namespace::std;



struct tipo_enlace_de_grafo //Guarda toda la informacion de la conexion entre 2 nodos: info_nodo1 + info_nodo2 + todo_lo_de_su_conexion
{
    string nodo1 = "";
    float costo_nodo1 = 0.0f;
    float posicion_x_nodo1 = 0.0f;
    float posicion_y_nodo1 = 0.0f;
    string nodo2 = "";
    float costo_nodo2 = 0.0f;
    float posicion_x_nodo2 = 0.0f;
    float posicion_y_nodo2 = 0.0f;
    float costo_del_enlace = 0.0f;

};



class Grafo
{
public:
    Grafo();
    ~Grafo();
    void borra_grafo();
    bool lee_grafo(string archivo);
    void devuelve_vecinos_grafo_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const;
    void devuelve_vecinos_grafo_no_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const;
    bool devuelve_informacion_de_un_vertice_del_grafo(Arbol& arbol, string nodo, int nodo_padre, tipo_nodo_informacion& informacion) const;
    unsigned int size() const;
    tipo_enlace_de_grafo operator [] (unsigned int indice) const;

private:
    
    vector <tipo_enlace_de_grafo> grafo; //Guarda todas las conexiones entre nodos que hay en el CSV
    
    
};


#endif /* Grafo_hpp */
