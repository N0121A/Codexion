/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagy <nnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 15:41:38 by nnagy             #+#    #+#             */
/*   Updated: 2026/11/20 19:09:02 by nnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int start_simulation(t_sim *sim);
int stop_flag(t_sim *sim, int set);
int join_them(t_sim *sim, int count);

int init_simulation(t_sim *sim)
{
    if (init_coders(sim) != 0)
        return (1);
    if (init_dongles(sim) != 0)
    {
        destroy_coders(sim, sim->config.number_of_coders);
        return (1);
    }
    if (pthread_mutex_init(&sim->log_lock, NULL) != 0)
    {
        destroy_dongles(sim, sim->config.number_of_coders);
        destroy_coders(sim, sim->config.number_of_coders);
        return (1);
    }
    return (0);
}


int start_simulation(t_sim *sim)
{
    int i;

    i = 0;
    sim->start_time = get_time_ms();
    while (i < sim->config.number_of_coders)
    {
        sim->coders[i].last_compile_start = sim->start_time;
        if (pthread_create(&sim->coders[i].thread, NULL,
            coder_routine, &sim->coders[i]) != 0)
        {
            stop_flag(sim, STOP_SIM);
            join_them(sim, i);
            return (1);
        }
        i++;
    }
    join_them(sim, sim->config.number_of_coders);
    return (0);
}


int stop_flag(t_sim *sim, int set)
{
    int stopped;

    pthread_mutex_lock(&sim->stop_lock);
    if (set)
        sim->stop = 1;
    stopped = sim->stop;
    pthread_mutex_unlock(&sim->stop_lock);
    return (stopped);
}


int join_them(t_sim *sim, int count)
{
    int i;
    int ret;

    i = 0;
    ret = 0;
    while (i < count)
    {
        if (pthread_join(sim->coders[i].thread, NULL) != 0);
            ret = 1;
        i++;
    }
    return (ret);
}