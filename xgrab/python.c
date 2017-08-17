#include <Python.h>
#include <numpy/ndarrayobject.h>
#include "xgrab.h"

#if PY_MAJOR_VERSION >= 3
#define IS_PY3K
#endif 


static PyObject* py_grab_screen(PyObject *self, PyObject *args, PyObject *kwargs)
{
    unsigned int x, y, width, height;
    static char *kwlist[] = {"x", "y", "width", "height", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "IIII|IIII",
                                     kwlist, &x, &y, &width, &height)) {
        return NULL;
    }

    const size_t buffer_size = width * height * 3;
    uint8_t *buffer = malloc(buffer_size);

    grab_screen(x, y, width, height, buffer);

    npy_intp dims[3] = { height, width, 3 };
    PyObject *arr = PyArray_SimpleNewFromData(3, dims, NPY_UINT8, buffer);
    PyArray_ENABLEFLAGS((PyArrayObject *) arr, NPY_ARRAY_OWNDATA);
    return arr;
}

static PyMethodDef _methods[] = {
    {"grab_screen", (PyCFunction) py_grab_screen, METH_VARARGS | METH_KEYWORDS, "Grab screen."},
    {NULL, NULL, 0, NULL}
};

#ifdef IS_PY3K
static struct PyModuleDef _module_def = {
    PyModuleDef_HEAD_INIT,
    "xgrab",
    NULL,   // module documentation
    -1,
    _methods
};
#endif

#ifdef IS_PY3K
PyMODINIT_FUNC PyInit_xgrab()
{
    PyObject *module = PyModule_Create(&_module_def);
    if (module == NULL) return NULL;
    import_array();
    return module;
}
#else
void initxgrab()
{
    Py_InitModule("xgrab", _methods);
    import_array();
}
#endif
