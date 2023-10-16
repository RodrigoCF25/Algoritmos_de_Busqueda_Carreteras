//
//  Agenda.hpp
//  Carreteras
//
//  Created by Rodri on 02/06/23.
//


#ifndef Agenda_hpp
#define Agenda_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>



using namespace std;


struct informacion_en_agenda
{
    unsigned int nodo = 0;
    float costo_acumulado = 0.0f;
    float costo_estimado = 0.0f;
    
};



class Agenda //Clase que se encarga de manejar la agenda de los algoritmos de busqueda
{
public:
    Agenda();
    ~Agenda();
    void push_back(informacion_en_agenda informacion_del_nodo_para_la_agenda);
    void push_front(informacion_en_agenda informacion_del_nodo_para_la_agenda);
    informacion_en_agenda front();
    informacion_en_agenda back();
    void pop_front();
    void pop_back();
    informacion_en_agenda operator [] (unsigned int indice) const;
    bool esta_vacia() const;
    void limpia_agenda();
    unsigned int size() const;
    void erase(unsigned int indice);
    void revisa_tamano_maximo_de_la_agenda();
    unsigned int obten_tamano_maximo_de_la_agenda();
    
private:
    vector <informacion_en_agenda> agenda;
    unsigned int tamano_maximo_de_la_agenda;
};



#endif /* Agenda_hpp */
