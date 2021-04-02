#include <Python.h>

/**
 * print_python_list - prints info about python list object
 * @p: pointer to PyObject
 */
void print_python_list(PyObject *p)
{
	printf("[*] Python list info\n");
	if (PyList_Check(p))
	{
		Py_ssize_t size = PyList_Size(p);
		printf("[*] Size of the Python List = %ld\n", size);
		printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);
		for (Py_ssize_t i = 0; i < size; ++i)
			printf("Element %ld: %s\n", i,
			       Py_TYPE(PyList_GET_ITEM(p, i))->tp_name);
	}
	else
		puts("  [ERROR] Invalid List Object");
}
