/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by wclayton          #+#    #+#             */
/*   Updated: 2020/01/30 01:02:13 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc.h"
#include <stdio.h>
#include <errno.h>

int f_lex(int fd)
{
    char *line;

    get_next_line(fd, &line);

}

int main(void)
{
    int fd;

    errno = 0;
    if (!(fd = open("src", O_RDONLY)))
    {
        perror("lol");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
    f_lex(fd);
}

//lex and compile asm to bytecode