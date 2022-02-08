#include "includes.h"
/*
typedef struct s_cordinates
{
	int	x0;
	int	y0;
	int	xE;
	int	yE;
	int	z;
	int	color;
}t_cordinates;
*/
unsigned int	my_abs(int x)
{
	if (x < 0)
		return(-x);
	return(x);
}
int	count_elements_(char	**table)
{
	int	i;

	i = 0;
	while(table[i])
		i++;
	return (i);
}

int	*parser_h(char *line, int	*nb_elements)
{
	int		index;
	int		*int_data;
	char	**splited_line;

	splited_line = ft_split(line, ' ');
	*nb_elements = count_elements_(splited_line);
	int_data = (int *)(malloc(sizeof(int) * (*nb_elements)));
	ft_bzero(int_data, sizeof(int) * (*nb_elements));
	index = 0;
	while (index < *nb_elements)
	{
		int_data[index] = ft_atoi(splited_line[index]);
		free(splited_line[index]);
		index++;
	}
	free(splited_line);
	return (int_data);
}


t_list *parse_file(int fd, int *nb_lines, int *nb_ints)
{
	t_list 	*root;
	char	*line;
	int		i;

	i = 0;
	root = NULL;
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&root, ft_lstnew(parser_h(line, nb_ints)));
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	*nb_lines = ft_lstsize(root);
	return (root);
}

void	drow_line(t_dda *v, const t_cordinates *cc, t_info *win)
{
	int	pixel;
	t_cordinates c;

	c = *cc;
	pixel = 0;	
	
	c.x0 += 120;
	c.y0 += 120;
	c.xE += 120;
	c.yE += 120;
	
	if (c.z)
		c.color = 0x000000FF;	

	while (pixel < v->slop)
	{
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, round(c.x0), round(c.y0), c.color);
		c.x0 += v->xscale;
		c.y0 += v->yscale;
		pixel++;
	}
}

void	link_dda(t_cordinates *cc, t_info *window)
{
	t_dda v;
	t_cordinates c;
	c = *cc;
	
	c.x0 *= 100;
	c.y0 *= 100;
	c.xE *= 100;
	c.yE *= 100;
	
	c.x0 = (c.x0 - c.y0) * cos(0.8);
	c.y0 = (c.x0 + c.y0) * sin(0.8) - c.z;
	c.xE = (c.xE - c.yE) * cos(0.8);
	c.yE = (c.xE + c.yE) * sin(0.8) - c.z ;

	v.dx = c.xE - c.x0;
	v.dy = c.yE - c.y0;
	if (my_abs(v.dx) > my_abs(v.dy))
		v.slop = my_abs(v.dx);
	else
		v.slop = my_abs(v.dy);

		v.xscale = (float) (v.dx) / v.slop;
		v.yscale = (float) (v.dy) / v.slop;
	drow_line(&v, &c, window);

}

void	continue_(int sofare, int	height, int	width, t_cordinates *c, t_list *data)
{
	int	loop1;
	int	loop2;
	int	*line;

	if (sofare < height * width)
	{
		loop1 = sofare / width;
		loop2 = sofare % width;
		while(loop1--)
			data = data->next;
		line = (int *)(data->content);
		while(loop2--)
			line++;	
		c->z = *line;
	}

}

void	drowX_down_rigth(int	height, int width, t_info *window, t_list *data)
{
	t_cordinates c;
	int	i  = 0;
	
	c.color = 0x0000FF00;
	c.yE = 0;
	while(c.yE < height)
	{
		c.x0 = 0;
		c.xE = 0;
		while (c.xE < width)
		{
			continue_(i, height,width, &c, data);
			link_dda(&c, window);
			c.x0 = c.xE;
			c.xE += 1;
			i++;
		}
		c.yE += 1;
		c.y0 = c.yE;
	}
}

void	drowY_down_rigth(int	height, int width, t_info *window, t_list *data)
{
	t_cordinates c1;
	int	i;
	int	j;
	
	
	i = 0;
	j = 0;	
	c1.xE = 0;
	c1.x0 = 0;
	c1.color = 0x00FF0000;
	while (c1.xE < width)
	{
		c1.y0 = 0;
		c1.yE = 0;
		while (c1.yE < height)
		{
			continue_(i, height, width, &c1, data);
			link_dda(&c1, window);
			c1.y0 = c1.yE;
			c1.yE += 1;
			i += width;
		}
		c1.xE += 1;
		c1.x0 = c1.xE;
		i = ++j;
	}
}
int main(int ac, char **av)
{
	t_list 	*data;
	t_info	win;
	int		fd;
	int		nb_lines;
	int		nb_ints;

	ac--;
	fd = open(av[1], O_RDONLY);
	data = parse_file(fd, &nb_lines, &nb_ints);
	close(fd);
	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win.mlx_ptr, 1300,  1300, "my_fdf_window");
	
	drowX_down_rigth(nb_lines, nb_ints, &win, data);
	drowY_down_rigth(nb_lines, nb_ints, &win, data);
	
	mlx_loop(win.mlx_ptr);
	return (0);
}
