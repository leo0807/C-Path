#include <stdio.h>
#define NODE_POOL_CAP 1024
typedef struct Node Node;

struct Node
{
  char text[32];
  Node *left;
  Node *right;
};

Node node_pool[NODE_POOL_CAP];
