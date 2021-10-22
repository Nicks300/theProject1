#include <stdio.h>
#include <stdlib.h>

void drawGraph(FILE* fname, int** mas, int size);
void verifyGraph(int** mas, int size);
void freeMemory(char* mas);


int main(void) {
	int width;
	printf("Enter the dimension: ");
	scanf("%d", &width);


	printf("\nEnter the rows of your matrix! Press 'SPACE' to change column and 'ENTER' to change row\n");

	getchar();


	int** mas = NULL;
	mas = (int**)malloc(sizeof(*mas) * width);
	for (int i = 0; i < width; i++) {
		mas[i] = (int*)malloc(sizeof(**mas) * width);
	}

	char* s, c;
	s = (char*)malloc(sizeof(char));


	for (int i = 0, m = 1, j = 0; j < width; j++) {

		while ((c = getchar()) != '\n') {

			if (c < '0' && c > '9' && c != ' ') {
				printf("ERROR: the entered values is wrong!\n");
				return -1;
			}

			if (c != ' ') {
				s[m - 1] = c;

				s = (char*)realloc(s, sizeof(char) * (++m));
			}

			else {
				s[m - 1] = '\0';

				if (i >= width) {
					printf("ERROR: numders that you entered more than entered width!\n ");
					return -1;
				}

				mas[i][j] = atoi(s);
				i++;
				m = 1;

				freeMemory(s);

			}

		}

		s[m - 1] = '\0';

		if (i >= width) {
			printf("ERROR: numders that you entered more than entered width!\n ");
			return -1;
		}

		mas[i][j] = atoi(s);

		if (i < width) {
			++i;
			while (i < width)
				mas[i++][j] = 0;
		}

		i = 0;
		m = 1;

		freeMemory(s);
	}

	free(s);
	s = NULL;



	FILE* foo;
	foo = fopen("graph.gv", "w");

	if (foo!= NULL) {

	drawGraph(foo, mas, width);

	verifyGraph(mas, width);


	for (int i = 0; i < width; i++)
		free(mas[i]);
	free(mas);
	mas = NULL;
 }
	return 0;
}



void drawGraph(FILE* fname, int** mas, int size)
{
	fprintf(fname, "graph G{\n");

	for (int j = 0; j < size; j++) {
		for (int i = j; i < size; i++)
			for (int k = 0; k < mas[i][j]; k++)
				fprintf(fname, "%d -- %d;\n", j+1, i+1);
	}
	fprintf(fname, "}");

	fclose(fname);
}

void verifyGraph(int** mas, int size) {

	for (int i, j = 0; j < size; j++) {
		i = j;
		if (mas[i][j] != 0) {
			printf("The entered graph is not simple cycle");
			return;
		}
	}

	for (int j = 0; j < size; j++)
		for (int i = 0; i < size; i++) {
			if (mas[i][j] > 1) {
				printf("The entered graph is not simple cycle.\n");
				return;
			}
		}

	printf("The entered graph is simple cycle.\n");
}

void freeMemory(char* mas) {
	free(mas);
	mas = NULL;
	mas = (char*)malloc(sizeof(char));
}


