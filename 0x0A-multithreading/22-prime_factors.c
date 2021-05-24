#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multithreading.h"

static pthread_mutex_t task_lock;

/**
  * construct_task_mutex - builds mutex before main function runs using a
  * *		      GCC constructor attribute
  */
__attribute__((constructor))void construct_task_mutex(void)
{
	pthread_mutex_init(&task_lock, NULL);
}

/**
  * destroy_task_mutex - destroys mutex after main function runs using a
  * *		      GCC destructor attribute
  */
__attribute__((destructor))void destroy_task_mutex(void)
{
	pthread_mutex_destroy(&task_lock);
}



/**
 * create_task - desc
 * @entry: entry
 * @param: param
 * Return: task_t pointer
 */
task_t *create_task(task_entry_t entry, void *param)
{C99(
	task_t src = (task_t){entry, param, PENDING, NULL, task_lock};
	task_t *dst = calloc(1, sizeof(*dst));
	if (!dst) return (NULL);
	return (memcpy(dst, &src, sizeof(src)));
);}

/**
 * destroy_task - desc
 * @task:  task_t pointer
 */
void destroy_task(task_t *task)
{
	if (!task) return;
	if (task->result)
	{
		list_destroy((list_t *) task->result, free);
		free((list_t *) task->result);
	}
	free(task);
}

/**
 * exec_tasks - execute tasks
 * @tasks: list_t
 * Return: NULL
 */
void *exec_tasks(list_t const *tasks)
{C99(
	if (!tasks) return (NULL);
	node_t *node = tasks->head;
	size_t i = 0;
	for (; node && i < tasks->size; i++, node = node->next)
	{
		task_t* t = (task_t *)node->content;
		pthread_mutex_lock(&task_lock);
		if (t->status == PENDING)
		{
			t->status = STARTED;
			pthread_mutex_unlock(&task_lock);
			tprintf("[%02lu] Started\n", i);
			t->result = t->entry(t->param);
			t->status = t->result ? SUCCESS : FAILURE;
			tprintf("[%02lu] %s\n", i, t->result ? "Success" : "Failure");
		}
		else
			pthread_mutex_unlock(&task_lock);
	}
	return (NULL);
);}
