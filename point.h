#if !defined(_POINT_H_)
#define _POINT_H_

typedef struct Point Point;

Point *point_construct(char *id, int size);
Point *point_read(int size, char *line);
void point_destroy(Point *p);
void point_print(Point *p);

#endif // _POINT_H_
