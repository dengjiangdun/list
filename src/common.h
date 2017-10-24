#ifndef _COMMON_H_
#define _COMMON_H_

#define return_if_fail(value) \
	if (value) { \
		printf("The parameter is unvalid, please check it. [%s, %d]\n", __func__, __LINE__); \
		return; \
	}

#define return_value_if_fail(value, ret) \
	if (value) { \
		printf("The parameter is unvalid, please check it. [%s, %d]\n", __func__, __LINE__); \
		return ret; \
	}

#define return_NULL_if_malloc_fail(value)\
	if (value) {\
		printf("Failed to apply for space.[%s,%d]\n",__func__, __LINE__); \
		return NULL;\
	}

#endif
