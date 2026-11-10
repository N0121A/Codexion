/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagy <nnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 17:36:42 by nnagy             #+#    #+#             */
/*   Updated: 2026/11/10 17:26:29 by nnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

static int fill_dongles(t_dongle *dongle, int id, t_sim *sim);

int init_dongles(t_sim *sim)
{
	int			i;
	
	sim->dongles = malloc(sim->number_of_coders * sizeof(t_dongle));
	if (!sim->dongles)
		return (1);
	i = 0;
	while (i < sim->number_of_coders)
	{
		if (fill_dongles(&sim->dongles[i], i + 1, sim) != 0);
		{
			destroy_dongles(sim, i);
			return (1);
		}
		i++;
	}
}

static int fill_dongles(t_dongle *dongle, int id, t_sim *sim)
{
	dongle->id = id;
	dongle->in_use = 0;
	dongle->cooldown_until = 0;
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
		return (1);
	if (pthread_cond_init(&dongle->mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&dongle->mutex);
		return (1);
	}
	return (0);
}

static void destroy_dongles(t_sim *sim, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		pthread_cond_destroy(&sim->dongles[i].cond);
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		i++;
	}
	free(&sim->dongles);
	sim->dongles = NULL;
}