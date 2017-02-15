#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday Log Kernel Module.");
MODULE_AUTHOR("(c) 2016 Jonathan Green");

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

struct birthday *first, *second, *third, *fourth, *fifth;

LIST_HEAD(head);

struct birthday me = {
    .day = 26,
    .month = 1,
    .year = 1989,
    .list = LIST_HEAD_INIT(me.list)
};

struct birthday brian = {
    .day = 1,
    .month = 1,
    .year = 1942,
};

struct birthday ken = {
    .day = 4,
    .month = 2,
    .year = 1943
};

struct birthday dennis = {
    .day = 9,
    .month = 9,
    .year = 1941
};

struct birthday steve = {
    .day = 24,
    .month = 2,
    .year = 1955
};

static int simple_init(void) {
    struct birthday *iter;

    first = kmalloc(sizeof(me), GFP_KERNEL);
    first = &me;
    list_add(&first->list, &head);

    second = kmalloc(sizeof(brian), GFP_KERNEL);
    second = &brian;
    list_add(&second->list, &first->list);

    third = kmalloc(sizeof(ken), GFP_KERNEL);
    third = &ken;
    list_add(&third->list, &second->list);

    fourth = kmalloc(sizeof(dennis), GFP_KERNEL);
    fourth = &dennis;
    list_add(&fourth->list, &third->list);

    fifth = kmalloc(sizeof(steve), GFP_KERNEL);
    fifth = &steve;
    list_add(&fifth->list, &fourth->list);

    printk(KERN_ALERT "Birthday Log Kernel Module Loaded.\n");
    list_for_each_entry(iter, &head, list)  {
        printk("Birthday: Day = %d month = %d year = %d\n",
        iter->day, iter->month, iter->year);
    }

    return 0;
}

static void simple_exit(void) {
    struct list_head *pos, *q;
    struct birthday *tmp;

    printk(KERN_ALERT "Birthday Log Kernel Module Removed.\n");

    list_for_each_safe(pos, q, &head) {
        tmp = list_entry(pos, struct birthday, list);
        printk("Removing Birthday: Day = %d month = %d year = %d\n",
        tmp->day, tmp->month, tmp->year);
        list_del(pos);
    }
}

module_init( simple_init );
module_exit( simple_exit );
