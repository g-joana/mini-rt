cc -Wall -Wextra -Iincludes -Ilibft -Imlx -Itrivec -ggdb3 -c src/main.c -o obj/main.o
src/main.c: In function ‘main’:
src/main.c:13:31: error: passing argument 2 of ‘mlx_loop_hook’ from incompatible pointer type [-Wincompatible-pointer-types]
   13 |     mlx_loop_hook(scene->mlx, render, scene);
      |                               ^~~~~~
      |                               |
      |                               int (*)(t_scene *) {aka int (*)(struct s_scene *)}
In file included from src/../includes/minirt.h:5,
                 from src/main.c:1:
src/../includes/../mlx/mlx.h:88:45: note: expected ‘int (*)(void)’ but argument is of type ‘int (*)(t_scene *)’ {aka ‘int (*)(struct s_scene *)’}
   88 | int     mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param);
      |                                       ~~~~~~^~~~~~~~~~~~
src/../includes/minirt.h:141:8: note: ‘render’ declared here
  141 | int    render(t_scene *scene);
      |        ^~~~~~



# Arch linux: mudar o compilador para clang e -std=gnu11 nos 2 makefiles da mlx
