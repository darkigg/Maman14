
/* definition of the first word structure*/
struct as_first_word{

	unsigned int opcode : 6;
	unsigned int origin_address : 2;
	unsigned int origin_register : 3;
	unsigned int destination_address : 2;
	unsigned int destination_register : 3;
	unsigned int funct : 6;
	unsigned int A : 1;
	unsigned int R : 1;
	unsigned int E : 1;

};

typedef struct as_first_word startword; /*startword is a struct used to represent the first word of an instruction*/