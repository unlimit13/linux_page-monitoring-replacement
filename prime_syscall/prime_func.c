/* Start of my_func.c */
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <asm/uaccess.h>
#include <linux/export.h>

static int is_prime(int num)
{
  int i = 0;
  int last = int_sqrt(num);
  if(num == 1 || num == 0) return 0;
  for (i = 2; i <= last; i++) //i를 2부터 last까지 1씩 증가시키며 반복 수행
  {
      if ((num%i) == 0) //n을 i로 나누었을때 나머지가 0이면(즉, i는 n의 약수가 아님)
      {
        return 0; //소수가 아니므로 0반환(i가 약수이므로 n은 소수가 아님)
      }
  }
  return 1; //1~last(자기자신/2)사이에 약수가 없으므로 소수임
}

SYSCALL_DEFINE2(prime_syscall,int,Maxsize,int*,numarr)
{
    
    int kernel_cnt=0;
    int* test_arr;
    int kernel_maxsize= Maxsize;
    test_arr = kmalloc(sizeof(int)*kernel_maxsize, GFP_KERNEL);
    
    int ret;
    ret = copy_from_user(test_arr,numarr,sizeof(int)*kernel_maxsize);
    int i;
    for(i=0;i<kernel_maxsize;i++){
        if(is_prime(test_arr[i])){
          kernel_cnt++;
        }
    }
    
    return kernel_cnt;
}

