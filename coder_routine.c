/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagy <nnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:49:50 by nnagy             #+#    #+#             */
/*   Updated: 2026/11/20 19:22:46 by nnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *coder_routine(void *arg)
{
    t_coder *coder;
    int go;

    coder = (t_coder *)arg;
    pthread_mutex_lock(&coder->lock);
    go = (coder->compile_done < coder->sim->config.nbr_of_compiles_required);
    pthread_mutex_unlock(&coder->lock);
    while (go)
    {

    }

}

static void take_dongle(t_sim *sim, t_coder *coder, t_dongle *dongle)
{
    long wait;

    pthread_mutex_lock(&dongle->mutex);
    wait = dongle->cooldown_until - get_time_ms();
	while (wait > 0)
    log_state(sim, coder->id, "has taken a dongle");
}

static void release_dongle(t_sim *sim, t_dongle *dongle)
{
    dongle->cooldown_until = get_time_ms() + sim->config.dongle_cooldown;
    pthread_mutex_unlock(&dongle->mutex);
}

void compile(t_sim *sim, t_coder *coder)
{
    t_dongle *low;
    t_dongle *high;

    low = coder->left;
    high = coder->right;
    if (low->id > high->id)
    {
        low = coder->right;
        high = coder->left;
    }
    take_dongle(sim, coder, low);
    take_dongle(sim, coder, high);
    pthread_mutex_lock(&coder->lock);
    coder->last_compile_start = get_time_ms();
    pthread_mutex_unlock(&coder->lock);
    log_state(sim, coder->id, "is compiling");
    pthread_mutex_lock(&coder->lock);
    release_dongle(sim, low);
    release_dongle(sim, high);
}