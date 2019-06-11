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

# ifndef FTCHEKER
#  define BLINK	"\e[5m"
#  define LR		"\e[38;2;225;100;125m"
#  define LY		"\e[38;2;255;220;65m"
#  define LG		"\e[38;2;185;225;70m"
#  define LB		"\e[38;2;80;220;200m"
#  define LP		"\e[38;2;160;160;255m"
#  define R		"\e[1;38;2;225;20;20m"
#  define O		"\e[1;38;2;255;120;10m"
#  define Y		"\e[1;38;2;255;200;0m"
#  define G		"\e[1;38;2;80;200;60m"
#  define B		"\e[1;38;2;50;150;250m"
#  define P		"\e[1;38;2;150;75;255m"
#  define W		"\e[1;38;2;255;250;232m"
#  define BR		"\e[1;48;2;150;0;0m"
#  define BY		"\e[1;48;2;255;155;0m"
#  define BG		"\e[1;48;2;0;100;25m"
#  define BB		"\e[1;48;2;0;65;140m"
#  define BP		"\e[1;48;2;60;0;125m"
#  define E		"\e[0m"
# else
#  define BLINK	""
#  define LR		""
#  define LY		""
#  define LG		""
#  define LB		""
#  define LP		""
#  define R		""
#  define O		""
#  define Y		""
#  define G		""
#  define B		""
#  define P		""
#  define W		""
#  define BR		""
#  define BY		""
#  define BG		""
#  define BB		""
#  define BP		""
#  define E		""
# endif

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
