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

    fprintf(file, "list");
    fclose(file);
    printf("Graph script saved to %s\n", filename);
}

void input_custom_graph(const char *filename, int vertices, int edges) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "new -f\n");
    for (int i = 0; i < vertices; i++) {
        fprintf(file, "add\n");
    }

    printf("Enter %d edges in format: vertex1 vertex2\n", edges);
    for (int i = 0; i < edges; i++) {
        int a, b;
        printf("Edge %d: ", i + 1);
        scanf("%d %d", &a, &b);
        fprintf(file, "arch add %d %d\n", a, b);
    }

    fprintf(file, "list");
    fclose(file);
    printf("Custom graph script saved to %s\n", filename);
}

int main() {
    int vertices, edges, mode;
    char filename[256];

    printf("Enter output filename: ");
    scanf("%255s", filename);
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Select mode (1 - Random Graph, 2 - Custom Graph): ");
    scanf("%d", &mode);

    if (mode == 1) {
        generate_graph(filename, vertices, edges);
    } else if (mode == 2) {
        input_custom_graph(filename, vertices, edges);
    } else {
        printf("Invalid mode selected.\n");
    }

    return 0;
}
