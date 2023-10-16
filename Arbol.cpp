//
//  Arbol.cpp
//  Carreteras
//
//  Created by Rodri on 02/06/23.
//

#include "Arbol.hpp"


using  namespace::std;


Arbol::Arbol()
{

}

Arbol::~Arbol()
{

}


//añade el primer nodo al arbol, el cual no tiene padre y su nivel de profundidad es cero
void Arbol::crea_arbol(tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol nodo;
    nodo.contenido = contenido;
    nodo.nivel_de_profundidad = 0;
    nodo.padre = -1;
    arbol.push_back(nodo);
}


//añade un nodo al arbol y crea la union entre el padre y el nuevo nodo (hijo)
void Arbol::agrega_hijo_a_un_nodo_del_arbol(int padre, tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol nodo;
    nodo.contenido = contenido;
    nodo.nivel_de_profundidad = arbol[padre].nivel_de_profundidad + 1;
    nodo.padre = padre;
    arbol.push_back(nodo);
    arbol[padre].hijos.push_back((unsigned int)arbol.size() - 1);
}


//añade un nodo al vector arbol, misma funcion que el push_back de un vector cualquiera
void Arbol::push_back(tipo_nodo_del_arbol nodo)
{
    arbol.push_back(nodo);
}


//limpia el vector arbol
void Arbol::limpia_arbol()
{
    arbol.clear();
}

//recorre los ancestros del nodo_actual para saber si el nombre del nodo (un vecino) no ha sido parte de su camino o rama.
//Si es un ancestro, se devuelve un true. En caso contrario, un false
bool Arbol::esta_un_nodo_en_ancestros(unsigned int nodo_actual, string nombre_del_nodo) const
{
    int temporal = arbol[nodo_actual].padre;
    while (temporal != -1) {
        if (arbol[temporal].contenido.nombre_del_nodo == nombre_del_nodo)
            return true;
        temporal = arbol[temporal].padre;
    }
    return false;
}


//devuelve el tamaño del vector arbol
unsigned int Arbol::size() const
{
    return (unsigned int)arbol.size();
}


//Sobrecarga del operador [] para poder acceder a los valores del vector arbol, en lugar de una funcion get
tipo_nodo_del_arbol Arbol::operator [] (unsigned int indice) const
{
    return arbol[indice];
}


//Borra el elemento que este en tal poscion del vector
void Arbol::erase(unsigned int indice)
{
    arbol.erase(arbol.begin() + indice);
}


//A partir del nodo_encontrado (la meta) se hace un recorrido hacia atras almacenando los indices de los ancestros hasta llegar al inicio cuyo padre es -1. Se entrega un string con la ruta de inicio a meta y el costo acumulado
string Arbol::devuelve_la_ruta_encontrada(int nodo_encontrado) const
{
    vector<unsigned int> temporal;
    string ruta = "";
    temporal.clear();
    
    float costo_acumulado = 0.0f;
    
    
    costo_acumulado += arbol[nodo_encontrado].contenido.costo_acumulado;
    
    while (nodo_encontrado != -1)
    {
        temporal.push_back(nodo_encontrado);
        nodo_encontrado = arbol[nodo_encontrado].padre;
    }
    
    
    
    for (int i = (int)temporal.size() - 1; i >= 0; i--)
    {
        ruta = ruta + "->" + arbol[temporal[i]].contenido.nombre_del_nodo;
    }
    
    ruta = ruta + "  costo total = " + to_string(costo_acumulado);
    
    return ruta;
}
