//
//  Agenda.cpp
//  Carreteras
//
//  Created by Rodri on 02/06/23.
//


#include "Agenda.hpp"

using namespace std;

Agenda::Agenda()
{
    tamano_maximo_de_la_agenda = 0;
}

Agenda::~Agenda()
{
}

void Agenda::push_back(informacion_en_agenda informacion_del_nodo_para_la_agenda)
{
    agenda.push_back(informacion_del_nodo_para_la_agenda);
}

void Agenda::push_front(informacion_en_agenda informacion_del_nodo_para_la_agenda)
{
    agenda.insert(agenda.begin(), informacion_del_nodo_para_la_agenda);
}

informacion_en_agenda Agenda::front()
{
    return agenda.front();
}

informacion_en_agenda Agenda::back()
{
    return agenda.back();
}


void Agenda::pop_front()
{
    agenda.erase(agenda.begin());
}

void Agenda::pop_back()
{
    agenda.erase(agenda.end()-1);
}

informacion_en_agenda Agenda::operator [] (unsigned int indice) const
{
    return agenda[indice];
}


void Agenda:: revisa_tamano_maximo_de_la_agenda()
{
    if(tamano_maximo_de_la_agenda < agenda.size())
        tamano_maximo_de_la_agenda = (unsigned int)agenda.size();
}

unsigned int Agenda::obten_tamano_maximo_de_la_agenda()
{
    return tamano_maximo_de_la_agenda;
}


bool Agenda::esta_vacia() const
{
    return agenda.empty();
}



void Agenda::limpia_agenda()
{
    tamano_maximo_de_la_agenda = 0;
    agenda.clear();
}


unsigned int Agenda::size() const
{
    return (unsigned int)agenda.size();
}

void Agenda::erase(unsigned int indice)
{
    agenda.erase(agenda.begin() + indice);
}
