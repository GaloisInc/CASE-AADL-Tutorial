SHELL = bash
CFLAGS = -std=c11 -Wall -Wextra

DEPS = protocol.o
OBJECTS = protocol.o gc.o uav.o
EXECUTABLES = gc uav

.PHONY: all
all: $(OBJECTS) $(EXECUTABLES)

.PHONY: run
run: all
	@echo Starting client and server... hit ctrl-C to quit
	@trap 'kill %1 %2; exit' SIGINT; \
		$(CURDIR)/uav & \
		$(CURDIR)/gc & \
		while true; do : ; done

%.o: %.c
	$(CC) -c $^ -o $@ $(CFLAGS)

%: %.o $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(EXECUTABLES)
