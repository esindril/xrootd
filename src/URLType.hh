#ifndef URLTYPE_HH_
#define URLTYPE_HH_

#include <Python.h>
#include "structmember.h"

namespace XrdClBind
{
    typedef struct {
        PyObject_HEAD
        /* Type-specific fields */
        XrdCl::URL *url;
    } URL;

    static void URL_dealloc(URL *self)
    {
        delete self->url;
        self->ob_type->tp_free((PyObject*) self);
    }

    static int URL_init(URL *self, PyObject *args, PyObject *kwds) {

        const char *url;
        static char *kwlist[] = {"url", NULL};

        if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &url))
            return -1;

        if (url) {
            self->url = new XrdCl::URL(url);
        }

        return 0;
    }

    static PyObject* URL_str(URL *url)
    {
        return PyString_FromString(url->url->GetURL().c_str());
    }

    static PyObject* IsValid(URL *self)
    {
        return Py_BuildValue("O", PyBool_FromLong(self->url->IsValid()));
    }

    static PyObject* GetHostId(URL *self)
    {
        return Py_BuildValue("S", PyString_FromString(self->url->GetHostId().c_str()));
    }

    static PyObject* GetProtocol(URL *self)
    {
        return Py_BuildValue("S", PyString_FromString(self->url->GetProtocol().c_str()));
    }

    static PyObject* SetProtocol(URL *self, PyObject *args)
    {
        const char *protocol;
        if (!PyArg_ParseTuple(args, "s", &protocol))
            return NULL;
        self->url->SetProtocol(std::string(protocol));
        Py_RETURN_NONE;
    }

    static PyObject* GetUserName(URL *self)
    {
        return Py_BuildValue("S", PyString_FromString(self->url->GetUserName().c_str()));
    }

    static PyObject* SetUserName(URL *self, PyObject *args)
    {
        const char *username;
        if (!PyArg_ParseTuple(args, "s", &username))
            return NULL;
        self->url->SetUserName(std::string(username));
        Py_RETURN_NONE ;
    }

    static PyObject* GetPassword(URL *self)
    {
        return Py_BuildValue("S", PyString_FromString(self->url->GetPassword().c_str()));
    }

    static PyObject* SetPassword(URL *self, PyObject *args)
    {
        const char *password;
        if (!PyArg_ParseTuple(args, "s", &password))
            return NULL;
        self->url->SetPassword(std::string(password));
        Py_RETURN_NONE;
    }

    static PyObject* GetHostName(URL *self)
    {
        return Py_BuildValue("S", PyString_FromString(self->url->GetHostName().c_str()));
    }

    static PyObject* SetHostName(URL *self, PyObject *args)
    {
        const char *hostname;
        if (!PyArg_ParseTuple(args, "s", &hostname))
            return NULL;
        self->url->SetHostName(std::string(hostname));
        Py_RETURN_NONE;
    }

    static PyObject* GetPort(URL *self)
    {
        return Py_BuildValue("i", self->url->GetPort());
    }

    static PyObject* SetPort(URL *self, PyObject *args)
    {
        int port;
        if (!PyArg_ParseTuple(args, "i", &port))
            return NULL;
        self->url->SetPort(port);
        Py_RETURN_NONE;
    }

    static PyObject* GetPath(URL *self)
    {
        return Py_BuildValue("S", PyString_FromString(self->url->GetPath().c_str()));
    }

    static PyObject* SetPath(URL *self, PyObject *args)
    {
        const char *path;
        if (!PyArg_ParseTuple(args, "s", &path))
            return NULL;
        self->url->SetPath(std::string(path));
        Py_RETURN_NONE;
    }

    static PyObject* GetPathWithParams(URL *self)
    {
        return Py_BuildValue("S", PyString_FromString(self->url->GetPathWithParams().c_str()));
    }

    static PyObject* Clear(URL *self)
    {
        self->url->Clear();
        Py_RETURN_NONE;
    }

    static PyMemberDef URLMembers[] = {
        {NULL}  /* Sentinel */
    };

    static PyMethodDef URLMethods[] = {
        { "IsValid", (PyCFunction) IsValid, METH_NOARGS,
          "Return the validity of the URL" },
        { "GetHostId", (PyCFunction) GetHostId, METH_NOARGS,
          "Get the host part of the URL (user:password@host:port)" },
        { "GetProtocol", (PyCFunction) GetProtocol, METH_NOARGS,
          "Get the protocol" },
        { "SetProtocol", (PyCFunction) SetProtocol, METH_VARARGS,
          "Set protocol" },
        { "GetUserName", (PyCFunction) GetUserName, METH_NOARGS,
          "Get the username" },
        { "SetUserName", (PyCFunction) SetUserName, METH_VARARGS,
          "Set the username" },
        { "GetPassword", (PyCFunction) GetPassword, METH_NOARGS,
          "Get the password" },
        { "SetPassword", (PyCFunction) SetPassword, METH_VARARGS,
          "Set the password" },
        { "GetHostName", (PyCFunction) GetHostName, METH_NOARGS,
          "Get the name of the target host" },
        { "SetHostName", (PyCFunction) SetHostName, METH_VARARGS,
          "Set the host name" },
        { "GetPort", (PyCFunction) GetPort, METH_NOARGS,
          "Get the target port" },
        { "SetPort", (PyCFunction) SetPort, METH_VARARGS,
          "Set port" },
        { "GetPath", (PyCFunction) GetPath, METH_NOARGS,
          "Get the path" },
        { "SetPath", (PyCFunction) SetPath, METH_VARARGS,
          "Set the path" },
        { "GetPathWithParams", (PyCFunction) GetPathWithParams, METH_NOARGS,
          "Get the path with params" },
        { "Clear", (PyCFunction) Clear, METH_NOARGS,
          "Clear the url" },
        { NULL } /* Sentinel */
    };

    static PyTypeObject URLType = {
        PyObject_HEAD_INIT(NULL)
        0,                                          /* ob_size */
        "client.URL",                               /* tp_name */
        sizeof(URL),                                /* tp_basicsize */
        0,                                          /* tp_itemsize */
        (destructor) URL_dealloc,                   /* tp_dealloc */
        0,                                          /* tp_print */
        0,                                          /* tp_getattr */
        0,                                          /* tp_setattr */
        0,                                          /* tp_compare */
        0,                                          /* tp_repr */
        0,                                          /* tp_as_number */
        0,                                          /* tp_as_sequence */
        0,                                          /* tp_as_mapping */
        0,                                          /* tp_hash */
        0,                                          /* tp_call */
        (reprfunc) URL_str,                         /* tp_str */
        0,                                          /* tp_getattro */
        0,                                          /* tp_setattro */
        0,                                          /* tp_as_buffer */
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,   /* tp_flags */
        "URL object",                               /* tp_doc */
        0,                                          /* tp_traverse */
        0,                                          /* tp_clear */
        0,                                          /* tp_richcompare */
        0,                                          /* tp_weaklistoffset */
        0,                                          /* tp_iter */
        0,                                          /* tp_iternext */
        URLMethods,                                 /* tp_methods */
        URLMembers,                                 /* tp_members */
        0,                                          /* tp_getset */
        0,                                          /* tp_base */
        0,                                          /* tp_dict */
        0,                                          /* tp_descr_get */
        0,                                          /* tp_descr_set */
        0,                                          /* tp_dictoffset */
        (initproc) URL_init,                        /* tp_init */
    };
}

#endif /* URLTYPE_HH_ */
