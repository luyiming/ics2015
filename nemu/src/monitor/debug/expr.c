#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ, NUM, REG, VAR, NEG, DEREF, NOP
};

static bool is_operator(int type) {
    if(type == '+' || type == '-' || type == '*' || type == '/' ||
       type == NEG || type == DEREF)
        return true;
    else
        return false;
}

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{ " +",	            NOTYPE },   // spaces
	{ "==",             EQ },       // equal
    { "(0x)?[0-9]+",    NUM },      // number
    { "%[a-zA-Z]+",     REG },      // register
    { "[^%][a-zA-Z]+",  VAR },      // variable
    { "\\(",            '('},
    { "\\)",            ')'},
	{ "\\+",            '+'},				
	{ "-",              '-'},				
	{ "\\*",            '*'},				
	{ "/",              '/'},					
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[64];
} Token;

Token tokens[64];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain 
				 * types of tokens, some extra actions should be performed.
				 */
                Assert(nr_token < 64, "tokens out of range");

				switch(rules[i].token_type) {
                    case NUM:
                    {
                        tokens[nr_token].type = NUM; 
                        strncpy(tokens[nr_token].str, substr_start, substr_len);
                        tokens[nr_token].str[substr_len + 1] = '\0';
                        nr_token++;
                        break;
                    }
                    case REG:   //remove prefix %
                    {
                        tokens[nr_token].type = REG; 
                        strncpy(tokens[nr_token].str, substr_start + 1, substr_len - 1);
                        tokens[nr_token].str[substr_len] = '\0';
                        nr_token++;
                        break;
                    }
                    case NOTYPE: break;
					default: tokens[nr_token++].type = rules[i].token_type; break;
				}
				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}
    for(i = 0; i < nr_token; i ++) {
        if(tokens[i].type == '*' && (i == 0 || tokens[i - 1].type == '(' || is_operator(tokens[i - 1].type)) ) {
            tokens[i].type = DEREF;
        }
    }
    for(i = 0; i < nr_token; i ++) {
        if(tokens[i].type == '-' && (i == 0 || tokens[i - 1].type == '(' || is_operator(tokens[i - 1].type)) ) {
            tokens[i].type = NEG;
        }
    }
	return true; 
}

static int check_parentheses(int p, int q) {
    // return value:
    // 0  match
    // -1 bad expression
    // 1  good expression, not match
    int st[64], top = 0;
    (void)st;
    int i;
    for(i = p; i <= q; i ++) {
        if(tokens[i].type == '(') {
            st[top++] = '(';
        }
        else if(tokens[i].type == ')') {
            if(top == 0)
                return -1;  // lack left parenthesis
            top--;
        }
    }
    if(top != 0)
        return -1;  //lack right parenthesis
    else if(tokens[p].type == '(' && tokens[q].type == ')')
        return 0;
    else
        return 1;
}

static bool op_less_equal(int pt, int qt) {
    if(qt == NOP)
        return true;
    if(pt == NEG || pt == DEREF)
        return false;
    else if (pt == '+' || pt == '-')
        return true;
    else {
        if(qt == NEG || qt == DEREF)
            return false;
        else
            return true;
    }
}

static int eval(int p, int q) {
    if(p > q) {
                /* Bad expression */
        return 0;
    }
    else if(p == q) { 
    /* Single token.
     *       * For now this token should be a number. 
     *               * Return the value of the number.
     *                       */ 
        if(tokens[p].type == NUM) {
            int value = 0;
            if(strncmp(tokens[p].str, "0x", 2) == 0) { // Hex
                int i, len = strlen(tokens[p].str);
                for(i = 2; i < len; i ++) {
                    int tmp = tokens[p].str[i] - '0';
                    if(tmp > 9 || tmp < 0)
                        tmp = tokens[p].str[i] - 'a' + 10;
                    value = value * 16 + tmp; 
                }
            }   
            else { // Dec
                int i, len = strlen(tokens[p].str);
                for(i = 0; i < len; i ++) {
                    value = value * 10 + tokens[p].str[i] - '0'; 
                }
            }
            return value;
        }
        else if(tokens[p].type == REG) {
            uint32_t value = 0;
            int i;
            for(i = R_EAX; i <= R_EDI; i ++) {
                if(strcmp(tokens[p].str, regsl[i]) == 0) {
                    value = reg_l(i);
                    return value;
                }
            }
            for(i = R_AX; i <= R_DI; i ++) {
                if(strcmp(tokens[p].str, regsw[i]) == 0) {
                    value = reg_w(i);
                    return value;
                }
            }
            for(i = R_AL; i <= R_BH; i ++) {
                if(strcmp(tokens[p].str, regsb[i]) == 0) {
                    value = reg_b(i);
                    return value;
                }
            }
            if(strcmp(tokens[p].str, "eip") == 0)
                return cpu.eip;
            printf("undefined register\n");
            return -1;
        }
        else
            return 0;
    }
    else if(check_parentheses(p, q) == 0) {
    /* The expression is surrounded by a matched pair of parentheses. 
     *       * If that is the case, just throw away the parentheses.
     *               */
        return eval(p + 1, q - 1); 
    }
    else {
        int i, in_bracket = 0;
        int op = 0, op_type = NOP; // initial op_type should be large enough
        // op = the position of dominant operator in the token expression;
        for(i = p; i <= q; i++) {
            if(tokens[i].type == '(')
                in_bracket++;
            else if(tokens[i].type == ')')
                in_bracket--;
            else if(is_operator(tokens[i].type) && !in_bracket) {
                if(op_less_equal(tokens[i].type, op_type)) {
                    op = i;
                    op_type = tokens[i].type;
                }
            }
        }

        switch(op_type) {
            case '+': return eval(p, op - 1) + eval(op + 1, q);
            case '-': return eval(p, op - 1) - eval(op + 1, q);
            case '*': return eval(p, op - 1) * eval(op + 1, q);
            case '/': return eval(p, op - 1) / eval(op + 1, q);
            case NEG: return -eval(op + 1, q);
            case DEREF:
            {
                int t_addr = eval(op + 1, q);
                Assert(t_addr >= 0, "address out of range: 0x%x\t %d\n", t_addr, t_addr);
                uint32_t value = swaddr_read(t_addr, 4);
                return value;
            }
            default: Assert(0, "bad expression\n");
        }
    }
}

int expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
    if(check_parentheses(0, nr_token - 1) == -1) {
		*success = false;
		return 0;
    }
    *success = true;
    return eval(0, nr_token - 1);
}

