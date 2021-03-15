/*
 *                                                                          
 * Copyright (c)  :2019-05-7  Grand Vision Design Systems Inc.   /
 * Permission is hereby granted, free of charge, to any person obtaining  /
 * a copy of this software and associated documentation files (the   /
 * Software), to deal in the Software without restriction, including   /
 * without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to   /
 * permit persons to whom the Software is furnished to do so, subject to   /
 * the following conditions:  /
 * The above copyright notice and this permission notice shall be included   /
 * in all copies or substantial portions of the Software.  /
 *                                                                          
 * THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND,  /
 * EXPRESS OR IPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF  /
 * ERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  /
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   /
 * CLAI, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  /
 * TORT OR OTHERWISE, ARISING FRO, OUT OF OR IN CONNECTION WITH THE   /
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  /
 *  
 *
 */

/*
 * =============================================================================
 *
 * @Filename	:  topsort.c
 *
 * @Author		:  adrian.yan (), yehe.yan@byavs.com
 *
 * @Version		:  1.0
 *
 * @Created		:  2021年03月15日 15时45分53秒
 *
 * @Revision	:  none
 *
 * @Compiler	:  csky-linux-gcc
 *
 * 
 * @Company		:  Grand Vision Technology Co., Ltd.
 *
 * @Description	: 
 *
 *
 *
 * @Modification History: 
 *
 *
 * =============================================================================
 */
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>



#include <stdio.h>
#include <stdlib.h>

void topologicalSort(adjlist GL,int n)
{
	int i,j,k,top,m=0;      /* m用来统计拓扑序列中的顶点数*/
	struct edgenode *p;		/* 单链表*/
	int *d=(int *)malloc(n*sizeof(int));  /* 定义存储图中每个顶点
												入度的一维整形数组d
												*/
	for(i=0;i<n;i++){
		d[i]=0;
	}

	/*利用数组d中的对应元素统计出图中每个顶点的入度*/
	for(i=0;i<n;i++){
		p=GL[i];
		while(p!=NULL){
			j=p->adjvex;
			d[j]++;
			p=p->next;
		}
	}

	top=-1;					/*	初始化用于链接入度为0的元素的栈的栈顶指针为-1*/
	for(i=0;i<n;i++){		/*	建立初始化栈*/
		if(d[i]==0){
			d[i]=top;
			top=i;
		}			
	}

	/*每循环一次删除一个顶点及所有以它为弧尾的顶点入度减一*/
	while(top!=-1){
		j=top;				/*	j的值为一个入度为0的顶点序号*/
		top=d[top];			/*	得到下一个入度为0的顶点下标*/
		printf("%d",j);		/*	输出一个顶点*/
		m++;				/*	输出的顶点个数加1*/
		p=GL[j];			/*	p指向vj顶点邻接表的第一个节点，目的是开始把以它为
								弧尾的顶点入度减一
								*/
		while(p!=NULL){
			k=p->adjvex;	/*	vk是vj的一个邻接点*/
			d[k]--;			/*	vk入度减一*/
			if(d[k]==0){	/*	把入度为0的元素进栈，对应着图看更容易明白*/
				d[k]=top;
				top=k;
			}
			p=p->next;
		}
	}
	if(m<n){
		printf("The graph has cycle\r\n")；
	}
	free(d);				/*	删除动态分配的数组d*/
}
