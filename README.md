# Arboles AVL
Fundamentos - Algoritmos - C++ - Implementación árbol AVL

En un AVL, se crea insertando nodos con un valor (clave), el primer elemento constituye la raíz del árbol.
Para subsiguientes inserciones si el clave del nodo es menor, se inserta a la izquierda o a la derecha si es mayor.

Cada nodo del AVL es un AVL en si mismo.

El arbol se considera balanceado cuando tiene un elemento en izquierda y/o en derecha, y a su vez estos solo tienen un elemento a su izquierda y/o derecha.

Para una mejor explicacion ver:

    El Profe Ariel. (2022, December 30). Árboles binarios en lenguaje C [Cap. 5: Balanceo, Árbol AVL] [Video].
    
    YouTube. https://www.youtube.com/watch?v=6zFL7I0vuzQ

Este programa implementa una clase ArbolAVL con metodos para manipularlo y se hace una breve demostracion de las funciones recursivas que recorren el arbol:

* Inserta una clave en el árbol. Complejidad: O(log n), Recursiva.
* Elimina una clave del árbol. Complejidad: O(log n), Recursiva.
* Busca una clave en el árbol. Complejidad: O(log n), Recursiva.
* Imprime los elementos en orden ascendente. Complejidad: O(n), Recursiva.
* Imprime los elementos en orden descendente. Complejidad: O(n), Recursiva.
* Devuelve la altura del nodo con la clave dada. Complejidad: O(log n), Recursiva.
* Devuelve la profundidad del nodo con la clave dada. Complejidad: O(log n), Recursiva.
* Devuelve el nivel del nodo con la clave dada (igual a profundidad). Complejidad: O(log n), Recursiva.
* Verifica si el árbol cumple con las propiedades de un AVL. Complejidad: O(n), Recursiva.

Un arbol:
```
     (100)
   /       \
 (90)     (110)
```

Se escribe en orden como: 90 , 100 , 110

Su orden inverso como: 110 , 100 , 90

