#include "../Header Files/assemblerErrorHandling.h"

assemblerErrorType is_label_def_valid( const char *label ){

	/* if the label name doesn't start with a letter, the name is illegal */
	if(IS_LETTER(label[0])) return ILLEGAL_LABEL_NAME;

	/* if the label name overlaps with a language word, it is illegal */
	if(is_language_word(label)) return ILLEGAL_LABEL_NAME;

	/* (to be added) if the label name overlaps with a macro name, it is illegal */

	/* (to be added) if a label by the same name has already been declared, it is illegal */

}