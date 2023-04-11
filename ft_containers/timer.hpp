/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:32:36 by bperraud          #+#    #+#             */
/*   Updated: 2023/04/11 15:38:39 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_HPP
#define TIMER_HPP

#include <sys/time.h>
#include <cstdlib>

class timer
{
public:
    timer();

public:
    long get_time();
    void reset();

private:
    struct timeval stamp;
};

#endif
