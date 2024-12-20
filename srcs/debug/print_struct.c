/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:54:48 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/20 16:21:27 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_envp_array(t_data *data)
{
    int i = 0;
    while (data->envp_array[i])
    {
        printf("%s\n", data->envp_array[i]);
        i++;
    }
}
