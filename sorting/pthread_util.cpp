
#include"pthread_util.h"

void PthreadCall(const char* label, int result) // 不需要修改字符数组，const
{
	if (result)
	{
		fprintf(stderr, "pthread %s: %s\n", label, strerror(result));
		abort();
	}
}
