#ifndef INCLUDES_H
# define INCLUDES_H


# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>

# define BUFFER_SIZE 1
typedef struct s_cordinates
{
    int x0;
    int y0;
    int xE;
    int yE;
    int z;
    int color;
}t_cordinates;

typedef struct s_dda
{
	int		dx;
	int		dy;
	int		slop;
	float	xscale;
	float	yscale;
}t_dda;

typedef struct s_info
{
	void    *mlx_ptr;
	void    *win_ptr;

}t_info;
	
#endif
