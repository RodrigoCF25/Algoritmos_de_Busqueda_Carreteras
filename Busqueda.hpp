//
//  Busqueda.hpp
//  Carreteras
//
//  Created by Rodri on 02/06/23.
//


#ifndef Busqueda_hpp
#define Busqueda_hpp

#include <stdio.h>
#include <ctime>
#include "Arbol.hpp"
#include "Agenda.hpp"
#include "Grafo.hpp"
#include "Arbol_Binario.hpp"

using namespace std;



enum class TIPO_DE_OPTIMIZACION //Mayor costo o menor costo
{
    MAXIMIZAR_COSTO,
    MINIMIZAR_COSTO
};



class Busqueda //Clase que se encarga de ejecutar los algoritmos de b�squedas en cualquier grafo
{
public:
    Busqueda();
    ~Busqueda();
    bool lee_grafo(string archivo);
    bool busqueda_a_lo_ancho(string nodo_inicio, string nodo_final, bool grafo_no_dirigido, int& nodo_encontrado);
    bool busqueda_primero_en_profundidad(string nodo_inicio, string nodo_final, bool grafo_no_dirigido, int& nodo_encontrado);
    bool busqueda_profundidad_limitada(string nodo_inicio, string nodo_final, unsigned int nivel_de_profundidad_limite,bool grafo_no_dirigido, int& nodo_encontrado);
    bool busqueda_de_profundidad_iterativa(string nodo_inicio, string nodo_final, unsigned int limite_inicial_de_profundidad, unsigned int incremento_en_profundidad, bool grafo_no_dirigido,int& nodo_encontrado);
    bool busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado);
    bool busqueda_ascenso_a_la_colina(string nodo_inicio, string nodo_final, TIPO_DE_OPTIMIZACION tipo_de_optimizacion,bool grafo_no_dirigido, int& nodo_econtrado);
    bool busqueda_primero_el_mejor(string nodo_inicio, string nodo_final, TIPO_DE_OPTIMIZACION tipo_de_optimizacion, bool grafo_no_dirigido, int& nodo_econtrado);
    bool busqueda_k_beams(string nodo_inicio, string nodo_final, unsigned int k_mejores, TIPO_DE_OPTIMIZACION tipo_de_optimizacion, bool grafo_no_dirigido, int& nodo_encontrado);
    string devuelve_la_ruta_encontrada(int nodo_encontrado) const;
    bool busqueda_branch_and_bound(string nodo_inicio, string nodo_final, bool grafo_no_dirigido, int& nodo_encontrado);
    float calcula_heuristica_a_la_meta(string nodo_actual, string meta) const;
    bool busqueda_A_ESTRELLA(string nodo_inicio, string nodo_final,bool grafo_no_dirigido,  int& nodo_encontrado);
    bool busqueda_de_Dijkstra(string nodo_inicio, string nodo_final,bool grafo_no_dirigido,  int& nodo_encontrado);
    
private:
    Grafo grafo;//Guarda todas las conexiones entre nodos que hay en el CSV
    Arbol arbol_de_busqueda; //Para algoritmos que usan un solo arbol
    Agenda agenda;
    Arbol arbol_de_busqueda_desde_el_inicio; //Para el bidireccional
    Agenda agenda_desde_el_inicio;
    Arbol arbol_de_busqueda_desde_el_final; //Para el bidireccional
    Agenda agenda_desde_el_final;
    bool existe_un_nodo_comun_en_las_agendas(unsigned int& nodo_interseccion_arbol_inicio, unsigned int& nodo_interseccion_arbol_final) const;


};


#endif /* Busqueda_hpp */
