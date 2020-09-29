#pragma once
#include <iostream>

#include "CProgramShader.h"

//Creamos un strcut que representa el objeto 3d que contiene vertices y mallas triangulares. 
typedef struct Surface {
	GLfloat* vertices; //informacon de los Vertices de la geometria(VAO)
	GLushort* triangles; //informacion de los triangulos(EBO)
	int numVertices; //Numero de vertices
	int numTriangles; //Numero de triangulos

	GLuint id_vbo; //identidad de vertex buffer object
	GLuint id_ebo; //identidad del elemnt buffer object
	glm::mat4 model; //tipo de dato mat4

}TSurface;



float xmin = 1e09, xmax = -1e09, ymin = 1e09, ymax = -1e09, zmin = 1e09, zmax = -1e09;



//funcion para leer un archivo off
void Leer_Archivo(const char * nombreArchivo, TSurface * T) {
	FILE * archivo = fopen(nombreArchivo, "rt");
	char buffer[100];

	//leemos la cabezera OFF

	fscanf(archivo, "%s", buffer);
	int aux;

	//leemos numero de vertices ,aristas y  triangulos
	fscanf(archivo, "%d %d %d", &T->numVertices, &T->numTriangles, &aux);

	T->vertices = new GLfloat[T->numVertices * 3];
	T->triangles = new GLushort[T->numTriangles * 3];

	for (int i = 0; i < T->numVertices; i++) {

		GLfloat x, y, z;

		fscanf(archivo, "%f %f %f", &x, &y, &z);

		if (x < xmin)	xmin = x;
		if (x > xmax)	xmax = x;
		if (y < ymin)	ymin = y;
		if (y > ymax)	ymax = y;
		if (z < zmin)	zmin = z;
		if (z > zmax)	zmax = z;

		T->vertices[3 * i] = x;
		T->vertices[3 * i + 1] = y;
		T->vertices[3 * i + 2] = z;

	}

	for (int i = 0; i < T->numTriangles; i++) {

		fscanf(archivo, "%d %d %d", &aux, &T->triangles[3 * i], &T->triangles[3 * i + 1], &T->triangles[3 * i + 2]);
	}

	fclose(archivo);
}