#include <mysql.h>
#include <iostream>
#include "Estudiantes.cpp"

using namespace std;


// Función para conectar a la base de datos
MYSQL* conectarDB() {
    MYSQL* conector = mysql_init(0);
    conector = mysql_real_connect(conector, "127.0.0.1", "root", "root", "estudiantes", 3306, NULL, 0);
    if (conector == nullptr) {
        cout << "Error al conectar la base de datos: " << mysql_error(conector) << endl;
    }
    return conector;
}

// Función para desconectar de la base de datos
void desconectarDB(MYSQL* conector) {
    if (conector) {
        mysql_close(conector);
    }
}


// Función principal
int main() {
    // Conectar a la base de datos
    MYSQL* con = conectarDB();
    if (!con) {
        cerr << "No se pudo conectar a la base de datos." << endl;
        return 1;
    }


    Estudiantes estu_notas(con);

    int opc, id;
    while (true) {
        cout << "\n\t\tMENU";
        cout << "\n\n\t1. Crear";
        cout << "\n\t2. Mostrar";
        cout << "\n\t3. Modificar";
        cout << "\n\t4. Eliminar";
        cout << "\n\t5. Salir";
        cout << "\n\n\tSeleccione una opcion: ";
        cin >> opc;

        switch (opc) {
        case 1:
            system("cls");
            estu_notas.crearEstudiante();
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            estu_notas.mostrarEstudiante();
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            cout << "\nDigite el Id del Estudiante a Modificar: ";
            cin >> id;
            estu_notas.modificarEstudiante(id);
            system("pause");
            system("cls");
            break;
        case 4:
            system("cls");
            cout << "\nDigite el Id del Estudiante a Eliminar: ";
            cin >> id;
            estu_notas.eliminarEstudiante(id);
            system("pause");
            system("cls");
            break;
        case 5:
            desconectarDB(con);
            system("cls");
            exit(1);
        default:
            cout << "\nOpcion no valida, intente de nuevo." << endl;
            system("pause");
            system("cls");
            break;
        }
    }

    return 0;
};


