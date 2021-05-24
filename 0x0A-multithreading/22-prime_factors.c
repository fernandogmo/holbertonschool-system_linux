#include <stdio.h>
#include <stdlib.h>
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
{
	task_t *t = malloc(sizeof(*t));
	if (!t) return (NULL);
	t->entry = entry;
	t->param = param;
	t->status = PENDING;
	t->result = NULL;
	return (t);
}

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
	int i = 0;
	while (node)
	{
		task_t* task = (task_t *) node->content;
		if (task->status == PENDING)
		{
			task->status = STARTED;
			tprintf("[%02d] Started\n", i);
			task->result = (void *)
				(((list_t *(*) (char const *)) task->entry)((char const *) task->param));
			tprintf("[%02d] Success\n", i);
			if (task->result == NULL)
				task->status = FAILURE;
			else
				task->status = SUCCESS;
		}
		node = node->next;
		i++;
	}
	return (NULL);
);}
