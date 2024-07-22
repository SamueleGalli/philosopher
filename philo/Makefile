
NAME = philo

GCC = 	gcc -Wall -Werror -Wextra -g3 -pthread

SRC	=	main.c \
		control.c \
		INIT/start.c \
		INIT/timer.c \
		INIT/more_philo.c \
		INIT/status_p.c \
		EXTRA/function.c \
		EXTRA/help.c 

OBJECTS = $(SRC:.c=.o)

%.o : %.c
		@echo Complinig [$<]...
		$(GCC) -c -o $@ $<

$(NAME): $(OBJECTS)
		@echo Compiling: [$(SRC)]...
		@echo Completed [$(SRC)]
		@echo
		@echo Compiling [$(NAME)]
		$(GCC) $(OBJECTS) -o $(NAME)
		@echo Completed [$(NAME)]

all: $(NAME)

clean:	
		rm -f $(OBJECTS)
		@echo Removed [$(OBJECTS)]

fclean:	clean
		@rm -f $(NAME)
		@echo Removed [$(NAME)]

re:		fclean all

norm:
		norminette *

.PHONY: all clean fclean re norm

.PHONY: ft_printf

ft_printf:
	$(MAKE) -C ft_printf
