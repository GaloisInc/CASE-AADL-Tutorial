SHELL = bash
CFLAGS = --std=c11 -Wall -Werror

.PHONY: all
all: autopilot controller

.PHONY: run
run: all
	@echo Starting autopilot and controller... hit ctrl-C to quit
	@trap 'kill %1 %2; exit' SIGINT; \
		$(CURDIR)/autopilot & \
		$(CURDIR)/controller & \
		while true; do : ; done

%: %.c common.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< $(LDFLAGS)

.PHONY: clean
clean:
	$(RM) autopilot controller
