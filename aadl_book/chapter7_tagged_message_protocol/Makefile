SHELL = bash
CFLAGS = --std=c11 -Wall -Werror

.PHONY: all
all: vehicle controller

.PHONY: run
run: all
	@echo Starting vehicle and controller... hit ctrl-C to quit
	@trap 'kill %1 %2; exit' SIGINT; \
		$(CURDIR)/vehicle & \
		$(CURDIR)/controller & \
		while true; do : ; done

%: %.c protocol.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< $(LDFLAGS)

.PHONY: clean
clean:
	$(RM) vehicle controller
