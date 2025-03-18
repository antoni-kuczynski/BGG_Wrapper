#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_graph(const char *filename, int vertices, int edges) {
    if (vertices <= 0 || edges < 0) {
        printf("Invalid number of vertices or edges.\n");
        return;
    }

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "new -f\n");
    for (int i = 0; i < vertices; i++) {
        fprintf(file, "add\n");
    }

    srand(time(NULL));
    for (int i = 0; i < edges; i++) {
        int a = rand() % vertices;
        int b = rand() % vertices;
        fprintf(file, "arch add %d %d\n", a, b);
    }

    fclose(file);
    printf("Graph script saved to %s\n", filename);
}

int main() {
    int vertices, edges;
    char filename[256];

    printf("Enter output filename: ");
    scanf("%255s", filename);
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    generate_graph(filename, vertices, edges);
    return 0;
}