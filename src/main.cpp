#include <iostream>
#include <memory>
#include <algorithm>
#include <optional>

struct Nodo {
    int clave;
    int altura;
    std::unique_ptr<Nodo> izquierdo;
    std::unique_ptr<Nodo> derecho;

    Nodo(int c) : clave(c), altura(1) {}
};

class ArbolAVL {
private:
    std::unique_ptr<Nodo> raiz;

    int obtenerAltura(const std::unique_ptr<Nodo>& nodo) const {
        return nodo ? nodo->altura : 0;
    }

    void actualizarAltura(std::unique_ptr<Nodo>& nodo) {
        nodo->altura = 1 + std::max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
    }

    int obtenerBalance(const std::unique_ptr<Nodo>& nodo) const {
        return nodo ? obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho) : 0;
    }

    std::unique_ptr<Nodo> rotacionDerecha(std::unique_ptr<Nodo> y) {
        std::unique_ptr<Nodo> x = std::move(y->izquierdo);
        std::unique_ptr<Nodo> T2 = std::move(x->derecho);
        x->derecho = std::move(y);
        x->derecho->izquierdo = std::move(T2);
        actualizarAltura(x->derecho);
        actualizarAltura(x);
        return x;
    }

    std::unique_ptr<Nodo> rotacionIzquierda(std::unique_ptr<Nodo> x) {
        std::unique_ptr<Nodo> y = std::move(x->derecho);
        std::unique_ptr<Nodo> T2 = std::move(y->izquierdo);
        y->izquierdo = std::move(x);
        y->izquierdo->derecho = std::move(T2);
        actualizarAltura(y->izquierdo);
        actualizarAltura(y);
        return y;
    }

    std::unique_ptr<Nodo> insertarNodo(std::unique_ptr<Nodo> nodo, int clave) {
        if (!nodo) return std::make_unique<Nodo>(clave);
        if (clave < nodo->clave) nodo->izquierdo = insertarNodo(std::move(nodo->izquierdo), clave);
        else if (clave > nodo->clave) nodo->derecho = insertarNodo(std::move(nodo->derecho), clave);
        else return nodo;

        actualizarAltura(nodo);
        int balance = obtenerBalance(nodo);

        if (balance > 1 && clave < nodo->izquierdo->clave)
            return rotacionDerecha(std::move(nodo));
        if (balance < -1 && clave > nodo->derecho->clave)
            return rotacionIzquierda(std::move(nodo));
        if (balance > 1 && clave > nodo->izquierdo->clave) {
            nodo->izquierdo = rotacionIzquierda(std::move(nodo->izquierdo));
            return rotacionDerecha(std::move(nodo));
        }
        if (balance < -1 && clave < nodo->derecho->clave) {
            nodo->derecho = rotacionDerecha(std::move(nodo->derecho));
            return rotacionIzquierda(std::move(nodo));
        }

        return nodo;
    }

    std::unique_ptr<Nodo> eliminarNodo(std::unique_ptr<Nodo> nodo, int clave) {
        if (!nodo) return nullptr;
        if (clave < nodo->clave) nodo->izquierdo = eliminarNodo(std::move(nodo->izquierdo), clave);
        else if (clave > nodo->clave) nodo->derecho = eliminarNodo(std::move(nodo->derecho), clave);
        else {
            if (!nodo->izquierdo) return std::move(nodo->derecho);
            if (!nodo->derecho) return std::move(nodo->izquierdo);

            Nodo* minimo = nodo->derecho.get();
            while (minimo->izquierdo)
                minimo = minimo->izquierdo.get();
            nodo->clave = minimo->clave;
            nodo->derecho = eliminarNodo(std::move(nodo->derecho), minimo->clave);
        }

        actualizarAltura(nodo);
        int balance = obtenerBalance(nodo);

        if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0)
            return rotacionDerecha(std::move(nodo));
        if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) {
            nodo->izquierdo = rotacionIzquierda(std::move(nodo->izquierdo));
            return rotacionDerecha(std::move(nodo));
        }
        if (balance < -1 && obtenerBalance(nodo->derecho) <= 0)
            return rotacionIzquierda(std::move(nodo));
        if (balance < -1 && obtenerBalance(nodo->derecho) > 0) {
            nodo->derecho = rotacionDerecha(std::move(nodo->derecho));
            return rotacionIzquierda(std::move(nodo));
        }

        return nodo;
    }

    const Nodo* buscarNodo(const std::unique_ptr<Nodo>& nodo, int clave) const {
        if (!nodo) return nullptr;
        if (clave == nodo->clave) return nodo.get();
        if (clave < nodo->clave) return buscarNodo(nodo->izquierdo, clave);
        return buscarNodo(nodo->derecho, clave);
    }

    void imprimirEnOrden(const std::unique_ptr<Nodo>& nodo) const {
        if (nodo) {
            imprimirEnOrden(nodo->izquierdo);
            std::cout << nodo->clave << " ";
            imprimirEnOrden(nodo->derecho);
        }
    }

    void imprimirEnOrdenInverso(const std::unique_ptr<Nodo>& nodo) const {
        if (nodo) {
            imprimirEnOrdenInverso(nodo->derecho);
            std::cout << nodo->clave << " ";
            imprimirEnOrdenInverso(nodo->izquierdo);
        }
    }

    int obtenerProfundidad(const std::unique_ptr<Nodo>& nodo, int clave, int profundidad = 0) const {
        if (!nodo) return -1;
        if (clave == nodo->clave) return profundidad;
        if (clave < nodo->clave) return obtenerProfundidad(nodo->izquierdo, clave, profundidad + 1);
        return obtenerProfundidad(nodo->derecho, clave, profundidad + 1);
    }

    int obtenerAlturaClave(const std::unique_ptr<Nodo>& nodo, int clave) const {
        if (!nodo) return -1;
        if (clave == nodo->clave) return obtenerAltura(nodo);
        if (clave < nodo->clave) return obtenerAlturaClave(nodo->izquierdo, clave);
        return obtenerAlturaClave(nodo->derecho, clave);
    }

    bool esAVLValido(const std::unique_ptr<Nodo>& nodo) const {
        if (!nodo) return true;
        int balance = obtenerBalance(nodo);
        if (balance > 1 || balance < -1) return false;
        return esAVLValido(nodo->izquierdo) && esAVLValido(nodo->derecho);
    }

public:
    // Inserta una clave en el árbol. Complejidad: O(log n)
    void insertar(int clave) { raiz = insertarNodo(std::move(raiz), clave); }

    // Elimina una clave del árbol. Complejidad: O(log n)
    void borrar(int clave) { raiz = eliminarNodo(std::move(raiz), clave); }

    // Busca una clave en el árbol. Complejidad: O(log n)
    bool buscar(int clave) const { return buscarNodo(raiz, clave) != nullptr; }

    // Imprime los elementos en orden ascendente. Complejidad: O(n)
    void imprimirAscendente() const { imprimirEnOrden(raiz); std::cout << "\n"; }

    // Imprime los elementos en orden descendente. Complejidad: O(n)
    void imprimirDescendente() const { imprimirEnOrdenInverso(raiz); std::cout << "\n"; }

    // Devuelve la altura del nodo con la clave dada. Complejidad: O(log n)
    int altura(int clave) const { return obtenerAlturaClave(raiz, clave); }

    // Devuelve la profundidad del nodo con la clave dada. Complejidad: O(log n)
    int profundidad(int clave) const { return obtenerProfundidad(raiz, clave); }

    // Devuelve el nivel del nodo con la clave dada (igual a profundidad). Complejidad: O(log n)
    int nivel(int clave) const { return obtenerProfundidad(raiz, clave); }

    // Verifica si el árbol cumple con las propiedades de un AVL. Complejidad: O(n)
    bool esAVL() const { return esAVLValido(raiz); }
};

int main() {
    ArbolAVL arbol;
    arbol.insertar(10);
    arbol.insertar(20);
    arbol.insertar(5);
    arbol.insertar(4);
    arbol.insertar(15);
    arbol.insertar(25);
    arbol.imprimirAscendente();
    arbol.imprimirDescendente();
    std::cout << "Buscar 15: " << (arbol.buscar(15) ? "Sí" : "No") << "\n";
    std::cout << "Altura 10: " << arbol.altura(10) << "\n";
    std::cout << "Profundidad 15: " << arbol.profundidad(15) << "\n";
    std::cout << "Nivel 15: " << arbol.nivel(15) << "\n";
    std::cout << "Es AVL: " << (arbol.esAVL() ? "Sí" : "No") << "\n";
    std::cout << "Borrar 10\n";
    arbol.borrar(10);
    arbol.imprimirAscendente();
    std::cout << "Es AVL: " << (arbol.esAVL() ? "Sí" : "No") << "\n";
    return 0;
}
