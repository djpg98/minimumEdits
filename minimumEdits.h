#define AGREGAR 0
#define INTERCAMBIAR 1
#define ELIMINAR 2

/* Si se tiene una matriz guardada como un arreglo 2D ordenado por filas, dado el número de columnas y las coordenadas
de un elemento, calcula el índice que ocupa elelemento en ese arreglo */
int getMatrixIndex(int ncolumns, int row, int column);

/* Dados 3 valores enteros calcula el menor de ellos */
int minValue(int value1, int value2, int value3);

/* Dados tres valores enteros de la matriz adyacentes a un elemento dado, indica cual es el tipo de modificación que hay que
hacer al string. Asume que value1 es el valor de las coordenadas (i, j - 1), value2 el de las coordenadas (i - 1, j - 1) 
y value3 el de la casilla (i - 1, j), ya que estas representan las operaciones de agregar, intercambiar y eliminar en ese 
orden y ese es el orden en que la función revisa cual operación es la de menor costo. ES decir: NO FUNCIONA SI NO PASAS LOS
ELEMENTOS EN ESE ORDEN */
int typeOfEdit(int value1, int value2, int value3);

/* Resolución DP del problema de minimum edits */
int * minimumEdits(char * str1, char * str2);

/*Imprime el número de edits que hay que aplicarle al str1 y llama a la función que explica los edits que hay que hacer*/
void returnSolution(int * edits, char * str1, char * str2);

/*Imprime los edits que hay que hacer tal que se haga el menor número de ediciones posibles*/
void viewEdits(int * edits, char * str1, char * str2, int cols, int rowIndex, int colIndex);