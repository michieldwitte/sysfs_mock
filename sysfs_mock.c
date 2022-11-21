#include <linux/kernel.h>
#include <linux/module.h>

#define BUF_SIZE 100
volatile char model[BUF_SIZE] = "model";
struct kobject* devicetree;
struct kobject* base;

static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%s", model);
}

static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    memcpy((void*)model, buf, min((size_t)BUF_SIZE-1, count));
    model[min(((size_t)BUF_SIZE), count)] = '\0';
	return count;
}

struct kobj_attribute model_attr = __ATTR(model, 0660, sysfs_show, sysfs_store);

struct kernfs_node *my_search(struct rb_root *root, char *string)
{
	struct rb_node *node = root->rb_node;

	while (node) {
		struct kernfs_node *data = container_of(node, struct kernfs_node, rb);
		int result;

		result = strcmp(string, data->name);

		if (result < 0)
			node = node->rb_left;
		else if (result > 0)
			node = node->rb_right;
		else
			return data;
	}
	return NULL;
}

static int __init model_driver_init(void)
{
	struct kernfs_node* node = my_search(&firmware_kobj->sd->dir.children, "devicetree");

	if (!node){
		return -1;
	}

	if (!node->priv){
		return -1;
	}

	devicetree = node->priv;

	node = my_search(&devicetree->sd->dir.children, "base");

	if (!node){
		return -1;
	}

	if (!node->priv){
		return -1;
	}

	base = node->priv;

	base->ktype->sysfs_ops = devicetree->ktype->sysfs_ops; //hack but works

	if(sysfs_create_file(base, &model_attr.attr)){
		sysfs_remove_file(base, &model_attr.attr);
		return -1;
	}
	return 0;
}

static void __exit model_driver_exit(void)
{
	sysfs_remove_file(base, &model_attr.attr);
}

module_init(model_driver_init);
module_exit(model_driver_exit);

MODULE_VERSION("1");
MODULE_DESCRIPTION("Add a sysfs file on an existing location");
MODULE_LICENSE("GPL");
