/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagy <nnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:59:43 by nnagy             #+#    #+#             */
/*   Updated: 2026/11/20 18:59:52 by nnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int argc, char **argv)
{
    t_sim sim;

    if (parse_input(&sim, argc, argv) != 0)
        return (1);
    if (init_simulation(&sim) != 0)
        return (1);
    if (start_simulation(&sim) != 0)
    {
        return (1);
    }
    return (0);
}
