#include "fdf.h"

void    mlx_connect(t_mlx *mlx)
{
    mlx->w = W;
    mlx->h = H;
    if (!(mlx->mlx_ptr = mlx_init()))
        exit(EXIT_FAILURE);
    if (!(mlx->win = mlx_new_window(mlx->mlx_ptr, mlx->w, mlx->h, "FDF")))
    {
        free(mlx->mlx_ptr);
        mlx->mlx_ptr = NULL;
        exit(EXIT_FAILURE);
    }
}


void    mlx_disconnect(t_mlx *mlx)
{
    mlx_clear_window(mlx->mlx_ptr, mlx->win);
    mlx_destroy_window(mlx->mlx_ptr, mlx->win);
}

void    mlx_create_image(t_mlx *mlx)
{
    mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->w, mlx->h);
    mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);

}

void    mlx_clear_image(t_mlx *mlx)
{
    bzero(mlx->img.data, mlx->w * mlx->h * 4);
}

void    mlx_close_image(t_mlx *mlx)
{
    mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);      
}

static  void    line(t_mlx *mlx, int x0, int y0, int x1, int y1, int z0, int z1)
{ 
        //int dx = abs(mlx->pt.l.x1 - mlx->pt.l.x0), sx = mlx->pt.l.x0 < mlx->pt->l.x1 ? 1 : -1;
        //int dy = abs(mlx->pt.l.y1 - mlx->pt.l.y0), sy = mlx->pt.l.y0 < mlx->pt->l.y1 ? 1 : -1; 
        //int err = (dx>dy ? dx : -dy)/2, e2;

    x0 = (int)(0.71 * (x0 - y0)) + 210;
    y0 = (int)(-(-0.41 * (x0 + y0)) + 0.82 * -z0) + 210;
    x1 = (int)(0.71 * (x1 - y1)) + 210;
    y1 = (int)(-(-0.41 * (x1 + y1)) + 0.82 * -z1) + 210;

    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int err = (dx>dy ? dx : -dy)/2, e2;

    for(;;)
    {
        put_pixel(&(*mlx), x0 , y0);
                //mlx->img.data[(mlx->pt.l.y0 * 600 + mlx->pt.l.x0)] = mlx->pt.l.color;
        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void    put_pixel(t_mlx *mlx, int x, int y)
{
    mlx->img.data[(y) * 600 + (x)] = 0xFF0000;
}

void    mlx_draw_image(t_mlx *mlx, t_point **pt, int cols, int rows)
{
    int             y;
    int             x;
    int             y_p;
    int             x_p;

    y = 0;
    y_p = 0;
    while (y < cols)
    {
        x = 0;
        x_p = 0;
        while (x < rows)
        {
            line(&*mlx, (*pt)[y * rows + x_p].x, (*pt)[y * rows + x].y, (*pt)[y * rows + x].x, (*pt)[y * rows + x_p].y, (*pt)[y * rows + x_p].z, (*pt)[y * rows + x].z);
            line(&*mlx, (*pt)[y * rows + x].x, (*pt)[y_p * rows + x].y, (*pt)[y * rows + x].x, (*pt)[y * rows + x_p].y, (*pt)[y_p * rows + x].z, (*pt)[y * rows + x].z);
            x++;
            x_p = x - 1;
        }
        y++;
        y_p = y - 1;
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
}


