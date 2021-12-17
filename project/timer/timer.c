/*
 * Deferred Work
 *
 * Exercise #1, #2: simple timer
 */

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
#include <linux/types.h>
#include <trace/events/vmscan.h>
#include <linux/mmzone.h>
#include <linux/memcontrol.h>
#include <linux/swap.h>

MODULE_DESCRIPTION("Counter based algorithm helper");
MODULE_AUTHOR("Team2");
MODULE_LICENSE("GPL");

#define TIMER_TIMEOUT	1
#define TIMER_FLAG 		0

static struct timer_list timer_file_act;
static struct timer_list timer_file_inact;
static struct timer_list timer_anon_act;
static struct timer_list timer_anon_inact;

static struct pglist_data *current_pglist = NULL;
static struct lruvec *lruvec = NULL;
static struct mem_cgroup *memcg = NULL;


static void timer_handler_file_act(struct timer_list *tl)
{
  	struct page *p = NULL;
	struct list_head *i, *n;
	list_for_each_safe(i, n, &lruvec->lists[LRU_ACTIVE_FILE]) {
		p = list_entry(i, struct page, lru);
    if(PageReferenced(p)){
	  if(p->ref_counter.counter!=0x7ffffff){
      	atomic_inc(&p->ref_counter);
	  }
      ClearPageReferenced(p);
    }
    else{
	  if(p->ref_counter.counter>0){
      	atomic_dec(&p->ref_counter);
	  }
    }
	}	

	mod_timer(&timer_file_act, jiffies+TIMER_TIMEOUT*HZ);
}
static void timer_handler_file_inact(struct timer_list *tl)
{
	struct page *p = NULL;
	struct list_head *i, *n;
	list_for_each_safe(i, n, &lruvec->lists[LRU_INACTIVE_FILE]) {
		p = list_entry(i, struct page, lru);
    if(PageReferenced(p)){
	  if(p->ref_counter.counter!=0x7ffffff){
      	atomic_inc(&p->ref_counter);
	  }
      ClearPageReferenced(p);
    }
    else{
	  if(p->ref_counter.counter>0){
      	atomic_dec(&p->ref_counter);
	  }
    }
	}	

	mod_timer(&timer_file_inact, jiffies+TIMER_TIMEOUT*HZ);
}
static void timer_handler_anon_act(struct timer_list *tl)
{
	struct page *p = NULL;
	struct list_head *i, *n;
	list_for_each_safe(i, n, &lruvec->lists[LRU_ACTIVE_ANON]) {
		p = list_entry(i, struct page, lru);
    if(PageReferenced(p)){
	  if(p->ref_counter.counter!=0x7ffffff){
      	atomic_inc(&p->ref_counter);
	  }
      ClearPageReferenced(p);
    }
    else{
	  if(p->ref_counter.counter>0){
      	atomic_dec(&p->ref_counter);
	  }
    }
	}	

	mod_timer(&timer_anon_act, jiffies+TIMER_TIMEOUT*HZ);
}
static void timer_handler_anon_inact(struct timer_list *tl)
{
	struct page *p = NULL;
	struct list_head *i, *n;
	list_for_each_safe(i, n, &lruvec->lists[LRU_INACTIVE_ANON]) {
		p = list_entry(i, struct page, lru);
    if(PageReferenced(p)){
	  if(p->ref_counter.counter!=0x7ffffff){
      	atomic_inc(&p->ref_counter);
	  }
      ClearPageReferenced(p);
    }
    else{
	  if(p->ref_counter.counter>0){
      	atomic_dec(&p->ref_counter);
	  }
    }
	}	

	mod_timer(&timer_anon_inact, jiffies+TIMER_TIMEOUT*HZ);
}
static int __init timer_init(void)
{
	pr_info("[timer_init] Init module\n");

	current_pglist = NODE_DATA(0);

	if(current_pglist->node_present_pages==0){
      printk(KERN_ALERT "No page in node-0\n");
      return 0;
    }

	memcg = get_mem_cgroup_from_mm(NULL);
    lruvec = mem_cgroup_lruvec(memcg,current_pglist);

	timer_setup(&timer_file_act, timer_handler_file_act, TIMER_FLAG);
	timer_setup(&timer_file_inact, timer_handler_file_inact, TIMER_FLAG);
	timer_setup(&timer_anon_act, timer_handler_anon_act, TIMER_FLAG);
	timer_setup(&timer_anon_inact, timer_handler_anon_inact, TIMER_FLAG);

	mod_timer(&timer_file_act, jiffies+TIMER_TIMEOUT*HZ);
	mod_timer(&timer_file_inact, jiffies+TIMER_TIMEOUT*HZ);
	mod_timer(&timer_anon_act, jiffies+TIMER_TIMEOUT*HZ);
	mod_timer(&timer_anon_inact, jiffies+TIMER_TIMEOUT*HZ);

	return 0;
}

static void __exit timer_exit(void)
{
	pr_info("[timer_exit] Exit module\n");

	del_timer_sync(&timer_file_act);
	del_timer_sync(&timer_file_inact);
	del_timer_sync(&timer_anon_act);
	del_timer_sync(&timer_anon_inact);
}

module_init(timer_init);
module_exit(timer_exit);
