#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    fprintf(file, "list\n");
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
        if (a >= vertices || b >= vertices) {
            printf("Warning: Invalid edge (%d, %d) - One or both vertices do not exist.\n", a, b);
            continue;
        }
        fprintf(file, "arch add %d %d\n", a, b);
    }

    fprintf(file, "list\n");
    fclose(file);
    printf("Custom graph script saved to %s\n", filename);
}

int validate_script(const char *filename, int expected_vertices, int expected_edges, int compare) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file for validation");
        return 0;
    }

    char line[256];
    int vertex_count = 0, edge_count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "add", 3) == 0) {
            vertex_count++;
        } else if (strncmp(line, "arch add", 8) == 0) {
            int a, b;
            if (sscanf(line, "arch add %d %d", &a, &b) == 2) {
                if (a >= vertex_count || b >= vertex_count) {
                    printf("Invalid edge (%d, %d) - One or both vertices do not exist\n", a, b);
                } else {
                    edge_count++;
                }
            }
        } else if (strncmp(line, "del", 3) == 0) {
            vertex_count--;
        } else if (strncmp(line, "arch del", 8) == 0) {
            edge_count--;
        }
    }

    fclose(file);

    if (vertex_count < 0)
        vertex_count = 0;

    if (edge_count < 0)
        edge_count = 0;

    printf("Validation result: %d vertices, %d edges\n", vertex_count, edge_count);

    if (compare) {
        if (vertex_count != expected_vertices || edge_count != expected_edges) {
            printf("Mismatch: Expected %d vertices and %d edges\n", expected_vertices, expected_edges);
        } else {
            printf("Validation successful: Graph matches expected values\n");
        }
    }

    return 1;
}

int main() {
    int vertices, edges, mode, compare = 0;
    char filename[256];

    printf("Select mode (1 - Random Graph, 2 - Custom Graph, 3 - Validate Script): ");
    scanf("%d", &mode);

    if (mode == 1 || mode == 2) {
        printf("Enter number of vertices: ");
        scanf("%d", &vertices);
        printf("Enter number of edges: ");
        scanf("%d", &edges);
        strcpy(filename, "graph.gr");

        if (mode == 1) {
            generate_graph(filename, vertices, edges);
        } else {
            input_custom_graph(filename, vertices, edges);
        }

        validate_script(filename, vertices, edges, 1);
    } else if (mode == 3) {
        printf("Enter script filename to validate: ");
        scanf("%s", filename);
        printf("Do you want to compare with expected values? (1 - Yes, 0 - No): ");
        scanf("%d", &compare);
        if (compare) {
            printf("Enter expected number of vertices: ");
            scanf("%d", &vertices);
            printf("Enter expected number of edges: ");
            scanf("%d", &edges);
        }
        validate_script(filename, vertices, edges, compare);
    } else {
        printf("Invalid mode\n");
        return -1;
    }

    return 0;
}