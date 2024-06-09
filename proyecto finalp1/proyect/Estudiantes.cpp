#include <iostream>
#include <mysql.h>
#include <sstream>

using namespace std;

class Estudiantes {
private:
    MYSQL* conector;

public:
    Estudiantes(MYSQL* con);
    void crearEstudiante();
    void mostrarEstudiante();
    void modificarEstudiante(int id);
    void eliminarEstudiante(int id);
};

Estudiantes::Estudiantes(MYSQL* con) : conector(con) {}

void Estudiantes::crearEstudiante() {
    string nombres, apellidos, resultado;
    double nota1, nota2, nota3, nota4, promedio;

    cout << "Digite los nombres del Estudiante: ";
    cin.ignore();
    getline(cin, nombres);
    cout << "Digite los apellidos del Estudiante: ";
    getline(cin, apellidos);
    cout << "Digite la nota 1: ";
    cin >> nota1;
    cout << "Digite la nota 2: ";
    cin >> nota2;
    cout << "Digite la nota 3: ";
    cin >> nota3;
    cout << "Digite la nota 4: ";
    cin >> nota4;

    promedio = (nota1 + nota2 + nota3 + nota4) / 4;
    resultado = (promedio > 61) ? "aprobado" : "reprobado";

    stringstream ss;
    ss << "INSERT INTO notasestudiantes (nombres, apellidos, nota1, nota2, nota3, nota4, promedio, resultado) VALUES ('"
        << nombres << "', '" << apellidos << "', " << nota1 << ", " << nota2 << ", " << nota3 << ", " << nota4
        << ", " << promedio << ", '" << resultado << "')";

    string query = ss.str();
    if (mysql_query(conector, query.c_str()) == 0) {
        cout << "Estudiante creado exitosamente." << endl;
    }
    else {
        cout << "Error al crear estudiante: " << mysql_error(conector) << endl;
    }
}

void Estudiantes::mostrarEstudiante() {
    if (mysql_query(conector, "SELECT * FROM notasestudiantes") == 0) {
        MYSQL_RES* res = mysql_store_result(conector);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "\nID: " << row[0] << endl;
            cout << "Nombres: " << row[1] << endl;
            cout << "Apellidos: " << row[2] << endl;
            cout << "Nota 1: " << row[3] << endl;
            cout << "Nota 2: " << row[4] << endl;
            cout << "Nota 3: " << row[5] << endl;
            cout << "Nota 4: " << row[6] << endl;
            cout << "Promedio: " << row[7] << endl;
            cout << "Resultado: " << row[8] << endl;
            cout << "\n-----------------------------------------\n";
        }
        mysql_free_result(res);
    }
    else {
        cout << "Error al mostrar los estudiantes: " << mysql_error(conector) << endl;
    }
}

void Estudiantes::modificarEstudiante(int id) {
    string nuevoNombres, nuevoApellidos, nuevoResultado;
    double nuevaNota1, nuevaNota2, nuevaNota3, nuevaNota4, nuevoPromedio;

    cout << "Digite los nuevos nombres del Estudiante: ";
    cin.ignore();
    getline(cin, nuevoNombres);
    cout << "Digite los nuevos apellidos del Estudiante: ";
    getline(cin, nuevoApellidos);
    cout << "Digite la nueva nota 1: ";
    cin >> nuevaNota1;
    cout << "Digite la nueva nota 2: ";
    cin >> nuevaNota2;
    cout << "Digite la nueva nota 3: ";
    cin >> nuevaNota3;
    cout << "Digite la nueva nota 4: ";
    cin >> nuevaNota4;

    nuevoPromedio = (nuevaNota1 + nuevaNota2 + nuevaNota3 + nuevaNota4) / 4;
    nuevoResultado = (nuevoPromedio > 61) ? "aprobado" : "reprobado";

    stringstream ss;
    ss << "UPDATE notasestudiantes SET nombres = '" << nuevoNombres << "', apellidos = '" << nuevoApellidos << "', nota1 = " << nuevaNota1
        << ", nota2 = " << nuevaNota2 << ", nota3 = " << nuevaNota3 << ", nota4 = " << nuevaNota4 << ", promedio = " << nuevoPromedio
        << ", resultado = '" << nuevoResultado << "' WHERE id = " << id;

    string query = ss.str();
    if (mysql_query(conector, query.c_str()) == 0) {
        cout << "Estudiante modificado exitosamente." << endl;
    }
    else {
        cout << "Error al modificar el estudiante: " << mysql_error(conector) << endl;
    }
}

void Estudiantes::eliminarEstudiante(int id) {
    stringstream ss;
    ss << "DELETE FROM notasestudiantes WHERE id = " << id;
    string query = ss.str();
    if (mysql_query(conector, query.c_str()) == 0) {
        cout << "Estudiante eliminado exitosamente." << endl;
    }
    else {
        cout << "Error al eliminar el estudiante: " << mysql_error(conector) << endl;
    }
}