#if !defined(_CARTESIAN_PLANE_H_)
#define _CARTESIAN_PLANE_H_

#include "point.h"
typedef struct CartesianPlane CartesianPlane;

CartesianPlane *cartesian_plane_construct();
void cartesian_plane_destroy(CartesianPlane *cp);
void cartesian_plane_read(CartesianPlane *cp, char *input_file);
int cartesian_plane_get_number_points(CartesianPlane *cp);
Point *cartesian_plane_get_point(CartesianPlane *cp, int i);
int cartesian_plane_get_dimension(CartesianPlane *cp);

#endif // _CARTESIAN_PLANE_H_
