#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * Creates node of a tree.
 * 
 * @param name Name of the node
*/
node* create_node(const char* name) {
    node* new_node = malloc(sizeof(node));
    for(int i = 0; i < SIZE; i++) {
        new_node->child_nodes[i] = NULL;
    }

    new_node->name = name;

    return new_node;
}

/**
 * Creates specific node, that contains some value.
 * 
 * @param name Name of the node.
 * @param value Value of the node.
*/
node* create_node_value(const char* name, double value) {
    node* new_node = create_node(name);
    new_node->value = value;
    return new_node;
}

/**
 * Appends node to the other node.
 * 
 * @param parent_node Node to which we are appending.
 * @param child_node Node which is being appended.
*/
void append_node(node* parent_node, node* child_node)
{
    int i = 0;
    while (parent_node->child_nodes[i] != NULL)
    {
        i++;
    }

    parent_node->child_nodes[i] = child_node;
}

/*
 * Sometimes it is feasible to use functions which make node with 3 or two child at once.
 * Such a function can be used when we are trying to add binary or unary expression. 
*/

/**
 * Function creates a new node, and accepts three childs.
*/
node* create_node_list_binary(const char* name, node* one, node* two, node* three) 
{
    node* new_node = create_node(name);
    append_node(new_node, one);
    append_node(new_node, two);
    append_node(new_node, three);

    return new_node;
}

/**
 * Function creates a new node, and accepts two childs.
*/
node* create_node_list_unary(const char* name, node* one, node* two) 
{
    node* new_node = create_node(name);
    append_node(new_node, one);
    append_node(new_node, two);

    return new_node;
}

/**
 * Function recursively prints current node and all its child nodes.
*/
void print_node_tree(node* node, char* ind, int is_last) 
{
    char *indent = strdup(ind);
    int ch = 0;
    printf("%s", indent);

    if(is_last) {
        printf("+");
        strcat(indent, "   ");
    } else {
        printf("|_");
        strcat(indent, "|  ");
    }

    printf(" %s\n", node->name);

    ch = 0;
    while (node->child_nodes[ch] != NULL)
    {
        print_node_tree(node->child_nodes[ch], indent, node->child_nodes[ch+1] == NULL);
        ch++;
    }
}

/**
 * Wrapper around "print_node_tree" to print tree.
*/
void print_syntax_tree(node* node) 
{
    printf("\n");
    char indent[100];
    indent[0] = 0;
    print_node_tree(node, indent, 1);
}


