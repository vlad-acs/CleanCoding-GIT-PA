// parcurgerge graf cu DFS/BFS

// M: Imi cer scuze in avans
// V: Implementarea cozii e teribil de ineficienta, dar in rest formatarea a fost ok.
// V: Cere-ti scuze pentru cealalta!

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int key;
    struct node *next;
} NODE;

typedef struct graph
{
    int vertices;
    int *visited;
    NODE **adjacency_lists;
} GRAPH;

// utils

NODE* create_node(int key)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

GRAPH* create_graph(int vertices)
{
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->vertices = vertices;

    graph->adjacency_lists = malloc((vertices+1) * sizeof(NODE*));
    graph->visited = malloc((vertices+1) * sizeof(int));
    for (int i = 1; i <= vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(GRAPH *graph, int src, int dest)
{
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(int nr_of_edges, GRAPH *graph)
{
    printf("adauga %d muchii (de la 1 la %d)\n", nr_of_edges, graph->vertices);
    for (int i = 0; i < nr_of_edges; i++)
    {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

// bfs utils

int is_empty(NODE *queue)
{
    return queue == NULL;
}

void enqueue(NODE **queue, int key)
{
    NODE *new_node = create_node(key);

    if (is_empty(*queue))
    {
        *queue = new_node;
    }
    else
    {
        NODE *temp = *queue;
        while (temp->next != NULL) // the horror
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue)
{
    int key = (*queue)->key;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return key;
}

void print_queue(NODE *queue)
{
    for (NODE *current = queue; current != NULL; current = current->next)
    {
        printf("%d ", current->key);
    }
}

void print_graph(GRAPH *graph)
{
    for (int i = 1; i <= graph->vertices; i++)
    {
        printf("%d -> ", i);
        print_queue(graph->adjacency_lists[i]);
        printf("\n");
    }
}

void wipe_visited_list(GRAPH *graph)
{
    for (int i = 1; i <= graph->vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

//parcurgeri

void DFS(GRAPH *graph, int vertex_nr)
{
    graph->visited[vertex_nr] = 1;
    printf("%d ", vertex_nr);

    for (NODE *adj_list = graph->adjacency_lists[vertex_nr]; adj_list != NULL; adj_list = adj_list->next)
    {
        int connected_vertex = adj_list->key;
        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
    }
}

void BFS(GRAPH *graph, int start)
{
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        for (NODE *cursor = graph->adjacency_lists[current]; cursor != NULL; cursor = cursor->next)
        {
            int adj_vertex = cursor->key;
            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
        }
    }
}

int main()
{
    int nr_of_vertices, nr_of_edges, starting_vertex;

    printf("cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);
    
    printf("cate muchii are graful? ");
    scanf("%d", &nr_of_edges);
    
    GRAPH *graph = create_graph(nr_of_vertices);
    insert_edges(nr_of_edges, graph);
    print_graph(graph);
    
    printf("de unde plecam in DFS? ");
    scanf("%d", &starting_vertex); // =)))
    
    printf("parcurgere cu DFS: ");
    DFS(graph, starting_vertex);
    
    wipe_visited_list(graph);
    printf("\n");
    
    printf("de unde plecam in BFS? ");
    scanf("%d", &starting_vertex);
    
    printf("parcurgere cu BFS: ");
    BFS(graph, starting_vertex);

    //  /\_/\  
    // ( o.o ) 
    //  > ^ <

    return 0;
}