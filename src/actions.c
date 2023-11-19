#include "actions.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

static var_node* variable_table;

/**
 * Function returns node that corresponds to the variable with the specific name.
 * 
 * @param name Name of the variable
*/
var_node* get_var_node(const char* name) {
    var_node* tmp = variable_table;

    while(tmp != NULL) {
        if(strcmp(tmp->name, name) == 0) {
            break;
        }
        tmp = tmp->next;
    }

    return tmp;
}

/**
 * Function creates node of the variable. 
 * 
 * @param name Name of the variable
 * @param value Value that variable contains
*/
var_node* create_var_node(const char* name, double value) {
    var_node* new_node = malloc(sizeof(var_node));
    new_node->name = name;
    new_node->value = value;

    return new_node;
}

/**
 * Function adds variable to the table of variables.
 * 
 * @param name
 * @param value
*/
void append_var_node(const char* name, double value)
{
    var_node* found = get_var_node(name);
    if(found != NULL) {
        found->value = value;
        return;
    }

    found = create_var_node(name, value);
    found->next = variable_table;
    variable_table = found;
}

/**
 * Function creates the table of variables
*/
void init_variable_table() {
    variable_table = create_var_node("\r", 0);
    variable_table->next = NULL;
}

/**
 * Function calculates the unary functions. Function supports log|sin|cos|tan|abs
 * 
 * @param func Name of the function
 * @param val Value on which need to execute function
 * @param res Variable in which to contain the result
*/
int process_unary_function(const char* func, double val, double* res) 
{
    double result = 0;

    if(strcmp(func, "log") == 0) {
        if(val < 0) {
            printf("Non positive number to logarithm - %f", val);
            return 0;
        }
        result = log(val);
    } 
    else if(strcmp(func, "sin") == 0) {
        result = sin(val);
    }
    else if(strcmp(func, "cos") == 0) {
        result = cos(val);
    }
    else if(strcmp(func, "tan") == 0) {
        result = tan(val);
    } 
    else if(strcmp(func, "abs") == 0) {
        result = val < 0 ? -val : val;
    }

    (*res) = result;
    return 1;
}