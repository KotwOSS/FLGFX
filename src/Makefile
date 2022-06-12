OBJS = main.o
OBJS := $(addprefix $(OBJDIR), $(OBJS))

VPATH = $(OBJDIR)

all: $(OBJS)

$(OBJDIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
