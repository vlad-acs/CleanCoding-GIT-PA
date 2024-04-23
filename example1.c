// Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf

#include <stdlib.h>
#include <stdio.h>

// pentru simplitate, folosim int-uri pt a numi restaurantel/locatiile
// ex: 1 - restaurantul 1 si tot asa

typedef struct node
{
    int key;
    struct node *next;
} NODE;

typedef struct graph
{
    int size;
    int *visited;
    NODE **adjacencyList;
} GRAPH;

typedef struct stack
{
    int top;
    int size;
    int *array;
} STACK;

STACK* create_stack(int size)
{
    STACK *s = malloc(sizeof(STACK));
    s->array = malloc(size * sizeof(int));
    s->top = 0;
    s->size = size;
    return s;
}

void push(int node, STACK *stack)
{
    stack->array[stack->top] = node;
    stack->top++;
}

NODE* create_node(int key)
{
    NODE *newNode = malloc(sizeof(NODE));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

GRAPH* create_graph(int size)
{
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->size = size;
    graph->adjacencyList = malloc((size+1) * sizeof(NODE*));
    graph->visited = malloc((size+1) * sizeof(int));

    for (int i = 1; i <= size; i++)
    {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(GRAPH* graph, int src, int dest)
{
    NODE *newNode = create_node(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    newNode = create_node(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

void insert_edges(GRAPH *graph, int edgeCount, int nodeCount)
{
    printf("adauga %d munchii (de la 1 la %d)\n", edgeCount, nodeCount);

    for (int i = 0; i < edgeCount; i++)
    {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void wipe_visited(GRAPH *graph)
{
    printf("\n");
    for (int i = 1; i <= graph->size; i++)
    {
        graph->visited[i] = 0;
    }
}

void DFS(GRAPH *graph, STACK *stack, int node)
{
    graph->visited[node] = 1;
    printf("%d ", node);
    push(node, stack);
    
    for (NODE *currentNode = graph->adjacencyList[node]; currentNode != NULL; currentNode = currentNode->next)
    {
        int newNode = currentNode->key;
        if (graph->visited[newNode] == 0)
        {
            DFS(graph, stack, newNode);
        }
    }
}

void can_be_reached(GRAPH *graph) // 0 sau 1 daca poate fi sau nu ajuns
{
    int nodeCount = graph->size;
    STACK *stack1 = create_stack(2 * nodeCount);
    STACK *stack2 = create_stack(2 * nodeCount);
    
    for (int i = 1; i < nodeCount; i++) // aici i tine loc de numar adica de restaurant {for (int j = 0; j < 5; j++)}
    {
        DFS(graph, stack1, i);
        wipe_visited(graph);
        
        for (int j = i+1; j <= nodeCount; j++)
        {
            DFS(graph, stack2, j);
            wipe_visited(graph);

            // Burn it all
            int ans = 0;
            for (int k = 0; k < stack1->top && !ans; k++)
            {
                for (int l = 0; l < stack2->top && !ans; l++)
                {
                    if (stack1->array[k] == stack2->array[l])
                    {
                        ans = 1;
                        printf("Exista drum intre %d si %d\n", i, j);
                    }
                }
            }
        }
    }
}

int main()
{
    int nodeCount, edgeCount;

    printf("Cate noduri are graful?\n");
    scanf("%d", &nodeCount);
    printf("Cate muchii are giraful?\n");
    scanf("%d", &edgeCount);

    GRAPH *graph = create_graph(nodeCount);
    insert_edges(graph, edgeCount, nodeCount);

    can_be_reached(graph);
    return 0;
}