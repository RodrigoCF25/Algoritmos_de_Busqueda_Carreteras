//
//  Arbol_Binario.cpp
//  Carreteras
//
//  Created by Rodri on 02/06/23.
//



#include "Arbol_Binario.hpp"


Arbol_Binario::Arbol_Binario(void)
{
    
}

Arbol_Binario::~Arbol_Binario(void)
{
    
}

void Arbol_Binario::push(string pValue)
{
    
    
    Nodo nodo_a_agregar;
    nodo_a_agregar.value = pValue;
    
    if(arbol_binario.size() != 0)
    {
        unsigned int nodo_temp  = 0;
        string valor_del_nodo_temp = "";
    
        while(true)
        {
            valor_del_nodo_temp = arbol_binario[nodo_temp].value;
            if(pValue < valor_del_nodo_temp)
            {
                if(arbol_binario[nodo_temp].pIzq == "")
                {
                    arbol_binario.push_back(nodo_a_agregar);
                    arbol_binario[nodo_temp].pIzq = to_string(arbol_binario.size()-1);
                    break;
                }
                else
                    nodo_temp = stoi(arbol_binario[nodo_temp].pIzq);
            }
            else if(pValue > valor_del_nodo_temp)
            {
                if(arbol_binario[nodo_temp].pDer == "")
                {
                    arbol_binario.push_back(nodo_a_agregar);
                    arbol_binario[nodo_temp].pDer = to_string(arbol_binario.size()-1);
                    break;
                }
                else
                    nodo_temp = stoi(arbol_binario[nodo_temp].pDer);
            }
            else
                break;
        }
        
    }
    
    else
        arbol_binario.push_back(nodo_a_agregar);

}


bool Arbol_Binario::esta_en_el_arbol(string pValue)
{
    
    
    Nodo nodo_a_agregar;
    nodo_a_agregar.value = pValue;
    
    if(arbol_binario.size() != 0)
    {
        unsigned int nodo_temp  = 0;
        string valor_del_nodo_temp = "";
    
        while(true)
        {
            valor_del_nodo_temp = arbol_binario[nodo_temp].value;
            if(pValue < valor_del_nodo_temp)
            {
                if(arbol_binario[nodo_temp].pIzq == "") //No esta en el arbol
                    return false;
                else
                    nodo_temp = stoi(arbol_binario[nodo_temp].pIzq);
            }
            else if(pValue > valor_del_nodo_temp)
            {
                if(arbol_binario[nodo_temp].pDer == "") //No esta en el arbol
                    return false;
                else
                    nodo_temp = stoi(arbol_binario[nodo_temp].pDer);
            }
            else
                return true; //Esta en el arbol
        }
        
    }
    
    else //No hay nada en el arbol
        return false;

}







void Arbol_Binario::repr()
{

    vector <unsigned int> pila_de_nodos;
    unsigned int contador = 0;
   if(arbol_binario.size()!=0)
   {
       unsigned int nodo_temp = 0;
       string valor_de_nodo_temp = arbol_binario[nodo_temp].value;
       
       while(contador < arbol_binario.size() || pila_de_nodos.empty() == false)
       {
           
           if(valor_de_nodo_temp != "")
           {
               pila_de_nodos.push_back(nodo_temp);
               if(arbol_binario[nodo_temp].pIzq != "")
               {
                   nodo_temp = stoi(arbol_binario[nodo_temp].pIzq);
               }
               else
                   valor_de_nodo_temp = "";
           }
           else
           {
               nodo_temp = pila_de_nodos.back();
               valor_de_nodo_temp = arbol_binario[nodo_temp].value;
               cout << arbol_binario[nodo_temp].value << ", ";
               pila_de_nodos.pop_back();
               contador++;
               if(arbol_binario[nodo_temp].pDer != "")
               {
                   nodo_temp = stoi(arbol_binario[nodo_temp].pDer);
                   
               }
               else
                   valor_de_nodo_temp = "";
           }
           
       }
       
   }
    
    cout << endl;
}





void Arbol_Binario::clear()
{
    arbol_binario.clear();
}

