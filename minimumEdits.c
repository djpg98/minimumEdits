#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minimumEdits.h"

/* Si se tiene una matriz guardada como un arreglo 2D ordenado por filas, dado el número de columnas y las coordenadas
de un elemento, calcula el índice que ocupa elelemento en ese arreglo */
int getMatrixIndex(int ncolumns, int row, int column){
    return ncolumns * row + column;
}

/* Dados 3 valores enteros calcula el menor de ellos */
int minValue(int value1, int value2, int value3){
    int min;

    if (value1 <= value2){
        min = value1;
    } else{
        min = value2;
    }

    if (min > value3){
        min = value3;
    }

    return min;
}

/* Dados tres valores enteros de la matriz adyacentes a un elemento dado, indica cual es el tipo de modificación que hay que
hacer al string. Asume que value1 es el valor de las coordenadas (i, j - 1), value2 el de las coordenadas (i - 1, j - 1) 
y value3 el de la casilla (i - 1, j), ya que estas representan las operaciones de agregar, intercambiar y eliminar en ese 
orden y ese es el orden en que la función revisa cual operación es la de menor costo. ES decir: NO FUNCIONA SI NO PASAS LOS
ELEMENTOS EN ESE ORDEN */
int typeOfEdit(int value1, int value2, int value3){
    int min, editType;

    if (value1 <= value2){
        min = value1;
        editType = AGREGAR;
    } else{
        min = value2;
        editType = INTERCAMBIAR;
    }

    if (min > value3){
        min = value3;
        editType = ELIMINAR;
    }

    return editType;
}

/* Resolución DP del problema de minimum edits */
int * minimumEdits(char * str1, char * str2){
    int * edits; //MAtriz guardada por filas
    int rows, cols, minEdit;;
    
    //El número de fila representa la cantidad de caracteres que estamos tomando del str1, partiendo desde el string vacío
    //El número de columna tienen función análoga para str2
    //Como estamos tomando en cuenta el string "" para los cálculos, el número de filas y de columnas aumenta en 1 respecto
    //a la longitud de str1 y str2 respectivamente
    rows = strlen(str1) + 1;
    cols = strlen(str2) + 1;

    edits = (int *)malloc(rows * cols * sizeof(int));

    for (int j = 0; j < cols; j++){
        edits[getMatrixIndex(cols, 0, j)] = j;
    }

    for(int i = 0; i < rows; i++){
        edits[getMatrixIndex(cols, i, 0)] = i;
    }

    for(int i = 1; i < rows; i++){
        for(int j = 1; j < cols; j++){
            //Ese - 1 hace falta porque hay que recordar que para efectos de la matriz, los strings están indexados desde 1
            //Pero en realidad están indexados desde 0
            if (str1[i - 1] == str2[j - 1]){
                edits[getMatrixIndex(cols, i, j)] = edits[getMatrixIndex(cols, i -1, j -1)];
            } else {
                minEdit = minValue(edits[getMatrixIndex(cols, i, j - 1)], edits[getMatrixIndex(cols, i -1, j -1)], edits[getMatrixIndex(cols, i -1, j)]) + 1;
                edits[getMatrixIndex(cols, i, j)] = minEdit;
            }
        }
    }

    return edits;
}

/*Imprime el número de edits que hay que aplicarle al str1 y llama a la función que explica los edits que hay que hacer*/
void returnSolution(int * edits, char * str1, char * str2){
    int cols;

    cols = strlen(str2) + 1;
    printf("El numero de minimo de ediciones que hay que hacer es: %d\n",  edits[getMatrixIndex(cols, strlen(str1), strlen(str2))]);
    viewEdits(edits, str1, str2, cols, strlen(str1), strlen(str2));
}

/*Imprime los edits que hay que hacer tal que se haga el menor número de ediciones posibles. Es case sensitive*/
void viewEdits(int * edits, char * str1, char * str2, int cols, int rowIndex, int colIndex){
    int editType;

    if(rowIndex == 0 && colIndex == 0){
        return;
    } else if (rowIndex == 0){
        viewEdits(edits, str1, str2, cols, rowIndex, colIndex - 1);
        printf("Agregar %c\n", str2[colIndex - 1]);
        return;
    } else if (colIndex == 0) {
        viewEdits(edits, str1, str2, cols, rowIndex - 1, colIndex);
        printf("Eliminar %c\n", str1[rowIndex - 1]); 
        return;
    }

    if (str1[rowIndex - 1] == str2[colIndex - 1]){
        viewEdits(edits, str1, str2, cols, rowIndex - 1, colIndex - 1);
    } else {
        editType = typeOfEdit(edits[getMatrixIndex(cols, rowIndex, colIndex - 1)], edits[getMatrixIndex(cols, rowIndex -1, colIndex -1)], edits[getMatrixIndex(cols, rowIndex -1, colIndex)]);

        switch (editType){
            case AGREGAR:
                viewEdits(edits, str1, str2, cols, rowIndex, colIndex - 1);
                printf("Agregar %c\n", str2[colIndex - 1]);
                break;
            case INTERCAMBIAR:
                viewEdits(edits, str1, str2, cols, rowIndex - 1, colIndex - 1);
                printf("Intercambiar %c por %c\n", str1[rowIndex - 1], str2[colIndex - 1]);
                break;
            case ELIMINAR:
                viewEdits(edits, str1, str2, cols, rowIndex - 1, colIndex);
                printf("Eliminar %c\n", str1[rowIndex - 1]);
                break;
            default:
                printf("Error inesperado\n");
                break;
        }
    }

    return;
}