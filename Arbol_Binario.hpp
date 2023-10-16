//
//  Arbol_Binario.hpp
//  Carreteras
//
//  Created by Rodri on 02/06/23.
//


#ifndef Arbol_Binario_hpp
#define Arbol_Binario_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;



struct Nodo
{
    string value = "";
    string pDer = "";
    string pIzq = "";
};




class Arbol_Binario
{
public:
    Arbol_Binario(void);
    ~Arbol_Binario();
    void push(string pValue); 
    bool esta_en_el_arbol(string pValue);
    void repr();
    void clear();
    
private:
    vector <Nodo> arbol_binario;
    
};

#endif /* Arbol_Binario_hpp */
