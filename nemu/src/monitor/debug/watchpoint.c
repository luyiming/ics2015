#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_pool[i].NO = i + 1;
		wp_pool[i].next = &wp_pool[i + 1];
        wp_pool[i].hit_times = 0;
	}
	wp_pool[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_pool;
}

WP* new_wp() {
    if(free_ == NULL)
        return NULL;
    WP *p = free_;
    free_ = free_->next;

    p->next = head;
    head = p;
    return p;
}

bool free_wp(int number) {
    WP *p1, *p2;
    for(p1 = NULL, p2 = head; p2 != NULL; p1 = p2, p2 = p2->next) {
        if(p2->NO == number) {
            if(p2 == head)
                head = head->next;
            else
                p1->next = p2;
        }
    }
    if(p2 == NULL)
        return false;
    p2->hit_times = 0;
    p2->next = free_;
    free_ = p2;
    return true;
}

void print_wp() {
    WP *p;
    printf("Num\t\tExpression\n");
    for(p = head; p != NULL; p = p->next) {
        printf("%d\t\t%s\n", p->NO, p->str);
    }
}

bool hit_wp()
{
    WP *p;
    for(p = head; p != NULL; p = p->next) {
        bool success = false;
        int temp = expr(p->str, &success);
        if(temp != p->value)
        {
            printf("Hit watchpoint #%d\texpr = %s, value = %d/%x\n", p->NO, p->str, p->value, p->value);
            p->hit_times++;
            return true;
        }       
    }
    return false;
}
