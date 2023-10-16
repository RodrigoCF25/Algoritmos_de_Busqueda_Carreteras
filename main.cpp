//
//  main.cpp
//  Carreteras
//
//  Created by Rodri on 02/06/23.
//


#include <iostream>
#include "Busqueda.hpp"
#include <fstream>
#include <ctime>



#define RutaGrafo "Mexico-USA.csv"

int main(int argc, const char * argv[])
{
    
    
    Busqueda algoritmo_busqueda = Busqueda();
    int nodo_encontrado = -1;
    string ruta = "";
    
    if (algoritmo_busqueda.lee_grafo(RutaGrafo))
    {
        
        
        cout << "BUSQUEDAS Grafo Dirigido" << endl;
        
        cout <<"Cancun - Chetumal" << endl;
        
        
        
        cout << "Busqueda a lo ancho" << endl;
        if (algoritmo_busqueda.busqueda_a_lo_ancho("Cancun", "Chetumal", false, nodo_encontrado))
        {
            
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
            
            cout << ruta << endl;
            
        }
        else
            cout << "No hay ruta posible" << endl;
        
        cout << "---------------------------------------------------" << endl;
        
        
        
        cout << "Busqueda primero en profundidad" << endl;
        if (algoritmo_busqueda.busqueda_primero_en_profundidad("Cancun", "Chetumal", false, nodo_encontrado))
        {
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
            cout << ruta << endl;
        }
        else
            cout << "No hay ruta posible" << endl;
        
        
        
        cout << "---------------------------------------------------" << endl;
        
        cout << "Busqueda profundidad limitada" << endl;
        
        if (algoritmo_busqueda.busqueda_profundidad_limitada("Cancun", "Chetumal", 10, false, nodo_encontrado))
        {
            
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada((nodo_encontrado));
            cout << ruta << endl;
        }
        else
            cout << "No hay ruta posible" << endl;
        
        
        cout << "---------------------------------------------------" << endl;
        
        
        cout << "Busqueda profundidad iterativa" << endl;
        
        if (algoritmo_busqueda.busqueda_de_profundidad_iterativa("Cancun", "Chetumal",5,5, false, nodo_encontrado))
        {
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
            cout << ruta << endl;
        }
        else
            cout << "No hay ruta posible" << endl;
        
        cout << "---------------------------------------------------" << endl;
        
        
        
        
        cout << "Busqueda Ascenso a la colina MINIMIZAR" << endl;
        
        
        if (algoritmo_busqueda.busqueda_ascenso_a_la_colina("Cancun", "Chetumal", TIPO_DE_OPTIMIZACION::MINIMIZAR_COSTO, false, nodo_encontrado))
        {
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
            cout << ruta << endl;
        }
        else
            cout << "No hay ruta posible" << endl;
        
        
        cout << "---------------------------------------------------" << endl;
        
        cout << "Busqueda Ascenso a la colina MAXIMIZAR" << endl;
        
        
        if (algoritmo_busqueda.busqueda_ascenso_a_la_colina("Cancun", "Chetumal", TIPO_DE_OPTIMIZACION::MAXIMIZAR_COSTO, false, nodo_encontrado))
        {
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
            cout << ruta << endl;
        }
        else
            cout << "No hay ruta posible" << endl;
        
        
        cout << "---------------------------------------------------" << endl;
        
        cout << "Busqueda primero el mejor MINIMIZAR" << endl;
        
        
        if (algoritmo_busqueda.busqueda_primero_el_mejor("Cancun", "Chetumal", TIPO_DE_OPTIMIZACION::MINIMIZAR_COSTO, false, nodo_encontrado))
        {
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
            cout << ruta << endl;
        }
        else
            cout << "No hay ruta posible" << endl;
        
        
        cout << "---------------------------------------------------" << endl;
        
        cout << "Busqueda primero el mejor MAXIMIZAR" << endl;
        
        
        if (algoritmo_busqueda.busqueda_primero_el_mejor("Cancun", "Chetumal", TIPO_DE_OPTIMIZACION::MAXIMIZAR_COSTO, false, nodo_encontrado))
        {
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
            cout << ruta << endl;
        }
        else
            cout << "No hay ruta posible" << endl;
        
        
        cout << "---------------------------------------------------" << endl;
        
        cout << "Busqueda K beams MINIMIZAR" << endl;
        
        
        if (algoritmo_busqueda.busqueda_k_beams("Cancun", "Chetumal", 10, TIPO_DE_OPTIMIZACION::MINIMIZAR_COSTO, false, nodo_encontrado))
        {
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
            cout << ruta << endl;
        }
        else
            cout << "No hay ruta posible" << endl;
        
        
        cout << "---------------------------------------------------" << endl;
        
        
        
        cout << "Busqueda K beams MAXIMIZAR" << endl;
        
        
        if (algoritmo_busqueda.busqueda_k_beams("Cancun", "Chetumal", 10, TIPO_DE_OPTIMIZACION::MAXIMIZAR_COSTO, false, nodo_encontrado))
        {
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
            cout << ruta << endl;
        }
        else
            cout << "No hay ruta posible" << endl;
        
        
        cout << "---------------------------------------------------" << endl;
        
        
        cout << "Busqueda BRANCH_AND_BOUND" << endl;
        
        
        if (algoritmo_busqueda.busqueda_branch_and_bound("Cancun", "Chetumal",false, nodo_encontrado))
        {
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
            cout << ruta << endl;
        }
        else
            cout << "No hay ruta posible" << endl;
        
        
        cout << "---------------------------------------------------" << endl;
        
        
        cout << "Busqueda A ESTRELLA" << endl;
        
        
        if (algoritmo_busqueda.busqueda_A_ESTRELLA("Cancun", "Chetumal", false, nodo_encontrado))
        {
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
            cout << ruta << endl;
        }
        else
            cout << "No hay ruta posible" << endl;
        
        cout << "---------------------------------------------------" << endl << endl;
        
        
        cout << "Busqueda de Dijkstra" << endl;
        if (algoritmo_busqueda.busqueda_de_Dijkstra("Cancun", "Chetumal", false, nodo_encontrado))
        {
            
            ruta = algoritmo_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
            
            cout << ruta << endl;
        }
        cout << "---------------------------------------------------" << endl;
        
        return 0;
        
    }
}
