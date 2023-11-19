struct var_node
{
    const char* name;
    double value;
    struct var_node
* next;
};

typedef struct var_node var_node;

var_node* get_var_node(const char* name);
var_node* create_var_node(const char* name, double value);
void append_var_node(const char* name, double value);
void init_variable_table();
int process_unary_function(const char* func, double val, double* res);