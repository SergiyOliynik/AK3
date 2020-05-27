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
static uint howmany = 1;

module_param(howmany, uint, S_IRUGO);

static int __init hello_init(void)
{
	uint k;
	ktime_t start, finish;
	struct linked_list *data;

 	WARN_ON(howmany==0 || (howmany>=5 && howmany<=10));
 	BUG_ON(howmany>10);

 	BUG_ON(!list_empty(&linked_head));
 	for (k=0; k<howmany; k++) {
 		start = ktime_get();
 		pr_info("Hello, world!\n");
 		finish = ktime_get();
 		data = (struct linked_list *) kmalloc(sizeof(struct linked_list),GFP_KERNEL);
 	if (k == 5){
 		data = NULL;
 }
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
		pr_info("%lld\n", data->finish-data->start);
		list_del(&data->node);
		kfree(data);
	}
}
module_init(hello_init);
module_exit(hello_exit);
