#------------------------------------------------------------------------------#
#----------------------------------PROPERTIES----------------------------------#
#------------------------------------------------------------------------------#

CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g
# -fsanitize=thread -O1
DFLAGS	 	= -MD -MP
IFLAGS		= -I $(INCLUDES)
MAKEFLAGS	= -j$(nproc) --no-print-directory

NAME		= philo

SRCSDIR		= srcs
INCLUDES	= include

SRCS		= \
			$(SRCSDIR)/main.c \
			$(SRCSDIR)/utils.c \
			$(SRCSDIR)/validate.c \
			$(SRCSDIR)/validate_utils.c \
			$(SRCSDIR)/simulation.c \
			$(SRCSDIR)/time.c \
			$(SRCSDIR)/init.c \
			$(SRCSDIR)/print.c \
			$(SRCSDIR)/check.c \
			$(SRCSDIR)/monitoring.c \
			$(SRCSDIR)/free_data.c \


OBJSDIR		= objs
OBJS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
DEPS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.d))

#------------------------------------------------------------------------------#
#------------------------------------RULES-------------------------------------#
#------------------------------------------------------------------------------#

all		: $(NAME)

$(NAME)	: ${OBJS}
		$(CC) ${CFLAGS} ${DFLAGS} ${IFLAGS} -o $@ $^

# -lpthread

${OBJSDIR}/%.o	: %.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} ${DFLAGS} ${IFLAGS} -c $< -o $@

clean	:
		$(RM) $(OBJSDIR)

fclean	:
		$(RM) $(OBJSDIR) $(NAME)

re		:
		$(RM) $(OBJSDIR) $(NAME)
		$(MAKE) all

-include $(DEPS)

.PHONY	: all clean fclean re
