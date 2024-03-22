#if !defined(_CARTESIAN_PLANE_H_)
#define _CARTESIAN_PLANE_H_

typedef struct CartesianPlane CartesianPlane;

CartesianPlane *cartesian_plane_construct();
void cartesian_plane_destroy(CartesianPlane *cp);
void cartesian_plane_read(CartesianPlane *cp, FILE *input);
void cartesian_plane_calculate_distances(CartesianPlane *cp);
void cartesian_plane_print_distances(CartesianPlane *cp);

#endif // _CARTESIAN_PLANE_H_
