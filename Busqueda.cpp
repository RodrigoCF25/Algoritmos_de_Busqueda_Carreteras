//
//  Busqueda.cpp
//  Carreteras
//
//  Created by Rodri on 02/06/23.
//


#include "Busqueda.hpp"




using namespace::std;

#pragma warning(disable : 6011)

Busqueda::Busqueda()
{
}
//---------------------------------------------------------------------------------------------------------------

Busqueda::~Busqueda()
{

}
//---------------------------------------------------------------------------------------------------------------

bool Busqueda::lee_grafo(string archivo)
{
    
    return grafo.lee_grafo(archivo);

}

//---------------------------------------------------------------------------------------------------------------



bool Busqueda::busqueda_a_lo_ancho(string nodo_inicio, string nodo_final,bool grafo_no_dirigido, int& nodo_encontrado)
{

    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();

    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_nodo_final;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    int nodo_actual = 0;
    vector <tipo_enlace_de_grafo> vecinos;

    if (!grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, nodo_inicio, -1, informacion_del_nodo_inicio) || !grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, nodo_final, -1, informacion_del_nodo_final))
        return false;

    unsigned int t1, t2;
    t1 = (unsigned int)clock();
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);

    informacion_en_agenda informacion_del_nodo_para_la_agenda;
    informacion_del_nodo_para_la_agenda.nodo = 0;
    agenda.push_back(informacion_del_nodo_para_la_agenda);

    while (!agenda.esta_vacia())
    {
        nodo_actual = agenda.front().nodo;
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos"  << endl;
            return true;
        }

        agenda.pop_front();
        if(grafo_no_dirigido)
            grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        else
            grafo.devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        
        for (size_t i = 0; i < vecinos.size(); i++)
        {
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        }

        for (size_t i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, vecinos[i].nodo2, nodo_actual, informacion_del_hijo_a_adicionar);
            arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(nodo_actual, informacion_del_hijo_a_adicionar);
            informacion_del_nodo_para_la_agenda.nodo = arbol_de_busqueda.size()-1;
            agenda.push_back(informacion_del_nodo_para_la_agenda);
        }
        
        agenda.revisa_tamano_maximo_de_la_agenda();
        
    }
    return false;
}

//---------------------------------------------------------------------------------------------------------------

bool Busqueda::busqueda_primero_en_profundidad(string nodo_inicio, string nodo_final,bool grafo_no_dirigido, int& nodo_encontrado)
{
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();

    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    tipo_nodo_informacion informacion_del_nodo_final;
    int nodo_actual = 0;
    vector <tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, nodo_inicio, -1, informacion_del_nodo_inicio) || !grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, nodo_final, -1, informacion_del_nodo_final))
        return false;

    unsigned int t1, t2;
    t1 = (unsigned int)clock();
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);
    informacion_en_agenda informacion_del_nodo_para_la_agenda;
    informacion_del_nodo_para_la_agenda.nodo = 0;
    agenda.push_back(informacion_del_nodo_para_la_agenda);
    while (!agenda.esta_vacia())
    {
        nodo_actual = agenda.front().nodo;
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos"  << endl;
            return true;
        }

        agenda.pop_front();
        if(grafo_no_dirigido)
            grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        else
            grafo.devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);

        for (size_t i = 0; i < vecinos.size(); i++)
        {
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        }


        for (size_t i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, vecinos[i].nodo2, nodo_actual, informacion_del_hijo_a_adicionar);
            arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(nodo_actual, informacion_del_hijo_a_adicionar);
            informacion_del_nodo_para_la_agenda.nodo = arbol_de_busqueda.size()-1;
            agenda.push_front(informacion_del_nodo_para_la_agenda);
        }
        
        agenda.revisa_tamano_maximo_de_la_agenda();
        
    }
    t2 = (unsigned int)clock();
    cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
    cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
    cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos" << endl;
    return false;
}

//---------------------------------------------------------------------------------------------------------------


bool Busqueda::busqueda_profundidad_limitada(string nodo_inicio, string nodo_final, unsigned int nivel_de_profundidad_limite, bool grafo_no_dirigido, int& nodo_encontrado)
{

    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    tipo_nodo_informacion informacion_del_nodo_final;
    int nodo_actual = 0;

    vector <tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, nodo_inicio, -1, informacion_del_nodo_inicio) || !grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, nodo_final, -1, informacion_del_nodo_final))
        return false;

    unsigned int t1, t2;
    t1 = (unsigned int)clock();
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);

    informacion_en_agenda informacion_del_nodo_para_la_agenda;
    informacion_del_nodo_para_la_agenda.nodo = 0;
    agenda.push_back(informacion_del_nodo_para_la_agenda);

    while (!agenda.esta_vacia())
    {

        nodo_actual = agenda.front().nodo;
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos"  << endl;
            return true;
        }

        agenda.pop_front();

        if (arbol_de_busqueda[nodo_actual].nivel_de_profundidad < nivel_de_profundidad_limite)
        {

            if(grafo_no_dirigido)
                grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
            else
                grafo.devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);

            for (size_t i = 0; i < vecinos.size(); i++)
            {
                if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo2))
                {
                    vecinos.erase(vecinos.begin() + i);
                    i--;
                }
            }

            

            for (size_t i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, vecinos[i].nodo2, nodo_actual, informacion_del_hijo_a_adicionar);

                arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(nodo_actual, informacion_del_hijo_a_adicionar);
                informacion_del_nodo_para_la_agenda.nodo = arbol_de_busqueda.size()-1;
                agenda.push_front(informacion_del_nodo_para_la_agenda);
            }
            
            agenda.revisa_tamano_maximo_de_la_agenda();

        }

        
    }
    t2 = (unsigned int)clock();
    cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
    cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
    cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda()  << " nodos" << endl;
    return false;


}

//---------------------------------------------------------------------------------------------------------------


bool Busqueda::busqueda_de_profundidad_iterativa(string nodo_inicio, string nodo_final,unsigned int limite_inicial_de_profundidad,unsigned int incremento_en_profundidad,bool grafo_no_dirigido, int& nodo_encontrado)
{
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    tipo_nodo_informacion informacion_del_nodo_final;
    int nodo_actual = 0;
    unsigned int nivel_de_profundidad_limite = limite_inicial_de_profundidad;

    vector <tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, nodo_inicio, -1, informacion_del_nodo_inicio) || !grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, nodo_final, -1, informacion_del_nodo_final))
        return false;

    bool hijos_en_algun_nodo_que_esta_en_profundidad_limite = false;

    unsigned int t1, t2;
    t1 = (unsigned int)clock();
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);

    informacion_en_agenda informacion_del_nodo_para_la_agenda;
    informacion_del_nodo_para_la_agenda.nodo = 0;
    agenda.push_back(informacion_del_nodo_para_la_agenda);

    while (!agenda.esta_vacia())
    {
        nodo_actual = agenda.front().nodo;
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos" << endl;
            return true;
        }

        agenda.pop_front();
        unsigned int nivel_de_profundidad_del_nodo_actual = arbol_de_busqueda[nodo_actual].nivel_de_profundidad;
        if (nivel_de_profundidad_del_nodo_actual < nivel_de_profundidad_limite)
        {
            if(grafo_no_dirigido)
                grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
            else
                grafo.devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);

            for (size_t i = 0; i < vecinos.size(); i++)
            {
                if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo2))
                {
                    vecinos.erase(vecinos.begin() + i);
                    i--;
                }
            }



            for (size_t i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, vecinos[i].nodo2, nodo_actual, informacion_del_hijo_a_adicionar);

                arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(nodo_actual, informacion_del_hijo_a_adicionar);
                informacion_del_nodo_para_la_agenda.nodo = arbol_de_busqueda.size()-1;
                agenda.push_front(informacion_del_nodo_para_la_agenda);
            }
            agenda.revisa_tamano_maximo_de_la_agenda();
            
        }

        else
        {
            if(grafo_no_dirigido)
                grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
            else
                grafo.devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);

            for (size_t i = 0; i < vecinos.size(); i++)
                if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo2))
                {
                    vecinos.erase(vecinos.begin() + i);
                    i--;
                }

            //Debemos revisar que alguno de los hijos del nodo que est� en el nivel de profundidad limite
            //tenga hijos. Si por lo menos 1 de los nodos del nivel de profundidad limite tiene hijos
            //ya sabemos que vale la pena iterar
            if (!hijos_en_algun_nodo_que_esta_en_profundidad_limite && vecinos.size() > 0) //La 1era condici�n para ignorar el if m�s r�pido
                hijos_en_algun_nodo_que_esta_en_profundidad_limite = true;
        }

        

        //Solo si la agenda est� vac�a y vale la pena iterar, entonces hay que reiniciar el algoritmo, pero con un
        //nivel de profundidad aumentado en 1 unidad
        if (agenda.esta_vacia() && hijos_en_algun_nodo_que_esta_en_profundidad_limite)
        {
            arbol_de_busqueda.limpia_arbol();
            arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);
            informacion_del_nodo_para_la_agenda.nodo = 0;
            agenda.push_back(informacion_del_nodo_para_la_agenda);
            hijos_en_algun_nodo_que_esta_en_profundidad_limite = false;
            nivel_de_profundidad_limite += incremento_en_profundidad;
        }

    }
    t2 = (unsigned int)clock();
    cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
    cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
    cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos" << endl;
    return false;
}

//--------------------------------------------------------------------------------------------------------------

bool Busqueda::existe_un_nodo_comun_en_las_agendas(unsigned int& nodo_interseccion_arbol_inicio, unsigned int& nodo_interseccion_arbol_final) const
{

    for (size_t i = 0; i < agenda_desde_el_inicio.size(); i++)
    {
        
        for (int j = (int)agenda_desde_el_final.size() - 1; j >= 0; j--)
        {

            if (arbol_de_busqueda_desde_el_inicio[agenda_desde_el_inicio[(unsigned int)i].nodo].contenido.nombre_del_nodo == arbol_de_busqueda_desde_el_final[agenda_desde_el_final[(unsigned int)j].nodo].contenido.nombre_del_nodo)
            {
                
                nodo_interseccion_arbol_inicio = agenda_desde_el_inicio[(unsigned int)i].nodo;
                nodo_interseccion_arbol_final = agenda_desde_el_final[(unsigned int)j].nodo;
                
                return true;
            }
        }
    }

    return false;
}

//--------------------------------------------------------------------------------------------------------------


bool Busqueda::busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    arbol_de_busqueda_desde_el_inicio.limpia_arbol();
    agenda_desde_el_inicio.limpia_agenda();
    arbol_de_busqueda_desde_el_final.limpia_arbol();
    agenda_desde_el_final.limpia_agenda();
    
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_nodo_final;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    
    

    
    vector <tipo_enlace_de_grafo> vecinos;
    
    if (!grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_inicio, nodo_inicio, -1, informacion_del_nodo_inicio) || !grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_final, nodo_final, -1, informacion_del_nodo_final))
        return false;
    
    unsigned int t1, t2;
    t1 = (unsigned int)clock();
    arbol_de_busqueda_desde_el_inicio.crea_arbol(informacion_del_nodo_inicio);
    informacion_en_agenda informacion_del_nodo_para_la_agenda;
    informacion_del_nodo_para_la_agenda.nodo = 0;
    agenda_desde_el_inicio.push_back(informacion_del_nodo_para_la_agenda);
    
    arbol_de_busqueda_desde_el_final.crea_arbol(informacion_del_nodo_final);
    agenda_desde_el_final.push_back(informacion_del_nodo_para_la_agenda);
    
    unsigned int nodo_encontrado_desde_el_inicio = 0;
    unsigned int nodo_encontrado_desde_el_final = 0;
    unsigned int nodo_actual = 0;
    
    while (!agenda_desde_el_inicio.esta_vacia() || !agenda_desde_el_final.esta_vacia())
    {

        if (!agenda_desde_el_inicio.esta_vacia())
        {
            nodo_actual = agenda_desde_el_inicio.front().nodo;
            vecinos.clear();
            
            if (arbol_de_busqueda_desde_el_inicio[nodo_actual].contenido.nombre_del_nodo == nodo_final)
            {
                arbol_de_busqueda = arbol_de_busqueda_desde_el_inicio;
                nodo_encontrado = nodo_actual;
                t2 = (unsigned int)clock();
                cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
                cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
                cout << "Tamano maximo de la agenda: " << agenda_desde_el_inicio.obten_tamano_maximo_de_la_agenda() << " nodos"  << endl;
                return true;
            }
            
            agenda_desde_el_inicio.pop_front();
            grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda_desde_el_inicio[nodo_actual].contenido.nombre_del_nodo, vecinos);

            for (size_t i = 0; i < vecinos.size(); i++)
            {
                if (arbol_de_busqueda_desde_el_inicio.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo2))
                {
                    vecinos.erase(vecinos.begin() + i);
                    i--;
                }
            }
            
            for (size_t i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_inicio, vecinos[i].nodo2, nodo_actual, informacion_del_hijo_a_adicionar);
                arbol_de_busqueda_desde_el_inicio.agrega_hijo_a_un_nodo_del_arbol(nodo_actual, informacion_del_hijo_a_adicionar);
                informacion_del_nodo_para_la_agenda.nodo = arbol_de_busqueda_desde_el_inicio.size()-1;
                agenda_desde_el_inicio.push_back(informacion_del_nodo_para_la_agenda);
            }
            agenda_desde_el_inicio.revisa_tamano_maximo_de_la_agenda();
        }
        
        
        if (!agenda_desde_el_final.esta_vacia())
        {
            nodo_actual = agenda_desde_el_final.front().nodo;
            vecinos.clear();
            
            if (arbol_de_busqueda_desde_el_final[nodo_actual].contenido.nombre_del_nodo == nodo_inicio)
            {
                nodo_encontrado = nodo_actual;
                arbol_de_busqueda = arbol_de_busqueda_desde_el_final;
                
                t2 = (unsigned int)clock();
                cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
                cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
                cout << "Tamano maximo de la agenda: " << agenda_desde_el_final.obten_tamano_maximo_de_la_agenda() << " nodos" << endl;
                return true;
            }

            agenda_desde_el_final.pop_front();
            grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda_desde_el_final[nodo_actual].contenido.nombre_del_nodo, vecinos);
            
            for (size_t i = 0; i < vecinos.size(); i++)
            {
                if (arbol_de_busqueda_desde_el_final.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo2))
                {
                    vecinos.erase(vecinos.begin() + i);
                    i--;
                }
            }
            
            
            for (size_t i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_final, vecinos[i].nodo2, nodo_actual, informacion_del_hijo_a_adicionar);
                arbol_de_busqueda_desde_el_final.agrega_hijo_a_un_nodo_del_arbol(nodo_actual, informacion_del_hijo_a_adicionar);
                informacion_en_agenda informacion_del_nodo_para_la_agenda;
                informacion_del_nodo_para_la_agenda.nodo = arbol_de_busqueda_desde_el_final.size()-1;
                agenda_desde_el_final.push_front(informacion_del_nodo_para_la_agenda);
            }
            agenda_desde_el_final.revisa_tamano_maximo_de_la_agenda();
        }
        
        
        if (existe_un_nodo_comun_en_las_agendas(nodo_encontrado_desde_el_inicio, nodo_encontrado_desde_el_final))
        {
            unsigned int nodo_padre = nodo_encontrado_desde_el_inicio;
            unsigned int nodo_hijo = arbol_de_busqueda_desde_el_final[nodo_encontrado_desde_el_final].padre;
            tipo_nodo_del_arbol nodo_hijo_informacion;
            tipo_nodo_del_arbol nodo_hijo_informacion_actualizada;
            while(nodo_hijo != -1)
            {
                arbol_de_busqueda_desde_el_inicio[nodo_padre].hijos.clear();
                nodo_hijo_informacion.contenido = arbol_de_busqueda_desde_el_final[nodo_hijo].contenido;
                grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_inicio,nodo_hijo_informacion.contenido.nombre_del_nodo, nodo_padre, nodo_hijo_informacion_actualizada.contenido);
                arbol_de_busqueda_desde_el_inicio.agrega_hijo_a_un_nodo_del_arbol(nodo_padre, nodo_hijo_informacion_actualizada.contenido);
                arbol_de_busqueda_desde_el_inicio[nodo_padre].hijos.push_back(arbol_de_busqueda_desde_el_inicio.size()-1);
                nodo_padre = arbol_de_busqueda_desde_el_inicio.size() - 1;
                nodo_hijo = arbol_de_busqueda_desde_el_final[nodo_hijo].padre;
            }
            
            
            
            arbol_de_busqueda = arbol_de_busqueda_desde_el_inicio;
            nodo_encontrado = arbol_de_busqueda_desde_el_inicio.size()-1;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            cout << "Tamano del arbol desde el inicio: " << arbol_de_busqueda_desde_el_inicio.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda desde el inicio: " << agenda_desde_el_inicio.obten_tamano_maximo_de_la_agenda()  << endl;
            cout << "Tamano del arbol desde el final: " << arbol_de_busqueda_desde_el_final.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda desde el final: " << agenda_desde_el_final.obten_tamano_maximo_de_la_agenda()  << " nodos" << endl;
            return true;
        }
        
        
    }
    t2 = (unsigned int)clock();
    cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
    cout << "Tamano del arbol desde el inicio: " << arbol_de_busqueda_desde_el_inicio.size() << " nodos" << endl;
    cout << "Tamano maximo de la agenda desde el inicio: " << agenda_desde_el_inicio.obten_tamano_maximo_de_la_agenda()  << endl;
    cout << "Tamano del arbol desde el final: " << arbol_de_busqueda_desde_el_final.size() << " nodos" << endl;
    cout << "Tamano de la agenda desde el final: " << agenda_desde_el_final.obten_tamano_maximo_de_la_agenda()  << " nodos" << endl;
    return false;
}



//----------------------------------------------------------------------------------------------------------------


bool Busqueda::busqueda_ascenso_a_la_colina(string nodo_inicio, string nodo_final, TIPO_DE_OPTIMIZACION tipo_de_optimizacion, bool grafo_no_dirigido, int& nodo_econtrado)
{
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();

    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    tipo_nodo_informacion informacion_del_nodo_final;
    vector <tipo_enlace_de_grafo> vecinos;
    unsigned int nodo_actual = 0;

    if (!grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_inicio, nodo_inicio, -1, informacion_del_nodo_inicio) || !grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_final, nodo_final, -1, informacion_del_nodo_final))
        return false;

    unsigned int t1, t2;
    t1 = (unsigned int)clock();
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);
    informacion_en_agenda informacion_del_nodo_para_la_agenda;
    informacion_del_nodo_para_la_agenda.nodo = 0;
    agenda.push_back(informacion_del_nodo_para_la_agenda);

    unsigned int tamano_maximo_de_la_agenda = 0;
    
    while (!agenda.esta_vacia())
    {
        nodo_actual = agenda.front().nodo;
        vecinos.clear();

        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_econtrado = nodo_actual;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda: " << tamano_maximo_de_la_agenda << "nodos"  << endl;
            return true;
        }

        agenda.pop_front();

        if(grafo_no_dirigido)
            grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        else
            grafo.devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        
        for (size_t i = 0; i < vecinos.size(); i++)
        {

            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        }

        for (size_t i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, vecinos[i].nodo2, nodo_actual, informacion_del_hijo_a_adicionar);
            
            arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(nodo_actual, informacion_del_hijo_a_adicionar);
            informacion_del_nodo_para_la_agenda.nodo = arbol_de_busqueda.size()-1;
            informacion_del_nodo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
            agenda.push_back(informacion_del_nodo_para_la_agenda);
        }
        
        
        
        if(agenda.size()>0)
        {
            unsigned int indice_nodo_mejor_opcion = 0;
            if(tipo_de_optimizacion == TIPO_DE_OPTIMIZACION::MINIMIZAR_COSTO)
            {
                float minimo = INT_MAX;
                for(unsigned int i = 0; i < agenda.size();i++)
                    if(agenda[i].costo_acumulado < minimo)
                    {
                        minimo = agenda[i].costo_acumulado;
                        indice_nodo_mejor_opcion = i;
                    }
            }
            else
            {
                float maximo = -1 * INT_MAX;
                for(unsigned int i = 0; i < agenda.size();i++)
                    if(agenda[i].costo_acumulado > maximo)
                    {
                        maximo = agenda[i].costo_acumulado;
                        indice_nodo_mejor_opcion = i;
                    }
            }
            
            informacion_en_agenda nodo_mejor_opcion = agenda[indice_nodo_mejor_opcion];
            agenda.limpia_agenda();
            agenda.push_back(nodo_mejor_opcion);
            
            agenda.revisa_tamano_maximo_de_la_agenda();
            if(tamano_maximo_de_la_agenda < agenda.obten_tamano_maximo_de_la_agenda())
                tamano_maximo_de_la_agenda = agenda.obten_tamano_maximo_de_la_agenda();
        }
        else
        {
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda: " << tamano_maximo_de_la_agenda << " nodos"  << endl;
            return false;
        }
        
        
    }
    t2 = (unsigned int)clock();
    cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
    cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
    cout << "Tamano maximo de la agenda: " << tamano_maximo_de_la_agenda << " nodos"  << endl;
    return false;
}




//---------------------------------------------------------------------------------------------------------------

bool Busqueda::busqueda_primero_el_mejor(string nodo_inicio, string nodo_final, TIPO_DE_OPTIMIZACION tipo_de_optimizacion, bool grafo_no_dirigido, int& nodo_econtrado)
{
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();

    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    tipo_nodo_informacion informacion_del_nodo_final;
    vector <tipo_enlace_de_grafo> vecinos;
    unsigned int nodo_actual = 0;

    if (!grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_inicio, nodo_inicio, -1, informacion_del_nodo_inicio) || !grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_final, nodo_final, -1, informacion_del_nodo_final))
        return false;

    unsigned int t1, t2;
    t1 = (unsigned int)clock();
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);
    informacion_en_agenda informacion_del_nodo_para_la_agenda;
    informacion_del_nodo_para_la_agenda.nodo = 0;
    agenda.push_back(informacion_del_nodo_para_la_agenda);

    while (!agenda.esta_vacia())
    {
        nodo_actual = agenda.front().nodo;
        vecinos.clear();

        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_econtrado = nodo_actual;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            cout << "Tamao del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos" << endl;
            return true;
        }

        agenda.pop_front();

        if(grafo_no_dirigido)
            grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        else
            grafo.devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);

        for (size_t i = 0; i < vecinos.size(); i++)
        {
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        }

        for (size_t i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, vecinos[i].nodo2, nodo_actual, informacion_del_hijo_a_adicionar);

            arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(nodo_actual, informacion_del_hijo_a_adicionar);
            informacion_del_nodo_para_la_agenda.nodo = arbol_de_busqueda.size()-1;
            informacion_del_nodo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
            agenda.push_back(informacion_del_nodo_para_la_agenda);
        }
        agenda.revisa_tamano_maximo_de_la_agenda();

        if(agenda.size()>0)
        {
            if(tipo_de_optimizacion == TIPO_DE_OPTIMIZACION::MINIMIZAR_COSTO)
            {
                unsigned int indice_nodo_con_menor_costo = 0;
                float minimo = MAXFLOAT;
                for(unsigned int i = 0; i < agenda.size();i++)
                {
                    if(agenda[i].costo_acumulado < minimo)
                    {
                        indice_nodo_con_menor_costo = i;
                        minimo = agenda[i].costo_acumulado;
                    }
                }
                informacion_en_agenda nodo_con_menor_costo = agenda[indice_nodo_con_menor_costo];
                agenda.erase(indice_nodo_con_menor_costo);
                agenda.push_front(nodo_con_menor_costo);
                
            }
            else
            {
                unsigned int indice_nodo_con_mayor_costo = 0;
                float maximo = -1 * MAXFLOAT;
                for(unsigned int i = 0; i < agenda.size();i++)
                {
                    if(agenda[i].costo_acumulado > maximo)
                    {
                        indice_nodo_con_mayor_costo = i;
                        maximo = agenda[i].costo_acumulado;
                    }
                }
                informacion_en_agenda nodo_con_mayor_costo = agenda[indice_nodo_con_mayor_costo];
                agenda.erase(indice_nodo_con_mayor_costo);
                agenda.push_front(nodo_con_mayor_costo);
                
            }
        }
        
        
    }
    
    t2 = (unsigned int)clock();
    cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
    cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
    cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos"  << endl;

    return false;



}

//---------------------------------------------------------------------------------------------------------------




bool Busqueda::busqueda_k_beams(string nodo_inicio, string nodo_final, unsigned int k_mejores, TIPO_DE_OPTIMIZACION tipo_de_optimizacion, bool grafo_no_dirigido, int& nodo_econtrado)
{
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();

    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    tipo_nodo_informacion informacion_del_nodo_final;
    vector <tipo_enlace_de_grafo> vecinos;
    unsigned int nodo_actual = 0;

    if (!grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_inicio, nodo_inicio, -1, informacion_del_nodo_inicio) || !grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_final, nodo_final, -1, informacion_del_nodo_final))
        return false;

    unsigned int tamano_maximo_de_la_agenda = 0;
    unsigned int t1, t2;
    t1 = (unsigned int)clock();
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);
    informacion_en_agenda informacion_del_nodo_para_la_agenda;
    informacion_del_nodo_para_la_agenda.nodo = 0;
    agenda.push_back(informacion_del_nodo_para_la_agenda);
    
    
    while (!agenda.esta_vacia())
    {
        nodo_actual = agenda.front().nodo;
        vecinos.clear();

        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_econtrado = nodo_actual;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda: " << tamano_maximo_de_la_agenda << " nodos" << endl;
            return true;
        }

        agenda.pop_front();

        if(grafo_no_dirigido)
            grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        else
            grafo.devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);


        for (size_t i = 0; i < vecinos.size(); i++)
        {
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;

            }
        }

        for (size_t i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, vecinos[i].nodo2, nodo_actual, informacion_del_hijo_a_adicionar);

            arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(nodo_actual, informacion_del_hijo_a_adicionar);
            informacion_del_nodo_para_la_agenda.nodo = arbol_de_busqueda.size()-1;
            informacion_del_nodo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
            agenda.push_back(informacion_del_nodo_para_la_agenda);
        }
        
        
        
        
        if(!agenda.esta_vacia())
        {
            int contador_k_elementos_en_agenda = 0;
            Agenda agenda_temporal_ordenada;
            if (tipo_de_optimizacion == TIPO_DE_OPTIMIZACION::MINIMIZAR_COSTO)
            {
                while(contador_k_elementos_en_agenda < k_mejores && !agenda.esta_vacia())
                {
                    unsigned int indice_nodo_con_menor_costo = 0;
                    float minimo = INT_MAX;
                    for(unsigned int i = 0; i < agenda.size();i++)
                    {
                        if(agenda[i].costo_acumulado < minimo)
                        {
                            indice_nodo_con_menor_costo = i;
                            minimo = agenda[i].costo_acumulado;
                        }
                    }
                    agenda_temporal_ordenada.push_back(agenda[indice_nodo_con_menor_costo]);
                    agenda.erase(indice_nodo_con_menor_costo);
                    contador_k_elementos_en_agenda++;
                }
            }
            else
            {
                while(contador_k_elementos_en_agenda < k_mejores && !agenda.esta_vacia())
                {
                    unsigned int indice_nodo_con_mayor_costo = 0;
                    float maximo = -1 * INT_MAX;
                    for(unsigned int i = 0; i < agenda.size();i++)
                    {
                        if(agenda[i].costo_acumulado > maximo)
                        {
                            indice_nodo_con_mayor_costo = i;
                            maximo = agenda[i].costo_acumulado;
                        }
                    }
                    agenda_temporal_ordenada.push_back(agenda[indice_nodo_con_mayor_costo]);
                    agenda.erase(indice_nodo_con_mayor_costo);
                    contador_k_elementos_en_agenda++;
                }
            }
            
            
            if(!agenda_temporal_ordenada.esta_vacia())
            {
                agenda = agenda_temporal_ordenada;
            }
            
            agenda.revisa_tamano_maximo_de_la_agenda();
            
            if(tamano_maximo_de_la_agenda < agenda.obten_tamano_maximo_de_la_agenda())
                tamano_maximo_de_la_agenda = agenda.obten_tamano_maximo_de_la_agenda();
            
            
            
        }
        else
        {
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda: " << tamano_maximo_de_la_agenda << " nodos" << endl;
            return false;
        }
        
        

    }

    t2 = (unsigned int)clock();
    cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
    cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
    cout << "Tamano maximo de la agenda: " << tamano_maximo_de_la_agenda << " nodos"  << endl;
    return false;

}


//---------------------------------------------------------------------------------------------------------------


bool Busqueda::busqueda_branch_and_bound(string nodo_inicio, string nodo_final, bool grafo_no_dirigido, int& nodo_encontrado)
{
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    tipo_nodo_informacion informacion_del_nodo_final;
    unsigned int mejor_nodo = 0;
    unsigned int posicion_del_mejor_nodo = 0;
    float costo_del_mejor_nodo = 0.0f;
    int meta_temporal = -1;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_inicio, nodo_inicio, -1, informacion_del_nodo_inicio) || !grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_final, nodo_final, -1, informacion_del_nodo_final))
        return false;
        
    unsigned int t1 = 0,t2 = 0;
    t1 = (unsigned int)clock();
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);
    informacion_en_agenda informacion_del_nodo_para_la_agenda;
    informacion_del_nodo_para_la_agenda.nodo = 0;
    agenda.push_back(informacion_del_nodo_para_la_agenda);
    while (!agenda.esta_vacia())
    {
        mejor_nodo = agenda[0].nodo;
        posicion_del_mejor_nodo = 0;
        costo_del_mejor_nodo = agenda[0].costo_acumulado;
        for (unsigned int i = 1; i < agenda.size(); i++)
            if (costo_del_mejor_nodo >
                (agenda[i].costo_acumulado))
            {
                mejor_nodo = agenda[i].nodo;
                posicion_del_mejor_nodo = i;
                costo_del_mejor_nodo = agenda[i].costo_acumulado;
            }
        agenda.erase(posicion_del_mejor_nodo);
        
        if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == nodo_final)
        {
            if (meta_temporal == -1)
                meta_temporal = mejor_nodo;
            else
                if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado >
                    arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado)
                    meta_temporal = mejor_nodo;
            for (unsigned int i = 0; i < agenda.size(); i++)
                if (agenda[i].costo_acumulado >=
                    arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                {
                    agenda.erase(i);
                    i--;
                }
            if (agenda.esta_vacia())
            {
                nodo_encontrado = meta_temporal;
                t2 = (unsigned int)clock();
                cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
                cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
                cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos"  << endl;
                return true;
            }
        }
        
        if(grafo_no_dirigido)
            grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
        else
            grafo.devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
        
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(mejor_nodo, vecinos[i].nodo2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, vecinos[i].nodo2, mejor_nodo, informacion_del_hijo_a_adicionar);
            if (meta_temporal != -1)
                if(informacion_del_hijo_a_adicionar.costo_acumulado > arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                    continue;
            arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(mejor_nodo, informacion_del_hijo_a_adicionar);
            informacion_del_nodo_para_la_agenda.nodo = arbol_de_busqueda.size()-1;
            informacion_del_nodo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
            agenda.push_back(informacion_del_nodo_para_la_agenda);
        }
        agenda.revisa_tamano_maximo_de_la_agenda();
        
        if (agenda.esta_vacia())
        {
            nodo_encontrado = meta_temporal;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos"  << endl;
            return meta_temporal != -1;
        }
    }
    
    nodo_encontrado = meta_temporal;
    if(meta_temporal != -1)
    {
        t2 = (unsigned int)clock();
        cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
        cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
        cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos" << endl;
    }
    return meta_temporal != -1;
}

    
//---------------------------------------------------------------------------------------------------------------


//Devuelve el resultado de la siguiente operación: ((x_2-x_1))^2+ ((y_2-y_1))^2 Esta operacion parte de la formula de la distancia euclidiana, pero se omite la raíz cuadrada, ya que únicamente se desea obtener para cada nodo un valor que cuantifique su cercania con la meta y nos ahorramos de una operación. Unicamente es usada por el algoritmo de búsqueda A*.

float Busqueda::calcula_heuristica_a_la_meta(string nodo_actual, string meta) const
{
    float calculo = 0.0f;
    float x1 = 0.0f;
    float y1 = 0.0f;
    float x2 = 0.0f;
    float y2 = 0.0f;
    for (unsigned int i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo1 == nodo_actual)
        {
            x1 = grafo[i].posicion_x_nodo1;
            y1 = grafo[i].posicion_y_nodo1;
            break;
        }
        else if (grafo[i].nodo2 == nodo_actual)
        {
            x1 = grafo[i].posicion_x_nodo2;
            y1 = grafo[i].posicion_y_nodo2;
            break;
        }
    for (unsigned int i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo1 == meta)
        {
            x2 = grafo[i].posicion_x_nodo1;
            y2 = grafo[i].posicion_y_nodo1;
            break;
        }
        else if (grafo[i].nodo2 == meta)
        {
            x2 = grafo[i].posicion_x_nodo2;
            y2 = grafo[i].posicion_y_nodo2;
            break;
        }
    calculo = (float)(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return calculo;
}
    
    

bool Busqueda::busqueda_A_ESTRELLA(string nodo_inicio, string nodo_final, bool grafo_no_dirigido, int& nodo_encontrado)
{
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();

    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    tipo_nodo_informacion informacion_del_nodo_final;
    unsigned int mejor_nodo = 0;
    unsigned int posicion_del_mejor_nodo = 0;
    float costo_del_mejor_nodo = 0.0f;
    int meta_temporal = -1;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_inicio, nodo_inicio, -1, informacion_del_nodo_inicio) || !grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda_desde_el_final, nodo_final, -1, informacion_del_nodo_final))
        return false;
    
    unsigned int t1 = 0, t2 = 0;
    t1 = (unsigned int)clock();
    informacion_del_nodo_inicio.costo_estimado = calcula_heuristica_a_la_meta(nodo_inicio, nodo_final);
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);
    
    informacion_en_agenda informacion_del_nodo_para_la_agenda;
    informacion_del_nodo_para_la_agenda.nodo = 0;
    agenda.push_back(informacion_del_nodo_para_la_agenda);
    while (!agenda.esta_vacia())
    {
        mejor_nodo = agenda[0].nodo;
        posicion_del_mejor_nodo = 0;
        costo_del_mejor_nodo = agenda[0].costo_acumulado +
                               agenda[0].costo_estimado;
        for (unsigned int i = 1; i < agenda.size(); i++)
            if (costo_del_mejor_nodo >
                (agenda[i].costo_acumulado +
                    agenda[i].costo_estimado))
            {
                mejor_nodo = agenda[i].nodo;
                posicion_del_mejor_nodo = i;
                costo_del_mejor_nodo = agenda[i].costo_acumulado +
                                       agenda[i].costo_estimado;
            }
        agenda.erase(posicion_del_mejor_nodo);
        if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == nodo_final)
        {
            
            if (meta_temporal == -1)
                meta_temporal = mejor_nodo;
            else if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado >
                arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado)
                meta_temporal = mejor_nodo;
            for (unsigned int i = 0; i < agenda.size(); i++)
                if (agenda[i].costo_acumulado >=
                    arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                {
                    agenda.erase(i);
                    i--;
                }
            if (agenda.esta_vacia())
            {
                nodo_encontrado = meta_temporal;
                t2 = (unsigned int)clock();
                cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
                cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
                cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda()  << " nodos" << endl;
                return true;
            }
        }
       
        if(grafo_no_dirigido)
            grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
        else
            grafo.devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
        
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(mejor_nodo, vecinos[i].nodo2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda,vecinos[i].nodo2,
                mejor_nodo, informacion_del_hijo_a_adicionar);
            if (meta_temporal != -1)
                if (informacion_del_hijo_a_adicionar.costo_acumulado > arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                    continue;
            informacion_del_hijo_a_adicionar.costo_estimado = calcula_heuristica_a_la_meta(vecinos[i].nodo2,
                nodo_final);
            arbol_de_busqueda.agrega_hijo_a_un_nodo_del_arbol(mejor_nodo, informacion_del_hijo_a_adicionar);
            informacion_del_nodo_para_la_agenda.nodo = arbol_de_busqueda.size()-1;
            informacion_del_nodo_para_la_agenda.costo_acumulado = informacion_del_hijo_a_adicionar.costo_acumulado;
            informacion_del_nodo_para_la_agenda.costo_estimado = informacion_del_hijo_a_adicionar.costo_estimado;
            agenda.push_back(informacion_del_nodo_para_la_agenda);
        }
        agenda.revisa_tamano_maximo_de_la_agenda();
        
        if (agenda.esta_vacia())
        {
            nodo_encontrado = meta_temporal;
            t2 = (unsigned int)clock();
            cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
            cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
            cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos"  << endl;
            return meta_temporal != -1;
        }
    }
    
    nodo_encontrado = meta_temporal;

    t2 = (unsigned int)clock();
    cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
    cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
    cout << "Tamano maximo de la agenda: " << agenda.obten_tamano_maximo_de_la_agenda() << " nodos"  << endl;
    
    return meta_temporal != -1;
}


//---------------------------------------------------------------------------------------------------------------
bool Busqueda::busqueda_de_Dijkstra(string nodo_inicio, string nodo_final,bool grafo_no_dirigido,  int& nodo_encontrado)
{
    
    arbol_de_busqueda.limpia_arbol();
    agenda.limpia_agenda();
    nodo_encontrado = -1;
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_nodo_final;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int tamano_nodos_no_resueltos_maximo = 0;
    unsigned int numero_de_nodos_no_resueltos_que_se_tuvieron_en_total = 0;


    if (!grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, nodo_inicio, -1, informacion_del_nodo_inicio) || !grafo.devuelve_informacion_de_un_vertice_del_grafo(arbol_de_busqueda, nodo_final, -1, informacion_del_nodo_final))
    {
        return false;
    }

    unsigned int t1, t2;
    t1 = (unsigned int)clock();
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);
    
    Arbol_Binario nodos_resueltos = Arbol_Binario();
    nodos_resueltos.push(nodo_inicio);
    
    vector <tipo_nodo_del_arbol> nodos_no_resueltos;
    tipo_nodo_del_arbol nodo_no_resuelto;
    vector <tipo_enlace_de_grafo> vecinos_de_un_nodo_resuelto;
    unsigned int tamano_del_arbol_anterior_ciclo = 1, tamano_actual = 1;
    float menor_costo_acumulado;
    
    do
    {
        tamano_actual = arbol_de_busqueda.size();
        
        for(unsigned int i = tamano_actual - tamano_del_arbol_anterior_ciclo; i < tamano_actual;i++ ) //Obtenemos los vecinos de cada nodo_resuelto (estan en el arbol de busqueda
        {
            if(arbol_de_busqueda[i].contenido.nombre_del_nodo == nodo_final) //Es la meta ?
            {
                
                nodo_encontrado = i;
                t2 = (unsigned int)clock();
                cout << "Tiempo de busqueda: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl;
                cout << "Tamano del arbol: " << arbol_de_busqueda.size() << " nodos" << endl;
                cout << "Nodos no resueltos que se tuvieron en total: " << numero_de_nodos_no_resueltos_que_se_tuvieron_en_total<< " nodos" <<  endl;
                cout << "Tamano nodos no resueltos maximo: " << tamano_nodos_no_resueltos_maximo << " nodos" <<  endl;
                return true;
            }
            
            vecinos_de_un_nodo_resuelto.clear();
            //Obtener los vecinos de un nodo resuelto dependiendo del tipo de grafo
            if (grafo_no_dirigido)
                grafo.devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[i].contenido.nombre_del_nodo, vecinos_de_un_nodo_resuelto);
            else
                grafo.devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[i].contenido.nombre_del_nodo, vecinos_de_un_nodo_resuelto);
            
            //Si los vecinos ya son un nodo resuelto (estan el arbol de busqueda y en el binario), entonces no queremos expandirlos. Si no estan, entonces los metemos en el vector de nodos_no_resueltos (porque estos tienen posibilidad de expandirse)
            for(unsigned int j = 0; j < vecinos_de_un_nodo_resuelto.size();j++)
                if(!nodos_resueltos.esta_en_el_arbol(vecinos_de_un_nodo_resuelto[j].nodo2))
                {
                    nodo_no_resuelto.contenido.nombre_del_nodo = vecinos_de_un_nodo_resuelto[j].nodo2;
                    nodo_no_resuelto.contenido.costo_acumulado = arbol_de_busqueda[i].contenido.costo_acumulado + vecinos_de_un_nodo_resuelto[j].costo_nodo2 + vecinos_de_un_nodo_resuelto[j].costo_del_enlace;
                    nodo_no_resuelto.padre = i;
                    nodo_no_resuelto.nivel_de_profundidad = arbol_de_busqueda[nodo_no_resuelto.padre].nivel_de_profundidad + 1;
                    nodos_no_resueltos.push_back(nodo_no_resuelto);
                    numero_de_nodos_no_resueltos_que_se_tuvieron_en_total++;
                }
            
        }
        
        if(nodos_no_resueltos.size() > tamano_nodos_no_resueltos_maximo)
            tamano_nodos_no_resueltos_maximo = (unsigned int)nodos_no_resueltos.size();
        
        
        //Ahora que ya tenemos todos los nodos resueltos hasta este punto (iteracion), entonces hay que escoger el o los mejores (menor costo acumulado) y agregarlos al arbol de busqueda
        
        if(nodos_no_resueltos.size()>0)
        {
            //Encontrar de los nodos no resueltos el menor costo acumulado
            menor_costo_acumulado = nodos_no_resueltos[0].contenido.costo_acumulado;
            for (unsigned int i = 1; i < nodos_no_resueltos.size();i++)
                if(nodos_no_resueltos[i].contenido.costo_acumulado < menor_costo_acumulado)
                    menor_costo_acumulado = nodos_no_resueltos[i].contenido.costo_acumulado;
            

            
            for(unsigned int i = 0; i < nodos_no_resueltos.size();i++)
                //Seleccionar los nodos con menor costo acumulado y hacerlos nodos resueltos
                //Si hay nodos no resueltos iguales en nombre y costo acumulado, solo se vuelve resuelto uno de ellos (ya que son el mismo nodo)
                if(nodos_no_resueltos[i].contenido.costo_acumulado == menor_costo_acumulado && !nodos_resueltos.esta_en_el_arbol(nodos_no_resueltos[i].contenido.nombre_del_nodo))
                {
                    arbol_de_busqueda.push_back(nodos_no_resueltos[i]);
                    nodos_resueltos.push(nodos_no_resueltos[i].contenido.nombre_del_nodo);
                    nodos_no_resueltos.erase(nodos_no_resueltos.begin()+i);
                    i--;
                }

            //Eliminar de los nodos no resueltos aquellos que recien se volvieron nodos resueltos
            for(unsigned int i = 0; i < nodos_no_resueltos.size();i++)
                if(nodos_resueltos.esta_en_el_arbol(nodos_no_resueltos[i].contenido.nombre_del_nodo))
                {
                    nodos_no_resueltos.erase(nodos_no_resueltos.begin()+i);
                    i--;
                }
        }

        tamano_del_arbol_anterior_ciclo = tamano_actual;
        
        
    }while (!nodos_no_resueltos.empty());

    
    return false;
    

}



//-------------------------------------------------------------------------------------------------------------

string Busqueda::devuelve_la_ruta_encontrada(int nodo_encontrado) const
{
    
    return arbol_de_busqueda.devuelve_la_ruta_encontrada(nodo_encontrado);
}

