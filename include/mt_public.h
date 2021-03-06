/*
 * Copyright (C) zhoulv2000@163.com
 */

#ifndef _MT_PUBLIC_H_INCLUDED_
#define _MT_PUBLIC_H_INCLUDED_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <math.h>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <errno.h>
#include <unistd.h>

#define MTHREAD_NAMESPACE_BEGIN namespace mthread {
#define MTHREAD_NAMESPACE_END   }
#define MTHREAD_NAMESPACE_USING using namespace mthread;

#define mt_min(x,y) (((x)<(y))?(x):(y))
#define mt_max(x,y) (((x)<(y))?(x):(y))
#define mt_gettid() pthread_self()
#define mt_maxint   0x7fffffff
#define mt_maxtime  2177280000

#if defined(__APPLE__)
#if __GNUC__ == 2 && __GNUC_MINOR__ < 96 
#define __builtin_expect(x, expected_value) (x) 
#endif
#define likely(x)   __builtin_expect((x),1) 
#define unlikely(x) __builtin_expect((x),0)
#endif

// 安全DELETE
#define safe_delete(ptr) do {               \
    if (ptr != NULL) delete ptr;            \
    ptr = NULL;                             \
} while(0)

// 安全DELETE数组
#define safe_delete_arr(ptr) do {           \
    if (ptr != NULL) delete [] ptr;         \
    ptr = NULL;                             \
} while(0)

// 安全的Free
#define safe_free(ptr) do {                 \
    if (ptr != NULL) free(ptr);         \
    ptr = NULL;                             \
} while(0)

// 对应的错误信息
#define MT_ERROR      -1
#define MT_UNKOWN     -2
#define MT_BUSY       -3
#define MT_DONE       -4
#define MT_DECLINED   -5
#define MT_ABORT      -6

#define MT_NONE 		0
#define MT_READABLE 	1 // EPOLLIN
#define	MT_WRITEABLE 	2 // EPOLLOUT
#define MT_EVERR		4 // ERR, HUP

// 判断是否使用协程
#define MT_HOOK_MAX_FD      65535 * 2
#define MT_FD_FLG_NOUSE     0x0
#define MT_FD_FLG_INUSE     0x1
#define MT_FD_FLG_UNBLOCK   0x2
#define MT_LISTEN_LEN       1024

// 边界对齐
#define MT_ALGIN(size)      ((size) + (8-(size)%8))

// 回调函数
typedef void (*ThreadRunCallback)(void*);
typedef unsigned int (*TcpCheckMsgLenCallback)(void* buf, int len);
typedef void (*FrameCallback)(void*);

#if TRACE
#define LOG_TRACE(fmt, args...) fprintf(stdout, (char*)"[TRACE][%ld][%ld][%-10s][%-4d][%-10s]"fmt"\n", mt_gettid(), mt_get_threadid(), __FILE__, __LINE__, __FUNCTION__, ##args);
#define LOG_DEBUG(fmt, args...) fprintf(stdout, (char*)"[DEBUG][%ld][%ld][%-10s][%-4d][%-10s]"fmt"\n", mt_gettid(), mt_get_threadid(), __FILE__, __LINE__, __FUNCTION__, ##args);
#define LOG_WARN(fmt, args...) fprintf(stdout, (char*)"[WARN][%ld][%ld][%-10s][%-4d][%-10s]"fmt"\n", mt_gettid(), mt_get_threadid(), __FILE__, __LINE__, __FUNCTION__, ##args);
#define LOG_ERROR(fmt, args...) fprintf(stdout, (char*)"[ERROR][%ld][%ld][%-10s][%-4d][%-10s]"fmt"\n", mt_gettid(), mt_get_threadid(), __FILE__, __LINE__, __FUNCTION__, ##args);
#define LOG_CHECK_FUNCTION	fprintf(stdout, (char*)"[TRACE][%ld][%ld][%-10s][%-4d][%-10s] check function ...\n", mt_gettid(), mt_get_threadid(), __FILE__, __LINE__, __FUNCTION__);
#elif DEBUG
#define LOG_TRACE(fmt, args...)
#define LOG_DEBUG(fmt, args...) fprintf(stdout, (char*)"[DEBUG][%ld][%ld][%-10s][%-4d][%-10s]"fmt"\n", mt_gettid(), mt_get_threadid(), __FILE__, __LINE__, __FUNCTION__, ##args);
#define LOG_WARN(fmt, args...) fprintf(stdout, (char*)"[WARN][%ld][%ld][%-10s][%-4d][%-10s]"fmt"\n", mt_gettid(), mt_get_threadid(), __FILE__, __LINE__, __FUNCTION__, ##args);
#define LOG_ERROR(fmt, args...) fprintf(stdout, (char*)"[ERROR][%ld][%ld][%-10s][%-4d][%-10s]"fmt"\n", mt_gettid(), mt_get_threadid(), __FILE__, __LINE__, __FUNCTION__, ##args);
#define LOG_CHECK_FUNCTION fprintf(stdout, (char*)"[TRACE][%ld][%ld][%-10s][%-4d][%-10s] check function ...\n", mt_gettid(), mt_get_threadid(), __FILE__, __LINE__, __FUNCTION__);
#else
#define LOG_TRACE(fmt, args...)
#define LOG_DEBUG(fmt, args...)
#define LOG_WARN(fmt, args...) fprintf(stdout, (char*)"[WARN][%ld][%ld][%-10s][%-4d][%-10s]"fmt"\n", mt_gettid(), mt_get_threadid(), __FILE__, __LINE__, __FUNCTION__, ##args);
#define LOG_ERROR(fmt, args...) fprintf(stdout, (char*)"[ERROR][%ld][%ld][%-10s][%-4d][%-10s]"fmt"\n", mt_gettid(), mt_get_threadid(), __FILE__, __LINE__, __FUNCTION__, ##args);
#define LOG_CHECK_FUNCTION
#endif

#define MT_ASSERT(eq)

#endif