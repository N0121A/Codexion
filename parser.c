/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagy <nnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 13:10:31 by nnagy             #+#    #+#             */
/*   Updated: 2026/11/09 17:15:09 by nnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


static long parse_arg_to_int(const char *s);
static void fill_config(t_sim *sim, const long *av);
static int parse_scheduler(t_sim *sim, const char *s);

int parse_args(int argc, const char **argv, t_sim *sim)
{
	long    av[7];
    int     i;

    if (argc != 9)
        return (1);
    i = 0;
    while (i < 7)
    {
        av[i] = parse_arg_to_int(argv[i + 1]);
        if (av[i] < 0)
            return (1);
        i++;
    }
	if (av[0] < 1)
		return (1);
	fill_config(sim, av);
	if (parse_scheduler(sim, av[8]) != 0)
		return (1);
    return (0);
}

static long parse_arg_to_int(const char *s)
{
    long    n;
    int     i;

    if (s[0] == '\0')
        return (1);
    n = 0;
    i = 0;
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (1);
        n = n * 10 + (s[i] - '0');
        if (n > INT_MAX)
            return (1);
        i++;
    }
    return(n);
}

static void fill_config(t_sim *sim, const long *av)
{
	sim->number_of_coders = av[0];
    sim->time_to_burnout = av[1];
    sim->time_to_compile = av[2];
    sim->time_to_debug = av[3];
    sim->time_to_refactor = av[4];
    sim->number_of_compiles_required = av[5];
    sim->dongle_cooldown = av[6];
}


static int parse_scheduler(t_sim *sim, const char *s)
{
	if (strcmp(s, "fifo") == 0)
		sim->scheduler == FIFO;
	else if (strcmp(s, "edf") == 1)
		sim->scheduler == EDF;
	else
		return (1);
    return (0);
}
