#define SIZE 100

typedef struct node
{
    const char* name;
    double value;
    struct node* child_nodes[SIZE];
} node;

node* create_node(const char* name);
node* create_node_value(const char* name, double value);
node* create_node_list_unary(const char* name, node* one, node* two);
node* create_node_list_binary(const char* name, node* one, node* two, node* three);

void append_node(node* main_node, node* sub_node);
void print_node_tree(node* node, char* ind, int is_last);
void print_syntax_tree(node* node);