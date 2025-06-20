## Definindo as váriaveis ##

# Nome do projeto:
PROJ_NAME=jogadores

# Arquivos .c:
C_SOURCE=$(wildcard *.c)

# Arquivos .o:
OBJ=$(C_SOURCE:.c=.o)

# Compilador:
CC=gcc

# Opções para o compilador:
CC_FLAGS=-c         \
         -Wall      \
		 -g         \
         -pedantic


## Compilação e linkagem ##

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME) *~