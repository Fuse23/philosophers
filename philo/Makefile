NAME				=	philo

CC 					=	gcc
FLAGS 				=	-Wall -Werror -Wextra
INCLUDES			=	-I$(HEADERS_DIRECTORY)

SOURCES_DIRECTORY	=	./src/
SOURCES_LIST		=	main.c		init.c		utils.c		philo.c
SOURCES				=	$(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

HEADERS_DIRECTORY	=	./inc/
HEADERS_LIST		=	philosophers.h
HEADERS				=	$(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

OBJECTS_DIRECTORY	=	./objects/
OBJECTS_LIST		=	$(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS				=	$(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

.PHONY: all clean fclean re

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJECTS_DIRECTORY)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all
