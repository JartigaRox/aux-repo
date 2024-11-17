#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <filesystem>

// Estructura del árbol genealógico
struct Familia {
    std::string nombre;
    std::string parentesco;
    int edad;
    Familia* padre = nullptr;
    Familia* madre = nullptr;
};

// Función para agregar un miembro individual
void agregarMiembro(std::map<std::string, Familia>& miembros, const std::string& nombre, const std::string& parentesco, int edad) {
    miembros[nombre] = {nombre, parentesco, edad};
}

// Función para agregar miembros en lote
void agregarMiembrosEnLote(std::map<std::string, Familia>& miembros) {
    std::string nombre, parentesco;
    int edad;

    std::cout << "Para finalizar la entrada de datos, ingrese '*' como nombre.\n";
    while (true) {
        std::cout << "Ingrese nombre (o '*' para terminar): ";
        std::cin >> nombre;
        if (nombre == "*") break;

        std::cout << "Ingrese parentesco: ";
        std::cin >> parentesco;
        std::cout << "Ingrese edad: ";
        std::cin >> edad;

        agregarMiembro(miembros, nombre, parentesco, edad);
        std::cout << "Miembro " << nombre << " agregado.\n";
    }
}

// Función para asignar padres
void asignarPadres(std::map<std::string, Familia>& miembros, const std::string& nombreHijo, const std::string& nombrePadre, const std::string& nombreMadre) {
    if (miembros.find(nombreHijo) != miembros.end()) {
        miembros[nombreHijo].padre = &miembros[nombrePadre];
        miembros[nombreHijo].madre = &miembros[nombreMadre];
    }
}

// Función para mostrar el menú
void mostrarMenu() {
    std::cout << "\nMenú:\n";
    std::cout << "1. Agregar miembro\n";
    std::cout << "2. Agregar miembros en lote\n";
    std::cout << "3. Asignar padres\n";
    std::cout << "4. Imprimir árbol genealógico\n";
    std::cout << "5. Exportar árbol genealógico\n";
    std::cout << "6. Importar árbol genealógico\n";
    std::cout << "7. Salir\n";
    std::cout << "Seleccione una opción: ";
}

// Función para imprimir ancestros en formato bonito
void imprimirAncestros(Familia* miembro, int nivel = 0) {
    if (miembro == nullptr) return;

    // Imprimir al miembro primero
    for (int i = 0; i < nivel; ++i) std::cout << "    ";
    std::cout << "--> " << miembro->parentesco << ": "" (" << miembro->nombre  << ", Edad: " << miembro->edad << "\n";

    // Recursivamente imprimir padre y madre
    //if (miembro->padre != nullptr || miembro->madre != nullptr) {
       // std::cout << "\nAncestros de " << miembro->nombre << ":\n";
  //  }
    if (miembro->padre != nullptr) {
        //std::cout << "Padre:\n";
        imprimirAncestros(miembro->padre, nivel + 1);
    }
    if (miembro->madre != nullptr) {
        //std::cout << "Madre:\n";
        imprimirAncestros(miembro->madre, nivel + 1);
    }
}


// Función para exportar el árbol genealógico a un archivo
void exportarArbolGenealogico(std::map<std::string, Familia>& miembros) {
    static int fileCounter = 1;
    std::string fileName = "arbol_genealogico_" + std::to_string(fileCounter++) + ".txt";
    std::ofstream archivo(fileName);
    if (archivo.is_open()) {
        for (const auto& miembro : miembros) {
            archivo << "Nombre: " << miembro.second.nombre << "\n";
            archivo << "Parentesco: " << miembro.second.parentesco << "\n";
            archivo << "Edad: " << miembro.second.edad << "\n";
            archivo << "Padre: " << (miembro.second.padre ? miembro.second.padre->nombre : "N/A") << "\n";
            archivo << "Madre: " << (miembro.second.madre ? miembro.second.madre->nombre : "N/A") << "\n";
            archivo << "\n";
        }
        archivo.close();
        std::cout << "Árbol genealógico exportado a " << fileName << "\n";
    } else {
        std::cout << "No se pudo abrir el archivo para escritura.\n";
    }
}

// Función para importar el árbol genealógico desde un archivo
void importarArbolGenealogico() {
    std::ifstream archivo;
    std::string texto;
    std::string archivoExiste;

    // Solicitar el nombre del archivo
    std::cout << "Ingrese el nombre del archivo que desea abrir: ";
    std::cin >> archivoExiste;

    // Intentar abrir el archivo en modo de lectura
    archivo.open(archivoExiste, std::ios::in);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo '" << archivoExiste << "' para lectura.\n";
        return;  // Salir de la función si no se puede abrir el archivo
    }

    // Leer y mostrar el contenido del archivo línea por línea
    while (getline(archivo, texto)) {
        std::cout << texto << std::endl;
    }

    // Cerrar el archivo después de leerlo
    archivo.close();
}



// Función principal
int main() {
    std::map<std::string, Familia> miembros;
    int opcion;

    do {
        mostrarMenu();
        std::cin >> opcion;
        std::string nombre, parentesco, nombrePadre, nombreMadre;
        int edad;

        switch (opcion) {
            case 1:
                std::cout << "Ingrese nombre: ";
                std::cin >> nombre;
                std::cout << "Ingrese parentesco: ";
                std::cin >> parentesco;
                std::cout << "Ingrese edad: ";
                std::cin >> edad;
                agregarMiembro(miembros, nombre, parentesco, edad);
                break;

            case 2:
                agregarMiembrosEnLote(miembros);
                break;

            case 3:
                std::cout << "Ingrese nombre del hijo: ";
                std::cin >> nombre;
                std::cout << "Ingrese nombre del padre: ";
                std::cin >> nombrePadre;
                std::cout << "Ingrese nombre de la madre: ";
                std::cin >> nombreMadre;
                asignarPadres(miembros, nombre, nombrePadre, nombreMadre);
                break;

            case 4:
                std::cout << "Ingrese el nombre de la persona de inicio: ";
                std::cin >> nombre;
                if (miembros.find(nombre) != miembros.end()) {
                    imprimirAncestros(&miembros[nombre]);
                } else {
                    std::cout << "Miembro no encontrado.\n";
                }
                break;

            case 5:
                exportarArbolGenealogico(miembros);
                break;

            case 6:
                importarArbolGenealogico();
                break;

            case 7:
                std::cout << "Saliendo...\n";
                break;

            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 7);

    return 0;
}
