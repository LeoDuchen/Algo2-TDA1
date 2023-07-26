#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define ERROR -1
#define EXITO 0

lista_t* lista_crear() {
	lista_t* lista = malloc(1 * sizeof(lista_t));
	if (!lista) {
		return NULL;
	}

	lista->nodo_inicio = NULL;
	lista->nodo_fin = NULL;
	lista->cantidad = 0;

	return lista;
}

int lista_insertar(lista_t* lista, void* elemento) {
	if (!lista) {
		return ERROR;
	}

	nodo_t* nodo_nuevo = malloc(1 * sizeof(nodo_t));
	if (!nodo_nuevo) {
		return ERROR;
	}

	if (!lista->nodo_inicio) {
		lista->nodo_inicio = nodo_nuevo;
	}

	nodo_nuevo->elemento = elemento;
	nodo_nuevo->siguiente = NULL;

	if (lista->nodo_fin != NULL) {
		lista->nodo_fin->siguiente = nodo_nuevo;
	}
	lista->nodo_fin = nodo_nuevo;
	lista->cantidad++;
	
	return EXITO;
}

/* Devuelve el nodo en la posición indicada.*/
nodo_t* buscar_nodo_en_posicion(nodo_t* nodo, size_t posicion) {
	int posicion_buscada = 0;

	while (posicion_buscada != posicion) {
		nodo = nodo->siguiente;
		posicion_buscada++;
	}

	return nodo;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion) {
	if (!lista) {
		return ERROR;
	}

	if (posicion < lista->cantidad) {
		nodo_t* nodo_nuevo = malloc(1 * sizeof(nodo_t));
		if (!nodo_nuevo) {
			return ERROR;
		}
		nodo_nuevo->elemento = elemento;

		if (posicion == 0) {
			nodo_nuevo->siguiente = lista->nodo_inicio;
			lista->nodo_inicio = nodo_nuevo;
		} else {
			nodo_t* nodo_en_posicion = lista->nodo_inicio;
			nodo_t* nodo_aux = NULL;

			nodo_en_posicion = buscar_nodo_en_posicion(nodo_en_posicion, (posicion - 1));
			nodo_aux = nodo_en_posicion->siguiente;
			nodo_en_posicion->siguiente = nodo_nuevo;
			nodo_nuevo->siguiente = nodo_aux;
		}

		lista->cantidad++;
	} else {
		lista_insertar(lista, elemento);
	}

	return EXITO;
}

int lista_borrar(lista_t* lista) {
	if ((!lista) || (lista->cantidad == 0)) {
		return ERROR;
	}

	if (lista->nodo_inicio->siguiente == NULL) {
		free(lista->nodo_inicio);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		lista->cantidad--;
		return EXITO;
	}

	nodo_t* nodo_actual = lista->nodo_inicio;

	while (nodo_actual->siguiente != lista->nodo_fin) {
		nodo_actual = nodo_actual->siguiente;
	}

	free(nodo_actual->siguiente);
	nodo_actual->siguiente = NULL;
	lista->nodo_fin = nodo_actual;
	lista->cantidad--;

	return EXITO;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion) {
	if ((!lista) || (lista->cantidad == 0)) {
		return ERROR;
	}

	if ((lista->nodo_inicio->siguiente == NULL) || (posicion >= lista->cantidad)) {
		lista_borrar(lista);
		return EXITO;
	}

	nodo_t* nodo = lista->nodo_inicio;
	nodo_t* nodo_a_eliminar;

	if (posicion == 0) {
		lista->nodo_inicio = nodo->siguiente;
		free(nodo);
		lista->cantidad--;
		return EXITO;
	}

	nodo = buscar_nodo_en_posicion(nodo, posicion - 1);

	nodo_a_eliminar = nodo->siguiente;
	nodo->siguiente = nodo->siguiente->siguiente;
	free(nodo_a_eliminar);
	lista->cantidad--;

	return EXITO;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion) {
	if ((!lista) || (posicion >= lista->cantidad)) {
		return NULL;
	}

	nodo_t* nodo = lista->nodo_inicio;

	nodo = buscar_nodo_en_posicion(nodo, posicion);

	return nodo->elemento;
}

void* lista_ultimo(lista_t* lista) {
	if ((!lista) || (lista->cantidad == 0)) {
		return NULL;
	}

	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista) {
	if ((!lista) || (lista->cantidad == 0)) {
		return true;
	}

	return false;
}

size_t lista_elementos(lista_t* lista) {
	if (!lista) {
		return 0;
	}

	return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento) {
	return lista_insertar(lista, elemento);
}

int lista_desapilar(lista_t* lista) {
	return lista_borrar(lista);
}

void* lista_tope(lista_t* lista) {
	return lista_ultimo(lista);
}

int lista_encolar(lista_t* lista, void* elemento) {
	return lista_insertar(lista, elemento);
}

int lista_desencolar(lista_t* lista) {
	return lista_borrar_de_posicion(lista, 0);
}

void* lista_primero(lista_t* lista) {
	return lista_elemento_en_posicion(lista, 0);
}

void lista_destruir(lista_t* lista) {
	if (!lista) {
		return;
	}

	if (lista->nodo_inicio) {
		nodo_t* nodo = lista->nodo_inicio;
		while (lista->nodo_inicio->siguiente != NULL) {
			lista->nodo_inicio = nodo->siguiente;
			free(nodo);
			nodo = lista->nodo_inicio;
		}
		free(lista->nodo_inicio);
	}

	free(lista);
}

lista_iterador_t* lista_iterador_crear(lista_t* lista) {
	if (!lista) {
		return NULL;
	}

	lista_iterador_t* iterador = malloc(1 * sizeof(lista_iterador_t));
	if (!iterador) {
		return NULL;
	}

	iterador->lista = lista;
	iterador->corriente = lista->nodo_inicio;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador) {
	if (!iterador->corriente) {
		return false;
	}

	return true;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador) {
	if (!iterador->corriente) {
		return false;
	}

	if (!iterador->corriente->siguiente) {
		iterador->corriente = iterador->corriente->siguiente;
		return false;
	}

	iterador->corriente = iterador->corriente->siguiente;

	return true;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador) {
	if (!iterador->corriente) {
		return NULL;
	}

	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador) {
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto) {
	if (!lista) {
		return 0;
	}

	if (funcion == NULL) {
		return 0;
	}

	nodo_t* nodo_actual = lista->nodo_inicio;
	if (!nodo_actual) {
		return 0;
	}

	bool seguir_iterando = true;
	size_t elementos_iterados = 0;

	seguir_iterando = funcion(nodo_actual->elemento, contexto);
	elementos_iterados++;

	while ((nodo_actual->siguiente != NULL) && (seguir_iterando == true)) {
		nodo_actual = nodo_actual->siguiente;
		seguir_iterando = funcion(nodo_actual->elemento, contexto);
		elementos_iterados++;
	}

	return elementos_iterados;
}