#------------------------------------------------------------------------------#
#----------------------------------PROPERTIES----------------------------------#
#------------------------------------------------------------------------------#

CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g
DFLAGS	 	= -MD -MP
IFLAGS		= -I $(INCLUDES)
MAKEFLAGS	= -j$(nproc) --no-print-directory

NAME		= philo_bonus

SRCSDIR		= srcs
INCLUDES	= include

SRCS		= \
			$(SRCSDIR)/main.c \

OBJSDIR		= objs
OBJS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
DEPS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.d))

#------------------------------------------------------------------------------#
#------------------------------------RULES-------------------------------------#
#------------------------------------------------------------------------------#

all		: $(NAME)

$(NAME)	: ${OBJS}
		$(MAKE) -C ${LIBDIR} all
		$(CC) ${CFLAGS} ${DFLAGS} ${IFLAGS} -o $@ $^

${OBJSDIR}/%.o	: %.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} ${DFLAGS} ${IFLAGS} -c $< -o $@

clean	:
		$(MAKE) -C ${LIBDIR} clean
		$(RM) $(OBJSDIR)

fclean	:
		$(MAKE) -C ${LIBDIR} fclean
		$(RM) $(OBJSDIR) $(NAME)

re		:
		$(MAKE) -C ${LIBDIR} fclean
		$(RM) $(OBJSDIR) $(NAME)
		$(MAKE) all

-include $(DEPS)

.PHONY	: all clean fclean re
