/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colored_str.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 17:48:17 by omiroshn          #+#    #+#             */
/*   Updated: 2018/08/26 17:48:18 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORED_STR_H
# define COLORED_STR_H

# define ANSI_COLOR_RED				"\x1b[31m"
# define ANSI_COLOR_GREEN			"\x1b[32m"
# define ANSI_COLOR_YELLOW			"\x1b[33m"
# define ANSI_COLOR_BLUE			"\x1b[34m"
# define ANSI_COLOR_MAGENTA			"\x1b[35m"
# define ANSI_COLOR_CYAN			"\x1b[36m"

# define ANSI_COLOR_RED_BOLD		"\x1b[1;31m"
# define ANSI_COLOR_GREEN_BOLD		"\x1b[1;32m"
# define ANSI_COLOR_YELLOW_BOLD		"\x1b[1;33m"
# define ANSI_COLOR_BLUE_BOLD		"\x1b[1;34m"
# define ANSI_COLOR_MAGENTA_BOLD	"\x1b[1;35m"
# define ANSI_COLOR_CYAN_BOLD		"\x1b[1;36m"

# define ANSI_COLOR_RESET			"\x1b[0m"

# define RED_STR(s) (ANSI_COLOR_RED s ANSI_COLOR_RESET)
# define GREEN_STR(s) (ANSI_COLOR_GREEN s ANSI_COLOR_RESET)
# define YELLOW_STR(s) (ANSI_COLOR_YELLOW s ANSI_COLOR_RESET)
# define BLUE_STR(s) (ANSI_COLOR_BLUE s ANSI_COLOR_RESET)
# define MAGENTA_STR(s) (ANSI_COLOR_MAGENTA s ANSI_COLOR_RESET)
# define CYAN_STR(s) (ANSI_COLOR_CYAN s ANSI_COLOR_RESET)

# define RED_BOLD_STR(s) (ANSI_COLOR_RED_BOLD s ANSI_COLOR_RESET)
# define GREEN_BOLD_STR(s) (ANSI_COLOR_GREEN_BOLD s ANSI_COLOR_RESET)
# define YELLOW_BOLD_STR(s) (ANSI_COLOR_YELLOW_BOLD s ANSI_COLOR_RESET)
# define BLUE_BOLD_STR(s) (ANSI_COLOR_BLUE_BOLD s ANSI_COLOR_RESET)
# define MAGENTA_BOLD_STR(s) (ANSI_COLOR_MAGENTA_BOLD s ANSI_COLOR_RESET)
# define CYAN_BOLD_STR(s) (ANSI_COLOR_CYAN_BOLD s ANSI_COLOR_RESET)

#endif
