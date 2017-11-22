asmlinkage long sys_hellosys(long uid, const char __user *content){
    printk("%d wants to say hello, and %s", uid, content);
    return 1;
}