/* Start of monitor_func.c */
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/cpuset.h>
#include <linux/export.h>
#include <linux/mm.h>
#include <linux/list.h>
#include <trace/events/vmscan.h>
#include <linux/mmzone.h>
#include <linux/memcontrol.h>
#include <linux/swap.h>



void show_pfn(struct list_head *src){
  int page_count=0;
  struct page *p = NULL;
	struct list_head *i, *n;
	list_for_each_safe(i, n, src) {
		p = list_entry(i, struct page, lru);
		page_count++;
	}

  /*while(!list_empty(src)){
    if(++page_count >=20) break;
    p= lru_to_page(src);
    printk(KERN_CONT "(%lx) ",page_to_pfn(p));
    p= list_entry(p->lru,struct page, lru);
  }*/
  printk(KERN_INFO "num : %d\n",page_count);
}

SYSCALL_DEFINE0(monitor_syscall)
{
    
  struct pglist_data *current_pglist;
  struct lruvec *lruvec;
  struct mem_cgroup *memcg = NULL;
  int i;

  for(i=0;i<MAX_NUMNODES;i++){
    if(NODE_DATA(i)==NULL) continue;

    current_pglist = NODE_DATA(i);

    if(current_pglist->node_present_pages==0){
      printk(KERN_ALERT "No page in node-%d\n",i);
      continue;
    }

    memcg = get_mem_cgroup_from_mm(NULL);
    lruvec = mem_cgroup_lruvec(memcg,current_pglist);
    enum lru_list lru;

    
    spin_lock_irq(&lruvec->lru_lock);
    printk("========== LRU_ACTIVE_FILE ============\n"); 
    show_pfn(&lruvec->lists[LRU_ACTIVE_FILE]); 
    lru = LRU_ACTIVE_FILE;
    printk(KERN_INFO "%ld\n",lruvec_lru_size(lruvec,lru,MAX_NR_ZONES));

    printk("========== LRU_INACTIVE_FILE ============\n"); 
    show_pfn(&lruvec->lists[LRU_INACTIVE_FILE]); 
    lru = LRU_INACTIVE_FILE;
    printk(KERN_INFO "%ld\n",lruvec_lru_size(lruvec,lru,MAX_NR_ZONES));

    printk("========== LRU_ACTIVE_ANON ============\n"); 
    show_pfn(&lruvec->lists[LRU_ACTIVE_ANON]); 
    lru = LRU_ACTIVE_ANON;
    printk(KERN_INFO "%ld\n",lruvec_lru_size(lruvec,lru,MAX_NR_ZONES));

    printk("========== LRU_INACTIVE_ANON ============\n"); 
    show_pfn(&lruvec->lists[LRU_INACTIVE_ANON]); 
    lru = LRU_INACTIVE_ANON;
    printk(KERN_INFO "%ld\n",lruvec_lru_size(lruvec,lru,MAX_NR_ZONES));

    spin_unlock_irq(&lruvec->lru_lock);
  }
  return 1;
}