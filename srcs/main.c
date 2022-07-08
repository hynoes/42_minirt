/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:40:56 by kangkim           #+#    #+#             */
/*   Updated: 2022/07/08 20:20:25 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>
#include <mlx.h>
#include "libft.h"


int main(void)
{
    printf("%c", ft_toupper('a'));
    void *mlx_ptr = mlx_init();
    void *mlx_win = mlx_new_window(mlx_ptr, 1600, 900, "TEST");
    (void)mlx_win;
    mlx_loop(mlx_ptr);
}