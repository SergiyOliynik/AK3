#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/ktime.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

struct linked_list {
	struct list_head node;
	ktime_t start;
	ktime_t finish;
};
	

static LIST_HEAD(linked_head);
static uint how_many = 1;
module_param(how_many, uint, S_IRUGO);
static int __init hello_init(void)
{
	int error = -EINVAL;
	uint k;
	ktime_t start, finish;
	struct linked_list *data;

	if (how_many==0 || (how_many>=5 && how_many<=10))
	{
		printk(KERN_EMERG "WARNING! Got big number, but not so critical. Going to go further, anyway...\n");
	}
	if (how_many>10)
	{
		printk(KERN_ERR "ERROR! Argument is way too big. Stop there.\n");
		return error;
	}
	BUG_ON(!list_empty(&linked_head));
	for (k=0; k<how_many; k++) {
		start = ktime_get();
		printk(KERN_EMERG "Hello, world!\n");
		finish = ktime_get();
		data = (struct linked_list *) kmalloc(sizeof(struct linked_list), GFP_KERNEL);
		*data = (struct linked_list) {
			(struct list_head) {NULL, NULL},
				start,
				finish
		};	
		list_add_tail(&data->node, &linked_head);
	}
	return 0;
}
EXPORT_SYMBOL(hello_init);
static void __exit hello_exit(void)
{
	struct linked_list *data, *tmp;
	list_for_each_entry_safe(data, tmp, &linked_head, node){
		printk(KERN_EMERG "%lld\n", data->finish-data->start);
		list_del(&data->node);
		kfree(data);
	}
}
module_init(hello_init);
module_exit(hello_exit);
