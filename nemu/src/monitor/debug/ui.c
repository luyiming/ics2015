#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "cpu/reg.h"

void cpu_exec(uint32_t);

/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;
    char *temp_line = NULL;

	temp_line = readline("(nemu) ");

    int i, valid = 0, len = strlen(temp_line);
    for(i = 0; i < len; i++) {
        if(!isspace(temp_line[i])) {
            valid = 1;
            break;
        }
    }

    if(valid) {
        if(line_read) {
            free(line_read);
        }
        line_read = temp_line;
        add_history(line_read);
    }
    else {
        if(temp_line) {
            free(temp_line);
        }
    }

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_help(char *args);
static int cmd_si(char *args);
static int cmd_info(char *args);
static int cmd_x(char *args);
static int cmd_p(char *args);

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands\n", cmd_help },
	{ "c", "Continue the execution of the program\n", cmd_c },
	{ "q", "Exit NEMU\n", cmd_q },
    { "si", "Step one instruction exactly.\n", cmd_si },
    { "info", "Show information\n", cmd_info },
    { "x", "Examine memory\n", cmd_x },
    { "p", "Print expression\n", cmd_p },

	/* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

static int cmd_si(char *args) {
    char *arg = strtok(NULL, " ");
    int n = 1;
    if(arg != NULL) {
        n = atoi(arg);
    }
    cpu_exec(n);
    return 0;
}

static int cmd_info(char *args) {
    char *arg = strtok(NULL, " ");

    if(arg == NULL) {

    }
    else if(strcmp(arg, "r") == 0) {
        int i;
        for(i = R_EAX; i <= R_EDI; i ++) {
            printf("%s\t\t0x%08x\n", regsl[i], reg_l(i));
        }
        printf("eip\t\t0x%08x\n", cpu.eip);
    }
    else if(strcmp(arg, "w") == 0) {

    }
    else {
        printf("Invalid use\n");
    }
    return 0;
}

static int cmd_x(char *args) {
    return 0;
}

static int cmd_p(char *args) {
    if(args) {
        bool success = false;
        int value = expr(args, &success);
        if(success) {
            if(strchr(args, '%') != NULL)
                printf("0x%x\n", value);
            else
                printf("%d", value);
        }
        else
            printf("bad expression\n");
    }
    return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
