#ifndef TEMPLATES_H
#define TEMPLATES_H

#define CAT(X,Y) X##_##Y
#define TEMPLATE(FNAME, X) CAT(FNAME,Y)
#define TEMPLATE2(FNAME, X, Y) CAT(FNAME, CAT(X, Y))
#define TEMPLATE3(FNAME, X, Y, Z) CAT(FNAME, CAT(X, CAT(Y, Z)))

int map_compare_func_pointer_eq(const void* a, const void* b)
{
    return a == b;
}

void map_release_func_free(const void* a) 
{
    free(a);
}

#endif