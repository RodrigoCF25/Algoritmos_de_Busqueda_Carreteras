//
//  Grafo.cpp
//  Carreteras
//
//  Created by Rodri on 02/06/23.
//


#include "Grafo.hpp"


Grafo::Grafo() //El constructor de la clase
{
    
}

Grafo::~Grafo() //El destructor de la clase
{
    
}
void Grafo::borra_grafo() //Limpia el vector
{
    grafo.clear();
}

bool Grafo::lee_grafo(string archivo) //Lee el archivo csv que se le pase
{
    grafo.clear(); //Se limpia el vector para guardar los datos del archivo (No queremos mezclar datos de viejos archivos con el actual)
    string linea_capturada = "";
    ifstream file(archivo);
    if (file.is_open())
    {
        unsigned int t1, t2;
        t1 = (unsigned int)clock();
        getline(file, linea_capturada); //Capturamos la primera fila, los encabezados
        while (getline(file, linea_capturada)) //Capturamos las filas posteriores, los datos que nos importan
        {
            string dato = "";
            stringstream linea_csv(linea_capturada);
            int indice_columna = 0; //entero que nos indicara la columna en la que estamos, para saber que valor del archivo vamos a guardar y en que variable
            string ciudad1 = "", ciudad2 = "";
            float costo_ciudad1 = 0.0f, costo_ciudad2 = 0.0f, costo_del_enlace = 0.0f, coordenadaX_ciudad1 = 0.0f, coordenadaY_ciudad1 = 0.0f, coordenadaX_ciudad2 = 0.0f, coordenadaY_ciudad2 = 0.0f;
            while (getline(linea_csv, dato, ',')) //dato va recibiendo los valores de linea_csv teniendo como delimitador la coma
            {
                switch (indice_columna)
                {
                case 0:
                {
                    ciudad1 = dato;
                    break;
                }
                case 1:
                    costo_ciudad1 = atof(dato.c_str());
                    break;
                case 2:
                    coordenadaX_ciudad1 = atof(dato.c_str());;
                    break;
                case 3:
                    coordenadaY_ciudad1 = atof(dato.c_str());;
                    break;
                case 4:
                {
                    ciudad2 = dato;
                    break;
                }
                case 5:
                    costo_ciudad2 = stof(dato.c_str());
                    break;
                case 6:
                    coordenadaX_ciudad2 = atof(dato.c_str());;
                    break;
                case 7:
                    coordenadaY_ciudad2 = atof(dato.c_str());;
                    break;
                case 8:
                    costo_del_enlace = atof(dato.c_str());;
                    break;

                default:
                    break;
                }

                indice_columna++;

            }

            if(ciudad1 != ciudad2) //Medida preventiva en caso de que hubiera un registro erroneo donde un nodo se conecta consigo mismo
            {
                tipo_enlace_de_grafo informacion_enlace_nodos = { ciudad1,costo_ciudad1,coordenadaX_ciudad1,coordenadaY_ciudad1,ciudad2,costo_ciudad2, coordenadaX_ciudad2,coordenadaY_ciudad2,costo_del_enlace,};
                grafo.push_back(informacion_enlace_nodos); //El enlace entre dos nodos se guarda al final del vector
            }


        }
        file.close(); //Se cierra el archivo, ya que hemos obtenido lo que necesitabamos
        t2 = (unsigned int)clock();
        cout << "Tiempo lectura: " << (double(t2 - t1) / CLOCKS_PER_SEC) << " segundos" << endl << endl;
        return true;
    }
    else
        return false;
}




//devuelve los vecinos del nodo que se le pasa como parametro considerando el caso de que el grafo es dirigido
// es decir, que las conexiones solamente llevan el sentido de nodo1 a nodo2
//Las conexiones que tengan el nodo en la variable nodo1, se guardan en el vector vecinos (pasado por referencia)
void Grafo::devuelve_vecinos_grafo_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const
{
    vecinos.clear();
    tipo_enlace_de_grafo temporal;
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo1 == nodo)
            vecinos.push_back(grafo[i]);
}

//devuelve los vecinos del nodo que se le pasa como parametro considerando el caso de que el grafo es no dirigido
// es decir, que las conexiones son bidireccionales, pudiendo ir del nodo1 al nodo2 y viceversa.
//Por consiguiente, se busca tambien el nodo en la variable nodo2. Si se cumple tal situacion, se invierten los datos de las variables del nodo1 y nodo2 en la variable temporal, para contar con un mismo formato.
//Se almacenan las conexiones donde esta el nodo en el vecctor vecinos (pasado por referencia).
void Grafo::devuelve_vecinos_grafo_no_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const
{
    
    vecinos.clear();
    tipo_enlace_de_grafo temporal;
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo1 == nodo)
            vecinos.push_back(grafo[i]);
        else if (grafo[i].nodo2 == nodo)
        {
            temporal.nodo1 = grafo[i].nodo2;
            temporal.costo_nodo1 = grafo[i].costo_nodo2;
            temporal.posicion_x_nodo1 = grafo[i].posicion_x_nodo2;
            temporal.posicion_y_nodo1 = grafo[i].posicion_y_nodo2;
            temporal.nodo2 = grafo[i].nodo1;
            temporal.costo_nodo2 = grafo[i].costo_nodo1;
            temporal.posicion_x_nodo2 = grafo[i].posicion_x_nodo1;
            temporal.posicion_y_nodo2 = grafo[i].posicion_y_nodo1;
            temporal.costo_del_enlace = grafo[i].costo_del_enlace;
            vecinos.push_back(temporal);
        }
}


//Se busca la conexion entre el nodo_padre y el nodo (hijo) en el vector grafo para poder entregar los datos del hijo:
//el nombre del nodo y el costo acumuluado (suma del costo del nodo, costo acumulado del padre y del costo del enlace)
//En caso de ser el primer nodo del arbol,se busca un enlace donde este el nodo y el costo acumulado es unicamente
//el costo del nodo
bool Grafo::devuelve_informacion_de_un_vertice_del_grafo(Arbol& arbol, string nodo, int nodo_padre, tipo_nodo_informacion& informacion) const
{
    float costo_acumulado_del_padre = 0.0f;
    string nombre_del_nodo_padre = "";
    if (nodo_padre != -1)
    {
        costo_acumulado_del_padre = arbol[nodo_padre].contenido.costo_acumulado;

        nombre_del_nodo_padre = arbol[nodo_padre].contenido.nombre_del_nodo;

        for (size_t i = 0; i < grafo.size(); i++)
        {
            if (grafo[i].nodo1 == nodo && grafo[i].nodo2 == nombre_del_nodo_padre)
            {
                informacion.nombre_del_nodo = grafo[i].nodo1;
                informacion.costo_acumulado = grafo[i].costo_nodo1 + costo_acumulado_del_padre + grafo[i].costo_del_enlace;
                return true;
            }
            else if(grafo[i].nodo2 == nodo && grafo[i].nodo1 == nombre_del_nodo_padre)
            {
                informacion.nombre_del_nodo = grafo[i].nodo2;
                informacion.costo_acumulado = grafo[i].costo_nodo2 +
                    costo_acumulado_del_padre +
                    grafo[i].costo_del_enlace;

                return true;
            }
        }

        return false;

    }
    else
    {
        for (size_t i = 0; i < grafo.size(); i++)
        {
            if (grafo[i].nodo1 == nodo)
            {
                informacion.nombre_del_nodo = grafo[i].nodo1;
                informacion.costo_acumulado = grafo[i].costo_nodo1;
                return true;
            }
            
            else if (grafo[i].nodo2 == nodo)
            {
                informacion.nombre_del_nodo = grafo[i].nodo2;
                informacion.costo_acumulado = grafo[i].costo_nodo2;
                return true;
            }
        }
        return false;
    }
}





//Sobrecarga del operador [] para poder acceder a los valores del vector grafo.
tipo_enlace_de_grafo Grafo::operator [] (unsigned int indice) const
{
    return grafo[indice];
}


//Devuelve el tamano del vector grafo
unsigned int Grafo::size() const
{
    return (unsigned int)grafo.size();
}


