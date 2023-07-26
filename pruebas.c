#include <stdio.h>
#include "lista.h"
#include "pa2mm.h"

#define ERROR -1
#define EXITO 0

/* En el caso de haber un error al crearse la lista, la función termina para que no haya errores 
al intentar a acceder a una lista que no existe. */
void prueba_lista_crear() {
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista != NULL, "Puedo crear una lista.");
	if (!lista) {
		return;
	}

    pa2m_afirmar(lista->nodo_inicio == NULL, "El nodo inicial es NULL.");
    pa2m_afirmar(lista->nodo_fin == NULL, "El nodo final es NULL.");
    pa2m_afirmar(lista->cantidad == 0, "Una lista se crea vacía.");

    lista_destruir(lista);
}

/* Asumo que la función lista_elemento_en_posicion funciona correctamente. 
Asumo que lista_crear funciona correctamente. */
void prueba_lista_insertar() {
	lista_t* lista = lista_crear();

	int numero = 5;
	char letra = 'a';

	pa2m_afirmar((lista_insertar(NULL, &numero) == ERROR), "No puedo insertar en una lista que es NULL.")
	pa2m_afirmar(lista->cantidad == 0, "La cantidad de elementos de la lista se mantiene en 0.");
	pa2m_afirmar(((lista->nodo_inicio == NULL) && (lista->nodo_fin == NULL)), "El nodo inicial y el nodo final siguen siendo NULL.")

	pa2m_afirmar((lista_insertar(lista, &numero) == EXITO), "Puedo insertar un elemento en una lista vacía.");
	pa2m_afirmar(lista->cantidad == 1, "La cantidad de elementos de la lista es 1.");
	pa2m_afirmar(((lista->nodo_inicio == lista->nodo_fin) && (lista->nodo_inicio != NULL) && (lista->nodo_fin != NULL)), "El nodo inicial y el nodo final apuntan al mismo nodo, y son distintos de NULL.");
	pa2m_afirmar(lista->nodo_inicio->elemento == &numero, "El elemento insertado es el correcto.");

	pa2m_afirmar((lista_insertar(lista, &letra) == EXITO), "Puedo insertar algo en una lista con un elemento.");
	pa2m_afirmar(lista->cantidad == 2, "La cantidad de elementos de la lista es 2.");
	pa2m_afirmar(lista->nodo_inicio != lista->nodo_fin, "El nodo inicial y el nodo final apuntan a un nodo diferente.");
	pa2m_afirmar(lista->nodo_fin->elemento == &letra, "El elemento insertado es el correcto.");

	pa2m_afirmar(((lista_insertar(lista, &numero) == EXITO) && (lista_insertar(lista, &letra) == EXITO) && (lista_insertar(lista, &numero) == EXITO)), "Puedo insertar tres elementos en una lista con dos elementos.");
	pa2m_afirmar(lista->cantidad == 5, "La cantidad de elementos de la lista es 3.");
	pa2m_afirmar(((lista->nodo_inicio->siguiente->siguiente->elemento == &numero) && (lista->nodo_inicio->siguiente->siguiente->siguiente->elemento == &letra) && (lista->nodo_fin->elemento == &numero)), "Los elementos insertados son los correctos.");

	int estado_lista = ERROR;
	int vector_numeros[100];

	for (int i = 0; i < 100; i++) {
		vector_numeros[i] = i;
		estado_lista = lista_insertar(lista, &vector_numeros[i]);
	}
	pa2m_afirmar(estado_lista == EXITO, "Puedo insertar 100 elementos en una lista con 5 elementos.");
	pa2m_afirmar(lista->cantidad == 105, "La cantidad de elementos de la lista es 105.");
	pa2m_afirmar((lista_elemento_en_posicion(lista, 83) == &vector_numeros[78]), "El elemento 78 esta en la posición 83.");

	lista_destruir(lista);
}

void prueba_lista_insertar_en_posicion() {
	lista_t* lista = lista_crear();

	int numero = 9;
	char letra = 'g';

	pa2m_afirmar((lista_insertar_en_posicion(NULL, &numero, 0) == ERROR), "No puedo insertar en una lista que es NULL.")
	pa2m_afirmar(lista->cantidad == 0, "La cantidad de elementos de la lista se mantiene en 0.");
	pa2m_afirmar(((lista->nodo_inicio == NULL) && (lista->nodo_fin == NULL)), "El nodo inicial y el nodo final siguen siendo NULL.")

	pa2m_afirmar((lista_insertar_en_posicion(lista, &numero, 1) == EXITO), "Le paso una posición que no existe y lo inserta en la última posición.");
	pa2m_afirmar(lista->cantidad == 1, "La cantidad de elementos de la lista es 1.");
	pa2m_afirmar(((lista->nodo_inicio == lista->nodo_fin) && (lista->nodo_inicio != NULL) && (lista->nodo_fin != NULL)), "El nodo inicial y el nodo final apuntan al mismo nodo, y son distintos de NULL.");

	lista_insertar(lista, &letra);
	lista_insertar(lista, &letra);
	pa2m_afirmar((lista_insertar_en_posicion(lista, &numero, 0) == EXITO), "Le paso una lista con tres elementos y la posición 0, y lo inserta en la primera posición.");
	pa2m_afirmar(lista->cantidad == 4, "La cantidad de elementos de la lista es 4.");

	pa2m_afirmar((lista_insertar_en_posicion(lista, &numero, 3) == EXITO), "Le paso una lista con cuatro elementos y la posición 3, y lo inserta correctamente.");
	pa2m_afirmar(lista->cantidad == 5, "La cantidad de elementos de la lista es 5.");

	lista_destruir(lista);
}

void prueba_lista_borrar() {
	lista_t* lista = lista_crear();

	char letra = 'm';

	pa2m_afirmar((lista_borrar(NULL) == ERROR), "Le paso una lista NULL y me devuelve error.");
	pa2m_afirmar((lista_borrar(lista) == ERROR), "Le paso una lista sin elementos y me devuelve error.");
	lista_insertar(lista, &letra);
	pa2m_afirmar((lista_borrar(lista) == EXITO), "Le paso una lista con un elemento y lo borra correctamente.");
	lista_insertar(lista, &letra);
	lista_insertar(lista, &letra);
	pa2m_afirmar((lista_borrar(lista) == EXITO), "Le paso una lista con dos elementos y borra el último correctamente.");

	lista_destruir(lista);
}

void prueba_lista_borrar_de_posicion() {
	lista_t* lista = lista_crear();

	int numero = 4;
	char letra = 'o';

	pa2m_afirmar((lista_borrar_de_posicion(NULL, 0) == ERROR), "Le paso una lista NULL y me devuelve error.");
	pa2m_afirmar((lista_borrar_de_posicion(lista, 0) == ERROR), "Le paso una lista sin elementos y me devuelve error.");
	lista_insertar(lista, &numero);
	pa2m_afirmar((lista_borrar_de_posicion(lista, 0) == EXITO), "Le paso una lista con un elemento y lo borra correctamente.");
	lista_insertar(lista, &letra);
	lista_insertar(lista, &numero);
	pa2m_afirmar((lista_borrar_de_posicion(lista, 0) == EXITO), "Le paso una lista con dos elementos y borra el de la posición indicada.");
	lista_insertar(lista, &numero);
	lista_insertar(lista, &letra);
	pa2m_afirmar((lista_borrar_de_posicion(lista, 1) == EXITO), "Le paso una lista con tres elementos y borra el de la posición indicada.");
	pa2m_afirmar((lista_borrar_de_posicion(lista, 3) == EXITO), "Le paso una lista con dos elementos y una posición que no existe, y borra el último correctamente.");

	lista_destruir(lista);
}

void prueba_lista_elemento_en_posicion() {
	lista_t* lista = lista_crear();

	int numero = 100;

	pa2m_afirmar((lista_elemento_en_posicion(NULL, 1) == NULL), "Le paso una lista NULL y me devuelve NULL.");
	pa2m_afirmar((lista_elemento_en_posicion(lista, 0) == NULL), "Le paso una posición que no existe y me devuelve NULL.");
	lista_insertar(lista, &numero);
	pa2m_afirmar((lista_elemento_en_posicion(lista, 0) == &numero), "Le paso una posición que existe y me devuelve el elemento correctamente.");

	lista_destruir(lista);
}

/* Asumo que la función lista_insertar funciona correctamente. */
void prueba_lista_ultimo() {
	lista_t* lista = lista_crear();

	int numero = 6;

	pa2m_afirmar((lista_ultimo(NULL) == NULL), "Le paso una lista NULL y me devuelve NULL.");
	pa2m_afirmar((lista_ultimo(lista) == NULL), "Le paso una lista sin elementos y me devuelve NULL.");
	lista_insertar(lista, &numero);
	pa2m_afirmar((lista_ultimo(lista) == &numero), "Le paso una lista con un elemento y me devuelve correctamente el último.");

	lista_destruir(lista);
}

void prueba_lista_vacia() {
	lista_t* lista = lista_crear();

	char letra = 'l';

	pa2m_afirmar((lista_vacia(NULL) == true), "Le paso una lista NULL y me devuelve que esta vacía.");
	pa2m_afirmar((lista_vacia(lista) == true), "Le paso una lista sin elementos y me devuelve que esta vacía.");
	lista_insertar(lista, &letra);
	pa2m_afirmar((lista_vacia(lista) == false), "Le paso una lista con un elemento y me devuelve que no esta vacía.");

	lista_destruir(lista);
}

void prueba_lista_elementos() {
	lista_t* lista = lista_crear();

	pa2m_afirmar((lista_elementos(NULL) == 0), "Le paso una lista NULL y me devuelve 0.");
	pa2m_afirmar((lista_elementos(lista) == 0), "Le paso una lista y me devuelve la cantidad de elementos correctamente.");

	lista_destruir(lista);
}

/* Asumo que lista_tope funciona. */
void prueba_lista_apilar() {
	lista_t* lista = lista_crear();

	int numero = 18;

	pa2m_afirmar((lista_apilar(NULL, &numero) == ERROR), "Le paso una lista NULL y me devuelve error.");
	pa2m_afirmar((lista_apilar(lista, &numero) == EXITO), "Le paso un elemento y lo apila.")
	pa2m_afirmar((lista_tope(lista) == &numero), "El tope de la pila es el elemento correcto.");
	pa2m_afirmar((lista->cantidad == 1), "La cantidad de elementos de la lista es 1.");

	lista_destruir(lista);
}

/* Asumo que lista_apilar funciona. */
void prueba_lista_desapilar() {
	lista_t* lista = lista_crear();

	char letra = 's';

	pa2m_afirmar((lista_desapilar(NULL) == ERROR), "Le paso una lista NULL y me devuelve error.");
	lista_apilar(lista, &letra);
	pa2m_afirmar((lista_desapilar(lista) == EXITO), "Le paso una lista con un elemento y lo desapila.")
	pa2m_afirmar((lista->cantidad == 0), "La cantidad de elementos de la lista es 0.");

	lista_destruir(lista);
}

void prueba_lista_tope() {
	lista_t* lista = lista_crear();

	int numero = 20;

	pa2m_afirmar((lista_tope(NULL) == NULL), "Le paso una lista NULL y me devuelve NULL.");
	pa2m_afirmar((lista_tope(lista) == NULL), "Le paso una lista sin elementos y me devuelve NULL.");
	lista_apilar(lista, &numero);
	pa2m_afirmar((lista_tope(lista) == &numero), "Le paso una lista con un elemento y me devuelve el último correctamente.")

	lista_destruir(lista);
}

/* Asumo que lista_primero funciona. */
void prueba_lista_encolar() {
	lista_t* lista = lista_crear();

	char letra = 'd';

	pa2m_afirmar((lista_apilar(NULL, &letra) == ERROR), "Le paso una lista NULL y me devuelve error.");
	pa2m_afirmar((lista_apilar(lista, &letra) == EXITO), "Le paso un elemento y lo encola.")
	pa2m_afirmar((lista_primero(lista) == &letra), "El primer elemento de la cola es el correcto.");

	lista_destruir(lista);
}

/* Asumo que lista_encolar funciona. */
void prueba_lista_desencolar() {
	lista_t* lista = lista_crear();

	int numero = 99;

	pa2m_afirmar((lista_desencolar(NULL) == ERROR), "Le paso una lista NULL y me devuelve error.");
	lista_encolar(lista, &numero);
	pa2m_afirmar((lista_desencolar(lista) == EXITO), "Le paso una lista con un elemento y lo desencola.")
	pa2m_afirmar((lista->cantidad == 0), "La cantidad de elementos de la lista es 0.");

	lista_destruir(lista);
}

/* Asumo que lista_encolar funciona. */
void prueba_lista_primero() {
	lista_t* lista = lista_crear();

	int numero = 74;

	pa2m_afirmar((lista_primero(NULL) == NULL), "Le paso una lista NULL y me devuelve NULL.");
	pa2m_afirmar((lista_primero(lista) == NULL), "Le paso una lista sin elementos y me devuelve NULL.");
	lista_encolar(lista, &numero);
	pa2m_afirmar((lista_primero(lista) == &numero), "Le paso una lista con un elemento y me devuelve el primero correctamente.")

	lista_destruir(lista);
}

void prueba_lista_iterador_externo() {
	lista_t* lista = lista_crear();
	lista_iterador_t* iterador = lista_iterador_crear(NULL);
	int numero1 = 21, numero2 = 12;

	pa2m_afirmar((iterador == NULL), "Le paso una lista NULL y me devuelve NULL.");
	lista_iterador_destruir(iterador);

	iterador = lista_iterador_crear(lista);
	pa2m_afirmar((iterador != NULL), "Puedo crear un iterador con una lista vacía.");
	pa2m_afirmar((lista_iterador_tiene_siguiente(iterador) == false), "El iterador no tiene siguiente.");
	pa2m_afirmar((lista_iterador_avanzar(iterador) == false), "El iterador no pudo avanzar.");
	pa2m_afirmar((lista_iterador_elemento_actual(iterador) == NULL), "No existe elemento actual.");
	lista_iterador_destruir(iterador);

	lista_insertar(lista, &numero1);
	lista_insertar(lista, &numero2);
	lista_insertar(lista, &numero1);
	lista_insertar(lista, &numero2);

	iterador = lista_iterador_crear(lista);
	pa2m_afirmar((lista_iterador_tiene_siguiente(iterador) == true), "El iterador tiene siguiente.");
	pa2m_afirmar((lista_iterador_avanzar(iterador) == true), "No estoy en el último elemento, devuelve true y avanza.");
	pa2m_afirmar((lista_iterador_elemento_actual(iterador) == &numero2), "El elemento actual es el correcto.");
	
	pa2m_afirmar((lista_iterador_tiene_siguiente(iterador) == true), "El iterador tiene siguiente.");
	pa2m_afirmar((lista_iterador_avanzar(iterador) == true), "No estoy en el último elemento, devuelve true y avanza.");
	pa2m_afirmar((lista_iterador_elemento_actual(iterador) == &numero1), "El elemento actual es el correcto.");
	
	pa2m_afirmar((lista_iterador_tiene_siguiente(iterador) == true), "El iterador tiene siguiente.");
	pa2m_afirmar((lista_iterador_avanzar(iterador) == true), "No estoy en el último elemento, devuelve true y avanza.");
	pa2m_afirmar((lista_iterador_elemento_actual(iterador) == &numero2), "El elemento actual es el correcto.");

	pa2m_afirmar((lista_iterador_avanzar(iterador) == false), "Estoy en el último elemento, devuelve false y no avanza.");
	pa2m_afirmar((lista_iterador_elemento_actual(iterador) == NULL), "El elemento actual es el correcto.");
	lista_iterador_destruir(iterador);

	lista_destruir(lista);
}

/* Suma los elementos de cada nodo. */
bool sumar_elementos(void *elemento, void *suma) {
	if((elemento) && (suma)) {
		*(int*)suma += *(int*)elemento;
	}

    return true;
}

void prueba_lista_iterador_interno() {
	lista_t* lista = lista_crear();
	int suma = 0;
	size_t elementos_recorridos = 0;
	int numero = 56;

	pa2m_afirmar((lista_con_cada_elemento(NULL, sumar_elementos, (void*)&suma) == 0), "Le paso una lista NULl y me devuelve 0.");
	pa2m_afirmar((lista_con_cada_elemento(lista, sumar_elementos, (void*)&suma) == 0), "Le paso una lista vacía y me devuelve 0.");
	pa2m_afirmar((lista_con_cada_elemento(lista, NULL, (void*)&suma) == 0), "Le paso una función NULL y me devuelve 0.");	
	lista_insertar(lista, &numero);
	lista_insertar(lista, &numero);
	lista_insertar(lista, &numero);
	pa2m_afirmar(((elementos_recorridos = (lista_con_cada_elemento(lista, sumar_elementos, (void*)&suma))) == 3), "Le paso una lista con elementos, los recorre correctamente y los suma.");
	pa2m_afirmar(elementos_recorridos == lista->cantidad, "La cantidad de elementos recorridos es igual a la cantidad de elementos en la lista.");
	printf("Recorri %lu elementos con el iterador interno y la suma de elementos total es %i\n", elementos_recorridos, suma);

	lista_destruir(lista);
}

int main() {
	pa2m_nuevo_grupo("Pruebas de creación de una lista.");
	prueba_lista_crear();

	pa2m_nuevo_grupo("Pruebas de insertar en una lista.");
	prueba_lista_insertar();

	pa2m_nuevo_grupo("Pruebas de insertar en posición en una lista.");
	prueba_lista_insertar_en_posicion();

	pa2m_nuevo_grupo("Pruebas de borrar el último elemento de una lista.");
	prueba_lista_borrar();

	pa2m_nuevo_grupo("Pruebas de borrar el elemento de la posición indicada.");
	prueba_lista_borrar_de_posicion();

	pa2m_nuevo_grupo("Pruebas de devolver el elemento en la posición indicada.");
	prueba_lista_elemento_en_posicion();

	pa2m_nuevo_grupo("Pruebas de devolver último elemento de una lista.");
	prueba_lista_ultimo();

	pa2m_nuevo_grupo("Pruebas de devolver si una lista esta vacía.");
	prueba_lista_vacia();

	pa2m_nuevo_grupo("Pruebas de devolver la cantidad de elementos en una lista.");
	prueba_lista_elementos();

	pa2m_nuevo_grupo("Pruebas de apilar elementos en una lista.");
	prueba_lista_apilar();

	pa2m_nuevo_grupo("Pruebas de desapilar elementos en una lista.");
	prueba_lista_desapilar();

	pa2m_nuevo_grupo("Pruebas de devolver el tope de una pila.");
	prueba_lista_tope();

	pa2m_nuevo_grupo("Pruebas de encolar elementos en una lista.");
	prueba_lista_encolar();

	pa2m_nuevo_grupo("Pruebas de desencolar elementos en una lista.");
	prueba_lista_desencolar();

	pa2m_nuevo_grupo("Pruebas de devolver el primer elemento de la cola.");
	prueba_lista_primero();

	pa2m_nuevo_grupo("Pruebas de iterador externo para una lista.");
	prueba_lista_iterador_externo();

	pa2m_nuevo_grupo("Pruebas de iterador interno para una lista.");
	prueba_lista_iterador_interno();

	return 0;
}