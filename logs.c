/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagy <nnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:58:55 by nnagy             #+#    #+#             */
/*   Updated: 2026/11/20 18:58:59 by nnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void print_error(const char *msg)
{
    write(STDERR_FILENO, "Error: ", 7);
    write(STDERR_FILENO, msg, strlen(msg));
    write(STDERR_FILENO, "\n", 1);
}


void log_state(t_sim *sim, int coder_id, const char *msg)
{
    pthread_mutex_lock(&sim->log_lock);
    printf("%ld %d %s\n", get_time_ms() - sim->start_time, coder_id, msg);
    pthread_mutex_unlock(&sim->log_lock);
}
