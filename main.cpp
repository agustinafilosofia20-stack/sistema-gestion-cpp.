#include <iostream>
#include <string>
#include <vector>
#include <fstream> // Para trabajar con archivos

using namespace std;

// Clase Producto
class Producto {
public:
    string nombre;
    double precio;
    int stock;

    Producto(string n, double p, int s) {
        nombre = n;
        precio = p;
        stock = s;
    }

    void mostrar() {
        cout << "Producto: " << nombre << endl;
        cout << "Precio: $" << precio << endl;
        cout << "Stock: " << stock << endl << endl;
    }
};

// Guardar productos en archivo
void guardarInventario(vector<Producto> &inventario) {
    ofstream archivo("inventario.txt");
    for(int i = 0; i < inventario.size(); i++) {
        archivo << inventario[i].nombre << ";"
                << inventario[i].precio << ";"
                << inventario[i].stock << endl;
    }
    archivo.close();
}

// Cargar productos desde archivo
void cargarInventario(vector<Producto> &inventario) {
    ifstream archivo("inventario.txt");
    if (!archivo.is_open()) return;

    string linea;
    while(getline(archivo, linea)) {
        size_t pos1 = linea.find(";");
        size_t pos2 = linea.rfind(";");

        string nombre = linea.substr(0, pos1);
        double precio = stod(linea.substr(pos1+1, pos2-pos1-1));
        int stock = stoi(linea.substr(pos2+1));

        inventario.push_back(Producto(nombre, precio, stock));
    }

    archivo.close();
}

// Buscar producto por nombre
int buscarProducto(vector<Producto> &inventario, string nombre) {
    for(int i = 0; i < inventario.size(); i++) {
        if(inventario[i].nombre == nombre) {
            return i;
        }
    }
    return -1;
}

// Eliminar producto por nombre
void eliminarProducto(vector<Producto> &inventario, string nombre) {
    int pos = buscarProducto(inventario, nombre);
    if(pos != -1) {
        inventario.erase(inventario.begin() + pos);
        guardarInventario(inventario);
        cout << "Producto eliminado!" << endl << endl;
    } else {
        cout << "Producto no encontrado!" << endl << endl;
    }
}

// Generar reporte en CSV
void generarReporte(vector<Producto> &inventario) {
    ofstream archivo("reportes.csv");

    // Escribimos la cabecera
    archivo << "Nombre,Precio,Stock" << endl;

    double valorTotal = 0;
    for(int i = 0; i < inventario.size(); i++) {
        archivo << inventario[i].nombre << ","
                << inventario[i].precio << ","
                << inventario[i].stock << endl;
        valorTotal += inventario[i].precio * inventario[i].stock;
    }

    archivo.close();

    cout << "Reporte generado correctamente: reportes.csv" << endl;
    cout << "Valor total del stock: $" << valorTotal << endl << endl;
}

int main() {
    vector<Producto> inventario;
    cargarInventario(inventario);
    int opcion;

    do {
        cout << "=== SISTEMA DE GESTION DE PRODUCTOS ===" << endl;
        cout << "1. Agregar producto" << endl;
        cout << "2. Listar productos" << endl;
        cout << "3. Buscar producto" << endl;
        cout << "4. Eliminar producto" << endl;
        cout << "5. Salir" << endl;
        cout << "6. Generar reporte" << endl;
        cout << "Elija una opcion: ";
        cin >> opcion;
        cin.ignore();

        if(opcion == 1) {
            string nombre;
            double precio;
            int stock;

            cout << "Nombre del producto: ";
            getline(cin, nombre);
            cout << "Precio: $";
            cin >> precio;
            cout << "Stock: ";
            cin >> stock;
            cin.ignore();

            inventario.push_back(Producto(nombre, precio, stock));
            guardarInventario(inventario);
            cout << "Producto agregado!" << endl << endl;

        } else if(opcion == 2) {
            cout << "--- LISTA DE PRODUCTOS ---" << endl;
            for(int i = 0; i < inventario.size(); i++) {
                inventario[i].mostrar();
            }

        } else if(opcion == 3) {
            string nombre;
            cout << "Nombre del producto a buscar: ";
            getline(cin, nombre);
            int pos = buscarProducto(inventario, nombre);
            if(pos != -1) {
                cout << "Producto encontrado:" << endl;
                inventario[pos].mostrar();
            } else {
                cout << "Producto no encontrado!" << endl << endl;
            }

        } else if(opcion == 4) {
            string nombre;
            cout << "Nombre del producto a eliminar: ";
            getline(cin, nombre);
            eliminarProducto(inventario, nombre);

        } else if(opcion == 5) {
            cout << "Saliendo del programa..." << endl;

        } else if(opcion == 6) {
            generarReporte(inventario);

        } else {
            cout << "Opcion invalida, intente de nuevo." << endl;
        }

    } while(opcion != 5);

    return 0;
}
