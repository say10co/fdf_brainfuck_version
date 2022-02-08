#include "includes.h"

void	drwo_line(int x, int y, t_wdata *d, int color)
{
	mlx_pixel_put(d->mlx_ptr, d->win_ptr, x, y, color);
}

unsigned int	my_abs(int x)
{
	if (x < 0)
		return(-x);
	return(x);
}

void	DDA_calcuation(t_wdata *d, int color)
{
	t_dda	vars;
	int	k;
	
	k = 0;
	vars.x = d->x0;
	vars.y = d->y0;
		
	vars.dx = d->xe - d->x0;
	vars.dy = d->ye - d->y0;
	if (my_abs(vars.dx) > my_abs(vars.dy))
		vars.slop = my_abs(vars.dx);	
	else
		vars.slop = my_abs(vars.dy);

	if (vars.dy == 0)
		vars.xscale = 1;
	else if (vars.dx == 0)
		vars.yscale = 1;
	else
	{
		vars.yscale = (float ) ((vars.dy)) / vars.slop;
		vars.xscale = (float ) ((vars.dx)) / vars.slop;
	}
	while (k++ < vars.slop)
	{
		//printf("%f %f\n", vars.x, vars.y);
		drwo_line(round(vars.x), round(vars.y), d, color);
		drwo_line(round(vars.y), round(vars.x), d, color);
		vars.x += vars.xscale;
		vars.y += vars.yscale;

		if (vars.x > d->xe || vars.y > d->ye)
			break;
	}
}

int	main(int ac, char **av)
{
	t_wdata d;

	(void)ac;
	d.mlx_ptr = mlx_init();
	d.win_ptr = mlx_new_window(d.mlx_ptr, 900, 800, "mine");
	parse_send_line(av[1], &d);
	mlx_loop(d.mlx_ptr);
}
