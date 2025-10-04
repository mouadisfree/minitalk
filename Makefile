CC = cc
CFLAGS = -Wall -Wextra -Werror

CLIENT_SRCS = client.c
SERVER_SRCS = server.c

CLIENT_NAME = client
SERVER_NAME = server

FT_PRINTF_DIR = ./ft_printf/
FT_PRINTF = $(FT_PRINTF_DIR)libftprintf.a

all: $(FT_PRINTF) $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_SRCS) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(CLIENT_SRCS) -o $(CLIENT_NAME) -L $(FT_PRINTF_DIR) -lftprintf

$(SERVER_NAME): $(SERVER_SRCS) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o $(SERVER_NAME) -L $(FT_PRINTF_DIR) -lftprintf

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

clean:
	make -C $(FT_PRINTF_DIR) clean
	rm -f *.o

fclean: clean
	make -C $(FT_PRINTF_DIR) fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)

re: fclean all

.PHONY: all clean fclean re