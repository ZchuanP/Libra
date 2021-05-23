#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

static struct task_struct * MyThread = NULL;
static int MyKThread(void *str){
    // 读取输入信息
    char *mydata = kmalloc(strlen(str)+1,GFP_KERNEL);
    memset(mydata,'\0',strlen(str)+1);
    strncpy(mydata,str,strlen(str));
    printk("%s\n",mydata);
    kfree(mydata);
    return 0;
}
static int __init hellokernel(void)
{
    // 运行线程
    MyThread = kthread_run(MyKThread,"hello world,i am the first kernel module of you!","Mythread");
    return 0;
}

static void __exit exitkernel(void)
{ 
    // 判断线程是否存在，终止线程
    if(MyThread)
    {
        printk("goodbye,my handsome.\n");
        kthread_stop(MyThread);
    }  
}
module_init(hellokernel);
module_exit(exitkernel);
