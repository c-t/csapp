#ifndef STACKVIZ_H
#define STACKVIZ_H

#include <stddef.h>

typedef struct
{
	const char *name;
	ptrdiff_t offset;
	size_t size;
	const char *type_name;
} stackviz_var_t;

void stackviz_dump();
void stackviz_dump_vars(void *frame_base, const stackviz_var_t *vars, size_t count);

#endif
