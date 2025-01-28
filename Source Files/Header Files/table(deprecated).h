/*
In this header, the basic definitions of the table type are present. The table type allows the
creation of data tables, which can contain line of different, varied other types.

A table is an array of lines,
a line is a linked list of nodes,
and a node is a value with a pointer to the next element of the line.

Creation and management of tables requires carefulness, as there are no functions allowing for 
non type-specific management of nodes nor is there a method allowing one to set a whole line (row)
at once.
*/

/* It is greatly advised not to access the structs and manage them directly, rather only through the functions declared here - Assaf (note for my partner) */

/** POINTER TO NEXT ELEMENT OF LINE **/

typedef union{

	/*union used for pointing to any of the defined node types*/
	table_int_node *int_ptr;
	table_char_node *char_ptr;
	table_str_node *str_ptr;
	table_table_node *table_ptr;

} table_node_ptr_union;

enum table_node_type{

	/*enum used to determine what is the type of node the above union points to*/
	Integer,
	Character,
	String,
	Table

};

typedef struct{

	/*struct for generalized access to any node type*/
	table_node_ptr_union node_ptr;
	enum table_node_type node_type;

} table_node_ptr;

/**
 * Function used to access data of a data table node, regardless of its type.
 * @param node the node pointer struct, from the node referred in which the value will be taken.
 * @return pointer to the value found in the node, of void type (it is strictly necessary to verify the type of pointer with a cast attempt before use).
*/
void *get_node_value_ptr(table_node_ptr node);

/** NODE TYPES **/
typedef struct{

	int value;
	table_node_ptr next;

} table_int_node;

typedef struct{

	char value;
	table_node_ptr next;

} table_char_node;

typedef struct{

	char *value;
	table_node_ptr next;

} table_str_node;

typedef struct{

	data_table *value;
	table_node_ptr next;

} table_table_node;

/** LINE TYPE **/

typedef struct{

	table_node_ptr first;
	int argument_count;

} data_table_line;

data_table_line build_line(char *node_formats);

table_node_ptr get_node_ptr(data_table_line line, int index);

void free_line(data_table_line);

/** TABLE TYPE **/

typedef struct{

	data_table_line model_line;
	data_table_line *line_array;
	int line_count;

} data_table;

data_table build_data_table(data_table_line base_line, int line_count);

data_table build_data_table(char *node_formats, int line_count);

table_node_ptr get_node_ptr(data_table table, int line, int index);

void free_table(data_table table);