CC = cc
CFLAGS = -pthread -Wall -Werror -Wextra 
INCLUDE = -I./inc

PHILO = inc/philo.h 
PHILO_BONUS = inc/philo_bonus.h

FILES = philo.o \
		parsing.o \
		initialize.o \
		execution.o \
		utils.o \
		ft_atoi.o

FILES_B = philo_bonus.o \
			ft_isnumber.o \
			ft_strlen.o \
			ft_strcmp.o \
			ft_atoi.o \
			philos_states_bonus.o \
			utils_bonus.o \


B_DIR = build

OBJ = $(addprefix $(B_DIR)/, $(FILES))
OBJ_B = $(addprefix $(B_DIR)/philo_bonus/, $(FILES_B))

NAME = philos
NAME_B = philo_bonus

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(MFLAGS) $^ -o $@
	@echo "\033[30;1m---> \033[0m42 Dining Philosophers (Multithreading) V2.0 \033[32;1m [OK] \033[0m"
	

bonus : $(OBJ_B)
	$(CC) $(MFLAGS) $^ -o $(NAME_B)
	@echo "\033[30;1m---> \033[0m42 Dining Philosophers (Multiprocessing) V2.0 \033[32;1m [OK] \033[0m"

$(B_DIR)/bonus/%.o: src/bonus/%.c $(PHILO_BONUS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c  $<

$(B_DIR)/%.o: philo/%.c $(PHILO)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c  $<

clean :
	@echo "\033[30;1m---> \033[0mObject files clean\033[32;1m [DONE] \033[0m"
	rm -rf $(B_DIR)  

fclean : clean
	@echo "\033[30;1m---> \033[0mBinary files clean\033[32;1m [DONE] \033[0m"
	rm -rf $(NAME) $(NAME_B)

re : fclean all

.PHONY : all bonus clean fclean re 