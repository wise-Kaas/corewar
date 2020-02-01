/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:34:54 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/12 17:15:32 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

void		read_card(void *dst, void *src, short int value)
{
	short int	size;

	size = (MEM_SIZE - value) > 4 ? 4 : MEM_SIZE - value;
	if (size > 0)
		ft_memcpy(dst, src + value, size);
	if (size < REG_SIZE)
		ft_memcpy(dst + size, src, REG_SIZE - size);
}

void		write_card(void *dst, void *src, short int value)
{
	short int	size;

	size = (MEM_SIZE - value) > 4 ? 4 : MEM_SIZE - value;
	if (size > 0)
		ft_memcpy(dst + value, src, size);
	if (size < REG_SIZE)
		ft_memcpy(dst, src + size, REG_SIZE - size);
}

void		init_info(t_info *info)
{
	int		i;

	if (!(info->arena = (unsigned char *)malloc(MEM_SIZE)))
		error(8);
	ft_bzero(info->arena, MEM_SIZE);
	info->dump = -1;
	info->cycle_to_die = CYCLE_TO_DIE;
	info->count_cycles = 0;
	info->count_live = 0;
	info->count_check = 0;
	info->i = -1;
	info->processes = NULL;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		(info->players)[i].magic = 0;
		(info->players)[i].prog_size = 0;
		ft_bzero((info->players)[i].prog_name, PROG_NAME_LENGTH + 1);
		ft_bzero((info->players)[i].comment, COMMENT_LENGTH + 1);
	}
}

int			main(int argc, char *argv[])
{
	t_info	info;
	t_sdl	sdl;
	int 	*play;

	if (argc < 2)
		error(7);
	init_info(&info);
	read_arg(&info, argc, argv);
	present_champion(info.players);
	create_processes(&info);
	if (info.dump == -666)
	{
		if (init_sdl(info.arena, &sdl))
			error(8);
		initialize_visual_arena(&sdl, &info);
		event_handler(&info, &sdl);
		free_resources(&sdl);
	}
	else if (info.dump >= 0)
	{
		*play = 0;
		while (info.count_cycles < info.dump && *play != -1)
			gladiatorial_fight(NULL, &info, NULL);
		if (info.count_cycles == info.dump)
			print_arena(info.arena);
		else
			printf("Contestant %d, \"%s\", has won !\n", info.last_live,
				   (info.players)[info.last_live - 1].prog_name);
	}
	else
	{
		*play = 0;
		while (*play != -1)
			gladiatorial_fight(play, &info, NULL);
		printf("Contestant %d, \"%s\", has won !\n", info.last_live,
			   (info.players)[info.last_live - 1].prog_name);
	}
	return (0);
}
