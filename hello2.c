#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/errno.h>
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Hello2 module for Lab 5");

static uint hello_count = 1;
module_param(hello_count, uint, 0644);
MODULE_PARM_DESC(hello_count, "How many times to print 'Hello, world!'");

static int __init hello2_init(void)
{
    int i;

    if (hello_count == 0 || (hello_count >= 5 && hello_count <= 10)) {
        pr_warn("hello2: suspicious hello_count = %u\n", hello_count);
    }

    if (hello_count > 10) {
        pr_err("hello2: invalid hello_count = %u\n", hello_count);
        return -EINVAL;
    }

    for (i = 0; i < hello_count; i++)
        print_hello();

    pr_info("hello2 loaded\n");
    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("hello2 exit\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
