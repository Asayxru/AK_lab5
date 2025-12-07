#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Hello1 module for Lab 5");

struct hello_event {
    struct list_head list;
    ktime_t start;
    ktime_t end;
};

static LIST_HEAD(events_list);

void print_hello(void)
{
    struct hello_event *event;

    event = kmalloc(sizeof(*event), GFP_KERNEL);
    if (!event) {
        pr_err("hello1: memory allocation failed\n");
        return;
    }

    event->start = ktime_get();
    pr_info("Hello, world!\n");
    event->end = ktime_get();

    list_add_tail(&event->list, &events_list);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
    pr_info("hello1 loaded\n");
    return 0;
}

static void __exit hello1_exit(void)
{
    struct hello_event *event, *tmp;
    ktime_t dt;

    pr_info("hello1 exit: printing event times\n");

    list_for_each_entry_safe(event, tmp, &events_list, list) {
        dt = ktime_sub(event->end, event->start);
        pr_info("event duration = %lld ns\n", ktime_to_ns(dt));
        list_del(&event->list);
        kfree(event);
    }
}

module_init(hello1_init);
module_exit(hello1_exit);
