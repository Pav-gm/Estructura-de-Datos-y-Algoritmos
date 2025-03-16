#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

struct Producto {
    int id;
    string nombre;
    int cantidad;
    double precio;
};

vector<Producto> inventario;

void agregarProducto(int id, const string& nombre, int cantidad, double precio) {
    for (const auto& producto : inventario) {
        if (producto.id == id) {
            cout << "Error: El ID " << id << " ya existe en el inventario." << endl;
            return;
        }
    }

    Producto nuevoProducto = { id, nombre, cantidad, precio };
    inventario.push_back(nuevoProducto);
    cout << "Producto '" << nombre << "' agregado correctamente." << endl;
}

void eliminarProducto(int id) {
    auto it = find_if(inventario.begin(), inventario.end(),
        [id](const Producto& p) { return p.id == id; });

    if (it != inventario.end()) {
        string nombre = it->nombre;
        inventario.erase(it);
        cout << "Producto '" << nombre << "' eliminado correctamente." << endl;
    }
    else {
        cout << "Error: No se encontró ningún producto con ID " << id << "." << endl;
    }
}

void actualizarCantidad(int id, int nuevaCantidad) {
    for (auto& producto : inventario) {
        if (producto.id == id) {
            producto.cantidad = nuevaCantidad;
            cout << "Cantidad del producto '" << producto.nombre << "' actualizada a " << nuevaCantidad << "." << endl;
            return;
        }
    }

    cout << "Error: No se encontró ningún producto con ID " << id << "." << endl;
}

void mostrarInventario() {
    cout << "\n--- INVENTARIO DE PRODUCTOS ---" << endl;
    cout << setw(5) << "ID" << setw(25) << "Nombre" << setw(10) << "Cantidad" << setw(10) << "Precio" << endl;
    cout << string(50, '-') << endl;

    for (const auto& producto : inventario) {
        cout << setw(5) << producto.id
            << setw(25) << producto.nombre
            << setw(10) << producto.cantidad
            << setw(10) << fixed << setprecision(2) << producto.precio << endl;
    }

    cout << string(50, '-') << endl;
}

void buscarProducto(const string& nombre) {
    vector<Producto> encontrados;
    string nombreLower = nombre;
    transform(nombreLower.begin(), nombreLower.end(), nombreLower.begin(), ::tolower);

    for (const auto& producto : inventario) {
        string productoNombre = producto.nombre;
        transform(productoNombre.begin(), productoNombre.end(), productoNombre.begin(), ::tolower);

        if (productoNombre.find(nombreLower) != string::npos) {
            encontrados.push_back(producto);
        }
    }

    if (!encontrados.empty()) {
        cout << "\nResultados de la búsqueda para '" << nombre << "':" << endl;
        cout << setw(5) << "ID" << setw(25) << "Nombre" << setw(10) << "Cantidad" << setw(10) << "Precio" << endl;
        cout << string(50, '-') << endl;

        for (const auto& producto : encontrados) {
            cout << setw(5) << producto.id
                << setw(25) << producto.nombre
                << setw(10) << producto.cantidad
                << setw(10) << fixed << setprecision(2) << producto.precio << endl;
        }

        cout << string(50, '-') << endl;
    }
    else {
        cout << "No se encontró ningún producto con el nombre '" << nombre << "'." << endl;
    }
}

double calcularValorTotal() {
    double valorTotal = 0.0;
    for (const auto& producto : inventario) {
        valorTotal += producto.cantidad * producto.precio;
    }

    cout << "\nValor total del inventario: $" << fixed << setprecision(2) << valorTotal << endl;
    return valorTotal;
}

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    // Inicializar el inventario con algunos productos
    inventario = {
        {1, "Laptop HP", 10, 800.0},
        {2, "Monitor LG 24\"", 15, 200.0},
        {3, "Teclado Mecánico", 20, 50.0},
        {4, "Mouse Inalámbrico", 30, 25.0},
        {5, "Disco Duro Externo 1TB", 8, 100.0}
    };

    int opcion;
    do {
        cout << "\n==== MENÚ DE GESTIÓN DE INVENTARIO ====\n";
        cout << "1. Mostrar inventario\n";
        cout << "2. Agregar producto\n";
        cout << "3. Eliminar producto\n";
        cout << "4. Actualizar cantidad\n";
        cout << "5. Buscar producto\n";
        cout << "6. Calcular valor total\n";
        cout << "0. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;

        // Validar la entrada
        if (cin.fail()) {
            cout << "Error: Entrada inválida. Por favor, ingrese un número." << endl;
            limpiarBuffer();
            continue;
        }

        // Procesar la opción seleccionada
        switch (opcion) {
        case 0:
            cout << "Saliendo del programa. ¡Hasta luego!" << endl;
            break;
        case 1:
            mostrarInventario();
            break;
        case 2: {
            int id;
            string nombre;
            int cantidad;
            double precio;

            cout << "\n--- AGREGAR NUEVO PRODUCTO ---\n";
            cout << "Ingrese ID del producto: ";
            cin >> id;
            if (cin.fail()) {
                cout << "Error: ID inválido." << endl;
                limpiarBuffer();
                break;
            }

            limpiarBuffer(); // Limpiar buffer antes de leer el nombre
            cout << "Ingrese nombre del producto: ";
            getline(cin, nombre);

            cout << "Ingrese cantidad en stock: ";
            cin >> cantidad;
            if (cin.fail() || cantidad < 0) {
                cout << "Error: Cantidad inválida." << endl;
                limpiarBuffer();
                break;
            }

            cout << "Ingrese precio del producto: ";
            cin >> precio;
            if (cin.fail() || precio < 0) {
                cout << "Error: Precio inválido." << endl;
                limpiarBuffer();
                break;
            }

            agregarProducto(id, nombre, cantidad, precio);
            break;
        }
        case 3: {
            int id;
            cout << "\n--- ELIMINAR PRODUCTO ---\n";
            cout << "Ingrese ID del producto a eliminar: ";
            cin >> id;
            if (cin.fail()) {
                cout << "Error: ID inválido." << endl;
                limpiarBuffer();
                break;
            }

            eliminarProducto(id);
            break;
        }
        case 4: {
            int id, nuevaCantidad;
            cout << "\n--- ACTUALIZAR CANTIDAD ---\n";
            cout << "Ingrese ID del producto: ";
            cin >> id;
            if (cin.fail()) {
                cout << "Error: ID inválido." << endl;
                limpiarBuffer();
                break;
            }

            cout << "Ingrese nueva cantidad en stock: ";
            cin >> nuevaCantidad;
            if (cin.fail() || nuevaCantidad < 0) {
                cout << "Error: Cantidad inválida." << endl;
                limpiarBuffer();
                break;
            }

            actualizarCantidad(id, nuevaCantidad);
            break;
        }
        case 5: {
            string nombre;
            cout << "\n--- BUSCAR PRODUCTO ---\n";
            limpiarBuffer(); // Limpiar buffer antes de leer el nombre
            cout << "Ingrese nombre o parte del nombre a buscar: ";
            getline(cin, nombre);

            buscarProducto(nombre);
            break;
        }
        case 6:
            calcularValorTotal();
            break;
        default:
            cout << "Opción inválida. Por favor, intente nuevamente." << endl;
        }
    } while (opcion != 0);

    return 0;
}