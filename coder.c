/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagy <nnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 15:32:15 by nnagy             #+#    #+#             */
/*   Updated: 2026/11/10 15:37:19 by nnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int fill_coders(t_coder *coder, int i, t_sim *sim);
static void destroy_coders(t_sim *sim, int count);

int init_coders(t_sim *sim)
{
	int		i;
	
	sim->coders = malloc(sim->number_of_coders * sizeof(t_coder));
	if (!sim->coders)
		return (1);
	i = 0;
	while (i < sim->number_of_coders)
	{
		if (fill_coders(&sim->coders[i], i + 1, sim) != 0)
		{
			destroy_coders(sim, i);
			return (1);
		}
		i++;
	}
}

static int fill_coders(t_coder *coder, int id, t_sim *sim)
{
	coder->id = id;
	coder->compile_count = 0;
	coder->left = id;
	coder->right = (id % sim->number_of_coders) + 1;
	coder->last_compile_start = -1;
	coder->sim = sim;
	if (pthread_mutex_init(&coder->lock, NULL) != 0)
		return (1);
	return (0);
}

static void destroy_coders(t_sim *sim, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&sim->coders[i].lock);
		i++;
	}
	free(&sim->coders);
	sim->coders = NULL;
}