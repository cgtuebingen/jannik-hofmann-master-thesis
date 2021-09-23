/*
This file fa2util.c is part of NeuralVisUAL.

NeuralVisUAL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

NeuralVisUAL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with NeuralVisUAL.  If not, see <https://www.gnu.org/licenses/>.
*/

/* BEGIN: Cython Metadata
{
    "distutils": {
        "name": "fa2.fa2util",
        "sources": [
            "E:\\Nextcloud\\Jannik\\Documents\\Studies\\MA\\Python Interaction Scripts\\forceatlas2\\fa2\\fa2util.py"
        ]
    },
    "module_name": "fa2.fa2util"
}
END: Cython Metadata */

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#ifndef Py_PYTHON_H
    #error Python headers needed to compile C extensions, please install development version of Python.
#elif PY_VERSION_HEX < 0x02060000 || (0x03000000 <= PY_VERSION_HEX && PY_VERSION_HEX < 0x03030000)
    #error Cython requires Python 2.6+ or Python 3.3+.
#else
#define CYTHON_ABI "0_29_22"
#define CYTHON_HEX_VERSION 0x001D16F0
#define CYTHON_FUTURE_DIVISION 0
#include <stddef.h>
#ifndef offsetof
  #define offsetof(type, member) ( (size_t) & ((type*)0) -> member )
#endif
#if !defined(WIN32) && !defined(MS_WINDOWS)
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
  #ifndef __fastcall
    #define __fastcall
  #endif
#endif
#ifndef DL_IMPORT
  #define DL_IMPORT(t) t
#endif
#ifndef DL_EXPORT
  #define DL_EXPORT(t) t
#endif
#define __PYX_COMMA ,
#ifndef HAVE_LONG_LONG
  #if PY_VERSION_HEX >= 0x02070000
    #define HAVE_LONG_LONG
  #endif
#endif
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#ifndef Py_HUGE_VAL
  #define Py_HUGE_VAL HUGE_VAL
#endif
#ifdef PYPY_VERSION
  #define CYTHON_COMPILING_IN_PYPY 1
  #define CYTHON_COMPILING_IN_PYSTON 0
  #define CYTHON_COMPILING_IN_CPYTHON 0
  #undef CYTHON_USE_TYPE_SLOTS
  #define CYTHON_USE_TYPE_SLOTS 0
  #undef CYTHON_USE_PYTYPE_LOOKUP
  #define CYTHON_USE_PYTYPE_LOOKUP 0
  #if PY_VERSION_HEX < 0x03050000
    #undef CYTHON_USE_ASYNC_SLOTS
    #define CYTHON_USE_ASYNC_SLOTS 0
  #elif !defined(CYTHON_USE_ASYNC_SLOTS)
    #define CYTHON_USE_ASYNC_SLOTS 1
  #endif
  #undef CYTHON_USE_PYLIST_INTERNALS
  #define CYTHON_USE_PYLIST_INTERNALS 0
  #undef CYTHON_USE_UNICODE_INTERNALS
  #define CYTHON_USE_UNICODE_INTERNALS 0
  #undef CYTHON_USE_UNICODE_WRITER
  #define CYTHON_USE_UNICODE_WRITER 0
  #undef CYTHON_USE_PYLONG_INTERNALS
  #define CYTHON_USE_PYLONG_INTERNALS 0
  #undef CYTHON_AVOID_BORROWED_REFS
  #define CYTHON_AVOID_BORROWED_REFS 1
  #undef CYTHON_ASSUME_SAFE_MACROS
  #define CYTHON_ASSUME_SAFE_MACROS 0
  #undef CYTHON_UNPACK_METHODS
  #define CYTHON_UNPACK_METHODS 0
  #undef CYTHON_FAST_THREAD_STATE
  #define CYTHON_FAST_THREAD_STATE 0
  #undef CYTHON_FAST_PYCALL
  #define CYTHON_FAST_PYCALL 0
  #undef CYTHON_PEP489_MULTI_PHASE_INIT
  #define CYTHON_PEP489_MULTI_PHASE_INIT 0
  #undef CYTHON_USE_TP_FINALIZE
  #define CYTHON_USE_TP_FINALIZE 0
  #undef CYTHON_USE_DICT_VERSIONS
  #define CYTHON_USE_DICT_VERSIONS 0
  #undef CYTHON_USE_EXC_INFO_STACK
  #define CYTHON_USE_EXC_INFO_STACK 0
#elif defined(PYSTON_VERSION)
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_PYSTON 1
  #define CYTHON_COMPILING_IN_CPYTHON 0
  #ifndef CYTHON_USE_TYPE_SLOTS
    #define CYTHON_USE_TYPE_SLOTS 1
  #endif
  #undef CYTHON_USE_PYTYPE_LOOKUP
  #define CYTHON_USE_PYTYPE_LOOKUP 0
  #undef CYTHON_USE_ASYNC_SLOTS
  #define CYTHON_USE_ASYNC_SLOTS 0
  #undef CYTHON_USE_PYLIST_INTERNALS
  #define CYTHON_USE_PYLIST_INTERNALS 0
  #ifndef CYTHON_USE_UNICODE_INTERNALS
    #define CYTHON_USE_UNICODE_INTERNALS 1
  #endif
  #undef CYTHON_USE_UNICODE_WRITER
  #define CYTHON_USE_UNICODE_WRITER 0
  #undef CYTHON_USE_PYLONG_INTERNALS
  #define CYTHON_USE_PYLONG_INTERNALS 0
  #ifndef CYTHON_AVOID_BORROWED_REFS
    #define CYTHON_AVOID_BORROWED_REFS 0
  #endif
  #ifndef CYTHON_ASSUME_SAFE_MACROS
    #define CYTHON_ASSUME_SAFE_MACROS 1
  #endif
  #ifndef CYTHON_UNPACK_METHODS
    #define CYTHON_UNPACK_METHODS 1
  #endif
  #undef CYTHON_FAST_THREAD_STATE
  #define CYTHON_FAST_THREAD_STATE 0
  #undef CYTHON_FAST_PYCALL
  #define CYTHON_FAST_PYCALL 0
  #undef CYTHON_PEP489_MULTI_PHASE_INIT
  #define CYTHON_PEP489_MULTI_PHASE_INIT 0
  #undef CYTHON_USE_TP_FINALIZE
  #define CYTHON_USE_TP_FINALIZE 0
  #undef CYTHON_USE_DICT_VERSIONS
  #define CYTHON_USE_DICT_VERSIONS 0
  #undef CYTHON_USE_EXC_INFO_STACK
  #define CYTHON_USE_EXC_INFO_STACK 0
#else
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_PYSTON 0
  #define CYTHON_COMPILING_IN_CPYTHON 1
  #ifndef CYTHON_USE_TYPE_SLOTS
    #define CYTHON_USE_TYPE_SLOTS 1
  #endif
  #if PY_VERSION_HEX < 0x02070000
    #undef CYTHON_USE_PYTYPE_LOOKUP
    #define CYTHON_USE_PYTYPE_LOOKUP 0
  #elif !defined(CYTHON_USE_PYTYPE_LOOKUP)
    #define CYTHON_USE_PYTYPE_LOOKUP 1
  #endif
  #if PY_MAJOR_VERSION < 3
    #undef CYTHON_USE_ASYNC_SLOTS
    #define CYTHON_USE_ASYNC_SLOTS 0
  #elif !defined(CYTHON_USE_ASYNC_SLOTS)
    #define CYTHON_USE_ASYNC_SLOTS 1
  #endif
  #if PY_VERSION_HEX < 0x02070000
    #undef CYTHON_USE_PYLONG_INTERNALS
    #define CYTHON_USE_PYLONG_INTERNALS 0
  #elif !defined(CYTHON_USE_PYLONG_INTERNALS)
    #define CYTHON_USE_PYLONG_INTERNALS 1
  #endif
  #ifndef CYTHON_USE_PYLIST_INTERNALS
    #define CYTHON_USE_PYLIST_INTERNALS 1
  #endif
  #ifndef CYTHON_USE_UNICODE_INTERNALS
    #define CYTHON_USE_UNICODE_INTERNALS 1
  #endif
  #if PY_VERSION_HEX < 0x030300F0
    #undef CYTHON_USE_UNICODE_WRITER
    #define CYTHON_USE_UNICODE_WRITER 0
  #elif !defined(CYTHON_USE_UNICODE_WRITER)
    #define CYTHON_USE_UNICODE_WRITER 1
  #endif
  #ifndef CYTHON_AVOID_BORROWED_REFS
    #define CYTHON_AVOID_BORROWED_REFS 0
  #endif
  #ifndef CYTHON_ASSUME_SAFE_MACROS
    #define CYTHON_ASSUME_SAFE_MACROS 1
  #endif
  #ifndef CYTHON_UNPACK_METHODS
    #define CYTHON_UNPACK_METHODS 1
  #endif
  #ifndef CYTHON_FAST_THREAD_STATE
    #define CYTHON_FAST_THREAD_STATE 1
  #endif
  #ifndef CYTHON_FAST_PYCALL
    #define CYTHON_FAST_PYCALL 1
  #endif
  #ifndef CYTHON_PEP489_MULTI_PHASE_INIT
    #define CYTHON_PEP489_MULTI_PHASE_INIT (PY_VERSION_HEX >= 0x03050000)
  #endif
  #ifndef CYTHON_USE_TP_FINALIZE
    #define CYTHON_USE_TP_FINALIZE (PY_VERSION_HEX >= 0x030400a1)
  #endif
  #ifndef CYTHON_USE_DICT_VERSIONS
    #define CYTHON_USE_DICT_VERSIONS (PY_VERSION_HEX >= 0x030600B1)
  #endif
  #ifndef CYTHON_USE_EXC_INFO_STACK
    #define CYTHON_USE_EXC_INFO_STACK (PY_VERSION_HEX >= 0x030700A3)
  #endif
#endif
#if !defined(CYTHON_FAST_PYCCALL)
#define CYTHON_FAST_PYCCALL  (CYTHON_FAST_PYCALL && PY_VERSION_HEX >= 0x030600B1)
#endif
#if CYTHON_USE_PYLONG_INTERNALS
  #include "longintrepr.h"
  #undef SHIFT
  #undef BASE
  #undef MASK
  #ifdef SIZEOF_VOID_P
    enum { __pyx_check_sizeof_voidp = 1 / (int)(SIZEOF_VOID_P == sizeof(void*)) };
  #endif
#endif
#ifndef __has_attribute
  #define __has_attribute(x) 0
#endif
#ifndef __has_cpp_attribute
  #define __has_cpp_attribute(x) 0
#endif
#ifndef CYTHON_RESTRICT
  #if defined(__GNUC__)
    #define CYTHON_RESTRICT __restrict__
  #elif defined(_MSC_VER) && _MSC_VER >= 1400
    #define CYTHON_RESTRICT __restrict
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_RESTRICT restrict
  #else
    #define CYTHON_RESTRICT
  #endif
#endif
#ifndef CYTHON_UNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define CYTHON_UNUSED __attribute__ ((__unused__))
#   else
#     define CYTHON_UNUSED
#   endif
# elif defined(__ICC) || (defined(__INTEL_COMPILER) && !defined(_MSC_VER))
#   define CYTHON_UNUSED __attribute__ ((__unused__))
# else
#   define CYTHON_UNUSED
# endif
#endif
#ifndef CYTHON_MAYBE_UNUSED_VAR
#  if defined(__cplusplus)
     template<class T> void CYTHON_MAYBE_UNUSED_VAR( const T& ) { }
#  else
#    define CYTHON_MAYBE_UNUSED_VAR(x) (void)(x)
#  endif
#endif
#ifndef CYTHON_NCP_UNUSED
# if CYTHON_COMPILING_IN_CPYTHON
#  define CYTHON_NCP_UNUSED
# else
#  define CYTHON_NCP_UNUSED CYTHON_UNUSED
# endif
#endif
#define __Pyx_void_to_None(void_result) ((void)(void_result), Py_INCREF(Py_None), Py_None)
#ifdef _MSC_VER
    #ifndef _MSC_STDINT_H_
        #if _MSC_VER < 1300
           typedef unsigned char     uint8_t;
           typedef unsigned int      uint32_t;
        #else
           typedef unsigned __int8   uint8_t;
           typedef unsigned __int32  uint32_t;
        #endif
    #endif
#else
   #include <stdint.h>
#endif
#ifndef CYTHON_FALLTHROUGH
  #if defined(__cplusplus) && __cplusplus >= 201103L
    #if __has_cpp_attribute(fallthrough)
      #define CYTHON_FALLTHROUGH [[fallthrough]]
    #elif __has_cpp_attribute(clang::fallthrough)
      #define CYTHON_FALLTHROUGH [[clang::fallthrough]]
    #elif __has_cpp_attribute(gnu::fallthrough)
      #define CYTHON_FALLTHROUGH [[gnu::fallthrough]]
    #endif
  #endif
  #ifndef CYTHON_FALLTHROUGH
    #if __has_attribute(fallthrough)
      #define CYTHON_FALLTHROUGH __attribute__((fallthrough))
    #else
      #define CYTHON_FALLTHROUGH
    #endif
  #endif
  #if defined(__clang__ ) && defined(__apple_build_version__)
    #if __apple_build_version__ < 7000000
      #undef  CYTHON_FALLTHROUGH
      #define CYTHON_FALLTHROUGH
    #endif
  #endif
#endif

#ifndef CYTHON_INLINE
  #if defined(__clang__)
    #define CYTHON_INLINE __inline__ __attribute__ ((__unused__))
  #elif defined(__GNUC__)
    #define CYTHON_INLINE __inline__
  #elif defined(_MSC_VER)
    #define CYTHON_INLINE __inline
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_INLINE inline
  #else
    #define CYTHON_INLINE
  #endif
#endif

#if CYTHON_COMPILING_IN_PYPY && PY_VERSION_HEX < 0x02070600 && !defined(Py_OptimizeFlag)
  #define Py_OptimizeFlag 0
#endif
#define __PYX_BUILD_PY_SSIZE_T "n"
#define CYTHON_FORMAT_SSIZE_T "z"
#if PY_MAJOR_VERSION < 3
  #define __Pyx_BUILTIN_MODULE_NAME "__builtin__"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a+k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyClass_Type
#else
  #define __Pyx_BUILTIN_MODULE_NAME "builtins"
#if PY_VERSION_HEX >= 0x030800A4 && PY_VERSION_HEX < 0x030800B2
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a, 0, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
#else
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
#endif
  #define __Pyx_DefaultClassType PyType_Type
#endif
#ifndef Py_TPFLAGS_CHECKTYPES
  #define Py_TPFLAGS_CHECKTYPES 0
#endif
#ifndef Py_TPFLAGS_HAVE_INDEX
  #define Py_TPFLAGS_HAVE_INDEX 0
#endif
#ifndef Py_TPFLAGS_HAVE_NEWBUFFER
  #define Py_TPFLAGS_HAVE_NEWBUFFER 0
#endif
#ifndef Py_TPFLAGS_HAVE_FINALIZE
  #define Py_TPFLAGS_HAVE_FINALIZE 0
#endif
#ifndef METH_STACKLESS
  #define METH_STACKLESS 0
#endif
#if PY_VERSION_HEX <= 0x030700A3 || !defined(METH_FASTCALL)
  #ifndef METH_FASTCALL
     #define METH_FASTCALL 0x80
  #endif
  typedef PyObject *(*__Pyx_PyCFunctionFast) (PyObject *self, PyObject *const *args, Py_ssize_t nargs);
  typedef PyObject *(*__Pyx_PyCFunctionFastWithKeywords) (PyObject *self, PyObject *const *args,
                                                          Py_ssize_t nargs, PyObject *kwnames);
#else
  #define __Pyx_PyCFunctionFast _PyCFunctionFast
  #define __Pyx_PyCFunctionFastWithKeywords _PyCFunctionFastWithKeywords
#endif
#if CYTHON_FAST_PYCCALL
#define __Pyx_PyFastCFunction_Check(func)\
    ((PyCFunction_Check(func) && (METH_FASTCALL == (PyCFunction_GET_FLAGS(func) & ~(METH_CLASS | METH_STATIC | METH_COEXIST | METH_KEYWORDS | METH_STACKLESS)))))
#else
#define __Pyx_PyFastCFunction_Check(func) 0
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyObject_Malloc)
  #define PyObject_Malloc(s)   PyMem_Malloc(s)
  #define PyObject_Free(p)     PyMem_Free(p)
  #define PyObject_Realloc(p)  PyMem_Realloc(p)
#endif
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX < 0x030400A1
  #define PyMem_RawMalloc(n)           PyMem_Malloc(n)
  #define PyMem_RawRealloc(p, n)       PyMem_Realloc(p, n)
  #define PyMem_RawFree(p)             PyMem_Free(p)
#endif
#if CYTHON_COMPILING_IN_PYSTON
  #define __Pyx_PyCode_HasFreeVars(co)  PyCode_HasFreeVars(co)
  #define __Pyx_PyFrame_SetLineNumber(frame, lineno) PyFrame_SetLineNumber(frame, lineno)
#else
  #define __Pyx_PyCode_HasFreeVars(co)  (PyCode_GetNumFree(co) > 0)
  #define __Pyx_PyFrame_SetLineNumber(frame, lineno)  (frame)->f_lineno = (lineno)
#endif
#if !CYTHON_FAST_THREAD_STATE || PY_VERSION_HEX < 0x02070000
  #define __Pyx_PyThreadState_Current PyThreadState_GET()
#elif PY_VERSION_HEX >= 0x03060000
  #define __Pyx_PyThreadState_Current _PyThreadState_UncheckedGet()
#elif PY_VERSION_HEX >= 0x03000000
  #define __Pyx_PyThreadState_Current PyThreadState_GET()
#else
  #define __Pyx_PyThreadState_Current _PyThreadState_Current
#endif
#if PY_VERSION_HEX < 0x030700A2 && !defined(PyThread_tss_create) && !defined(Py_tss_NEEDS_INIT)
#include "pythread.h"
#define Py_tss_NEEDS_INIT 0
typedef int Py_tss_t;
static CYTHON_INLINE int PyThread_tss_create(Py_tss_t *key) {
  *key = PyThread_create_key();
  return 0;
}
static CYTHON_INLINE Py_tss_t * PyThread_tss_alloc(void) {
  Py_tss_t *key = (Py_tss_t *)PyObject_Malloc(sizeof(Py_tss_t));
  *key = Py_tss_NEEDS_INIT;
  return key;
}
static CYTHON_INLINE void PyThread_tss_free(Py_tss_t *key) {
  PyObject_Free(key);
}
static CYTHON_INLINE int PyThread_tss_is_created(Py_tss_t *key) {
  return *key != Py_tss_NEEDS_INIT;
}
static CYTHON_INLINE void PyThread_tss_delete(Py_tss_t *key) {
  PyThread_delete_key(*key);
  *key = Py_tss_NEEDS_INIT;
}
static CYTHON_INLINE int PyThread_tss_set(Py_tss_t *key, void *value) {
  return PyThread_set_key_value(*key, value);
}
static CYTHON_INLINE void * PyThread_tss_get(Py_tss_t *key) {
  return PyThread_get_key_value(*key);
}
#endif
#if CYTHON_COMPILING_IN_CPYTHON || defined(_PyDict_NewPresized)
#define __Pyx_PyDict_NewPresized(n)  ((n <= 8) ? PyDict_New() : _PyDict_NewPresized(n))
#else
#define __Pyx_PyDict_NewPresized(n)  PyDict_New()
#endif
#if PY_MAJOR_VERSION >= 3 || CYTHON_FUTURE_DIVISION
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_TrueDivide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceTrueDivide(x,y)
#else
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_Divide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceDivide(x,y)
#endif
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x030500A1 && CYTHON_USE_UNICODE_INTERNALS
#define __Pyx_PyDict_GetItemStr(dict, name)  _PyDict_GetItem_KnownHash(dict, name, ((PyASCIIObject *) name)->hash)
#else
#define __Pyx_PyDict_GetItemStr(dict, name)  PyDict_GetItem(dict, name)
#endif
#if PY_VERSION_HEX > 0x03030000 && defined(PyUnicode_KIND)
  #define CYTHON_PEP393_ENABLED 1
  #define __Pyx_PyUnicode_READY(op)       (likely(PyUnicode_IS_READY(op)) ?\
                                              0 : _PyUnicode_Ready((PyObject *)(op)))
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_LENGTH(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) PyUnicode_READ_CHAR(u, i)
  #define __Pyx_PyUnicode_MAX_CHAR_VALUE(u)   PyUnicode_MAX_CHAR_VALUE(u)
  #define __Pyx_PyUnicode_KIND(u)         PyUnicode_KIND(u)
  #define __Pyx_PyUnicode_DATA(u)         PyUnicode_DATA(u)
  #define __Pyx_PyUnicode_READ(k, d, i)   PyUnicode_READ(k, d, i)
  #define __Pyx_PyUnicode_WRITE(k, d, i, ch)  PyUnicode_WRITE(k, d, i, ch)
  #if defined(PyUnicode_IS_READY) && defined(PyUnicode_GET_SIZE)
  #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != (likely(PyUnicode_IS_READY(u)) ? PyUnicode_GET_LENGTH(u) : PyUnicode_GET_SIZE(u)))
  #else
  #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != PyUnicode_GET_LENGTH(u))
  #endif
#else
  #define CYTHON_PEP393_ENABLED 0
  #define PyUnicode_1BYTE_KIND  1
  #define PyUnicode_2BYTE_KIND  2
  #define PyUnicode_4BYTE_KIND  4
  #define __Pyx_PyUnicode_READY(op)       (0)
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_SIZE(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) ((Py_UCS4)(PyUnicode_AS_UNICODE(u)[i]))
  #define __Pyx_PyUnicode_MAX_CHAR_VALUE(u)   ((sizeof(Py_UNICODE) == 2) ? 65535 : 1114111)
  #define __Pyx_PyUnicode_KIND(u)         (sizeof(Py_UNICODE))
  #define __Pyx_PyUnicode_DATA(u)         ((void*)PyUnicode_AS_UNICODE(u))
  #define __Pyx_PyUnicode_READ(k, d, i)   ((void)(k), (Py_UCS4)(((Py_UNICODE*)d)[i]))
  #define __Pyx_PyUnicode_WRITE(k, d, i, ch)  (((void)(k)), ((Py_UNICODE*)d)[i] = ch)
  #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != PyUnicode_GET_SIZE(u))
#endif
#if CYTHON_COMPILING_IN_PYPY
  #define __Pyx_PyUnicode_Concat(a, b)      PyNumber_Add(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  PyNumber_Add(a, b)
#else
  #define __Pyx_PyUnicode_Concat(a, b)      PyUnicode_Concat(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  ((unlikely((a) == Py_None) || unlikely((b) == Py_None)) ?\
      PyNumber_Add(a, b) : __Pyx_PyUnicode_Concat(a, b))
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyUnicode_Contains)
  #define PyUnicode_Contains(u, s)  PySequence_Contains(u, s)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyByteArray_Check)
  #define PyByteArray_Check(obj)  PyObject_TypeCheck(obj, &PyByteArray_Type)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyObject_Format)
  #define PyObject_Format(obj, fmt)  PyObject_CallMethod(obj, "__format__", "O", fmt)
#endif
#define __Pyx_PyString_FormatSafe(a, b)   ((unlikely((a) == Py_None || (PyString_Check(b) && !PyString_CheckExact(b)))) ? PyNumber_Remainder(a, b) : __Pyx_PyString_Format(a, b))
#define __Pyx_PyUnicode_FormatSafe(a, b)  ((unlikely((a) == Py_None || (PyUnicode_Check(b) && !PyUnicode_CheckExact(b)))) ? PyNumber_Remainder(a, b) : PyUnicode_Format(a, b))
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyString_Format(a, b)  PyUnicode_Format(a, b)
#else
  #define __Pyx_PyString_Format(a, b)  PyString_Format(a, b)
#endif
#if PY_MAJOR_VERSION < 3 && !defined(PyObject_ASCII)
  #define PyObject_ASCII(o)            PyObject_Repr(o)
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBaseString_Type            PyUnicode_Type
  #define PyStringObject               PyUnicodeObject
  #define PyString_Type                PyUnicode_Type
  #define PyString_Check               PyUnicode_Check
  #define PyString_CheckExact          PyUnicode_CheckExact
#ifndef PyObject_Unicode
  #define PyObject_Unicode             PyObject_Str
#endif
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyBaseString_Check(obj) PyUnicode_Check(obj)
  #define __Pyx_PyBaseString_CheckExact(obj) PyUnicode_CheckExact(obj)
#else
  #define __Pyx_PyBaseString_Check(obj) (PyString_Check(obj) || PyUnicode_Check(obj))
  #define __Pyx_PyBaseString_CheckExact(obj) (PyString_CheckExact(obj) || PyUnicode_CheckExact(obj))
#endif
#ifndef PySet_CheckExact
  #define PySet_CheckExact(obj)        (Py_TYPE(obj) == &PySet_Type)
#endif
#if PY_VERSION_HEX >= 0x030900A4
  #define __Pyx_SET_REFCNT(obj, refcnt) Py_SET_REFCNT(obj, refcnt)
  #define __Pyx_SET_SIZE(obj, size) Py_SET_SIZE(obj, size)
#else
  #define __Pyx_SET_REFCNT(obj, refcnt) Py_REFCNT(obj) = (refcnt)
  #define __Pyx_SET_SIZE(obj, size) Py_SIZE(obj) = (size)
#endif
#if CYTHON_ASSUME_SAFE_MACROS
  #define __Pyx_PySequence_SIZE(seq)  Py_SIZE(seq)
#else
  #define __Pyx_PySequence_SIZE(seq)  PySequence_Size(seq)
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyIntObject                  PyLongObject
  #define PyInt_Type                   PyLong_Type
  #define PyInt_Check(op)              PyLong_Check(op)
  #define PyInt_CheckExact(op)         PyLong_CheckExact(op)
  #define PyInt_FromString             PyLong_FromString
  #define PyInt_FromUnicode            PyLong_FromUnicode
  #define PyInt_FromLong               PyLong_FromLong
  #define PyInt_FromSize_t             PyLong_FromSize_t
  #define PyInt_FromSsize_t            PyLong_FromSsize_t
  #define PyInt_AsLong                 PyLong_AsLong
  #define PyInt_AS_LONG                PyLong_AS_LONG
  #define PyInt_AsSsize_t              PyLong_AsSsize_t
  #define PyInt_AsUnsignedLongMask     PyLong_AsUnsignedLongMask
  #define PyInt_AsUnsignedLongLongMask PyLong_AsUnsignedLongLongMask
  #define PyNumber_Int                 PyNumber_Long
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBoolObject                 PyLongObject
#endif
#if PY_MAJOR_VERSION >= 3 && CYTHON_COMPILING_IN_PYPY
  #ifndef PyUnicode_InternFromString
    #define PyUnicode_InternFromString(s) PyUnicode_FromString(s)
  #endif
#endif
#if PY_VERSION_HEX < 0x030200A4
  typedef long Py_hash_t;
  #define __Pyx_PyInt_FromHash_t PyInt_FromLong
  #define __Pyx_PyInt_AsHash_t   PyInt_AsLong
#else
  #define __Pyx_PyInt_FromHash_t PyInt_FromSsize_t
  #define __Pyx_PyInt_AsHash_t   PyInt_AsSsize_t
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyMethod_New(func, self, klass) ((self) ? ((void)(klass), PyMethod_New(func, self)) : __Pyx_NewRef(func))
#else
  #define __Pyx_PyMethod_New(func, self, klass) PyMethod_New(func, self, klass)
#endif
#if CYTHON_USE_ASYNC_SLOTS
  #if PY_VERSION_HEX >= 0x030500B1
    #define __Pyx_PyAsyncMethodsStruct PyAsyncMethods
    #define __Pyx_PyType_AsAsync(obj) (Py_TYPE(obj)->tp_as_async)
  #else
    #define __Pyx_PyType_AsAsync(obj) ((__Pyx_PyAsyncMethodsStruct*) (Py_TYPE(obj)->tp_reserved))
  #endif
#else
  #define __Pyx_PyType_AsAsync(obj) NULL
#endif
#ifndef __Pyx_PyAsyncMethodsStruct
    typedef struct {
        unaryfunc am_await;
        unaryfunc am_aiter;
        unaryfunc am_anext;
    } __Pyx_PyAsyncMethodsStruct;
#endif

#if defined(WIN32) || defined(MS_WINDOWS)
  #define _USE_MATH_DEFINES
#endif
#include <math.h>
#ifdef NAN
#define __PYX_NAN() ((float) NAN)
#else
static CYTHON_INLINE float __PYX_NAN() {
  float value;
  memset(&value, 0xFF, sizeof(value));
  return value;
}
#endif
#if defined(__CYGWIN__) && defined(_LDBL_EQ_DBL)
#define __Pyx_truncl trunc
#else
#define __Pyx_truncl truncl
#endif

#define __PYX_MARK_ERR_POS(f_index, lineno) \
    { __pyx_filename = __pyx_f[f_index]; (void)__pyx_filename; __pyx_lineno = lineno; (void)__pyx_lineno; __pyx_clineno = __LINE__; (void)__pyx_clineno; }
#define __PYX_ERR(f_index, lineno, Ln_error) \
    { __PYX_MARK_ERR_POS(f_index, lineno) goto Ln_error; }

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

#define __PYX_HAVE__fa2__fa2util
#define __PYX_HAVE_API__fa2__fa2util
/* Early includes */
#ifdef _OPENMP
#include <omp.h>
#endif /* _OPENMP */

#if defined(PYREX_WITHOUT_ASSERTIONS) && !defined(CYTHON_WITHOUT_ASSERTIONS)
#define CYTHON_WITHOUT_ASSERTIONS
#endif

typedef struct {PyObject **p; const char *s; const Py_ssize_t n; const char* encoding;
                const char is_unicode; const char is_str; const char intern; } __Pyx_StringTabEntry;

#define __PYX_DEFAULT_STRING_ENCODING_IS_ASCII 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_UTF8 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT (PY_MAJOR_VERSION >= 3 && __PYX_DEFAULT_STRING_ENCODING_IS_UTF8)
#define __PYX_DEFAULT_STRING_ENCODING ""
#define __Pyx_PyObject_FromString __Pyx_PyBytes_FromString
#define __Pyx_PyObject_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#define __Pyx_uchar_cast(c) ((unsigned char)c)
#define __Pyx_long_cast(x) ((long)x)
#define __Pyx_fits_Py_ssize_t(v, type, is_signed)  (\
    (sizeof(type) < sizeof(Py_ssize_t))  ||\
    (sizeof(type) > sizeof(Py_ssize_t) &&\
          likely(v < (type)PY_SSIZE_T_MAX ||\
                 v == (type)PY_SSIZE_T_MAX)  &&\
          (!is_signed || likely(v > (type)PY_SSIZE_T_MIN ||\
                                v == (type)PY_SSIZE_T_MIN)))  ||\
    (sizeof(type) == sizeof(Py_ssize_t) &&\
          (is_signed || likely(v < (type)PY_SSIZE_T_MAX ||\
                               v == (type)PY_SSIZE_T_MAX)))  )
static CYTHON_INLINE int __Pyx_is_valid_index(Py_ssize_t i, Py_ssize_t limit) {
    return (size_t) i < (size_t) limit;
}
#if defined (__cplusplus) && __cplusplus >= 201103L
    #include <cstdlib>
    #define __Pyx_sst_abs(value) std::abs(value)
#elif SIZEOF_INT >= SIZEOF_SIZE_T
    #define __Pyx_sst_abs(value) abs(value)
#elif SIZEOF_LONG >= SIZEOF_SIZE_T
    #define __Pyx_sst_abs(value) labs(value)
#elif defined (_MSC_VER)
    #define __Pyx_sst_abs(value) ((Py_ssize_t)_abs64(value))
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define __Pyx_sst_abs(value) llabs(value)
#elif defined (__GNUC__)
    #define __Pyx_sst_abs(value) __builtin_llabs(value)
#else
    #define __Pyx_sst_abs(value) ((value<0) ? -value : value)
#endif
static CYTHON_INLINE const char* __Pyx_PyObject_AsString(PyObject*);
static CYTHON_INLINE const char* __Pyx_PyObject_AsStringAndSize(PyObject*, Py_ssize_t* length);
#define __Pyx_PyByteArray_FromString(s) PyByteArray_FromStringAndSize((const char*)s, strlen((const char*)s))
#define __Pyx_PyByteArray_FromStringAndSize(s, l) PyByteArray_FromStringAndSize((const char*)s, l)
#define __Pyx_PyBytes_FromString        PyBytes_FromString
#define __Pyx_PyBytes_FromStringAndSize PyBytes_FromStringAndSize
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char*);
#if PY_MAJOR_VERSION < 3
    #define __Pyx_PyStr_FromString        __Pyx_PyBytes_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#else
    #define __Pyx_PyStr_FromString        __Pyx_PyUnicode_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyUnicode_FromStringAndSize
#endif
#define __Pyx_PyBytes_AsWritableString(s)     ((char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsWritableSString(s)    ((signed char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsWritableUString(s)    ((unsigned char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsString(s)     ((const char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsSString(s)    ((const signed char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsUString(s)    ((const unsigned char*) PyBytes_AS_STRING(s))
#define __Pyx_PyObject_AsWritableString(s)    ((char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsWritableSString(s)    ((signed char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsWritableUString(s)    ((unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsSString(s)    ((const signed char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsUString(s)    ((const unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_FromCString(s)  __Pyx_PyObject_FromString((const char*)s)
#define __Pyx_PyBytes_FromCString(s)   __Pyx_PyBytes_FromString((const char*)s)
#define __Pyx_PyByteArray_FromCString(s)   __Pyx_PyByteArray_FromString((const char*)s)
#define __Pyx_PyStr_FromCString(s)     __Pyx_PyStr_FromString((const char*)s)
#define __Pyx_PyUnicode_FromCString(s) __Pyx_PyUnicode_FromString((const char*)s)
static CYTHON_INLINE size_t __Pyx_Py_UNICODE_strlen(const Py_UNICODE *u) {
    const Py_UNICODE *u_end = u;
    while (*u_end++) ;
    return (size_t)(u_end - u - 1);
}
#define __Pyx_PyUnicode_FromUnicode(u)       PyUnicode_FromUnicode(u, __Pyx_Py_UNICODE_strlen(u))
#define __Pyx_PyUnicode_FromUnicodeAndLength PyUnicode_FromUnicode
#define __Pyx_PyUnicode_AsUnicode            PyUnicode_AsUnicode
#define __Pyx_NewRef(obj) (Py_INCREF(obj), obj)
#define __Pyx_Owned_Py_None(b) __Pyx_NewRef(Py_None)
static CYTHON_INLINE PyObject * __Pyx_PyBool_FromLong(long b);
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject*);
static CYTHON_INLINE int __Pyx_PyObject_IsTrueAndDecref(PyObject*);
static CYTHON_INLINE PyObject* __Pyx_PyNumber_IntOrLong(PyObject* x);
#define __Pyx_PySequence_Tuple(obj)\
    (likely(PyTuple_CheckExact(obj)) ? __Pyx_NewRef(obj) : PySequence_Tuple(obj))
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject*);
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t);
#if CYTHON_ASSUME_SAFE_MACROS
#define __pyx_PyFloat_AsDouble(x) (PyFloat_CheckExact(x) ? PyFloat_AS_DOUBLE(x) : PyFloat_AsDouble(x))
#else
#define __pyx_PyFloat_AsDouble(x) PyFloat_AsDouble(x)
#endif
#define __pyx_PyFloat_AsFloat(x) ((float) __pyx_PyFloat_AsDouble(x))
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyNumber_Int(x) (PyLong_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Long(x))
#else
#define __Pyx_PyNumber_Int(x) (PyInt_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Int(x))
#endif
#define __Pyx_PyNumber_Float(x) (PyFloat_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Float(x))
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
static int __Pyx_sys_getdefaultencoding_not_ascii;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    PyObject* ascii_chars_u = NULL;
    PyObject* ascii_chars_b = NULL;
    const char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    if (strcmp(default_encoding_c, "ascii") == 0) {
        __Pyx_sys_getdefaultencoding_not_ascii = 0;
    } else {
        char ascii_chars[128];
        int c;
        for (c = 0; c < 128; c++) {
            ascii_chars[c] = c;
        }
        __Pyx_sys_getdefaultencoding_not_ascii = 1;
        ascii_chars_u = PyUnicode_DecodeASCII(ascii_chars, 128, NULL);
        if (!ascii_chars_u) goto bad;
        ascii_chars_b = PyUnicode_AsEncodedString(ascii_chars_u, default_encoding_c, NULL);
        if (!ascii_chars_b || !PyBytes_Check(ascii_chars_b) || memcmp(ascii_chars, PyBytes_AS_STRING(ascii_chars_b), 128) != 0) {
            PyErr_Format(
                PyExc_ValueError,
                "This module compiled with c_string_encoding=ascii, but default encoding '%.200s' is not a superset of ascii.",
                default_encoding_c);
            goto bad;
        }
        Py_DECREF(ascii_chars_u);
        Py_DECREF(ascii_chars_b);
    }
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    Py_XDECREF(ascii_chars_u);
    Py_XDECREF(ascii_chars_b);
    return -1;
}
#endif
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT && PY_MAJOR_VERSION >= 3
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_DecodeUTF8(c_str, size, NULL)
#else
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_Decode(c_str, size, __PYX_DEFAULT_STRING_ENCODING, NULL)
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
static char* __PYX_DEFAULT_STRING_ENCODING;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) (const char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    __PYX_DEFAULT_STRING_ENCODING = (char*) malloc(strlen(default_encoding_c) + 1);
    if (!__PYX_DEFAULT_STRING_ENCODING) goto bad;
    strcpy(__PYX_DEFAULT_STRING_ENCODING, default_encoding_c);
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    return -1;
}
#endif
#endif


/* Test for GCC > 2.95 */
#if defined(__GNUC__)     && (__GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95)))
  #define likely(x)   __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else /* !__GNUC__ or GCC < 2.95 */
  #define likely(x)   (x)
  #define unlikely(x) (x)
#endif /* __GNUC__ */
static CYTHON_INLINE void __Pyx_pretend_to_initialize(void* ptr) { (void)ptr; }

static PyObject *__pyx_m = NULL;
static PyObject *__pyx_d;
static PyObject *__pyx_b;
static PyObject *__pyx_cython_runtime = NULL;
static PyObject *__pyx_empty_tuple;
static PyObject *__pyx_empty_bytes;
static PyObject *__pyx_empty_unicode;
static int __pyx_lineno;
static int __pyx_clineno = 0;
static const char * __pyx_cfilenm= __FILE__;
static const char *__pyx_filename;


static const char *__pyx_f[] = {
  "fa2util.pxd",
  "stringsource",
  "fa2util.py",
};

/*--- Type declarations ---*/
struct __pyx_obj_3fa2_7fa2util_Node;
struct __pyx_obj_3fa2_7fa2util_Edge;
struct __pyx_obj_3fa2_7fa2util_Region;
struct __pyx_opt_args_3fa2_7fa2util_linRepulsion;
struct __pyx_opt_args_3fa2_7fa2util_linRepulsion_region;
struct __pyx_opt_args_3fa2_7fa2util_strongGravity;
struct __pyx_opt_args_3fa2_7fa2util_linAttraction;
struct __pyx_opt_args_3fa2_7fa2util_apply_gravity;
struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForce;
struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForceOnNodes;

/* "fa2/fa2util.pxd":38
 *                distance2 = cython.double,
 *                factor = cython.double)
 * cdef void linRepulsion(Node n1, Node n2, double coefficient=*)             # <<<<<<<<<<<<<<
 * 
 * @cython.locals(xDist = cython.double,
 */
struct __pyx_opt_args_3fa2_7fa2util_linRepulsion {
  int __pyx_n;
  double coefficient;
};

/* "fa2/fa2util.pxd":44
 *                distance2 = cython.double,
 *                factor = cython.double)
 * cdef void linRepulsion_region(Node n, Region r, double coefficient=*)             # <<<<<<<<<<<<<<
 * 
 * 
 */
struct __pyx_opt_args_3fa2_7fa2util_linRepulsion_region {
  int __pyx_n;
  double coefficient;
};

/* "fa2/fa2util.pxd":57
 *                yDist = cython.double,
 *                factor = cython.double)
 * cdef void strongGravity(Node n, double g, double coefficient=*)             # <<<<<<<<<<<<<<
 * 
 * @cython.locals(xDist = cython.double,
 */
struct __pyx_opt_args_3fa2_7fa2util_strongGravity {
  int __pyx_n;
  double coefficient;
};

/* "fa2/fa2util.pxd":62
 *                yDist = cython.double,
 *                factor = cython.double)
 * cpdef void linAttraction(Node n1, Node n2, double e, bint distributedAttraction, double coefficient=*)             # <<<<<<<<<<<<<<
 * 
 * @cython.locals(i = cython.int,
 */
struct __pyx_opt_args_3fa2_7fa2util_linAttraction {
  int __pyx_n;
  double coefficient;
};

/* "fa2/fa2util.pxd":71
 * 
 * @cython.locals(n = Node)
 * cpdef void apply_gravity(list nodes, double gravity, double scalingRatio, bint useStrongGravity=*)             # <<<<<<<<<<<<<<
 * 
 * @cython.locals(edge = Edge)
 */
struct __pyx_opt_args_3fa2_7fa2util_apply_gravity {
  int __pyx_n;
  int useStrongGravity;
};

/* "fa2/fa2util.pxd":100
 *     @cython.locals(distance = cython.double,
 *                    subregion = Region)
 *     cdef void applyForce(self, Node n, double theta, double coefficient=*)             # <<<<<<<<<<<<<<
 * 
 *     @cython.locals(n = Node)
 */
struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForce {
  int __pyx_n;
  double coefficient;
};

/* "fa2/fa2util.pxd":103
 * 
 *     @cython.locals(n = Node)
 *     cpdef applyForceOnNodes(self, list nodes, double theta, double coefficient=*)             # <<<<<<<<<<<<<<
 * 
 * @cython.locals(totalSwinging = cython.double,
 */
struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForceOnNodes {
  int __pyx_n;
  double coefficient;
};

/* "fa2/fa2util.pxd":18
 * 
 * # This will substitute for the nLayout object
 * cdef class Node:             # <<<<<<<<<<<<<<
 *     cdef public double mass
 *     cdef public double old_dx, old_dy
 */
struct __pyx_obj_3fa2_7fa2util_Node {
  PyObject_HEAD
  double mass;
  double old_dx;
  double old_dy;
  double dx;
  double dy;
  double x;
  double y;
};


/* "fa2/fa2util.pxd":26
 * # This is not in the original java function, but it makes it easier to
 * # deal with edges.
 * cdef class Edge:             # <<<<<<<<<<<<<<
 *     cdef public int node1, node2
 *     cdef public double weight
 */
struct __pyx_obj_3fa2_7fa2util_Edge {
  PyObject_HEAD
  int node1;
  int node2;
  double weight;
};


/* "fa2/fa2util.pxd":76
 * cpdef void apply_attraction(list nodes, list edges, bint distributedAttraction, double coefficient, double edgeWeightInfluence)
 * 
 * cdef class Region:             # <<<<<<<<<<<<<<
 *     cdef public double mass
 *     cdef public double massCenterX, massCenterY
 */
struct __pyx_obj_3fa2_7fa2util_Region {
  PyObject_HEAD
  struct __pyx_vtabstruct_3fa2_7fa2util_Region *__pyx_vtab;
  double mass;
  double massCenterX;
  double massCenterY;
  double size;
  PyObject *nodes;
  PyObject *subregions;
};



/* "fa2/fa2util.py":149
 * 
 * # For Barnes Hut Optimization
 * class Region:             # <<<<<<<<<<<<<<
 *     def __init__(self, nodes):
 *         self.mass = 0.0
 */

struct __pyx_vtabstruct_3fa2_7fa2util_Region {
  void (*updateMassAndGeometry)(struct __pyx_obj_3fa2_7fa2util_Region *);
  void (*buildSubRegions)(struct __pyx_obj_3fa2_7fa2util_Region *, int __pyx_skip_dispatch);
  void (*applyForce)(struct __pyx_obj_3fa2_7fa2util_Region *, struct __pyx_obj_3fa2_7fa2util_Node *, double, struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForce *__pyx_optional_args);
  PyObject *(*applyForceOnNodes)(struct __pyx_obj_3fa2_7fa2util_Region *, PyObject *, double, int __pyx_skip_dispatch, struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForceOnNodes *__pyx_optional_args);
};
static struct __pyx_vtabstruct_3fa2_7fa2util_Region *__pyx_vtabptr_3fa2_7fa2util_Region;

/* --- Runtime support code (head) --- */
/* Refnanny.proto */
#ifndef CYTHON_REFNANNY
  #define CYTHON_REFNANNY 0
#endif
#if CYTHON_REFNANNY
  typedef struct {
    void (*INCREF)(void*, PyObject*, int);
    void (*DECREF)(void*, PyObject*, int);
    void (*GOTREF)(void*, PyObject*, int);
    void (*GIVEREF)(void*, PyObject*, int);
    void* (*SetupContext)(const char*, int, const char*);
    void (*FinishContext)(void**);
  } __Pyx_RefNannyAPIStruct;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNanny = NULL;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname);
  #define __Pyx_RefNannyDeclarations void *__pyx_refnanny = NULL;
#ifdef WITH_THREAD
  #define __Pyx_RefNannySetupContext(name, acquire_gil)\
          if (acquire_gil) {\
              PyGILState_STATE __pyx_gilstate_save = PyGILState_Ensure();\
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__);\
              PyGILState_Release(__pyx_gilstate_save);\
          } else {\
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__);\
          }
#else
  #define __Pyx_RefNannySetupContext(name, acquire_gil)\
          __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__)
#endif
  #define __Pyx_RefNannyFinishContext()\
          __Pyx_RefNanny->FinishContext(&__pyx_refnanny)
  #define __Pyx_INCREF(r)  __Pyx_RefNanny->INCREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_DECREF(r)  __Pyx_RefNanny->DECREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GOTREF(r)  __Pyx_RefNanny->GOTREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GIVEREF(r) __Pyx_RefNanny->GIVEREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_XINCREF(r)  do { if((r) != NULL) {__Pyx_INCREF(r); }} while(0)
  #define __Pyx_XDECREF(r)  do { if((r) != NULL) {__Pyx_DECREF(r); }} while(0)
  #define __Pyx_XGOTREF(r)  do { if((r) != NULL) {__Pyx_GOTREF(r); }} while(0)
  #define __Pyx_XGIVEREF(r) do { if((r) != NULL) {__Pyx_GIVEREF(r);}} while(0)
#else
  #define __Pyx_RefNannyDeclarations
  #define __Pyx_RefNannySetupContext(name, acquire_gil)
  #define __Pyx_RefNannyFinishContext()
  #define __Pyx_INCREF(r) Py_INCREF(r)
  #define __Pyx_DECREF(r) Py_DECREF(r)
  #define __Pyx_GOTREF(r)
  #define __Pyx_GIVEREF(r)
  #define __Pyx_XINCREF(r) Py_XINCREF(r)
  #define __Pyx_XDECREF(r) Py_XDECREF(r)
  #define __Pyx_XGOTREF(r)
  #define __Pyx_XGIVEREF(r)
#endif
#define __Pyx_XDECREF_SET(r, v) do {\
        PyObject *tmp = (PyObject *) r;\
        r = v; __Pyx_XDECREF(tmp);\
    } while (0)
#define __Pyx_DECREF_SET(r, v) do {\
        PyObject *tmp = (PyObject *) r;\
        r = v; __Pyx_DECREF(tmp);\
    } while (0)
#define __Pyx_CLEAR(r)    do { PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);} while(0)
#define __Pyx_XCLEAR(r)   do { if((r) != NULL) {PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);}} while(0)

/* RaiseArgTupleInvalid.proto */
static void __Pyx_RaiseArgtupleInvalid(const char* func_name, int exact,
    Py_ssize_t num_min, Py_ssize_t num_max, Py_ssize_t num_found);

/* KeywordStringCheck.proto */
static int __Pyx_CheckKeywordStrings(PyObject *kwdict, const char* function_name, int kw_allowed);

/* PyErrExceptionMatches.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyErr_ExceptionMatches(err) __Pyx_PyErr_ExceptionMatchesInState(__pyx_tstate, err)
static CYTHON_INLINE int __Pyx_PyErr_ExceptionMatchesInState(PyThreadState* tstate, PyObject* err);
#else
#define __Pyx_PyErr_ExceptionMatches(err)  PyErr_ExceptionMatches(err)
#endif

/* PyThreadStateGet.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyThreadState_declare  PyThreadState *__pyx_tstate;
#define __Pyx_PyThreadState_assign  __pyx_tstate = __Pyx_PyThreadState_Current;
#define __Pyx_PyErr_Occurred()  __pyx_tstate->curexc_type
#else
#define __Pyx_PyThreadState_declare
#define __Pyx_PyThreadState_assign
#define __Pyx_PyErr_Occurred()  PyErr_Occurred()
#endif

/* PyErrFetchRestore.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyErr_Clear() __Pyx_ErrRestore(NULL, NULL, NULL)
#define __Pyx_ErrRestoreWithState(type, value, tb)  __Pyx_ErrRestoreInState(PyThreadState_GET(), type, value, tb)
#define __Pyx_ErrFetchWithState(type, value, tb)    __Pyx_ErrFetchInState(PyThreadState_GET(), type, value, tb)
#define __Pyx_ErrRestore(type, value, tb)  __Pyx_ErrRestoreInState(__pyx_tstate, type, value, tb)
#define __Pyx_ErrFetch(type, value, tb)    __Pyx_ErrFetchInState(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx_ErrRestoreInState(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb);
static CYTHON_INLINE void __Pyx_ErrFetchInState(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#if CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_PyErr_SetNone(exc) (Py_INCREF(exc), __Pyx_ErrRestore((exc), NULL, NULL))
#else
#define __Pyx_PyErr_SetNone(exc) PyErr_SetNone(exc)
#endif
#else
#define __Pyx_PyErr_Clear() PyErr_Clear()
#define __Pyx_PyErr_SetNone(exc) PyErr_SetNone(exc)
#define __Pyx_ErrRestoreWithState(type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetchWithState(type, value, tb)  PyErr_Fetch(type, value, tb)
#define __Pyx_ErrRestoreInState(tstate, type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetchInState(tstate, type, value, tb)  PyErr_Fetch(type, value, tb)
#define __Pyx_ErrRestore(type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetch(type, value, tb)  PyErr_Fetch(type, value, tb)
#endif

/* PyObjectGetAttrStr.proto */
#if CYTHON_USE_TYPE_SLOTS
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStr(PyObject* obj, PyObject* attr_name);
#else
#define __Pyx_PyObject_GetAttrStr(o,n) PyObject_GetAttr(o,n)
#endif

/* GetAttr.proto */
static CYTHON_INLINE PyObject *__Pyx_GetAttr(PyObject *, PyObject *);

/* GetAttr3.proto */
static CYTHON_INLINE PyObject *__Pyx_GetAttr3(PyObject *, PyObject *, PyObject *);

/* GetBuiltinName.proto */
static PyObject *__Pyx_GetBuiltinName(PyObject *name);

/* PyDictVersioning.proto */
#if CYTHON_USE_DICT_VERSIONS && CYTHON_USE_TYPE_SLOTS
#define __PYX_DICT_VERSION_INIT  ((PY_UINT64_T) -1)
#define __PYX_GET_DICT_VERSION(dict)  (((PyDictObject*)(dict))->ma_version_tag)
#define __PYX_UPDATE_DICT_CACHE(dict, value, cache_var, version_var)\
    (version_var) = __PYX_GET_DICT_VERSION(dict);\
    (cache_var) = (value);
#define __PYX_PY_DICT_LOOKUP_IF_MODIFIED(VAR, DICT, LOOKUP) {\
    static PY_UINT64_T __pyx_dict_version = 0;\
    static PyObject *__pyx_dict_cached_value = NULL;\
    if (likely(__PYX_GET_DICT_VERSION(DICT) == __pyx_dict_version)) {\
        (VAR) = __pyx_dict_cached_value;\
    } else {\
        (VAR) = __pyx_dict_cached_value = (LOOKUP);\
        __pyx_dict_version = __PYX_GET_DICT_VERSION(DICT);\
    }\
}
static CYTHON_INLINE PY_UINT64_T __Pyx_get_tp_dict_version(PyObject *obj);
static CYTHON_INLINE PY_UINT64_T __Pyx_get_object_dict_version(PyObject *obj);
static CYTHON_INLINE int __Pyx_object_dict_version_matches(PyObject* obj, PY_UINT64_T tp_dict_version, PY_UINT64_T obj_dict_version);
#else
#define __PYX_GET_DICT_VERSION(dict)  (0)
#define __PYX_UPDATE_DICT_CACHE(dict, value, cache_var, version_var)
#define __PYX_PY_DICT_LOOKUP_IF_MODIFIED(VAR, DICT, LOOKUP)  (VAR) = (LOOKUP);
#endif

/* GetModuleGlobalName.proto */
#if CYTHON_USE_DICT_VERSIONS
#define __Pyx_GetModuleGlobalName(var, name)  {\
    static PY_UINT64_T __pyx_dict_version = 0;\
    static PyObject *__pyx_dict_cached_value = NULL;\
    (var) = (likely(__pyx_dict_version == __PYX_GET_DICT_VERSION(__pyx_d))) ?\
        (likely(__pyx_dict_cached_value) ? __Pyx_NewRef(__pyx_dict_cached_value) : __Pyx_GetBuiltinName(name)) :\
        __Pyx__GetModuleGlobalName(name, &__pyx_dict_version, &__pyx_dict_cached_value);\
}
#define __Pyx_GetModuleGlobalNameUncached(var, name)  {\
    PY_UINT64_T __pyx_dict_version;\
    PyObject *__pyx_dict_cached_value;\
    (var) = __Pyx__GetModuleGlobalName(name, &__pyx_dict_version, &__pyx_dict_cached_value);\
}
static PyObject *__Pyx__GetModuleGlobalName(PyObject *name, PY_UINT64_T *dict_version, PyObject **dict_cached_value);
#else
#define __Pyx_GetModuleGlobalName(var, name)  (var) = __Pyx__GetModuleGlobalName(name)
#define __Pyx_GetModuleGlobalNameUncached(var, name)  (var) = __Pyx__GetModuleGlobalName(name)
static CYTHON_INLINE PyObject *__Pyx__GetModuleGlobalName(PyObject *name);
#endif

/* WriteUnraisableException.proto */
static void __Pyx_WriteUnraisable(const char *name, int clineno,
                                  int lineno, const char *filename,
                                  int full_traceback, int nogil);

/* PyCFunctionFastCall.proto */
#if CYTHON_FAST_PYCCALL
static CYTHON_INLINE PyObject *__Pyx_PyCFunction_FastCall(PyObject *func, PyObject **args, Py_ssize_t nargs);
#else
#define __Pyx_PyCFunction_FastCall(func, args, nargs)  (assert(0), NULL)
#endif

/* PyFunctionFastCall.proto */
#if CYTHON_FAST_PYCALL
#define __Pyx_PyFunction_FastCall(func, args, nargs)\
    __Pyx_PyFunction_FastCallDict((func), (args), (nargs), NULL)
#if 1 || PY_VERSION_HEX < 0x030600B1
static PyObject *__Pyx_PyFunction_FastCallDict(PyObject *func, PyObject **args, Py_ssize_t nargs, PyObject *kwargs);
#else
#define __Pyx_PyFunction_FastCallDict(func, args, nargs, kwargs) _PyFunction_FastCallDict(func, args, nargs, kwargs)
#endif
#define __Pyx_BUILD_ASSERT_EXPR(cond)\
    (sizeof(char [1 - 2*!(cond)]) - 1)
#ifndef Py_MEMBER_SIZE
#define Py_MEMBER_SIZE(type, member) sizeof(((type *)0)->member)
#endif
  static size_t __pyx_pyframe_localsplus_offset = 0;
  #include "frameobject.h"
  #define __Pxy_PyFrame_Initialize_Offsets()\
    ((void)__Pyx_BUILD_ASSERT_EXPR(sizeof(PyFrameObject) == offsetof(PyFrameObject, f_localsplus) + Py_MEMBER_SIZE(PyFrameObject, f_localsplus)),\
     (void)(__pyx_pyframe_localsplus_offset = ((size_t)PyFrame_Type.tp_basicsize) - Py_MEMBER_SIZE(PyFrameObject, f_localsplus)))
  #define __Pyx_PyFrame_GetLocalsplus(frame)\
    (assert(__pyx_pyframe_localsplus_offset), (PyObject **)(((char *)(frame)) + __pyx_pyframe_localsplus_offset))
#endif

/* PyObjectCall.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw);
#else
#define __Pyx_PyObject_Call(func, arg, kw) PyObject_Call(func, arg, kw)
#endif

/* PyObjectCall2Args.proto */
static CYTHON_UNUSED PyObject* __Pyx_PyObject_Call2Args(PyObject* function, PyObject* arg1, PyObject* arg2);

/* PyObjectCallMethO.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg);
#endif

/* PyObjectCallOneArg.proto */
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg);

/* RaiseDoubleKeywords.proto */
static void __Pyx_RaiseDoubleKeywordsError(const char* func_name, PyObject* kw_name);

/* ParseKeywords.proto */
static int __Pyx_ParseOptionalKeywords(PyObject *kwds, PyObject **argnames[],\
    PyObject *kwds2, PyObject *values[], Py_ssize_t num_pos_args,\
    const char* function_name);

/* ArgTypeTest.proto */
#define __Pyx_ArgTypeTest(obj, type, none_allowed, name, exact)\
    ((likely((Py_TYPE(obj) == type) | (none_allowed && (obj == Py_None)))) ? 1 :\
        __Pyx__ArgTypeTest(obj, type, name, exact))
static int __Pyx__ArgTypeTest(PyObject *obj, PyTypeObject *type, const char *name, int exact);

/* ExtTypeTest.proto */
static CYTHON_INLINE int __Pyx_TypeTest(PyObject *obj, PyTypeObject *type);

/* GetItemInt.proto */
#define __Pyx_GetItemInt(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_Fast(o, (Py_ssize_t)i, is_list, wraparound, boundscheck) :\
    (is_list ? (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL) :\
               __Pyx_GetItemInt_Generic(o, to_py_func(i))))
#define __Pyx_GetItemInt_List(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_List_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) :\
    (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
#define __Pyx_GetItemInt_Tuple(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_Tuple_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) :\
    (PyErr_SetString(PyExc_IndexError, "tuple index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
static PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                                     int is_list, int wraparound, int boundscheck);

/* pow2.proto */
#define __Pyx_PyNumber_Power2(a, b) PyNumber_Power(a, b, Py_None)

/* PyObjectCallNoArg.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func);
#else
#define __Pyx_PyObject_CallNoArg(func) __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL)
#endif

/* ListAppend.proto */
#if CYTHON_USE_PYLIST_INTERNALS && CYTHON_ASSUME_SAFE_MACROS
static CYTHON_INLINE int __Pyx_PyList_Append(PyObject* list, PyObject* x) {
    PyListObject* L = (PyListObject*) list;
    Py_ssize_t len = Py_SIZE(list);
    if (likely(L->allocated > len) & likely(len > (L->allocated >> 1))) {
        Py_INCREF(x);
        PyList_SET_ITEM(list, len, x);
        __Pyx_SET_SIZE(list, len + 1);
        return 0;
    }
    return PyList_Append(list, x);
}
#else
#define __Pyx_PyList_Append(L,x) PyList_Append(L,x)
#endif

/* pyobject_as_double.proto */
static double __Pyx__PyObject_AsDouble(PyObject* obj);
#if CYTHON_COMPILING_IN_PYPY
#define __Pyx_PyObject_AsDouble(obj)\
(likely(PyFloat_CheckExact(obj)) ? PyFloat_AS_DOUBLE(obj) :\
 likely(PyInt_CheckExact(obj)) ?\
 PyFloat_AsDouble(obj) : __Pyx__PyObject_AsDouble(obj))
#else
#define __Pyx_PyObject_AsDouble(obj)\
((likely(PyFloat_CheckExact(obj))) ?\
 PyFloat_AS_DOUBLE(obj) : __Pyx__PyObject_AsDouble(obj))
#endif

/* PyFloatBinop.proto */
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyFloat_AddCObj(PyObject *op1, PyObject *op2, double floatval, int inplace, int zerodivision_check);
#else
#define __Pyx_PyFloat_AddCObj(op1, op2, floatval, inplace, zerodivision_check)\
    (inplace ? PyNumber_InPlaceAdd(op1, op2) : PyNumber_Add(op1, op2))
#endif

/* Import.proto */
static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level);

/* ImportFrom.proto */
static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name);

/* RaiseException.proto */
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb, PyObject *cause);

/* HasAttr.proto */
static CYTHON_INLINE int __Pyx_HasAttr(PyObject *, PyObject *);

/* PyObject_GenericGetAttrNoDict.proto */
#if CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP && PY_VERSION_HEX < 0x03070000
static CYTHON_INLINE PyObject* __Pyx_PyObject_GenericGetAttrNoDict(PyObject* obj, PyObject* attr_name);
#else
#define __Pyx_PyObject_GenericGetAttrNoDict PyObject_GenericGetAttr
#endif

/* PyObject_GenericGetAttr.proto */
#if CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP && PY_VERSION_HEX < 0x03070000
static PyObject* __Pyx_PyObject_GenericGetAttr(PyObject* obj, PyObject* attr_name);
#else
#define __Pyx_PyObject_GenericGetAttr PyObject_GenericGetAttr
#endif

/* PyObjectGetAttrStrNoError.proto */
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStrNoError(PyObject* obj, PyObject* attr_name);

/* SetupReduce.proto */
static int __Pyx_setup_reduce(PyObject* type_obj);

/* SetVTable.proto */
static int __Pyx_SetVtable(PyObject *dict, void *vtable);

/* FetchCommonType.proto */
static PyTypeObject* __Pyx_FetchCommonType(PyTypeObject* type);

/* CythonFunctionShared.proto */
#define __Pyx_CyFunction_USED 1
#define __Pyx_CYFUNCTION_STATICMETHOD  0x01
#define __Pyx_CYFUNCTION_CLASSMETHOD   0x02
#define __Pyx_CYFUNCTION_CCLASS        0x04
#define __Pyx_CyFunction_GetClosure(f)\
    (((__pyx_CyFunctionObject *) (f))->func_closure)
#define __Pyx_CyFunction_GetClassObj(f)\
    (((__pyx_CyFunctionObject *) (f))->func_classobj)
#define __Pyx_CyFunction_Defaults(type, f)\
    ((type *)(((__pyx_CyFunctionObject *) (f))->defaults))
#define __Pyx_CyFunction_SetDefaultsGetter(f, g)\
    ((__pyx_CyFunctionObject *) (f))->defaults_getter = (g)
typedef struct {
    PyCFunctionObject func;
#if PY_VERSION_HEX < 0x030500A0
    PyObject *func_weakreflist;
#endif
    PyObject *func_dict;
    PyObject *func_name;
    PyObject *func_qualname;
    PyObject *func_doc;
    PyObject *func_globals;
    PyObject *func_code;
    PyObject *func_closure;
    PyObject *func_classobj;
    void *defaults;
    int defaults_pyobjects;
    size_t defaults_size;  // used by FusedFunction for copying defaults
    int flags;
    PyObject *defaults_tuple;
    PyObject *defaults_kwdict;
    PyObject *(*defaults_getter)(PyObject *);
    PyObject *func_annotations;
} __pyx_CyFunctionObject;
static PyTypeObject *__pyx_CyFunctionType = 0;
#define __Pyx_CyFunction_Check(obj)  (__Pyx_TypeCheck(obj, __pyx_CyFunctionType))
static PyObject *__Pyx_CyFunction_Init(__pyx_CyFunctionObject* op, PyMethodDef *ml,
                                      int flags, PyObject* qualname,
                                      PyObject *self,
                                      PyObject *module, PyObject *globals,
                                      PyObject* code);
static CYTHON_INLINE void *__Pyx_CyFunction_InitDefaults(PyObject *m,
                                                         size_t size,
                                                         int pyobjects);
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsTuple(PyObject *m,
                                                            PyObject *tuple);
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsKwDict(PyObject *m,
                                                             PyObject *dict);
static CYTHON_INLINE void __Pyx_CyFunction_SetAnnotationsDict(PyObject *m,
                                                              PyObject *dict);
static int __pyx_CyFunction_init(void);

/* CythonFunction.proto */
static PyObject *__Pyx_CyFunction_New(PyMethodDef *ml,
                                      int flags, PyObject* qualname,
                                      PyObject *closure,
                                      PyObject *module, PyObject *globals,
                                      PyObject* code);

/* GetTopmostException.proto */
#if CYTHON_USE_EXC_INFO_STACK
static _PyErr_StackItem * __Pyx_PyErr_GetTopmostException(PyThreadState *tstate);
#endif

/* SaveResetException.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_ExceptionSave(type, value, tb)  __Pyx__ExceptionSave(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#define __Pyx_ExceptionReset(type, value, tb)  __Pyx__ExceptionReset(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb);
#else
#define __Pyx_ExceptionSave(type, value, tb)   PyErr_GetExcInfo(type, value, tb)
#define __Pyx_ExceptionReset(type, value, tb)  PyErr_SetExcInfo(type, value, tb)
#endif

/* GetException.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_GetException(type, value, tb)  __Pyx__GetException(__pyx_tstate, type, value, tb)
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#else
static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb);
#endif

/* CLineInTraceback.proto */
#ifdef CYTHON_CLINE_IN_TRACEBACK
#define __Pyx_CLineForTraceback(tstate, c_line)  (((CYTHON_CLINE_IN_TRACEBACK)) ? c_line : 0)
#else
static int __Pyx_CLineForTraceback(PyThreadState *tstate, int c_line);
#endif

/* CodeObjectCache.proto */
typedef struct {
    PyCodeObject* code_object;
    int code_line;
} __Pyx_CodeObjectCacheEntry;
struct __Pyx_CodeObjectCache {
    int count;
    int max_count;
    __Pyx_CodeObjectCacheEntry* entries;
};
static struct __Pyx_CodeObjectCache __pyx_code_cache = {0,0,NULL};
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line);
static PyCodeObject *__pyx_find_code_object(int code_line);
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object);

/* AddTraceback.proto */
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename);

/* GCCDiagnostics.proto */
#if defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#define __Pyx_HAS_GCC_DIAGNOSTIC
#endif

/* Print.proto */
static int __Pyx_Print(PyObject*, PyObject *, int);
#if CYTHON_COMPILING_IN_PYPY || PY_MAJOR_VERSION >= 3
static PyObject* __pyx_print = 0;
static PyObject* __pyx_print_kwargs = 0;
#endif

/* CIntToPy.proto */
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_int(int value);

/* CIntFromPy.proto */
static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *);

/* CIntFromPy.proto */
static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *);

/* CIntToPy.proto */
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value);

/* PrintOne.proto */
static int __Pyx_PrintOne(PyObject* stream, PyObject *o);

/* FastTypeChecks.proto */
#if CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_TypeCheck(obj, type) __Pyx_IsSubtype(Py_TYPE(obj), (PyTypeObject *)type)
static CYTHON_INLINE int __Pyx_IsSubtype(PyTypeObject *a, PyTypeObject *b);
static CYTHON_INLINE int __Pyx_PyErr_GivenExceptionMatches(PyObject *err, PyObject *type);
static CYTHON_INLINE int __Pyx_PyErr_GivenExceptionMatches2(PyObject *err, PyObject *type1, PyObject *type2);
#else
#define __Pyx_TypeCheck(obj, type) PyObject_TypeCheck(obj, (PyTypeObject *)type)
#define __Pyx_PyErr_GivenExceptionMatches(err, type) PyErr_GivenExceptionMatches(err, type)
#define __Pyx_PyErr_GivenExceptionMatches2(err, type1, type2) (PyErr_GivenExceptionMatches(err, type1) || PyErr_GivenExceptionMatches(err, type2))
#endif
#define __Pyx_PyException_Check(obj) __Pyx_TypeCheck(obj, PyExc_Exception)

/* CheckBinaryVersion.proto */
static int __Pyx_check_binary_version(void);

/* FunctionExport.proto */
static int __Pyx_ExportFunction(const char *name, void (*f)(void), const char *sig);

/* InitStrings.proto */
static int __Pyx_InitStrings(__Pyx_StringTabEntry *t);

static void __pyx_f_3fa2_7fa2util_6Region_updateMassAndGeometry(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self); /* proto*/
static void __pyx_f_3fa2_7fa2util_6Region_buildSubRegions(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, int __pyx_skip_dispatch); /* proto*/
static void __pyx_f_3fa2_7fa2util_6Region_applyForce(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n, double __pyx_v_theta, struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForce *__pyx_optional_args); /* proto*/
static PyObject *__pyx_f_3fa2_7fa2util_6Region_applyForceOnNodes(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_nodes, double __pyx_v_theta, int __pyx_skip_dispatch, struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForceOnNodes *__pyx_optional_args); /* proto*/

/* Module declarations from 'cython' */

/* Module declarations from 'fa2.fa2util' */
static PyTypeObject *__pyx_ptype_3fa2_7fa2util_Node = 0;
static PyTypeObject *__pyx_ptype_3fa2_7fa2util_Edge = 0;
static PyTypeObject *__pyx_ptype_3fa2_7fa2util_Region = 0;
static void __pyx_f_3fa2_7fa2util_linRepulsion(struct __pyx_obj_3fa2_7fa2util_Node *, struct __pyx_obj_3fa2_7fa2util_Node *, struct __pyx_opt_args_3fa2_7fa2util_linRepulsion *__pyx_optional_args); /*proto*/
static void __pyx_f_3fa2_7fa2util_linRepulsion_region(struct __pyx_obj_3fa2_7fa2util_Node *, struct __pyx_obj_3fa2_7fa2util_Region *, struct __pyx_opt_args_3fa2_7fa2util_linRepulsion_region *__pyx_optional_args); /*proto*/
static void __pyx_f_3fa2_7fa2util_linGravity(struct __pyx_obj_3fa2_7fa2util_Node *, double); /*proto*/
static void __pyx_f_3fa2_7fa2util_strongGravity(struct __pyx_obj_3fa2_7fa2util_Node *, double, struct __pyx_opt_args_3fa2_7fa2util_strongGravity *__pyx_optional_args); /*proto*/
static void __pyx_f_3fa2_7fa2util_linAttraction(struct __pyx_obj_3fa2_7fa2util_Node *, struct __pyx_obj_3fa2_7fa2util_Node *, double, int, int __pyx_skip_dispatch, struct __pyx_opt_args_3fa2_7fa2util_linAttraction *__pyx_optional_args); /*proto*/
static void __pyx_f_3fa2_7fa2util_apply_repulsion(PyObject *, double, int __pyx_skip_dispatch); /*proto*/
static void __pyx_f_3fa2_7fa2util_apply_gravity(PyObject *, double, double, int __pyx_skip_dispatch, struct __pyx_opt_args_3fa2_7fa2util_apply_gravity *__pyx_optional_args); /*proto*/
static void __pyx_f_3fa2_7fa2util_apply_attraction(PyObject *, PyObject *, int, double, double, int __pyx_skip_dispatch); /*proto*/
static PyObject *__pyx_f_3fa2_7fa2util_adjustSpeedAndApplyForces(PyObject *, double, double, double, int __pyx_skip_dispatch); /*proto*/
static PyObject *__pyx_f_3fa2_7fa2util___pyx_unpickle_Node__set_state(struct __pyx_obj_3fa2_7fa2util_Node *, PyObject *); /*proto*/
static PyObject *__pyx_f_3fa2_7fa2util___pyx_unpickle_Edge__set_state(struct __pyx_obj_3fa2_7fa2util_Edge *, PyObject *); /*proto*/
static PyObject *__pyx_f_3fa2_7fa2util___pyx_unpickle_Region__set_state(struct __pyx_obj_3fa2_7fa2util_Region *, PyObject *); /*proto*/
#define __Pyx_MODULE_NAME "fa2.fa2util"
extern int __pyx_module_is_main_fa2__fa2util;
int __pyx_module_is_main_fa2__fa2util = 0;

/* Implementation of 'fa2.fa2util' */
static const char __pyx_k_e[] = "e";
static const char __pyx_k_n1[] = "n1";
static const char __pyx_k_n2[] = "n2";
static const char __pyx_k_end[] = "end";
static const char __pyx_k_inf[] = "inf";
static const char __pyx_k_new[] = "__new__";
static const char __pyx_k_Edge[] = "Edge";
static const char __pyx_k_Node[] = "Node";
static const char __pyx_k_dict[] = "__dict__";
static const char __pyx_k_file[] = "file";
static const char __pyx_k_main[] = "__main__";
static const char __pyx_k_math[] = "math";
static const char __pyx_k_name[] = "__name__";
static const char __pyx_k_self[] = "self";
static const char __pyx_k_sqrt[] = "sqrt";
static const char __pyx_k_test[] = "__test__";
static const char __pyx_k_edges[] = "edges";
static const char __pyx_k_nodes[] = "nodes";
static const char __pyx_k_print[] = "print";
static const char __pyx_k_speed[] = "speed";
static const char __pyx_k_state[] = "state";
static const char __pyx_k_theta[] = "theta";
static const char __pyx_k_Region[] = "Region";
static const char __pyx_k_dict_2[] = "_dict";
static const char __pyx_k_import[] = "__import__";
static const char __pyx_k_pickle[] = "pickle";
static const char __pyx_k_reduce[] = "__reduce__";
static const char __pyx_k_update[] = "update";
static const char __pyx_k_gravity[] = "gravity";
static const char __pyx_k_getstate[] = "__getstate__";
static const char __pyx_k_pyx_type[] = "__pyx_type";
static const char __pyx_k_setstate[] = "__setstate__";
static const char __pyx_k_pyx_state[] = "__pyx_state";
static const char __pyx_k_reduce_ex[] = "__reduce_ex__";
static const char __pyx_k_fa2util_py[] = "fa2util.py";
static const char __pyx_k_pyx_result[] = "__pyx_result";
static const char __pyx_k_pyx_vtable[] = "__pyx_vtable__";
static const char __pyx_k_PickleError[] = "PickleError";
static const char __pyx_k_coefficient[] = "coefficient";
static const char __pyx_k_fa2_fa2util[] = "fa2.fa2util";
static const char __pyx_k_pyx_checksum[] = "__pyx_checksum";
static const char __pyx_k_scalingRatio[] = "scalingRatio";
static const char __pyx_k_stringsource[] = "stringsource";
static const char __pyx_k_use_setstate[] = "use_setstate";
static const char __pyx_k_apply_gravity[] = "apply_gravity";
static const char __pyx_k_linAttraction[] = "linAttraction";
static const char __pyx_k_reduce_cython[] = "__reduce_cython__";
static const char __pyx_k_apply_repulsion[] = "apply_repulsion";
static const char __pyx_k_buildSubRegions[] = "buildSubRegions";
static const char __pyx_k_jitterTolerance[] = "jitterTolerance";
static const char __pyx_k_pyx_PickleError[] = "__pyx_PickleError";
static const char __pyx_k_setstate_cython[] = "__setstate_cython__";
static const char __pyx_k_speedEfficiency[] = "speedEfficiency";
static const char __pyx_k_apply_attraction[] = "apply_attraction";
static const char __pyx_k_useStrongGravity[] = "useStrongGravity";
static const char __pyx_k_applyForceOnNodes[] = "applyForceOnNodes";
static const char __pyx_k_pyx_unpickle_Edge[] = "__pyx_unpickle_Edge";
static const char __pyx_k_pyx_unpickle_Node[] = "__pyx_unpickle_Node";
static const char __pyx_k_cline_in_traceback[] = "cline_in_traceback";
static const char __pyx_k_edgeWeightInfluence[] = "edgeWeightInfluence";
static const char __pyx_k_pyx_unpickle_Region[] = "__pyx_unpickle_Region";
static const char __pyx_k_Edge___reduce_cython[] = "Edge.__reduce_cython__";
static const char __pyx_k_Node___reduce_cython[] = "Node.__reduce_cython__";
static const char __pyx_k_distributedAttraction[] = "distributedAttraction";
static const char __pyx_k_Edge___setstate_cython[] = "Edge.__setstate_cython__";
static const char __pyx_k_Node___setstate_cython[] = "Node.__setstate_cython__";
static const char __pyx_k_Region___reduce_cython[] = "Region.__reduce_cython__";
static const char __pyx_k_Region_buildSubRegions[] = "Region.buildSubRegions";
static const char __pyx_k_Region___setstate_cython[] = "Region.__setstate_cython__";
static const char __pyx_k_Region_applyForceOnNodes[] = "Region.applyForceOnNodes";
static const char __pyx_k_adjustSpeedAndApplyForces[] = "adjustSpeedAndApplyForces";
static const char __pyx_k_Incompatible_checksums_s_vs_0x2f[] = "Incompatible checksums (%s vs 0x2f233dd = (dx, dy, mass, old_dx, old_dy, x, y))";
static const char __pyx_k_Incompatible_checksums_s_vs_0x66[] = "Incompatible checksums (%s vs 0x66ef4c7 = (mass, massCenterX, massCenterY, nodes, size, subregions))";
static const char __pyx_k_Incompatible_checksums_s_vs_0xb4[] = "Incompatible checksums (%s vs 0xb469544 = (node1, node2, weight))";
static const char __pyx_k_No_cython_detected_Install_cytho[] = "No cython detected.  Install cython and compile the fa2util module for a 10-100x speed boost.";
static const char __pyx_k_Warning_uncompiled_fa2util_modul[] = "Warning: uncompiled fa2util module.  Compile with cython for a 10-100x speed boost.";
static PyObject *__pyx_n_s_Edge;
static PyObject *__pyx_n_s_Edge___reduce_cython;
static PyObject *__pyx_n_s_Edge___setstate_cython;
static PyObject *__pyx_kp_s_Incompatible_checksums_s_vs_0x2f;
static PyObject *__pyx_kp_s_Incompatible_checksums_s_vs_0x66;
static PyObject *__pyx_kp_s_Incompatible_checksums_s_vs_0xb4;
static PyObject *__pyx_kp_s_No_cython_detected_Install_cytho;
static PyObject *__pyx_n_s_Node;
static PyObject *__pyx_n_s_Node___reduce_cython;
static PyObject *__pyx_n_s_Node___setstate_cython;
static PyObject *__pyx_n_s_PickleError;
static PyObject *__pyx_n_s_Region;
static PyObject *__pyx_n_s_Region___reduce_cython;
static PyObject *__pyx_n_s_Region___setstate_cython;
static PyObject *__pyx_n_s_Region_applyForceOnNodes;
static PyObject *__pyx_n_s_Region_buildSubRegions;
static PyObject *__pyx_kp_s_Warning_uncompiled_fa2util_modul;
static PyObject *__pyx_n_s_adjustSpeedAndApplyForces;
static PyObject *__pyx_n_s_applyForceOnNodes;
static PyObject *__pyx_n_s_apply_attraction;
static PyObject *__pyx_n_s_apply_gravity;
static PyObject *__pyx_n_s_apply_repulsion;
static PyObject *__pyx_n_s_buildSubRegions;
static PyObject *__pyx_n_s_cline_in_traceback;
static PyObject *__pyx_n_s_coefficient;
static PyObject *__pyx_n_s_dict;
static PyObject *__pyx_n_s_dict_2;
static PyObject *__pyx_n_s_distributedAttraction;
static PyObject *__pyx_n_s_e;
static PyObject *__pyx_n_s_edgeWeightInfluence;
static PyObject *__pyx_n_s_edges;
static PyObject *__pyx_n_s_end;
static PyObject *__pyx_n_s_fa2_fa2util;
static PyObject *__pyx_kp_s_fa2util_py;
static PyObject *__pyx_n_s_file;
static PyObject *__pyx_n_s_getstate;
static PyObject *__pyx_n_s_gravity;
static PyObject *__pyx_n_s_import;
static PyObject *__pyx_n_s_inf;
static PyObject *__pyx_n_s_jitterTolerance;
static PyObject *__pyx_n_s_linAttraction;
static PyObject *__pyx_n_s_main;
static PyObject *__pyx_n_s_math;
static PyObject *__pyx_n_s_n1;
static PyObject *__pyx_n_s_n2;
static PyObject *__pyx_n_s_name;
static PyObject *__pyx_n_s_new;
static PyObject *__pyx_n_s_nodes;
static PyObject *__pyx_n_s_pickle;
static PyObject *__pyx_n_s_print;
static PyObject *__pyx_n_s_pyx_PickleError;
static PyObject *__pyx_n_s_pyx_checksum;
static PyObject *__pyx_n_s_pyx_result;
static PyObject *__pyx_n_s_pyx_state;
static PyObject *__pyx_n_s_pyx_type;
static PyObject *__pyx_n_s_pyx_unpickle_Edge;
static PyObject *__pyx_n_s_pyx_unpickle_Node;
static PyObject *__pyx_n_s_pyx_unpickle_Region;
static PyObject *__pyx_n_s_pyx_vtable;
static PyObject *__pyx_n_s_reduce;
static PyObject *__pyx_n_s_reduce_cython;
static PyObject *__pyx_n_s_reduce_ex;
static PyObject *__pyx_n_s_scalingRatio;
static PyObject *__pyx_n_s_self;
static PyObject *__pyx_n_s_setstate;
static PyObject *__pyx_n_s_setstate_cython;
static PyObject *__pyx_n_s_speed;
static PyObject *__pyx_n_s_speedEfficiency;
static PyObject *__pyx_n_s_sqrt;
static PyObject *__pyx_n_s_state;
static PyObject *__pyx_kp_s_stringsource;
static PyObject *__pyx_n_s_test;
static PyObject *__pyx_n_s_theta;
static PyObject *__pyx_n_s_update;
static PyObject *__pyx_n_s_useStrongGravity;
static PyObject *__pyx_n_s_use_setstate;
static int __pyx_pf_3fa2_7fa2util_4Node___init__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Node_4mass___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_4Node_4mass_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Node_6old_dx___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_4Node_6old_dx_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Node_6old_dy___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_4Node_6old_dy_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Node_2dx___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_4Node_2dx_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Node_2dy___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_4Node_2dy_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Node_1x___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_4Node_1x_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Node_1y___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_4Node_1y_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Node_2__reduce_cython__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Node_4__setstate_cython__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v___pyx_state); /* proto */
static int __pyx_pf_3fa2_7fa2util_4Edge___init__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Edge_5node1___get__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_4Edge_5node1_2__set__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Edge_5node2___get__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_4Edge_5node2_2__set__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Edge_6weight___get__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_4Edge_6weight_2__set__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Edge_2__reduce_cython__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4Edge_4__setstate_cython__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self, PyObject *__pyx_v___pyx_state); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_linAttraction(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n1, struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n2, double __pyx_v_e, int __pyx_v_distributedAttraction, double __pyx_v_coefficient); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_2apply_repulsion(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_nodes, double __pyx_v_coefficient); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_4apply_gravity(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_nodes, double __pyx_v_gravity, double __pyx_v_scalingRatio, int __pyx_v_useStrongGravity); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_6apply_attraction(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_nodes, PyObject *__pyx_v_edges, int __pyx_v_distributedAttraction, double __pyx_v_coefficient, double __pyx_v_edgeWeightInfluence); /* proto */
static int __pyx_pf_3fa2_7fa2util_6Region___init__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_nodes); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_6Region_2buildSubRegions(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_6Region_4applyForceOnNodes(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_nodes, double __pyx_v_theta, double __pyx_v_coefficient); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_6Region_4mass___get__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_6Region_4mass_2__set__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_6Region_11massCenterX___get__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_6Region_11massCenterX_2__set__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_6Region_11massCenterY___get__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_6Region_11massCenterY_2__set__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_6Region_4size___get__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_6Region_4size_2__set__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_6Region_5nodes___get__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_6Region_5nodes_2__set__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_3fa2_7fa2util_6Region_5nodes_4__del__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_6Region_10subregions___get__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self); /* proto */
static int __pyx_pf_3fa2_7fa2util_6Region_10subregions_2__set__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_3fa2_7fa2util_6Region_10subregions_4__del__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_6Region_6__reduce_cython__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_6Region_8__setstate_cython__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v___pyx_state); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_8adjustSpeedAndApplyForces(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_nodes, double __pyx_v_speed, double __pyx_v_speedEfficiency, double __pyx_v_jitterTolerance); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_10__pyx_unpickle_Node(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v___pyx_type, long __pyx_v___pyx_checksum, PyObject *__pyx_v___pyx_state); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_12__pyx_unpickle_Edge(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v___pyx_type, long __pyx_v___pyx_checksum, PyObject *__pyx_v___pyx_state); /* proto */
static PyObject *__pyx_pf_3fa2_7fa2util_14__pyx_unpickle_Region(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v___pyx_type, long __pyx_v___pyx_checksum, PyObject *__pyx_v___pyx_state); /* proto */
static PyObject *__pyx_tp_new_3fa2_7fa2util_Node(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_3fa2_7fa2util_Edge(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_3fa2_7fa2util_Region(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_float__05;
static PyObject *__pyx_float_1_0;
static PyObject *__pyx_int_49427421;
static PyObject *__pyx_int_107934919;
static PyObject *__pyx_int_189175108;
static PyObject *__pyx_tuple_;
static PyObject *__pyx_tuple__3;
static PyObject *__pyx_tuple__5;
static PyObject *__pyx_tuple__7;
static PyObject *__pyx_tuple__9;
static PyObject *__pyx_tuple__11;
static PyObject *__pyx_tuple__13;
static PyObject *__pyx_tuple__15;
static PyObject *__pyx_tuple__17;
static PyObject *__pyx_tuple__19;
static PyObject *__pyx_tuple__21;
static PyObject *__pyx_tuple__23;
static PyObject *__pyx_tuple__25;
static PyObject *__pyx_tuple__27;
static PyObject *__pyx_tuple__29;
static PyObject *__pyx_tuple__31;
static PyObject *__pyx_codeobj__2;
static PyObject *__pyx_codeobj__4;
static PyObject *__pyx_codeobj__6;
static PyObject *__pyx_codeobj__8;
static PyObject *__pyx_codeobj__10;
static PyObject *__pyx_codeobj__12;
static PyObject *__pyx_codeobj__14;
static PyObject *__pyx_codeobj__16;
static PyObject *__pyx_codeobj__18;
static PyObject *__pyx_codeobj__20;
static PyObject *__pyx_codeobj__22;
static PyObject *__pyx_codeobj__24;
static PyObject *__pyx_codeobj__26;
static PyObject *__pyx_codeobj__28;
static PyObject *__pyx_codeobj__30;
static PyObject *__pyx_codeobj__32;
/* Late includes */

/* "fa2/fa2util.py":18
 * # This will substitute for the nLayout object
 * class Node:
 *     def __init__(self):             # <<<<<<<<<<<<<<
 *         self.mass = 0.0
 *         self.old_dx = 0.0
 */

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_4Node_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_pw_3fa2_7fa2util_4Node_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  if (unlikely(PyTuple_GET_SIZE(__pyx_args) > 0)) {
    __Pyx_RaiseArgtupleInvalid("__init__", 1, 0, 0, PyTuple_GET_SIZE(__pyx_args)); return -1;}
  if (unlikely(__pyx_kwds) && unlikely(PyDict_Size(__pyx_kwds) > 0) && unlikely(!__Pyx_CheckKeywordStrings(__pyx_kwds, "__init__", 0))) return -1;
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node___init__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_4Node___init__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__", 0);

  /* "fa2/fa2util.py":19
 * class Node:
 *     def __init__(self):
 *         self.mass = 0.0             # <<<<<<<<<<<<<<
 *         self.old_dx = 0.0
 *         self.old_dy = 0.0
 */
  __pyx_v_self->mass = 0.0;

  /* "fa2/fa2util.py":20
 *     def __init__(self):
 *         self.mass = 0.0
 *         self.old_dx = 0.0             # <<<<<<<<<<<<<<
 *         self.old_dy = 0.0
 *         self.dx = 0.0
 */
  __pyx_v_self->old_dx = 0.0;

  /* "fa2/fa2util.py":21
 *         self.mass = 0.0
 *         self.old_dx = 0.0
 *         self.old_dy = 0.0             # <<<<<<<<<<<<<<
 *         self.dx = 0.0
 *         self.dy = 0.0
 */
  __pyx_v_self->old_dy = 0.0;

  /* "fa2/fa2util.py":22
 *         self.old_dx = 0.0
 *         self.old_dy = 0.0
 *         self.dx = 0.0             # <<<<<<<<<<<<<<
 *         self.dy = 0.0
 *         self.x = 0.0
 */
  __pyx_v_self->dx = 0.0;

  /* "fa2/fa2util.py":23
 *         self.old_dy = 0.0
 *         self.dx = 0.0
 *         self.dy = 0.0             # <<<<<<<<<<<<<<
 *         self.x = 0.0
 *         self.y = 0.0
 */
  __pyx_v_self->dy = 0.0;

  /* "fa2/fa2util.py":24
 *         self.dx = 0.0
 *         self.dy = 0.0
 *         self.x = 0.0             # <<<<<<<<<<<<<<
 *         self.y = 0.0
 * 
 */
  __pyx_v_self->x = 0.0;

  /* "fa2/fa2util.py":25
 *         self.dy = 0.0
 *         self.x = 0.0
 *         self.y = 0.0             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_v_self->y = 0.0;

  /* "fa2/fa2util.py":18
 * # This will substitute for the nLayout object
 * class Node:
 *     def __init__(self):             # <<<<<<<<<<<<<<
 *         self.mass = 0.0
 *         self.old_dx = 0.0
 */

  /* function exit code */
  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.pxd":19
 * # This will substitute for the nLayout object
 * cdef class Node:
 *     cdef public double mass             # <<<<<<<<<<<<<<
 *     cdef public double old_dx, old_dy
 *     cdef public double dx, dy
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_4mass_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_4mass_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_4mass___get__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Node_4mass___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->mass); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 19, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Node.mass.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_4Node_4mass_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_4Node_4mass_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_4mass_2__set__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_4Node_4mass_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 19, __pyx_L1_error)
  __pyx_v_self->mass = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Node.mass.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.pxd":20
 * cdef class Node:
 *     cdef public double mass
 *     cdef public double old_dx, old_dy             # <<<<<<<<<<<<<<
 *     cdef public double dx, dy
 *     cdef public double x, y
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_6old_dx_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_6old_dx_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_6old_dx___get__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Node_6old_dx___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->old_dx); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 20, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Node.old_dx.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_4Node_6old_dx_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_4Node_6old_dx_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_6old_dx_2__set__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_4Node_6old_dx_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 20, __pyx_L1_error)
  __pyx_v_self->old_dx = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Node.old_dx.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_6old_dy_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_6old_dy_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_6old_dy___get__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Node_6old_dy___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->old_dy); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 20, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Node.old_dy.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_4Node_6old_dy_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_4Node_6old_dy_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_6old_dy_2__set__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_4Node_6old_dy_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 20, __pyx_L1_error)
  __pyx_v_self->old_dy = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Node.old_dy.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.pxd":21
 *     cdef public double mass
 *     cdef public double old_dx, old_dy
 *     cdef public double dx, dy             # <<<<<<<<<<<<<<
 *     cdef public double x, y
 * 
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_2dx_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_2dx_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_2dx___get__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Node_2dx___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->dx); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 21, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Node.dx.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_4Node_2dx_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_4Node_2dx_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_2dx_2__set__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_4Node_2dx_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 21, __pyx_L1_error)
  __pyx_v_self->dx = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Node.dx.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_2dy_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_2dy_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_2dy___get__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Node_2dy___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->dy); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 21, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Node.dy.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_4Node_2dy_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_4Node_2dy_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_2dy_2__set__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_4Node_2dy_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 21, __pyx_L1_error)
  __pyx_v_self->dy = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Node.dy.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.pxd":22
 *     cdef public double old_dx, old_dy
 *     cdef public double dx, dy
 *     cdef public double x, y             # <<<<<<<<<<<<<<
 * 
 * # This is not in the original java function, but it makes it easier to
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_1x_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_1x_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_1x___get__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Node_1x___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->x); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 22, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Node.x.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_4Node_1x_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_4Node_1x_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_1x_2__set__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_4Node_1x_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 22, __pyx_L1_error)
  __pyx_v_self->x = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Node.x.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_1y_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_1y_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_1y___get__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Node_1y___get__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->y); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 22, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Node.y.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_4Node_1y_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_4Node_1y_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_1y_2__set__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_4Node_1y_2__set__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 22, __pyx_L1_error)
  __pyx_v_self->y = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Node.y.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "(tree fragment)":1
 * def __reduce_cython__(self):             # <<<<<<<<<<<<<<
 *     cdef tuple state
 *     cdef object _dict
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_3__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_4Node_3__reduce_cython__ = {"__reduce_cython__", (PyCFunction)__pyx_pw_3fa2_7fa2util_4Node_3__reduce_cython__, METH_NOARGS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_3__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__reduce_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_2__reduce_cython__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Node_2__reduce_cython__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self) {
  PyObject *__pyx_v_state = 0;
  PyObject *__pyx_v__dict = 0;
  int __pyx_v_use_setstate;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  int __pyx_t_9;
  int __pyx_t_10;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__reduce_cython__", 0);

  /* "(tree fragment)":5
 *     cdef object _dict
 *     cdef bint use_setstate
 *     state = (self.dx, self.dy, self.mass, self.old_dx, self.old_dy, self.x, self.y)             # <<<<<<<<<<<<<<
 *     _dict = getattr(self, '__dict__', None)
 *     if _dict is not None:
 */
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->dx); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyFloat_FromDouble(__pyx_v_self->dy); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyFloat_FromDouble(__pyx_v_self->mass); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = PyFloat_FromDouble(__pyx_v_self->old_dx); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = PyFloat_FromDouble(__pyx_v_self->old_dy); if (unlikely(!__pyx_t_5)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyFloat_FromDouble(__pyx_v_self->x); if (unlikely(!__pyx_t_6)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_7 = PyFloat_FromDouble(__pyx_v_self->y); if (unlikely(!__pyx_t_7)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __pyx_t_8 = PyTuple_New(7); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_8, 1, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_8, 2, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_8, 3, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_8, 4, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_8, 5, __pyx_t_6);
  __Pyx_GIVEREF(__pyx_t_7);
  PyTuple_SET_ITEM(__pyx_t_8, 6, __pyx_t_7);
  __pyx_t_1 = 0;
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_6 = 0;
  __pyx_t_7 = 0;
  __pyx_v_state = ((PyObject*)__pyx_t_8);
  __pyx_t_8 = 0;

  /* "(tree fragment)":6
 *     cdef bint use_setstate
 *     state = (self.dx, self.dy, self.mass, self.old_dx, self.old_dy, self.x, self.y)
 *     _dict = getattr(self, '__dict__', None)             # <<<<<<<<<<<<<<
 *     if _dict is not None:
 *         state += (_dict,)
 */
  __pyx_t_8 = __Pyx_GetAttr3(((PyObject *)__pyx_v_self), __pyx_n_s_dict, Py_None); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_8);
  __pyx_v__dict = __pyx_t_8;
  __pyx_t_8 = 0;

  /* "(tree fragment)":7
 *     state = (self.dx, self.dy, self.mass, self.old_dx, self.old_dy, self.x, self.y)
 *     _dict = getattr(self, '__dict__', None)
 *     if _dict is not None:             # <<<<<<<<<<<<<<
 *         state += (_dict,)
 *         use_setstate = True
 */
  __pyx_t_9 = (__pyx_v__dict != Py_None);
  __pyx_t_10 = (__pyx_t_9 != 0);
  if (__pyx_t_10) {

    /* "(tree fragment)":8
 *     _dict = getattr(self, '__dict__', None)
 *     if _dict is not None:
 *         state += (_dict,)             # <<<<<<<<<<<<<<
 *         use_setstate = True
 *     else:
 */
    __pyx_t_8 = PyTuple_New(1); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 8, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_INCREF(__pyx_v__dict);
    __Pyx_GIVEREF(__pyx_v__dict);
    PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_v__dict);
    __pyx_t_7 = PyNumber_InPlaceAdd(__pyx_v_state, __pyx_t_8); if (unlikely(!__pyx_t_7)) __PYX_ERR(1, 8, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_DECREF_SET(__pyx_v_state, ((PyObject*)__pyx_t_7));
    __pyx_t_7 = 0;

    /* "(tree fragment)":9
 *     if _dict is not None:
 *         state += (_dict,)
 *         use_setstate = True             # <<<<<<<<<<<<<<
 *     else:
 *         use_setstate = False
 */
    __pyx_v_use_setstate = 1;

    /* "(tree fragment)":7
 *     state = (self.dx, self.dy, self.mass, self.old_dx, self.old_dy, self.x, self.y)
 *     _dict = getattr(self, '__dict__', None)
 *     if _dict is not None:             # <<<<<<<<<<<<<<
 *         state += (_dict,)
 *         use_setstate = True
 */
    goto __pyx_L3;
  }

  /* "(tree fragment)":11
 *         use_setstate = True
 *     else:
 *         use_setstate = False             # <<<<<<<<<<<<<<
 *     if use_setstate:
 *         return __pyx_unpickle_Node, (type(self), 0x2f233dd, None), state
 */
  /*else*/ {
    __pyx_v_use_setstate = 0;
  }
  __pyx_L3:;

  /* "(tree fragment)":12
 *     else:
 *         use_setstate = False
 *     if use_setstate:             # <<<<<<<<<<<<<<
 *         return __pyx_unpickle_Node, (type(self), 0x2f233dd, None), state
 *     else:
 */
  __pyx_t_10 = (__pyx_v_use_setstate != 0);
  if (__pyx_t_10) {

    /* "(tree fragment)":13
 *         use_setstate = False
 *     if use_setstate:
 *         return __pyx_unpickle_Node, (type(self), 0x2f233dd, None), state             # <<<<<<<<<<<<<<
 *     else:
 *         return __pyx_unpickle_Node, (type(self), 0x2f233dd, state)
 */
    __Pyx_XDECREF(__pyx_r);
    __Pyx_GetModuleGlobalName(__pyx_t_7, __pyx_n_s_pyx_unpickle_Node); if (unlikely(!__pyx_t_7)) __PYX_ERR(1, 13, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_8 = PyTuple_New(3); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 13, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_INCREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_GIVEREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    PyTuple_SET_ITEM(__pyx_t_8, 0, ((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_INCREF(__pyx_int_49427421);
    __Pyx_GIVEREF(__pyx_int_49427421);
    PyTuple_SET_ITEM(__pyx_t_8, 1, __pyx_int_49427421);
    __Pyx_INCREF(Py_None);
    __Pyx_GIVEREF(Py_None);
    PyTuple_SET_ITEM(__pyx_t_8, 2, Py_None);
    __pyx_t_6 = PyTuple_New(3); if (unlikely(!__pyx_t_6)) __PYX_ERR(1, 13, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_GIVEREF(__pyx_t_7);
    PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_7);
    __Pyx_GIVEREF(__pyx_t_8);
    PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_8);
    __Pyx_INCREF(__pyx_v_state);
    __Pyx_GIVEREF(__pyx_v_state);
    PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_v_state);
    __pyx_t_7 = 0;
    __pyx_t_8 = 0;
    __pyx_r = __pyx_t_6;
    __pyx_t_6 = 0;
    goto __pyx_L0;

    /* "(tree fragment)":12
 *     else:
 *         use_setstate = False
 *     if use_setstate:             # <<<<<<<<<<<<<<
 *         return __pyx_unpickle_Node, (type(self), 0x2f233dd, None), state
 *     else:
 */
  }

  /* "(tree fragment)":15
 *         return __pyx_unpickle_Node, (type(self), 0x2f233dd, None), state
 *     else:
 *         return __pyx_unpickle_Node, (type(self), 0x2f233dd, state)             # <<<<<<<<<<<<<<
 * def __setstate_cython__(self, __pyx_state):
 *     __pyx_unpickle_Node__set_state(self, __pyx_state)
 */
  /*else*/ {
    __Pyx_XDECREF(__pyx_r);
    __Pyx_GetModuleGlobalName(__pyx_t_6, __pyx_n_s_pyx_unpickle_Node); if (unlikely(!__pyx_t_6)) __PYX_ERR(1, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_8 = PyTuple_New(3); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_INCREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_GIVEREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    PyTuple_SET_ITEM(__pyx_t_8, 0, ((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_INCREF(__pyx_int_49427421);
    __Pyx_GIVEREF(__pyx_int_49427421);
    PyTuple_SET_ITEM(__pyx_t_8, 1, __pyx_int_49427421);
    __Pyx_INCREF(__pyx_v_state);
    __Pyx_GIVEREF(__pyx_v_state);
    PyTuple_SET_ITEM(__pyx_t_8, 2, __pyx_v_state);
    __pyx_t_7 = PyTuple_New(2); if (unlikely(!__pyx_t_7)) __PYX_ERR(1, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_GIVEREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_6);
    __Pyx_GIVEREF(__pyx_t_8);
    PyTuple_SET_ITEM(__pyx_t_7, 1, __pyx_t_8);
    __pyx_t_6 = 0;
    __pyx_t_8 = 0;
    __pyx_r = __pyx_t_7;
    __pyx_t_7 = 0;
    goto __pyx_L0;
  }

  /* "(tree fragment)":1
 * def __reduce_cython__(self):             # <<<<<<<<<<<<<<
 *     cdef tuple state
 *     cdef object _dict
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_AddTraceback("fa2.fa2util.Node.__reduce_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_state);
  __Pyx_XDECREF(__pyx_v__dict);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "(tree fragment)":16
 *     else:
 *         return __pyx_unpickle_Node, (type(self), 0x2f233dd, state)
 * def __setstate_cython__(self, __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_unpickle_Node__set_state(self, __pyx_state)
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_5__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_4Node_5__setstate_cython__ = {"__setstate_cython__", (PyCFunction)__pyx_pw_3fa2_7fa2util_4Node_5__setstate_cython__, METH_O, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_4Node_5__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__setstate_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Node_4__setstate_cython__(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v_self), ((PyObject *)__pyx_v___pyx_state));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Node_4__setstate_cython__(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_self, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__setstate_cython__", 0);

  /* "(tree fragment)":17
 *         return __pyx_unpickle_Node, (type(self), 0x2f233dd, state)
 * def __setstate_cython__(self, __pyx_state):
 *     __pyx_unpickle_Node__set_state(self, __pyx_state)             # <<<<<<<<<<<<<<
 */
  if (!(likely(PyTuple_CheckExact(__pyx_v___pyx_state))||((__pyx_v___pyx_state) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "tuple", Py_TYPE(__pyx_v___pyx_state)->tp_name), 0))) __PYX_ERR(1, 17, __pyx_L1_error)
  __pyx_t_1 = __pyx_f_3fa2_7fa2util___pyx_unpickle_Node__set_state(__pyx_v_self, ((PyObject*)__pyx_v___pyx_state)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 17, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "(tree fragment)":16
 *     else:
 *         return __pyx_unpickle_Node, (type(self), 0x2f233dd, state)
 * def __setstate_cython__(self, __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_unpickle_Node__set_state(self, __pyx_state)
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Node.__setstate_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.py":30
 * # This is not in the original java code, but it makes it easier to deal with edges
 * class Edge:
 *     def __init__(self):             # <<<<<<<<<<<<<<
 *         self.node1 = -1
 *         self.node2 = -1
 */

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_4Edge_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_pw_3fa2_7fa2util_4Edge_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  if (unlikely(PyTuple_GET_SIZE(__pyx_args) > 0)) {
    __Pyx_RaiseArgtupleInvalid("__init__", 1, 0, 0, PyTuple_GET_SIZE(__pyx_args)); return -1;}
  if (unlikely(__pyx_kwds) && unlikely(PyDict_Size(__pyx_kwds) > 0) && unlikely(!__Pyx_CheckKeywordStrings(__pyx_kwds, "__init__", 0))) return -1;
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Edge___init__(((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_4Edge___init__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__", 0);

  /* "fa2/fa2util.py":31
 * class Edge:
 *     def __init__(self):
 *         self.node1 = -1             # <<<<<<<<<<<<<<
 *         self.node2 = -1
 *         self.weight = 0.0
 */
  __pyx_v_self->node1 = -1;

  /* "fa2/fa2util.py":32
 *     def __init__(self):
 *         self.node1 = -1
 *         self.node2 = -1             # <<<<<<<<<<<<<<
 *         self.weight = 0.0
 * 
 */
  __pyx_v_self->node2 = -1;

  /* "fa2/fa2util.py":33
 *         self.node1 = -1
 *         self.node2 = -1
 *         self.weight = 0.0             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_v_self->weight = 0.0;

  /* "fa2/fa2util.py":30
 * # This is not in the original java code, but it makes it easier to deal with edges
 * class Edge:
 *     def __init__(self):             # <<<<<<<<<<<<<<
 *         self.node1 = -1
 *         self.node2 = -1
 */

  /* function exit code */
  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.pxd":27
 * # deal with edges.
 * cdef class Edge:
 *     cdef public int node1, node2             # <<<<<<<<<<<<<<
 *     cdef public double weight
 * 
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Edge_5node1_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_4Edge_5node1_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Edge_5node1___get__(((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Edge_5node1___get__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_PyInt_From_int(__pyx_v_self->node1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 27, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Edge.node1.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_4Edge_5node1_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_4Edge_5node1_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Edge_5node1_2__set__(((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_4Edge_5node1_2__set__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __Pyx_PyInt_As_int(__pyx_v_value); if (unlikely((__pyx_t_1 == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 27, __pyx_L1_error)
  __pyx_v_self->node1 = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Edge.node1.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Edge_5node2_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_4Edge_5node2_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Edge_5node2___get__(((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Edge_5node2___get__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_PyInt_From_int(__pyx_v_self->node2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 27, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Edge.node2.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_4Edge_5node2_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_4Edge_5node2_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Edge_5node2_2__set__(((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_4Edge_5node2_2__set__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __Pyx_PyInt_As_int(__pyx_v_value); if (unlikely((__pyx_t_1 == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 27, __pyx_L1_error)
  __pyx_v_self->node2 = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Edge.node2.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.pxd":28
 * cdef class Edge:
 *     cdef public int node1, node2
 *     cdef public double weight             # <<<<<<<<<<<<<<
 * 
 * # Repulsion function.  `n1` and `n2` should be nodes.  This will
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Edge_6weight_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_4Edge_6weight_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Edge_6weight___get__(((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Edge_6weight___get__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->weight); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 28, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Edge.weight.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_4Edge_6weight_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_4Edge_6weight_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Edge_6weight_2__set__(((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_4Edge_6weight_2__set__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 28, __pyx_L1_error)
  __pyx_v_self->weight = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Edge.weight.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "(tree fragment)":1
 * def __reduce_cython__(self):             # <<<<<<<<<<<<<<
 *     cdef tuple state
 *     cdef object _dict
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Edge_3__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_4Edge_3__reduce_cython__ = {"__reduce_cython__", (PyCFunction)__pyx_pw_3fa2_7fa2util_4Edge_3__reduce_cython__, METH_NOARGS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_4Edge_3__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__reduce_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Edge_2__reduce_cython__(((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Edge_2__reduce_cython__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self) {
  PyObject *__pyx_v_state = 0;
  PyObject *__pyx_v__dict = 0;
  int __pyx_v_use_setstate;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_t_5;
  int __pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__reduce_cython__", 0);

  /* "(tree fragment)":5
 *     cdef object _dict
 *     cdef bint use_setstate
 *     state = (self.node1, self.node2, self.weight)             # <<<<<<<<<<<<<<
 *     _dict = getattr(self, '__dict__', None)
 *     if _dict is not None:
 */
  __pyx_t_1 = __Pyx_PyInt_From_int(__pyx_v_self->node1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyInt_From_int(__pyx_v_self->node2); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyFloat_FromDouble(__pyx_v_self->weight); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = PyTuple_New(3); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_4, 2, __pyx_t_3);
  __pyx_t_1 = 0;
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_v_state = ((PyObject*)__pyx_t_4);
  __pyx_t_4 = 0;

  /* "(tree fragment)":6
 *     cdef bint use_setstate
 *     state = (self.node1, self.node2, self.weight)
 *     _dict = getattr(self, '__dict__', None)             # <<<<<<<<<<<<<<
 *     if _dict is not None:
 *         state += (_dict,)
 */
  __pyx_t_4 = __Pyx_GetAttr3(((PyObject *)__pyx_v_self), __pyx_n_s_dict, Py_None); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_v__dict = __pyx_t_4;
  __pyx_t_4 = 0;

  /* "(tree fragment)":7
 *     state = (self.node1, self.node2, self.weight)
 *     _dict = getattr(self, '__dict__', None)
 *     if _dict is not None:             # <<<<<<<<<<<<<<
 *         state += (_dict,)
 *         use_setstate = True
 */
  __pyx_t_5 = (__pyx_v__dict != Py_None);
  __pyx_t_6 = (__pyx_t_5 != 0);
  if (__pyx_t_6) {

    /* "(tree fragment)":8
 *     _dict = getattr(self, '__dict__', None)
 *     if _dict is not None:
 *         state += (_dict,)             # <<<<<<<<<<<<<<
 *         use_setstate = True
 *     else:
 */
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 8, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_INCREF(__pyx_v__dict);
    __Pyx_GIVEREF(__pyx_v__dict);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_v__dict);
    __pyx_t_3 = PyNumber_InPlaceAdd(__pyx_v_state, __pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 8, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_DECREF_SET(__pyx_v_state, ((PyObject*)__pyx_t_3));
    __pyx_t_3 = 0;

    /* "(tree fragment)":9
 *     if _dict is not None:
 *         state += (_dict,)
 *         use_setstate = True             # <<<<<<<<<<<<<<
 *     else:
 *         use_setstate = False
 */
    __pyx_v_use_setstate = 1;

    /* "(tree fragment)":7
 *     state = (self.node1, self.node2, self.weight)
 *     _dict = getattr(self, '__dict__', None)
 *     if _dict is not None:             # <<<<<<<<<<<<<<
 *         state += (_dict,)
 *         use_setstate = True
 */
    goto __pyx_L3;
  }

  /* "(tree fragment)":11
 *         use_setstate = True
 *     else:
 *         use_setstate = False             # <<<<<<<<<<<<<<
 *     if use_setstate:
 *         return __pyx_unpickle_Edge, (type(self), 0xb469544, None), state
 */
  /*else*/ {
    __pyx_v_use_setstate = 0;
  }
  __pyx_L3:;

  /* "(tree fragment)":12
 *     else:
 *         use_setstate = False
 *     if use_setstate:             # <<<<<<<<<<<<<<
 *         return __pyx_unpickle_Edge, (type(self), 0xb469544, None), state
 *     else:
 */
  __pyx_t_6 = (__pyx_v_use_setstate != 0);
  if (__pyx_t_6) {

    /* "(tree fragment)":13
 *         use_setstate = False
 *     if use_setstate:
 *         return __pyx_unpickle_Edge, (type(self), 0xb469544, None), state             # <<<<<<<<<<<<<<
 *     else:
 *         return __pyx_unpickle_Edge, (type(self), 0xb469544, state)
 */
    __Pyx_XDECREF(__pyx_r);
    __Pyx_GetModuleGlobalName(__pyx_t_3, __pyx_n_s_pyx_unpickle_Edge); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 13, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(3); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 13, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_INCREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_GIVEREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    PyTuple_SET_ITEM(__pyx_t_4, 0, ((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_INCREF(__pyx_int_189175108);
    __Pyx_GIVEREF(__pyx_int_189175108);
    PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_int_189175108);
    __Pyx_INCREF(Py_None);
    __Pyx_GIVEREF(Py_None);
    PyTuple_SET_ITEM(__pyx_t_4, 2, Py_None);
    __pyx_t_2 = PyTuple_New(3); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 13, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_4);
    __Pyx_INCREF(__pyx_v_state);
    __Pyx_GIVEREF(__pyx_v_state);
    PyTuple_SET_ITEM(__pyx_t_2, 2, __pyx_v_state);
    __pyx_t_3 = 0;
    __pyx_t_4 = 0;
    __pyx_r = __pyx_t_2;
    __pyx_t_2 = 0;
    goto __pyx_L0;

    /* "(tree fragment)":12
 *     else:
 *         use_setstate = False
 *     if use_setstate:             # <<<<<<<<<<<<<<
 *         return __pyx_unpickle_Edge, (type(self), 0xb469544, None), state
 *     else:
 */
  }

  /* "(tree fragment)":15
 *         return __pyx_unpickle_Edge, (type(self), 0xb469544, None), state
 *     else:
 *         return __pyx_unpickle_Edge, (type(self), 0xb469544, state)             # <<<<<<<<<<<<<<
 * def __setstate_cython__(self, __pyx_state):
 *     __pyx_unpickle_Edge__set_state(self, __pyx_state)
 */
  /*else*/ {
    __Pyx_XDECREF(__pyx_r);
    __Pyx_GetModuleGlobalName(__pyx_t_2, __pyx_n_s_pyx_unpickle_Edge); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_4 = PyTuple_New(3); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_INCREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_GIVEREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    PyTuple_SET_ITEM(__pyx_t_4, 0, ((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_INCREF(__pyx_int_189175108);
    __Pyx_GIVEREF(__pyx_int_189175108);
    PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_int_189175108);
    __Pyx_INCREF(__pyx_v_state);
    __Pyx_GIVEREF(__pyx_v_state);
    PyTuple_SET_ITEM(__pyx_t_4, 2, __pyx_v_state);
    __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_4);
    __pyx_t_2 = 0;
    __pyx_t_4 = 0;
    __pyx_r = __pyx_t_3;
    __pyx_t_3 = 0;
    goto __pyx_L0;
  }

  /* "(tree fragment)":1
 * def __reduce_cython__(self):             # <<<<<<<<<<<<<<
 *     cdef tuple state
 *     cdef object _dict
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("fa2.fa2util.Edge.__reduce_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_state);
  __Pyx_XDECREF(__pyx_v__dict);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "(tree fragment)":16
 *     else:
 *         return __pyx_unpickle_Edge, (type(self), 0xb469544, state)
 * def __setstate_cython__(self, __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_unpickle_Edge__set_state(self, __pyx_state)
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_4Edge_5__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_4Edge_5__setstate_cython__ = {"__setstate_cython__", (PyCFunction)__pyx_pw_3fa2_7fa2util_4Edge_5__setstate_cython__, METH_O, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_4Edge_5__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__setstate_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_4Edge_4__setstate_cython__(((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_v_self), ((PyObject *)__pyx_v___pyx_state));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4Edge_4__setstate_cython__(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_self, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__setstate_cython__", 0);

  /* "(tree fragment)":17
 *         return __pyx_unpickle_Edge, (type(self), 0xb469544, state)
 * def __setstate_cython__(self, __pyx_state):
 *     __pyx_unpickle_Edge__set_state(self, __pyx_state)             # <<<<<<<<<<<<<<
 */
  if (!(likely(PyTuple_CheckExact(__pyx_v___pyx_state))||((__pyx_v___pyx_state) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "tuple", Py_TYPE(__pyx_v___pyx_state)->tp_name), 0))) __PYX_ERR(1, 17, __pyx_L1_error)
  __pyx_t_1 = __pyx_f_3fa2_7fa2util___pyx_unpickle_Edge__set_state(__pyx_v_self, ((PyObject*)__pyx_v___pyx_state)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 17, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "(tree fragment)":16
 *     else:
 *         return __pyx_unpickle_Edge, (type(self), 0xb469544, state)
 * def __setstate_cython__(self, __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_unpickle_Edge__set_state(self, __pyx_state)
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Edge.__setstate_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.py":41
 * # Repulsion function.  `n1` and `n2` should be nodes.  This will
 * # adjust the dx and dy values of `n1`  `n2`
 * def linRepulsion(n1, n2, coefficient=0):             # <<<<<<<<<<<<<<
 *     xDist = n1.x - n2.x
 *     yDist = n1.y - n2.y
 */

static void __pyx_f_3fa2_7fa2util_linRepulsion(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n1, struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n2, struct __pyx_opt_args_3fa2_7fa2util_linRepulsion *__pyx_optional_args) {
  double __pyx_v_coefficient = ((double)0.0);
  double __pyx_v_xDist;
  double __pyx_v_yDist;
  double __pyx_v_distance2;
  double __pyx_v_factor;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  double __pyx_t_2;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("linRepulsion", 0);
  if (__pyx_optional_args) {
    if (__pyx_optional_args->__pyx_n > 0) {
      __pyx_v_coefficient = __pyx_optional_args->coefficient;
    }
  }

  /* "fa2/fa2util.py":42
 * # adjust the dx and dy values of `n1`  `n2`
 * def linRepulsion(n1, n2, coefficient=0):
 *     xDist = n1.x - n2.x             # <<<<<<<<<<<<<<
 *     yDist = n1.y - n2.y
 *     distance2 = xDist * xDist + yDist * yDist  # Distance squared
 */
  __pyx_v_xDist = (__pyx_v_n1->x - __pyx_v_n2->x);

  /* "fa2/fa2util.py":43
 * def linRepulsion(n1, n2, coefficient=0):
 *     xDist = n1.x - n2.x
 *     yDist = n1.y - n2.y             # <<<<<<<<<<<<<<
 *     distance2 = xDist * xDist + yDist * yDist  # Distance squared
 * 
 */
  __pyx_v_yDist = (__pyx_v_n1->y - __pyx_v_n2->y);

  /* "fa2/fa2util.py":44
 *     xDist = n1.x - n2.x
 *     yDist = n1.y - n2.y
 *     distance2 = xDist * xDist + yDist * yDist  # Distance squared             # <<<<<<<<<<<<<<
 * 
 *     if distance2 > 0:
 */
  __pyx_v_distance2 = ((__pyx_v_xDist * __pyx_v_xDist) + (__pyx_v_yDist * __pyx_v_yDist));

  /* "fa2/fa2util.py":46
 *     distance2 = xDist * xDist + yDist * yDist  # Distance squared
 * 
 *     if distance2 > 0:             # <<<<<<<<<<<<<<
 *         factor = coefficient * n1.mass * n2.mass / distance2
 *         n1.dx += xDist * factor
 */
  __pyx_t_1 = ((__pyx_v_distance2 > 0.0) != 0);
  if (__pyx_t_1) {

    /* "fa2/fa2util.py":47
 * 
 *     if distance2 > 0:
 *         factor = coefficient * n1.mass * n2.mass / distance2             # <<<<<<<<<<<<<<
 *         n1.dx += xDist * factor
 *         n1.dy += yDist * factor
 */
    __pyx_t_2 = ((__pyx_v_coefficient * __pyx_v_n1->mass) * __pyx_v_n2->mass);
    if (unlikely(__pyx_v_distance2 == 0)) {
      PyErr_SetString(PyExc_ZeroDivisionError, "float division");
      __PYX_ERR(2, 47, __pyx_L1_error)
    }
    __pyx_v_factor = (__pyx_t_2 / __pyx_v_distance2);

    /* "fa2/fa2util.py":48
 *     if distance2 > 0:
 *         factor = coefficient * n1.mass * n2.mass / distance2
 *         n1.dx += xDist * factor             # <<<<<<<<<<<<<<
 *         n1.dy += yDist * factor
 *         n2.dx -= xDist * factor
 */
    __pyx_v_n1->dx = (__pyx_v_n1->dx + (__pyx_v_xDist * __pyx_v_factor));

    /* "fa2/fa2util.py":49
 *         factor = coefficient * n1.mass * n2.mass / distance2
 *         n1.dx += xDist * factor
 *         n1.dy += yDist * factor             # <<<<<<<<<<<<<<
 *         n2.dx -= xDist * factor
 *         n2.dy -= yDist * factor
 */
    __pyx_v_n1->dy = (__pyx_v_n1->dy + (__pyx_v_yDist * __pyx_v_factor));

    /* "fa2/fa2util.py":50
 *         n1.dx += xDist * factor
 *         n1.dy += yDist * factor
 *         n2.dx -= xDist * factor             # <<<<<<<<<<<<<<
 *         n2.dy -= yDist * factor
 * 
 */
    __pyx_v_n2->dx = (__pyx_v_n2->dx - (__pyx_v_xDist * __pyx_v_factor));

    /* "fa2/fa2util.py":51
 *         n1.dy += yDist * factor
 *         n2.dx -= xDist * factor
 *         n2.dy -= yDist * factor             # <<<<<<<<<<<<<<
 * 
 * 
 */
    __pyx_v_n2->dy = (__pyx_v_n2->dy - (__pyx_v_yDist * __pyx_v_factor));

    /* "fa2/fa2util.py":46
 *     distance2 = xDist * xDist + yDist * yDist  # Distance squared
 * 
 *     if distance2 > 0:             # <<<<<<<<<<<<<<
 *         factor = coefficient * n1.mass * n2.mass / distance2
 *         n1.dx += xDist * factor
 */
  }

  /* "fa2/fa2util.py":41
 * # Repulsion function.  `n1` and `n2` should be nodes.  This will
 * # adjust the dx and dy values of `n1`  `n2`
 * def linRepulsion(n1, n2, coefficient=0):             # <<<<<<<<<<<<<<
 *     xDist = n1.x - n2.x
 *     yDist = n1.y - n2.y
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_WriteUnraisable("fa2.fa2util.linRepulsion", __pyx_clineno, __pyx_lineno, __pyx_filename, 1, 0);
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
}

/* "fa2/fa2util.py":55
 * 
 * # Repulsion function. 'n' is node and 'r' is region
 * def linRepulsion_region(n, r, coefficient=0):             # <<<<<<<<<<<<<<
 *     xDist = n.x - r.massCenterX
 *     yDist = n.y - r.massCenterY
 */

static void __pyx_f_3fa2_7fa2util_linRepulsion_region(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n, struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_r, struct __pyx_opt_args_3fa2_7fa2util_linRepulsion_region *__pyx_optional_args) {
  double __pyx_v_coefficient = ((double)0.0);
  double __pyx_v_xDist;
  double __pyx_v_yDist;
  double __pyx_v_distance2;
  double __pyx_v_factor;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  double __pyx_t_2;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("linRepulsion_region", 0);
  if (__pyx_optional_args) {
    if (__pyx_optional_args->__pyx_n > 0) {
      __pyx_v_coefficient = __pyx_optional_args->coefficient;
    }
  }

  /* "fa2/fa2util.py":56
 * # Repulsion function. 'n' is node and 'r' is region
 * def linRepulsion_region(n, r, coefficient=0):
 *     xDist = n.x - r.massCenterX             # <<<<<<<<<<<<<<
 *     yDist = n.y - r.massCenterY
 *     distance2 = xDist * xDist + yDist * yDist
 */
  __pyx_v_xDist = (__pyx_v_n->x - __pyx_v_r->massCenterX);

  /* "fa2/fa2util.py":57
 * def linRepulsion_region(n, r, coefficient=0):
 *     xDist = n.x - r.massCenterX
 *     yDist = n.y - r.massCenterY             # <<<<<<<<<<<<<<
 *     distance2 = xDist * xDist + yDist * yDist
 * 
 */
  __pyx_v_yDist = (__pyx_v_n->y - __pyx_v_r->massCenterY);

  /* "fa2/fa2util.py":58
 *     xDist = n.x - r.massCenterX
 *     yDist = n.y - r.massCenterY
 *     distance2 = xDist * xDist + yDist * yDist             # <<<<<<<<<<<<<<
 * 
 *     if distance2 > 0:
 */
  __pyx_v_distance2 = ((__pyx_v_xDist * __pyx_v_xDist) + (__pyx_v_yDist * __pyx_v_yDist));

  /* "fa2/fa2util.py":60
 *     distance2 = xDist * xDist + yDist * yDist
 * 
 *     if distance2 > 0:             # <<<<<<<<<<<<<<
 *         factor = coefficient * n.mass * r.mass / distance2
 *         n.dx += xDist * factor
 */
  __pyx_t_1 = ((__pyx_v_distance2 > 0.0) != 0);
  if (__pyx_t_1) {

    /* "fa2/fa2util.py":61
 * 
 *     if distance2 > 0:
 *         factor = coefficient * n.mass * r.mass / distance2             # <<<<<<<<<<<<<<
 *         n.dx += xDist * factor
 *         n.dy += yDist * factor
 */
    __pyx_t_2 = ((__pyx_v_coefficient * __pyx_v_n->mass) * __pyx_v_r->mass);
    if (unlikely(__pyx_v_distance2 == 0)) {
      PyErr_SetString(PyExc_ZeroDivisionError, "float division");
      __PYX_ERR(2, 61, __pyx_L1_error)
    }
    __pyx_v_factor = (__pyx_t_2 / __pyx_v_distance2);

    /* "fa2/fa2util.py":62
 *     if distance2 > 0:
 *         factor = coefficient * n.mass * r.mass / distance2
 *         n.dx += xDist * factor             # <<<<<<<<<<<<<<
 *         n.dy += yDist * factor
 * 
 */
    __pyx_v_n->dx = (__pyx_v_n->dx + (__pyx_v_xDist * __pyx_v_factor));

    /* "fa2/fa2util.py":63
 *         factor = coefficient * n.mass * r.mass / distance2
 *         n.dx += xDist * factor
 *         n.dy += yDist * factor             # <<<<<<<<<<<<<<
 * 
 * 
 */
    __pyx_v_n->dy = (__pyx_v_n->dy + (__pyx_v_yDist * __pyx_v_factor));

    /* "fa2/fa2util.py":60
 *     distance2 = xDist * xDist + yDist * yDist
 * 
 *     if distance2 > 0:             # <<<<<<<<<<<<<<
 *         factor = coefficient * n.mass * r.mass / distance2
 *         n.dx += xDist * factor
 */
  }

  /* "fa2/fa2util.py":55
 * 
 * # Repulsion function. 'n' is node and 'r' is region
 * def linRepulsion_region(n, r, coefficient=0):             # <<<<<<<<<<<<<<
 *     xDist = n.x - r.massCenterX
 *     yDist = n.y - r.massCenterY
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_WriteUnraisable("fa2.fa2util.linRepulsion_region", __pyx_clineno, __pyx_lineno, __pyx_filename, 1, 0);
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
}

/* "fa2/fa2util.py":71
 * # nodes repelling each other, and b. gravity is actually an
 * # attraction)
 * def linGravity(n, g):             # <<<<<<<<<<<<<<
 *     xDist = n.x
 *     yDist = n.y
 */

static void __pyx_f_3fa2_7fa2util_linGravity(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n, double __pyx_v_g) {
  double __pyx_v_xDist;
  double __pyx_v_yDist;
  double __pyx_v_distance;
  double __pyx_v_factor;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("linGravity", 0);

  /* "fa2/fa2util.py":72
 * # attraction)
 * def linGravity(n, g):
 *     xDist = n.x             # <<<<<<<<<<<<<<
 *     yDist = n.y
 *     distance = sqrt(xDist * xDist + yDist * yDist)
 */
  __pyx_t_1 = __pyx_v_n->x;
  __pyx_v_xDist = __pyx_t_1;

  /* "fa2/fa2util.py":73
 * def linGravity(n, g):
 *     xDist = n.x
 *     yDist = n.y             # <<<<<<<<<<<<<<
 *     distance = sqrt(xDist * xDist + yDist * yDist)
 * 
 */
  __pyx_t_1 = __pyx_v_n->y;
  __pyx_v_yDist = __pyx_t_1;

  /* "fa2/fa2util.py":74
 *     xDist = n.x
 *     yDist = n.y
 *     distance = sqrt(xDist * xDist + yDist * yDist)             # <<<<<<<<<<<<<<
 * 
 *     if distance > 0:
 */
  __Pyx_GetModuleGlobalName(__pyx_t_3, __pyx_n_s_sqrt); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 74, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = PyFloat_FromDouble(((__pyx_v_xDist * __pyx_v_xDist) + (__pyx_v_yDist * __pyx_v_yDist))); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 74, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  __pyx_t_2 = (__pyx_t_5) ? __Pyx_PyObject_Call2Args(__pyx_t_3, __pyx_t_5, __pyx_t_4) : __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 74, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_t_2); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 74, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_distance = __pyx_t_1;

  /* "fa2/fa2util.py":76
 *     distance = sqrt(xDist * xDist + yDist * yDist)
 * 
 *     if distance > 0:             # <<<<<<<<<<<<<<
 *         factor = n.mass * g / distance
 *         n.dx -= xDist * factor
 */
  __pyx_t_6 = ((__pyx_v_distance > 0.0) != 0);
  if (__pyx_t_6) {

    /* "fa2/fa2util.py":77
 * 
 *     if distance > 0:
 *         factor = n.mass * g / distance             # <<<<<<<<<<<<<<
 *         n.dx -= xDist * factor
 *         n.dy -= yDist * factor
 */
    __pyx_t_1 = (__pyx_v_n->mass * __pyx_v_g);
    if (unlikely(__pyx_v_distance == 0)) {
      PyErr_SetString(PyExc_ZeroDivisionError, "float division");
      __PYX_ERR(2, 77, __pyx_L1_error)
    }
    __pyx_v_factor = (__pyx_t_1 / __pyx_v_distance);

    /* "fa2/fa2util.py":78
 *     if distance > 0:
 *         factor = n.mass * g / distance
 *         n.dx -= xDist * factor             # <<<<<<<<<<<<<<
 *         n.dy -= yDist * factor
 * 
 */
    __pyx_v_n->dx = (__pyx_v_n->dx - (__pyx_v_xDist * __pyx_v_factor));

    /* "fa2/fa2util.py":79
 *         factor = n.mass * g / distance
 *         n.dx -= xDist * factor
 *         n.dy -= yDist * factor             # <<<<<<<<<<<<<<
 * 
 * 
 */
    __pyx_v_n->dy = (__pyx_v_n->dy - (__pyx_v_yDist * __pyx_v_factor));

    /* "fa2/fa2util.py":76
 *     distance = sqrt(xDist * xDist + yDist * yDist)
 * 
 *     if distance > 0:             # <<<<<<<<<<<<<<
 *         factor = n.mass * g / distance
 *         n.dx -= xDist * factor
 */
  }

  /* "fa2/fa2util.py":71
 * # nodes repelling each other, and b. gravity is actually an
 * # attraction)
 * def linGravity(n, g):             # <<<<<<<<<<<<<<
 *     xDist = n.x
 *     yDist = n.y
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_WriteUnraisable("fa2.fa2util.linGravity", __pyx_clineno, __pyx_lineno, __pyx_filename, 1, 0);
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
}

/* "fa2/fa2util.py":84
 * # Strong gravity force function. `n` should be a node, and `g`
 * # should be a constant by which to apply the force.
 * def strongGravity(n, g, coefficient=0):             # <<<<<<<<<<<<<<
 *     xDist = n.x
 *     yDist = n.y
 */

static void __pyx_f_3fa2_7fa2util_strongGravity(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n, double __pyx_v_g, struct __pyx_opt_args_3fa2_7fa2util_strongGravity *__pyx_optional_args) {
  double __pyx_v_coefficient = ((double)0.0);
  double __pyx_v_xDist;
  double __pyx_v_yDist;
  double __pyx_v_factor;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  __Pyx_RefNannySetupContext("strongGravity", 0);
  if (__pyx_optional_args) {
    if (__pyx_optional_args->__pyx_n > 0) {
      __pyx_v_coefficient = __pyx_optional_args->coefficient;
    }
  }

  /* "fa2/fa2util.py":85
 * # should be a constant by which to apply the force.
 * def strongGravity(n, g, coefficient=0):
 *     xDist = n.x             # <<<<<<<<<<<<<<
 *     yDist = n.y
 * 
 */
  __pyx_t_1 = __pyx_v_n->x;
  __pyx_v_xDist = __pyx_t_1;

  /* "fa2/fa2util.py":86
 * def strongGravity(n, g, coefficient=0):
 *     xDist = n.x
 *     yDist = n.y             # <<<<<<<<<<<<<<
 * 
 *     if xDist != 0 and yDist != 0:
 */
  __pyx_t_1 = __pyx_v_n->y;
  __pyx_v_yDist = __pyx_t_1;

  /* "fa2/fa2util.py":88
 *     yDist = n.y
 * 
 *     if xDist != 0 and yDist != 0:             # <<<<<<<<<<<<<<
 *         factor = coefficient * n.mass * g
 *         n.dx -= xDist * factor
 */
  __pyx_t_3 = ((__pyx_v_xDist != 0.0) != 0);
  if (__pyx_t_3) {
  } else {
    __pyx_t_2 = __pyx_t_3;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_3 = ((__pyx_v_yDist != 0.0) != 0);
  __pyx_t_2 = __pyx_t_3;
  __pyx_L4_bool_binop_done:;
  if (__pyx_t_2) {

    /* "fa2/fa2util.py":89
 * 
 *     if xDist != 0 and yDist != 0:
 *         factor = coefficient * n.mass * g             # <<<<<<<<<<<<<<
 *         n.dx -= xDist * factor
 *         n.dy -= yDist * factor
 */
    __pyx_v_factor = ((__pyx_v_coefficient * __pyx_v_n->mass) * __pyx_v_g);

    /* "fa2/fa2util.py":90
 *     if xDist != 0 and yDist != 0:
 *         factor = coefficient * n.mass * g
 *         n.dx -= xDist * factor             # <<<<<<<<<<<<<<
 *         n.dy -= yDist * factor
 * 
 */
    __pyx_v_n->dx = (__pyx_v_n->dx - (__pyx_v_xDist * __pyx_v_factor));

    /* "fa2/fa2util.py":91
 *         factor = coefficient * n.mass * g
 *         n.dx -= xDist * factor
 *         n.dy -= yDist * factor             # <<<<<<<<<<<<<<
 * 
 * 
 */
    __pyx_v_n->dy = (__pyx_v_n->dy - (__pyx_v_yDist * __pyx_v_factor));

    /* "fa2/fa2util.py":88
 *     yDist = n.y
 * 
 *     if xDist != 0 and yDist != 0:             # <<<<<<<<<<<<<<
 *         factor = coefficient * n.mass * g
 *         n.dx -= xDist * factor
 */
  }

  /* "fa2/fa2util.py":84
 * # Strong gravity force function. `n` should be a node, and `g`
 * # should be a constant by which to apply the force.
 * def strongGravity(n, g, coefficient=0):             # <<<<<<<<<<<<<<
 *     xDist = n.x
 *     yDist = n.y
 */

  /* function exit code */
  __Pyx_RefNannyFinishContext();
}

/* "fa2/fa2util.py":97
 * # adjust the dx and dy values of `n1` and `n2`.  It does
 * # not return anything.
 * def linAttraction(n1, n2, e, distributedAttraction, coefficient=0):             # <<<<<<<<<<<<<<
 *     xDist = n1.x - n2.x
 *     yDist = n1.y - n2.y
 */

static PyObject *__pyx_pw_3fa2_7fa2util_1linAttraction(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static void __pyx_f_3fa2_7fa2util_linAttraction(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n1, struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n2, double __pyx_v_e, int __pyx_v_distributedAttraction, CYTHON_UNUSED int __pyx_skip_dispatch, struct __pyx_opt_args_3fa2_7fa2util_linAttraction *__pyx_optional_args) {
  double __pyx_v_coefficient = ((double)0.0);
  double __pyx_v_xDist;
  double __pyx_v_yDist;
  double __pyx_v_factor;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  double __pyx_t_2;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("linAttraction", 0);
  if (__pyx_optional_args) {
    if (__pyx_optional_args->__pyx_n > 0) {
      __pyx_v_coefficient = __pyx_optional_args->coefficient;
    }
  }

  /* "fa2/fa2util.py":98
 * # not return anything.
 * def linAttraction(n1, n2, e, distributedAttraction, coefficient=0):
 *     xDist = n1.x - n2.x             # <<<<<<<<<<<<<<
 *     yDist = n1.y - n2.y
 *     if not distributedAttraction:
 */
  __pyx_v_xDist = (__pyx_v_n1->x - __pyx_v_n2->x);

  /* "fa2/fa2util.py":99
 * def linAttraction(n1, n2, e, distributedAttraction, coefficient=0):
 *     xDist = n1.x - n2.x
 *     yDist = n1.y - n2.y             # <<<<<<<<<<<<<<
 *     if not distributedAttraction:
 *         factor = -coefficient * e
 */
  __pyx_v_yDist = (__pyx_v_n1->y - __pyx_v_n2->y);

  /* "fa2/fa2util.py":100
 *     xDist = n1.x - n2.x
 *     yDist = n1.y - n2.y
 *     if not distributedAttraction:             # <<<<<<<<<<<<<<
 *         factor = -coefficient * e
 *     else:
 */
  __pyx_t_1 = ((!(__pyx_v_distributedAttraction != 0)) != 0);
  if (__pyx_t_1) {

    /* "fa2/fa2util.py":101
 *     yDist = n1.y - n2.y
 *     if not distributedAttraction:
 *         factor = -coefficient * e             # <<<<<<<<<<<<<<
 *     else:
 *         factor = -coefficient * e / n1.mass
 */
    __pyx_v_factor = ((-__pyx_v_coefficient) * __pyx_v_e);

    /* "fa2/fa2util.py":100
 *     xDist = n1.x - n2.x
 *     yDist = n1.y - n2.y
 *     if not distributedAttraction:             # <<<<<<<<<<<<<<
 *         factor = -coefficient * e
 *     else:
 */
    goto __pyx_L3;
  }

  /* "fa2/fa2util.py":103
 *         factor = -coefficient * e
 *     else:
 *         factor = -coefficient * e / n1.mass             # <<<<<<<<<<<<<<
 *     n1.dx += xDist * factor
 *     n1.dy += yDist * factor
 */
  /*else*/ {
    __pyx_t_2 = ((-__pyx_v_coefficient) * __pyx_v_e);
    if (unlikely(__pyx_v_n1->mass == 0)) {
      PyErr_SetString(PyExc_ZeroDivisionError, "float division");
      __PYX_ERR(2, 103, __pyx_L1_error)
    }
    __pyx_v_factor = (__pyx_t_2 / __pyx_v_n1->mass);
  }
  __pyx_L3:;

  /* "fa2/fa2util.py":104
 *     else:
 *         factor = -coefficient * e / n1.mass
 *     n1.dx += xDist * factor             # <<<<<<<<<<<<<<
 *     n1.dy += yDist * factor
 *     n2.dx -= xDist * factor
 */
  __pyx_v_n1->dx = (__pyx_v_n1->dx + (__pyx_v_xDist * __pyx_v_factor));

  /* "fa2/fa2util.py":105
 *         factor = -coefficient * e / n1.mass
 *     n1.dx += xDist * factor
 *     n1.dy += yDist * factor             # <<<<<<<<<<<<<<
 *     n2.dx -= xDist * factor
 *     n2.dy -= yDist * factor
 */
  __pyx_v_n1->dy = (__pyx_v_n1->dy + (__pyx_v_yDist * __pyx_v_factor));

  /* "fa2/fa2util.py":106
 *     n1.dx += xDist * factor
 *     n1.dy += yDist * factor
 *     n2.dx -= xDist * factor             # <<<<<<<<<<<<<<
 *     n2.dy -= yDist * factor
 * 
 */
  __pyx_v_n2->dx = (__pyx_v_n2->dx - (__pyx_v_xDist * __pyx_v_factor));

  /* "fa2/fa2util.py":107
 *     n1.dy += yDist * factor
 *     n2.dx -= xDist * factor
 *     n2.dy -= yDist * factor             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_v_n2->dy = (__pyx_v_n2->dy - (__pyx_v_yDist * __pyx_v_factor));

  /* "fa2/fa2util.py":97
 * # adjust the dx and dy values of `n1` and `n2`.  It does
 * # not return anything.
 * def linAttraction(n1, n2, e, distributedAttraction, coefficient=0):             # <<<<<<<<<<<<<<
 *     xDist = n1.x - n2.x
 *     yDist = n1.y - n2.y
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_WriteUnraisable("fa2.fa2util.linAttraction", __pyx_clineno, __pyx_lineno, __pyx_filename, 1, 0);
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
}

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_1linAttraction(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_1linAttraction = {"linAttraction", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_3fa2_7fa2util_1linAttraction, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_1linAttraction(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n1 = 0;
  struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n2 = 0;
  double __pyx_v_e;
  int __pyx_v_distributedAttraction;
  double __pyx_v_coefficient;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("linAttraction (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_n1,&__pyx_n_s_n2,&__pyx_n_s_e,&__pyx_n_s_distributedAttraction,&__pyx_n_s_coefficient,0};
    PyObject* values[5] = {0,0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_n1)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_n2)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("linAttraction", 0, 4, 5, 1); __PYX_ERR(2, 97, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (likely((values[2] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_e)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("linAttraction", 0, 4, 5, 2); __PYX_ERR(2, 97, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  3:
        if (likely((values[3] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_distributedAttraction)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("linAttraction", 0, 4, 5, 3); __PYX_ERR(2, 97, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  4:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_coefficient);
          if (value) { values[4] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "linAttraction") < 0)) __PYX_ERR(2, 97, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_n1 = ((struct __pyx_obj_3fa2_7fa2util_Node *)values[0]);
    __pyx_v_n2 = ((struct __pyx_obj_3fa2_7fa2util_Node *)values[1]);
    __pyx_v_e = __pyx_PyFloat_AsDouble(values[2]); if (unlikely((__pyx_v_e == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 97, __pyx_L3_error)
    __pyx_v_distributedAttraction = __Pyx_PyObject_IsTrue(values[3]); if (unlikely((__pyx_v_distributedAttraction == (int)-1) && PyErr_Occurred())) __PYX_ERR(2, 97, __pyx_L3_error)
    if (values[4]) {
      __pyx_v_coefficient = __pyx_PyFloat_AsDouble(values[4]); if (unlikely((__pyx_v_coefficient == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 97, __pyx_L3_error)
    } else {
      __pyx_v_coefficient = ((double)0.0);
    }
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("linAttraction", 0, 4, 5, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(2, 97, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("fa2.fa2util.linAttraction", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_n1), __pyx_ptype_3fa2_7fa2util_Node, 1, "n1", 0))) __PYX_ERR(2, 97, __pyx_L1_error)
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_n2), __pyx_ptype_3fa2_7fa2util_Node, 1, "n2", 0))) __PYX_ERR(2, 97, __pyx_L1_error)
  __pyx_r = __pyx_pf_3fa2_7fa2util_linAttraction(__pyx_self, __pyx_v_n1, __pyx_v_n2, __pyx_v_e, __pyx_v_distributedAttraction, __pyx_v_coefficient);

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_linAttraction(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n1, struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n2, double __pyx_v_e, int __pyx_v_distributedAttraction, double __pyx_v_coefficient) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  struct __pyx_opt_args_3fa2_7fa2util_linAttraction __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("linAttraction", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1.__pyx_n = 1;
  __pyx_t_1.coefficient = __pyx_v_coefficient;
  __pyx_f_3fa2_7fa2util_linAttraction(__pyx_v_n1, __pyx_v_n2, __pyx_v_e, __pyx_v_distributedAttraction, 0, &__pyx_t_1); 
  __pyx_t_2 = __Pyx_void_to_None(NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("fa2.fa2util.linAttraction", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.py":113
 * # the forces directly to the node objects.  These iterations are here
 * # instead of the main file because Python is slow with loops.
 * def apply_repulsion(nodes, coefficient):             # <<<<<<<<<<<<<<
 *     i = 0
 *     for n1 in nodes:
 */

static PyObject *__pyx_pw_3fa2_7fa2util_3apply_repulsion(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static void __pyx_f_3fa2_7fa2util_apply_repulsion(PyObject *__pyx_v_nodes, double __pyx_v_coefficient, CYTHON_UNUSED int __pyx_skip_dispatch) {
  int __pyx_v_i;
  int __pyx_v_j;
  struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n1 = 0;
  struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n2 = 0;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  Py_ssize_t __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  Py_ssize_t __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  struct __pyx_opt_args_3fa2_7fa2util_linRepulsion __pyx_t_7;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("apply_repulsion", 0);

  /* "fa2/fa2util.py":114
 * # instead of the main file because Python is slow with loops.
 * def apply_repulsion(nodes, coefficient):
 *     i = 0             # <<<<<<<<<<<<<<
 *     for n1 in nodes:
 *         j = i
 */
  __pyx_v_i = 0;

  /* "fa2/fa2util.py":115
 * def apply_repulsion(nodes, coefficient):
 *     i = 0
 *     for n1 in nodes:             # <<<<<<<<<<<<<<
 *         j = i
 *         for n2 in nodes:
 */
  if (unlikely(__pyx_v_nodes == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
    __PYX_ERR(2, 115, __pyx_L1_error)
  }
  __pyx_t_1 = __pyx_v_nodes; __Pyx_INCREF(__pyx_t_1); __pyx_t_2 = 0;
  for (;;) {
    if (__pyx_t_2 >= PyList_GET_SIZE(__pyx_t_1)) break;
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    __pyx_t_3 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_3); __pyx_t_2++; if (unlikely(0 < 0)) __PYX_ERR(2, 115, __pyx_L1_error)
    #else
    __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 115, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    #endif
    if (!(likely(((__pyx_t_3) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_3, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 115, __pyx_L1_error)
    __Pyx_XDECREF_SET(__pyx_v_n1, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_3));
    __pyx_t_3 = 0;

    /* "fa2/fa2util.py":116
 *     i = 0
 *     for n1 in nodes:
 *         j = i             # <<<<<<<<<<<<<<
 *         for n2 in nodes:
 *             if j == 0:
 */
    __pyx_v_j = __pyx_v_i;

    /* "fa2/fa2util.py":117
 *     for n1 in nodes:
 *         j = i
 *         for n2 in nodes:             # <<<<<<<<<<<<<<
 *             if j == 0:
 *                 break
 */
    if (unlikely(__pyx_v_nodes == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
      __PYX_ERR(2, 117, __pyx_L1_error)
    }
    __pyx_t_3 = __pyx_v_nodes; __Pyx_INCREF(__pyx_t_3); __pyx_t_4 = 0;
    for (;;) {
      if (__pyx_t_4 >= PyList_GET_SIZE(__pyx_t_3)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_5 = PyList_GET_ITEM(__pyx_t_3, __pyx_t_4); __Pyx_INCREF(__pyx_t_5); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(2, 117, __pyx_L1_error)
      #else
      __pyx_t_5 = PySequence_ITEM(__pyx_t_3, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 117, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      #endif
      if (!(likely(((__pyx_t_5) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_5, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 117, __pyx_L1_error)
      __Pyx_XDECREF_SET(__pyx_v_n2, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_5));
      __pyx_t_5 = 0;

      /* "fa2/fa2util.py":118
 *         j = i
 *         for n2 in nodes:
 *             if j == 0:             # <<<<<<<<<<<<<<
 *                 break
 *             linRepulsion(n1, n2, coefficient)
 */
      __pyx_t_6 = ((__pyx_v_j == 0) != 0);
      if (__pyx_t_6) {

        /* "fa2/fa2util.py":119
 *         for n2 in nodes:
 *             if j == 0:
 *                 break             # <<<<<<<<<<<<<<
 *             linRepulsion(n1, n2, coefficient)
 *             j -= 1
 */
        goto __pyx_L6_break;

        /* "fa2/fa2util.py":118
 *         j = i
 *         for n2 in nodes:
 *             if j == 0:             # <<<<<<<<<<<<<<
 *                 break
 *             linRepulsion(n1, n2, coefficient)
 */
      }

      /* "fa2/fa2util.py":120
 *             if j == 0:
 *                 break
 *             linRepulsion(n1, n2, coefficient)             # <<<<<<<<<<<<<<
 *             j -= 1
 *         i += 1
 */
      __pyx_t_7.__pyx_n = 1;
      __pyx_t_7.coefficient = __pyx_v_coefficient;
      __pyx_f_3fa2_7fa2util_linRepulsion(__pyx_v_n1, __pyx_v_n2, &__pyx_t_7); 

      /* "fa2/fa2util.py":121
 *                 break
 *             linRepulsion(n1, n2, coefficient)
 *             j -= 1             # <<<<<<<<<<<<<<
 *         i += 1
 * 
 */
      __pyx_v_j = (__pyx_v_j - 1);

      /* "fa2/fa2util.py":117
 *     for n1 in nodes:
 *         j = i
 *         for n2 in nodes:             # <<<<<<<<<<<<<<
 *             if j == 0:
 *                 break
 */
    }
    __pyx_L6_break:;
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "fa2/fa2util.py":122
 *             linRepulsion(n1, n2, coefficient)
 *             j -= 1
 *         i += 1             # <<<<<<<<<<<<<<
 * 
 * 
 */
    __pyx_v_i = (__pyx_v_i + 1);

    /* "fa2/fa2util.py":115
 * def apply_repulsion(nodes, coefficient):
 *     i = 0
 *     for n1 in nodes:             # <<<<<<<<<<<<<<
 *         j = i
 *         for n2 in nodes:
 */
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "fa2/fa2util.py":113
 * # the forces directly to the node objects.  These iterations are here
 * # instead of the main file because Python is slow with loops.
 * def apply_repulsion(nodes, coefficient):             # <<<<<<<<<<<<<<
 *     i = 0
 *     for n1 in nodes:
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_WriteUnraisable("fa2.fa2util.apply_repulsion", __pyx_clineno, __pyx_lineno, __pyx_filename, 1, 0);
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_n1);
  __Pyx_XDECREF((PyObject *)__pyx_v_n2);
  __Pyx_RefNannyFinishContext();
}

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_3apply_repulsion(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_3apply_repulsion = {"apply_repulsion", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_3fa2_7fa2util_3apply_repulsion, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_3apply_repulsion(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_nodes = 0;
  double __pyx_v_coefficient;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("apply_repulsion (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_nodes,&__pyx_n_s_coefficient,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_nodes)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_coefficient)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("apply_repulsion", 1, 2, 2, 1); __PYX_ERR(2, 113, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "apply_repulsion") < 0)) __PYX_ERR(2, 113, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_nodes = ((PyObject*)values[0]);
    __pyx_v_coefficient = __pyx_PyFloat_AsDouble(values[1]); if (unlikely((__pyx_v_coefficient == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 113, __pyx_L3_error)
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("apply_repulsion", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(2, 113, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("fa2.fa2util.apply_repulsion", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_nodes), (&PyList_Type), 1, "nodes", 1))) __PYX_ERR(2, 113, __pyx_L1_error)
  __pyx_r = __pyx_pf_3fa2_7fa2util_2apply_repulsion(__pyx_self, __pyx_v_nodes, __pyx_v_coefficient);

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_2apply_repulsion(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_nodes, double __pyx_v_coefficient) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("apply_repulsion", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_void_to_None(__pyx_f_3fa2_7fa2util_apply_repulsion(__pyx_v_nodes, __pyx_v_coefficient, 0)); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 113, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.apply_repulsion", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.py":125
 * 
 * 
 * def apply_gravity(nodes, gravity, scalingRatio, useStrongGravity=False):             # <<<<<<<<<<<<<<
 *     if not useStrongGravity:
 *         for n in nodes:
 */

static PyObject *__pyx_pw_3fa2_7fa2util_5apply_gravity(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static void __pyx_f_3fa2_7fa2util_apply_gravity(PyObject *__pyx_v_nodes, double __pyx_v_gravity, double __pyx_v_scalingRatio, CYTHON_UNUSED int __pyx_skip_dispatch, struct __pyx_opt_args_3fa2_7fa2util_apply_gravity *__pyx_optional_args) {
  int __pyx_v_useStrongGravity = ((int)0);
  struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n = 0;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  Py_ssize_t __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  struct __pyx_opt_args_3fa2_7fa2util_strongGravity __pyx_t_5;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("apply_gravity", 0);
  if (__pyx_optional_args) {
    if (__pyx_optional_args->__pyx_n > 0) {
      __pyx_v_useStrongGravity = __pyx_optional_args->useStrongGravity;
    }
  }

  /* "fa2/fa2util.py":126
 * 
 * def apply_gravity(nodes, gravity, scalingRatio, useStrongGravity=False):
 *     if not useStrongGravity:             # <<<<<<<<<<<<<<
 *         for n in nodes:
 *             linGravity(n, gravity)
 */
  __pyx_t_1 = ((!(__pyx_v_useStrongGravity != 0)) != 0);
  if (__pyx_t_1) {

    /* "fa2/fa2util.py":127
 * def apply_gravity(nodes, gravity, scalingRatio, useStrongGravity=False):
 *     if not useStrongGravity:
 *         for n in nodes:             # <<<<<<<<<<<<<<
 *             linGravity(n, gravity)
 *     else:
 */
    if (unlikely(__pyx_v_nodes == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
      __PYX_ERR(2, 127, __pyx_L1_error)
    }
    __pyx_t_2 = __pyx_v_nodes; __Pyx_INCREF(__pyx_t_2); __pyx_t_3 = 0;
    for (;;) {
      if (__pyx_t_3 >= PyList_GET_SIZE(__pyx_t_2)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_4 = PyList_GET_ITEM(__pyx_t_2, __pyx_t_3); __Pyx_INCREF(__pyx_t_4); __pyx_t_3++; if (unlikely(0 < 0)) __PYX_ERR(2, 127, __pyx_L1_error)
      #else
      __pyx_t_4 = PySequence_ITEM(__pyx_t_2, __pyx_t_3); __pyx_t_3++; if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 127, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      #endif
      if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 127, __pyx_L1_error)
      __Pyx_XDECREF_SET(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_4));
      __pyx_t_4 = 0;

      /* "fa2/fa2util.py":128
 *     if not useStrongGravity:
 *         for n in nodes:
 *             linGravity(n, gravity)             # <<<<<<<<<<<<<<
 *     else:
 *         for n in nodes:
 */
      __pyx_f_3fa2_7fa2util_linGravity(__pyx_v_n, __pyx_v_gravity);

      /* "fa2/fa2util.py":127
 * def apply_gravity(nodes, gravity, scalingRatio, useStrongGravity=False):
 *     if not useStrongGravity:
 *         for n in nodes:             # <<<<<<<<<<<<<<
 *             linGravity(n, gravity)
 *     else:
 */
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "fa2/fa2util.py":126
 * 
 * def apply_gravity(nodes, gravity, scalingRatio, useStrongGravity=False):
 *     if not useStrongGravity:             # <<<<<<<<<<<<<<
 *         for n in nodes:
 *             linGravity(n, gravity)
 */
    goto __pyx_L3;
  }

  /* "fa2/fa2util.py":130
 *             linGravity(n, gravity)
 *     else:
 *         for n in nodes:             # <<<<<<<<<<<<<<
 *             strongGravity(n, gravity, scalingRatio)
 * 
 */
  /*else*/ {
    if (unlikely(__pyx_v_nodes == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
      __PYX_ERR(2, 130, __pyx_L1_error)
    }
    __pyx_t_2 = __pyx_v_nodes; __Pyx_INCREF(__pyx_t_2); __pyx_t_3 = 0;
    for (;;) {
      if (__pyx_t_3 >= PyList_GET_SIZE(__pyx_t_2)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_4 = PyList_GET_ITEM(__pyx_t_2, __pyx_t_3); __Pyx_INCREF(__pyx_t_4); __pyx_t_3++; if (unlikely(0 < 0)) __PYX_ERR(2, 130, __pyx_L1_error)
      #else
      __pyx_t_4 = PySequence_ITEM(__pyx_t_2, __pyx_t_3); __pyx_t_3++; if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 130, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      #endif
      if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 130, __pyx_L1_error)
      __Pyx_XDECREF_SET(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_4));
      __pyx_t_4 = 0;

      /* "fa2/fa2util.py":131
 *     else:
 *         for n in nodes:
 *             strongGravity(n, gravity, scalingRatio)             # <<<<<<<<<<<<<<
 * 
 * 
 */
      __pyx_t_5.__pyx_n = 1;
      __pyx_t_5.coefficient = __pyx_v_scalingRatio;
      __pyx_f_3fa2_7fa2util_strongGravity(__pyx_v_n, __pyx_v_gravity, &__pyx_t_5); 

      /* "fa2/fa2util.py":130
 *             linGravity(n, gravity)
 *     else:
 *         for n in nodes:             # <<<<<<<<<<<<<<
 *             strongGravity(n, gravity, scalingRatio)
 * 
 */
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  }
  __pyx_L3:;

  /* "fa2/fa2util.py":125
 * 
 * 
 * def apply_gravity(nodes, gravity, scalingRatio, useStrongGravity=False):             # <<<<<<<<<<<<<<
 *     if not useStrongGravity:
 *         for n in nodes:
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_WriteUnraisable("fa2.fa2util.apply_gravity", __pyx_clineno, __pyx_lineno, __pyx_filename, 1, 0);
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_n);
  __Pyx_RefNannyFinishContext();
}

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_5apply_gravity(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_5apply_gravity = {"apply_gravity", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_3fa2_7fa2util_5apply_gravity, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_5apply_gravity(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_nodes = 0;
  double __pyx_v_gravity;
  double __pyx_v_scalingRatio;
  int __pyx_v_useStrongGravity;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("apply_gravity (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_nodes,&__pyx_n_s_gravity,&__pyx_n_s_scalingRatio,&__pyx_n_s_useStrongGravity,0};
    PyObject* values[4] = {0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_nodes)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_gravity)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("apply_gravity", 0, 3, 4, 1); __PYX_ERR(2, 125, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (likely((values[2] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_scalingRatio)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("apply_gravity", 0, 3, 4, 2); __PYX_ERR(2, 125, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  3:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_useStrongGravity);
          if (value) { values[3] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "apply_gravity") < 0)) __PYX_ERR(2, 125, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_nodes = ((PyObject*)values[0]);
    __pyx_v_gravity = __pyx_PyFloat_AsDouble(values[1]); if (unlikely((__pyx_v_gravity == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 125, __pyx_L3_error)
    __pyx_v_scalingRatio = __pyx_PyFloat_AsDouble(values[2]); if (unlikely((__pyx_v_scalingRatio == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 125, __pyx_L3_error)
    if (values[3]) {
      __pyx_v_useStrongGravity = __Pyx_PyObject_IsTrue(values[3]); if (unlikely((__pyx_v_useStrongGravity == (int)-1) && PyErr_Occurred())) __PYX_ERR(2, 125, __pyx_L3_error)
    } else {
      __pyx_v_useStrongGravity = ((int)0);
    }
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("apply_gravity", 0, 3, 4, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(2, 125, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("fa2.fa2util.apply_gravity", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_nodes), (&PyList_Type), 1, "nodes", 1))) __PYX_ERR(2, 125, __pyx_L1_error)
  __pyx_r = __pyx_pf_3fa2_7fa2util_4apply_gravity(__pyx_self, __pyx_v_nodes, __pyx_v_gravity, __pyx_v_scalingRatio, __pyx_v_useStrongGravity);

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_4apply_gravity(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_nodes, double __pyx_v_gravity, double __pyx_v_scalingRatio, int __pyx_v_useStrongGravity) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  struct __pyx_opt_args_3fa2_7fa2util_apply_gravity __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("apply_gravity", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1.__pyx_n = 1;
  __pyx_t_1.useStrongGravity = __pyx_v_useStrongGravity;
  __pyx_f_3fa2_7fa2util_apply_gravity(__pyx_v_nodes, __pyx_v_gravity, __pyx_v_scalingRatio, 0, &__pyx_t_1); 
  __pyx_t_2 = __Pyx_void_to_None(NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 125, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("fa2.fa2util.apply_gravity", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.py":134
 * 
 * 
 * def apply_attraction(nodes, edges, distributedAttraction, coefficient, edgeWeightInfluence):             # <<<<<<<<<<<<<<
 *     # Optimization, since usually edgeWeightInfluence is 0 or 1, and pow is slow
 *     if edgeWeightInfluence == 0:
 */

static PyObject *__pyx_pw_3fa2_7fa2util_7apply_attraction(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static void __pyx_f_3fa2_7fa2util_apply_attraction(PyObject *__pyx_v_nodes, PyObject *__pyx_v_edges, int __pyx_v_distributedAttraction, double __pyx_v_coefficient, double __pyx_v_edgeWeightInfluence, CYTHON_UNUSED int __pyx_skip_dispatch) {
  struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v_edge = 0;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  Py_ssize_t __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  struct __pyx_opt_args_3fa2_7fa2util_linAttraction __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  double __pyx_t_10;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("apply_attraction", 0);

  /* "fa2/fa2util.py":136
 * def apply_attraction(nodes, edges, distributedAttraction, coefficient, edgeWeightInfluence):
 *     # Optimization, since usually edgeWeightInfluence is 0 or 1, and pow is slow
 *     if edgeWeightInfluence == 0:             # <<<<<<<<<<<<<<
 *         for edge in edges:
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], 1, distributedAttraction, coefficient)
 */
  __pyx_t_1 = ((__pyx_v_edgeWeightInfluence == 0.0) != 0);
  if (__pyx_t_1) {

    /* "fa2/fa2util.py":137
 *     # Optimization, since usually edgeWeightInfluence is 0 or 1, and pow is slow
 *     if edgeWeightInfluence == 0:
 *         for edge in edges:             # <<<<<<<<<<<<<<
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], 1, distributedAttraction, coefficient)
 *     elif edgeWeightInfluence == 1:
 */
    if (unlikely(__pyx_v_edges == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
      __PYX_ERR(2, 137, __pyx_L1_error)
    }
    __pyx_t_2 = __pyx_v_edges; __Pyx_INCREF(__pyx_t_2); __pyx_t_3 = 0;
    for (;;) {
      if (__pyx_t_3 >= PyList_GET_SIZE(__pyx_t_2)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_4 = PyList_GET_ITEM(__pyx_t_2, __pyx_t_3); __Pyx_INCREF(__pyx_t_4); __pyx_t_3++; if (unlikely(0 < 0)) __PYX_ERR(2, 137, __pyx_L1_error)
      #else
      __pyx_t_4 = PySequence_ITEM(__pyx_t_2, __pyx_t_3); __pyx_t_3++; if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 137, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      #endif
      if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_3fa2_7fa2util_Edge))))) __PYX_ERR(2, 137, __pyx_L1_error)
      __Pyx_XDECREF_SET(__pyx_v_edge, ((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_t_4));
      __pyx_t_4 = 0;

      /* "fa2/fa2util.py":138
 *     if edgeWeightInfluence == 0:
 *         for edge in edges:
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], 1, distributedAttraction, coefficient)             # <<<<<<<<<<<<<<
 *     elif edgeWeightInfluence == 1:
 *         for edge in edges:
 */
      if (unlikely(__pyx_v_nodes == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
        __PYX_ERR(2, 138, __pyx_L1_error)
      }
      __pyx_t_4 = __Pyx_GetItemInt_List(__pyx_v_nodes, __pyx_v_edge->node1, int, 1, __Pyx_PyInt_From_int, 1, 1, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 138, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 138, __pyx_L1_error)
      if (unlikely(__pyx_v_nodes == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
        __PYX_ERR(2, 138, __pyx_L1_error)
      }
      __pyx_t_5 = __Pyx_GetItemInt_List(__pyx_v_nodes, __pyx_v_edge->node2, int, 1, __Pyx_PyInt_From_int, 1, 1, 1); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 138, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      if (!(likely(((__pyx_t_5) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_5, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 138, __pyx_L1_error)
      __pyx_t_6.__pyx_n = 1;
      __pyx_t_6.coefficient = __pyx_v_coefficient;
      __pyx_f_3fa2_7fa2util_linAttraction(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_4), ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_5), 1.0, __pyx_v_distributedAttraction, 0, &__pyx_t_6); 
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

      /* "fa2/fa2util.py":137
 *     # Optimization, since usually edgeWeightInfluence is 0 or 1, and pow is slow
 *     if edgeWeightInfluence == 0:
 *         for edge in edges:             # <<<<<<<<<<<<<<
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], 1, distributedAttraction, coefficient)
 *     elif edgeWeightInfluence == 1:
 */
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "fa2/fa2util.py":136
 * def apply_attraction(nodes, edges, distributedAttraction, coefficient, edgeWeightInfluence):
 *     # Optimization, since usually edgeWeightInfluence is 0 or 1, and pow is slow
 *     if edgeWeightInfluence == 0:             # <<<<<<<<<<<<<<
 *         for edge in edges:
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], 1, distributedAttraction, coefficient)
 */
    goto __pyx_L3;
  }

  /* "fa2/fa2util.py":139
 *         for edge in edges:
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], 1, distributedAttraction, coefficient)
 *     elif edgeWeightInfluence == 1:             # <<<<<<<<<<<<<<
 *         for edge in edges:
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], edge.weight, distributedAttraction, coefficient)
 */
  __pyx_t_1 = ((__pyx_v_edgeWeightInfluence == 1.0) != 0);
  if (__pyx_t_1) {

    /* "fa2/fa2util.py":140
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], 1, distributedAttraction, coefficient)
 *     elif edgeWeightInfluence == 1:
 *         for edge in edges:             # <<<<<<<<<<<<<<
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], edge.weight, distributedAttraction, coefficient)
 *     else:
 */
    if (unlikely(__pyx_v_edges == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
      __PYX_ERR(2, 140, __pyx_L1_error)
    }
    __pyx_t_2 = __pyx_v_edges; __Pyx_INCREF(__pyx_t_2); __pyx_t_3 = 0;
    for (;;) {
      if (__pyx_t_3 >= PyList_GET_SIZE(__pyx_t_2)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_5 = PyList_GET_ITEM(__pyx_t_2, __pyx_t_3); __Pyx_INCREF(__pyx_t_5); __pyx_t_3++; if (unlikely(0 < 0)) __PYX_ERR(2, 140, __pyx_L1_error)
      #else
      __pyx_t_5 = PySequence_ITEM(__pyx_t_2, __pyx_t_3); __pyx_t_3++; if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 140, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      #endif
      if (!(likely(((__pyx_t_5) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_5, __pyx_ptype_3fa2_7fa2util_Edge))))) __PYX_ERR(2, 140, __pyx_L1_error)
      __Pyx_XDECREF_SET(__pyx_v_edge, ((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_t_5));
      __pyx_t_5 = 0;

      /* "fa2/fa2util.py":141
 *     elif edgeWeightInfluence == 1:
 *         for edge in edges:
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], edge.weight, distributedAttraction, coefficient)             # <<<<<<<<<<<<<<
 *     else:
 *         for edge in edges:
 */
      if (unlikely(__pyx_v_nodes == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
        __PYX_ERR(2, 141, __pyx_L1_error)
      }
      __pyx_t_5 = __Pyx_GetItemInt_List(__pyx_v_nodes, __pyx_v_edge->node1, int, 1, __Pyx_PyInt_From_int, 1, 1, 1); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 141, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      if (!(likely(((__pyx_t_5) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_5, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 141, __pyx_L1_error)
      if (unlikely(__pyx_v_nodes == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
        __PYX_ERR(2, 141, __pyx_L1_error)
      }
      __pyx_t_4 = __Pyx_GetItemInt_List(__pyx_v_nodes, __pyx_v_edge->node2, int, 1, __Pyx_PyInt_From_int, 1, 1, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 141, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 141, __pyx_L1_error)
      __pyx_t_6.__pyx_n = 1;
      __pyx_t_6.coefficient = __pyx_v_coefficient;
      __pyx_f_3fa2_7fa2util_linAttraction(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_5), ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_4), __pyx_v_edge->weight, __pyx_v_distributedAttraction, 0, &__pyx_t_6); 
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

      /* "fa2/fa2util.py":140
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], 1, distributedAttraction, coefficient)
 *     elif edgeWeightInfluence == 1:
 *         for edge in edges:             # <<<<<<<<<<<<<<
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], edge.weight, distributedAttraction, coefficient)
 *     else:
 */
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "fa2/fa2util.py":139
 *         for edge in edges:
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], 1, distributedAttraction, coefficient)
 *     elif edgeWeightInfluence == 1:             # <<<<<<<<<<<<<<
 *         for edge in edges:
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], edge.weight, distributedAttraction, coefficient)
 */
    goto __pyx_L3;
  }

  /* "fa2/fa2util.py":143
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], edge.weight, distributedAttraction, coefficient)
 *     else:
 *         for edge in edges:             # <<<<<<<<<<<<<<
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], pow(edge.weight, edgeWeightInfluence),
 *                           distributedAttraction, coefficient)
 */
  /*else*/ {
    if (unlikely(__pyx_v_edges == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
      __PYX_ERR(2, 143, __pyx_L1_error)
    }
    __pyx_t_2 = __pyx_v_edges; __Pyx_INCREF(__pyx_t_2); __pyx_t_3 = 0;
    for (;;) {
      if (__pyx_t_3 >= PyList_GET_SIZE(__pyx_t_2)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_4 = PyList_GET_ITEM(__pyx_t_2, __pyx_t_3); __Pyx_INCREF(__pyx_t_4); __pyx_t_3++; if (unlikely(0 < 0)) __PYX_ERR(2, 143, __pyx_L1_error)
      #else
      __pyx_t_4 = PySequence_ITEM(__pyx_t_2, __pyx_t_3); __pyx_t_3++; if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 143, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      #endif
      if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_3fa2_7fa2util_Edge))))) __PYX_ERR(2, 143, __pyx_L1_error)
      __Pyx_XDECREF_SET(__pyx_v_edge, ((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_t_4));
      __pyx_t_4 = 0;

      /* "fa2/fa2util.py":144
 *     else:
 *         for edge in edges:
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], pow(edge.weight, edgeWeightInfluence),             # <<<<<<<<<<<<<<
 *                           distributedAttraction, coefficient)
 * 
 */
      if (unlikely(__pyx_v_nodes == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
        __PYX_ERR(2, 144, __pyx_L1_error)
      }
      __pyx_t_4 = __Pyx_GetItemInt_List(__pyx_v_nodes, __pyx_v_edge->node1, int, 1, __Pyx_PyInt_From_int, 1, 1, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 144, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 144, __pyx_L1_error)
      if (unlikely(__pyx_v_nodes == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
        __PYX_ERR(2, 144, __pyx_L1_error)
      }
      __pyx_t_5 = __Pyx_GetItemInt_List(__pyx_v_nodes, __pyx_v_edge->node2, int, 1, __Pyx_PyInt_From_int, 1, 1, 1); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 144, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      if (!(likely(((__pyx_t_5) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_5, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 144, __pyx_L1_error)
      __pyx_t_7 = PyFloat_FromDouble(__pyx_v_edge->weight); if (unlikely(!__pyx_t_7)) __PYX_ERR(2, 144, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_8 = PyFloat_FromDouble(__pyx_v_edgeWeightInfluence); if (unlikely(!__pyx_t_8)) __PYX_ERR(2, 144, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_9 = __Pyx_PyNumber_Power2(__pyx_t_7, __pyx_t_8); if (unlikely(!__pyx_t_9)) __PYX_ERR(2, 144, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      __pyx_t_10 = __pyx_PyFloat_AsDouble(__pyx_t_9); if (unlikely((__pyx_t_10 == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 144, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;

      /* "fa2/fa2util.py":145
 *         for edge in edges:
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], pow(edge.weight, edgeWeightInfluence),
 *                           distributedAttraction, coefficient)             # <<<<<<<<<<<<<<
 * 
 * 
 */
      __pyx_t_6.__pyx_n = 1;
      __pyx_t_6.coefficient = __pyx_v_coefficient;
      __pyx_f_3fa2_7fa2util_linAttraction(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_4), ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_5), __pyx_t_10, __pyx_v_distributedAttraction, 0, &__pyx_t_6); 
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

      /* "fa2/fa2util.py":143
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], edge.weight, distributedAttraction, coefficient)
 *     else:
 *         for edge in edges:             # <<<<<<<<<<<<<<
 *             linAttraction(nodes[edge.node1], nodes[edge.node2], pow(edge.weight, edgeWeightInfluence),
 *                           distributedAttraction, coefficient)
 */
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  }
  __pyx_L3:;

  /* "fa2/fa2util.py":134
 * 
 * 
 * def apply_attraction(nodes, edges, distributedAttraction, coefficient, edgeWeightInfluence):             # <<<<<<<<<<<<<<
 *     # Optimization, since usually edgeWeightInfluence is 0 or 1, and pow is slow
 *     if edgeWeightInfluence == 0:
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_WriteUnraisable("fa2.fa2util.apply_attraction", __pyx_clineno, __pyx_lineno, __pyx_filename, 1, 0);
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_edge);
  __Pyx_RefNannyFinishContext();
}

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_7apply_attraction(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_7apply_attraction = {"apply_attraction", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_3fa2_7fa2util_7apply_attraction, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_7apply_attraction(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_nodes = 0;
  PyObject *__pyx_v_edges = 0;
  int __pyx_v_distributedAttraction;
  double __pyx_v_coefficient;
  double __pyx_v_edgeWeightInfluence;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("apply_attraction (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_nodes,&__pyx_n_s_edges,&__pyx_n_s_distributedAttraction,&__pyx_n_s_coefficient,&__pyx_n_s_edgeWeightInfluence,0};
    PyObject* values[5] = {0,0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_nodes)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_edges)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("apply_attraction", 1, 5, 5, 1); __PYX_ERR(2, 134, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (likely((values[2] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_distributedAttraction)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("apply_attraction", 1, 5, 5, 2); __PYX_ERR(2, 134, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  3:
        if (likely((values[3] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_coefficient)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("apply_attraction", 1, 5, 5, 3); __PYX_ERR(2, 134, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  4:
        if (likely((values[4] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_edgeWeightInfluence)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("apply_attraction", 1, 5, 5, 4); __PYX_ERR(2, 134, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "apply_attraction") < 0)) __PYX_ERR(2, 134, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 5) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
      values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
      values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
    }
    __pyx_v_nodes = ((PyObject*)values[0]);
    __pyx_v_edges = ((PyObject*)values[1]);
    __pyx_v_distributedAttraction = __Pyx_PyObject_IsTrue(values[2]); if (unlikely((__pyx_v_distributedAttraction == (int)-1) && PyErr_Occurred())) __PYX_ERR(2, 134, __pyx_L3_error)
    __pyx_v_coefficient = __pyx_PyFloat_AsDouble(values[3]); if (unlikely((__pyx_v_coefficient == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 134, __pyx_L3_error)
    __pyx_v_edgeWeightInfluence = __pyx_PyFloat_AsDouble(values[4]); if (unlikely((__pyx_v_edgeWeightInfluence == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 134, __pyx_L3_error)
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("apply_attraction", 1, 5, 5, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(2, 134, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("fa2.fa2util.apply_attraction", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_nodes), (&PyList_Type), 1, "nodes", 1))) __PYX_ERR(2, 134, __pyx_L1_error)
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_edges), (&PyList_Type), 1, "edges", 1))) __PYX_ERR(2, 134, __pyx_L1_error)
  __pyx_r = __pyx_pf_3fa2_7fa2util_6apply_attraction(__pyx_self, __pyx_v_nodes, __pyx_v_edges, __pyx_v_distributedAttraction, __pyx_v_coefficient, __pyx_v_edgeWeightInfluence);

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_6apply_attraction(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_nodes, PyObject *__pyx_v_edges, int __pyx_v_distributedAttraction, double __pyx_v_coefficient, double __pyx_v_edgeWeightInfluence) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("apply_attraction", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_void_to_None(__pyx_f_3fa2_7fa2util_apply_attraction(__pyx_v_nodes, __pyx_v_edges, __pyx_v_distributedAttraction, __pyx_v_coefficient, __pyx_v_edgeWeightInfluence, 0)); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 134, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.apply_attraction", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.py":150
 * # For Barnes Hut Optimization
 * class Region:
 *     def __init__(self, nodes):             # <<<<<<<<<<<<<<
 *         self.mass = 0.0
 *         self.massCenterX = 0.0
 */

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_6Region_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_pw_3fa2_7fa2util_6Region_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_nodes = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_nodes,0};
    PyObject* values[1] = {0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_nodes)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__init__") < 0)) __PYX_ERR(2, 150, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 1) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
    }
    __pyx_v_nodes = values[0];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 1, 1, 1, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(2, 150, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("fa2.fa2util.Region.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return -1;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region___init__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self), __pyx_v_nodes);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_6Region___init__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_nodes) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__init__", 0);

  /* "fa2/fa2util.py":151
 * class Region:
 *     def __init__(self, nodes):
 *         self.mass = 0.0             # <<<<<<<<<<<<<<
 *         self.massCenterX = 0.0
 *         self.massCenterY = 0.0
 */
  __pyx_v_self->mass = 0.0;

  /* "fa2/fa2util.py":152
 *     def __init__(self, nodes):
 *         self.mass = 0.0
 *         self.massCenterX = 0.0             # <<<<<<<<<<<<<<
 *         self.massCenterY = 0.0
 *         self.size = 0.0
 */
  __pyx_v_self->massCenterX = 0.0;

  /* "fa2/fa2util.py":153
 *         self.mass = 0.0
 *         self.massCenterX = 0.0
 *         self.massCenterY = 0.0             # <<<<<<<<<<<<<<
 *         self.size = 0.0
 *         self.nodes = nodes
 */
  __pyx_v_self->massCenterY = 0.0;

  /* "fa2/fa2util.py":154
 *         self.massCenterX = 0.0
 *         self.massCenterY = 0.0
 *         self.size = 0.0             # <<<<<<<<<<<<<<
 *         self.nodes = nodes
 *         self.subregions = []
 */
  __pyx_v_self->size = 0.0;

  /* "fa2/fa2util.py":155
 *         self.massCenterY = 0.0
 *         self.size = 0.0
 *         self.nodes = nodes             # <<<<<<<<<<<<<<
 *         self.subregions = []
 *         self.updateMassAndGeometry()
 */
  if (!(likely(PyList_CheckExact(__pyx_v_nodes))||((__pyx_v_nodes) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "list", Py_TYPE(__pyx_v_nodes)->tp_name), 0))) __PYX_ERR(2, 155, __pyx_L1_error)
  __pyx_t_1 = __pyx_v_nodes;
  __Pyx_INCREF(__pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __Pyx_GOTREF(__pyx_v_self->nodes);
  __Pyx_DECREF(__pyx_v_self->nodes);
  __pyx_v_self->nodes = ((PyObject*)__pyx_t_1);
  __pyx_t_1 = 0;

  /* "fa2/fa2util.py":156
 *         self.size = 0.0
 *         self.nodes = nodes
 *         self.subregions = []             # <<<<<<<<<<<<<<
 *         self.updateMassAndGeometry()
 * 
 */
  __pyx_t_1 = PyList_New(0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 156, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __Pyx_GOTREF(__pyx_v_self->subregions);
  __Pyx_DECREF(__pyx_v_self->subregions);
  __pyx_v_self->subregions = ((PyObject*)__pyx_t_1);
  __pyx_t_1 = 0;

  /* "fa2/fa2util.py":157
 *         self.nodes = nodes
 *         self.subregions = []
 *         self.updateMassAndGeometry()             # <<<<<<<<<<<<<<
 * 
 *     def updateMassAndGeometry(self):
 */
  ((struct __pyx_vtabstruct_3fa2_7fa2util_Region *)__pyx_v_self->__pyx_vtab)->updateMassAndGeometry(__pyx_v_self);

  /* "fa2/fa2util.py":150
 * # For Barnes Hut Optimization
 * class Region:
 *     def __init__(self, nodes):             # <<<<<<<<<<<<<<
 *         self.mass = 0.0
 *         self.massCenterX = 0.0
 */

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Region.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.py":159
 *         self.updateMassAndGeometry()
 * 
 *     def updateMassAndGeometry(self):             # <<<<<<<<<<<<<<
 *         if len(self.nodes) > 1:
 *             self.mass = 0
 */

static void __pyx_f_3fa2_7fa2util_6Region_updateMassAndGeometry(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self) {
  double __pyx_v_massSumX;
  double __pyx_v_massSumY;
  struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n = 0;
  double __pyx_v_distance;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  Py_ssize_t __pyx_t_2;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  double __pyx_t_8;
  double __pyx_t_9;
  double __pyx_t_10;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("updateMassAndGeometry", 0);

  /* "fa2/fa2util.py":160
 * 
 *     def updateMassAndGeometry(self):
 *         if len(self.nodes) > 1:             # <<<<<<<<<<<<<<
 *             self.mass = 0
 *             massSumX = 0
 */
  __pyx_t_1 = __pyx_v_self->nodes;
  __Pyx_INCREF(__pyx_t_1);
  if (unlikely(__pyx_t_1 == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    __PYX_ERR(2, 160, __pyx_L1_error)
  }
  __pyx_t_2 = PyList_GET_SIZE(__pyx_t_1); if (unlikely(__pyx_t_2 == ((Py_ssize_t)-1))) __PYX_ERR(2, 160, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_3 = ((__pyx_t_2 > 1) != 0);
  if (__pyx_t_3) {

    /* "fa2/fa2util.py":161
 *     def updateMassAndGeometry(self):
 *         if len(self.nodes) > 1:
 *             self.mass = 0             # <<<<<<<<<<<<<<
 *             massSumX = 0
 *             massSumY = 0
 */
    __pyx_v_self->mass = 0.0;

    /* "fa2/fa2util.py":162
 *         if len(self.nodes) > 1:
 *             self.mass = 0
 *             massSumX = 0             # <<<<<<<<<<<<<<
 *             massSumY = 0
 *             for n in self.nodes:
 */
    __pyx_v_massSumX = 0.0;

    /* "fa2/fa2util.py":163
 *             self.mass = 0
 *             massSumX = 0
 *             massSumY = 0             # <<<<<<<<<<<<<<
 *             for n in self.nodes:
 *                 self.mass += n.mass
 */
    __pyx_v_massSumY = 0.0;

    /* "fa2/fa2util.py":164
 *             massSumX = 0
 *             massSumY = 0
 *             for n in self.nodes:             # <<<<<<<<<<<<<<
 *                 self.mass += n.mass
 *                 massSumX += n.x * n.mass
 */
    if (unlikely(__pyx_v_self->nodes == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
      __PYX_ERR(2, 164, __pyx_L1_error)
    }
    __pyx_t_1 = __pyx_v_self->nodes; __Pyx_INCREF(__pyx_t_1); __pyx_t_2 = 0;
    for (;;) {
      if (__pyx_t_2 >= PyList_GET_SIZE(__pyx_t_1)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_4 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_4); __pyx_t_2++; if (unlikely(0 < 0)) __PYX_ERR(2, 164, __pyx_L1_error)
      #else
      __pyx_t_4 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 164, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      #endif
      if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 164, __pyx_L1_error)
      __Pyx_XDECREF_SET(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_4));
      __pyx_t_4 = 0;

      /* "fa2/fa2util.py":165
 *             massSumY = 0
 *             for n in self.nodes:
 *                 self.mass += n.mass             # <<<<<<<<<<<<<<
 *                 massSumX += n.x * n.mass
 *                 massSumY += n.y * n.mass
 */
      __pyx_v_self->mass = (__pyx_v_self->mass + __pyx_v_n->mass);

      /* "fa2/fa2util.py":166
 *             for n in self.nodes:
 *                 self.mass += n.mass
 *                 massSumX += n.x * n.mass             # <<<<<<<<<<<<<<
 *                 massSumY += n.y * n.mass
 *             self.massCenterX = massSumX / self.mass
 */
      __pyx_v_massSumX = (__pyx_v_massSumX + (__pyx_v_n->x * __pyx_v_n->mass));

      /* "fa2/fa2util.py":167
 *                 self.mass += n.mass
 *                 massSumX += n.x * n.mass
 *                 massSumY += n.y * n.mass             # <<<<<<<<<<<<<<
 *             self.massCenterX = massSumX / self.mass
 *             self.massCenterY = massSumY / self.mass
 */
      __pyx_v_massSumY = (__pyx_v_massSumY + (__pyx_v_n->y * __pyx_v_n->mass));

      /* "fa2/fa2util.py":164
 *             massSumX = 0
 *             massSumY = 0
 *             for n in self.nodes:             # <<<<<<<<<<<<<<
 *                 self.mass += n.mass
 *                 massSumX += n.x * n.mass
 */
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "fa2/fa2util.py":168
 *                 massSumX += n.x * n.mass
 *                 massSumY += n.y * n.mass
 *             self.massCenterX = massSumX / self.mass             # <<<<<<<<<<<<<<
 *             self.massCenterY = massSumY / self.mass
 * 
 */
    if (unlikely(__pyx_v_self->mass == 0)) {
      PyErr_SetString(PyExc_ZeroDivisionError, "float division");
      __PYX_ERR(2, 168, __pyx_L1_error)
    }
    __pyx_v_self->massCenterX = (__pyx_v_massSumX / __pyx_v_self->mass);

    /* "fa2/fa2util.py":169
 *                 massSumY += n.y * n.mass
 *             self.massCenterX = massSumX / self.mass
 *             self.massCenterY = massSumY / self.mass             # <<<<<<<<<<<<<<
 * 
 *             self.size = 0.0
 */
    if (unlikely(__pyx_v_self->mass == 0)) {
      PyErr_SetString(PyExc_ZeroDivisionError, "float division");
      __PYX_ERR(2, 169, __pyx_L1_error)
    }
    __pyx_v_self->massCenterY = (__pyx_v_massSumY / __pyx_v_self->mass);

    /* "fa2/fa2util.py":171
 *             self.massCenterY = massSumY / self.mass
 * 
 *             self.size = 0.0             # <<<<<<<<<<<<<<
 *             for n in self.nodes:
 *                 distance = sqrt((n.x - self.massCenterX) ** 2 + (n.y - self.massCenterY) ** 2)
 */
    __pyx_v_self->size = 0.0;

    /* "fa2/fa2util.py":172
 * 
 *             self.size = 0.0
 *             for n in self.nodes:             # <<<<<<<<<<<<<<
 *                 distance = sqrt((n.x - self.massCenterX) ** 2 + (n.y - self.massCenterY) ** 2)
 *                 self.size = max(self.size, 2 * distance)
 */
    if (unlikely(__pyx_v_self->nodes == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
      __PYX_ERR(2, 172, __pyx_L1_error)
    }
    __pyx_t_1 = __pyx_v_self->nodes; __Pyx_INCREF(__pyx_t_1); __pyx_t_2 = 0;
    for (;;) {
      if (__pyx_t_2 >= PyList_GET_SIZE(__pyx_t_1)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_4 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_4); __pyx_t_2++; if (unlikely(0 < 0)) __PYX_ERR(2, 172, __pyx_L1_error)
      #else
      __pyx_t_4 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 172, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      #endif
      if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 172, __pyx_L1_error)
      __Pyx_XDECREF_SET(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_4));
      __pyx_t_4 = 0;

      /* "fa2/fa2util.py":173
 *             self.size = 0.0
 *             for n in self.nodes:
 *                 distance = sqrt((n.x - self.massCenterX) ** 2 + (n.y - self.massCenterY) ** 2)             # <<<<<<<<<<<<<<
 *                 self.size = max(self.size, 2 * distance)
 * 
 */
      __Pyx_GetModuleGlobalName(__pyx_t_5, __pyx_n_s_sqrt); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 173, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_6 = PyFloat_FromDouble((pow((__pyx_v_n->x - __pyx_v_self->massCenterX), 2.0) + pow((__pyx_v_n->y - __pyx_v_self->massCenterY), 2.0))); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 173, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_7 = NULL;
      if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
        __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_5);
        if (likely(__pyx_t_7)) {
          PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
          __Pyx_INCREF(__pyx_t_7);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_5, function);
        }
      }
      __pyx_t_4 = (__pyx_t_7) ? __Pyx_PyObject_Call2Args(__pyx_t_5, __pyx_t_7, __pyx_t_6) : __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_t_6);
      __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 173, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_8 = __pyx_PyFloat_AsDouble(__pyx_t_4); if (unlikely((__pyx_t_8 == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 173, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_v_distance = __pyx_t_8;

      /* "fa2/fa2util.py":174
 *             for n in self.nodes:
 *                 distance = sqrt((n.x - self.massCenterX) ** 2 + (n.y - self.massCenterY) ** 2)
 *                 self.size = max(self.size, 2 * distance)             # <<<<<<<<<<<<<<
 * 
 *     def buildSubRegions(self):
 */
      __pyx_t_8 = (2.0 * __pyx_v_distance);
      __pyx_t_9 = __pyx_v_self->size;
      if (((__pyx_t_8 > __pyx_t_9) != 0)) {
        __pyx_t_10 = __pyx_t_8;
      } else {
        __pyx_t_10 = __pyx_t_9;
      }
      __pyx_v_self->size = __pyx_t_10;

      /* "fa2/fa2util.py":172
 * 
 *             self.size = 0.0
 *             for n in self.nodes:             # <<<<<<<<<<<<<<
 *                 distance = sqrt((n.x - self.massCenterX) ** 2 + (n.y - self.massCenterY) ** 2)
 *                 self.size = max(self.size, 2 * distance)
 */
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "fa2/fa2util.py":160
 * 
 *     def updateMassAndGeometry(self):
 *         if len(self.nodes) > 1:             # <<<<<<<<<<<<<<
 *             self.mass = 0
 *             massSumX = 0
 */
  }

  /* "fa2/fa2util.py":159
 *         self.updateMassAndGeometry()
 * 
 *     def updateMassAndGeometry(self):             # <<<<<<<<<<<<<<
 *         if len(self.nodes) > 1:
 *             self.mass = 0
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_WriteUnraisable("fa2.fa2util.Region.updateMassAndGeometry", __pyx_clineno, __pyx_lineno, __pyx_filename, 1, 0);
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_n);
  __Pyx_RefNannyFinishContext();
}

/* "fa2/fa2util.py":176
 *                 self.size = max(self.size, 2 * distance)
 * 
 *     def buildSubRegions(self):             # <<<<<<<<<<<<<<
 *         if len(self.nodes) > 1:
 *             topleftNodes = []
 */

static PyObject *__pyx_pw_3fa2_7fa2util_6Region_3buildSubRegions(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); /*proto*/
static void __pyx_f_3fa2_7fa2util_6Region_buildSubRegions(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, int __pyx_skip_dispatch) {
  struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n = 0;
  PyObject *__pyx_v_topleftNodes = 0;
  PyObject *__pyx_v_bottomleftNodes = 0;
  PyObject *__pyx_v_toprightNodes = 0;
  PyObject *__pyx_v_bottomrightNodes = 0;
  struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_subregion = 0;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  Py_ssize_t __pyx_t_5;
  int __pyx_t_6;
  int __pyx_t_7;
  Py_ssize_t __pyx_t_8;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("buildSubRegions", 0);
  /* Check if called by wrapper */
  if (unlikely(__pyx_skip_dispatch)) ;
  /* Check if overridden in Python */
  else if (unlikely((Py_TYPE(((PyObject *)__pyx_v_self))->tp_dictoffset != 0) || (Py_TYPE(((PyObject *)__pyx_v_self))->tp_flags & (Py_TPFLAGS_IS_ABSTRACT | Py_TPFLAGS_HEAPTYPE)))) {
    #if CYTHON_USE_DICT_VERSIONS && CYTHON_USE_PYTYPE_LOOKUP && CYTHON_USE_TYPE_SLOTS
    static PY_UINT64_T __pyx_tp_dict_version = __PYX_DICT_VERSION_INIT, __pyx_obj_dict_version = __PYX_DICT_VERSION_INIT;
    if (unlikely(!__Pyx_object_dict_version_matches(((PyObject *)__pyx_v_self), __pyx_tp_dict_version, __pyx_obj_dict_version))) {
      PY_UINT64_T __pyx_type_dict_guard = __Pyx_get_tp_dict_version(((PyObject *)__pyx_v_self));
      #endif
      __pyx_t_1 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v_self), __pyx_n_s_buildSubRegions); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 176, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      if (!PyCFunction_Check(__pyx_t_1) || (PyCFunction_GET_FUNCTION(__pyx_t_1) != (PyCFunction)(void*)__pyx_pw_3fa2_7fa2util_6Region_3buildSubRegions)) {
        __Pyx_INCREF(__pyx_t_1);
        __pyx_t_3 = __pyx_t_1; __pyx_t_4 = NULL;
        if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
          __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_3);
          if (likely(__pyx_t_4)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
            __Pyx_INCREF(__pyx_t_4);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_3, function);
          }
        }
        __pyx_t_2 = (__pyx_t_4) ? __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_4) : __Pyx_PyObject_CallNoArg(__pyx_t_3);
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 176, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        goto __pyx_L0;
      }
      #if CYTHON_USE_DICT_VERSIONS && CYTHON_USE_PYTYPE_LOOKUP && CYTHON_USE_TYPE_SLOTS
      __pyx_tp_dict_version = __Pyx_get_tp_dict_version(((PyObject *)__pyx_v_self));
      __pyx_obj_dict_version = __Pyx_get_object_dict_version(((PyObject *)__pyx_v_self));
      if (unlikely(__pyx_type_dict_guard != __pyx_tp_dict_version)) {
        __pyx_tp_dict_version = __pyx_obj_dict_version = __PYX_DICT_VERSION_INIT;
      }
      #endif
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      #if CYTHON_USE_DICT_VERSIONS && CYTHON_USE_PYTYPE_LOOKUP && CYTHON_USE_TYPE_SLOTS
    }
    #endif
  }

  /* "fa2/fa2util.py":177
 * 
 *     def buildSubRegions(self):
 *         if len(self.nodes) > 1:             # <<<<<<<<<<<<<<
 *             topleftNodes = []
 *             bottomleftNodes = []
 */
  __pyx_t_1 = __pyx_v_self->nodes;
  __Pyx_INCREF(__pyx_t_1);
  if (unlikely(__pyx_t_1 == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    __PYX_ERR(2, 177, __pyx_L1_error)
  }
  __pyx_t_5 = PyList_GET_SIZE(__pyx_t_1); if (unlikely(__pyx_t_5 == ((Py_ssize_t)-1))) __PYX_ERR(2, 177, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_6 = ((__pyx_t_5 > 1) != 0);
  if (__pyx_t_6) {

    /* "fa2/fa2util.py":178
 *     def buildSubRegions(self):
 *         if len(self.nodes) > 1:
 *             topleftNodes = []             # <<<<<<<<<<<<<<
 *             bottomleftNodes = []
 *             toprightNodes = []
 */
    __pyx_t_1 = PyList_New(0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 178, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_v_topleftNodes = ((PyObject*)__pyx_t_1);
    __pyx_t_1 = 0;

    /* "fa2/fa2util.py":179
 *         if len(self.nodes) > 1:
 *             topleftNodes = []
 *             bottomleftNodes = []             # <<<<<<<<<<<<<<
 *             toprightNodes = []
 *             bottomrightNodes = []
 */
    __pyx_t_1 = PyList_New(0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 179, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_v_bottomleftNodes = ((PyObject*)__pyx_t_1);
    __pyx_t_1 = 0;

    /* "fa2/fa2util.py":180
 *             topleftNodes = []
 *             bottomleftNodes = []
 *             toprightNodes = []             # <<<<<<<<<<<<<<
 *             bottomrightNodes = []
 *             # Optimization: The distribution of self.nodes into
 */
    __pyx_t_1 = PyList_New(0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 180, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_v_toprightNodes = ((PyObject*)__pyx_t_1);
    __pyx_t_1 = 0;

    /* "fa2/fa2util.py":181
 *             bottomleftNodes = []
 *             toprightNodes = []
 *             bottomrightNodes = []             # <<<<<<<<<<<<<<
 *             # Optimization: The distribution of self.nodes into
 *             # subregions now requires only one for loop. Removed
 */
    __pyx_t_1 = PyList_New(0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 181, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_v_bottomrightNodes = ((PyObject*)__pyx_t_1);
    __pyx_t_1 = 0;

    /* "fa2/fa2util.py":185
 *             # subregions now requires only one for loop. Removed
 *             # topNodes and bottomNodes arrays: memory space saving.
 *             for n in self.nodes:             # <<<<<<<<<<<<<<
 *                 if n.x < self.massCenterX:
 *                     if n.y < self.massCenterY:
 */
    if (unlikely(__pyx_v_self->nodes == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
      __PYX_ERR(2, 185, __pyx_L1_error)
    }
    __pyx_t_1 = __pyx_v_self->nodes; __Pyx_INCREF(__pyx_t_1); __pyx_t_5 = 0;
    for (;;) {
      if (__pyx_t_5 >= PyList_GET_SIZE(__pyx_t_1)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_2 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_5); __Pyx_INCREF(__pyx_t_2); __pyx_t_5++; if (unlikely(0 < 0)) __PYX_ERR(2, 185, __pyx_L1_error)
      #else
      __pyx_t_2 = PySequence_ITEM(__pyx_t_1, __pyx_t_5); __pyx_t_5++; if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 185, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      #endif
      if (!(likely(((__pyx_t_2) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_2, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 185, __pyx_L1_error)
      __Pyx_XDECREF_SET(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_2));
      __pyx_t_2 = 0;

      /* "fa2/fa2util.py":186
 *             # topNodes and bottomNodes arrays: memory space saving.
 *             for n in self.nodes:
 *                 if n.x < self.massCenterX:             # <<<<<<<<<<<<<<
 *                     if n.y < self.massCenterY:
 *                         bottomleftNodes.append(n)
 */
      __pyx_t_6 = ((__pyx_v_n->x < __pyx_v_self->massCenterX) != 0);
      if (__pyx_t_6) {

        /* "fa2/fa2util.py":187
 *             for n in self.nodes:
 *                 if n.x < self.massCenterX:
 *                     if n.y < self.massCenterY:             # <<<<<<<<<<<<<<
 *                         bottomleftNodes.append(n)
 *                     else:
 */
        __pyx_t_6 = ((__pyx_v_n->y < __pyx_v_self->massCenterY) != 0);
        if (__pyx_t_6) {

          /* "fa2/fa2util.py":188
 *                 if n.x < self.massCenterX:
 *                     if n.y < self.massCenterY:
 *                         bottomleftNodes.append(n)             # <<<<<<<<<<<<<<
 *                     else:
 *                         topleftNodes.append(n)
 */
          __pyx_t_7 = __Pyx_PyList_Append(__pyx_v_bottomleftNodes, ((PyObject *)__pyx_v_n)); if (unlikely(__pyx_t_7 == ((int)-1))) __PYX_ERR(2, 188, __pyx_L1_error)

          /* "fa2/fa2util.py":187
 *             for n in self.nodes:
 *                 if n.x < self.massCenterX:
 *                     if n.y < self.massCenterY:             # <<<<<<<<<<<<<<
 *                         bottomleftNodes.append(n)
 *                     else:
 */
          goto __pyx_L7;
        }

        /* "fa2/fa2util.py":190
 *                         bottomleftNodes.append(n)
 *                     else:
 *                         topleftNodes.append(n)             # <<<<<<<<<<<<<<
 *                 else:
 *                     if n.y < self.massCenterY:
 */
        /*else*/ {
          __pyx_t_7 = __Pyx_PyList_Append(__pyx_v_topleftNodes, ((PyObject *)__pyx_v_n)); if (unlikely(__pyx_t_7 == ((int)-1))) __PYX_ERR(2, 190, __pyx_L1_error)
        }
        __pyx_L7:;

        /* "fa2/fa2util.py":186
 *             # topNodes and bottomNodes arrays: memory space saving.
 *             for n in self.nodes:
 *                 if n.x < self.massCenterX:             # <<<<<<<<<<<<<<
 *                     if n.y < self.massCenterY:
 *                         bottomleftNodes.append(n)
 */
        goto __pyx_L6;
      }

      /* "fa2/fa2util.py":192
 *                         topleftNodes.append(n)
 *                 else:
 *                     if n.y < self.massCenterY:             # <<<<<<<<<<<<<<
 *                         bottomrightNodes.append(n)
 *                     else:
 */
      /*else*/ {
        __pyx_t_6 = ((__pyx_v_n->y < __pyx_v_self->massCenterY) != 0);
        if (__pyx_t_6) {

          /* "fa2/fa2util.py":193
 *                 else:
 *                     if n.y < self.massCenterY:
 *                         bottomrightNodes.append(n)             # <<<<<<<<<<<<<<
 *                     else:
 *                         toprightNodes.append(n)
 */
          __pyx_t_7 = __Pyx_PyList_Append(__pyx_v_bottomrightNodes, ((PyObject *)__pyx_v_n)); if (unlikely(__pyx_t_7 == ((int)-1))) __PYX_ERR(2, 193, __pyx_L1_error)

          /* "fa2/fa2util.py":192
 *                         topleftNodes.append(n)
 *                 else:
 *                     if n.y < self.massCenterY:             # <<<<<<<<<<<<<<
 *                         bottomrightNodes.append(n)
 *                     else:
 */
          goto __pyx_L8;
        }

        /* "fa2/fa2util.py":195
 *                         bottomrightNodes.append(n)
 *                     else:
 *                         toprightNodes.append(n)             # <<<<<<<<<<<<<<
 * 
 *             if len(topleftNodes) > 0:
 */
        /*else*/ {
          __pyx_t_7 = __Pyx_PyList_Append(__pyx_v_toprightNodes, ((PyObject *)__pyx_v_n)); if (unlikely(__pyx_t_7 == ((int)-1))) __PYX_ERR(2, 195, __pyx_L1_error)
        }
        __pyx_L8:;
      }
      __pyx_L6:;

      /* "fa2/fa2util.py":185
 *             # subregions now requires only one for loop. Removed
 *             # topNodes and bottomNodes arrays: memory space saving.
 *             for n in self.nodes:             # <<<<<<<<<<<<<<
 *                 if n.x < self.massCenterX:
 *                     if n.y < self.massCenterY:
 */
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "fa2/fa2util.py":197
 *                         toprightNodes.append(n)
 * 
 *             if len(topleftNodes) > 0:             # <<<<<<<<<<<<<<
 *                 if len(topleftNodes) < len(self.nodes):
 *                     subregion = Region(topleftNodes)
 */
    __pyx_t_5 = PyList_GET_SIZE(__pyx_v_topleftNodes); if (unlikely(__pyx_t_5 == ((Py_ssize_t)-1))) __PYX_ERR(2, 197, __pyx_L1_error)
    __pyx_t_6 = ((__pyx_t_5 > 0) != 0);
    if (__pyx_t_6) {

      /* "fa2/fa2util.py":198
 * 
 *             if len(topleftNodes) > 0:
 *                 if len(topleftNodes) < len(self.nodes):             # <<<<<<<<<<<<<<
 *                     subregion = Region(topleftNodes)
 *                     self.subregions.append(subregion)
 */
      __pyx_t_5 = PyList_GET_SIZE(__pyx_v_topleftNodes); if (unlikely(__pyx_t_5 == ((Py_ssize_t)-1))) __PYX_ERR(2, 198, __pyx_L1_error)
      __pyx_t_1 = __pyx_v_self->nodes;
      __Pyx_INCREF(__pyx_t_1);
      if (unlikely(__pyx_t_1 == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
        __PYX_ERR(2, 198, __pyx_L1_error)
      }
      __pyx_t_8 = PyList_GET_SIZE(__pyx_t_1); if (unlikely(__pyx_t_8 == ((Py_ssize_t)-1))) __PYX_ERR(2, 198, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_6 = ((__pyx_t_5 < __pyx_t_8) != 0);
      if (__pyx_t_6) {

        /* "fa2/fa2util.py":199
 *             if len(topleftNodes) > 0:
 *                 if len(topleftNodes) < len(self.nodes):
 *                     subregion = Region(topleftNodes)             # <<<<<<<<<<<<<<
 *                     self.subregions.append(subregion)
 *                 else:
 */
        __pyx_t_1 = __Pyx_PyObject_CallOneArg(((PyObject *)__pyx_ptype_3fa2_7fa2util_Region), __pyx_v_topleftNodes); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 199, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_v_subregion = ((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_t_1);
        __pyx_t_1 = 0;

        /* "fa2/fa2util.py":200
 *                 if len(topleftNodes) < len(self.nodes):
 *                     subregion = Region(topleftNodes)
 *                     self.subregions.append(subregion)             # <<<<<<<<<<<<<<
 *                 else:
 *                     for n in topleftNodes:
 */
        if (unlikely(__pyx_v_self->subregions == Py_None)) {
          PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%.30s'", "append");
          __PYX_ERR(2, 200, __pyx_L1_error)
        }
        __pyx_t_7 = __Pyx_PyList_Append(__pyx_v_self->subregions, ((PyObject *)__pyx_v_subregion)); if (unlikely(__pyx_t_7 == ((int)-1))) __PYX_ERR(2, 200, __pyx_L1_error)

        /* "fa2/fa2util.py":198
 * 
 *             if len(topleftNodes) > 0:
 *                 if len(topleftNodes) < len(self.nodes):             # <<<<<<<<<<<<<<
 *                     subregion = Region(topleftNodes)
 *                     self.subregions.append(subregion)
 */
        goto __pyx_L10;
      }

      /* "fa2/fa2util.py":202
 *                     self.subregions.append(subregion)
 *                 else:
 *                     for n in topleftNodes:             # <<<<<<<<<<<<<<
 *                         subregion = Region([n])
 *                         self.subregions.append(subregion)
 */
      /*else*/ {
        __pyx_t_1 = __pyx_v_topleftNodes; __Pyx_INCREF(__pyx_t_1); __pyx_t_8 = 0;
        for (;;) {
          if (__pyx_t_8 >= PyList_GET_SIZE(__pyx_t_1)) break;
          #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
          __pyx_t_2 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_8); __Pyx_INCREF(__pyx_t_2); __pyx_t_8++; if (unlikely(0 < 0)) __PYX_ERR(2, 202, __pyx_L1_error)
          #else
          __pyx_t_2 = PySequence_ITEM(__pyx_t_1, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 202, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
          #endif
          if (!(likely(((__pyx_t_2) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_2, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 202, __pyx_L1_error)
          __Pyx_XDECREF_SET(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_2));
          __pyx_t_2 = 0;

          /* "fa2/fa2util.py":203
 *                 else:
 *                     for n in topleftNodes:
 *                         subregion = Region([n])             # <<<<<<<<<<<<<<
 *                         self.subregions.append(subregion)
 * 
 */
          __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 203, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_INCREF(((PyObject *)__pyx_v_n));
          __Pyx_GIVEREF(((PyObject *)__pyx_v_n));
          PyList_SET_ITEM(__pyx_t_2, 0, ((PyObject *)__pyx_v_n));
          __pyx_t_3 = __Pyx_PyObject_CallOneArg(((PyObject *)__pyx_ptype_3fa2_7fa2util_Region), __pyx_t_2); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 203, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
          __Pyx_XDECREF_SET(__pyx_v_subregion, ((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_t_3));
          __pyx_t_3 = 0;

          /* "fa2/fa2util.py":204
 *                     for n in topleftNodes:
 *                         subregion = Region([n])
 *                         self.subregions.append(subregion)             # <<<<<<<<<<<<<<
 * 
 *             if len(bottomleftNodes) > 0:
 */
          if (unlikely(__pyx_v_self->subregions == Py_None)) {
            PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%.30s'", "append");
            __PYX_ERR(2, 204, __pyx_L1_error)
          }
          __pyx_t_7 = __Pyx_PyList_Append(__pyx_v_self->subregions, ((PyObject *)__pyx_v_subregion)); if (unlikely(__pyx_t_7 == ((int)-1))) __PYX_ERR(2, 204, __pyx_L1_error)

          /* "fa2/fa2util.py":202
 *                     self.subregions.append(subregion)
 *                 else:
 *                     for n in topleftNodes:             # <<<<<<<<<<<<<<
 *                         subregion = Region([n])
 *                         self.subregions.append(subregion)
 */
        }
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      }
      __pyx_L10:;

      /* "fa2/fa2util.py":197
 *                         toprightNodes.append(n)
 * 
 *             if len(topleftNodes) > 0:             # <<<<<<<<<<<<<<
 *                 if len(topleftNodes) < len(self.nodes):
 *                     subregion = Region(topleftNodes)
 */
    }

    /* "fa2/fa2util.py":206
 *                         self.subregions.append(subregion)
 * 
 *             if len(bottomleftNodes) > 0:             # <<<<<<<<<<<<<<
 *                 if len(bottomleftNodes) < len(self.nodes):
 *                     subregion = Region(bottomleftNodes)
 */
    __pyx_t_8 = PyList_GET_SIZE(__pyx_v_bottomleftNodes); if (unlikely(__pyx_t_8 == ((Py_ssize_t)-1))) __PYX_ERR(2, 206, __pyx_L1_error)
    __pyx_t_6 = ((__pyx_t_8 > 0) != 0);
    if (__pyx_t_6) {

      /* "fa2/fa2util.py":207
 * 
 *             if len(bottomleftNodes) > 0:
 *                 if len(bottomleftNodes) < len(self.nodes):             # <<<<<<<<<<<<<<
 *                     subregion = Region(bottomleftNodes)
 *                     self.subregions.append(subregion)
 */
      __pyx_t_8 = PyList_GET_SIZE(__pyx_v_bottomleftNodes); if (unlikely(__pyx_t_8 == ((Py_ssize_t)-1))) __PYX_ERR(2, 207, __pyx_L1_error)
      __pyx_t_1 = __pyx_v_self->nodes;
      __Pyx_INCREF(__pyx_t_1);
      if (unlikely(__pyx_t_1 == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
        __PYX_ERR(2, 207, __pyx_L1_error)
      }
      __pyx_t_5 = PyList_GET_SIZE(__pyx_t_1); if (unlikely(__pyx_t_5 == ((Py_ssize_t)-1))) __PYX_ERR(2, 207, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_6 = ((__pyx_t_8 < __pyx_t_5) != 0);
      if (__pyx_t_6) {

        /* "fa2/fa2util.py":208
 *             if len(bottomleftNodes) > 0:
 *                 if len(bottomleftNodes) < len(self.nodes):
 *                     subregion = Region(bottomleftNodes)             # <<<<<<<<<<<<<<
 *                     self.subregions.append(subregion)
 *                 else:
 */
        __pyx_t_1 = __Pyx_PyObject_CallOneArg(((PyObject *)__pyx_ptype_3fa2_7fa2util_Region), __pyx_v_bottomleftNodes); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 208, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_XDECREF_SET(__pyx_v_subregion, ((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_t_1));
        __pyx_t_1 = 0;

        /* "fa2/fa2util.py":209
 *                 if len(bottomleftNodes) < len(self.nodes):
 *                     subregion = Region(bottomleftNodes)
 *                     self.subregions.append(subregion)             # <<<<<<<<<<<<<<
 *                 else:
 *                     for n in bottomleftNodes:
 */
        if (unlikely(__pyx_v_self->subregions == Py_None)) {
          PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%.30s'", "append");
          __PYX_ERR(2, 209, __pyx_L1_error)
        }
        __pyx_t_7 = __Pyx_PyList_Append(__pyx_v_self->subregions, ((PyObject *)__pyx_v_subregion)); if (unlikely(__pyx_t_7 == ((int)-1))) __PYX_ERR(2, 209, __pyx_L1_error)

        /* "fa2/fa2util.py":207
 * 
 *             if len(bottomleftNodes) > 0:
 *                 if len(bottomleftNodes) < len(self.nodes):             # <<<<<<<<<<<<<<
 *                     subregion = Region(bottomleftNodes)
 *                     self.subregions.append(subregion)
 */
        goto __pyx_L14;
      }

      /* "fa2/fa2util.py":211
 *                     self.subregions.append(subregion)
 *                 else:
 *                     for n in bottomleftNodes:             # <<<<<<<<<<<<<<
 *                         subregion = Region([n])
 *                         self.subregions.append(subregion)
 */
      /*else*/ {
        __pyx_t_1 = __pyx_v_bottomleftNodes; __Pyx_INCREF(__pyx_t_1); __pyx_t_5 = 0;
        for (;;) {
          if (__pyx_t_5 >= PyList_GET_SIZE(__pyx_t_1)) break;
          #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
          __pyx_t_3 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_5); __Pyx_INCREF(__pyx_t_3); __pyx_t_5++; if (unlikely(0 < 0)) __PYX_ERR(2, 211, __pyx_L1_error)
          #else
          __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_5); __pyx_t_5++; if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 211, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          #endif
          if (!(likely(((__pyx_t_3) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_3, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 211, __pyx_L1_error)
          __Pyx_XDECREF_SET(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_3));
          __pyx_t_3 = 0;

          /* "fa2/fa2util.py":212
 *                 else:
 *                     for n in bottomleftNodes:
 *                         subregion = Region([n])             # <<<<<<<<<<<<<<
 *                         self.subregions.append(subregion)
 * 
 */
          __pyx_t_3 = PyList_New(1); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 212, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_INCREF(((PyObject *)__pyx_v_n));
          __Pyx_GIVEREF(((PyObject *)__pyx_v_n));
          PyList_SET_ITEM(__pyx_t_3, 0, ((PyObject *)__pyx_v_n));
          __pyx_t_2 = __Pyx_PyObject_CallOneArg(((PyObject *)__pyx_ptype_3fa2_7fa2util_Region), __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 212, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          __Pyx_XDECREF_SET(__pyx_v_subregion, ((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_t_2));
          __pyx_t_2 = 0;

          /* "fa2/fa2util.py":213
 *                     for n in bottomleftNodes:
 *                         subregion = Region([n])
 *                         self.subregions.append(subregion)             # <<<<<<<<<<<<<<
 * 
 *             if len(toprightNodes) > 0:
 */
          if (unlikely(__pyx_v_self->subregions == Py_None)) {
            PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%.30s'", "append");
            __PYX_ERR(2, 213, __pyx_L1_error)
          }
          __pyx_t_7 = __Pyx_PyList_Append(__pyx_v_self->subregions, ((PyObject *)__pyx_v_subregion)); if (unlikely(__pyx_t_7 == ((int)-1))) __PYX_ERR(2, 213, __pyx_L1_error)

          /* "fa2/fa2util.py":211
 *                     self.subregions.append(subregion)
 *                 else:
 *                     for n in bottomleftNodes:             # <<<<<<<<<<<<<<
 *                         subregion = Region([n])
 *                         self.subregions.append(subregion)
 */
        }
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      }
      __pyx_L14:;

      /* "fa2/fa2util.py":206
 *                         self.subregions.append(subregion)
 * 
 *             if len(bottomleftNodes) > 0:             # <<<<<<<<<<<<<<
 *                 if len(bottomleftNodes) < len(self.nodes):
 *                     subregion = Region(bottomleftNodes)
 */
    }

    /* "fa2/fa2util.py":215
 *                         self.subregions.append(subregion)
 * 
 *             if len(toprightNodes) > 0:             # <<<<<<<<<<<<<<
 *                 if len(toprightNodes) < len(self.nodes):
 *                     subregion = Region(toprightNodes)
 */
    __pyx_t_5 = PyList_GET_SIZE(__pyx_v_toprightNodes); if (unlikely(__pyx_t_5 == ((Py_ssize_t)-1))) __PYX_ERR(2, 215, __pyx_L1_error)
    __pyx_t_6 = ((__pyx_t_5 > 0) != 0);
    if (__pyx_t_6) {

      /* "fa2/fa2util.py":216
 * 
 *             if len(toprightNodes) > 0:
 *                 if len(toprightNodes) < len(self.nodes):             # <<<<<<<<<<<<<<
 *                     subregion = Region(toprightNodes)
 *                     self.subregions.append(subregion)
 */
      __pyx_t_5 = PyList_GET_SIZE(__pyx_v_toprightNodes); if (unlikely(__pyx_t_5 == ((Py_ssize_t)-1))) __PYX_ERR(2, 216, __pyx_L1_error)
      __pyx_t_1 = __pyx_v_self->nodes;
      __Pyx_INCREF(__pyx_t_1);
      if (unlikely(__pyx_t_1 == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
        __PYX_ERR(2, 216, __pyx_L1_error)
      }
      __pyx_t_8 = PyList_GET_SIZE(__pyx_t_1); if (unlikely(__pyx_t_8 == ((Py_ssize_t)-1))) __PYX_ERR(2, 216, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_6 = ((__pyx_t_5 < __pyx_t_8) != 0);
      if (__pyx_t_6) {

        /* "fa2/fa2util.py":217
 *             if len(toprightNodes) > 0:
 *                 if len(toprightNodes) < len(self.nodes):
 *                     subregion = Region(toprightNodes)             # <<<<<<<<<<<<<<
 *                     self.subregions.append(subregion)
 *                 else:
 */
        __pyx_t_1 = __Pyx_PyObject_CallOneArg(((PyObject *)__pyx_ptype_3fa2_7fa2util_Region), __pyx_v_toprightNodes); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 217, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_XDECREF_SET(__pyx_v_subregion, ((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_t_1));
        __pyx_t_1 = 0;

        /* "fa2/fa2util.py":218
 *                 if len(toprightNodes) < len(self.nodes):
 *                     subregion = Region(toprightNodes)
 *                     self.subregions.append(subregion)             # <<<<<<<<<<<<<<
 *                 else:
 *                     for n in toprightNodes:
 */
        if (unlikely(__pyx_v_self->subregions == Py_None)) {
          PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%.30s'", "append");
          __PYX_ERR(2, 218, __pyx_L1_error)
        }
        __pyx_t_7 = __Pyx_PyList_Append(__pyx_v_self->subregions, ((PyObject *)__pyx_v_subregion)); if (unlikely(__pyx_t_7 == ((int)-1))) __PYX_ERR(2, 218, __pyx_L1_error)

        /* "fa2/fa2util.py":216
 * 
 *             if len(toprightNodes) > 0:
 *                 if len(toprightNodes) < len(self.nodes):             # <<<<<<<<<<<<<<
 *                     subregion = Region(toprightNodes)
 *                     self.subregions.append(subregion)
 */
        goto __pyx_L18;
      }

      /* "fa2/fa2util.py":220
 *                     self.subregions.append(subregion)
 *                 else:
 *                     for n in toprightNodes:             # <<<<<<<<<<<<<<
 *                         subregion = Region([n])
 *                         self.subregions.append(subregion)
 */
      /*else*/ {
        __pyx_t_1 = __pyx_v_toprightNodes; __Pyx_INCREF(__pyx_t_1); __pyx_t_8 = 0;
        for (;;) {
          if (__pyx_t_8 >= PyList_GET_SIZE(__pyx_t_1)) break;
          #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
          __pyx_t_2 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_8); __Pyx_INCREF(__pyx_t_2); __pyx_t_8++; if (unlikely(0 < 0)) __PYX_ERR(2, 220, __pyx_L1_error)
          #else
          __pyx_t_2 = PySequence_ITEM(__pyx_t_1, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 220, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
          #endif
          if (!(likely(((__pyx_t_2) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_2, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 220, __pyx_L1_error)
          __Pyx_XDECREF_SET(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_2));
          __pyx_t_2 = 0;

          /* "fa2/fa2util.py":221
 *                 else:
 *                     for n in toprightNodes:
 *                         subregion = Region([n])             # <<<<<<<<<<<<<<
 *                         self.subregions.append(subregion)
 * 
 */
          __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 221, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_INCREF(((PyObject *)__pyx_v_n));
          __Pyx_GIVEREF(((PyObject *)__pyx_v_n));
          PyList_SET_ITEM(__pyx_t_2, 0, ((PyObject *)__pyx_v_n));
          __pyx_t_3 = __Pyx_PyObject_CallOneArg(((PyObject *)__pyx_ptype_3fa2_7fa2util_Region), __pyx_t_2); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 221, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
          __Pyx_XDECREF_SET(__pyx_v_subregion, ((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_t_3));
          __pyx_t_3 = 0;

          /* "fa2/fa2util.py":222
 *                     for n in toprightNodes:
 *                         subregion = Region([n])
 *                         self.subregions.append(subregion)             # <<<<<<<<<<<<<<
 * 
 *             if len(bottomrightNodes) > 0:
 */
          if (unlikely(__pyx_v_self->subregions == Py_None)) {
            PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%.30s'", "append");
            __PYX_ERR(2, 222, __pyx_L1_error)
          }
          __pyx_t_7 = __Pyx_PyList_Append(__pyx_v_self->subregions, ((PyObject *)__pyx_v_subregion)); if (unlikely(__pyx_t_7 == ((int)-1))) __PYX_ERR(2, 222, __pyx_L1_error)

          /* "fa2/fa2util.py":220
 *                     self.subregions.append(subregion)
 *                 else:
 *                     for n in toprightNodes:             # <<<<<<<<<<<<<<
 *                         subregion = Region([n])
 *                         self.subregions.append(subregion)
 */
        }
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      }
      __pyx_L18:;

      /* "fa2/fa2util.py":215
 *                         self.subregions.append(subregion)
 * 
 *             if len(toprightNodes) > 0:             # <<<<<<<<<<<<<<
 *                 if len(toprightNodes) < len(self.nodes):
 *                     subregion = Region(toprightNodes)
 */
    }

    /* "fa2/fa2util.py":224
 *                         self.subregions.append(subregion)
 * 
 *             if len(bottomrightNodes) > 0:             # <<<<<<<<<<<<<<
 *                 if len(bottomrightNodes) < len(self.nodes):
 *                     subregion = Region(bottomrightNodes)
 */
    __pyx_t_8 = PyList_GET_SIZE(__pyx_v_bottomrightNodes); if (unlikely(__pyx_t_8 == ((Py_ssize_t)-1))) __PYX_ERR(2, 224, __pyx_L1_error)
    __pyx_t_6 = ((__pyx_t_8 > 0) != 0);
    if (__pyx_t_6) {

      /* "fa2/fa2util.py":225
 * 
 *             if len(bottomrightNodes) > 0:
 *                 if len(bottomrightNodes) < len(self.nodes):             # <<<<<<<<<<<<<<
 *                     subregion = Region(bottomrightNodes)
 *                     self.subregions.append(subregion)
 */
      __pyx_t_8 = PyList_GET_SIZE(__pyx_v_bottomrightNodes); if (unlikely(__pyx_t_8 == ((Py_ssize_t)-1))) __PYX_ERR(2, 225, __pyx_L1_error)
      __pyx_t_1 = __pyx_v_self->nodes;
      __Pyx_INCREF(__pyx_t_1);
      if (unlikely(__pyx_t_1 == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
        __PYX_ERR(2, 225, __pyx_L1_error)
      }
      __pyx_t_5 = PyList_GET_SIZE(__pyx_t_1); if (unlikely(__pyx_t_5 == ((Py_ssize_t)-1))) __PYX_ERR(2, 225, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_6 = ((__pyx_t_8 < __pyx_t_5) != 0);
      if (__pyx_t_6) {

        /* "fa2/fa2util.py":226
 *             if len(bottomrightNodes) > 0:
 *                 if len(bottomrightNodes) < len(self.nodes):
 *                     subregion = Region(bottomrightNodes)             # <<<<<<<<<<<<<<
 *                     self.subregions.append(subregion)
 *                 else:
 */
        __pyx_t_1 = __Pyx_PyObject_CallOneArg(((PyObject *)__pyx_ptype_3fa2_7fa2util_Region), __pyx_v_bottomrightNodes); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 226, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_XDECREF_SET(__pyx_v_subregion, ((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_t_1));
        __pyx_t_1 = 0;

        /* "fa2/fa2util.py":227
 *                 if len(bottomrightNodes) < len(self.nodes):
 *                     subregion = Region(bottomrightNodes)
 *                     self.subregions.append(subregion)             # <<<<<<<<<<<<<<
 *                 else:
 *                     for n in bottomrightNodes:
 */
        if (unlikely(__pyx_v_self->subregions == Py_None)) {
          PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%.30s'", "append");
          __PYX_ERR(2, 227, __pyx_L1_error)
        }
        __pyx_t_7 = __Pyx_PyList_Append(__pyx_v_self->subregions, ((PyObject *)__pyx_v_subregion)); if (unlikely(__pyx_t_7 == ((int)-1))) __PYX_ERR(2, 227, __pyx_L1_error)

        /* "fa2/fa2util.py":225
 * 
 *             if len(bottomrightNodes) > 0:
 *                 if len(bottomrightNodes) < len(self.nodes):             # <<<<<<<<<<<<<<
 *                     subregion = Region(bottomrightNodes)
 *                     self.subregions.append(subregion)
 */
        goto __pyx_L22;
      }

      /* "fa2/fa2util.py":229
 *                     self.subregions.append(subregion)
 *                 else:
 *                     for n in bottomrightNodes:             # <<<<<<<<<<<<<<
 *                         subregion = Region([n])
 *                         self.subregions.append(subregion)
 */
      /*else*/ {
        __pyx_t_1 = __pyx_v_bottomrightNodes; __Pyx_INCREF(__pyx_t_1); __pyx_t_5 = 0;
        for (;;) {
          if (__pyx_t_5 >= PyList_GET_SIZE(__pyx_t_1)) break;
          #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
          __pyx_t_3 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_5); __Pyx_INCREF(__pyx_t_3); __pyx_t_5++; if (unlikely(0 < 0)) __PYX_ERR(2, 229, __pyx_L1_error)
          #else
          __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_5); __pyx_t_5++; if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 229, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          #endif
          if (!(likely(((__pyx_t_3) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_3, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 229, __pyx_L1_error)
          __Pyx_XDECREF_SET(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_3));
          __pyx_t_3 = 0;

          /* "fa2/fa2util.py":230
 *                 else:
 *                     for n in bottomrightNodes:
 *                         subregion = Region([n])             # <<<<<<<<<<<<<<
 *                         self.subregions.append(subregion)
 * 
 */
          __pyx_t_3 = PyList_New(1); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 230, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_INCREF(((PyObject *)__pyx_v_n));
          __Pyx_GIVEREF(((PyObject *)__pyx_v_n));
          PyList_SET_ITEM(__pyx_t_3, 0, ((PyObject *)__pyx_v_n));
          __pyx_t_2 = __Pyx_PyObject_CallOneArg(((PyObject *)__pyx_ptype_3fa2_7fa2util_Region), __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 230, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          __Pyx_XDECREF_SET(__pyx_v_subregion, ((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_t_2));
          __pyx_t_2 = 0;

          /* "fa2/fa2util.py":231
 *                     for n in bottomrightNodes:
 *                         subregion = Region([n])
 *                         self.subregions.append(subregion)             # <<<<<<<<<<<<<<
 * 
 *             for subregion in self.subregions:
 */
          if (unlikely(__pyx_v_self->subregions == Py_None)) {
            PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%.30s'", "append");
            __PYX_ERR(2, 231, __pyx_L1_error)
          }
          __pyx_t_7 = __Pyx_PyList_Append(__pyx_v_self->subregions, ((PyObject *)__pyx_v_subregion)); if (unlikely(__pyx_t_7 == ((int)-1))) __PYX_ERR(2, 231, __pyx_L1_error)

          /* "fa2/fa2util.py":229
 *                     self.subregions.append(subregion)
 *                 else:
 *                     for n in bottomrightNodes:             # <<<<<<<<<<<<<<
 *                         subregion = Region([n])
 *                         self.subregions.append(subregion)
 */
        }
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      }
      __pyx_L22:;

      /* "fa2/fa2util.py":224
 *                         self.subregions.append(subregion)
 * 
 *             if len(bottomrightNodes) > 0:             # <<<<<<<<<<<<<<
 *                 if len(bottomrightNodes) < len(self.nodes):
 *                     subregion = Region(bottomrightNodes)
 */
    }

    /* "fa2/fa2util.py":233
 *                         self.subregions.append(subregion)
 * 
 *             for subregion in self.subregions:             # <<<<<<<<<<<<<<
 *                 subregion.buildSubRegions()
 * 
 */
    if (unlikely(__pyx_v_self->subregions == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
      __PYX_ERR(2, 233, __pyx_L1_error)
    }
    __pyx_t_1 = __pyx_v_self->subregions; __Pyx_INCREF(__pyx_t_1); __pyx_t_5 = 0;
    for (;;) {
      if (__pyx_t_5 >= PyList_GET_SIZE(__pyx_t_1)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_2 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_5); __Pyx_INCREF(__pyx_t_2); __pyx_t_5++; if (unlikely(0 < 0)) __PYX_ERR(2, 233, __pyx_L1_error)
      #else
      __pyx_t_2 = PySequence_ITEM(__pyx_t_1, __pyx_t_5); __pyx_t_5++; if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 233, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      #endif
      if (!(likely(((__pyx_t_2) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_2, __pyx_ptype_3fa2_7fa2util_Region))))) __PYX_ERR(2, 233, __pyx_L1_error)
      __Pyx_XDECREF_SET(__pyx_v_subregion, ((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_t_2));
      __pyx_t_2 = 0;

      /* "fa2/fa2util.py":234
 * 
 *             for subregion in self.subregions:
 *                 subregion.buildSubRegions()             # <<<<<<<<<<<<<<
 * 
 *     def applyForce(self, n, theta, coefficient=0):
 */
      ((struct __pyx_vtabstruct_3fa2_7fa2util_Region *)__pyx_v_subregion->__pyx_vtab)->buildSubRegions(__pyx_v_subregion, 0);

      /* "fa2/fa2util.py":233
 *                         self.subregions.append(subregion)
 * 
 *             for subregion in self.subregions:             # <<<<<<<<<<<<<<
 *                 subregion.buildSubRegions()
 * 
 */
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "fa2/fa2util.py":177
 * 
 *     def buildSubRegions(self):
 *         if len(self.nodes) > 1:             # <<<<<<<<<<<<<<
 *             topleftNodes = []
 *             bottomleftNodes = []
 */
  }

  /* "fa2/fa2util.py":176
 *                 self.size = max(self.size, 2 * distance)
 * 
 *     def buildSubRegions(self):             # <<<<<<<<<<<<<<
 *         if len(self.nodes) > 1:
 *             topleftNodes = []
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_WriteUnraisable("fa2.fa2util.Region.buildSubRegions", __pyx_clineno, __pyx_lineno, __pyx_filename, 1, 0);
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_n);
  __Pyx_XDECREF(__pyx_v_topleftNodes);
  __Pyx_XDECREF(__pyx_v_bottomleftNodes);
  __Pyx_XDECREF(__pyx_v_toprightNodes);
  __Pyx_XDECREF(__pyx_v_bottomrightNodes);
  __Pyx_XDECREF((PyObject *)__pyx_v_subregion);
  __Pyx_RefNannyFinishContext();
}

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_3buildSubRegions(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_6Region_3buildSubRegions = {"buildSubRegions", (PyCFunction)__pyx_pw_3fa2_7fa2util_6Region_3buildSubRegions, METH_NOARGS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_3buildSubRegions(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("buildSubRegions (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_2buildSubRegions(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_6Region_2buildSubRegions(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("buildSubRegions", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_void_to_None(__pyx_f_3fa2_7fa2util_6Region_buildSubRegions(__pyx_v_self, 1)); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 176, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Region.buildSubRegions", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.py":236
 *                 subregion.buildSubRegions()
 * 
 *     def applyForce(self, n, theta, coefficient=0):             # <<<<<<<<<<<<<<
 *         if len(self.nodes) < 2:
 *             linRepulsion(n, self.nodes[0], coefficient)
 */

static void __pyx_f_3fa2_7fa2util_6Region_applyForce(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n, double __pyx_v_theta, struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForce *__pyx_optional_args) {
  double __pyx_v_coefficient = ((double)0.0);
  double __pyx_v_distance;
  struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_subregion = 0;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  Py_ssize_t __pyx_t_2;
  int __pyx_t_3;
  struct __pyx_opt_args_3fa2_7fa2util_linRepulsion __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  double __pyx_t_8;
  struct __pyx_opt_args_3fa2_7fa2util_linRepulsion_region __pyx_t_9;
  struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForce __pyx_t_10;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("applyForce", 0);
  if (__pyx_optional_args) {
    if (__pyx_optional_args->__pyx_n > 0) {
      __pyx_v_coefficient = __pyx_optional_args->coefficient;
    }
  }

  /* "fa2/fa2util.py":237
 * 
 *     def applyForce(self, n, theta, coefficient=0):
 *         if len(self.nodes) < 2:             # <<<<<<<<<<<<<<
 *             linRepulsion(n, self.nodes[0], coefficient)
 *         else:
 */
  __pyx_t_1 = __pyx_v_self->nodes;
  __Pyx_INCREF(__pyx_t_1);
  if (unlikely(__pyx_t_1 == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    __PYX_ERR(2, 237, __pyx_L1_error)
  }
  __pyx_t_2 = PyList_GET_SIZE(__pyx_t_1); if (unlikely(__pyx_t_2 == ((Py_ssize_t)-1))) __PYX_ERR(2, 237, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_3 = ((__pyx_t_2 < 2) != 0);
  if (__pyx_t_3) {

    /* "fa2/fa2util.py":238
 *     def applyForce(self, n, theta, coefficient=0):
 *         if len(self.nodes) < 2:
 *             linRepulsion(n, self.nodes[0], coefficient)             # <<<<<<<<<<<<<<
 *         else:
 *             distance = sqrt((n.x - self.massCenterX) ** 2 + (n.y - self.massCenterY) ** 2)
 */
    if (unlikely(__pyx_v_self->nodes == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      __PYX_ERR(2, 238, __pyx_L1_error)
    }
    __pyx_t_1 = __Pyx_GetItemInt_List(__pyx_v_self->nodes, 0, long, 1, __Pyx_PyInt_From_long, 1, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 238, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 238, __pyx_L1_error)
    __pyx_t_4.__pyx_n = 1;
    __pyx_t_4.coefficient = __pyx_v_coefficient;
    __pyx_f_3fa2_7fa2util_linRepulsion(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_1), &__pyx_t_4); 
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "fa2/fa2util.py":237
 * 
 *     def applyForce(self, n, theta, coefficient=0):
 *         if len(self.nodes) < 2:             # <<<<<<<<<<<<<<
 *             linRepulsion(n, self.nodes[0], coefficient)
 *         else:
 */
    goto __pyx_L3;
  }

  /* "fa2/fa2util.py":240
 *             linRepulsion(n, self.nodes[0], coefficient)
 *         else:
 *             distance = sqrt((n.x - self.massCenterX) ** 2 + (n.y - self.massCenterY) ** 2)             # <<<<<<<<<<<<<<
 *             if distance * theta > self.size:
 *                 linRepulsion_region(n, self, coefficient)
 */
  /*else*/ {
    __Pyx_GetModuleGlobalName(__pyx_t_5, __pyx_n_s_sqrt); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 240, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_6 = PyFloat_FromDouble((pow((__pyx_v_n->x - __pyx_v_self->massCenterX), 2.0) + pow((__pyx_v_n->y - __pyx_v_self->massCenterY), 2.0))); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 240, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_7 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
      __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_5);
      if (likely(__pyx_t_7)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_7);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_5, function);
      }
    }
    __pyx_t_1 = (__pyx_t_7) ? __Pyx_PyObject_Call2Args(__pyx_t_5, __pyx_t_7, __pyx_t_6) : __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_t_6);
    __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 240, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_8 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_8 == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 240, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_v_distance = __pyx_t_8;

    /* "fa2/fa2util.py":241
 *         else:
 *             distance = sqrt((n.x - self.massCenterX) ** 2 + (n.y - self.massCenterY) ** 2)
 *             if distance * theta > self.size:             # <<<<<<<<<<<<<<
 *                 linRepulsion_region(n, self, coefficient)
 *             else:
 */
    __pyx_t_3 = (((__pyx_v_distance * __pyx_v_theta) > __pyx_v_self->size) != 0);
    if (__pyx_t_3) {

      /* "fa2/fa2util.py":242
 *             distance = sqrt((n.x - self.massCenterX) ** 2 + (n.y - self.massCenterY) ** 2)
 *             if distance * theta > self.size:
 *                 linRepulsion_region(n, self, coefficient)             # <<<<<<<<<<<<<<
 *             else:
 *                 for subregion in self.subregions:
 */
      __pyx_t_9.__pyx_n = 1;
      __pyx_t_9.coefficient = __pyx_v_coefficient;
      __pyx_f_3fa2_7fa2util_linRepulsion_region(__pyx_v_n, __pyx_v_self, &__pyx_t_9); 

      /* "fa2/fa2util.py":241
 *         else:
 *             distance = sqrt((n.x - self.massCenterX) ** 2 + (n.y - self.massCenterY) ** 2)
 *             if distance * theta > self.size:             # <<<<<<<<<<<<<<
 *                 linRepulsion_region(n, self, coefficient)
 *             else:
 */
      goto __pyx_L4;
    }

    /* "fa2/fa2util.py":244
 *                 linRepulsion_region(n, self, coefficient)
 *             else:
 *                 for subregion in self.subregions:             # <<<<<<<<<<<<<<
 *                     subregion.applyForce(n, theta, coefficient)
 * 
 */
    /*else*/ {
      if (unlikely(__pyx_v_self->subregions == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
        __PYX_ERR(2, 244, __pyx_L1_error)
      }
      __pyx_t_1 = __pyx_v_self->subregions; __Pyx_INCREF(__pyx_t_1); __pyx_t_2 = 0;
      for (;;) {
        if (__pyx_t_2 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_5 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_5); __pyx_t_2++; if (unlikely(0 < 0)) __PYX_ERR(2, 244, __pyx_L1_error)
        #else
        __pyx_t_5 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 244, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        #endif
        if (!(likely(((__pyx_t_5) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_5, __pyx_ptype_3fa2_7fa2util_Region))))) __PYX_ERR(2, 244, __pyx_L1_error)
        __Pyx_XDECREF_SET(__pyx_v_subregion, ((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_t_5));
        __pyx_t_5 = 0;

        /* "fa2/fa2util.py":245
 *             else:
 *                 for subregion in self.subregions:
 *                     subregion.applyForce(n, theta, coefficient)             # <<<<<<<<<<<<<<
 * 
 *     def applyForceOnNodes(self, nodes, theta, coefficient=0):
 */
        __pyx_t_10.__pyx_n = 1;
        __pyx_t_10.coefficient = __pyx_v_coefficient;
        ((struct __pyx_vtabstruct_3fa2_7fa2util_Region *)__pyx_v_subregion->__pyx_vtab)->applyForce(__pyx_v_subregion, __pyx_v_n, __pyx_v_theta, &__pyx_t_10); 

        /* "fa2/fa2util.py":244
 *                 linRepulsion_region(n, self, coefficient)
 *             else:
 *                 for subregion in self.subregions:             # <<<<<<<<<<<<<<
 *                     subregion.applyForce(n, theta, coefficient)
 * 
 */
      }
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    }
    __pyx_L4:;
  }
  __pyx_L3:;

  /* "fa2/fa2util.py":236
 *                 subregion.buildSubRegions()
 * 
 *     def applyForce(self, n, theta, coefficient=0):             # <<<<<<<<<<<<<<
 *         if len(self.nodes) < 2:
 *             linRepulsion(n, self.nodes[0], coefficient)
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_WriteUnraisable("fa2.fa2util.Region.applyForce", __pyx_clineno, __pyx_lineno, __pyx_filename, 1, 0);
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_subregion);
  __Pyx_RefNannyFinishContext();
}

/* "fa2/fa2util.py":247
 *                     subregion.applyForce(n, theta, coefficient)
 * 
 *     def applyForceOnNodes(self, nodes, theta, coefficient=0):             # <<<<<<<<<<<<<<
 *         for n in nodes:
 *             self.applyForce(n, theta, coefficient)
 */

static PyObject *__pyx_pw_3fa2_7fa2util_6Region_5applyForceOnNodes(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyObject *__pyx_f_3fa2_7fa2util_6Region_applyForceOnNodes(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_nodes, double __pyx_v_theta, int __pyx_skip_dispatch, struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForceOnNodes *__pyx_optional_args) {
  double __pyx_v_coefficient = ((double)0.0);
  struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n = 0;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_t_7;
  PyObject *__pyx_t_8 = NULL;
  Py_ssize_t __pyx_t_9;
  struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForce __pyx_t_10;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("applyForceOnNodes", 0);
  if (__pyx_optional_args) {
    if (__pyx_optional_args->__pyx_n > 0) {
      __pyx_v_coefficient = __pyx_optional_args->coefficient;
    }
  }
  /* Check if called by wrapper */
  if (unlikely(__pyx_skip_dispatch)) ;
  /* Check if overridden in Python */
  else if (unlikely((Py_TYPE(((PyObject *)__pyx_v_self))->tp_dictoffset != 0) || (Py_TYPE(((PyObject *)__pyx_v_self))->tp_flags & (Py_TPFLAGS_IS_ABSTRACT | Py_TPFLAGS_HEAPTYPE)))) {
    #if CYTHON_USE_DICT_VERSIONS && CYTHON_USE_PYTYPE_LOOKUP && CYTHON_USE_TYPE_SLOTS
    static PY_UINT64_T __pyx_tp_dict_version = __PYX_DICT_VERSION_INIT, __pyx_obj_dict_version = __PYX_DICT_VERSION_INIT;
    if (unlikely(!__Pyx_object_dict_version_matches(((PyObject *)__pyx_v_self), __pyx_tp_dict_version, __pyx_obj_dict_version))) {
      PY_UINT64_T __pyx_type_dict_guard = __Pyx_get_tp_dict_version(((PyObject *)__pyx_v_self));
      #endif
      __pyx_t_1 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v_self), __pyx_n_s_applyForceOnNodes); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 247, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      if (!PyCFunction_Check(__pyx_t_1) || (PyCFunction_GET_FUNCTION(__pyx_t_1) != (PyCFunction)(void*)__pyx_pw_3fa2_7fa2util_6Region_5applyForceOnNodes)) {
        __Pyx_XDECREF(__pyx_r);
        __pyx_t_3 = PyFloat_FromDouble(__pyx_v_theta); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 247, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_4 = PyFloat_FromDouble(__pyx_v_coefficient); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 247, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_1);
        __pyx_t_5 = __pyx_t_1; __pyx_t_6 = NULL;
        __pyx_t_7 = 0;
        if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
          __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_5);
          if (likely(__pyx_t_6)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
            __Pyx_INCREF(__pyx_t_6);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_5, function);
            __pyx_t_7 = 1;
          }
        }
        #if CYTHON_FAST_PYCALL
        if (PyFunction_Check(__pyx_t_5)) {
          PyObject *__pyx_temp[4] = {__pyx_t_6, __pyx_v_nodes, __pyx_t_3, __pyx_t_4};
          __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_7, 3+__pyx_t_7); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 247, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
        } else
        #endif
        #if CYTHON_FAST_PYCCALL
        if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
          PyObject *__pyx_temp[4] = {__pyx_t_6, __pyx_v_nodes, __pyx_t_3, __pyx_t_4};
          __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_7, 3+__pyx_t_7); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 247, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
        } else
        #endif
        {
          __pyx_t_8 = PyTuple_New(3+__pyx_t_7); if (unlikely(!__pyx_t_8)) __PYX_ERR(2, 247, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          if (__pyx_t_6) {
            __Pyx_GIVEREF(__pyx_t_6); PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_6); __pyx_t_6 = NULL;
          }
          __Pyx_INCREF(__pyx_v_nodes);
          __Pyx_GIVEREF(__pyx_v_nodes);
          PyTuple_SET_ITEM(__pyx_t_8, 0+__pyx_t_7, __pyx_v_nodes);
          __Pyx_GIVEREF(__pyx_t_3);
          PyTuple_SET_ITEM(__pyx_t_8, 1+__pyx_t_7, __pyx_t_3);
          __Pyx_GIVEREF(__pyx_t_4);
          PyTuple_SET_ITEM(__pyx_t_8, 2+__pyx_t_7, __pyx_t_4);
          __pyx_t_3 = 0;
          __pyx_t_4 = 0;
          __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_8, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 247, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
        }
        __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
        __pyx_r = __pyx_t_2;
        __pyx_t_2 = 0;
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        goto __pyx_L0;
      }
      #if CYTHON_USE_DICT_VERSIONS && CYTHON_USE_PYTYPE_LOOKUP && CYTHON_USE_TYPE_SLOTS
      __pyx_tp_dict_version = __Pyx_get_tp_dict_version(((PyObject *)__pyx_v_self));
      __pyx_obj_dict_version = __Pyx_get_object_dict_version(((PyObject *)__pyx_v_self));
      if (unlikely(__pyx_type_dict_guard != __pyx_tp_dict_version)) {
        __pyx_tp_dict_version = __pyx_obj_dict_version = __PYX_DICT_VERSION_INIT;
      }
      #endif
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      #if CYTHON_USE_DICT_VERSIONS && CYTHON_USE_PYTYPE_LOOKUP && CYTHON_USE_TYPE_SLOTS
    }
    #endif
  }

  /* "fa2/fa2util.py":248
 * 
 *     def applyForceOnNodes(self, nodes, theta, coefficient=0):
 *         for n in nodes:             # <<<<<<<<<<<<<<
 *             self.applyForce(n, theta, coefficient)
 * 
 */
  if (unlikely(__pyx_v_nodes == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
    __PYX_ERR(2, 248, __pyx_L1_error)
  }
  __pyx_t_1 = __pyx_v_nodes; __Pyx_INCREF(__pyx_t_1); __pyx_t_9 = 0;
  for (;;) {
    if (__pyx_t_9 >= PyList_GET_SIZE(__pyx_t_1)) break;
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    __pyx_t_2 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_9); __Pyx_INCREF(__pyx_t_2); __pyx_t_9++; if (unlikely(0 < 0)) __PYX_ERR(2, 248, __pyx_L1_error)
    #else
    __pyx_t_2 = PySequence_ITEM(__pyx_t_1, __pyx_t_9); __pyx_t_9++; if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 248, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    #endif
    if (!(likely(((__pyx_t_2) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_2, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 248, __pyx_L1_error)
    __Pyx_XDECREF_SET(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_2));
    __pyx_t_2 = 0;

    /* "fa2/fa2util.py":249
 *     def applyForceOnNodes(self, nodes, theta, coefficient=0):
 *         for n in nodes:
 *             self.applyForce(n, theta, coefficient)             # <<<<<<<<<<<<<<
 * 
 * 
 */
    __pyx_t_10.__pyx_n = 1;
    __pyx_t_10.coefficient = __pyx_v_coefficient;
    ((struct __pyx_vtabstruct_3fa2_7fa2util_Region *)__pyx_v_self->__pyx_vtab)->applyForce(__pyx_v_self, __pyx_v_n, __pyx_v_theta, &__pyx_t_10); 

    /* "fa2/fa2util.py":248
 * 
 *     def applyForceOnNodes(self, nodes, theta, coefficient=0):
 *         for n in nodes:             # <<<<<<<<<<<<<<
 *             self.applyForce(n, theta, coefficient)
 * 
 */
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "fa2/fa2util.py":247
 *                     subregion.applyForce(n, theta, coefficient)
 * 
 *     def applyForceOnNodes(self, nodes, theta, coefficient=0):             # <<<<<<<<<<<<<<
 *         for n in nodes:
 *             self.applyForce(n, theta, coefficient)
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_AddTraceback("fa2.fa2util.Region.applyForceOnNodes", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_n);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_5applyForceOnNodes(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_6Region_5applyForceOnNodes = {"applyForceOnNodes", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_3fa2_7fa2util_6Region_5applyForceOnNodes, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_5applyForceOnNodes(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_nodes = 0;
  double __pyx_v_theta;
  double __pyx_v_coefficient;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("applyForceOnNodes (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_nodes,&__pyx_n_s_theta,&__pyx_n_s_coefficient,0};
    PyObject* values[3] = {0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_nodes)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_theta)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("applyForceOnNodes", 0, 2, 3, 1); __PYX_ERR(2, 247, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_coefficient);
          if (value) { values[2] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "applyForceOnNodes") < 0)) __PYX_ERR(2, 247, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_nodes = ((PyObject*)values[0]);
    __pyx_v_theta = __pyx_PyFloat_AsDouble(values[1]); if (unlikely((__pyx_v_theta == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 247, __pyx_L3_error)
    if (values[2]) {
      __pyx_v_coefficient = __pyx_PyFloat_AsDouble(values[2]); if (unlikely((__pyx_v_coefficient == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 247, __pyx_L3_error)
    } else {
      __pyx_v_coefficient = ((double)0.0);
    }
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("applyForceOnNodes", 0, 2, 3, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(2, 247, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("fa2.fa2util.Region.applyForceOnNodes", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_nodes), (&PyList_Type), 1, "nodes", 1))) __PYX_ERR(2, 247, __pyx_L1_error)
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_4applyForceOnNodes(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self), __pyx_v_nodes, __pyx_v_theta, __pyx_v_coefficient);

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_6Region_4applyForceOnNodes(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_nodes, double __pyx_v_theta, double __pyx_v_coefficient) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForceOnNodes __pyx_t_2;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("applyForceOnNodes", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2.__pyx_n = 1;
  __pyx_t_2.coefficient = __pyx_v_coefficient;
  __pyx_t_1 = __pyx_vtabptr_3fa2_7fa2util_Region->applyForceOnNodes(__pyx_v_self, __pyx_v_nodes, __pyx_v_theta, 1, &__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 247, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Region.applyForceOnNodes", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.pxd":77
 * 
 * cdef class Region:
 *     cdef public double mass             # <<<<<<<<<<<<<<
 *     cdef public double massCenterX, massCenterY
 *     cdef public double size
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_4mass_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_4mass_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_4mass___get__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_6Region_4mass___get__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->mass); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 77, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Region.mass.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_6Region_4mass_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_6Region_4mass_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_4mass_2__set__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_6Region_4mass_2__set__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 77, __pyx_L1_error)
  __pyx_v_self->mass = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Region.mass.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.pxd":78
 * cdef class Region:
 *     cdef public double mass
 *     cdef public double massCenterX, massCenterY             # <<<<<<<<<<<<<<
 *     cdef public double size
 *     cdef public list nodes
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_11massCenterX_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_11massCenterX_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_11massCenterX___get__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_6Region_11massCenterX___get__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->massCenterX); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 78, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Region.massCenterX.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_6Region_11massCenterX_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_6Region_11massCenterX_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_11massCenterX_2__set__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_6Region_11massCenterX_2__set__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 78, __pyx_L1_error)
  __pyx_v_self->massCenterX = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Region.massCenterX.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_11massCenterY_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_11massCenterY_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_11massCenterY___get__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_6Region_11massCenterY___get__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->massCenterY); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 78, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Region.massCenterY.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_6Region_11massCenterY_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_6Region_11massCenterY_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_11massCenterY_2__set__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_6Region_11massCenterY_2__set__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 78, __pyx_L1_error)
  __pyx_v_self->massCenterY = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Region.massCenterY.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.pxd":79
 *     cdef public double mass
 *     cdef public double massCenterX, massCenterY
 *     cdef public double size             # <<<<<<<<<<<<<<
 *     cdef public list nodes
 *     cdef public list subregions
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_4size_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_4size_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_4size___get__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_6Region_4size___get__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->size); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 79, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Region.size.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_6Region_4size_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_6Region_4size_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_4size_2__set__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_6Region_4size_2__set__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 79, __pyx_L1_error)
  __pyx_v_self->size = __pyx_t_1;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("fa2.fa2util.Region.size.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.pxd":80
 *     cdef public double massCenterX, massCenterY
 *     cdef public double size
 *     cdef public list nodes             # <<<<<<<<<<<<<<
 *     cdef public list subregions
 * 
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_5nodes_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_5nodes_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_5nodes___get__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_6Region_5nodes___get__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_self->nodes);
  __pyx_r = __pyx_v_self->nodes;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_6Region_5nodes_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_6Region_5nodes_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_5nodes_2__set__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_6Region_5nodes_2__set__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "list", Py_TYPE(__pyx_v_value)->tp_name), 0))) __PYX_ERR(0, 80, __pyx_L1_error)
  __pyx_t_1 = __pyx_v_value;
  __Pyx_INCREF(__pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __Pyx_GOTREF(__pyx_v_self->nodes);
  __Pyx_DECREF(__pyx_v_self->nodes);
  __pyx_v_self->nodes = ((PyObject*)__pyx_t_1);
  __pyx_t_1 = 0;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Region.nodes.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_6Region_5nodes_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_3fa2_7fa2util_6Region_5nodes_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_5nodes_4__del__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_6Region_5nodes_4__del__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->nodes);
  __Pyx_DECREF(__pyx_v_self->nodes);
  __pyx_v_self->nodes = ((PyObject*)Py_None);

  /* function exit code */
  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.pxd":81
 *     cdef public double size
 *     cdef public list nodes
 *     cdef public list subregions             # <<<<<<<<<<<<<<
 * 
 *     @cython.locals(massSumX = cython.double,
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_10subregions_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_10subregions_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_10subregions___get__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_6Region_10subregions___get__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_self->subregions);
  __pyx_r = __pyx_v_self->subregions;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_6Region_10subregions_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_3fa2_7fa2util_6Region_10subregions_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_10subregions_2__set__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self), ((PyObject *)__pyx_v_value));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_6Region_10subregions_2__set__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "list", Py_TYPE(__pyx_v_value)->tp_name), 0))) __PYX_ERR(0, 81, __pyx_L1_error)
  __pyx_t_1 = __pyx_v_value;
  __Pyx_INCREF(__pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __Pyx_GOTREF(__pyx_v_self->subregions);
  __Pyx_DECREF(__pyx_v_self->subregions);
  __pyx_v_self->subregions = ((PyObject*)__pyx_t_1);
  __pyx_t_1 = 0;

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Region.subregions.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_3fa2_7fa2util_6Region_10subregions_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_3fa2_7fa2util_6Region_10subregions_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_10subregions_4__del__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_3fa2_7fa2util_6Region_10subregions_4__del__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->subregions);
  __Pyx_DECREF(__pyx_v_self->subregions);
  __pyx_v_self->subregions = ((PyObject*)Py_None);

  /* function exit code */
  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "(tree fragment)":1
 * def __reduce_cython__(self):             # <<<<<<<<<<<<<<
 *     cdef tuple state
 *     cdef object _dict
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_7__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_6Region_7__reduce_cython__ = {"__reduce_cython__", (PyCFunction)__pyx_pw_3fa2_7fa2util_6Region_7__reduce_cython__, METH_NOARGS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_7__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__reduce_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_6__reduce_cython__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_6Region_6__reduce_cython__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self) {
  PyObject *__pyx_v_state = 0;
  PyObject *__pyx_v__dict = 0;
  int __pyx_v_use_setstate;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  int __pyx_t_7;
  int __pyx_t_8;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__reduce_cython__", 0);

  /* "(tree fragment)":5
 *     cdef object _dict
 *     cdef bint use_setstate
 *     state = (self.mass, self.massCenterX, self.massCenterY, self.nodes, self.size, self.subregions)             # <<<<<<<<<<<<<<
 *     _dict = getattr(self, '__dict__', None)
 *     if _dict is not None:
 */
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->mass); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyFloat_FromDouble(__pyx_v_self->massCenterX); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyFloat_FromDouble(__pyx_v_self->massCenterY); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = PyFloat_FromDouble(__pyx_v_self->size); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = PyTuple_New(6); if (unlikely(!__pyx_t_5)) __PYX_ERR(1, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_5, 2, __pyx_t_3);
  __Pyx_INCREF(__pyx_v_self->nodes);
  __Pyx_GIVEREF(__pyx_v_self->nodes);
  PyTuple_SET_ITEM(__pyx_t_5, 3, __pyx_v_self->nodes);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_5, 4, __pyx_t_4);
  __Pyx_INCREF(__pyx_v_self->subregions);
  __Pyx_GIVEREF(__pyx_v_self->subregions);
  PyTuple_SET_ITEM(__pyx_t_5, 5, __pyx_v_self->subregions);
  __pyx_t_1 = 0;
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_v_state = ((PyObject*)__pyx_t_5);
  __pyx_t_5 = 0;

  /* "(tree fragment)":6
 *     cdef bint use_setstate
 *     state = (self.mass, self.massCenterX, self.massCenterY, self.nodes, self.size, self.subregions)
 *     _dict = getattr(self, '__dict__', None)             # <<<<<<<<<<<<<<
 *     if _dict is not None:
 *         state += (_dict,)
 */
  __pyx_t_5 = __Pyx_GetAttr3(((PyObject *)__pyx_v_self), __pyx_n_s_dict, Py_None); if (unlikely(!__pyx_t_5)) __PYX_ERR(1, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_v__dict = __pyx_t_5;
  __pyx_t_5 = 0;

  /* "(tree fragment)":7
 *     state = (self.mass, self.massCenterX, self.massCenterY, self.nodes, self.size, self.subregions)
 *     _dict = getattr(self, '__dict__', None)
 *     if _dict is not None:             # <<<<<<<<<<<<<<
 *         state += (_dict,)
 *         use_setstate = True
 */
  __pyx_t_6 = (__pyx_v__dict != Py_None);
  __pyx_t_7 = (__pyx_t_6 != 0);
  if (__pyx_t_7) {

    /* "(tree fragment)":8
 *     _dict = getattr(self, '__dict__', None)
 *     if _dict is not None:
 *         state += (_dict,)             # <<<<<<<<<<<<<<
 *         use_setstate = True
 *     else:
 */
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) __PYX_ERR(1, 8, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_INCREF(__pyx_v__dict);
    __Pyx_GIVEREF(__pyx_v__dict);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_v__dict);
    __pyx_t_4 = PyNumber_InPlaceAdd(__pyx_v_state, __pyx_t_5); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 8, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF_SET(__pyx_v_state, ((PyObject*)__pyx_t_4));
    __pyx_t_4 = 0;

    /* "(tree fragment)":9
 *     if _dict is not None:
 *         state += (_dict,)
 *         use_setstate = True             # <<<<<<<<<<<<<<
 *     else:
 *         use_setstate = self.nodes is not None or self.subregions is not None
 */
    __pyx_v_use_setstate = 1;

    /* "(tree fragment)":7
 *     state = (self.mass, self.massCenterX, self.massCenterY, self.nodes, self.size, self.subregions)
 *     _dict = getattr(self, '__dict__', None)
 *     if _dict is not None:             # <<<<<<<<<<<<<<
 *         state += (_dict,)
 *         use_setstate = True
 */
    goto __pyx_L3;
  }

  /* "(tree fragment)":11
 *         use_setstate = True
 *     else:
 *         use_setstate = self.nodes is not None or self.subregions is not None             # <<<<<<<<<<<<<<
 *     if use_setstate:
 *         return __pyx_unpickle_Region, (type(self), 0x66ef4c7, None), state
 */
  /*else*/ {
    __pyx_t_6 = (__pyx_v_self->nodes != ((PyObject*)Py_None));
    __pyx_t_8 = (__pyx_t_6 != 0);
    if (!__pyx_t_8) {
    } else {
      __pyx_t_7 = __pyx_t_8;
      goto __pyx_L4_bool_binop_done;
    }
    __pyx_t_8 = (__pyx_v_self->subregions != ((PyObject*)Py_None));
    __pyx_t_6 = (__pyx_t_8 != 0);
    __pyx_t_7 = __pyx_t_6;
    __pyx_L4_bool_binop_done:;
    __pyx_v_use_setstate = __pyx_t_7;
  }
  __pyx_L3:;

  /* "(tree fragment)":12
 *     else:
 *         use_setstate = self.nodes is not None or self.subregions is not None
 *     if use_setstate:             # <<<<<<<<<<<<<<
 *         return __pyx_unpickle_Region, (type(self), 0x66ef4c7, None), state
 *     else:
 */
  __pyx_t_7 = (__pyx_v_use_setstate != 0);
  if (__pyx_t_7) {

    /* "(tree fragment)":13
 *         use_setstate = self.nodes is not None or self.subregions is not None
 *     if use_setstate:
 *         return __pyx_unpickle_Region, (type(self), 0x66ef4c7, None), state             # <<<<<<<<<<<<<<
 *     else:
 *         return __pyx_unpickle_Region, (type(self), 0x66ef4c7, state)
 */
    __Pyx_XDECREF(__pyx_r);
    __Pyx_GetModuleGlobalName(__pyx_t_4, __pyx_n_s_pyx_unpickle_Region); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 13, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(3); if (unlikely(!__pyx_t_5)) __PYX_ERR(1, 13, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_INCREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_GIVEREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    PyTuple_SET_ITEM(__pyx_t_5, 0, ((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_INCREF(__pyx_int_107934919);
    __Pyx_GIVEREF(__pyx_int_107934919);
    PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_int_107934919);
    __Pyx_INCREF(Py_None);
    __Pyx_GIVEREF(Py_None);
    PyTuple_SET_ITEM(__pyx_t_5, 2, Py_None);
    __pyx_t_3 = PyTuple_New(3); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 13, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_5);
    __Pyx_INCREF(__pyx_v_state);
    __Pyx_GIVEREF(__pyx_v_state);
    PyTuple_SET_ITEM(__pyx_t_3, 2, __pyx_v_state);
    __pyx_t_4 = 0;
    __pyx_t_5 = 0;
    __pyx_r = __pyx_t_3;
    __pyx_t_3 = 0;
    goto __pyx_L0;

    /* "(tree fragment)":12
 *     else:
 *         use_setstate = self.nodes is not None or self.subregions is not None
 *     if use_setstate:             # <<<<<<<<<<<<<<
 *         return __pyx_unpickle_Region, (type(self), 0x66ef4c7, None), state
 *     else:
 */
  }

  /* "(tree fragment)":15
 *         return __pyx_unpickle_Region, (type(self), 0x66ef4c7, None), state
 *     else:
 *         return __pyx_unpickle_Region, (type(self), 0x66ef4c7, state)             # <<<<<<<<<<<<<<
 * def __setstate_cython__(self, __pyx_state):
 *     __pyx_unpickle_Region__set_state(self, __pyx_state)
 */
  /*else*/ {
    __Pyx_XDECREF(__pyx_r);
    __Pyx_GetModuleGlobalName(__pyx_t_3, __pyx_n_s_pyx_unpickle_Region); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_5 = PyTuple_New(3); if (unlikely(!__pyx_t_5)) __PYX_ERR(1, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_INCREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_GIVEREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    PyTuple_SET_ITEM(__pyx_t_5, 0, ((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_INCREF(__pyx_int_107934919);
    __Pyx_GIVEREF(__pyx_int_107934919);
    PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_int_107934919);
    __Pyx_INCREF(__pyx_v_state);
    __Pyx_GIVEREF(__pyx_v_state);
    PyTuple_SET_ITEM(__pyx_t_5, 2, __pyx_v_state);
    __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_5);
    __pyx_t_3 = 0;
    __pyx_t_5 = 0;
    __pyx_r = __pyx_t_4;
    __pyx_t_4 = 0;
    goto __pyx_L0;
  }

  /* "(tree fragment)":1
 * def __reduce_cython__(self):             # <<<<<<<<<<<<<<
 *     cdef tuple state
 *     cdef object _dict
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("fa2.fa2util.Region.__reduce_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_state);
  __Pyx_XDECREF(__pyx_v__dict);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "(tree fragment)":16
 *     else:
 *         return __pyx_unpickle_Region, (type(self), 0x66ef4c7, state)
 * def __setstate_cython__(self, __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_unpickle_Region__set_state(self, __pyx_state)
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_9__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_6Region_9__setstate_cython__ = {"__setstate_cython__", (PyCFunction)__pyx_pw_3fa2_7fa2util_6Region_9__setstate_cython__, METH_O, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_6Region_9__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__setstate_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf_3fa2_7fa2util_6Region_8__setstate_cython__(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v_self), ((PyObject *)__pyx_v___pyx_state));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_6Region_8__setstate_cython__(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v_self, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__setstate_cython__", 0);

  /* "(tree fragment)":17
 *         return __pyx_unpickle_Region, (type(self), 0x66ef4c7, state)
 * def __setstate_cython__(self, __pyx_state):
 *     __pyx_unpickle_Region__set_state(self, __pyx_state)             # <<<<<<<<<<<<<<
 */
  if (!(likely(PyTuple_CheckExact(__pyx_v___pyx_state))||((__pyx_v___pyx_state) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "tuple", Py_TYPE(__pyx_v___pyx_state)->tp_name), 0))) __PYX_ERR(1, 17, __pyx_L1_error)
  __pyx_t_1 = __pyx_f_3fa2_7fa2util___pyx_unpickle_Region__set_state(__pyx_v_self, ((PyObject*)__pyx_v___pyx_state)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 17, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "(tree fragment)":16
 *     else:
 *         return __pyx_unpickle_Region, (type(self), 0x66ef4c7, state)
 * def __setstate_cython__(self, __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_unpickle_Region__set_state(self, __pyx_state)
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.Region.__setstate_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "fa2/fa2util.py":253
 * 
 * # Adjust speed and apply forces step
 * def adjustSpeedAndApplyForces(nodes, speed, speedEfficiency, jitterTolerance):             # <<<<<<<<<<<<<<
 *     # Auto adjust speed.
 *     totalSwinging = 0.0  # How much irregular movement
 */

static PyObject *__pyx_pw_3fa2_7fa2util_9adjustSpeedAndApplyForces(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyObject *__pyx_f_3fa2_7fa2util_adjustSpeedAndApplyForces(PyObject *__pyx_v_nodes, double __pyx_v_speed, double __pyx_v_speedEfficiency, double __pyx_v_jitterTolerance, CYTHON_UNUSED int __pyx_skip_dispatch) {
  double __pyx_v_totalSwinging;
  double __pyx_v_totalEffectiveTraction;
  struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v_n = 0;
  double __pyx_v_swinging;
  double __pyx_v_estimatedOptimalJitterTolerance;
  double __pyx_v_minJT;
  double __pyx_v_maxJT;
  double __pyx_v_jt;
  double __pyx_v_minSpeedEfficiency;
  double __pyx_v_targetSpeed;
  double __pyx_v_maxRise;
  double __pyx_v_factor;
  PyObject *__pyx_v_values = 0;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  Py_ssize_t __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  double __pyx_t_7;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  Py_ssize_t __pyx_t_10;
  Py_ssize_t __pyx_t_11;
  double __pyx_t_12;
  double __pyx_t_13;
  int __pyx_t_14;
  int __pyx_t_15;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("adjustSpeedAndApplyForces", 0);

  /* "fa2/fa2util.py":255
 * def adjustSpeedAndApplyForces(nodes, speed, speedEfficiency, jitterTolerance):
 *     # Auto adjust speed.
 *     totalSwinging = 0.0  # How much irregular movement             # <<<<<<<<<<<<<<
 *     totalEffectiveTraction = 0.0  # How much useful movement
 *     for n in nodes:
 */
  __pyx_v_totalSwinging = 0.0;

  /* "fa2/fa2util.py":256
 *     # Auto adjust speed.
 *     totalSwinging = 0.0  # How much irregular movement
 *     totalEffectiveTraction = 0.0  # How much useful movement             # <<<<<<<<<<<<<<
 *     for n in nodes:
 *         swinging = sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))
 */
  __pyx_v_totalEffectiveTraction = 0.0;

  /* "fa2/fa2util.py":257
 *     totalSwinging = 0.0  # How much irregular movement
 *     totalEffectiveTraction = 0.0  # How much useful movement
 *     for n in nodes:             # <<<<<<<<<<<<<<
 *         swinging = sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))
 *         totalSwinging += n.mass * swinging
 */
  if (unlikely(__pyx_v_nodes == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
    __PYX_ERR(2, 257, __pyx_L1_error)
  }
  __pyx_t_1 = __pyx_v_nodes; __Pyx_INCREF(__pyx_t_1); __pyx_t_2 = 0;
  for (;;) {
    if (__pyx_t_2 >= PyList_GET_SIZE(__pyx_t_1)) break;
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    __pyx_t_3 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_3); __pyx_t_2++; if (unlikely(0 < 0)) __PYX_ERR(2, 257, __pyx_L1_error)
    #else
    __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 257, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    #endif
    if (!(likely(((__pyx_t_3) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_3, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 257, __pyx_L1_error)
    __Pyx_XDECREF_SET(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_3));
    __pyx_t_3 = 0;

    /* "fa2/fa2util.py":258
 *     totalEffectiveTraction = 0.0  # How much useful movement
 *     for n in nodes:
 *         swinging = sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))             # <<<<<<<<<<<<<<
 *         totalSwinging += n.mass * swinging
 *         totalEffectiveTraction += .5 * n.mass * sqrt(
 */
    __Pyx_GetModuleGlobalName(__pyx_t_4, __pyx_n_s_sqrt); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 258, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyFloat_FromDouble((((__pyx_v_n->old_dx - __pyx_v_n->dx) * (__pyx_v_n->old_dx - __pyx_v_n->dx)) + ((__pyx_v_n->old_dy - __pyx_v_n->dy) * (__pyx_v_n->old_dy - __pyx_v_n->dy)))); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 258, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_6 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
      __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_4);
      if (likely(__pyx_t_6)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_6);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_4, function);
      }
    }
    __pyx_t_3 = (__pyx_t_6) ? __Pyx_PyObject_Call2Args(__pyx_t_4, __pyx_t_6, __pyx_t_5) : __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_5);
    __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 258, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_7 = __pyx_PyFloat_AsDouble(__pyx_t_3); if (unlikely((__pyx_t_7 == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 258, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_v_swinging = __pyx_t_7;

    /* "fa2/fa2util.py":259
 *     for n in nodes:
 *         swinging = sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))
 *         totalSwinging += n.mass * swinging             # <<<<<<<<<<<<<<
 *         totalEffectiveTraction += .5 * n.mass * sqrt(
 *             (n.old_dx + n.dx) * (n.old_dx + n.dx) + (n.old_dy + n.dy) * (n.old_dy + n.dy))
 */
    __pyx_v_totalSwinging = (__pyx_v_totalSwinging + (__pyx_v_n->mass * __pyx_v_swinging));

    /* "fa2/fa2util.py":260
 *         swinging = sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))
 *         totalSwinging += n.mass * swinging
 *         totalEffectiveTraction += .5 * n.mass * sqrt(             # <<<<<<<<<<<<<<
 *             (n.old_dx + n.dx) * (n.old_dx + n.dx) + (n.old_dy + n.dy) * (n.old_dy + n.dy))
 * 
 */
    __pyx_t_3 = PyFloat_FromDouble(__pyx_v_totalEffectiveTraction); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 260, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyFloat_FromDouble((.5 * __pyx_v_n->mass)); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 260, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_GetModuleGlobalName(__pyx_t_6, __pyx_n_s_sqrt); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 260, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);

    /* "fa2/fa2util.py":261
 *         totalSwinging += n.mass * swinging
 *         totalEffectiveTraction += .5 * n.mass * sqrt(
 *             (n.old_dx + n.dx) * (n.old_dx + n.dx) + (n.old_dy + n.dy) * (n.old_dy + n.dy))             # <<<<<<<<<<<<<<
 * 
 *     # Optimize jitter tolerance.  The 'right' jitter tolerance for
 */
    __pyx_t_8 = PyFloat_FromDouble((((__pyx_v_n->old_dx + __pyx_v_n->dx) * (__pyx_v_n->old_dx + __pyx_v_n->dx)) + ((__pyx_v_n->old_dy + __pyx_v_n->dy) * (__pyx_v_n->old_dy + __pyx_v_n->dy)))); if (unlikely(!__pyx_t_8)) __PYX_ERR(2, 261, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __pyx_t_9 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_6))) {
      __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_6);
      if (likely(__pyx_t_9)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
        __Pyx_INCREF(__pyx_t_9);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_6, function);
      }
    }
    __pyx_t_5 = (__pyx_t_9) ? __Pyx_PyObject_Call2Args(__pyx_t_6, __pyx_t_9, __pyx_t_8) : __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_8);
    __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 260, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

    /* "fa2/fa2util.py":260
 *         swinging = sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))
 *         totalSwinging += n.mass * swinging
 *         totalEffectiveTraction += .5 * n.mass * sqrt(             # <<<<<<<<<<<<<<
 *             (n.old_dx + n.dx) * (n.old_dx + n.dx) + (n.old_dy + n.dy) * (n.old_dy + n.dy))
 * 
 */
    __pyx_t_6 = PyNumber_Multiply(__pyx_t_4, __pyx_t_5); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 260, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = PyNumber_InPlaceAdd(__pyx_t_3, __pyx_t_6); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 260, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_7 = __pyx_PyFloat_AsDouble(__pyx_t_5); if (unlikely((__pyx_t_7 == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 260, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_v_totalEffectiveTraction = __pyx_t_7;

    /* "fa2/fa2util.py":257
 *     totalSwinging = 0.0  # How much irregular movement
 *     totalEffectiveTraction = 0.0  # How much useful movement
 *     for n in nodes:             # <<<<<<<<<<<<<<
 *         swinging = sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))
 *         totalSwinging += n.mass * swinging
 */
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "fa2/fa2util.py":266
 *     # this network. Bigger networks need more tolerance. Denser
 *     # networks need less tolerance. Totally empiric.
 *     estimatedOptimalJitterTolerance = .05 * sqrt(len(nodes))             # <<<<<<<<<<<<<<
 *     minJT = sqrt(estimatedOptimalJitterTolerance)
 *     maxJT = 10
 */
  __Pyx_GetModuleGlobalName(__pyx_t_5, __pyx_n_s_sqrt); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 266, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (unlikely(__pyx_v_nodes == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    __PYX_ERR(2, 266, __pyx_L1_error)
  }
  __pyx_t_2 = PyList_GET_SIZE(__pyx_v_nodes); if (unlikely(__pyx_t_2 == ((Py_ssize_t)-1))) __PYX_ERR(2, 266, __pyx_L1_error)
  __pyx_t_6 = PyInt_FromSsize_t(__pyx_t_2); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 266, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_5);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_5, function);
    }
  }
  __pyx_t_1 = (__pyx_t_3) ? __Pyx_PyObject_Call2Args(__pyx_t_5, __pyx_t_3, __pyx_t_6) : __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_t_6);
  __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 266, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = PyNumber_Multiply(__pyx_float__05, __pyx_t_1); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 266, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_7 = __pyx_PyFloat_AsDouble(__pyx_t_5); if (unlikely((__pyx_t_7 == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 266, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_v_estimatedOptimalJitterTolerance = __pyx_t_7;

  /* "fa2/fa2util.py":267
 *     # networks need less tolerance. Totally empiric.
 *     estimatedOptimalJitterTolerance = .05 * sqrt(len(nodes))
 *     minJT = sqrt(estimatedOptimalJitterTolerance)             # <<<<<<<<<<<<<<
 *     maxJT = 10
 *     jt = jitterTolerance * max(minJT,
 */
  __Pyx_GetModuleGlobalName(__pyx_t_1, __pyx_n_s_sqrt); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 267, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_6 = PyFloat_FromDouble(__pyx_v_estimatedOptimalJitterTolerance); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 267, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
    }
  }
  __pyx_t_5 = (__pyx_t_3) ? __Pyx_PyObject_Call2Args(__pyx_t_1, __pyx_t_3, __pyx_t_6) : __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_6);
  __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 267, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_7 = __pyx_PyFloat_AsDouble(__pyx_t_5); if (unlikely((__pyx_t_7 == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 267, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_v_minJT = __pyx_t_7;

  /* "fa2/fa2util.py":268
 *     estimatedOptimalJitterTolerance = .05 * sqrt(len(nodes))
 *     minJT = sqrt(estimatedOptimalJitterTolerance)
 *     maxJT = 10             # <<<<<<<<<<<<<<
 *     jt = jitterTolerance * max(minJT,
 *                                min(maxJT, estimatedOptimalJitterTolerance * totalEffectiveTraction / (
 */
  __pyx_v_maxJT = 10.0;

  /* "fa2/fa2util.py":270
 *     maxJT = 10
 *     jt = jitterTolerance * max(minJT,
 *                                min(maxJT, estimatedOptimalJitterTolerance * totalEffectiveTraction / (             # <<<<<<<<<<<<<<
 *                                    len(nodes) * len(nodes))))
 * 
 */
  __pyx_t_7 = (__pyx_v_estimatedOptimalJitterTolerance * __pyx_v_totalEffectiveTraction);

  /* "fa2/fa2util.py":271
 *     jt = jitterTolerance * max(minJT,
 *                                min(maxJT, estimatedOptimalJitterTolerance * totalEffectiveTraction / (
 *                                    len(nodes) * len(nodes))))             # <<<<<<<<<<<<<<
 * 
 *     minSpeedEfficiency = 0.05
 */
  if (unlikely(__pyx_v_nodes == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    __PYX_ERR(2, 271, __pyx_L1_error)
  }
  __pyx_t_2 = PyList_GET_SIZE(__pyx_v_nodes); if (unlikely(__pyx_t_2 == ((Py_ssize_t)-1))) __PYX_ERR(2, 271, __pyx_L1_error)
  if (unlikely(__pyx_v_nodes == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    __PYX_ERR(2, 271, __pyx_L1_error)
  }
  __pyx_t_10 = PyList_GET_SIZE(__pyx_v_nodes); if (unlikely(__pyx_t_10 == ((Py_ssize_t)-1))) __PYX_ERR(2, 271, __pyx_L1_error)
  __pyx_t_11 = (__pyx_t_2 * __pyx_t_10);

  /* "fa2/fa2util.py":270
 *     maxJT = 10
 *     jt = jitterTolerance * max(minJT,
 *                                min(maxJT, estimatedOptimalJitterTolerance * totalEffectiveTraction / (             # <<<<<<<<<<<<<<
 *                                    len(nodes) * len(nodes))))
 * 
 */
  if (unlikely(__pyx_t_11 == 0)) {
    PyErr_SetString(PyExc_ZeroDivisionError, "float division");
    __PYX_ERR(2, 270, __pyx_L1_error)
  }
  __pyx_t_12 = (__pyx_t_7 / __pyx_t_11);
  __pyx_t_7 = __pyx_v_maxJT;
  if (((__pyx_t_12 < __pyx_t_7) != 0)) {
    __pyx_t_13 = __pyx_t_12;
  } else {
    __pyx_t_13 = __pyx_t_7;
  }
  __pyx_t_12 = __pyx_t_13;

  /* "fa2/fa2util.py":269
 *     minJT = sqrt(estimatedOptimalJitterTolerance)
 *     maxJT = 10
 *     jt = jitterTolerance * max(minJT,             # <<<<<<<<<<<<<<
 *                                min(maxJT, estimatedOptimalJitterTolerance * totalEffectiveTraction / (
 *                                    len(nodes) * len(nodes))))
 */
  __pyx_t_13 = __pyx_v_minJT;

  /* "fa2/fa2util.py":270
 *     maxJT = 10
 *     jt = jitterTolerance * max(minJT,
 *                                min(maxJT, estimatedOptimalJitterTolerance * totalEffectiveTraction / (             # <<<<<<<<<<<<<<
 *                                    len(nodes) * len(nodes))))
 * 
 */
  if (((__pyx_t_12 > __pyx_t_13) != 0)) {
    __pyx_t_7 = __pyx_t_12;
  } else {
    __pyx_t_7 = __pyx_t_13;
  }

  /* "fa2/fa2util.py":269
 *     minJT = sqrt(estimatedOptimalJitterTolerance)
 *     maxJT = 10
 *     jt = jitterTolerance * max(minJT,             # <<<<<<<<<<<<<<
 *                                min(maxJT, estimatedOptimalJitterTolerance * totalEffectiveTraction / (
 *                                    len(nodes) * len(nodes))))
 */
  __pyx_v_jt = (__pyx_v_jitterTolerance * __pyx_t_7);

  /* "fa2/fa2util.py":273
 *                                    len(nodes) * len(nodes))))
 * 
 *     minSpeedEfficiency = 0.05             # <<<<<<<<<<<<<<
 * 
 *     # Protective against erratic behavior
 */
  __pyx_v_minSpeedEfficiency = 0.05;

  /* "fa2/fa2util.py":276
 * 
 *     # Protective against erratic behavior
 *     if totalEffectiveTraction and totalSwinging / totalEffectiveTraction > 2.0:             # <<<<<<<<<<<<<<
 *         if speedEfficiency > minSpeedEfficiency:
 *             speedEfficiency *= .5
 */
  __pyx_t_15 = (__pyx_v_totalEffectiveTraction != 0);
  if (__pyx_t_15) {
  } else {
    __pyx_t_14 = __pyx_t_15;
    goto __pyx_L6_bool_binop_done;
  }
  if (unlikely(__pyx_v_totalEffectiveTraction == 0)) {
    PyErr_SetString(PyExc_ZeroDivisionError, "float division");
    __PYX_ERR(2, 276, __pyx_L1_error)
  }
  __pyx_t_15 = (((__pyx_v_totalSwinging / __pyx_v_totalEffectiveTraction) > 2.0) != 0);
  __pyx_t_14 = __pyx_t_15;
  __pyx_L6_bool_binop_done:;
  if (__pyx_t_14) {

    /* "fa2/fa2util.py":277
 *     # Protective against erratic behavior
 *     if totalEffectiveTraction and totalSwinging / totalEffectiveTraction > 2.0:
 *         if speedEfficiency > minSpeedEfficiency:             # <<<<<<<<<<<<<<
 *             speedEfficiency *= .5
 *         jt = max(jt, jitterTolerance)
 */
    __pyx_t_14 = ((__pyx_v_speedEfficiency > __pyx_v_minSpeedEfficiency) != 0);
    if (__pyx_t_14) {

      /* "fa2/fa2util.py":278
 *     if totalEffectiveTraction and totalSwinging / totalEffectiveTraction > 2.0:
 *         if speedEfficiency > minSpeedEfficiency:
 *             speedEfficiency *= .5             # <<<<<<<<<<<<<<
 *         jt = max(jt, jitterTolerance)
 * 
 */
      __pyx_v_speedEfficiency = (__pyx_v_speedEfficiency * .5);

      /* "fa2/fa2util.py":277
 *     # Protective against erratic behavior
 *     if totalEffectiveTraction and totalSwinging / totalEffectiveTraction > 2.0:
 *         if speedEfficiency > minSpeedEfficiency:             # <<<<<<<<<<<<<<
 *             speedEfficiency *= .5
 *         jt = max(jt, jitterTolerance)
 */
    }

    /* "fa2/fa2util.py":279
 *         if speedEfficiency > minSpeedEfficiency:
 *             speedEfficiency *= .5
 *         jt = max(jt, jitterTolerance)             # <<<<<<<<<<<<<<
 * 
 *     if totalSwinging == 0:
 */
    __pyx_t_7 = __pyx_v_jitterTolerance;
    __pyx_t_12 = __pyx_v_jt;
    if (((__pyx_t_7 > __pyx_t_12) != 0)) {
      __pyx_t_13 = __pyx_t_7;
    } else {
      __pyx_t_13 = __pyx_t_12;
    }
    __pyx_v_jt = __pyx_t_13;

    /* "fa2/fa2util.py":276
 * 
 *     # Protective against erratic behavior
 *     if totalEffectiveTraction and totalSwinging / totalEffectiveTraction > 2.0:             # <<<<<<<<<<<<<<
 *         if speedEfficiency > minSpeedEfficiency:
 *             speedEfficiency *= .5
 */
  }

  /* "fa2/fa2util.py":281
 *         jt = max(jt, jitterTolerance)
 * 
 *     if totalSwinging == 0:             # <<<<<<<<<<<<<<
 *         targetSpeed = float('inf')
 *     else:
 */
  __pyx_t_14 = ((__pyx_v_totalSwinging == 0.0) != 0);
  if (__pyx_t_14) {

    /* "fa2/fa2util.py":282
 * 
 *     if totalSwinging == 0:
 *         targetSpeed = float('inf')             # <<<<<<<<<<<<<<
 *     else:
 *         targetSpeed = jt * speedEfficiency * totalEffectiveTraction / totalSwinging
 */
    __pyx_t_13 = __Pyx_PyObject_AsDouble(__pyx_n_s_inf); if (unlikely(__pyx_t_13 == ((double)((double)-1)) && PyErr_Occurred())) __PYX_ERR(2, 282, __pyx_L1_error)
    __pyx_v_targetSpeed = __pyx_t_13;

    /* "fa2/fa2util.py":281
 *         jt = max(jt, jitterTolerance)
 * 
 *     if totalSwinging == 0:             # <<<<<<<<<<<<<<
 *         targetSpeed = float('inf')
 *     else:
 */
    goto __pyx_L9;
  }

  /* "fa2/fa2util.py":284
 *         targetSpeed = float('inf')
 *     else:
 *         targetSpeed = jt * speedEfficiency * totalEffectiveTraction / totalSwinging             # <<<<<<<<<<<<<<
 * 
 *     if totalSwinging > jt * totalEffectiveTraction:
 */
  /*else*/ {
    __pyx_t_13 = ((__pyx_v_jt * __pyx_v_speedEfficiency) * __pyx_v_totalEffectiveTraction);
    if (unlikely(__pyx_v_totalSwinging == 0)) {
      PyErr_SetString(PyExc_ZeroDivisionError, "float division");
      __PYX_ERR(2, 284, __pyx_L1_error)
    }
    __pyx_v_targetSpeed = (__pyx_t_13 / __pyx_v_totalSwinging);
  }
  __pyx_L9:;

  /* "fa2/fa2util.py":286
 *         targetSpeed = jt * speedEfficiency * totalEffectiveTraction / totalSwinging
 * 
 *     if totalSwinging > jt * totalEffectiveTraction:             # <<<<<<<<<<<<<<
 *         if speedEfficiency > minSpeedEfficiency:
 *             speedEfficiency *= .7
 */
  __pyx_t_14 = ((__pyx_v_totalSwinging > (__pyx_v_jt * __pyx_v_totalEffectiveTraction)) != 0);
  if (__pyx_t_14) {

    /* "fa2/fa2util.py":287
 * 
 *     if totalSwinging > jt * totalEffectiveTraction:
 *         if speedEfficiency > minSpeedEfficiency:             # <<<<<<<<<<<<<<
 *             speedEfficiency *= .7
 *     elif speed < 1000:
 */
    __pyx_t_14 = ((__pyx_v_speedEfficiency > __pyx_v_minSpeedEfficiency) != 0);
    if (__pyx_t_14) {

      /* "fa2/fa2util.py":288
 *     if totalSwinging > jt * totalEffectiveTraction:
 *         if speedEfficiency > minSpeedEfficiency:
 *             speedEfficiency *= .7             # <<<<<<<<<<<<<<
 *     elif speed < 1000:
 *         speedEfficiency *= 1.3
 */
      __pyx_v_speedEfficiency = (__pyx_v_speedEfficiency * .7);

      /* "fa2/fa2util.py":287
 * 
 *     if totalSwinging > jt * totalEffectiveTraction:
 *         if speedEfficiency > minSpeedEfficiency:             # <<<<<<<<<<<<<<
 *             speedEfficiency *= .7
 *     elif speed < 1000:
 */
    }

    /* "fa2/fa2util.py":286
 *         targetSpeed = jt * speedEfficiency * totalEffectiveTraction / totalSwinging
 * 
 *     if totalSwinging > jt * totalEffectiveTraction:             # <<<<<<<<<<<<<<
 *         if speedEfficiency > minSpeedEfficiency:
 *             speedEfficiency *= .7
 */
    goto __pyx_L10;
  }

  /* "fa2/fa2util.py":289
 *         if speedEfficiency > minSpeedEfficiency:
 *             speedEfficiency *= .7
 *     elif speed < 1000:             # <<<<<<<<<<<<<<
 *         speedEfficiency *= 1.3
 * 
 */
  __pyx_t_14 = ((__pyx_v_speed < 1000.0) != 0);
  if (__pyx_t_14) {

    /* "fa2/fa2util.py":290
 *             speedEfficiency *= .7
 *     elif speed < 1000:
 *         speedEfficiency *= 1.3             # <<<<<<<<<<<<<<
 * 
 *     # But the speed shoudn't rise too much too quickly, since it would
 */
    __pyx_v_speedEfficiency = (__pyx_v_speedEfficiency * 1.3);

    /* "fa2/fa2util.py":289
 *         if speedEfficiency > minSpeedEfficiency:
 *             speedEfficiency *= .7
 *     elif speed < 1000:             # <<<<<<<<<<<<<<
 *         speedEfficiency *= 1.3
 * 
 */
  }
  __pyx_L10:;

  /* "fa2/fa2util.py":294
 *     # But the speed shoudn't rise too much too quickly, since it would
 *     # make the convergence drop dramatically.
 *     maxRise = .5             # <<<<<<<<<<<<<<
 *     speed = speed + min(targetSpeed - speed, maxRise * speed)
 * 
 */
  __pyx_v_maxRise = .5;

  /* "fa2/fa2util.py":295
 *     # make the convergence drop dramatically.
 *     maxRise = .5
 *     speed = speed + min(targetSpeed - speed, maxRise * speed)             # <<<<<<<<<<<<<<
 * 
 *     # Apply forces.
 */
  __pyx_t_13 = (__pyx_v_maxRise * __pyx_v_speed);
  __pyx_t_7 = (__pyx_v_targetSpeed - __pyx_v_speed);
  if (((__pyx_t_13 < __pyx_t_7) != 0)) {
    __pyx_t_12 = __pyx_t_13;
  } else {
    __pyx_t_12 = __pyx_t_7;
  }
  __pyx_v_speed = (__pyx_v_speed + __pyx_t_12);

  /* "fa2/fa2util.py":301
 *     # Need to add a case if adjustSizes ("prevent overlap") is
 *     # implemented.
 *     for n in nodes:             # <<<<<<<<<<<<<<
 *         swinging = n.mass * sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))
 *         factor = speed / (1.0 + sqrt(speed * swinging))
 */
  if (unlikely(__pyx_v_nodes == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
    __PYX_ERR(2, 301, __pyx_L1_error)
  }
  __pyx_t_5 = __pyx_v_nodes; __Pyx_INCREF(__pyx_t_5); __pyx_t_11 = 0;
  for (;;) {
    if (__pyx_t_11 >= PyList_GET_SIZE(__pyx_t_5)) break;
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    __pyx_t_1 = PyList_GET_ITEM(__pyx_t_5, __pyx_t_11); __Pyx_INCREF(__pyx_t_1); __pyx_t_11++; if (unlikely(0 < 0)) __PYX_ERR(2, 301, __pyx_L1_error)
    #else
    __pyx_t_1 = PySequence_ITEM(__pyx_t_5, __pyx_t_11); __pyx_t_11++; if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 301, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    #endif
    if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_3fa2_7fa2util_Node))))) __PYX_ERR(2, 301, __pyx_L1_error)
    __Pyx_XDECREF_SET(__pyx_v_n, ((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_t_1));
    __pyx_t_1 = 0;

    /* "fa2/fa2util.py":302
 *     # implemented.
 *     for n in nodes:
 *         swinging = n.mass * sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))             # <<<<<<<<<<<<<<
 *         factor = speed / (1.0 + sqrt(speed * swinging))
 *         n.x = n.x + (n.dx * factor)
 */
    __pyx_t_1 = PyFloat_FromDouble(__pyx_v_n->mass); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 302, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_GetModuleGlobalName(__pyx_t_3, __pyx_n_s_sqrt); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 302, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyFloat_FromDouble((((__pyx_v_n->old_dx - __pyx_v_n->dx) * (__pyx_v_n->old_dx - __pyx_v_n->dx)) + ((__pyx_v_n->old_dy - __pyx_v_n->dy) * (__pyx_v_n->old_dy - __pyx_v_n->dy)))); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 302, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_8 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_8 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_8)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_8);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    __pyx_t_6 = (__pyx_t_8) ? __Pyx_PyObject_Call2Args(__pyx_t_3, __pyx_t_8, __pyx_t_4) : __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_4);
    __Pyx_XDECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 302, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = PyNumber_Multiply(__pyx_t_1, __pyx_t_6); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 302, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_12 = __pyx_PyFloat_AsDouble(__pyx_t_3); if (unlikely((__pyx_t_12 == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 302, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_v_swinging = __pyx_t_12;

    /* "fa2/fa2util.py":303
 *     for n in nodes:
 *         swinging = n.mass * sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))
 *         factor = speed / (1.0 + sqrt(speed * swinging))             # <<<<<<<<<<<<<<
 *         n.x = n.x + (n.dx * factor)
 *         n.y = n.y + (n.dy * factor)
 */
    __pyx_t_3 = PyFloat_FromDouble(__pyx_v_speed); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 303, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_GetModuleGlobalName(__pyx_t_1, __pyx_n_s_sqrt); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 303, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_4 = PyFloat_FromDouble((__pyx_v_speed * __pyx_v_swinging)); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 303, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_8 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
      __pyx_t_8 = PyMethod_GET_SELF(__pyx_t_1);
      if (likely(__pyx_t_8)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
        __Pyx_INCREF(__pyx_t_8);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_1, function);
      }
    }
    __pyx_t_6 = (__pyx_t_8) ? __Pyx_PyObject_Call2Args(__pyx_t_1, __pyx_t_8, __pyx_t_4) : __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_4);
    __Pyx_XDECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 303, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = __Pyx_PyFloat_AddCObj(__pyx_float_1_0, __pyx_t_6, 1.0, 0, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 303, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = __Pyx_PyNumber_Divide(__pyx_t_3, __pyx_t_1); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 303, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_12 = __pyx_PyFloat_AsDouble(__pyx_t_6); if (unlikely((__pyx_t_12 == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 303, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_v_factor = __pyx_t_12;

    /* "fa2/fa2util.py":304
 *         swinging = n.mass * sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))
 *         factor = speed / (1.0 + sqrt(speed * swinging))
 *         n.x = n.x + (n.dx * factor)             # <<<<<<<<<<<<<<
 *         n.y = n.y + (n.dy * factor)
 * 
 */
    __pyx_v_n->x = (__pyx_v_n->x + (__pyx_v_n->dx * __pyx_v_factor));

    /* "fa2/fa2util.py":305
 *         factor = speed / (1.0 + sqrt(speed * swinging))
 *         n.x = n.x + (n.dx * factor)
 *         n.y = n.y + (n.dy * factor)             # <<<<<<<<<<<<<<
 * 
 *     values = {}
 */
    __pyx_v_n->y = (__pyx_v_n->y + (__pyx_v_n->dy * __pyx_v_factor));

    /* "fa2/fa2util.py":301
 *     # Need to add a case if adjustSizes ("prevent overlap") is
 *     # implemented.
 *     for n in nodes:             # <<<<<<<<<<<<<<
 *         swinging = n.mass * sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))
 *         factor = speed / (1.0 + sqrt(speed * swinging))
 */
  }
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "fa2/fa2util.py":307
 *         n.y = n.y + (n.dy * factor)
 * 
 *     values = {}             # <<<<<<<<<<<<<<
 *     values['speed'] = speed
 *     values['speedEfficiency'] = speedEfficiency
 */
  __pyx_t_5 = __Pyx_PyDict_NewPresized(0); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 307, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_v_values = ((PyObject*)__pyx_t_5);
  __pyx_t_5 = 0;

  /* "fa2/fa2util.py":308
 * 
 *     values = {}
 *     values['speed'] = speed             # <<<<<<<<<<<<<<
 *     values['speedEfficiency'] = speedEfficiency
 * 
 */
  __pyx_t_5 = PyFloat_FromDouble(__pyx_v_speed); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 308, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (unlikely(PyDict_SetItem(__pyx_v_values, __pyx_n_s_speed, __pyx_t_5) < 0)) __PYX_ERR(2, 308, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "fa2/fa2util.py":309
 *     values = {}
 *     values['speed'] = speed
 *     values['speedEfficiency'] = speedEfficiency             # <<<<<<<<<<<<<<
 * 
 *     return values
 */
  __pyx_t_5 = PyFloat_FromDouble(__pyx_v_speedEfficiency); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 309, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (unlikely(PyDict_SetItem(__pyx_v_values, __pyx_n_s_speedEfficiency, __pyx_t_5) < 0)) __PYX_ERR(2, 309, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "fa2/fa2util.py":311
 *     values['speedEfficiency'] = speedEfficiency
 * 
 *     return values             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_values);
  __pyx_r = __pyx_v_values;
  goto __pyx_L0;

  /* "fa2/fa2util.py":253
 * 
 * # Adjust speed and apply forces step
 * def adjustSpeedAndApplyForces(nodes, speed, speedEfficiency, jitterTolerance):             # <<<<<<<<<<<<<<
 *     # Auto adjust speed.
 *     totalSwinging = 0.0  # How much irregular movement
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("fa2.fa2util.adjustSpeedAndApplyForces", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_n);
  __Pyx_XDECREF(__pyx_v_values);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_9adjustSpeedAndApplyForces(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_9adjustSpeedAndApplyForces = {"adjustSpeedAndApplyForces", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_3fa2_7fa2util_9adjustSpeedAndApplyForces, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_9adjustSpeedAndApplyForces(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_nodes = 0;
  double __pyx_v_speed;
  double __pyx_v_speedEfficiency;
  double __pyx_v_jitterTolerance;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("adjustSpeedAndApplyForces (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_nodes,&__pyx_n_s_speed,&__pyx_n_s_speedEfficiency,&__pyx_n_s_jitterTolerance,0};
    PyObject* values[4] = {0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_nodes)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_speed)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("adjustSpeedAndApplyForces", 1, 4, 4, 1); __PYX_ERR(2, 253, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (likely((values[2] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_speedEfficiency)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("adjustSpeedAndApplyForces", 1, 4, 4, 2); __PYX_ERR(2, 253, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  3:
        if (likely((values[3] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_jitterTolerance)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("adjustSpeedAndApplyForces", 1, 4, 4, 3); __PYX_ERR(2, 253, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "adjustSpeedAndApplyForces") < 0)) __PYX_ERR(2, 253, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 4) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
      values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
    }
    __pyx_v_nodes = ((PyObject*)values[0]);
    __pyx_v_speed = __pyx_PyFloat_AsDouble(values[1]); if (unlikely((__pyx_v_speed == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 253, __pyx_L3_error)
    __pyx_v_speedEfficiency = __pyx_PyFloat_AsDouble(values[2]); if (unlikely((__pyx_v_speedEfficiency == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 253, __pyx_L3_error)
    __pyx_v_jitterTolerance = __pyx_PyFloat_AsDouble(values[3]); if (unlikely((__pyx_v_jitterTolerance == (double)-1) && PyErr_Occurred())) __PYX_ERR(2, 253, __pyx_L3_error)
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("adjustSpeedAndApplyForces", 1, 4, 4, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(2, 253, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("fa2.fa2util.adjustSpeedAndApplyForces", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_nodes), (&PyList_Type), 1, "nodes", 1))) __PYX_ERR(2, 253, __pyx_L1_error)
  __pyx_r = __pyx_pf_3fa2_7fa2util_8adjustSpeedAndApplyForces(__pyx_self, __pyx_v_nodes, __pyx_v_speed, __pyx_v_speedEfficiency, __pyx_v_jitterTolerance);

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_8adjustSpeedAndApplyForces(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_nodes, double __pyx_v_speed, double __pyx_v_speedEfficiency, double __pyx_v_jitterTolerance) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("adjustSpeedAndApplyForces", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __pyx_f_3fa2_7fa2util_adjustSpeedAndApplyForces(__pyx_v_nodes, __pyx_v_speed, __pyx_v_speedEfficiency, __pyx_v_jitterTolerance, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 253, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("fa2.fa2util.adjustSpeedAndApplyForces", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "(tree fragment)":1
 * def __pyx_unpickle_Node(__pyx_type, long __pyx_checksum, __pyx_state):             # <<<<<<<<<<<<<<
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_11__pyx_unpickle_Node(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_11__pyx_unpickle_Node = {"__pyx_unpickle_Node", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_3fa2_7fa2util_11__pyx_unpickle_Node, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_11__pyx_unpickle_Node(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v___pyx_type = 0;
  long __pyx_v___pyx_checksum;
  PyObject *__pyx_v___pyx_state = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__pyx_unpickle_Node (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pyx_type,&__pyx_n_s_pyx_checksum,&__pyx_n_s_pyx_state,0};
    PyObject* values[3] = {0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_pyx_type)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_pyx_checksum)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__pyx_unpickle_Node", 1, 3, 3, 1); __PYX_ERR(1, 1, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (likely((values[2] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_pyx_state)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__pyx_unpickle_Node", 1, 3, 3, 2); __PYX_ERR(1, 1, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__pyx_unpickle_Node") < 0)) __PYX_ERR(1, 1, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 3) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
    }
    __pyx_v___pyx_type = values[0];
    __pyx_v___pyx_checksum = __Pyx_PyInt_As_long(values[1]); if (unlikely((__pyx_v___pyx_checksum == (long)-1) && PyErr_Occurred())) __PYX_ERR(1, 1, __pyx_L3_error)
    __pyx_v___pyx_state = values[2];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__pyx_unpickle_Node", 1, 3, 3, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(1, 1, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("fa2.fa2util.__pyx_unpickle_Node", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3fa2_7fa2util_10__pyx_unpickle_Node(__pyx_self, __pyx_v___pyx_type, __pyx_v___pyx_checksum, __pyx_v___pyx_state);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_10__pyx_unpickle_Node(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v___pyx_type, long __pyx_v___pyx_checksum, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_v___pyx_PickleError = 0;
  PyObject *__pyx_v___pyx_result = 0;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__pyx_unpickle_Node", 0);

  /* "(tree fragment)":4
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 *     if __pyx_checksum != 0x2f233dd:             # <<<<<<<<<<<<<<
 *         from pickle import PickleError as __pyx_PickleError
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x2f233dd = (dx, dy, mass, old_dx, old_dy, x, y))" % __pyx_checksum)
 */
  __pyx_t_1 = ((__pyx_v___pyx_checksum != 0x2f233dd) != 0);
  if (__pyx_t_1) {

    /* "(tree fragment)":5
 *     cdef object __pyx_result
 *     if __pyx_checksum != 0x2f233dd:
 *         from pickle import PickleError as __pyx_PickleError             # <<<<<<<<<<<<<<
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x2f233dd = (dx, dy, mass, old_dx, old_dy, x, y))" % __pyx_checksum)
 *     __pyx_result = Node.__new__(__pyx_type)
 */
    __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 5, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_n_s_PickleError);
    __Pyx_GIVEREF(__pyx_n_s_PickleError);
    PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_PickleError);
    __pyx_t_3 = __Pyx_Import(__pyx_n_s_pickle, __pyx_t_2, -1); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 5, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_3, __pyx_n_s_PickleError); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 5, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_t_2);
    __pyx_v___pyx_PickleError = __pyx_t_2;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "(tree fragment)":6
 *     if __pyx_checksum != 0x2f233dd:
 *         from pickle import PickleError as __pyx_PickleError
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x2f233dd = (dx, dy, mass, old_dx, old_dy, x, y))" % __pyx_checksum)             # <<<<<<<<<<<<<<
 *     __pyx_result = Node.__new__(__pyx_type)
 *     if __pyx_state is not None:
 */
    __pyx_t_2 = __Pyx_PyInt_From_long(__pyx_v___pyx_checksum); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 6, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_4 = __Pyx_PyString_Format(__pyx_kp_s_Incompatible_checksums_s_vs_0x2f, __pyx_t_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 6, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_INCREF(__pyx_v___pyx_PickleError);
    __pyx_t_2 = __pyx_v___pyx_PickleError; __pyx_t_5 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    __pyx_t_3 = (__pyx_t_5) ? __Pyx_PyObject_Call2Args(__pyx_t_2, __pyx_t_5, __pyx_t_4) : __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_4);
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 6, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(1, 6, __pyx_L1_error)

    /* "(tree fragment)":4
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 *     if __pyx_checksum != 0x2f233dd:             # <<<<<<<<<<<<<<
 *         from pickle import PickleError as __pyx_PickleError
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x2f233dd = (dx, dy, mass, old_dx, old_dy, x, y))" % __pyx_checksum)
 */
  }

  /* "(tree fragment)":7
 *         from pickle import PickleError as __pyx_PickleError
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x2f233dd = (dx, dy, mass, old_dx, old_dy, x, y))" % __pyx_checksum)
 *     __pyx_result = Node.__new__(__pyx_type)             # <<<<<<<<<<<<<<
 *     if __pyx_state is not None:
 *         __pyx_unpickle_Node__set_state(<Node> __pyx_result, __pyx_state)
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_ptype_3fa2_7fa2util_Node), __pyx_n_s_new); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  __pyx_t_3 = (__pyx_t_4) ? __Pyx_PyObject_Call2Args(__pyx_t_2, __pyx_t_4, __pyx_v___pyx_type) : __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_v___pyx_type);
  __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v___pyx_result = __pyx_t_3;
  __pyx_t_3 = 0;

  /* "(tree fragment)":8
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x2f233dd = (dx, dy, mass, old_dx, old_dy, x, y))" % __pyx_checksum)
 *     __pyx_result = Node.__new__(__pyx_type)
 *     if __pyx_state is not None:             # <<<<<<<<<<<<<<
 *         __pyx_unpickle_Node__set_state(<Node> __pyx_result, __pyx_state)
 *     return __pyx_result
 */
  __pyx_t_1 = (__pyx_v___pyx_state != Py_None);
  __pyx_t_6 = (__pyx_t_1 != 0);
  if (__pyx_t_6) {

    /* "(tree fragment)":9
 *     __pyx_result = Node.__new__(__pyx_type)
 *     if __pyx_state is not None:
 *         __pyx_unpickle_Node__set_state(<Node> __pyx_result, __pyx_state)             # <<<<<<<<<<<<<<
 *     return __pyx_result
 * cdef __pyx_unpickle_Node__set_state(Node __pyx_result, tuple __pyx_state):
 */
    if (!(likely(PyTuple_CheckExact(__pyx_v___pyx_state))||((__pyx_v___pyx_state) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "tuple", Py_TYPE(__pyx_v___pyx_state)->tp_name), 0))) __PYX_ERR(1, 9, __pyx_L1_error)
    __pyx_t_3 = __pyx_f_3fa2_7fa2util___pyx_unpickle_Node__set_state(((struct __pyx_obj_3fa2_7fa2util_Node *)__pyx_v___pyx_result), ((PyObject*)__pyx_v___pyx_state)); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 9, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "(tree fragment)":8
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x2f233dd = (dx, dy, mass, old_dx, old_dy, x, y))" % __pyx_checksum)
 *     __pyx_result = Node.__new__(__pyx_type)
 *     if __pyx_state is not None:             # <<<<<<<<<<<<<<
 *         __pyx_unpickle_Node__set_state(<Node> __pyx_result, __pyx_state)
 *     return __pyx_result
 */
  }

  /* "(tree fragment)":10
 *     if __pyx_state is not None:
 *         __pyx_unpickle_Node__set_state(<Node> __pyx_result, __pyx_state)
 *     return __pyx_result             # <<<<<<<<<<<<<<
 * cdef __pyx_unpickle_Node__set_state(Node __pyx_result, tuple __pyx_state):
 *     __pyx_result.dx = __pyx_state[0]; __pyx_result.dy = __pyx_state[1]; __pyx_result.mass = __pyx_state[2]; __pyx_result.old_dx = __pyx_state[3]; __pyx_result.old_dy = __pyx_state[4]; __pyx_result.x = __pyx_state[5]; __pyx_result.y = __pyx_state[6]
 */
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v___pyx_result);
  __pyx_r = __pyx_v___pyx_result;
  goto __pyx_L0;

  /* "(tree fragment)":1
 * def __pyx_unpickle_Node(__pyx_type, long __pyx_checksum, __pyx_state):             # <<<<<<<<<<<<<<
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("fa2.fa2util.__pyx_unpickle_Node", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v___pyx_PickleError);
  __Pyx_XDECREF(__pyx_v___pyx_result);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "(tree fragment)":11
 *         __pyx_unpickle_Node__set_state(<Node> __pyx_result, __pyx_state)
 *     return __pyx_result
 * cdef __pyx_unpickle_Node__set_state(Node __pyx_result, tuple __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_result.dx = __pyx_state[0]; __pyx_result.dy = __pyx_state[1]; __pyx_result.mass = __pyx_state[2]; __pyx_result.old_dx = __pyx_state[3]; __pyx_result.old_dy = __pyx_state[4]; __pyx_result.x = __pyx_state[5]; __pyx_result.y = __pyx_state[6]
 *     if len(__pyx_state) > 7 and hasattr(__pyx_result, '__dict__'):
 */

static PyObject *__pyx_f_3fa2_7fa2util___pyx_unpickle_Node__set_state(struct __pyx_obj_3fa2_7fa2util_Node *__pyx_v___pyx_result, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  double __pyx_t_2;
  int __pyx_t_3;
  Py_ssize_t __pyx_t_4;
  int __pyx_t_5;
  int __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__pyx_unpickle_Node__set_state", 0);

  /* "(tree fragment)":12
 *     return __pyx_result
 * cdef __pyx_unpickle_Node__set_state(Node __pyx_result, tuple __pyx_state):
 *     __pyx_result.dx = __pyx_state[0]; __pyx_result.dy = __pyx_state[1]; __pyx_result.mass = __pyx_state[2]; __pyx_result.old_dx = __pyx_state[3]; __pyx_result.old_dy = __pyx_state[4]; __pyx_result.x = __pyx_state[5]; __pyx_result.y = __pyx_state[6]             # <<<<<<<<<<<<<<
 *     if len(__pyx_state) > 7 and hasattr(__pyx_result, '__dict__'):
 *         __pyx_result.__dict__.update(__pyx_state[7])
 */
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_2 == (double)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->dx = __pyx_t_2;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_2 == (double)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->dy = __pyx_t_2;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 2, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_2 == (double)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->mass = __pyx_t_2;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 3, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_2 == (double)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->old_dx = __pyx_t_2;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 4, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_2 == (double)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->old_dy = __pyx_t_2;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 5, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_2 == (double)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->x = __pyx_t_2;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 6, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_2 == (double)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->y = __pyx_t_2;

  /* "(tree fragment)":13
 * cdef __pyx_unpickle_Node__set_state(Node __pyx_result, tuple __pyx_state):
 *     __pyx_result.dx = __pyx_state[0]; __pyx_result.dy = __pyx_state[1]; __pyx_result.mass = __pyx_state[2]; __pyx_result.old_dx = __pyx_state[3]; __pyx_result.old_dy = __pyx_state[4]; __pyx_result.x = __pyx_state[5]; __pyx_result.y = __pyx_state[6]
 *     if len(__pyx_state) > 7 and hasattr(__pyx_result, '__dict__'):             # <<<<<<<<<<<<<<
 *         __pyx_result.__dict__.update(__pyx_state[7])
 */
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    __PYX_ERR(1, 13, __pyx_L1_error)
  }
  __pyx_t_4 = PyTuple_GET_SIZE(__pyx_v___pyx_state); if (unlikely(__pyx_t_4 == ((Py_ssize_t)-1))) __PYX_ERR(1, 13, __pyx_L1_error)
  __pyx_t_5 = ((__pyx_t_4 > 7) != 0);
  if (__pyx_t_5) {
  } else {
    __pyx_t_3 = __pyx_t_5;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_5 = __Pyx_HasAttr(((PyObject *)__pyx_v___pyx_result), __pyx_n_s_dict); if (unlikely(__pyx_t_5 == ((int)-1))) __PYX_ERR(1, 13, __pyx_L1_error)
  __pyx_t_6 = (__pyx_t_5 != 0);
  __pyx_t_3 = __pyx_t_6;
  __pyx_L4_bool_binop_done:;
  if (__pyx_t_3) {

    /* "(tree fragment)":14
 *     __pyx_result.dx = __pyx_state[0]; __pyx_result.dy = __pyx_state[1]; __pyx_result.mass = __pyx_state[2]; __pyx_result.old_dx = __pyx_state[3]; __pyx_result.old_dy = __pyx_state[4]; __pyx_result.x = __pyx_state[5]; __pyx_result.y = __pyx_state[6]
 *     if len(__pyx_state) > 7 and hasattr(__pyx_result, '__dict__'):
 *         __pyx_result.__dict__.update(__pyx_state[7])             # <<<<<<<<<<<<<<
 */
    __pyx_t_7 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v___pyx_result), __pyx_n_s_dict); if (unlikely(!__pyx_t_7)) __PYX_ERR(1, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_update); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    if (unlikely(__pyx_v___pyx_state == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      __PYX_ERR(1, 14, __pyx_L1_error)
    }
    __pyx_t_7 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 7, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_7)) __PYX_ERR(1, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_9 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_8))) {
      __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_8);
      if (likely(__pyx_t_9)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_8);
        __Pyx_INCREF(__pyx_t_9);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_8, function);
      }
    }
    __pyx_t_1 = (__pyx_t_9) ? __Pyx_PyObject_Call2Args(__pyx_t_8, __pyx_t_9, __pyx_t_7) : __Pyx_PyObject_CallOneArg(__pyx_t_8, __pyx_t_7);
    __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "(tree fragment)":13
 * cdef __pyx_unpickle_Node__set_state(Node __pyx_result, tuple __pyx_state):
 *     __pyx_result.dx = __pyx_state[0]; __pyx_result.dy = __pyx_state[1]; __pyx_result.mass = __pyx_state[2]; __pyx_result.old_dx = __pyx_state[3]; __pyx_result.old_dy = __pyx_state[4]; __pyx_result.x = __pyx_state[5]; __pyx_result.y = __pyx_state[6]
 *     if len(__pyx_state) > 7 and hasattr(__pyx_result, '__dict__'):             # <<<<<<<<<<<<<<
 *         __pyx_result.__dict__.update(__pyx_state[7])
 */
  }

  /* "(tree fragment)":11
 *         __pyx_unpickle_Node__set_state(<Node> __pyx_result, __pyx_state)
 *     return __pyx_result
 * cdef __pyx_unpickle_Node__set_state(Node __pyx_result, tuple __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_result.dx = __pyx_state[0]; __pyx_result.dy = __pyx_state[1]; __pyx_result.mass = __pyx_state[2]; __pyx_result.old_dx = __pyx_state[3]; __pyx_result.old_dy = __pyx_state[4]; __pyx_result.x = __pyx_state[5]; __pyx_result.y = __pyx_state[6]
 *     if len(__pyx_state) > 7 and hasattr(__pyx_result, '__dict__'):
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("fa2.fa2util.__pyx_unpickle_Node__set_state", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "(tree fragment)":1
 * def __pyx_unpickle_Edge(__pyx_type, long __pyx_checksum, __pyx_state):             # <<<<<<<<<<<<<<
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_13__pyx_unpickle_Edge(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_13__pyx_unpickle_Edge = {"__pyx_unpickle_Edge", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_3fa2_7fa2util_13__pyx_unpickle_Edge, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_13__pyx_unpickle_Edge(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v___pyx_type = 0;
  long __pyx_v___pyx_checksum;
  PyObject *__pyx_v___pyx_state = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__pyx_unpickle_Edge (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pyx_type,&__pyx_n_s_pyx_checksum,&__pyx_n_s_pyx_state,0};
    PyObject* values[3] = {0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_pyx_type)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_pyx_checksum)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__pyx_unpickle_Edge", 1, 3, 3, 1); __PYX_ERR(1, 1, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (likely((values[2] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_pyx_state)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__pyx_unpickle_Edge", 1, 3, 3, 2); __PYX_ERR(1, 1, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__pyx_unpickle_Edge") < 0)) __PYX_ERR(1, 1, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 3) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
    }
    __pyx_v___pyx_type = values[0];
    __pyx_v___pyx_checksum = __Pyx_PyInt_As_long(values[1]); if (unlikely((__pyx_v___pyx_checksum == (long)-1) && PyErr_Occurred())) __PYX_ERR(1, 1, __pyx_L3_error)
    __pyx_v___pyx_state = values[2];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__pyx_unpickle_Edge", 1, 3, 3, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(1, 1, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("fa2.fa2util.__pyx_unpickle_Edge", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3fa2_7fa2util_12__pyx_unpickle_Edge(__pyx_self, __pyx_v___pyx_type, __pyx_v___pyx_checksum, __pyx_v___pyx_state);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_12__pyx_unpickle_Edge(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v___pyx_type, long __pyx_v___pyx_checksum, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_v___pyx_PickleError = 0;
  PyObject *__pyx_v___pyx_result = 0;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__pyx_unpickle_Edge", 0);

  /* "(tree fragment)":4
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 *     if __pyx_checksum != 0xb469544:             # <<<<<<<<<<<<<<
 *         from pickle import PickleError as __pyx_PickleError
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0xb469544 = (node1, node2, weight))" % __pyx_checksum)
 */
  __pyx_t_1 = ((__pyx_v___pyx_checksum != 0xb469544) != 0);
  if (__pyx_t_1) {

    /* "(tree fragment)":5
 *     cdef object __pyx_result
 *     if __pyx_checksum != 0xb469544:
 *         from pickle import PickleError as __pyx_PickleError             # <<<<<<<<<<<<<<
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0xb469544 = (node1, node2, weight))" % __pyx_checksum)
 *     __pyx_result = Edge.__new__(__pyx_type)
 */
    __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 5, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_n_s_PickleError);
    __Pyx_GIVEREF(__pyx_n_s_PickleError);
    PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_PickleError);
    __pyx_t_3 = __Pyx_Import(__pyx_n_s_pickle, __pyx_t_2, -1); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 5, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_3, __pyx_n_s_PickleError); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 5, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_t_2);
    __pyx_v___pyx_PickleError = __pyx_t_2;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "(tree fragment)":6
 *     if __pyx_checksum != 0xb469544:
 *         from pickle import PickleError as __pyx_PickleError
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0xb469544 = (node1, node2, weight))" % __pyx_checksum)             # <<<<<<<<<<<<<<
 *     __pyx_result = Edge.__new__(__pyx_type)
 *     if __pyx_state is not None:
 */
    __pyx_t_2 = __Pyx_PyInt_From_long(__pyx_v___pyx_checksum); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 6, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_4 = __Pyx_PyString_Format(__pyx_kp_s_Incompatible_checksums_s_vs_0xb4, __pyx_t_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 6, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_INCREF(__pyx_v___pyx_PickleError);
    __pyx_t_2 = __pyx_v___pyx_PickleError; __pyx_t_5 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    __pyx_t_3 = (__pyx_t_5) ? __Pyx_PyObject_Call2Args(__pyx_t_2, __pyx_t_5, __pyx_t_4) : __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_4);
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 6, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(1, 6, __pyx_L1_error)

    /* "(tree fragment)":4
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 *     if __pyx_checksum != 0xb469544:             # <<<<<<<<<<<<<<
 *         from pickle import PickleError as __pyx_PickleError
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0xb469544 = (node1, node2, weight))" % __pyx_checksum)
 */
  }

  /* "(tree fragment)":7
 *         from pickle import PickleError as __pyx_PickleError
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0xb469544 = (node1, node2, weight))" % __pyx_checksum)
 *     __pyx_result = Edge.__new__(__pyx_type)             # <<<<<<<<<<<<<<
 *     if __pyx_state is not None:
 *         __pyx_unpickle_Edge__set_state(<Edge> __pyx_result, __pyx_state)
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_ptype_3fa2_7fa2util_Edge), __pyx_n_s_new); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  __pyx_t_3 = (__pyx_t_4) ? __Pyx_PyObject_Call2Args(__pyx_t_2, __pyx_t_4, __pyx_v___pyx_type) : __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_v___pyx_type);
  __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v___pyx_result = __pyx_t_3;
  __pyx_t_3 = 0;

  /* "(tree fragment)":8
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0xb469544 = (node1, node2, weight))" % __pyx_checksum)
 *     __pyx_result = Edge.__new__(__pyx_type)
 *     if __pyx_state is not None:             # <<<<<<<<<<<<<<
 *         __pyx_unpickle_Edge__set_state(<Edge> __pyx_result, __pyx_state)
 *     return __pyx_result
 */
  __pyx_t_1 = (__pyx_v___pyx_state != Py_None);
  __pyx_t_6 = (__pyx_t_1 != 0);
  if (__pyx_t_6) {

    /* "(tree fragment)":9
 *     __pyx_result = Edge.__new__(__pyx_type)
 *     if __pyx_state is not None:
 *         __pyx_unpickle_Edge__set_state(<Edge> __pyx_result, __pyx_state)             # <<<<<<<<<<<<<<
 *     return __pyx_result
 * cdef __pyx_unpickle_Edge__set_state(Edge __pyx_result, tuple __pyx_state):
 */
    if (!(likely(PyTuple_CheckExact(__pyx_v___pyx_state))||((__pyx_v___pyx_state) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "tuple", Py_TYPE(__pyx_v___pyx_state)->tp_name), 0))) __PYX_ERR(1, 9, __pyx_L1_error)
    __pyx_t_3 = __pyx_f_3fa2_7fa2util___pyx_unpickle_Edge__set_state(((struct __pyx_obj_3fa2_7fa2util_Edge *)__pyx_v___pyx_result), ((PyObject*)__pyx_v___pyx_state)); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 9, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "(tree fragment)":8
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0xb469544 = (node1, node2, weight))" % __pyx_checksum)
 *     __pyx_result = Edge.__new__(__pyx_type)
 *     if __pyx_state is not None:             # <<<<<<<<<<<<<<
 *         __pyx_unpickle_Edge__set_state(<Edge> __pyx_result, __pyx_state)
 *     return __pyx_result
 */
  }

  /* "(tree fragment)":10
 *     if __pyx_state is not None:
 *         __pyx_unpickle_Edge__set_state(<Edge> __pyx_result, __pyx_state)
 *     return __pyx_result             # <<<<<<<<<<<<<<
 * cdef __pyx_unpickle_Edge__set_state(Edge __pyx_result, tuple __pyx_state):
 *     __pyx_result.node1 = __pyx_state[0]; __pyx_result.node2 = __pyx_state[1]; __pyx_result.weight = __pyx_state[2]
 */
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v___pyx_result);
  __pyx_r = __pyx_v___pyx_result;
  goto __pyx_L0;

  /* "(tree fragment)":1
 * def __pyx_unpickle_Edge(__pyx_type, long __pyx_checksum, __pyx_state):             # <<<<<<<<<<<<<<
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("fa2.fa2util.__pyx_unpickle_Edge", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v___pyx_PickleError);
  __Pyx_XDECREF(__pyx_v___pyx_result);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "(tree fragment)":11
 *         __pyx_unpickle_Edge__set_state(<Edge> __pyx_result, __pyx_state)
 *     return __pyx_result
 * cdef __pyx_unpickle_Edge__set_state(Edge __pyx_result, tuple __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_result.node1 = __pyx_state[0]; __pyx_result.node2 = __pyx_state[1]; __pyx_result.weight = __pyx_state[2]
 *     if len(__pyx_state) > 3 and hasattr(__pyx_result, '__dict__'):
 */

static PyObject *__pyx_f_3fa2_7fa2util___pyx_unpickle_Edge__set_state(struct __pyx_obj_3fa2_7fa2util_Edge *__pyx_v___pyx_result, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  double __pyx_t_3;
  int __pyx_t_4;
  Py_ssize_t __pyx_t_5;
  int __pyx_t_6;
  int __pyx_t_7;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__pyx_unpickle_Edge__set_state", 0);

  /* "(tree fragment)":12
 *     return __pyx_result
 * cdef __pyx_unpickle_Edge__set_state(Edge __pyx_result, tuple __pyx_state):
 *     __pyx_result.node1 = __pyx_state[0]; __pyx_result.node2 = __pyx_state[1]; __pyx_result.weight = __pyx_state[2]             # <<<<<<<<<<<<<<
 *     if len(__pyx_state) > 3 and hasattr(__pyx_result, '__dict__'):
 *         __pyx_result.__dict__.update(__pyx_state[3])
 */
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyInt_As_int(__pyx_t_1); if (unlikely((__pyx_t_2 == (int)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->node1 = __pyx_t_2;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyInt_As_int(__pyx_t_1); if (unlikely((__pyx_t_2 == (int)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->node2 = __pyx_t_2;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 2, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_3 == (double)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->weight = __pyx_t_3;

  /* "(tree fragment)":13
 * cdef __pyx_unpickle_Edge__set_state(Edge __pyx_result, tuple __pyx_state):
 *     __pyx_result.node1 = __pyx_state[0]; __pyx_result.node2 = __pyx_state[1]; __pyx_result.weight = __pyx_state[2]
 *     if len(__pyx_state) > 3 and hasattr(__pyx_result, '__dict__'):             # <<<<<<<<<<<<<<
 *         __pyx_result.__dict__.update(__pyx_state[3])
 */
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    __PYX_ERR(1, 13, __pyx_L1_error)
  }
  __pyx_t_5 = PyTuple_GET_SIZE(__pyx_v___pyx_state); if (unlikely(__pyx_t_5 == ((Py_ssize_t)-1))) __PYX_ERR(1, 13, __pyx_L1_error)
  __pyx_t_6 = ((__pyx_t_5 > 3) != 0);
  if (__pyx_t_6) {
  } else {
    __pyx_t_4 = __pyx_t_6;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_6 = __Pyx_HasAttr(((PyObject *)__pyx_v___pyx_result), __pyx_n_s_dict); if (unlikely(__pyx_t_6 == ((int)-1))) __PYX_ERR(1, 13, __pyx_L1_error)
  __pyx_t_7 = (__pyx_t_6 != 0);
  __pyx_t_4 = __pyx_t_7;
  __pyx_L4_bool_binop_done:;
  if (__pyx_t_4) {

    /* "(tree fragment)":14
 *     __pyx_result.node1 = __pyx_state[0]; __pyx_result.node2 = __pyx_state[1]; __pyx_result.weight = __pyx_state[2]
 *     if len(__pyx_state) > 3 and hasattr(__pyx_result, '__dict__'):
 *         __pyx_result.__dict__.update(__pyx_state[3])             # <<<<<<<<<<<<<<
 */
    __pyx_t_8 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v___pyx_result), __pyx_n_s_dict); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_update); if (unlikely(!__pyx_t_9)) __PYX_ERR(1, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    if (unlikely(__pyx_v___pyx_state == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      __PYX_ERR(1, 14, __pyx_L1_error)
    }
    __pyx_t_8 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 3, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __pyx_t_10 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_9))) {
      __pyx_t_10 = PyMethod_GET_SELF(__pyx_t_9);
      if (likely(__pyx_t_10)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
        __Pyx_INCREF(__pyx_t_10);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_9, function);
      }
    }
    __pyx_t_1 = (__pyx_t_10) ? __Pyx_PyObject_Call2Args(__pyx_t_9, __pyx_t_10, __pyx_t_8) : __Pyx_PyObject_CallOneArg(__pyx_t_9, __pyx_t_8);
    __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "(tree fragment)":13
 * cdef __pyx_unpickle_Edge__set_state(Edge __pyx_result, tuple __pyx_state):
 *     __pyx_result.node1 = __pyx_state[0]; __pyx_result.node2 = __pyx_state[1]; __pyx_result.weight = __pyx_state[2]
 *     if len(__pyx_state) > 3 and hasattr(__pyx_result, '__dict__'):             # <<<<<<<<<<<<<<
 *         __pyx_result.__dict__.update(__pyx_state[3])
 */
  }

  /* "(tree fragment)":11
 *         __pyx_unpickle_Edge__set_state(<Edge> __pyx_result, __pyx_state)
 *     return __pyx_result
 * cdef __pyx_unpickle_Edge__set_state(Edge __pyx_result, tuple __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_result.node1 = __pyx_state[0]; __pyx_result.node2 = __pyx_state[1]; __pyx_result.weight = __pyx_state[2]
 *     if len(__pyx_state) > 3 and hasattr(__pyx_result, '__dict__'):
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_AddTraceback("fa2.fa2util.__pyx_unpickle_Edge__set_state", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "(tree fragment)":1
 * def __pyx_unpickle_Region(__pyx_type, long __pyx_checksum, __pyx_state):             # <<<<<<<<<<<<<<
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 */

/* Python wrapper */
static PyObject *__pyx_pw_3fa2_7fa2util_15__pyx_unpickle_Region(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3fa2_7fa2util_15__pyx_unpickle_Region = {"__pyx_unpickle_Region", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_3fa2_7fa2util_15__pyx_unpickle_Region, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3fa2_7fa2util_15__pyx_unpickle_Region(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v___pyx_type = 0;
  long __pyx_v___pyx_checksum;
  PyObject *__pyx_v___pyx_state = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__pyx_unpickle_Region (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pyx_type,&__pyx_n_s_pyx_checksum,&__pyx_n_s_pyx_state,0};
    PyObject* values[3] = {0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_pyx_type)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_pyx_checksum)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__pyx_unpickle_Region", 1, 3, 3, 1); __PYX_ERR(1, 1, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (likely((values[2] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_pyx_state)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__pyx_unpickle_Region", 1, 3, 3, 2); __PYX_ERR(1, 1, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__pyx_unpickle_Region") < 0)) __PYX_ERR(1, 1, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 3) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
    }
    __pyx_v___pyx_type = values[0];
    __pyx_v___pyx_checksum = __Pyx_PyInt_As_long(values[1]); if (unlikely((__pyx_v___pyx_checksum == (long)-1) && PyErr_Occurred())) __PYX_ERR(1, 1, __pyx_L3_error)
    __pyx_v___pyx_state = values[2];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__pyx_unpickle_Region", 1, 3, 3, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(1, 1, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("fa2.fa2util.__pyx_unpickle_Region", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3fa2_7fa2util_14__pyx_unpickle_Region(__pyx_self, __pyx_v___pyx_type, __pyx_v___pyx_checksum, __pyx_v___pyx_state);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3fa2_7fa2util_14__pyx_unpickle_Region(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v___pyx_type, long __pyx_v___pyx_checksum, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_v___pyx_PickleError = 0;
  PyObject *__pyx_v___pyx_result = 0;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__pyx_unpickle_Region", 0);

  /* "(tree fragment)":4
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 *     if __pyx_checksum != 0x66ef4c7:             # <<<<<<<<<<<<<<
 *         from pickle import PickleError as __pyx_PickleError
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x66ef4c7 = (mass, massCenterX, massCenterY, nodes, size, subregions))" % __pyx_checksum)
 */
  __pyx_t_1 = ((__pyx_v___pyx_checksum != 0x66ef4c7) != 0);
  if (__pyx_t_1) {

    /* "(tree fragment)":5
 *     cdef object __pyx_result
 *     if __pyx_checksum != 0x66ef4c7:
 *         from pickle import PickleError as __pyx_PickleError             # <<<<<<<<<<<<<<
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x66ef4c7 = (mass, massCenterX, massCenterY, nodes, size, subregions))" % __pyx_checksum)
 *     __pyx_result = Region.__new__(__pyx_type)
 */
    __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 5, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_n_s_PickleError);
    __Pyx_GIVEREF(__pyx_n_s_PickleError);
    PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_PickleError);
    __pyx_t_3 = __Pyx_Import(__pyx_n_s_pickle, __pyx_t_2, -1); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 5, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_3, __pyx_n_s_PickleError); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 5, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_t_2);
    __pyx_v___pyx_PickleError = __pyx_t_2;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "(tree fragment)":6
 *     if __pyx_checksum != 0x66ef4c7:
 *         from pickle import PickleError as __pyx_PickleError
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x66ef4c7 = (mass, massCenterX, massCenterY, nodes, size, subregions))" % __pyx_checksum)             # <<<<<<<<<<<<<<
 *     __pyx_result = Region.__new__(__pyx_type)
 *     if __pyx_state is not None:
 */
    __pyx_t_2 = __Pyx_PyInt_From_long(__pyx_v___pyx_checksum); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 6, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_4 = __Pyx_PyString_Format(__pyx_kp_s_Incompatible_checksums_s_vs_0x66, __pyx_t_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 6, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_INCREF(__pyx_v___pyx_PickleError);
    __pyx_t_2 = __pyx_v___pyx_PickleError; __pyx_t_5 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    __pyx_t_3 = (__pyx_t_5) ? __Pyx_PyObject_Call2Args(__pyx_t_2, __pyx_t_5, __pyx_t_4) : __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_4);
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 6, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(1, 6, __pyx_L1_error)

    /* "(tree fragment)":4
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 *     if __pyx_checksum != 0x66ef4c7:             # <<<<<<<<<<<<<<
 *         from pickle import PickleError as __pyx_PickleError
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x66ef4c7 = (mass, massCenterX, massCenterY, nodes, size, subregions))" % __pyx_checksum)
 */
  }

  /* "(tree fragment)":7
 *         from pickle import PickleError as __pyx_PickleError
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x66ef4c7 = (mass, massCenterX, massCenterY, nodes, size, subregions))" % __pyx_checksum)
 *     __pyx_result = Region.__new__(__pyx_type)             # <<<<<<<<<<<<<<
 *     if __pyx_state is not None:
 *         __pyx_unpickle_Region__set_state(<Region> __pyx_result, __pyx_state)
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_ptype_3fa2_7fa2util_Region), __pyx_n_s_new); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  __pyx_t_3 = (__pyx_t_4) ? __Pyx_PyObject_Call2Args(__pyx_t_2, __pyx_t_4, __pyx_v___pyx_type) : __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_v___pyx_type);
  __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v___pyx_result = __pyx_t_3;
  __pyx_t_3 = 0;

  /* "(tree fragment)":8
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x66ef4c7 = (mass, massCenterX, massCenterY, nodes, size, subregions))" % __pyx_checksum)
 *     __pyx_result = Region.__new__(__pyx_type)
 *     if __pyx_state is not None:             # <<<<<<<<<<<<<<
 *         __pyx_unpickle_Region__set_state(<Region> __pyx_result, __pyx_state)
 *     return __pyx_result
 */
  __pyx_t_1 = (__pyx_v___pyx_state != Py_None);
  __pyx_t_6 = (__pyx_t_1 != 0);
  if (__pyx_t_6) {

    /* "(tree fragment)":9
 *     __pyx_result = Region.__new__(__pyx_type)
 *     if __pyx_state is not None:
 *         __pyx_unpickle_Region__set_state(<Region> __pyx_result, __pyx_state)             # <<<<<<<<<<<<<<
 *     return __pyx_result
 * cdef __pyx_unpickle_Region__set_state(Region __pyx_result, tuple __pyx_state):
 */
    if (!(likely(PyTuple_CheckExact(__pyx_v___pyx_state))||((__pyx_v___pyx_state) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "tuple", Py_TYPE(__pyx_v___pyx_state)->tp_name), 0))) __PYX_ERR(1, 9, __pyx_L1_error)
    __pyx_t_3 = __pyx_f_3fa2_7fa2util___pyx_unpickle_Region__set_state(((struct __pyx_obj_3fa2_7fa2util_Region *)__pyx_v___pyx_result), ((PyObject*)__pyx_v___pyx_state)); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 9, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "(tree fragment)":8
 *         raise __pyx_PickleError("Incompatible checksums (%s vs 0x66ef4c7 = (mass, massCenterX, massCenterY, nodes, size, subregions))" % __pyx_checksum)
 *     __pyx_result = Region.__new__(__pyx_type)
 *     if __pyx_state is not None:             # <<<<<<<<<<<<<<
 *         __pyx_unpickle_Region__set_state(<Region> __pyx_result, __pyx_state)
 *     return __pyx_result
 */
  }

  /* "(tree fragment)":10
 *     if __pyx_state is not None:
 *         __pyx_unpickle_Region__set_state(<Region> __pyx_result, __pyx_state)
 *     return __pyx_result             # <<<<<<<<<<<<<<
 * cdef __pyx_unpickle_Region__set_state(Region __pyx_result, tuple __pyx_state):
 *     __pyx_result.mass = __pyx_state[0]; __pyx_result.massCenterX = __pyx_state[1]; __pyx_result.massCenterY = __pyx_state[2]; __pyx_result.nodes = __pyx_state[3]; __pyx_result.size = __pyx_state[4]; __pyx_result.subregions = __pyx_state[5]
 */
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v___pyx_result);
  __pyx_r = __pyx_v___pyx_result;
  goto __pyx_L0;

  /* "(tree fragment)":1
 * def __pyx_unpickle_Region(__pyx_type, long __pyx_checksum, __pyx_state):             # <<<<<<<<<<<<<<
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("fa2.fa2util.__pyx_unpickle_Region", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v___pyx_PickleError);
  __Pyx_XDECREF(__pyx_v___pyx_result);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "(tree fragment)":11
 *         __pyx_unpickle_Region__set_state(<Region> __pyx_result, __pyx_state)
 *     return __pyx_result
 * cdef __pyx_unpickle_Region__set_state(Region __pyx_result, tuple __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_result.mass = __pyx_state[0]; __pyx_result.massCenterX = __pyx_state[1]; __pyx_result.massCenterY = __pyx_state[2]; __pyx_result.nodes = __pyx_state[3]; __pyx_result.size = __pyx_state[4]; __pyx_result.subregions = __pyx_state[5]
 *     if len(__pyx_state) > 6 and hasattr(__pyx_result, '__dict__'):
 */

static PyObject *__pyx_f_3fa2_7fa2util___pyx_unpickle_Region__set_state(struct __pyx_obj_3fa2_7fa2util_Region *__pyx_v___pyx_result, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  double __pyx_t_2;
  int __pyx_t_3;
  Py_ssize_t __pyx_t_4;
  int __pyx_t_5;
  int __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__pyx_unpickle_Region__set_state", 0);

  /* "(tree fragment)":12
 *     return __pyx_result
 * cdef __pyx_unpickle_Region__set_state(Region __pyx_result, tuple __pyx_state):
 *     __pyx_result.mass = __pyx_state[0]; __pyx_result.massCenterX = __pyx_state[1]; __pyx_result.massCenterY = __pyx_state[2]; __pyx_result.nodes = __pyx_state[3]; __pyx_result.size = __pyx_state[4]; __pyx_result.subregions = __pyx_state[5]             # <<<<<<<<<<<<<<
 *     if len(__pyx_state) > 6 and hasattr(__pyx_result, '__dict__'):
 *         __pyx_result.__dict__.update(__pyx_state[6])
 */
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_2 == (double)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->mass = __pyx_t_2;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_2 == (double)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->massCenterX = __pyx_t_2;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 2, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_2 == (double)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->massCenterY = __pyx_t_2;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 3, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (!(likely(PyList_CheckExact(__pyx_t_1))||((__pyx_t_1) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "list", Py_TYPE(__pyx_t_1)->tp_name), 0))) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GIVEREF(__pyx_t_1);
  __Pyx_GOTREF(__pyx_v___pyx_result->nodes);
  __Pyx_DECREF(__pyx_v___pyx_result->nodes);
  __pyx_v___pyx_result->nodes = ((PyObject*)__pyx_t_1);
  __pyx_t_1 = 0;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 4, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_2 == (double)-1) && PyErr_Occurred())) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result->size = __pyx_t_2;
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(1, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 5, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (!(likely(PyList_CheckExact(__pyx_t_1))||((__pyx_t_1) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "list", Py_TYPE(__pyx_t_1)->tp_name), 0))) __PYX_ERR(1, 12, __pyx_L1_error)
  __Pyx_GIVEREF(__pyx_t_1);
  __Pyx_GOTREF(__pyx_v___pyx_result->subregions);
  __Pyx_DECREF(__pyx_v___pyx_result->subregions);
  __pyx_v___pyx_result->subregions = ((PyObject*)__pyx_t_1);
  __pyx_t_1 = 0;

  /* "(tree fragment)":13
 * cdef __pyx_unpickle_Region__set_state(Region __pyx_result, tuple __pyx_state):
 *     __pyx_result.mass = __pyx_state[0]; __pyx_result.massCenterX = __pyx_state[1]; __pyx_result.massCenterY = __pyx_state[2]; __pyx_result.nodes = __pyx_state[3]; __pyx_result.size = __pyx_state[4]; __pyx_result.subregions = __pyx_state[5]
 *     if len(__pyx_state) > 6 and hasattr(__pyx_result, '__dict__'):             # <<<<<<<<<<<<<<
 *         __pyx_result.__dict__.update(__pyx_state[6])
 */
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    __PYX_ERR(1, 13, __pyx_L1_error)
  }
  __pyx_t_4 = PyTuple_GET_SIZE(__pyx_v___pyx_state); if (unlikely(__pyx_t_4 == ((Py_ssize_t)-1))) __PYX_ERR(1, 13, __pyx_L1_error)
  __pyx_t_5 = ((__pyx_t_4 > 6) != 0);
  if (__pyx_t_5) {
  } else {
    __pyx_t_3 = __pyx_t_5;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_5 = __Pyx_HasAttr(((PyObject *)__pyx_v___pyx_result), __pyx_n_s_dict); if (unlikely(__pyx_t_5 == ((int)-1))) __PYX_ERR(1, 13, __pyx_L1_error)
  __pyx_t_6 = (__pyx_t_5 != 0);
  __pyx_t_3 = __pyx_t_6;
  __pyx_L4_bool_binop_done:;
  if (__pyx_t_3) {

    /* "(tree fragment)":14
 *     __pyx_result.mass = __pyx_state[0]; __pyx_result.massCenterX = __pyx_state[1]; __pyx_result.massCenterY = __pyx_state[2]; __pyx_result.nodes = __pyx_state[3]; __pyx_result.size = __pyx_state[4]; __pyx_result.subregions = __pyx_state[5]
 *     if len(__pyx_state) > 6 and hasattr(__pyx_result, '__dict__'):
 *         __pyx_result.__dict__.update(__pyx_state[6])             # <<<<<<<<<<<<<<
 */
    __pyx_t_7 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v___pyx_result), __pyx_n_s_dict); if (unlikely(!__pyx_t_7)) __PYX_ERR(1, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_update); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    if (unlikely(__pyx_v___pyx_state == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      __PYX_ERR(1, 14, __pyx_L1_error)
    }
    __pyx_t_7 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 6, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_7)) __PYX_ERR(1, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_9 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_8))) {
      __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_8);
      if (likely(__pyx_t_9)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_8);
        __Pyx_INCREF(__pyx_t_9);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_8, function);
      }
    }
    __pyx_t_1 = (__pyx_t_9) ? __Pyx_PyObject_Call2Args(__pyx_t_8, __pyx_t_9, __pyx_t_7) : __Pyx_PyObject_CallOneArg(__pyx_t_8, __pyx_t_7);
    __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "(tree fragment)":13
 * cdef __pyx_unpickle_Region__set_state(Region __pyx_result, tuple __pyx_state):
 *     __pyx_result.mass = __pyx_state[0]; __pyx_result.massCenterX = __pyx_state[1]; __pyx_result.massCenterY = __pyx_state[2]; __pyx_result.nodes = __pyx_state[3]; __pyx_result.size = __pyx_state[4]; __pyx_result.subregions = __pyx_state[5]
 *     if len(__pyx_state) > 6 and hasattr(__pyx_result, '__dict__'):             # <<<<<<<<<<<<<<
 *         __pyx_result.__dict__.update(__pyx_state[6])
 */
  }

  /* "(tree fragment)":11
 *         __pyx_unpickle_Region__set_state(<Region> __pyx_result, __pyx_state)
 *     return __pyx_result
 * cdef __pyx_unpickle_Region__set_state(Region __pyx_result, tuple __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_result.mass = __pyx_state[0]; __pyx_result.massCenterX = __pyx_state[1]; __pyx_result.massCenterY = __pyx_state[2]; __pyx_result.nodes = __pyx_state[3]; __pyx_result.size = __pyx_state[4]; __pyx_result.subregions = __pyx_state[5]
 *     if len(__pyx_state) > 6 and hasattr(__pyx_result, '__dict__'):
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("fa2.fa2util.__pyx_unpickle_Region__set_state", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_tp_new_3fa2_7fa2util_Node(PyTypeObject *t, CYTHON_UNUSED PyObject *a, CYTHON_UNUSED PyObject *k) {
  PyObject *o;
  if (likely((t->tp_flags & Py_TPFLAGS_IS_ABSTRACT) == 0)) {
    o = (*t->tp_alloc)(t, 0);
  } else {
    o = (PyObject *) PyBaseObject_Type.tp_new(t, __pyx_empty_tuple, 0);
  }
  if (unlikely(!o)) return 0;
  return o;
}

static void __pyx_tp_dealloc_3fa2_7fa2util_Node(PyObject *o) {
  #if CYTHON_USE_TP_FINALIZE
  if (unlikely(PyType_HasFeature(Py_TYPE(o), Py_TPFLAGS_HAVE_FINALIZE) && Py_TYPE(o)->tp_finalize) && (!PyType_IS_GC(Py_TYPE(o)) || !_PyGC_FINALIZED(o))) {
    if (PyObject_CallFinalizerFromDealloc(o)) return;
  }
  #endif
  (*Py_TYPE(o)->tp_free)(o);
}

static PyObject *__pyx_getprop_3fa2_7fa2util_4Node_mass(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_4Node_4mass_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_4Node_mass(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_4Node_4mass_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_4Node_old_dx(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_4Node_6old_dx_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_4Node_old_dx(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_4Node_6old_dx_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_4Node_old_dy(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_4Node_6old_dy_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_4Node_old_dy(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_4Node_6old_dy_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_4Node_dx(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_4Node_2dx_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_4Node_dx(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_4Node_2dx_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_4Node_dy(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_4Node_2dy_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_4Node_dy(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_4Node_2dy_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_4Node_x(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_4Node_1x_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_4Node_x(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_4Node_1x_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_4Node_y(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_4Node_1y_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_4Node_y(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_4Node_1y_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyMethodDef __pyx_methods_3fa2_7fa2util_Node[] = {
  {"__reduce_cython__", (PyCFunction)__pyx_pw_3fa2_7fa2util_4Node_3__reduce_cython__, METH_NOARGS, 0},
  {"__setstate_cython__", (PyCFunction)__pyx_pw_3fa2_7fa2util_4Node_5__setstate_cython__, METH_O, 0},
  {0, 0, 0, 0}
};

static struct PyGetSetDef __pyx_getsets_3fa2_7fa2util_Node[] = {
  {(char *)"mass", __pyx_getprop_3fa2_7fa2util_4Node_mass, __pyx_setprop_3fa2_7fa2util_4Node_mass, (char *)0, 0},
  {(char *)"old_dx", __pyx_getprop_3fa2_7fa2util_4Node_old_dx, __pyx_setprop_3fa2_7fa2util_4Node_old_dx, (char *)0, 0},
  {(char *)"old_dy", __pyx_getprop_3fa2_7fa2util_4Node_old_dy, __pyx_setprop_3fa2_7fa2util_4Node_old_dy, (char *)0, 0},
  {(char *)"dx", __pyx_getprop_3fa2_7fa2util_4Node_dx, __pyx_setprop_3fa2_7fa2util_4Node_dx, (char *)0, 0},
  {(char *)"dy", __pyx_getprop_3fa2_7fa2util_4Node_dy, __pyx_setprop_3fa2_7fa2util_4Node_dy, (char *)0, 0},
  {(char *)"x", __pyx_getprop_3fa2_7fa2util_4Node_x, __pyx_setprop_3fa2_7fa2util_4Node_x, (char *)0, 0},
  {(char *)"y", __pyx_getprop_3fa2_7fa2util_4Node_y, __pyx_setprop_3fa2_7fa2util_4Node_y, (char *)0, 0},
  {0, 0, 0, 0, 0}
};

static PyTypeObject __pyx_type_3fa2_7fa2util_Node = {
  PyVarObject_HEAD_INIT(0, 0)
  "fa2.fa2util.Node", /*tp_name*/
  sizeof(struct __pyx_obj_3fa2_7fa2util_Node), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_3fa2_7fa2util_Node, /*tp_dealloc*/
  #if PY_VERSION_HEX < 0x030800b4
  0, /*tp_print*/
  #endif
  #if PY_VERSION_HEX >= 0x030800b4
  0, /*tp_vectorcall_offset*/
  #endif
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  #if PY_MAJOR_VERSION < 3
  0, /*tp_compare*/
  #endif
  #if PY_MAJOR_VERSION >= 3
  0, /*tp_as_async*/
  #endif
  0, /*tp_repr*/
  0, /*tp_as_number*/
  0, /*tp_as_sequence*/
  0, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  0, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_VERSION_TAG|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE, /*tp_flags*/
  0, /*tp_doc*/
  0, /*tp_traverse*/
  0, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_3fa2_7fa2util_Node, /*tp_methods*/
  0, /*tp_members*/
  __pyx_getsets_3fa2_7fa2util_Node, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_pw_3fa2_7fa2util_4Node_1__init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_3fa2_7fa2util_Node, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
  0, /*tp_del*/
  0, /*tp_version_tag*/
  #if PY_VERSION_HEX >= 0x030400a1
  0, /*tp_finalize*/
  #endif
  #if PY_VERSION_HEX >= 0x030800b1
  0, /*tp_vectorcall*/
  #endif
  #if PY_VERSION_HEX >= 0x030800b4 && PY_VERSION_HEX < 0x03090000
  0, /*tp_print*/
  #endif
};

static PyObject *__pyx_tp_new_3fa2_7fa2util_Edge(PyTypeObject *t, CYTHON_UNUSED PyObject *a, CYTHON_UNUSED PyObject *k) {
  PyObject *o;
  if (likely((t->tp_flags & Py_TPFLAGS_IS_ABSTRACT) == 0)) {
    o = (*t->tp_alloc)(t, 0);
  } else {
    o = (PyObject *) PyBaseObject_Type.tp_new(t, __pyx_empty_tuple, 0);
  }
  if (unlikely(!o)) return 0;
  return o;
}

static void __pyx_tp_dealloc_3fa2_7fa2util_Edge(PyObject *o) {
  #if CYTHON_USE_TP_FINALIZE
  if (unlikely(PyType_HasFeature(Py_TYPE(o), Py_TPFLAGS_HAVE_FINALIZE) && Py_TYPE(o)->tp_finalize) && (!PyType_IS_GC(Py_TYPE(o)) || !_PyGC_FINALIZED(o))) {
    if (PyObject_CallFinalizerFromDealloc(o)) return;
  }
  #endif
  (*Py_TYPE(o)->tp_free)(o);
}

static PyObject *__pyx_getprop_3fa2_7fa2util_4Edge_node1(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_4Edge_5node1_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_4Edge_node1(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_4Edge_5node1_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_4Edge_node2(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_4Edge_5node2_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_4Edge_node2(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_4Edge_5node2_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_4Edge_weight(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_4Edge_6weight_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_4Edge_weight(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_4Edge_6weight_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyMethodDef __pyx_methods_3fa2_7fa2util_Edge[] = {
  {"__reduce_cython__", (PyCFunction)__pyx_pw_3fa2_7fa2util_4Edge_3__reduce_cython__, METH_NOARGS, 0},
  {"__setstate_cython__", (PyCFunction)__pyx_pw_3fa2_7fa2util_4Edge_5__setstate_cython__, METH_O, 0},
  {0, 0, 0, 0}
};

static struct PyGetSetDef __pyx_getsets_3fa2_7fa2util_Edge[] = {
  {(char *)"node1", __pyx_getprop_3fa2_7fa2util_4Edge_node1, __pyx_setprop_3fa2_7fa2util_4Edge_node1, (char *)0, 0},
  {(char *)"node2", __pyx_getprop_3fa2_7fa2util_4Edge_node2, __pyx_setprop_3fa2_7fa2util_4Edge_node2, (char *)0, 0},
  {(char *)"weight", __pyx_getprop_3fa2_7fa2util_4Edge_weight, __pyx_setprop_3fa2_7fa2util_4Edge_weight, (char *)0, 0},
  {0, 0, 0, 0, 0}
};

static PyTypeObject __pyx_type_3fa2_7fa2util_Edge = {
  PyVarObject_HEAD_INIT(0, 0)
  "fa2.fa2util.Edge", /*tp_name*/
  sizeof(struct __pyx_obj_3fa2_7fa2util_Edge), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_3fa2_7fa2util_Edge, /*tp_dealloc*/
  #if PY_VERSION_HEX < 0x030800b4
  0, /*tp_print*/
  #endif
  #if PY_VERSION_HEX >= 0x030800b4
  0, /*tp_vectorcall_offset*/
  #endif
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  #if PY_MAJOR_VERSION < 3
  0, /*tp_compare*/
  #endif
  #if PY_MAJOR_VERSION >= 3
  0, /*tp_as_async*/
  #endif
  0, /*tp_repr*/
  0, /*tp_as_number*/
  0, /*tp_as_sequence*/
  0, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  0, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_VERSION_TAG|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE, /*tp_flags*/
  0, /*tp_doc*/
  0, /*tp_traverse*/
  0, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_3fa2_7fa2util_Edge, /*tp_methods*/
  0, /*tp_members*/
  __pyx_getsets_3fa2_7fa2util_Edge, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_pw_3fa2_7fa2util_4Edge_1__init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_3fa2_7fa2util_Edge, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
  0, /*tp_del*/
  0, /*tp_version_tag*/
  #if PY_VERSION_HEX >= 0x030400a1
  0, /*tp_finalize*/
  #endif
  #if PY_VERSION_HEX >= 0x030800b1
  0, /*tp_vectorcall*/
  #endif
  #if PY_VERSION_HEX >= 0x030800b4 && PY_VERSION_HEX < 0x03090000
  0, /*tp_print*/
  #endif
};
static struct __pyx_vtabstruct_3fa2_7fa2util_Region __pyx_vtable_3fa2_7fa2util_Region;

static PyObject *__pyx_tp_new_3fa2_7fa2util_Region(PyTypeObject *t, CYTHON_UNUSED PyObject *a, CYTHON_UNUSED PyObject *k) {
  struct __pyx_obj_3fa2_7fa2util_Region *p;
  PyObject *o;
  if (likely((t->tp_flags & Py_TPFLAGS_IS_ABSTRACT) == 0)) {
    o = (*t->tp_alloc)(t, 0);
  } else {
    o = (PyObject *) PyBaseObject_Type.tp_new(t, __pyx_empty_tuple, 0);
  }
  if (unlikely(!o)) return 0;
  p = ((struct __pyx_obj_3fa2_7fa2util_Region *)o);
  p->__pyx_vtab = __pyx_vtabptr_3fa2_7fa2util_Region;
  p->nodes = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->subregions = ((PyObject*)Py_None); Py_INCREF(Py_None);
  return o;
}

static void __pyx_tp_dealloc_3fa2_7fa2util_Region(PyObject *o) {
  struct __pyx_obj_3fa2_7fa2util_Region *p = (struct __pyx_obj_3fa2_7fa2util_Region *)o;
  #if CYTHON_USE_TP_FINALIZE
  if (unlikely(PyType_HasFeature(Py_TYPE(o), Py_TPFLAGS_HAVE_FINALIZE) && Py_TYPE(o)->tp_finalize) && !_PyGC_FINALIZED(o)) {
    if (PyObject_CallFinalizerFromDealloc(o)) return;
  }
  #endif
  PyObject_GC_UnTrack(o);
  Py_CLEAR(p->nodes);
  Py_CLEAR(p->subregions);
  (*Py_TYPE(o)->tp_free)(o);
}

static int __pyx_tp_traverse_3fa2_7fa2util_Region(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_3fa2_7fa2util_Region *p = (struct __pyx_obj_3fa2_7fa2util_Region *)o;
  if (p->nodes) {
    e = (*v)(p->nodes, a); if (e) return e;
  }
  if (p->subregions) {
    e = (*v)(p->subregions, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_3fa2_7fa2util_Region(PyObject *o) {
  PyObject* tmp;
  struct __pyx_obj_3fa2_7fa2util_Region *p = (struct __pyx_obj_3fa2_7fa2util_Region *)o;
  tmp = ((PyObject*)p->nodes);
  p->nodes = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->subregions);
  p->subregions = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  return 0;
}

static PyObject *__pyx_getprop_3fa2_7fa2util_6Region_mass(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_6Region_4mass_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_6Region_mass(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_6Region_4mass_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_6Region_massCenterX(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_6Region_11massCenterX_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_6Region_massCenterX(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_6Region_11massCenterX_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_6Region_massCenterY(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_6Region_11massCenterY_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_6Region_massCenterY(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_6Region_11massCenterY_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_6Region_size(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_6Region_4size_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_6Region_size(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_6Region_4size_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_6Region_nodes(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_6Region_5nodes_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_6Region_nodes(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_6Region_5nodes_3__set__(o, v);
  }
  else {
    return __pyx_pw_3fa2_7fa2util_6Region_5nodes_5__del__(o);
  }
}

static PyObject *__pyx_getprop_3fa2_7fa2util_6Region_subregions(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_3fa2_7fa2util_6Region_10subregions_1__get__(o);
}

static int __pyx_setprop_3fa2_7fa2util_6Region_subregions(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_3fa2_7fa2util_6Region_10subregions_3__set__(o, v);
  }
  else {
    return __pyx_pw_3fa2_7fa2util_6Region_10subregions_5__del__(o);
  }
}

static PyMethodDef __pyx_methods_3fa2_7fa2util_Region[] = {
  {"__reduce_cython__", (PyCFunction)__pyx_pw_3fa2_7fa2util_6Region_7__reduce_cython__, METH_NOARGS, 0},
  {"__setstate_cython__", (PyCFunction)__pyx_pw_3fa2_7fa2util_6Region_9__setstate_cython__, METH_O, 0},
  {0, 0, 0, 0}
};

static struct PyGetSetDef __pyx_getsets_3fa2_7fa2util_Region[] = {
  {(char *)"mass", __pyx_getprop_3fa2_7fa2util_6Region_mass, __pyx_setprop_3fa2_7fa2util_6Region_mass, (char *)0, 0},
  {(char *)"massCenterX", __pyx_getprop_3fa2_7fa2util_6Region_massCenterX, __pyx_setprop_3fa2_7fa2util_6Region_massCenterX, (char *)0, 0},
  {(char *)"massCenterY", __pyx_getprop_3fa2_7fa2util_6Region_massCenterY, __pyx_setprop_3fa2_7fa2util_6Region_massCenterY, (char *)0, 0},
  {(char *)"size", __pyx_getprop_3fa2_7fa2util_6Region_size, __pyx_setprop_3fa2_7fa2util_6Region_size, (char *)0, 0},
  {(char *)"nodes", __pyx_getprop_3fa2_7fa2util_6Region_nodes, __pyx_setprop_3fa2_7fa2util_6Region_nodes, (char *)0, 0},
  {(char *)"subregions", __pyx_getprop_3fa2_7fa2util_6Region_subregions, __pyx_setprop_3fa2_7fa2util_6Region_subregions, (char *)0, 0},
  {0, 0, 0, 0, 0}
};

static PyTypeObject __pyx_type_3fa2_7fa2util_Region = {
  PyVarObject_HEAD_INIT(0, 0)
  "fa2.fa2util.Region", /*tp_name*/
  sizeof(struct __pyx_obj_3fa2_7fa2util_Region), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_3fa2_7fa2util_Region, /*tp_dealloc*/
  #if PY_VERSION_HEX < 0x030800b4
  0, /*tp_print*/
  #endif
  #if PY_VERSION_HEX >= 0x030800b4
  0, /*tp_vectorcall_offset*/
  #endif
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  #if PY_MAJOR_VERSION < 3
  0, /*tp_compare*/
  #endif
  #if PY_MAJOR_VERSION >= 3
  0, /*tp_as_async*/
  #endif
  0, /*tp_repr*/
  0, /*tp_as_number*/
  0, /*tp_as_sequence*/
  0, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  0, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_VERSION_TAG|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, /*tp_flags*/
  0, /*tp_doc*/
  __pyx_tp_traverse_3fa2_7fa2util_Region, /*tp_traverse*/
  __pyx_tp_clear_3fa2_7fa2util_Region, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_3fa2_7fa2util_Region, /*tp_methods*/
  0, /*tp_members*/
  __pyx_getsets_3fa2_7fa2util_Region, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_pw_3fa2_7fa2util_6Region_1__init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_3fa2_7fa2util_Region, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
  0, /*tp_del*/
  0, /*tp_version_tag*/
  #if PY_VERSION_HEX >= 0x030400a1
  0, /*tp_finalize*/
  #endif
  #if PY_VERSION_HEX >= 0x030800b1
  0, /*tp_vectorcall*/
  #endif
  #if PY_VERSION_HEX >= 0x030800b4 && PY_VERSION_HEX < 0x03090000
  0, /*tp_print*/
  #endif
};

static PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};

#if PY_MAJOR_VERSION >= 3
#if CYTHON_PEP489_MULTI_PHASE_INIT
static PyObject* __pyx_pymod_create(PyObject *spec, PyModuleDef *def); /*proto*/
static int __pyx_pymod_exec_fa2util(PyObject* module); /*proto*/
static PyModuleDef_Slot __pyx_moduledef_slots[] = {
  {Py_mod_create, (void*)__pyx_pymod_create},
  {Py_mod_exec, (void*)__pyx_pymod_exec_fa2util},
  {0, NULL}
};
#endif

static struct PyModuleDef __pyx_moduledef = {
    PyModuleDef_HEAD_INIT,
    "fa2util",
    0, /* m_doc */
  #if CYTHON_PEP489_MULTI_PHASE_INIT
    0, /* m_size */
  #else
    -1, /* m_size */
  #endif
    __pyx_methods /* m_methods */,
  #if CYTHON_PEP489_MULTI_PHASE_INIT
    __pyx_moduledef_slots, /* m_slots */
  #else
    NULL, /* m_reload */
  #endif
    NULL, /* m_traverse */
    NULL, /* m_clear */
    NULL /* m_free */
};
#endif
#ifndef CYTHON_SMALL_CODE
#if defined(__clang__)
    #define CYTHON_SMALL_CODE
#elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
    #define CYTHON_SMALL_CODE __attribute__((cold))
#else
    #define CYTHON_SMALL_CODE
#endif
#endif

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_n_s_Edge, __pyx_k_Edge, sizeof(__pyx_k_Edge), 0, 0, 1, 1},
  {&__pyx_n_s_Edge___reduce_cython, __pyx_k_Edge___reduce_cython, sizeof(__pyx_k_Edge___reduce_cython), 0, 0, 1, 1},
  {&__pyx_n_s_Edge___setstate_cython, __pyx_k_Edge___setstate_cython, sizeof(__pyx_k_Edge___setstate_cython), 0, 0, 1, 1},
  {&__pyx_kp_s_Incompatible_checksums_s_vs_0x2f, __pyx_k_Incompatible_checksums_s_vs_0x2f, sizeof(__pyx_k_Incompatible_checksums_s_vs_0x2f), 0, 0, 1, 0},
  {&__pyx_kp_s_Incompatible_checksums_s_vs_0x66, __pyx_k_Incompatible_checksums_s_vs_0x66, sizeof(__pyx_k_Incompatible_checksums_s_vs_0x66), 0, 0, 1, 0},
  {&__pyx_kp_s_Incompatible_checksums_s_vs_0xb4, __pyx_k_Incompatible_checksums_s_vs_0xb4, sizeof(__pyx_k_Incompatible_checksums_s_vs_0xb4), 0, 0, 1, 0},
  {&__pyx_kp_s_No_cython_detected_Install_cytho, __pyx_k_No_cython_detected_Install_cytho, sizeof(__pyx_k_No_cython_detected_Install_cytho), 0, 0, 1, 0},
  {&__pyx_n_s_Node, __pyx_k_Node, sizeof(__pyx_k_Node), 0, 0, 1, 1},
  {&__pyx_n_s_Node___reduce_cython, __pyx_k_Node___reduce_cython, sizeof(__pyx_k_Node___reduce_cython), 0, 0, 1, 1},
  {&__pyx_n_s_Node___setstate_cython, __pyx_k_Node___setstate_cython, sizeof(__pyx_k_Node___setstate_cython), 0, 0, 1, 1},
  {&__pyx_n_s_PickleError, __pyx_k_PickleError, sizeof(__pyx_k_PickleError), 0, 0, 1, 1},
  {&__pyx_n_s_Region, __pyx_k_Region, sizeof(__pyx_k_Region), 0, 0, 1, 1},
  {&__pyx_n_s_Region___reduce_cython, __pyx_k_Region___reduce_cython, sizeof(__pyx_k_Region___reduce_cython), 0, 0, 1, 1},
  {&__pyx_n_s_Region___setstate_cython, __pyx_k_Region___setstate_cython, sizeof(__pyx_k_Region___setstate_cython), 0, 0, 1, 1},
  {&__pyx_n_s_Region_applyForceOnNodes, __pyx_k_Region_applyForceOnNodes, sizeof(__pyx_k_Region_applyForceOnNodes), 0, 0, 1, 1},
  {&__pyx_n_s_Region_buildSubRegions, __pyx_k_Region_buildSubRegions, sizeof(__pyx_k_Region_buildSubRegions), 0, 0, 1, 1},
  {&__pyx_kp_s_Warning_uncompiled_fa2util_modul, __pyx_k_Warning_uncompiled_fa2util_modul, sizeof(__pyx_k_Warning_uncompiled_fa2util_modul), 0, 0, 1, 0},
  {&__pyx_n_s_adjustSpeedAndApplyForces, __pyx_k_adjustSpeedAndApplyForces, sizeof(__pyx_k_adjustSpeedAndApplyForces), 0, 0, 1, 1},
  {&__pyx_n_s_applyForceOnNodes, __pyx_k_applyForceOnNodes, sizeof(__pyx_k_applyForceOnNodes), 0, 0, 1, 1},
  {&__pyx_n_s_apply_attraction, __pyx_k_apply_attraction, sizeof(__pyx_k_apply_attraction), 0, 0, 1, 1},
  {&__pyx_n_s_apply_gravity, __pyx_k_apply_gravity, sizeof(__pyx_k_apply_gravity), 0, 0, 1, 1},
  {&__pyx_n_s_apply_repulsion, __pyx_k_apply_repulsion, sizeof(__pyx_k_apply_repulsion), 0, 0, 1, 1},
  {&__pyx_n_s_buildSubRegions, __pyx_k_buildSubRegions, sizeof(__pyx_k_buildSubRegions), 0, 0, 1, 1},
  {&__pyx_n_s_cline_in_traceback, __pyx_k_cline_in_traceback, sizeof(__pyx_k_cline_in_traceback), 0, 0, 1, 1},
  {&__pyx_n_s_coefficient, __pyx_k_coefficient, sizeof(__pyx_k_coefficient), 0, 0, 1, 1},
  {&__pyx_n_s_dict, __pyx_k_dict, sizeof(__pyx_k_dict), 0, 0, 1, 1},
  {&__pyx_n_s_dict_2, __pyx_k_dict_2, sizeof(__pyx_k_dict_2), 0, 0, 1, 1},
  {&__pyx_n_s_distributedAttraction, __pyx_k_distributedAttraction, sizeof(__pyx_k_distributedAttraction), 0, 0, 1, 1},
  {&__pyx_n_s_e, __pyx_k_e, sizeof(__pyx_k_e), 0, 0, 1, 1},
  {&__pyx_n_s_edgeWeightInfluence, __pyx_k_edgeWeightInfluence, sizeof(__pyx_k_edgeWeightInfluence), 0, 0, 1, 1},
  {&__pyx_n_s_edges, __pyx_k_edges, sizeof(__pyx_k_edges), 0, 0, 1, 1},
  {&__pyx_n_s_end, __pyx_k_end, sizeof(__pyx_k_end), 0, 0, 1, 1},
  {&__pyx_n_s_fa2_fa2util, __pyx_k_fa2_fa2util, sizeof(__pyx_k_fa2_fa2util), 0, 0, 1, 1},
  {&__pyx_kp_s_fa2util_py, __pyx_k_fa2util_py, sizeof(__pyx_k_fa2util_py), 0, 0, 1, 0},
  {&__pyx_n_s_file, __pyx_k_file, sizeof(__pyx_k_file), 0, 0, 1, 1},
  {&__pyx_n_s_getstate, __pyx_k_getstate, sizeof(__pyx_k_getstate), 0, 0, 1, 1},
  {&__pyx_n_s_gravity, __pyx_k_gravity, sizeof(__pyx_k_gravity), 0, 0, 1, 1},
  {&__pyx_n_s_import, __pyx_k_import, sizeof(__pyx_k_import), 0, 0, 1, 1},
  {&__pyx_n_s_inf, __pyx_k_inf, sizeof(__pyx_k_inf), 0, 0, 1, 1},
  {&__pyx_n_s_jitterTolerance, __pyx_k_jitterTolerance, sizeof(__pyx_k_jitterTolerance), 0, 0, 1, 1},
  {&__pyx_n_s_linAttraction, __pyx_k_linAttraction, sizeof(__pyx_k_linAttraction), 0, 0, 1, 1},
  {&__pyx_n_s_main, __pyx_k_main, sizeof(__pyx_k_main), 0, 0, 1, 1},
  {&__pyx_n_s_math, __pyx_k_math, sizeof(__pyx_k_math), 0, 0, 1, 1},
  {&__pyx_n_s_n1, __pyx_k_n1, sizeof(__pyx_k_n1), 0, 0, 1, 1},
  {&__pyx_n_s_n2, __pyx_k_n2, sizeof(__pyx_k_n2), 0, 0, 1, 1},
  {&__pyx_n_s_name, __pyx_k_name, sizeof(__pyx_k_name), 0, 0, 1, 1},
  {&__pyx_n_s_new, __pyx_k_new, sizeof(__pyx_k_new), 0, 0, 1, 1},
  {&__pyx_n_s_nodes, __pyx_k_nodes, sizeof(__pyx_k_nodes), 0, 0, 1, 1},
  {&__pyx_n_s_pickle, __pyx_k_pickle, sizeof(__pyx_k_pickle), 0, 0, 1, 1},
  {&__pyx_n_s_print, __pyx_k_print, sizeof(__pyx_k_print), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_PickleError, __pyx_k_pyx_PickleError, sizeof(__pyx_k_pyx_PickleError), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_checksum, __pyx_k_pyx_checksum, sizeof(__pyx_k_pyx_checksum), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_result, __pyx_k_pyx_result, sizeof(__pyx_k_pyx_result), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_state, __pyx_k_pyx_state, sizeof(__pyx_k_pyx_state), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_type, __pyx_k_pyx_type, sizeof(__pyx_k_pyx_type), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_unpickle_Edge, __pyx_k_pyx_unpickle_Edge, sizeof(__pyx_k_pyx_unpickle_Edge), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_unpickle_Node, __pyx_k_pyx_unpickle_Node, sizeof(__pyx_k_pyx_unpickle_Node), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_unpickle_Region, __pyx_k_pyx_unpickle_Region, sizeof(__pyx_k_pyx_unpickle_Region), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_vtable, __pyx_k_pyx_vtable, sizeof(__pyx_k_pyx_vtable), 0, 0, 1, 1},
  {&__pyx_n_s_reduce, __pyx_k_reduce, sizeof(__pyx_k_reduce), 0, 0, 1, 1},
  {&__pyx_n_s_reduce_cython, __pyx_k_reduce_cython, sizeof(__pyx_k_reduce_cython), 0, 0, 1, 1},
  {&__pyx_n_s_reduce_ex, __pyx_k_reduce_ex, sizeof(__pyx_k_reduce_ex), 0, 0, 1, 1},
  {&__pyx_n_s_scalingRatio, __pyx_k_scalingRatio, sizeof(__pyx_k_scalingRatio), 0, 0, 1, 1},
  {&__pyx_n_s_self, __pyx_k_self, sizeof(__pyx_k_self), 0, 0, 1, 1},
  {&__pyx_n_s_setstate, __pyx_k_setstate, sizeof(__pyx_k_setstate), 0, 0, 1, 1},
  {&__pyx_n_s_setstate_cython, __pyx_k_setstate_cython, sizeof(__pyx_k_setstate_cython), 0, 0, 1, 1},
  {&__pyx_n_s_speed, __pyx_k_speed, sizeof(__pyx_k_speed), 0, 0, 1, 1},
  {&__pyx_n_s_speedEfficiency, __pyx_k_speedEfficiency, sizeof(__pyx_k_speedEfficiency), 0, 0, 1, 1},
  {&__pyx_n_s_sqrt, __pyx_k_sqrt, sizeof(__pyx_k_sqrt), 0, 0, 1, 1},
  {&__pyx_n_s_state, __pyx_k_state, sizeof(__pyx_k_state), 0, 0, 1, 1},
  {&__pyx_kp_s_stringsource, __pyx_k_stringsource, sizeof(__pyx_k_stringsource), 0, 0, 1, 0},
  {&__pyx_n_s_test, __pyx_k_test, sizeof(__pyx_k_test), 0, 0, 1, 1},
  {&__pyx_n_s_theta, __pyx_k_theta, sizeof(__pyx_k_theta), 0, 0, 1, 1},
  {&__pyx_n_s_update, __pyx_k_update, sizeof(__pyx_k_update), 0, 0, 1, 1},
  {&__pyx_n_s_useStrongGravity, __pyx_k_useStrongGravity, sizeof(__pyx_k_useStrongGravity), 0, 0, 1, 1},
  {&__pyx_n_s_use_setstate, __pyx_k_use_setstate, sizeof(__pyx_k_use_setstate), 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0}
};
static CYTHON_SMALL_CODE int __Pyx_InitCachedBuiltins(void) {
  return 0;
}

static CYTHON_SMALL_CODE int __Pyx_InitCachedConstants(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_InitCachedConstants", 0);

  /* "(tree fragment)":1
 * def __reduce_cython__(self):             # <<<<<<<<<<<<<<
 *     cdef tuple state
 *     cdef object _dict
 */
  __pyx_tuple_ = PyTuple_Pack(4, __pyx_n_s_self, __pyx_n_s_state, __pyx_n_s_dict_2, __pyx_n_s_use_setstate); if (unlikely(!__pyx_tuple_)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple_);
  __Pyx_GIVEREF(__pyx_tuple_);
  __pyx_codeobj__2 = (PyObject*)__Pyx_PyCode_New(1, 0, 4, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple_, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_stringsource, __pyx_n_s_reduce_cython, 1, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__2)) __PYX_ERR(1, 1, __pyx_L1_error)

  /* "(tree fragment)":16
 *     else:
 *         return __pyx_unpickle_Node, (type(self), 0x2f233dd, state)
 * def __setstate_cython__(self, __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_unpickle_Node__set_state(self, __pyx_state)
 */
  __pyx_tuple__3 = PyTuple_Pack(2, __pyx_n_s_self, __pyx_n_s_pyx_state); if (unlikely(!__pyx_tuple__3)) __PYX_ERR(1, 16, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__3);
  __Pyx_GIVEREF(__pyx_tuple__3);
  __pyx_codeobj__4 = (PyObject*)__Pyx_PyCode_New(2, 0, 2, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__3, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_stringsource, __pyx_n_s_setstate_cython, 16, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__4)) __PYX_ERR(1, 16, __pyx_L1_error)

  /* "(tree fragment)":1
 * def __reduce_cython__(self):             # <<<<<<<<<<<<<<
 *     cdef tuple state
 *     cdef object _dict
 */
  __pyx_tuple__5 = PyTuple_Pack(4, __pyx_n_s_self, __pyx_n_s_state, __pyx_n_s_dict_2, __pyx_n_s_use_setstate); if (unlikely(!__pyx_tuple__5)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__5);
  __Pyx_GIVEREF(__pyx_tuple__5);
  __pyx_codeobj__6 = (PyObject*)__Pyx_PyCode_New(1, 0, 4, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__5, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_stringsource, __pyx_n_s_reduce_cython, 1, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__6)) __PYX_ERR(1, 1, __pyx_L1_error)

  /* "(tree fragment)":16
 *     else:
 *         return __pyx_unpickle_Edge, (type(self), 0xb469544, state)
 * def __setstate_cython__(self, __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_unpickle_Edge__set_state(self, __pyx_state)
 */
  __pyx_tuple__7 = PyTuple_Pack(2, __pyx_n_s_self, __pyx_n_s_pyx_state); if (unlikely(!__pyx_tuple__7)) __PYX_ERR(1, 16, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__7);
  __Pyx_GIVEREF(__pyx_tuple__7);
  __pyx_codeobj__8 = (PyObject*)__Pyx_PyCode_New(2, 0, 2, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__7, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_stringsource, __pyx_n_s_setstate_cython, 16, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__8)) __PYX_ERR(1, 16, __pyx_L1_error)

  /* "fa2/fa2util.py":97
 * # adjust the dx and dy values of `n1` and `n2`.  It does
 * # not return anything.
 * def linAttraction(n1, n2, e, distributedAttraction, coefficient=0):             # <<<<<<<<<<<<<<
 *     xDist = n1.x - n2.x
 *     yDist = n1.y - n2.y
 */
  __pyx_tuple__9 = PyTuple_Pack(5, __pyx_n_s_n1, __pyx_n_s_n2, __pyx_n_s_e, __pyx_n_s_distributedAttraction, __pyx_n_s_coefficient); if (unlikely(!__pyx_tuple__9)) __PYX_ERR(2, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__9);
  __Pyx_GIVEREF(__pyx_tuple__9);
  __pyx_codeobj__10 = (PyObject*)__Pyx_PyCode_New(5, 0, 5, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__9, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_fa2util_py, __pyx_n_s_linAttraction, 97, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__10)) __PYX_ERR(2, 97, __pyx_L1_error)

  /* "fa2/fa2util.py":113
 * # the forces directly to the node objects.  These iterations are here
 * # instead of the main file because Python is slow with loops.
 * def apply_repulsion(nodes, coefficient):             # <<<<<<<<<<<<<<
 *     i = 0
 *     for n1 in nodes:
 */
  __pyx_tuple__11 = PyTuple_Pack(2, __pyx_n_s_nodes, __pyx_n_s_coefficient); if (unlikely(!__pyx_tuple__11)) __PYX_ERR(2, 113, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__11);
  __Pyx_GIVEREF(__pyx_tuple__11);
  __pyx_codeobj__12 = (PyObject*)__Pyx_PyCode_New(2, 0, 2, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__11, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_fa2util_py, __pyx_n_s_apply_repulsion, 113, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__12)) __PYX_ERR(2, 113, __pyx_L1_error)

  /* "fa2/fa2util.py":125
 * 
 * 
 * def apply_gravity(nodes, gravity, scalingRatio, useStrongGravity=False):             # <<<<<<<<<<<<<<
 *     if not useStrongGravity:
 *         for n in nodes:
 */
  __pyx_tuple__13 = PyTuple_Pack(4, __pyx_n_s_nodes, __pyx_n_s_gravity, __pyx_n_s_scalingRatio, __pyx_n_s_useStrongGravity); if (unlikely(!__pyx_tuple__13)) __PYX_ERR(2, 125, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__13);
  __Pyx_GIVEREF(__pyx_tuple__13);
  __pyx_codeobj__14 = (PyObject*)__Pyx_PyCode_New(4, 0, 4, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__13, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_fa2util_py, __pyx_n_s_apply_gravity, 125, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__14)) __PYX_ERR(2, 125, __pyx_L1_error)

  /* "fa2/fa2util.py":134
 * 
 * 
 * def apply_attraction(nodes, edges, distributedAttraction, coefficient, edgeWeightInfluence):             # <<<<<<<<<<<<<<
 *     # Optimization, since usually edgeWeightInfluence is 0 or 1, and pow is slow
 *     if edgeWeightInfluence == 0:
 */
  __pyx_tuple__15 = PyTuple_Pack(5, __pyx_n_s_nodes, __pyx_n_s_edges, __pyx_n_s_distributedAttraction, __pyx_n_s_coefficient, __pyx_n_s_edgeWeightInfluence); if (unlikely(!__pyx_tuple__15)) __PYX_ERR(2, 134, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__15);
  __Pyx_GIVEREF(__pyx_tuple__15);
  __pyx_codeobj__16 = (PyObject*)__Pyx_PyCode_New(5, 0, 5, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__15, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_fa2util_py, __pyx_n_s_apply_attraction, 134, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__16)) __PYX_ERR(2, 134, __pyx_L1_error)

  /* "fa2/fa2util.py":176
 *                 self.size = max(self.size, 2 * distance)
 * 
 *     def buildSubRegions(self):             # <<<<<<<<<<<<<<
 *         if len(self.nodes) > 1:
 *             topleftNodes = []
 */
  __pyx_tuple__17 = PyTuple_Pack(1, __pyx_n_s_self); if (unlikely(!__pyx_tuple__17)) __PYX_ERR(2, 176, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__17);
  __Pyx_GIVEREF(__pyx_tuple__17);
  __pyx_codeobj__18 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__17, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_fa2util_py, __pyx_n_s_buildSubRegions, 176, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__18)) __PYX_ERR(2, 176, __pyx_L1_error)

  /* "fa2/fa2util.py":247
 *                     subregion.applyForce(n, theta, coefficient)
 * 
 *     def applyForceOnNodes(self, nodes, theta, coefficient=0):             # <<<<<<<<<<<<<<
 *         for n in nodes:
 *             self.applyForce(n, theta, coefficient)
 */
  __pyx_tuple__19 = PyTuple_Pack(4, __pyx_n_s_self, __pyx_n_s_nodes, __pyx_n_s_theta, __pyx_n_s_coefficient); if (unlikely(!__pyx_tuple__19)) __PYX_ERR(2, 247, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__19);
  __Pyx_GIVEREF(__pyx_tuple__19);
  __pyx_codeobj__20 = (PyObject*)__Pyx_PyCode_New(4, 0, 4, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__19, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_fa2util_py, __pyx_n_s_applyForceOnNodes, 247, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__20)) __PYX_ERR(2, 247, __pyx_L1_error)

  /* "(tree fragment)":1
 * def __reduce_cython__(self):             # <<<<<<<<<<<<<<
 *     cdef tuple state
 *     cdef object _dict
 */
  __pyx_tuple__21 = PyTuple_Pack(4, __pyx_n_s_self, __pyx_n_s_state, __pyx_n_s_dict_2, __pyx_n_s_use_setstate); if (unlikely(!__pyx_tuple__21)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__21);
  __Pyx_GIVEREF(__pyx_tuple__21);
  __pyx_codeobj__22 = (PyObject*)__Pyx_PyCode_New(1, 0, 4, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__21, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_stringsource, __pyx_n_s_reduce_cython, 1, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__22)) __PYX_ERR(1, 1, __pyx_L1_error)

  /* "(tree fragment)":16
 *     else:
 *         return __pyx_unpickle_Region, (type(self), 0x66ef4c7, state)
 * def __setstate_cython__(self, __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_unpickle_Region__set_state(self, __pyx_state)
 */
  __pyx_tuple__23 = PyTuple_Pack(2, __pyx_n_s_self, __pyx_n_s_pyx_state); if (unlikely(!__pyx_tuple__23)) __PYX_ERR(1, 16, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__23);
  __Pyx_GIVEREF(__pyx_tuple__23);
  __pyx_codeobj__24 = (PyObject*)__Pyx_PyCode_New(2, 0, 2, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__23, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_stringsource, __pyx_n_s_setstate_cython, 16, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__24)) __PYX_ERR(1, 16, __pyx_L1_error)

  /* "fa2/fa2util.py":253
 * 
 * # Adjust speed and apply forces step
 * def adjustSpeedAndApplyForces(nodes, speed, speedEfficiency, jitterTolerance):             # <<<<<<<<<<<<<<
 *     # Auto adjust speed.
 *     totalSwinging = 0.0  # How much irregular movement
 */
  __pyx_tuple__25 = PyTuple_Pack(4, __pyx_n_s_nodes, __pyx_n_s_speed, __pyx_n_s_speedEfficiency, __pyx_n_s_jitterTolerance); if (unlikely(!__pyx_tuple__25)) __PYX_ERR(2, 253, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__25);
  __Pyx_GIVEREF(__pyx_tuple__25);
  __pyx_codeobj__26 = (PyObject*)__Pyx_PyCode_New(4, 0, 4, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__25, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_fa2util_py, __pyx_n_s_adjustSpeedAndApplyForces, 253, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__26)) __PYX_ERR(2, 253, __pyx_L1_error)

  /* "(tree fragment)":1
 * def __pyx_unpickle_Node(__pyx_type, long __pyx_checksum, __pyx_state):             # <<<<<<<<<<<<<<
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 */
  __pyx_tuple__27 = PyTuple_Pack(5, __pyx_n_s_pyx_type, __pyx_n_s_pyx_checksum, __pyx_n_s_pyx_state, __pyx_n_s_pyx_PickleError, __pyx_n_s_pyx_result); if (unlikely(!__pyx_tuple__27)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__27);
  __Pyx_GIVEREF(__pyx_tuple__27);
  __pyx_codeobj__28 = (PyObject*)__Pyx_PyCode_New(3, 0, 5, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__27, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_stringsource, __pyx_n_s_pyx_unpickle_Node, 1, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__28)) __PYX_ERR(1, 1, __pyx_L1_error)
  __pyx_tuple__29 = PyTuple_Pack(5, __pyx_n_s_pyx_type, __pyx_n_s_pyx_checksum, __pyx_n_s_pyx_state, __pyx_n_s_pyx_PickleError, __pyx_n_s_pyx_result); if (unlikely(!__pyx_tuple__29)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__29);
  __Pyx_GIVEREF(__pyx_tuple__29);
  __pyx_codeobj__30 = (PyObject*)__Pyx_PyCode_New(3, 0, 5, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__29, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_stringsource, __pyx_n_s_pyx_unpickle_Edge, 1, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__30)) __PYX_ERR(1, 1, __pyx_L1_error)
  __pyx_tuple__31 = PyTuple_Pack(5, __pyx_n_s_pyx_type, __pyx_n_s_pyx_checksum, __pyx_n_s_pyx_state, __pyx_n_s_pyx_PickleError, __pyx_n_s_pyx_result); if (unlikely(!__pyx_tuple__31)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__31);
  __Pyx_GIVEREF(__pyx_tuple__31);
  __pyx_codeobj__32 = (PyObject*)__Pyx_PyCode_New(3, 0, 5, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__31, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_stringsource, __pyx_n_s_pyx_unpickle_Region, 1, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__32)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static CYTHON_SMALL_CODE int __Pyx_InitGlobals(void) {
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) __PYX_ERR(2, 1, __pyx_L1_error);
  __pyx_float__05 = PyFloat_FromDouble(.05); if (unlikely(!__pyx_float__05)) __PYX_ERR(2, 1, __pyx_L1_error)
  __pyx_float_1_0 = PyFloat_FromDouble(1.0); if (unlikely(!__pyx_float_1_0)) __PYX_ERR(2, 1, __pyx_L1_error)
  __pyx_int_49427421 = PyInt_FromLong(49427421L); if (unlikely(!__pyx_int_49427421)) __PYX_ERR(2, 1, __pyx_L1_error)
  __pyx_int_107934919 = PyInt_FromLong(107934919L); if (unlikely(!__pyx_int_107934919)) __PYX_ERR(2, 1, __pyx_L1_error)
  __pyx_int_189175108 = PyInt_FromLong(189175108L); if (unlikely(!__pyx_int_189175108)) __PYX_ERR(2, 1, __pyx_L1_error)
  return 0;
  __pyx_L1_error:;
  return -1;
}

static CYTHON_SMALL_CODE int __Pyx_modinit_global_init_code(void); /*proto*/
static CYTHON_SMALL_CODE int __Pyx_modinit_variable_export_code(void); /*proto*/
static CYTHON_SMALL_CODE int __Pyx_modinit_function_export_code(void); /*proto*/
static CYTHON_SMALL_CODE int __Pyx_modinit_type_init_code(void); /*proto*/
static CYTHON_SMALL_CODE int __Pyx_modinit_type_import_code(void); /*proto*/
static CYTHON_SMALL_CODE int __Pyx_modinit_variable_import_code(void); /*proto*/
static CYTHON_SMALL_CODE int __Pyx_modinit_function_import_code(void); /*proto*/

static int __Pyx_modinit_global_init_code(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_modinit_global_init_code", 0);
  /*--- Global init code ---*/
  __Pyx_RefNannyFinishContext();
  return 0;
}

static int __Pyx_modinit_variable_export_code(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_modinit_variable_export_code", 0);
  /*--- Variable export code ---*/
  __Pyx_RefNannyFinishContext();
  return 0;
}

static int __Pyx_modinit_function_export_code(void) {
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__Pyx_modinit_function_export_code", 0);
  /*--- Function export code ---*/
  if (__Pyx_ExportFunction("linRepulsion", (void (*)(void))__pyx_f_3fa2_7fa2util_linRepulsion, "void (struct __pyx_obj_3fa2_7fa2util_Node *, struct __pyx_obj_3fa2_7fa2util_Node *, struct __pyx_opt_args_3fa2_7fa2util_linRepulsion *__pyx_optional_args)") < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  if (__Pyx_ExportFunction("linRepulsion_region", (void (*)(void))__pyx_f_3fa2_7fa2util_linRepulsion_region, "void (struct __pyx_obj_3fa2_7fa2util_Node *, struct __pyx_obj_3fa2_7fa2util_Region *, struct __pyx_opt_args_3fa2_7fa2util_linRepulsion_region *__pyx_optional_args)") < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  if (__Pyx_ExportFunction("linGravity", (void (*)(void))__pyx_f_3fa2_7fa2util_linGravity, "void (struct __pyx_obj_3fa2_7fa2util_Node *, double)") < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  if (__Pyx_ExportFunction("strongGravity", (void (*)(void))__pyx_f_3fa2_7fa2util_strongGravity, "void (struct __pyx_obj_3fa2_7fa2util_Node *, double, struct __pyx_opt_args_3fa2_7fa2util_strongGravity *__pyx_optional_args)") < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  if (__Pyx_ExportFunction("linAttraction", (void (*)(void))__pyx_f_3fa2_7fa2util_linAttraction, "void (struct __pyx_obj_3fa2_7fa2util_Node *, struct __pyx_obj_3fa2_7fa2util_Node *, double, int, int __pyx_skip_dispatch, struct __pyx_opt_args_3fa2_7fa2util_linAttraction *__pyx_optional_args)") < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  if (__Pyx_ExportFunction("apply_repulsion", (void (*)(void))__pyx_f_3fa2_7fa2util_apply_repulsion, "void (PyObject *, double, int __pyx_skip_dispatch)") < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  if (__Pyx_ExportFunction("apply_gravity", (void (*)(void))__pyx_f_3fa2_7fa2util_apply_gravity, "void (PyObject *, double, double, int __pyx_skip_dispatch, struct __pyx_opt_args_3fa2_7fa2util_apply_gravity *__pyx_optional_args)") < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  if (__Pyx_ExportFunction("apply_attraction", (void (*)(void))__pyx_f_3fa2_7fa2util_apply_attraction, "void (PyObject *, PyObject *, int, double, double, int __pyx_skip_dispatch)") < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  if (__Pyx_ExportFunction("adjustSpeedAndApplyForces", (void (*)(void))__pyx_f_3fa2_7fa2util_adjustSpeedAndApplyForces, "PyObject *(PyObject *, double, double, double, int __pyx_skip_dispatch)") < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_modinit_type_init_code(void) {
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__Pyx_modinit_type_init_code", 0);
  /*--- Type init code ---*/
  if (PyType_Ready(&__pyx_type_3fa2_7fa2util_Node) < 0) __PYX_ERR(2, 17, __pyx_L1_error)
  #if PY_VERSION_HEX < 0x030800B1
  __pyx_type_3fa2_7fa2util_Node.tp_print = 0;
  #endif
  if ((CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP) && likely(!__pyx_type_3fa2_7fa2util_Node.tp_dictoffset && __pyx_type_3fa2_7fa2util_Node.tp_getattro == PyObject_GenericGetAttr)) {
    __pyx_type_3fa2_7fa2util_Node.tp_getattro = __Pyx_PyObject_GenericGetAttr;
  }
  if (PyObject_SetAttr(__pyx_m, __pyx_n_s_Node, (PyObject *)&__pyx_type_3fa2_7fa2util_Node) < 0) __PYX_ERR(2, 17, __pyx_L1_error)
  if (__Pyx_setup_reduce((PyObject*)&__pyx_type_3fa2_7fa2util_Node) < 0) __PYX_ERR(2, 17, __pyx_L1_error)
  __pyx_ptype_3fa2_7fa2util_Node = &__pyx_type_3fa2_7fa2util_Node;
  if (PyType_Ready(&__pyx_type_3fa2_7fa2util_Edge) < 0) __PYX_ERR(2, 29, __pyx_L1_error)
  #if PY_VERSION_HEX < 0x030800B1
  __pyx_type_3fa2_7fa2util_Edge.tp_print = 0;
  #endif
  if ((CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP) && likely(!__pyx_type_3fa2_7fa2util_Edge.tp_dictoffset && __pyx_type_3fa2_7fa2util_Edge.tp_getattro == PyObject_GenericGetAttr)) {
    __pyx_type_3fa2_7fa2util_Edge.tp_getattro = __Pyx_PyObject_GenericGetAttr;
  }
  if (PyObject_SetAttr(__pyx_m, __pyx_n_s_Edge, (PyObject *)&__pyx_type_3fa2_7fa2util_Edge) < 0) __PYX_ERR(2, 29, __pyx_L1_error)
  if (__Pyx_setup_reduce((PyObject*)&__pyx_type_3fa2_7fa2util_Edge) < 0) __PYX_ERR(2, 29, __pyx_L1_error)
  __pyx_ptype_3fa2_7fa2util_Edge = &__pyx_type_3fa2_7fa2util_Edge;
  __pyx_vtabptr_3fa2_7fa2util_Region = &__pyx_vtable_3fa2_7fa2util_Region;
  __pyx_vtable_3fa2_7fa2util_Region.updateMassAndGeometry = (void (*)(struct __pyx_obj_3fa2_7fa2util_Region *))__pyx_f_3fa2_7fa2util_6Region_updateMassAndGeometry;
  __pyx_vtable_3fa2_7fa2util_Region.buildSubRegions = (void (*)(struct __pyx_obj_3fa2_7fa2util_Region *, int __pyx_skip_dispatch))__pyx_f_3fa2_7fa2util_6Region_buildSubRegions;
  __pyx_vtable_3fa2_7fa2util_Region.applyForce = (void (*)(struct __pyx_obj_3fa2_7fa2util_Region *, struct __pyx_obj_3fa2_7fa2util_Node *, double, struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForce *__pyx_optional_args))__pyx_f_3fa2_7fa2util_6Region_applyForce;
  __pyx_vtable_3fa2_7fa2util_Region.applyForceOnNodes = (PyObject *(*)(struct __pyx_obj_3fa2_7fa2util_Region *, PyObject *, double, int __pyx_skip_dispatch, struct __pyx_opt_args_3fa2_7fa2util_6Region_applyForceOnNodes *__pyx_optional_args))__pyx_f_3fa2_7fa2util_6Region_applyForceOnNodes;
  if (PyType_Ready(&__pyx_type_3fa2_7fa2util_Region) < 0) __PYX_ERR(2, 149, __pyx_L1_error)
  #if PY_VERSION_HEX < 0x030800B1
  __pyx_type_3fa2_7fa2util_Region.tp_print = 0;
  #endif
  if ((CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP) && likely(!__pyx_type_3fa2_7fa2util_Region.tp_dictoffset && __pyx_type_3fa2_7fa2util_Region.tp_getattro == PyObject_GenericGetAttr)) {
    __pyx_type_3fa2_7fa2util_Region.tp_getattro = __Pyx_PyObject_GenericGetAttr;
  }
  if (__Pyx_SetVtable(__pyx_type_3fa2_7fa2util_Region.tp_dict, __pyx_vtabptr_3fa2_7fa2util_Region) < 0) __PYX_ERR(2, 149, __pyx_L1_error)
  if (PyObject_SetAttr(__pyx_m, __pyx_n_s_Region, (PyObject *)&__pyx_type_3fa2_7fa2util_Region) < 0) __PYX_ERR(2, 149, __pyx_L1_error)
  if (__Pyx_setup_reduce((PyObject*)&__pyx_type_3fa2_7fa2util_Region) < 0) __PYX_ERR(2, 149, __pyx_L1_error)
  __pyx_ptype_3fa2_7fa2util_Region = &__pyx_type_3fa2_7fa2util_Region;
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_modinit_type_import_code(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_modinit_type_import_code", 0);
  /*--- Type import code ---*/
  __Pyx_RefNannyFinishContext();
  return 0;
}

static int __Pyx_modinit_variable_import_code(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_modinit_variable_import_code", 0);
  /*--- Variable import code ---*/
  __Pyx_RefNannyFinishContext();
  return 0;
}

static int __Pyx_modinit_function_import_code(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_modinit_function_import_code", 0);
  /*--- Function import code ---*/
  __Pyx_RefNannyFinishContext();
  return 0;
}


#ifndef CYTHON_NO_PYINIT_EXPORT
#define __Pyx_PyMODINIT_FUNC PyMODINIT_FUNC
#elif PY_MAJOR_VERSION < 3
#ifdef __cplusplus
#define __Pyx_PyMODINIT_FUNC extern "C" void
#else
#define __Pyx_PyMODINIT_FUNC void
#endif
#else
#ifdef __cplusplus
#define __Pyx_PyMODINIT_FUNC extern "C" PyObject *
#else
#define __Pyx_PyMODINIT_FUNC PyObject *
#endif
#endif


#if PY_MAJOR_VERSION < 3
__Pyx_PyMODINIT_FUNC initfa2util(void) CYTHON_SMALL_CODE; /*proto*/
__Pyx_PyMODINIT_FUNC initfa2util(void)
#else
__Pyx_PyMODINIT_FUNC PyInit_fa2util(void) CYTHON_SMALL_CODE; /*proto*/
__Pyx_PyMODINIT_FUNC PyInit_fa2util(void)
#if CYTHON_PEP489_MULTI_PHASE_INIT
{
  return PyModuleDef_Init(&__pyx_moduledef);
}
static CYTHON_SMALL_CODE int __Pyx_check_single_interpreter(void) {
    #if PY_VERSION_HEX >= 0x030700A1
    static PY_INT64_T main_interpreter_id = -1;
    PY_INT64_T current_id = PyInterpreterState_GetID(PyThreadState_Get()->interp);
    if (main_interpreter_id == -1) {
        main_interpreter_id = current_id;
        return (unlikely(current_id == -1)) ? -1 : 0;
    } else if (unlikely(main_interpreter_id != current_id))
    #else
    static PyInterpreterState *main_interpreter = NULL;
    PyInterpreterState *current_interpreter = PyThreadState_Get()->interp;
    if (!main_interpreter) {
        main_interpreter = current_interpreter;
    } else if (unlikely(main_interpreter != current_interpreter))
    #endif
    {
        PyErr_SetString(
            PyExc_ImportError,
            "Interpreter change detected - this module can only be loaded into one interpreter per process.");
        return -1;
    }
    return 0;
}
static CYTHON_SMALL_CODE int __Pyx_copy_spec_to_module(PyObject *spec, PyObject *moddict, const char* from_name, const char* to_name, int allow_none) {
    PyObject *value = PyObject_GetAttrString(spec, from_name);
    int result = 0;
    if (likely(value)) {
        if (allow_none || value != Py_None) {
            result = PyDict_SetItemString(moddict, to_name, value);
        }
        Py_DECREF(value);
    } else if (PyErr_ExceptionMatches(PyExc_AttributeError)) {
        PyErr_Clear();
    } else {
        result = -1;
    }
    return result;
}
static CYTHON_SMALL_CODE PyObject* __pyx_pymod_create(PyObject *spec, CYTHON_UNUSED PyModuleDef *def) {
    PyObject *module = NULL, *moddict, *modname;
    if (__Pyx_check_single_interpreter())
        return NULL;
    if (__pyx_m)
        return __Pyx_NewRef(__pyx_m);
    modname = PyObject_GetAttrString(spec, "name");
    if (unlikely(!modname)) goto bad;
    module = PyModule_NewObject(modname);
    Py_DECREF(modname);
    if (unlikely(!module)) goto bad;
    moddict = PyModule_GetDict(module);
    if (unlikely(!moddict)) goto bad;
    if (unlikely(__Pyx_copy_spec_to_module(spec, moddict, "loader", "__loader__", 1) < 0)) goto bad;
    if (unlikely(__Pyx_copy_spec_to_module(spec, moddict, "origin", "__file__", 1) < 0)) goto bad;
    if (unlikely(__Pyx_copy_spec_to_module(spec, moddict, "parent", "__package__", 1) < 0)) goto bad;
    if (unlikely(__Pyx_copy_spec_to_module(spec, moddict, "submodule_search_locations", "__path__", 0) < 0)) goto bad;
    return module;
bad:
    Py_XDECREF(module);
    return NULL;
}


static CYTHON_SMALL_CODE int __pyx_pymod_exec_fa2util(PyObject *__pyx_pyinit_module)
#endif
#endif
{
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannyDeclarations
  #if CYTHON_PEP489_MULTI_PHASE_INIT
  if (__pyx_m) {
    if (__pyx_m == __pyx_pyinit_module) return 0;
    PyErr_SetString(PyExc_RuntimeError, "Module 'fa2util' has already been imported. Re-initialisation is not supported.");
    return -1;
  }
  #elif PY_MAJOR_VERSION >= 3
  if (__pyx_m) return __Pyx_NewRef(__pyx_m);
  #endif
  #if CYTHON_REFNANNY
__Pyx_RefNanny = __Pyx_RefNannyImportAPI("refnanny");
if (!__Pyx_RefNanny) {
  PyErr_Clear();
  __Pyx_RefNanny = __Pyx_RefNannyImportAPI("Cython.Runtime.refnanny");
  if (!__Pyx_RefNanny)
      Py_FatalError("failed to import 'refnanny' module");
}
#endif
  __Pyx_RefNannySetupContext("__Pyx_PyMODINIT_FUNC PyInit_fa2util(void)", 0);
  if (__Pyx_check_binary_version() < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  #ifdef __Pxy_PyFrame_Initialize_Offsets
  __Pxy_PyFrame_Initialize_Offsets();
  #endif
  __pyx_empty_tuple = PyTuple_New(0); if (unlikely(!__pyx_empty_tuple)) __PYX_ERR(2, 1, __pyx_L1_error)
  __pyx_empty_bytes = PyBytes_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_bytes)) __PYX_ERR(2, 1, __pyx_L1_error)
  __pyx_empty_unicode = PyUnicode_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_unicode)) __PYX_ERR(2, 1, __pyx_L1_error)
  #ifdef __Pyx_CyFunction_USED
  if (__pyx_CyFunction_init() < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_FusedFunction_USED
  if (__pyx_FusedFunction_init() < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_Coroutine_USED
  if (__pyx_Coroutine_init() < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_Generator_USED
  if (__pyx_Generator_init() < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_AsyncGen_USED
  if (__pyx_AsyncGen_init() < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_StopAsyncIteration_USED
  if (__pyx_StopAsyncIteration_init() < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  #endif
  /*--- Library function declarations ---*/
  /*--- Threads initialization code ---*/
  #if defined(__PYX_FORCE_INIT_THREADS) && __PYX_FORCE_INIT_THREADS
  #ifdef WITH_THREAD /* Python build with threading support? */
  PyEval_InitThreads();
  #endif
  #endif
  /*--- Module creation code ---*/
  #if CYTHON_PEP489_MULTI_PHASE_INIT
  __pyx_m = __pyx_pyinit_module;
  Py_INCREF(__pyx_m);
  #else
  #if PY_MAJOR_VERSION < 3
  __pyx_m = Py_InitModule4("fa2util", __pyx_methods, 0, 0, PYTHON_API_VERSION); Py_XINCREF(__pyx_m);
  #else
  __pyx_m = PyModule_Create(&__pyx_moduledef);
  #endif
  if (unlikely(!__pyx_m)) __PYX_ERR(2, 1, __pyx_L1_error)
  #endif
  __pyx_d = PyModule_GetDict(__pyx_m); if (unlikely(!__pyx_d)) __PYX_ERR(2, 1, __pyx_L1_error)
  Py_INCREF(__pyx_d);
  __pyx_b = PyImport_AddModule(__Pyx_BUILTIN_MODULE_NAME); if (unlikely(!__pyx_b)) __PYX_ERR(2, 1, __pyx_L1_error)
  Py_INCREF(__pyx_b);
  __pyx_cython_runtime = PyImport_AddModule((char *) "cython_runtime"); if (unlikely(!__pyx_cython_runtime)) __PYX_ERR(2, 1, __pyx_L1_error)
  Py_INCREF(__pyx_cython_runtime);
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) __PYX_ERR(2, 1, __pyx_L1_error);
  /*--- Initialize various global constants etc. ---*/
  if (__Pyx_InitGlobals() < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  #if PY_MAJOR_VERSION < 3 && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
  if (__Pyx_init_sys_getdefaultencoding_params() < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  #endif
  if (__pyx_module_is_main_fa2__fa2util) {
    if (PyObject_SetAttr(__pyx_m, __pyx_n_s_name, __pyx_n_s_main) < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  }
  #if PY_MAJOR_VERSION >= 3
  {
    PyObject *modules = PyImport_GetModuleDict(); if (unlikely(!modules)) __PYX_ERR(2, 1, __pyx_L1_error)
    if (!PyDict_GetItemString(modules, "fa2.fa2util")) {
      if (unlikely(PyDict_SetItemString(modules, "fa2.fa2util", __pyx_m) < 0)) __PYX_ERR(2, 1, __pyx_L1_error)
    }
  }
  #endif
  /*--- Builtin init code ---*/
  if (__Pyx_InitCachedBuiltins() < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  /*--- Constants init code ---*/
  if (__Pyx_InitCachedConstants() < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  /*--- Global type/function init code ---*/
  (void)__Pyx_modinit_global_init_code();
  (void)__Pyx_modinit_variable_export_code();
  if (unlikely(__Pyx_modinit_function_export_code() < 0)) __PYX_ERR(2, 1, __pyx_L1_error)
  if (unlikely(__Pyx_modinit_type_init_code() < 0)) __PYX_ERR(2, 1, __pyx_L1_error)
  (void)__Pyx_modinit_type_import_code();
  (void)__Pyx_modinit_variable_import_code();
  (void)__Pyx_modinit_function_import_code();
  /*--- Execution code ---*/
  #if defined(__Pyx_Generator_USED) || defined(__Pyx_Coroutine_USED)
  if (__Pyx_patch_abc() < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  #endif

  /* "fa2/fa2util.py":13
 * # Available under the GPLv3
 * 
 * from math import sqrt             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_t_1 = PyList_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 13, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_sqrt);
  __Pyx_GIVEREF(__pyx_n_s_sqrt);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_sqrt);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_math, __pyx_t_1, -1); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 13, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_sqrt); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 13, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_sqrt, __pyx_t_1) < 0) __PYX_ERR(2, 13, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "(tree fragment)":1
 * def __reduce_cython__(self):             # <<<<<<<<<<<<<<
 *     cdef tuple state
 *     cdef object _dict
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_4Node_3__reduce_cython__, __Pyx_CYFUNCTION_CCLASS, __pyx_n_s_Node___reduce_cython, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__2)); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem((PyObject *)__pyx_ptype_3fa2_7fa2util_Node->tp_dict, __pyx_n_s_reduce_cython, __pyx_t_2) < 0) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  PyType_Modified(__pyx_ptype_3fa2_7fa2util_Node);

  /* "(tree fragment)":16
 *     else:
 *         return __pyx_unpickle_Node, (type(self), 0x2f233dd, state)
 * def __setstate_cython__(self, __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_unpickle_Node__set_state(self, __pyx_state)
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_4Node_5__setstate_cython__, __Pyx_CYFUNCTION_CCLASS, __pyx_n_s_Node___setstate_cython, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__4)); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 16, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem((PyObject *)__pyx_ptype_3fa2_7fa2util_Node->tp_dict, __pyx_n_s_setstate_cython, __pyx_t_2) < 0) __PYX_ERR(1, 16, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  PyType_Modified(__pyx_ptype_3fa2_7fa2util_Node);

  /* "(tree fragment)":1
 * def __reduce_cython__(self):             # <<<<<<<<<<<<<<
 *     cdef tuple state
 *     cdef object _dict
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_4Edge_3__reduce_cython__, __Pyx_CYFUNCTION_CCLASS, __pyx_n_s_Edge___reduce_cython, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__6)); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem((PyObject *)__pyx_ptype_3fa2_7fa2util_Edge->tp_dict, __pyx_n_s_reduce_cython, __pyx_t_2) < 0) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  PyType_Modified(__pyx_ptype_3fa2_7fa2util_Edge);

  /* "(tree fragment)":16
 *     else:
 *         return __pyx_unpickle_Edge, (type(self), 0xb469544, state)
 * def __setstate_cython__(self, __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_unpickle_Edge__set_state(self, __pyx_state)
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_4Edge_5__setstate_cython__, __Pyx_CYFUNCTION_CCLASS, __pyx_n_s_Edge___setstate_cython, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__8)); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 16, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem((PyObject *)__pyx_ptype_3fa2_7fa2util_Edge->tp_dict, __pyx_n_s_setstate_cython, __pyx_t_2) < 0) __PYX_ERR(1, 16, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  PyType_Modified(__pyx_ptype_3fa2_7fa2util_Edge);

  /* "fa2/fa2util.py":97
 * # adjust the dx and dy values of `n1` and `n2`.  It does
 * # not return anything.
 * def linAttraction(n1, n2, e, distributedAttraction, coefficient=0):             # <<<<<<<<<<<<<<
 *     xDist = n1.x - n2.x
 *     yDist = n1.y - n2.y
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_1linAttraction, 0, __pyx_n_s_linAttraction, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__10)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_linAttraction, __pyx_t_2) < 0) __PYX_ERR(2, 97, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "fa2/fa2util.py":113
 * # the forces directly to the node objects.  These iterations are here
 * # instead of the main file because Python is slow with loops.
 * def apply_repulsion(nodes, coefficient):             # <<<<<<<<<<<<<<
 *     i = 0
 *     for n1 in nodes:
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_3apply_repulsion, 0, __pyx_n_s_apply_repulsion, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__12)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 113, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_apply_repulsion, __pyx_t_2) < 0) __PYX_ERR(2, 113, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "fa2/fa2util.py":125
 * 
 * 
 * def apply_gravity(nodes, gravity, scalingRatio, useStrongGravity=False):             # <<<<<<<<<<<<<<
 *     if not useStrongGravity:
 *         for n in nodes:
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_5apply_gravity, 0, __pyx_n_s_apply_gravity, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__14)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 125, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_apply_gravity, __pyx_t_2) < 0) __PYX_ERR(2, 125, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "fa2/fa2util.py":134
 * 
 * 
 * def apply_attraction(nodes, edges, distributedAttraction, coefficient, edgeWeightInfluence):             # <<<<<<<<<<<<<<
 *     # Optimization, since usually edgeWeightInfluence is 0 or 1, and pow is slow
 *     if edgeWeightInfluence == 0:
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_7apply_attraction, 0, __pyx_n_s_apply_attraction, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__16)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 134, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_apply_attraction, __pyx_t_2) < 0) __PYX_ERR(2, 134, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "fa2/fa2util.py":176
 *                 self.size = max(self.size, 2 * distance)
 * 
 *     def buildSubRegions(self):             # <<<<<<<<<<<<<<
 *         if len(self.nodes) > 1:
 *             topleftNodes = []
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_6Region_3buildSubRegions, __Pyx_CYFUNCTION_CCLASS, __pyx_n_s_Region_buildSubRegions, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__18)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 176, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem((PyObject *)__pyx_ptype_3fa2_7fa2util_Region->tp_dict, __pyx_n_s_buildSubRegions, __pyx_t_2) < 0) __PYX_ERR(2, 176, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  PyType_Modified(__pyx_ptype_3fa2_7fa2util_Region);

  /* "fa2/fa2util.py":247
 *                     subregion.applyForce(n, theta, coefficient)
 * 
 *     def applyForceOnNodes(self, nodes, theta, coefficient=0):             # <<<<<<<<<<<<<<
 *         for n in nodes:
 *             self.applyForce(n, theta, coefficient)
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_6Region_5applyForceOnNodes, __Pyx_CYFUNCTION_CCLASS, __pyx_n_s_Region_applyForceOnNodes, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__20)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 247, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem((PyObject *)__pyx_ptype_3fa2_7fa2util_Region->tp_dict, __pyx_n_s_applyForceOnNodes, __pyx_t_2) < 0) __PYX_ERR(2, 247, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  PyType_Modified(__pyx_ptype_3fa2_7fa2util_Region);

  /* "(tree fragment)":1
 * def __reduce_cython__(self):             # <<<<<<<<<<<<<<
 *     cdef tuple state
 *     cdef object _dict
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_6Region_7__reduce_cython__, __Pyx_CYFUNCTION_CCLASS, __pyx_n_s_Region___reduce_cython, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__22)); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem((PyObject *)__pyx_ptype_3fa2_7fa2util_Region->tp_dict, __pyx_n_s_reduce_cython, __pyx_t_2) < 0) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  PyType_Modified(__pyx_ptype_3fa2_7fa2util_Region);

  /* "(tree fragment)":16
 *     else:
 *         return __pyx_unpickle_Region, (type(self), 0x66ef4c7, state)
 * def __setstate_cython__(self, __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_unpickle_Region__set_state(self, __pyx_state)
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_6Region_9__setstate_cython__, __Pyx_CYFUNCTION_CCLASS, __pyx_n_s_Region___setstate_cython, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__24)); if (unlikely(!__pyx_t_2)) __PYX_ERR(1, 16, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem((PyObject *)__pyx_ptype_3fa2_7fa2util_Region->tp_dict, __pyx_n_s_setstate_cython, __pyx_t_2) < 0) __PYX_ERR(1, 16, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  PyType_Modified(__pyx_ptype_3fa2_7fa2util_Region);

  /* "fa2/fa2util.py":253
 * 
 * # Adjust speed and apply forces step
 * def adjustSpeedAndApplyForces(nodes, speed, speedEfficiency, jitterTolerance):             # <<<<<<<<<<<<<<
 *     # Auto adjust speed.
 *     totalSwinging = 0.0  # How much irregular movement
 */
  __pyx_t_2 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_9adjustSpeedAndApplyForces, 0, __pyx_n_s_adjustSpeedAndApplyForces, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__26)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 253, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_adjustSpeedAndApplyForces, __pyx_t_2) < 0) __PYX_ERR(2, 253, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "fa2/fa2util.py":314
 * 
 * 
 * try:             # <<<<<<<<<<<<<<
 *     import cython
 * 
 */
  {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ExceptionSave(&__pyx_t_3, &__pyx_t_4, &__pyx_t_5);
    __Pyx_XGOTREF(__pyx_t_3);
    __Pyx_XGOTREF(__pyx_t_4);
    __Pyx_XGOTREF(__pyx_t_5);
    /*try:*/ {

      /* "fa2/fa2util.py":317
 *     import cython
 * 
 *     if not cython.compiled:             # <<<<<<<<<<<<<<
 *         print("Warning: uncompiled fa2util module.  Compile with cython for a 10-100x speed boost.")
 * except:
 */
      __pyx_t_6 = ((!(1 != 0)) != 0);
      if (__pyx_t_6) {

        /* "fa2/fa2util.py":318
 * 
 *     if not cython.compiled:
 *         print("Warning: uncompiled fa2util module.  Compile with cython for a 10-100x speed boost.")             # <<<<<<<<<<<<<<
 * except:
 *     print("No cython detected.  Install cython and compile the fa2util module for a 10-100x speed boost.")
 */
        if (__Pyx_PrintOne(0, __pyx_kp_s_Warning_uncompiled_fa2util_modul) < 0) __PYX_ERR(2, 318, __pyx_L2_error)

        /* "fa2/fa2util.py":317
 *     import cython
 * 
 *     if not cython.compiled:             # <<<<<<<<<<<<<<
 *         print("Warning: uncompiled fa2util module.  Compile with cython for a 10-100x speed boost.")
 * except:
 */
      }

      /* "fa2/fa2util.py":314
 * 
 * 
 * try:             # <<<<<<<<<<<<<<
 *     import cython
 * 
 */
    }
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    goto __pyx_L7_try_end;
    __pyx_L2_error:;
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "fa2/fa2util.py":319
 *     if not cython.compiled:
 *         print("Warning: uncompiled fa2util module.  Compile with cython for a 10-100x speed boost.")
 * except:             # <<<<<<<<<<<<<<
 *     print("No cython detected.  Install cython and compile the fa2util module for a 10-100x speed boost.")
 */
    /*except:*/ {
      __Pyx_AddTraceback("fa2.fa2util", __pyx_clineno, __pyx_lineno, __pyx_filename);
      if (__Pyx_GetException(&__pyx_t_2, &__pyx_t_1, &__pyx_t_7) < 0) __PYX_ERR(2, 319, __pyx_L4_except_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_GOTREF(__pyx_t_7);

      /* "fa2/fa2util.py":320
 *         print("Warning: uncompiled fa2util module.  Compile with cython for a 10-100x speed boost.")
 * except:
 *     print("No cython detected.  Install cython and compile the fa2util module for a 10-100x speed boost.")             # <<<<<<<<<<<<<<
 */
      if (__Pyx_PrintOne(0, __pyx_kp_s_No_cython_detected_Install_cytho) < 0) __PYX_ERR(2, 320, __pyx_L4_except_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
      goto __pyx_L3_exception_handled;
    }
    __pyx_L4_except_error:;

    /* "fa2/fa2util.py":314
 * 
 * 
 * try:             # <<<<<<<<<<<<<<
 *     import cython
 * 
 */
    __Pyx_XGIVEREF(__pyx_t_3);
    __Pyx_XGIVEREF(__pyx_t_4);
    __Pyx_XGIVEREF(__pyx_t_5);
    __Pyx_ExceptionReset(__pyx_t_3, __pyx_t_4, __pyx_t_5);
    goto __pyx_L1_error;
    __pyx_L3_exception_handled:;
    __Pyx_XGIVEREF(__pyx_t_3);
    __Pyx_XGIVEREF(__pyx_t_4);
    __Pyx_XGIVEREF(__pyx_t_5);
    __Pyx_ExceptionReset(__pyx_t_3, __pyx_t_4, __pyx_t_5);
    __pyx_L7_try_end:;
  }

  /* "(tree fragment)":1
 * def __pyx_unpickle_Node(__pyx_type, long __pyx_checksum, __pyx_state):             # <<<<<<<<<<<<<<
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 */
  __pyx_t_7 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_11__pyx_unpickle_Node, 0, __pyx_n_s_pyx_unpickle_Node, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__28)); if (unlikely(!__pyx_t_7)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_pyx_unpickle_Node, __pyx_t_7) < 0) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

  /* "(tree fragment)":11
 *         __pyx_unpickle_Node__set_state(<Node> __pyx_result, __pyx_state)
 *     return __pyx_result
 * cdef __pyx_unpickle_Node__set_state(Node __pyx_result, tuple __pyx_state):             # <<<<<<<<<<<<<<
 *     __pyx_result.dx = __pyx_state[0]; __pyx_result.dy = __pyx_state[1]; __pyx_result.mass = __pyx_state[2]; __pyx_result.old_dx = __pyx_state[3]; __pyx_result.old_dy = __pyx_state[4]; __pyx_result.x = __pyx_state[5]; __pyx_result.y = __pyx_state[6]
 *     if len(__pyx_state) > 7 and hasattr(__pyx_result, '__dict__'):
 */
  __pyx_t_7 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_13__pyx_unpickle_Edge, 0, __pyx_n_s_pyx_unpickle_Edge, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__30)); if (unlikely(!__pyx_t_7)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_pyx_unpickle_Edge, __pyx_t_7) < 0) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

  /* "(tree fragment)":1
 * def __pyx_unpickle_Region(__pyx_type, long __pyx_checksum, __pyx_state):             # <<<<<<<<<<<<<<
 *     cdef object __pyx_PickleError
 *     cdef object __pyx_result
 */
  __pyx_t_7 = __Pyx_CyFunction_New(&__pyx_mdef_3fa2_7fa2util_15__pyx_unpickle_Region, 0, __pyx_n_s_pyx_unpickle_Region, NULL, __pyx_n_s_fa2_fa2util, __pyx_d, ((PyObject *)__pyx_codeobj__32)); if (unlikely(!__pyx_t_7)) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_pyx_unpickle_Region, __pyx_t_7) < 0) __PYX_ERR(1, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

  /* "fa2/fa2util.py":1
 * # This file allows separating the most CPU intensive routines from the             # <<<<<<<<<<<<<<
 * # main code.  This allows them to be optimized with Cython.  If you
 * # don't have Cython, this will run normally.  However, if you use
 */
  __pyx_t_7 = __Pyx_PyDict_NewPresized(0); if (unlikely(!__pyx_t_7)) __PYX_ERR(2, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_test, __pyx_t_7) < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

  /*--- Wrapped vars code ---*/

  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_7);
  if (__pyx_m) {
    if (__pyx_d) {
      __Pyx_AddTraceback("init fa2.fa2util", __pyx_clineno, __pyx_lineno, __pyx_filename);
    }
    Py_CLEAR(__pyx_m);
  } else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_ImportError, "init fa2.fa2util");
  }
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  #if CYTHON_PEP489_MULTI_PHASE_INIT
  return (__pyx_m != NULL) ? 0 : -1;
  #elif PY_MAJOR_VERSION >= 3
  return __pyx_m;
  #else
  return;
  #endif
}

/* --- Runtime support code --- */
/* Refnanny */
#if CYTHON_REFNANNY
static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname) {
    PyObject *m = NULL, *p = NULL;
    void *r = NULL;
    m = PyImport_ImportModule(modname);
    if (!m) goto end;
    p = PyObject_GetAttrString(m, "RefNannyAPI");
    if (!p) goto end;
    r = PyLong_AsVoidPtr(p);
end:
    Py_XDECREF(p);
    Py_XDECREF(m);
    return (__Pyx_RefNannyAPIStruct *)r;
}
#endif

/* RaiseArgTupleInvalid */
static void __Pyx_RaiseArgtupleInvalid(
    const char* func_name,
    int exact,
    Py_ssize_t num_min,
    Py_ssize_t num_max,
    Py_ssize_t num_found)
{
    Py_ssize_t num_expected;
    const char *more_or_less;
    if (num_found < num_min) {
        num_expected = num_min;
        more_or_less = "at least";
    } else {
        num_expected = num_max;
        more_or_less = "at most";
    }
    if (exact) {
        more_or_less = "exactly";
    }
    PyErr_Format(PyExc_TypeError,
                 "%.200s() takes %.8s %" CYTHON_FORMAT_SSIZE_T "d positional argument%.1s (%" CYTHON_FORMAT_SSIZE_T "d given)",
                 func_name, more_or_less, num_expected,
                 (num_expected == 1) ? "" : "s", num_found);
}

/* KeywordStringCheck */
static int __Pyx_CheckKeywordStrings(
    PyObject *kwdict,
    const char* function_name,
    int kw_allowed)
{
    PyObject* key = 0;
    Py_ssize_t pos = 0;
#if CYTHON_COMPILING_IN_PYPY
    if (!kw_allowed && PyDict_Next(kwdict, &pos, &key, 0))
        goto invalid_keyword;
    return 1;
#else
    while (PyDict_Next(kwdict, &pos, &key, 0)) {
        #if PY_MAJOR_VERSION < 3
        if (unlikely(!PyString_Check(key)))
        #endif
            if (unlikely(!PyUnicode_Check(key)))
                goto invalid_keyword_type;
    }
    if ((!kw_allowed) && unlikely(key))
        goto invalid_keyword;
    return 1;
invalid_keyword_type:
    PyErr_Format(PyExc_TypeError,
        "%.200s() keywords must be strings", function_name);
    return 0;
#endif
invalid_keyword:
    PyErr_Format(PyExc_TypeError,
    #if PY_MAJOR_VERSION < 3
        "%.200s() got an unexpected keyword argument '%.200s'",
        function_name, PyString_AsString(key));
    #else
        "%s() got an unexpected keyword argument '%U'",
        function_name, key);
    #endif
    return 0;
}

/* PyErrExceptionMatches */
#if CYTHON_FAST_THREAD_STATE
static int __Pyx_PyErr_ExceptionMatchesTuple(PyObject *exc_type, PyObject *tuple) {
    Py_ssize_t i, n;
    n = PyTuple_GET_SIZE(tuple);
#if PY_MAJOR_VERSION >= 3
    for (i=0; i<n; i++) {
        if (exc_type == PyTuple_GET_ITEM(tuple, i)) return 1;
    }
#endif
    for (i=0; i<n; i++) {
        if (__Pyx_PyErr_GivenExceptionMatches(exc_type, PyTuple_GET_ITEM(tuple, i))) return 1;
    }
    return 0;
}
static CYTHON_INLINE int __Pyx_PyErr_ExceptionMatchesInState(PyThreadState* tstate, PyObject* err) {
    PyObject *exc_type = tstate->curexc_type;
    if (exc_type == err) return 1;
    if (unlikely(!exc_type)) return 0;
    if (unlikely(PyTuple_Check(err)))
        return __Pyx_PyErr_ExceptionMatchesTuple(exc_type, err);
    return __Pyx_PyErr_GivenExceptionMatches(exc_type, err);
}
#endif

/* PyErrFetchRestore */
#if CYTHON_FAST_THREAD_STATE
static CYTHON_INLINE void __Pyx_ErrRestoreInState(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb) {
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    tmp_type = tstate->curexc_type;
    tmp_value = tstate->curexc_value;
    tmp_tb = tstate->curexc_traceback;
    tstate->curexc_type = type;
    tstate->curexc_value = value;
    tstate->curexc_traceback = tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
}
static CYTHON_INLINE void __Pyx_ErrFetchInState(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
    *type = tstate->curexc_type;
    *value = tstate->curexc_value;
    *tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
}
#endif

/* PyObjectGetAttrStr */
#if CYTHON_USE_TYPE_SLOTS
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStr(PyObject* obj, PyObject* attr_name) {
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_getattro))
        return tp->tp_getattro(obj, attr_name);
#if PY_MAJOR_VERSION < 3
    if (likely(tp->tp_getattr))
        return tp->tp_getattr(obj, PyString_AS_STRING(attr_name));
#endif
    return PyObject_GetAttr(obj, attr_name);
}
#endif

/* GetAttr */
static CYTHON_INLINE PyObject *__Pyx_GetAttr(PyObject *o, PyObject *n) {
#if CYTHON_USE_TYPE_SLOTS
#if PY_MAJOR_VERSION >= 3
    if (likely(PyUnicode_Check(n)))
#else
    if (likely(PyString_Check(n)))
#endif
        return __Pyx_PyObject_GetAttrStr(o, n);
#endif
    return PyObject_GetAttr(o, n);
}

/* GetAttr3 */
static PyObject *__Pyx_GetAttr3Default(PyObject *d) {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    if (unlikely(!__Pyx_PyErr_ExceptionMatches(PyExc_AttributeError)))
        return NULL;
    __Pyx_PyErr_Clear();
    Py_INCREF(d);
    return d;
}
static CYTHON_INLINE PyObject *__Pyx_GetAttr3(PyObject *o, PyObject *n, PyObject *d) {
    PyObject *r = __Pyx_GetAttr(o, n);
    return (likely(r)) ? r : __Pyx_GetAttr3Default(d);
}

/* GetBuiltinName */
static PyObject *__Pyx_GetBuiltinName(PyObject *name) {
    PyObject* result = __Pyx_PyObject_GetAttrStr(__pyx_b, name);
    if (unlikely(!result)) {
        PyErr_Format(PyExc_NameError,
#if PY_MAJOR_VERSION >= 3
            "name '%U' is not defined", name);
#else
            "name '%.200s' is not defined", PyString_AS_STRING(name));
#endif
    }
    return result;
}

/* PyDictVersioning */
#if CYTHON_USE_DICT_VERSIONS && CYTHON_USE_TYPE_SLOTS
static CYTHON_INLINE PY_UINT64_T __Pyx_get_tp_dict_version(PyObject *obj) {
    PyObject *dict = Py_TYPE(obj)->tp_dict;
    return likely(dict) ? __PYX_GET_DICT_VERSION(dict) : 0;
}
static CYTHON_INLINE PY_UINT64_T __Pyx_get_object_dict_version(PyObject *obj) {
    PyObject **dictptr = NULL;
    Py_ssize_t offset = Py_TYPE(obj)->tp_dictoffset;
    if (offset) {
#if CYTHON_COMPILING_IN_CPYTHON
        dictptr = (likely(offset > 0)) ? (PyObject **) ((char *)obj + offset) : _PyObject_GetDictPtr(obj);
#else
        dictptr = _PyObject_GetDictPtr(obj);
#endif
    }
    return (dictptr && *dictptr) ? __PYX_GET_DICT_VERSION(*dictptr) : 0;
}
static CYTHON_INLINE int __Pyx_object_dict_version_matches(PyObject* obj, PY_UINT64_T tp_dict_version, PY_UINT64_T obj_dict_version) {
    PyObject *dict = Py_TYPE(obj)->tp_dict;
    if (unlikely(!dict) || unlikely(tp_dict_version != __PYX_GET_DICT_VERSION(dict)))
        return 0;
    return obj_dict_version == __Pyx_get_object_dict_version(obj);
}
#endif

/* GetModuleGlobalName */
#if CYTHON_USE_DICT_VERSIONS
static PyObject *__Pyx__GetModuleGlobalName(PyObject *name, PY_UINT64_T *dict_version, PyObject **dict_cached_value)
#else
static CYTHON_INLINE PyObject *__Pyx__GetModuleGlobalName(PyObject *name)
#endif
{
    PyObject *result;
#if !CYTHON_AVOID_BORROWED_REFS
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x030500A1
    result = _PyDict_GetItem_KnownHash(__pyx_d, name, ((PyASCIIObject *) name)->hash);
    __PYX_UPDATE_DICT_CACHE(__pyx_d, result, *dict_cached_value, *dict_version)
    if (likely(result)) {
        return __Pyx_NewRef(result);
    } else if (unlikely(PyErr_Occurred())) {
        return NULL;
    }
#else
    result = PyDict_GetItem(__pyx_d, name);
    __PYX_UPDATE_DICT_CACHE(__pyx_d, result, *dict_cached_value, *dict_version)
    if (likely(result)) {
        return __Pyx_NewRef(result);
    }
#endif
#else
    result = PyObject_GetItem(__pyx_d, name);
    __PYX_UPDATE_DICT_CACHE(__pyx_d, result, *dict_cached_value, *dict_version)
    if (likely(result)) {
        return __Pyx_NewRef(result);
    }
    PyErr_Clear();
#endif
    return __Pyx_GetBuiltinName(name);
}

/* WriteUnraisableException */
static void __Pyx_WriteUnraisable(const char *name, CYTHON_UNUSED int clineno,
                                  CYTHON_UNUSED int lineno, CYTHON_UNUSED const char *filename,
                                  int full_traceback, CYTHON_UNUSED int nogil) {
    PyObject *old_exc, *old_val, *old_tb;
    PyObject *ctx;
    __Pyx_PyThreadState_declare
#ifdef WITH_THREAD
    PyGILState_STATE state;
    if (nogil)
        state = PyGILState_Ensure();
#ifdef _MSC_VER
    else state = (PyGILState_STATE)-1;
#endif
#endif
    __Pyx_PyThreadState_assign
    __Pyx_ErrFetch(&old_exc, &old_val, &old_tb);
    if (full_traceback) {
        Py_XINCREF(old_exc);
        Py_XINCREF(old_val);
        Py_XINCREF(old_tb);
        __Pyx_ErrRestore(old_exc, old_val, old_tb);
        PyErr_PrintEx(1);
    }
    #if PY_MAJOR_VERSION < 3
    ctx = PyString_FromString(name);
    #else
    ctx = PyUnicode_FromString(name);
    #endif
    __Pyx_ErrRestore(old_exc, old_val, old_tb);
    if (!ctx) {
        PyErr_WriteUnraisable(Py_None);
    } else {
        PyErr_WriteUnraisable(ctx);
        Py_DECREF(ctx);
    }
#ifdef WITH_THREAD
    if (nogil)
        PyGILState_Release(state);
#endif
}

/* PyCFunctionFastCall */
#if CYTHON_FAST_PYCCALL
static CYTHON_INLINE PyObject * __Pyx_PyCFunction_FastCall(PyObject *func_obj, PyObject **args, Py_ssize_t nargs) {
    PyCFunctionObject *func = (PyCFunctionObject*)func_obj;
    PyCFunction meth = PyCFunction_GET_FUNCTION(func);
    PyObject *self = PyCFunction_GET_SELF(func);
    int flags = PyCFunction_GET_FLAGS(func);
    assert(PyCFunction_Check(func));
    assert(METH_FASTCALL == (flags & ~(METH_CLASS | METH_STATIC | METH_COEXIST | METH_KEYWORDS | METH_STACKLESS)));
    assert(nargs >= 0);
    assert(nargs == 0 || args != NULL);
    /* _PyCFunction_FastCallDict() must not be called with an exception set,
       because it may clear it (directly or indirectly) and so the
       caller loses its exception */
    assert(!PyErr_Occurred());
    if ((PY_VERSION_HEX < 0x030700A0) || unlikely(flags & METH_KEYWORDS)) {
        return (*((__Pyx_PyCFunctionFastWithKeywords)(void*)meth)) (self, args, nargs, NULL);
    } else {
        return (*((__Pyx_PyCFunctionFast)(void*)meth)) (self, args, nargs);
    }
}
#endif

/* PyFunctionFastCall */
#if CYTHON_FAST_PYCALL
static PyObject* __Pyx_PyFunction_FastCallNoKw(PyCodeObject *co, PyObject **args, Py_ssize_t na,
                                               PyObject *globals) {
    PyFrameObject *f;
    PyThreadState *tstate = __Pyx_PyThreadState_Current;
    PyObject **fastlocals;
    Py_ssize_t i;
    PyObject *result;
    assert(globals != NULL);
    /* XXX Perhaps we should create a specialized
       PyFrame_New() that doesn't take locals, but does
       take builtins without sanity checking them.
       */
    assert(tstate != NULL);
    f = PyFrame_New(tstate, co, globals, NULL);
    if (f == NULL) {
        return NULL;
    }
    fastlocals = __Pyx_PyFrame_GetLocalsplus(f);
    for (i = 0; i < na; i++) {
        Py_INCREF(*args);
        fastlocals[i] = *args++;
    }
    result = PyEval_EvalFrameEx(f,0);
    ++tstate->recursion_depth;
    Py_DECREF(f);
    --tstate->recursion_depth;
    return result;
}
#if 1 || PY_VERSION_HEX < 0x030600B1
static PyObject *__Pyx_PyFunction_FastCallDict(PyObject *func, PyObject **args, Py_ssize_t nargs, PyObject *kwargs) {
    PyCodeObject *co = (PyCodeObject *)PyFunction_GET_CODE(func);
    PyObject *globals = PyFunction_GET_GLOBALS(func);
    PyObject *argdefs = PyFunction_GET_DEFAULTS(func);
    PyObject *closure;
#if PY_MAJOR_VERSION >= 3
    PyObject *kwdefs;
#endif
    PyObject *kwtuple, **k;
    PyObject **d;
    Py_ssize_t nd;
    Py_ssize_t nk;
    PyObject *result;
    assert(kwargs == NULL || PyDict_Check(kwargs));
    nk = kwargs ? PyDict_Size(kwargs) : 0;
    if (Py_EnterRecursiveCall((char*)" while calling a Python object")) {
        return NULL;
    }
    if (
#if PY_MAJOR_VERSION >= 3
            co->co_kwonlyargcount == 0 &&
#endif
            likely(kwargs == NULL || nk == 0) &&
            co->co_flags == (CO_OPTIMIZED | CO_NEWLOCALS | CO_NOFREE)) {
        if (argdefs == NULL && co->co_argcount == nargs) {
            result = __Pyx_PyFunction_FastCallNoKw(co, args, nargs, globals);
            goto done;
        }
        else if (nargs == 0 && argdefs != NULL
                 && co->co_argcount == Py_SIZE(argdefs)) {
            /* function called with no arguments, but all parameters have
               a default value: use default values as arguments .*/
            args = &PyTuple_GET_ITEM(argdefs, 0);
            result =__Pyx_PyFunction_FastCallNoKw(co, args, Py_SIZE(argdefs), globals);
            goto done;
        }
    }
    if (kwargs != NULL) {
        Py_ssize_t pos, i;
        kwtuple = PyTuple_New(2 * nk);
        if (kwtuple == NULL) {
            result = NULL;
            goto done;
        }
        k = &PyTuple_GET_ITEM(kwtuple, 0);
        pos = i = 0;
        while (PyDict_Next(kwargs, &pos, &k[i], &k[i+1])) {
            Py_INCREF(k[i]);
            Py_INCREF(k[i+1]);
            i += 2;
        }
        nk = i / 2;
    }
    else {
        kwtuple = NULL;
        k = NULL;
    }
    closure = PyFunction_GET_CLOSURE(func);
#if PY_MAJOR_VERSION >= 3
    kwdefs = PyFunction_GET_KW_DEFAULTS(func);
#endif
    if (argdefs != NULL) {
        d = &PyTuple_GET_ITEM(argdefs, 0);
        nd = Py_SIZE(argdefs);
    }
    else {
        d = NULL;
        nd = 0;
    }
#if PY_MAJOR_VERSION >= 3
    result = PyEval_EvalCodeEx((PyObject*)co, globals, (PyObject *)NULL,
                               args, (int)nargs,
                               k, (int)nk,
                               d, (int)nd, kwdefs, closure);
#else
    result = PyEval_EvalCodeEx(co, globals, (PyObject *)NULL,
                               args, (int)nargs,
                               k, (int)nk,
                               d, (int)nd, closure);
#endif
    Py_XDECREF(kwtuple);
done:
    Py_LeaveRecursiveCall();
    return result;
}
#endif
#endif

/* PyObjectCall */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw) {
    PyObject *result;
    ternaryfunc call = func->ob_type->tp_call;
    if (unlikely(!call))
        return PyObject_Call(func, arg, kw);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = (*call)(func, arg, kw);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

/* PyObjectCall2Args */
static CYTHON_UNUSED PyObject* __Pyx_PyObject_Call2Args(PyObject* function, PyObject* arg1, PyObject* arg2) {
    PyObject *args, *result = NULL;
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(function)) {
        PyObject *args[2] = {arg1, arg2};
        return __Pyx_PyFunction_FastCall(function, args, 2);
    }
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(function)) {
        PyObject *args[2] = {arg1, arg2};
        return __Pyx_PyCFunction_FastCall(function, args, 2);
    }
    #endif
    args = PyTuple_New(2);
    if (unlikely(!args)) goto done;
    Py_INCREF(arg1);
    PyTuple_SET_ITEM(args, 0, arg1);
    Py_INCREF(arg2);
    PyTuple_SET_ITEM(args, 1, arg2);
    Py_INCREF(function);
    result = __Pyx_PyObject_Call(function, args, NULL);
    Py_DECREF(args);
    Py_DECREF(function);
done:
    return result;
}

/* PyObjectCallMethO */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg) {
    PyObject *self, *result;
    PyCFunction cfunc;
    cfunc = PyCFunction_GET_FUNCTION(func);
    self = PyCFunction_GET_SELF(func);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = cfunc(self, arg);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

/* PyObjectCallOneArg */
#if CYTHON_COMPILING_IN_CPYTHON
static PyObject* __Pyx__PyObject_CallOneArg(PyObject *func, PyObject *arg) {
    PyObject *result;
    PyObject *args = PyTuple_New(1);
    if (unlikely(!args)) return NULL;
    Py_INCREF(arg);
    PyTuple_SET_ITEM(args, 0, arg);
    result = __Pyx_PyObject_Call(func, args, NULL);
    Py_DECREF(args);
    return result;
}
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg) {
#if CYTHON_FAST_PYCALL
    if (PyFunction_Check(func)) {
        return __Pyx_PyFunction_FastCall(func, &arg, 1);
    }
#endif
    if (likely(PyCFunction_Check(func))) {
        if (likely(PyCFunction_GET_FLAGS(func) & METH_O)) {
            return __Pyx_PyObject_CallMethO(func, arg);
#if CYTHON_FAST_PYCCALL
        } else if (__Pyx_PyFastCFunction_Check(func)) {
            return __Pyx_PyCFunction_FastCall(func, &arg, 1);
#endif
        }
    }
    return __Pyx__PyObject_CallOneArg(func, arg);
}
#else
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg) {
    PyObject *result;
    PyObject *args = PyTuple_Pack(1, arg);
    if (unlikely(!args)) return NULL;
    result = __Pyx_PyObject_Call(func, args, NULL);
    Py_DECREF(args);
    return result;
}
#endif

/* RaiseDoubleKeywords */
static void __Pyx_RaiseDoubleKeywordsError(
    const char* func_name,
    PyObject* kw_name)
{
    PyErr_Format(PyExc_TypeError,
        #if PY_MAJOR_VERSION >= 3
        "%s() got multiple values for keyword argument '%U'", func_name, kw_name);
        #else
        "%s() got multiple values for keyword argument '%s'", func_name,
        PyString_AsString(kw_name));
        #endif
}

/* ParseKeywords */
static int __Pyx_ParseOptionalKeywords(
    PyObject *kwds,
    PyObject **argnames[],
    PyObject *kwds2,
    PyObject *values[],
    Py_ssize_t num_pos_args,
    const char* function_name)
{
    PyObject *key = 0, *value = 0;
    Py_ssize_t pos = 0;
    PyObject*** name;
    PyObject*** first_kw_arg = argnames + num_pos_args;
    while (PyDict_Next(kwds, &pos, &key, &value)) {
        name = first_kw_arg;
        while (*name && (**name != key)) name++;
        if (*name) {
            values[name-argnames] = value;
            continue;
        }
        name = first_kw_arg;
        #if PY_MAJOR_VERSION < 3
        if (likely(PyString_Check(key))) {
            while (*name) {
                if ((CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**name) == PyString_GET_SIZE(key))
                        && _PyString_Eq(**name, key)) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    if ((**argname == key) || (
                            (CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**argname) == PyString_GET_SIZE(key))
                             && _PyString_Eq(**argname, key))) {
                        goto arg_passed_twice;
                    }
                    argname++;
                }
            }
        } else
        #endif
        if (likely(PyUnicode_Check(key))) {
            while (*name) {
                int cmp = (**name == key) ? 0 :
                #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                    (__Pyx_PyUnicode_GET_LENGTH(**name) != __Pyx_PyUnicode_GET_LENGTH(key)) ? 1 :
                #endif
                    PyUnicode_Compare(**name, key);
                if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                if (cmp == 0) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    int cmp = (**argname == key) ? 0 :
                    #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                        (__Pyx_PyUnicode_GET_LENGTH(**argname) != __Pyx_PyUnicode_GET_LENGTH(key)) ? 1 :
                    #endif
                        PyUnicode_Compare(**argname, key);
                    if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                    if (cmp == 0) goto arg_passed_twice;
                    argname++;
                }
            }
        } else
            goto invalid_keyword_type;
        if (kwds2) {
            if (unlikely(PyDict_SetItem(kwds2, key, value))) goto bad;
        } else {
            goto invalid_keyword;
        }
    }
    return 0;
arg_passed_twice:
    __Pyx_RaiseDoubleKeywordsError(function_name, key);
    goto bad;
invalid_keyword_type:
    PyErr_Format(PyExc_TypeError,
        "%.200s() keywords must be strings", function_name);
    goto bad;
invalid_keyword:
    PyErr_Format(PyExc_TypeError,
    #if PY_MAJOR_VERSION < 3
        "%.200s() got an unexpected keyword argument '%.200s'",
        function_name, PyString_AsString(key));
    #else
        "%s() got an unexpected keyword argument '%U'",
        function_name, key);
    #endif
bad:
    return -1;
}

/* ArgTypeTest */
static int __Pyx__ArgTypeTest(PyObject *obj, PyTypeObject *type, const char *name, int exact)
{
    if (unlikely(!type)) {
        PyErr_SetString(PyExc_SystemError, "Missing type object");
        return 0;
    }
    else if (exact) {
        #if PY_MAJOR_VERSION == 2
        if ((type == &PyBaseString_Type) && likely(__Pyx_PyBaseString_CheckExact(obj))) return 1;
        #endif
    }
    else {
        if (likely(__Pyx_TypeCheck(obj, type))) return 1;
    }
    PyErr_Format(PyExc_TypeError,
        "Argument '%.200s' has incorrect type (expected %.200s, got %.200s)",
        name, type->tp_name, Py_TYPE(obj)->tp_name);
    return 0;
}

/* ExtTypeTest */
static CYTHON_INLINE int __Pyx_TypeTest(PyObject *obj, PyTypeObject *type) {
    if (unlikely(!type)) {
        PyErr_SetString(PyExc_SystemError, "Missing type object");
        return 0;
    }
    if (likely(__Pyx_TypeCheck(obj, type)))
        return 1;
    PyErr_Format(PyExc_TypeError, "Cannot convert %.200s to %.200s",
                 Py_TYPE(obj)->tp_name, type->tp_name);
    return 0;
}

/* GetItemInt */
static PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j) {
    PyObject *r;
    if (!j) return NULL;
    r = PyObject_GetItem(o, j);
    Py_DECREF(j);
    return r;
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              CYTHON_NCP_UNUSED int wraparound,
                                                              CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    Py_ssize_t wrapped_i = i;
    if (wraparound & unlikely(i < 0)) {
        wrapped_i += PyList_GET_SIZE(o);
    }
    if ((!boundscheck) || likely(__Pyx_is_valid_index(wrapped_i, PyList_GET_SIZE(o)))) {
        PyObject *r = PyList_GET_ITEM(o, wrapped_i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              CYTHON_NCP_UNUSED int wraparound,
                                                              CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    Py_ssize_t wrapped_i = i;
    if (wraparound & unlikely(i < 0)) {
        wrapped_i += PyTuple_GET_SIZE(o);
    }
    if ((!boundscheck) || likely(__Pyx_is_valid_index(wrapped_i, PyTuple_GET_SIZE(o)))) {
        PyObject *r = PyTuple_GET_ITEM(o, wrapped_i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i, int is_list,
                                                     CYTHON_NCP_UNUSED int wraparound,
                                                     CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS && CYTHON_USE_TYPE_SLOTS
    if (is_list || PyList_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyList_GET_SIZE(o);
        if ((!boundscheck) || (likely(__Pyx_is_valid_index(n, PyList_GET_SIZE(o))))) {
            PyObject *r = PyList_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    }
    else if (PyTuple_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyTuple_GET_SIZE(o);
        if ((!boundscheck) || likely(__Pyx_is_valid_index(n, PyTuple_GET_SIZE(o)))) {
            PyObject *r = PyTuple_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    } else {
        PySequenceMethods *m = Py_TYPE(o)->tp_as_sequence;
        if (likely(m && m->sq_item)) {
            if (wraparound && unlikely(i < 0) && likely(m->sq_length)) {
                Py_ssize_t l = m->sq_length(o);
                if (likely(l >= 0)) {
                    i += l;
                } else {
                    if (!PyErr_ExceptionMatches(PyExc_OverflowError))
                        return NULL;
                    PyErr_Clear();
                }
            }
            return m->sq_item(o, i);
        }
    }
#else
    if (is_list || PySequence_Check(o)) {
        return PySequence_GetItem(o, i);
    }
#endif
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
}

/* PyObjectCallNoArg */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func) {
#if CYTHON_FAST_PYCALL
    if (PyFunction_Check(func)) {
        return __Pyx_PyFunction_FastCall(func, NULL, 0);
    }
#endif
#ifdef __Pyx_CyFunction_USED
    if (likely(PyCFunction_Check(func) || __Pyx_CyFunction_Check(func)))
#else
    if (likely(PyCFunction_Check(func)))
#endif
    {
        if (likely(PyCFunction_GET_FLAGS(func) & METH_NOARGS)) {
            return __Pyx_PyObject_CallMethO(func, NULL);
        }
    }
    return __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL);
}
#endif

/* pyobject_as_double */
static double __Pyx__PyObject_AsDouble(PyObject* obj) {
    PyObject* float_value;
#if !CYTHON_USE_TYPE_SLOTS
    float_value = PyNumber_Float(obj);  if ((0)) goto bad;
#else
    PyNumberMethods *nb = Py_TYPE(obj)->tp_as_number;
    if (likely(nb) && likely(nb->nb_float)) {
        float_value = nb->nb_float(obj);
        if (likely(float_value) && unlikely(!PyFloat_Check(float_value))) {
            PyErr_Format(PyExc_TypeError,
                "__float__ returned non-float (type %.200s)",
                Py_TYPE(float_value)->tp_name);
            Py_DECREF(float_value);
            goto bad;
        }
    } else if (PyUnicode_CheckExact(obj) || PyBytes_CheckExact(obj)) {
#if PY_MAJOR_VERSION >= 3
        float_value = PyFloat_FromString(obj);
#else
        float_value = PyFloat_FromString(obj, 0);
#endif
    } else {
        PyObject* args = PyTuple_New(1);
        if (unlikely(!args)) goto bad;
        PyTuple_SET_ITEM(args, 0, obj);
        float_value = PyObject_Call((PyObject*)&PyFloat_Type, args, 0);
        PyTuple_SET_ITEM(args, 0, 0);
        Py_DECREF(args);
    }
#endif
    if (likely(float_value)) {
        double value = PyFloat_AS_DOUBLE(float_value);
        Py_DECREF(float_value);
        return value;
    }
bad:
    return (double)-1;
}

/* PyFloatBinop */
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyFloat_AddCObj(PyObject *op1, PyObject *op2, double floatval, int inplace, int zerodivision_check) {
    const double a = floatval;
    double b, result;
    (void)inplace;
    (void)zerodivision_check;
    if (likely(PyFloat_CheckExact(op2))) {
        b = PyFloat_AS_DOUBLE(op2);
        
    } else
    #if PY_MAJOR_VERSION < 3
    if (likely(PyInt_CheckExact(op2))) {
        b = (double) PyInt_AS_LONG(op2);
        
    } else
    #endif
    if (likely(PyLong_CheckExact(op2))) {
        #if CYTHON_USE_PYLONG_INTERNALS
        const digit* digits = ((PyLongObject*)op2)->ob_digit;
        const Py_ssize_t size = Py_SIZE(op2);
        switch (size) {
            case  0: b = 0.0; break;
            case -1: b = -(double) digits[0]; break;
            case  1: b = (double) digits[0]; break;
            case -2:
            case 2:
                if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT && ((8 * sizeof(unsigned long) < 53) || (1 * PyLong_SHIFT < 53))) {
                    b = (double) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                    if ((8 * sizeof(unsigned long) < 53) || (2 * PyLong_SHIFT < 53) || (b < (double) ((PY_LONG_LONG)1 << 53))) {
                        if (size == -2)
                            b = -b;
                        break;
                    }
                }
                CYTHON_FALLTHROUGH;
            case -3:
            case 3:
                if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT && ((8 * sizeof(unsigned long) < 53) || (2 * PyLong_SHIFT < 53))) {
                    b = (double) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                    if ((8 * sizeof(unsigned long) < 53) || (3 * PyLong_SHIFT < 53) || (b < (double) ((PY_LONG_LONG)1 << 53))) {
                        if (size == -3)
                            b = -b;
                        break;
                    }
                }
                CYTHON_FALLTHROUGH;
            case -4:
            case 4:
                if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT && ((8 * sizeof(unsigned long) < 53) || (3 * PyLong_SHIFT < 53))) {
                    b = (double) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                    if ((8 * sizeof(unsigned long) < 53) || (4 * PyLong_SHIFT < 53) || (b < (double) ((PY_LONG_LONG)1 << 53))) {
                        if (size == -4)
                            b = -b;
                        break;
                    }
                }
                CYTHON_FALLTHROUGH;
            default:
        #else
        {
        #endif
            b = PyLong_AsDouble(op2);
            if (unlikely(b == -1.0 && PyErr_Occurred())) return NULL;
            
        }
    } else {
        return (inplace ? PyNumber_InPlaceAdd : PyNumber_Add)(op1, op2);
    }
        
        PyFPE_START_PROTECT("add", return NULL)
        result = a + b;
        PyFPE_END_PROTECT(result)
        return PyFloat_FromDouble(result);
}
#endif

/* Import */
  static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level) {
    PyObject *empty_list = 0;
    PyObject *module = 0;
    PyObject *global_dict = 0;
    PyObject *empty_dict = 0;
    PyObject *list;
    #if PY_MAJOR_VERSION < 3
    PyObject *py_import;
    py_import = __Pyx_PyObject_GetAttrStr(__pyx_b, __pyx_n_s_import);
    if (!py_import)
        goto bad;
    #endif
    if (from_list)
        list = from_list;
    else {
        empty_list = PyList_New(0);
        if (!empty_list)
            goto bad;
        list = empty_list;
    }
    global_dict = PyModule_GetDict(__pyx_m);
    if (!global_dict)
        goto bad;
    empty_dict = PyDict_New();
    if (!empty_dict)
        goto bad;
    {
        #if PY_MAJOR_VERSION >= 3
        if (level == -1) {
            if ((1) && (strchr(__Pyx_MODULE_NAME, '.'))) {
                module = PyImport_ImportModuleLevelObject(
                    name, global_dict, empty_dict, list, 1);
                if (!module) {
                    if (!PyErr_ExceptionMatches(PyExc_ImportError))
                        goto bad;
                    PyErr_Clear();
                }
            }
            level = 0;
        }
        #endif
        if (!module) {
            #if PY_MAJOR_VERSION < 3
            PyObject *py_level = PyInt_FromLong(level);
            if (!py_level)
                goto bad;
            module = PyObject_CallFunctionObjArgs(py_import,
                name, global_dict, empty_dict, list, py_level, (PyObject *)NULL);
            Py_DECREF(py_level);
            #else
            module = PyImport_ImportModuleLevelObject(
                name, global_dict, empty_dict, list, level);
            #endif
        }
    }
bad:
    #if PY_MAJOR_VERSION < 3
    Py_XDECREF(py_import);
    #endif
    Py_XDECREF(empty_list);
    Py_XDECREF(empty_dict);
    return module;
}

/* ImportFrom */
  static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name) {
    PyObject* value = __Pyx_PyObject_GetAttrStr(module, name);
    if (unlikely(!value) && PyErr_ExceptionMatches(PyExc_AttributeError)) {
        PyErr_Format(PyExc_ImportError,
        #if PY_MAJOR_VERSION < 3
            "cannot import name %.230s", PyString_AS_STRING(name));
        #else
            "cannot import name %S", name);
        #endif
    }
    return value;
}

/* RaiseException */
  #if PY_MAJOR_VERSION < 3
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb,
                        CYTHON_UNUSED PyObject *cause) {
    __Pyx_PyThreadState_declare
    Py_XINCREF(type);
    if (!value || value == Py_None)
        value = NULL;
    else
        Py_INCREF(value);
    if (!tb || tb == Py_None)
        tb = NULL;
    else {
        Py_INCREF(tb);
        if (!PyTraceBack_Check(tb)) {
            PyErr_SetString(PyExc_TypeError,
                "raise: arg 3 must be a traceback or None");
            goto raise_error;
        }
    }
    if (PyType_Check(type)) {
#if CYTHON_COMPILING_IN_PYPY
        if (!value) {
            Py_INCREF(Py_None);
            value = Py_None;
        }
#endif
        PyErr_NormalizeException(&type, &value, &tb);
    } else {
        if (value) {
            PyErr_SetString(PyExc_TypeError,
                "instance exception may not have a separate value");
            goto raise_error;
        }
        value = type;
        type = (PyObject*) Py_TYPE(type);
        Py_INCREF(type);
        if (!PyType_IsSubtype((PyTypeObject *)type, (PyTypeObject *)PyExc_BaseException)) {
            PyErr_SetString(PyExc_TypeError,
                "raise: exception class must be a subclass of BaseException");
            goto raise_error;
        }
    }
    __Pyx_PyThreadState_assign
    __Pyx_ErrRestore(type, value, tb);
    return;
raise_error:
    Py_XDECREF(value);
    Py_XDECREF(type);
    Py_XDECREF(tb);
    return;
}
#else
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb, PyObject *cause) {
    PyObject* owned_instance = NULL;
    if (tb == Py_None) {
        tb = 0;
    } else if (tb && !PyTraceBack_Check(tb)) {
        PyErr_SetString(PyExc_TypeError,
            "raise: arg 3 must be a traceback or None");
        goto bad;
    }
    if (value == Py_None)
        value = 0;
    if (PyExceptionInstance_Check(type)) {
        if (value) {
            PyErr_SetString(PyExc_TypeError,
                "instance exception may not have a separate value");
            goto bad;
        }
        value = type;
        type = (PyObject*) Py_TYPE(value);
    } else if (PyExceptionClass_Check(type)) {
        PyObject *instance_class = NULL;
        if (value && PyExceptionInstance_Check(value)) {
            instance_class = (PyObject*) Py_TYPE(value);
            if (instance_class != type) {
                int is_subclass = PyObject_IsSubclass(instance_class, type);
                if (!is_subclass) {
                    instance_class = NULL;
                } else if (unlikely(is_subclass == -1)) {
                    goto bad;
                } else {
                    type = instance_class;
                }
            }
        }
        if (!instance_class) {
            PyObject *args;
            if (!value)
                args = PyTuple_New(0);
            else if (PyTuple_Check(value)) {
                Py_INCREF(value);
                args = value;
            } else
                args = PyTuple_Pack(1, value);
            if (!args)
                goto bad;
            owned_instance = PyObject_Call(type, args, NULL);
            Py_DECREF(args);
            if (!owned_instance)
                goto bad;
            value = owned_instance;
            if (!PyExceptionInstance_Check(value)) {
                PyErr_Format(PyExc_TypeError,
                             "calling %R should have returned an instance of "
                             "BaseException, not %R",
                             type, Py_TYPE(value));
                goto bad;
            }
        }
    } else {
        PyErr_SetString(PyExc_TypeError,
            "raise: exception class must be a subclass of BaseException");
        goto bad;
    }
    if (cause) {
        PyObject *fixed_cause;
        if (cause == Py_None) {
            fixed_cause = NULL;
        } else if (PyExceptionClass_Check(cause)) {
            fixed_cause = PyObject_CallObject(cause, NULL);
            if (fixed_cause == NULL)
                goto bad;
        } else if (PyExceptionInstance_Check(cause)) {
            fixed_cause = cause;
            Py_INCREF(fixed_cause);
        } else {
            PyErr_SetString(PyExc_TypeError,
                            "exception causes must derive from "
                            "BaseException");
            goto bad;
        }
        PyException_SetCause(value, fixed_cause);
    }
    PyErr_SetObject(type, value);
    if (tb) {
#if CYTHON_COMPILING_IN_PYPY
        PyObject *tmp_type, *tmp_value, *tmp_tb;
        PyErr_Fetch(&tmp_type, &tmp_value, &tmp_tb);
        Py_INCREF(tb);
        PyErr_Restore(tmp_type, tmp_value, tb);
        Py_XDECREF(tmp_tb);
#else
        PyThreadState *tstate = __Pyx_PyThreadState_Current;
        PyObject* tmp_tb = tstate->curexc_traceback;
        if (tb != tmp_tb) {
            Py_INCREF(tb);
            tstate->curexc_traceback = tb;
            Py_XDECREF(tmp_tb);
        }
#endif
    }
bad:
    Py_XDECREF(owned_instance);
    return;
}
#endif

/* HasAttr */
  static CYTHON_INLINE int __Pyx_HasAttr(PyObject *o, PyObject *n) {
    PyObject *r;
    if (unlikely(!__Pyx_PyBaseString_Check(n))) {
        PyErr_SetString(PyExc_TypeError,
                        "hasattr(): attribute name must be string");
        return -1;
    }
    r = __Pyx_GetAttr(o, n);
    if (unlikely(!r)) {
        PyErr_Clear();
        return 0;
    } else {
        Py_DECREF(r);
        return 1;
    }
}

/* PyObject_GenericGetAttrNoDict */
  #if CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP && PY_VERSION_HEX < 0x03070000
static PyObject *__Pyx_RaiseGenericGetAttributeError(PyTypeObject *tp, PyObject *attr_name) {
    PyErr_Format(PyExc_AttributeError,
#if PY_MAJOR_VERSION >= 3
                 "'%.50s' object has no attribute '%U'",
                 tp->tp_name, attr_name);
#else
                 "'%.50s' object has no attribute '%.400s'",
                 tp->tp_name, PyString_AS_STRING(attr_name));
#endif
    return NULL;
}
static CYTHON_INLINE PyObject* __Pyx_PyObject_GenericGetAttrNoDict(PyObject* obj, PyObject* attr_name) {
    PyObject *descr;
    PyTypeObject *tp = Py_TYPE(obj);
    if (unlikely(!PyString_Check(attr_name))) {
        return PyObject_GenericGetAttr(obj, attr_name);
    }
    assert(!tp->tp_dictoffset);
    descr = _PyType_Lookup(tp, attr_name);
    if (unlikely(!descr)) {
        return __Pyx_RaiseGenericGetAttributeError(tp, attr_name);
    }
    Py_INCREF(descr);
    #if PY_MAJOR_VERSION < 3
    if (likely(PyType_HasFeature(Py_TYPE(descr), Py_TPFLAGS_HAVE_CLASS)))
    #endif
    {
        descrgetfunc f = Py_TYPE(descr)->tp_descr_get;
        if (unlikely(f)) {
            PyObject *res = f(descr, obj, (PyObject *)tp);
            Py_DECREF(descr);
            return res;
        }
    }
    return descr;
}
#endif

/* PyObject_GenericGetAttr */
  #if CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP && PY_VERSION_HEX < 0x03070000
static PyObject* __Pyx_PyObject_GenericGetAttr(PyObject* obj, PyObject* attr_name) {
    if (unlikely(Py_TYPE(obj)->tp_dictoffset)) {
        return PyObject_GenericGetAttr(obj, attr_name);
    }
    return __Pyx_PyObject_GenericGetAttrNoDict(obj, attr_name);
}
#endif

/* PyObjectGetAttrStrNoError */
  static void __Pyx_PyObject_GetAttrStr_ClearAttributeError(void) {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    if (likely(__Pyx_PyErr_ExceptionMatches(PyExc_AttributeError)))
        __Pyx_PyErr_Clear();
}
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStrNoError(PyObject* obj, PyObject* attr_name) {
    PyObject *result;
#if CYTHON_COMPILING_IN_CPYTHON && CYTHON_USE_TYPE_SLOTS && PY_VERSION_HEX >= 0x030700B1
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_getattro == PyObject_GenericGetAttr)) {
        return _PyObject_GenericGetAttrWithDict(obj, attr_name, NULL, 1);
    }
#endif
    result = __Pyx_PyObject_GetAttrStr(obj, attr_name);
    if (unlikely(!result)) {
        __Pyx_PyObject_GetAttrStr_ClearAttributeError();
    }
    return result;
}

/* SetupReduce */
  static int __Pyx_setup_reduce_is_named(PyObject* meth, PyObject* name) {
  int ret;
  PyObject *name_attr;
  name_attr = __Pyx_PyObject_GetAttrStr(meth, __pyx_n_s_name);
  if (likely(name_attr)) {
      ret = PyObject_RichCompareBool(name_attr, name, Py_EQ);
  } else {
      ret = -1;
  }
  if (unlikely(ret < 0)) {
      PyErr_Clear();
      ret = 0;
  }
  Py_XDECREF(name_attr);
  return ret;
}
static int __Pyx_setup_reduce(PyObject* type_obj) {
    int ret = 0;
    PyObject *object_reduce = NULL;
    PyObject *object_reduce_ex = NULL;
    PyObject *reduce = NULL;
    PyObject *reduce_ex = NULL;
    PyObject *reduce_cython = NULL;
    PyObject *setstate = NULL;
    PyObject *setstate_cython = NULL;
#if CYTHON_USE_PYTYPE_LOOKUP
    if (_PyType_Lookup((PyTypeObject*)type_obj, __pyx_n_s_getstate)) goto __PYX_GOOD;
#else
    if (PyObject_HasAttr(type_obj, __pyx_n_s_getstate)) goto __PYX_GOOD;
#endif
#if CYTHON_USE_PYTYPE_LOOKUP
    object_reduce_ex = _PyType_Lookup(&PyBaseObject_Type, __pyx_n_s_reduce_ex); if (!object_reduce_ex) goto __PYX_BAD;
#else
    object_reduce_ex = __Pyx_PyObject_GetAttrStr((PyObject*)&PyBaseObject_Type, __pyx_n_s_reduce_ex); if (!object_reduce_ex) goto __PYX_BAD;
#endif
    reduce_ex = __Pyx_PyObject_GetAttrStr(type_obj, __pyx_n_s_reduce_ex); if (unlikely(!reduce_ex)) goto __PYX_BAD;
    if (reduce_ex == object_reduce_ex) {
#if CYTHON_USE_PYTYPE_LOOKUP
        object_reduce = _PyType_Lookup(&PyBaseObject_Type, __pyx_n_s_reduce); if (!object_reduce) goto __PYX_BAD;
#else
        object_reduce = __Pyx_PyObject_GetAttrStr((PyObject*)&PyBaseObject_Type, __pyx_n_s_reduce); if (!object_reduce) goto __PYX_BAD;
#endif
        reduce = __Pyx_PyObject_GetAttrStr(type_obj, __pyx_n_s_reduce); if (unlikely(!reduce)) goto __PYX_BAD;
        if (reduce == object_reduce || __Pyx_setup_reduce_is_named(reduce, __pyx_n_s_reduce_cython)) {
            reduce_cython = __Pyx_PyObject_GetAttrStrNoError(type_obj, __pyx_n_s_reduce_cython);
            if (likely(reduce_cython)) {
                ret = PyDict_SetItem(((PyTypeObject*)type_obj)->tp_dict, __pyx_n_s_reduce, reduce_cython); if (unlikely(ret < 0)) goto __PYX_BAD;
                ret = PyDict_DelItem(((PyTypeObject*)type_obj)->tp_dict, __pyx_n_s_reduce_cython); if (unlikely(ret < 0)) goto __PYX_BAD;
            } else if (reduce == object_reduce || PyErr_Occurred()) {
                goto __PYX_BAD;
            }
            setstate = __Pyx_PyObject_GetAttrStr(type_obj, __pyx_n_s_setstate);
            if (!setstate) PyErr_Clear();
            if (!setstate || __Pyx_setup_reduce_is_named(setstate, __pyx_n_s_setstate_cython)) {
                setstate_cython = __Pyx_PyObject_GetAttrStrNoError(type_obj, __pyx_n_s_setstate_cython);
                if (likely(setstate_cython)) {
                    ret = PyDict_SetItem(((PyTypeObject*)type_obj)->tp_dict, __pyx_n_s_setstate, setstate_cython); if (unlikely(ret < 0)) goto __PYX_BAD;
                    ret = PyDict_DelItem(((PyTypeObject*)type_obj)->tp_dict, __pyx_n_s_setstate_cython); if (unlikely(ret < 0)) goto __PYX_BAD;
                } else if (!setstate || PyErr_Occurred()) {
                    goto __PYX_BAD;
                }
            }
            PyType_Modified((PyTypeObject*)type_obj);
        }
    }
    goto __PYX_GOOD;
__PYX_BAD:
    if (!PyErr_Occurred())
        PyErr_Format(PyExc_RuntimeError, "Unable to initialize pickling for %s", ((PyTypeObject*)type_obj)->tp_name);
    ret = -1;
__PYX_GOOD:
#if !CYTHON_USE_PYTYPE_LOOKUP
    Py_XDECREF(object_reduce);
    Py_XDECREF(object_reduce_ex);
#endif
    Py_XDECREF(reduce);
    Py_XDECREF(reduce_ex);
    Py_XDECREF(reduce_cython);
    Py_XDECREF(setstate);
    Py_XDECREF(setstate_cython);
    return ret;
}

/* SetVTable */
  static int __Pyx_SetVtable(PyObject *dict, void *vtable) {
#if PY_VERSION_HEX >= 0x02070000
    PyObject *ob = PyCapsule_New(vtable, 0, 0);
#else
    PyObject *ob = PyCObject_FromVoidPtr(vtable, 0);
#endif
    if (!ob)
        goto bad;
    if (PyDict_SetItem(dict, __pyx_n_s_pyx_vtable, ob) < 0)
        goto bad;
    Py_DECREF(ob);
    return 0;
bad:
    Py_XDECREF(ob);
    return -1;
}

/* FetchCommonType */
  static PyTypeObject* __Pyx_FetchCommonType(PyTypeObject* type) {
    PyObject* fake_module;
    PyTypeObject* cached_type = NULL;
    fake_module = PyImport_AddModule((char*) "_cython_" CYTHON_ABI);
    if (!fake_module) return NULL;
    Py_INCREF(fake_module);
    cached_type = (PyTypeObject*) PyObject_GetAttrString(fake_module, type->tp_name);
    if (cached_type) {
        if (!PyType_Check((PyObject*)cached_type)) {
            PyErr_Format(PyExc_TypeError,
                "Shared Cython type %.200s is not a type object",
                type->tp_name);
            goto bad;
        }
        if (cached_type->tp_basicsize != type->tp_basicsize) {
            PyErr_Format(PyExc_TypeError,
                "Shared Cython type %.200s has the wrong size, try recompiling",
                type->tp_name);
            goto bad;
        }
    } else {
        if (!PyErr_ExceptionMatches(PyExc_AttributeError)) goto bad;
        PyErr_Clear();
        if (PyType_Ready(type) < 0) goto bad;
        if (PyObject_SetAttrString(fake_module, type->tp_name, (PyObject*) type) < 0)
            goto bad;
        Py_INCREF(type);
        cached_type = type;
    }
done:
    Py_DECREF(fake_module);
    return cached_type;
bad:
    Py_XDECREF(cached_type);
    cached_type = NULL;
    goto done;
}

/* CythonFunctionShared */
  #include <structmember.h>
static PyObject *
__Pyx_CyFunction_get_doc(__pyx_CyFunctionObject *op, CYTHON_UNUSED void *closure)
{
    if (unlikely(op->func_doc == NULL)) {
        if (op->func.m_ml->ml_doc) {
#if PY_MAJOR_VERSION >= 3
            op->func_doc = PyUnicode_FromString(op->func.m_ml->ml_doc);
#else
            op->func_doc = PyString_FromString(op->func.m_ml->ml_doc);
#endif
            if (unlikely(op->func_doc == NULL))
                return NULL;
        } else {
            Py_INCREF(Py_None);
            return Py_None;
        }
    }
    Py_INCREF(op->func_doc);
    return op->func_doc;
}
static int
__Pyx_CyFunction_set_doc(__pyx_CyFunctionObject *op, PyObject *value, CYTHON_UNUSED void *context)
{
    PyObject *tmp = op->func_doc;
    if (value == NULL) {
        value = Py_None;
    }
    Py_INCREF(value);
    op->func_doc = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_name(__pyx_CyFunctionObject *op, CYTHON_UNUSED void *context)
{
    if (unlikely(op->func_name == NULL)) {
#if PY_MAJOR_VERSION >= 3
        op->func_name = PyUnicode_InternFromString(op->func.m_ml->ml_name);
#else
        op->func_name = PyString_InternFromString(op->func.m_ml->ml_name);
#endif
        if (unlikely(op->func_name == NULL))
            return NULL;
    }
    Py_INCREF(op->func_name);
    return op->func_name;
}
static int
__Pyx_CyFunction_set_name(__pyx_CyFunctionObject *op, PyObject *value, CYTHON_UNUSED void *context)
{
    PyObject *tmp;
#if PY_MAJOR_VERSION >= 3
    if (unlikely(value == NULL || !PyUnicode_Check(value)))
#else
    if (unlikely(value == NULL || !PyString_Check(value)))
#endif
    {
        PyErr_SetString(PyExc_TypeError,
                        "__name__ must be set to a string object");
        return -1;
    }
    tmp = op->func_name;
    Py_INCREF(value);
    op->func_name = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_qualname(__pyx_CyFunctionObject *op, CYTHON_UNUSED void *context)
{
    Py_INCREF(op->func_qualname);
    return op->func_qualname;
}
static int
__Pyx_CyFunction_set_qualname(__pyx_CyFunctionObject *op, PyObject *value, CYTHON_UNUSED void *context)
{
    PyObject *tmp;
#if PY_MAJOR_VERSION >= 3
    if (unlikely(value == NULL || !PyUnicode_Check(value)))
#else
    if (unlikely(value == NULL || !PyString_Check(value)))
#endif
    {
        PyErr_SetString(PyExc_TypeError,
                        "__qualname__ must be set to a string object");
        return -1;
    }
    tmp = op->func_qualname;
    Py_INCREF(value);
    op->func_qualname = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_self(__pyx_CyFunctionObject *m, CYTHON_UNUSED void *closure)
{
    PyObject *self;
    self = m->func_closure;
    if (self == NULL)
        self = Py_None;
    Py_INCREF(self);
    return self;
}
static PyObject *
__Pyx_CyFunction_get_dict(__pyx_CyFunctionObject *op, CYTHON_UNUSED void *context)
{
    if (unlikely(op->func_dict == NULL)) {
        op->func_dict = PyDict_New();
        if (unlikely(op->func_dict == NULL))
            return NULL;
    }
    Py_INCREF(op->func_dict);
    return op->func_dict;
}
static int
__Pyx_CyFunction_set_dict(__pyx_CyFunctionObject *op, PyObject *value, CYTHON_UNUSED void *context)
{
    PyObject *tmp;
    if (unlikely(value == NULL)) {
        PyErr_SetString(PyExc_TypeError,
               "function's dictionary may not be deleted");
        return -1;
    }
    if (unlikely(!PyDict_Check(value))) {
        PyErr_SetString(PyExc_TypeError,
               "setting function's dictionary to a non-dict");
        return -1;
    }
    tmp = op->func_dict;
    Py_INCREF(value);
    op->func_dict = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_globals(__pyx_CyFunctionObject *op, CYTHON_UNUSED void *context)
{
    Py_INCREF(op->func_globals);
    return op->func_globals;
}
static PyObject *
__Pyx_CyFunction_get_closure(CYTHON_UNUSED __pyx_CyFunctionObject *op, CYTHON_UNUSED void *context)
{
    Py_INCREF(Py_None);
    return Py_None;
}
static PyObject *
__Pyx_CyFunction_get_code(__pyx_CyFunctionObject *op, CYTHON_UNUSED void *context)
{
    PyObject* result = (op->func_code) ? op->func_code : Py_None;
    Py_INCREF(result);
    return result;
}
static int
__Pyx_CyFunction_init_defaults(__pyx_CyFunctionObject *op) {
    int result = 0;
    PyObject *res = op->defaults_getter((PyObject *) op);
    if (unlikely(!res))
        return -1;
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    op->defaults_tuple = PyTuple_GET_ITEM(res, 0);
    Py_INCREF(op->defaults_tuple);
    op->defaults_kwdict = PyTuple_GET_ITEM(res, 1);
    Py_INCREF(op->defaults_kwdict);
    #else
    op->defaults_tuple = PySequence_ITEM(res, 0);
    if (unlikely(!op->defaults_tuple)) result = -1;
    else {
        op->defaults_kwdict = PySequence_ITEM(res, 1);
        if (unlikely(!op->defaults_kwdict)) result = -1;
    }
    #endif
    Py_DECREF(res);
    return result;
}
static int
__Pyx_CyFunction_set_defaults(__pyx_CyFunctionObject *op, PyObject* value, CYTHON_UNUSED void *context) {
    PyObject* tmp;
    if (!value) {
        value = Py_None;
    } else if (value != Py_None && !PyTuple_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "__defaults__ must be set to a tuple object");
        return -1;
    }
    Py_INCREF(value);
    tmp = op->defaults_tuple;
    op->defaults_tuple = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_defaults(__pyx_CyFunctionObject *op, CYTHON_UNUSED void *context) {
    PyObject* result = op->defaults_tuple;
    if (unlikely(!result)) {
        if (op->defaults_getter) {
            if (__Pyx_CyFunction_init_defaults(op) < 0) return NULL;
            result = op->defaults_tuple;
        } else {
            result = Py_None;
        }
    }
    Py_INCREF(result);
    return result;
}
static int
__Pyx_CyFunction_set_kwdefaults(__pyx_CyFunctionObject *op, PyObject* value, CYTHON_UNUSED void *context) {
    PyObject* tmp;
    if (!value) {
        value = Py_None;
    } else if (value != Py_None && !PyDict_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "__kwdefaults__ must be set to a dict object");
        return -1;
    }
    Py_INCREF(value);
    tmp = op->defaults_kwdict;
    op->defaults_kwdict = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_kwdefaults(__pyx_CyFunctionObject *op, CYTHON_UNUSED void *context) {
    PyObject* result = op->defaults_kwdict;
    if (unlikely(!result)) {
        if (op->defaults_getter) {
            if (__Pyx_CyFunction_init_defaults(op) < 0) return NULL;
            result = op->defaults_kwdict;
        } else {
            result = Py_None;
        }
    }
    Py_INCREF(result);
    return result;
}
static int
__Pyx_CyFunction_set_annotations(__pyx_CyFunctionObject *op, PyObject* value, CYTHON_UNUSED void *context) {
    PyObject* tmp;
    if (!value || value == Py_None) {
        value = NULL;
    } else if (!PyDict_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "__annotations__ must be set to a dict object");
        return -1;
    }
    Py_XINCREF(value);
    tmp = op->func_annotations;
    op->func_annotations = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_annotations(__pyx_CyFunctionObject *op, CYTHON_UNUSED void *context) {
    PyObject* result = op->func_annotations;
    if (unlikely(!result)) {
        result = PyDict_New();
        if (unlikely(!result)) return NULL;
        op->func_annotations = result;
    }
    Py_INCREF(result);
    return result;
}
static PyGetSetDef __pyx_CyFunction_getsets[] = {
    {(char *) "func_doc", (getter)__Pyx_CyFunction_get_doc, (setter)__Pyx_CyFunction_set_doc, 0, 0},
    {(char *) "__doc__",  (getter)__Pyx_CyFunction_get_doc, (setter)__Pyx_CyFunction_set_doc, 0, 0},
    {(char *) "func_name", (getter)__Pyx_CyFunction_get_name, (setter)__Pyx_CyFunction_set_name, 0, 0},
    {(char *) "__name__", (getter)__Pyx_CyFunction_get_name, (setter)__Pyx_CyFunction_set_name, 0, 0},
    {(char *) "__qualname__", (getter)__Pyx_CyFunction_get_qualname, (setter)__Pyx_CyFunction_set_qualname, 0, 0},
    {(char *) "__self__", (getter)__Pyx_CyFunction_get_self, 0, 0, 0},
    {(char *) "func_dict", (getter)__Pyx_CyFunction_get_dict, (setter)__Pyx_CyFunction_set_dict, 0, 0},
    {(char *) "__dict__", (getter)__Pyx_CyFunction_get_dict, (setter)__Pyx_CyFunction_set_dict, 0, 0},
    {(char *) "func_globals", (getter)__Pyx_CyFunction_get_globals, 0, 0, 0},
    {(char *) "__globals__", (getter)__Pyx_CyFunction_get_globals, 0, 0, 0},
    {(char *) "func_closure", (getter)__Pyx_CyFunction_get_closure, 0, 0, 0},
    {(char *) "__closure__", (getter)__Pyx_CyFunction_get_closure, 0, 0, 0},
    {(char *) "func_code", (getter)__Pyx_CyFunction_get_code, 0, 0, 0},
    {(char *) "__code__", (getter)__Pyx_CyFunction_get_code, 0, 0, 0},
    {(char *) "func_defaults", (getter)__Pyx_CyFunction_get_defaults, (setter)__Pyx_CyFunction_set_defaults, 0, 0},
    {(char *) "__defaults__", (getter)__Pyx_CyFunction_get_defaults, (setter)__Pyx_CyFunction_set_defaults, 0, 0},
    {(char *) "__kwdefaults__", (getter)__Pyx_CyFunction_get_kwdefaults, (setter)__Pyx_CyFunction_set_kwdefaults, 0, 0},
    {(char *) "__annotations__", (getter)__Pyx_CyFunction_get_annotations, (setter)__Pyx_CyFunction_set_annotations, 0, 0},
    {0, 0, 0, 0, 0}
};
static PyMemberDef __pyx_CyFunction_members[] = {
    {(char *) "__module__", T_OBJECT, offsetof(PyCFunctionObject, m_module), PY_WRITE_RESTRICTED, 0},
    {0, 0, 0,  0, 0}
};
static PyObject *
__Pyx_CyFunction_reduce(__pyx_CyFunctionObject *m, CYTHON_UNUSED PyObject *args)
{
#if PY_MAJOR_VERSION >= 3
    return PyUnicode_FromString(m->func.m_ml->ml_name);
#else
    return PyString_FromString(m->func.m_ml->ml_name);
#endif
}
static PyMethodDef __pyx_CyFunction_methods[] = {
    {"__reduce__", (PyCFunction)__Pyx_CyFunction_reduce, METH_VARARGS, 0},
    {0, 0, 0, 0}
};
#if PY_VERSION_HEX < 0x030500A0
#define __Pyx_CyFunction_weakreflist(cyfunc) ((cyfunc)->func_weakreflist)
#else
#define __Pyx_CyFunction_weakreflist(cyfunc) ((cyfunc)->func.m_weakreflist)
#endif
static PyObject *__Pyx_CyFunction_Init(__pyx_CyFunctionObject *op, PyMethodDef *ml, int flags, PyObject* qualname,
                                       PyObject *closure, PyObject *module, PyObject* globals, PyObject* code) {
    if (unlikely(op == NULL))
        return NULL;
    op->flags = flags;
    __Pyx_CyFunction_weakreflist(op) = NULL;
    op->func.m_ml = ml;
    op->func.m_self = (PyObject *) op;
    Py_XINCREF(closure);
    op->func_closure = closure;
    Py_XINCREF(module);
    op->func.m_module = module;
    op->func_dict = NULL;
    op->func_name = NULL;
    Py_INCREF(qualname);
    op->func_qualname = qualname;
    op->func_doc = NULL;
    op->func_classobj = NULL;
    op->func_globals = globals;
    Py_INCREF(op->func_globals);
    Py_XINCREF(code);
    op->func_code = code;
    op->defaults_pyobjects = 0;
    op->defaults_size = 0;
    op->defaults = NULL;
    op->defaults_tuple = NULL;
    op->defaults_kwdict = NULL;
    op->defaults_getter = NULL;
    op->func_annotations = NULL;
    return (PyObject *) op;
}
static int
__Pyx_CyFunction_clear(__pyx_CyFunctionObject *m)
{
    Py_CLEAR(m->func_closure);
    Py_CLEAR(m->func.m_module);
    Py_CLEAR(m->func_dict);
    Py_CLEAR(m->func_name);
    Py_CLEAR(m->func_qualname);
    Py_CLEAR(m->func_doc);
    Py_CLEAR(m->func_globals);
    Py_CLEAR(m->func_code);
    Py_CLEAR(m->func_classobj);
    Py_CLEAR(m->defaults_tuple);
    Py_CLEAR(m->defaults_kwdict);
    Py_CLEAR(m->func_annotations);
    if (m->defaults) {
        PyObject **pydefaults = __Pyx_CyFunction_Defaults(PyObject *, m);
        int i;
        for (i = 0; i < m->defaults_pyobjects; i++)
            Py_XDECREF(pydefaults[i]);
        PyObject_Free(m->defaults);
        m->defaults = NULL;
    }
    return 0;
}
static void __Pyx__CyFunction_dealloc(__pyx_CyFunctionObject *m)
{
    if (__Pyx_CyFunction_weakreflist(m) != NULL)
        PyObject_ClearWeakRefs((PyObject *) m);
    __Pyx_CyFunction_clear(m);
    PyObject_GC_Del(m);
}
static void __Pyx_CyFunction_dealloc(__pyx_CyFunctionObject *m)
{
    PyObject_GC_UnTrack(m);
    __Pyx__CyFunction_dealloc(m);
}
static int __Pyx_CyFunction_traverse(__pyx_CyFunctionObject *m, visitproc visit, void *arg)
{
    Py_VISIT(m->func_closure);
    Py_VISIT(m->func.m_module);
    Py_VISIT(m->func_dict);
    Py_VISIT(m->func_name);
    Py_VISIT(m->func_qualname);
    Py_VISIT(m->func_doc);
    Py_VISIT(m->func_globals);
    Py_VISIT(m->func_code);
    Py_VISIT(m->func_classobj);
    Py_VISIT(m->defaults_tuple);
    Py_VISIT(m->defaults_kwdict);
    if (m->defaults) {
        PyObject **pydefaults = __Pyx_CyFunction_Defaults(PyObject *, m);
        int i;
        for (i = 0; i < m->defaults_pyobjects; i++)
            Py_VISIT(pydefaults[i]);
    }
    return 0;
}
static PyObject *__Pyx_CyFunction_descr_get(PyObject *func, PyObject *obj, PyObject *type)
{
#if PY_MAJOR_VERSION < 3
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    if (m->flags & __Pyx_CYFUNCTION_STATICMETHOD) {
        Py_INCREF(func);
        return func;
    }
    if (m->flags & __Pyx_CYFUNCTION_CLASSMETHOD) {
        if (type == NULL)
            type = (PyObject *)(Py_TYPE(obj));
        return __Pyx_PyMethod_New(func, type, (PyObject *)(Py_TYPE(type)));
    }
    if (obj == Py_None)
        obj = NULL;
#endif
    return __Pyx_PyMethod_New(func, obj, type);
}
static PyObject*
__Pyx_CyFunction_repr(__pyx_CyFunctionObject *op)
{
#if PY_MAJOR_VERSION >= 3
    return PyUnicode_FromFormat("<cyfunction %U at %p>",
                                op->func_qualname, (void *)op);
#else
    return PyString_FromFormat("<cyfunction %s at %p>",
                               PyString_AsString(op->func_qualname), (void *)op);
#endif
}
static PyObject * __Pyx_CyFunction_CallMethod(PyObject *func, PyObject *self, PyObject *arg, PyObject *kw) {
    PyCFunctionObject* f = (PyCFunctionObject*)func;
    PyCFunction meth = f->m_ml->ml_meth;
    Py_ssize_t size;
    switch (f->m_ml->ml_flags & (METH_VARARGS | METH_KEYWORDS | METH_NOARGS | METH_O)) {
    case METH_VARARGS:
        if (likely(kw == NULL || PyDict_Size(kw) == 0))
            return (*meth)(self, arg);
        break;
    case METH_VARARGS | METH_KEYWORDS:
        return (*(PyCFunctionWithKeywords)(void*)meth)(self, arg, kw);
    case METH_NOARGS:
        if (likely(kw == NULL || PyDict_Size(kw) == 0)) {
            size = PyTuple_GET_SIZE(arg);
            if (likely(size == 0))
                return (*meth)(self, NULL);
            PyErr_Format(PyExc_TypeError,
                "%.200s() takes no arguments (%" CYTHON_FORMAT_SSIZE_T "d given)",
                f->m_ml->ml_name, size);
            return NULL;
        }
        break;
    case METH_O:
        if (likely(kw == NULL || PyDict_Size(kw) == 0)) {
            size = PyTuple_GET_SIZE(arg);
            if (likely(size == 1)) {
                PyObject *result, *arg0;
                #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
                arg0 = PyTuple_GET_ITEM(arg, 0);
                #else
                arg0 = PySequence_ITEM(arg, 0); if (unlikely(!arg0)) return NULL;
                #endif
                result = (*meth)(self, arg0);
                #if !(CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS)
                Py_DECREF(arg0);
                #endif
                return result;
            }
            PyErr_Format(PyExc_TypeError,
                "%.200s() takes exactly one argument (%" CYTHON_FORMAT_SSIZE_T "d given)",
                f->m_ml->ml_name, size);
            return NULL;
        }
        break;
    default:
        PyErr_SetString(PyExc_SystemError, "Bad call flags in "
                        "__Pyx_CyFunction_Call. METH_OLDARGS is no "
                        "longer supported!");
        return NULL;
    }
    PyErr_Format(PyExc_TypeError, "%.200s() takes no keyword arguments",
                 f->m_ml->ml_name);
    return NULL;
}
static CYTHON_INLINE PyObject *__Pyx_CyFunction_Call(PyObject *func, PyObject *arg, PyObject *kw) {
    return __Pyx_CyFunction_CallMethod(func, ((PyCFunctionObject*)func)->m_self, arg, kw);
}
static PyObject *__Pyx_CyFunction_CallAsMethod(PyObject *func, PyObject *args, PyObject *kw) {
    PyObject *result;
    __pyx_CyFunctionObject *cyfunc = (__pyx_CyFunctionObject *) func;
    if ((cyfunc->flags & __Pyx_CYFUNCTION_CCLASS) && !(cyfunc->flags & __Pyx_CYFUNCTION_STATICMETHOD)) {
        Py_ssize_t argc;
        PyObject *new_args;
        PyObject *self;
        argc = PyTuple_GET_SIZE(args);
        new_args = PyTuple_GetSlice(args, 1, argc);
        if (unlikely(!new_args))
            return NULL;
        self = PyTuple_GetItem(args, 0);
        if (unlikely(!self)) {
            Py_DECREF(new_args);
            return NULL;
        }
        result = __Pyx_CyFunction_CallMethod(func, self, new_args, kw);
        Py_DECREF(new_args);
    } else {
        result = __Pyx_CyFunction_Call(func, args, kw);
    }
    return result;
}
static PyTypeObject __pyx_CyFunctionType_type = {
    PyVarObject_HEAD_INIT(0, 0)
    "cython_function_or_method",
    sizeof(__pyx_CyFunctionObject),
    0,
    (destructor) __Pyx_CyFunction_dealloc,
    0,
    0,
    0,
#if PY_MAJOR_VERSION < 3
    0,
#else
    0,
#endif
    (reprfunc) __Pyx_CyFunction_repr,
    0,
    0,
    0,
    0,
    __Pyx_CyFunction_CallAsMethod,
    0,
    0,
    0,
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
    0,
    (traverseproc) __Pyx_CyFunction_traverse,
    (inquiry) __Pyx_CyFunction_clear,
    0,
#if PY_VERSION_HEX < 0x030500A0
    offsetof(__pyx_CyFunctionObject, func_weakreflist),
#else
    offsetof(PyCFunctionObject, m_weakreflist),
#endif
    0,
    0,
    __pyx_CyFunction_methods,
    __pyx_CyFunction_members,
    __pyx_CyFunction_getsets,
    0,
    0,
    __Pyx_CyFunction_descr_get,
    0,
    offsetof(__pyx_CyFunctionObject, func_dict),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
#if PY_VERSION_HEX >= 0x030400a1
    0,
#endif
#if PY_VERSION_HEX >= 0x030800b1
    0,
#endif
#if PY_VERSION_HEX >= 0x030800b4 && PY_VERSION_HEX < 0x03090000
    0,
#endif
};
static int __pyx_CyFunction_init(void) {
    __pyx_CyFunctionType = __Pyx_FetchCommonType(&__pyx_CyFunctionType_type);
    if (unlikely(__pyx_CyFunctionType == NULL)) {
        return -1;
    }
    return 0;
}
static CYTHON_INLINE void *__Pyx_CyFunction_InitDefaults(PyObject *func, size_t size, int pyobjects) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->defaults = PyObject_Malloc(size);
    if (unlikely(!m->defaults))
        return PyErr_NoMemory();
    memset(m->defaults, 0, size);
    m->defaults_pyobjects = pyobjects;
    m->defaults_size = size;
    return m->defaults;
}
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsTuple(PyObject *func, PyObject *tuple) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->defaults_tuple = tuple;
    Py_INCREF(tuple);
}
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsKwDict(PyObject *func, PyObject *dict) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->defaults_kwdict = dict;
    Py_INCREF(dict);
}
static CYTHON_INLINE void __Pyx_CyFunction_SetAnnotationsDict(PyObject *func, PyObject *dict) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->func_annotations = dict;
    Py_INCREF(dict);
}

/* CythonFunction */
  static PyObject *__Pyx_CyFunction_New(PyMethodDef *ml, int flags, PyObject* qualname,
                                      PyObject *closure, PyObject *module, PyObject* globals, PyObject* code) {
    PyObject *op = __Pyx_CyFunction_Init(
        PyObject_GC_New(__pyx_CyFunctionObject, __pyx_CyFunctionType),
        ml, flags, qualname, closure, module, globals, code
    );
    if (likely(op)) {
        PyObject_GC_Track(op);
    }
    return op;
}

/* GetTopmostException */
  #if CYTHON_USE_EXC_INFO_STACK
static _PyErr_StackItem *
__Pyx_PyErr_GetTopmostException(PyThreadState *tstate)
{
    _PyErr_StackItem *exc_info = tstate->exc_info;
    while ((exc_info->exc_type == NULL || exc_info->exc_type == Py_None) &&
           exc_info->previous_item != NULL)
    {
        exc_info = exc_info->previous_item;
    }
    return exc_info;
}
#endif

/* SaveResetException */
  #if CYTHON_FAST_THREAD_STATE
static CYTHON_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
    #if CYTHON_USE_EXC_INFO_STACK
    _PyErr_StackItem *exc_info = __Pyx_PyErr_GetTopmostException(tstate);
    *type = exc_info->exc_type;
    *value = exc_info->exc_value;
    *tb = exc_info->exc_traceback;
    #else
    *type = tstate->exc_type;
    *value = tstate->exc_value;
    *tb = tstate->exc_traceback;
    #endif
    Py_XINCREF(*type);
    Py_XINCREF(*value);
    Py_XINCREF(*tb);
}
static CYTHON_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb) {
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    #if CYTHON_USE_EXC_INFO_STACK
    _PyErr_StackItem *exc_info = tstate->exc_info;
    tmp_type = exc_info->exc_type;
    tmp_value = exc_info->exc_value;
    tmp_tb = exc_info->exc_traceback;
    exc_info->exc_type = type;
    exc_info->exc_value = value;
    exc_info->exc_traceback = tb;
    #else
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = type;
    tstate->exc_value = value;
    tstate->exc_traceback = tb;
    #endif
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
}
#endif

/* GetException */
  #if CYTHON_FAST_THREAD_STATE
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb)
#else
static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb)
#endif
{
    PyObject *local_type, *local_value, *local_tb;
#if CYTHON_FAST_THREAD_STATE
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    local_type = tstate->curexc_type;
    local_value = tstate->curexc_value;
    local_tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
#else
    PyErr_Fetch(&local_type, &local_value, &local_tb);
#endif
    PyErr_NormalizeException(&local_type, &local_value, &local_tb);
#if CYTHON_FAST_THREAD_STATE
    if (unlikely(tstate->curexc_type))
#else
    if (unlikely(PyErr_Occurred()))
#endif
        goto bad;
    #if PY_MAJOR_VERSION >= 3
    if (local_tb) {
        if (unlikely(PyException_SetTraceback(local_value, local_tb) < 0))
            goto bad;
    }
    #endif
    Py_XINCREF(local_tb);
    Py_XINCREF(local_type);
    Py_XINCREF(local_value);
    *type = local_type;
    *value = local_value;
    *tb = local_tb;
#if CYTHON_FAST_THREAD_STATE
    #if CYTHON_USE_EXC_INFO_STACK
    {
        _PyErr_StackItem *exc_info = tstate->exc_info;
        tmp_type = exc_info->exc_type;
        tmp_value = exc_info->exc_value;
        tmp_tb = exc_info->exc_traceback;
        exc_info->exc_type = local_type;
        exc_info->exc_value = local_value;
        exc_info->exc_traceback = local_tb;
    }
    #else
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = local_type;
    tstate->exc_value = local_value;
    tstate->exc_traceback = local_tb;
    #endif
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
#else
    PyErr_SetExcInfo(local_type, local_value, local_tb);
#endif
    return 0;
bad:
    *type = 0;
    *value = 0;
    *tb = 0;
    Py_XDECREF(local_type);
    Py_XDECREF(local_value);
    Py_XDECREF(local_tb);
    return -1;
}

/* CLineInTraceback */
  #ifndef CYTHON_CLINE_IN_TRACEBACK
static int __Pyx_CLineForTraceback(CYTHON_NCP_UNUSED PyThreadState *tstate, int c_line) {
    PyObject *use_cline;
    PyObject *ptype, *pvalue, *ptraceback;
#if CYTHON_COMPILING_IN_CPYTHON
    PyObject **cython_runtime_dict;
#endif
    if (unlikely(!__pyx_cython_runtime)) {
        return c_line;
    }
    __Pyx_ErrFetchInState(tstate, &ptype, &pvalue, &ptraceback);
#if CYTHON_COMPILING_IN_CPYTHON
    cython_runtime_dict = _PyObject_GetDictPtr(__pyx_cython_runtime);
    if (likely(cython_runtime_dict)) {
        __PYX_PY_DICT_LOOKUP_IF_MODIFIED(
            use_cline, *cython_runtime_dict,
            __Pyx_PyDict_GetItemStr(*cython_runtime_dict, __pyx_n_s_cline_in_traceback))
    } else
#endif
    {
      PyObject *use_cline_obj = __Pyx_PyObject_GetAttrStr(__pyx_cython_runtime, __pyx_n_s_cline_in_traceback);
      if (use_cline_obj) {
        use_cline = PyObject_Not(use_cline_obj) ? Py_False : Py_True;
        Py_DECREF(use_cline_obj);
      } else {
        PyErr_Clear();
        use_cline = NULL;
      }
    }
    if (!use_cline) {
        c_line = 0;
        PyObject_SetAttr(__pyx_cython_runtime, __pyx_n_s_cline_in_traceback, Py_False);
    }
    else if (use_cline == Py_False || (use_cline != Py_True && PyObject_Not(use_cline) != 0)) {
        c_line = 0;
    }
    __Pyx_ErrRestoreInState(tstate, ptype, pvalue, ptraceback);
    return c_line;
}
#endif

/* CodeObjectCache */
  static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line) {
    int start = 0, mid = 0, end = count - 1;
    if (end >= 0 && code_line > entries[end].code_line) {
        return count;
    }
    while (start < end) {
        mid = start + (end - start) / 2;
        if (code_line < entries[mid].code_line) {
            end = mid;
        } else if (code_line > entries[mid].code_line) {
             start = mid + 1;
        } else {
            return mid;
        }
    }
    if (code_line <= entries[mid].code_line) {
        return mid;
    } else {
        return mid + 1;
    }
}
static PyCodeObject *__pyx_find_code_object(int code_line) {
    PyCodeObject* code_object;
    int pos;
    if (unlikely(!code_line) || unlikely(!__pyx_code_cache.entries)) {
        return NULL;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if (unlikely(pos >= __pyx_code_cache.count) || unlikely(__pyx_code_cache.entries[pos].code_line != code_line)) {
        return NULL;
    }
    code_object = __pyx_code_cache.entries[pos].code_object;
    Py_INCREF(code_object);
    return code_object;
}
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object) {
    int pos, i;
    __Pyx_CodeObjectCacheEntry* entries = __pyx_code_cache.entries;
    if (unlikely(!code_line)) {
        return;
    }
    if (unlikely(!entries)) {
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Malloc(64*sizeof(__Pyx_CodeObjectCacheEntry));
        if (likely(entries)) {
            __pyx_code_cache.entries = entries;
            __pyx_code_cache.max_count = 64;
            __pyx_code_cache.count = 1;
            entries[0].code_line = code_line;
            entries[0].code_object = code_object;
            Py_INCREF(code_object);
        }
        return;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if ((pos < __pyx_code_cache.count) && unlikely(__pyx_code_cache.entries[pos].code_line == code_line)) {
        PyCodeObject* tmp = entries[pos].code_object;
        entries[pos].code_object = code_object;
        Py_DECREF(tmp);
        return;
    }
    if (__pyx_code_cache.count == __pyx_code_cache.max_count) {
        int new_max = __pyx_code_cache.max_count + 64;
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Realloc(
            __pyx_code_cache.entries, ((size_t)new_max) * sizeof(__Pyx_CodeObjectCacheEntry));
        if (unlikely(!entries)) {
            return;
        }
        __pyx_code_cache.entries = entries;
        __pyx_code_cache.max_count = new_max;
    }
    for (i=__pyx_code_cache.count; i>pos; i--) {
        entries[i] = entries[i-1];
    }
    entries[pos].code_line = code_line;
    entries[pos].code_object = code_object;
    __pyx_code_cache.count++;
    Py_INCREF(code_object);
}

/* AddTraceback */
  #include "compile.h"
#include "frameobject.h"
#include "traceback.h"
static PyCodeObject* __Pyx_CreateCodeObjectForTraceback(
            const char *funcname, int c_line,
            int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyObject *py_srcfile = 0;
    PyObject *py_funcname = 0;
    #if PY_MAJOR_VERSION < 3
    py_srcfile = PyString_FromString(filename);
    #else
    py_srcfile = PyUnicode_FromString(filename);
    #endif
    if (!py_srcfile) goto bad;
    if (c_line) {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #else
        py_funcname = PyUnicode_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #endif
    }
    else {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromString(funcname);
        #else
        py_funcname = PyUnicode_FromString(funcname);
        #endif
    }
    if (!py_funcname) goto bad;
    py_code = __Pyx_PyCode_New(
        0,
        0,
        0,
        0,
        0,
        __pyx_empty_bytes, /*PyObject *code,*/
        __pyx_empty_tuple, /*PyObject *consts,*/
        __pyx_empty_tuple, /*PyObject *names,*/
        __pyx_empty_tuple, /*PyObject *varnames,*/
        __pyx_empty_tuple, /*PyObject *freevars,*/
        __pyx_empty_tuple, /*PyObject *cellvars,*/
        py_srcfile,   /*PyObject *filename,*/
        py_funcname,  /*PyObject *name,*/
        py_line,
        __pyx_empty_bytes  /*PyObject *lnotab*/
    );
    Py_DECREF(py_srcfile);
    Py_DECREF(py_funcname);
    return py_code;
bad:
    Py_XDECREF(py_srcfile);
    Py_XDECREF(py_funcname);
    return NULL;
}
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyFrameObject *py_frame = 0;
    PyThreadState *tstate = __Pyx_PyThreadState_Current;
    if (c_line) {
        c_line = __Pyx_CLineForTraceback(tstate, c_line);
    }
    py_code = __pyx_find_code_object(c_line ? -c_line : py_line);
    if (!py_code) {
        py_code = __Pyx_CreateCodeObjectForTraceback(
            funcname, c_line, py_line, filename);
        if (!py_code) goto bad;
        __pyx_insert_code_object(c_line ? -c_line : py_line, py_code);
    }
    py_frame = PyFrame_New(
        tstate,            /*PyThreadState *tstate,*/
        py_code,           /*PyCodeObject *code,*/
        __pyx_d,    /*PyObject *globals,*/
        0                  /*PyObject *locals*/
    );
    if (!py_frame) goto bad;
    __Pyx_PyFrame_SetLineNumber(py_frame, py_line);
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}

/* CIntFromPyVerify */
  #define __PYX_VERIFY_RETURN_INT(target_type, func_type, func_value)\
    __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, 0)
#define __PYX_VERIFY_RETURN_INT_EXC(target_type, func_type, func_value)\
    __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, 1)
#define __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, exc)\
    {\
        func_type value = func_value;\
        if (sizeof(target_type) < sizeof(func_type)) {\
            if (unlikely(value != (func_type) (target_type) value)) {\
                func_type zero = 0;\
                if (exc && unlikely(value == (func_type)-1 && PyErr_Occurred()))\
                    return (target_type) -1;\
                if (is_unsigned && unlikely(value < zero))\
                    goto raise_neg_overflow;\
                else\
                    goto raise_overflow;\
            }\
        }\
        return (target_type) value;\
    }

/* Print */
  #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION < 3
static PyObject *__Pyx_GetStdout(void) {
    PyObject *f = PySys_GetObject((char *)"stdout");
    if (!f) {
        PyErr_SetString(PyExc_RuntimeError, "lost sys.stdout");
    }
    return f;
}
static int __Pyx_Print(PyObject* f, PyObject *arg_tuple, int newline) {
    int i;
    if (!f) {
        if (!(f = __Pyx_GetStdout()))
            return -1;
    }
    Py_INCREF(f);
    for (i=0; i < PyTuple_GET_SIZE(arg_tuple); i++) {
        PyObject* v;
        if (PyFile_SoftSpace(f, 1)) {
            if (PyFile_WriteString(" ", f) < 0)
                goto error;
        }
        v = PyTuple_GET_ITEM(arg_tuple, i);
        if (PyFile_WriteObject(v, f, Py_PRINT_RAW) < 0)
            goto error;
        if (PyString_Check(v)) {
            char *s = PyString_AsString(v);
            Py_ssize_t len = PyString_Size(v);
            if (len > 0) {
                switch (s[len-1]) {
                    case ' ': break;
                    case '\f': case '\r': case '\n': case '\t': case '\v':
                        PyFile_SoftSpace(f, 0);
                        break;
                    default:  break;
                }
            }
        }
    }
    if (newline) {
        if (PyFile_WriteString("\n", f) < 0)
            goto error;
        PyFile_SoftSpace(f, 0);
    }
    Py_DECREF(f);
    return 0;
error:
    Py_DECREF(f);
    return -1;
}
#else
static int __Pyx_Print(PyObject* stream, PyObject *arg_tuple, int newline) {
    PyObject* kwargs = 0;
    PyObject* result = 0;
    PyObject* end_string;
    if (unlikely(!__pyx_print)) {
        __pyx_print = PyObject_GetAttr(__pyx_b, __pyx_n_s_print);
        if (!__pyx_print)
            return -1;
    }
    if (stream) {
        kwargs = PyDict_New();
        if (unlikely(!kwargs))
            return -1;
        if (unlikely(PyDict_SetItem(kwargs, __pyx_n_s_file, stream) < 0))
            goto bad;
        if (!newline) {
            end_string = PyUnicode_FromStringAndSize(" ", 1);
            if (unlikely(!end_string))
                goto bad;
            if (PyDict_SetItem(kwargs, __pyx_n_s_end, end_string) < 0) {
                Py_DECREF(end_string);
                goto bad;
            }
            Py_DECREF(end_string);
        }
    } else if (!newline) {
        if (unlikely(!__pyx_print_kwargs)) {
            __pyx_print_kwargs = PyDict_New();
            if (unlikely(!__pyx_print_kwargs))
                return -1;
            end_string = PyUnicode_FromStringAndSize(" ", 1);
            if (unlikely(!end_string))
                return -1;
            if (PyDict_SetItem(__pyx_print_kwargs, __pyx_n_s_end, end_string) < 0) {
                Py_DECREF(end_string);
                return -1;
            }
            Py_DECREF(end_string);
        }
        kwargs = __pyx_print_kwargs;
    }
    result = PyObject_Call(__pyx_print, arg_tuple, kwargs);
    if (unlikely(kwargs) && (kwargs != __pyx_print_kwargs))
        Py_DECREF(kwargs);
    if (!result)
        return -1;
    Py_DECREF(result);
    return 0;
bad:
    if (kwargs != __pyx_print_kwargs)
        Py_XDECREF(kwargs);
    return -1;
}
#endif

/* CIntToPy */
  static CYTHON_INLINE PyObject* __Pyx_PyInt_From_int(int value) {
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    const int neg_one = (int) -1, const_zero = (int) 0;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic pop
#endif
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(int) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(int) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(int) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
#endif
        }
    } else {
        if (sizeof(int) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(int) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
#endif
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(int),
                                     little, !is_unsigned);
    }
}

/* CIntFromPy */
  static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *x) {
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    const int neg_one = (int) -1, const_zero = (int) 0;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic pop
#endif
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(int) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(int, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (int) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (int) 0;
                case  1: __PYX_VERIFY_RETURN_INT(int, digit, digits[0])
                case 2:
                    if (8 * sizeof(int) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 2 * PyLong_SHIFT) {
                            return (int) (((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(int) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 3 * PyLong_SHIFT) {
                            return (int) (((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(int) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 4 * PyLong_SHIFT) {
                            return (int) (((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (int) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(int) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, unsigned long, PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(int) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
#endif
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (int) 0;
                case -1: __PYX_VERIFY_RETURN_INT(int, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(int,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(int) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(int) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                            return (int) ((((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(int) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                            return (int) ((((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 4 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(int) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 4 * PyLong_SHIFT) {
                            return (int) ((((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(int) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, long, PyLong_AsLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(int) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, PY_LONG_LONG, PyLong_AsLongLong(x))
#endif
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            int val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (int) -1;
        }
    } else {
        int val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (int) -1;
        val = __Pyx_PyInt_As_int(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to int");
    return (int) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to int");
    return (int) -1;
}

/* CIntFromPy */
  static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *x) {
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    const long neg_one = (long) -1, const_zero = (long) 0;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic pop
#endif
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(long) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(long, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (long) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (long) 0;
                case  1: __PYX_VERIFY_RETURN_INT(long, digit, digits[0])
                case 2:
                    if (8 * sizeof(long) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 2 * PyLong_SHIFT) {
                            return (long) (((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(long) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 3 * PyLong_SHIFT) {
                            return (long) (((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(long) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 4 * PyLong_SHIFT) {
                            return (long) (((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (long) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(long) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, unsigned long, PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
#endif
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (long) 0;
                case -1: __PYX_VERIFY_RETURN_INT(long, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(long,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(long) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(long) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                            return (long) ((((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(long) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                            return (long) ((((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(long) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                            return (long) ((((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(long) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, long, PyLong_AsLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, PY_LONG_LONG, PyLong_AsLongLong(x))
#endif
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            long val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (long) -1;
        }
    } else {
        long val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (long) -1;
        val = __Pyx_PyInt_As_long(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to long");
    return (long) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to long");
    return (long) -1;
}

/* CIntToPy */
  static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value) {
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    const long neg_one = (long) -1, const_zero = (long) 0;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic pop
#endif
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(long) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(long) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
#endif
        }
    } else {
        if (sizeof(long) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
#endif
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(long),
                                     little, !is_unsigned);
    }
}

/* PrintOne */
  #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION < 3
static int __Pyx_PrintOne(PyObject* f, PyObject *o) {
    if (!f) {
        if (!(f = __Pyx_GetStdout()))
            return -1;
    }
    Py_INCREF(f);
    if (PyFile_SoftSpace(f, 0)) {
        if (PyFile_WriteString(" ", f) < 0)
            goto error;
    }
    if (PyFile_WriteObject(o, f, Py_PRINT_RAW) < 0)
        goto error;
    if (PyFile_WriteString("\n", f) < 0)
        goto error;
    Py_DECREF(f);
    return 0;
error:
    Py_DECREF(f);
    return -1;
    /* the line below is just to avoid C compiler
     * warnings about unused functions */
    return __Pyx_Print(f, NULL, 0);
}
#else
static int __Pyx_PrintOne(PyObject* stream, PyObject *o) {
    int res;
    PyObject* arg_tuple = PyTuple_Pack(1, o);
    if (unlikely(!arg_tuple))
        return -1;
    res = __Pyx_Print(stream, arg_tuple, 1);
    Py_DECREF(arg_tuple);
    return res;
}
#endif

/* FastTypeChecks */
  #if CYTHON_COMPILING_IN_CPYTHON
static int __Pyx_InBases(PyTypeObject *a, PyTypeObject *b) {
    while (a) {
        a = a->tp_base;
        if (a == b)
            return 1;
    }
    return b == &PyBaseObject_Type;
}
static CYTHON_INLINE int __Pyx_IsSubtype(PyTypeObject *a, PyTypeObject *b) {
    PyObject *mro;
    if (a == b) return 1;
    mro = a->tp_mro;
    if (likely(mro)) {
        Py_ssize_t i, n;
        n = PyTuple_GET_SIZE(mro);
        for (i = 0; i < n; i++) {
            if (PyTuple_GET_ITEM(mro, i) == (PyObject *)b)
                return 1;
        }
        return 0;
    }
    return __Pyx_InBases(a, b);
}
#if PY_MAJOR_VERSION == 2
static int __Pyx_inner_PyErr_GivenExceptionMatches2(PyObject *err, PyObject* exc_type1, PyObject* exc_type2) {
    PyObject *exception, *value, *tb;
    int res;
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ErrFetch(&exception, &value, &tb);
    res = exc_type1 ? PyObject_IsSubclass(err, exc_type1) : 0;
    if (unlikely(res == -1)) {
        PyErr_WriteUnraisable(err);
        res = 0;
    }
    if (!res) {
        res = PyObject_IsSubclass(err, exc_type2);
        if (unlikely(res == -1)) {
            PyErr_WriteUnraisable(err);
            res = 0;
        }
    }
    __Pyx_ErrRestore(exception, value, tb);
    return res;
}
#else
static CYTHON_INLINE int __Pyx_inner_PyErr_GivenExceptionMatches2(PyObject *err, PyObject* exc_type1, PyObject *exc_type2) {
    int res = exc_type1 ? __Pyx_IsSubtype((PyTypeObject*)err, (PyTypeObject*)exc_type1) : 0;
    if (!res) {
        res = __Pyx_IsSubtype((PyTypeObject*)err, (PyTypeObject*)exc_type2);
    }
    return res;
}
#endif
static int __Pyx_PyErr_GivenExceptionMatchesTuple(PyObject *exc_type, PyObject *tuple) {
    Py_ssize_t i, n;
    assert(PyExceptionClass_Check(exc_type));
    n = PyTuple_GET_SIZE(tuple);
#if PY_MAJOR_VERSION >= 3
    for (i=0; i<n; i++) {
        if (exc_type == PyTuple_GET_ITEM(tuple, i)) return 1;
    }
#endif
    for (i=0; i<n; i++) {
        PyObject *t = PyTuple_GET_ITEM(tuple, i);
        #if PY_MAJOR_VERSION < 3
        if (likely(exc_type == t)) return 1;
        #endif
        if (likely(PyExceptionClass_Check(t))) {
            if (__Pyx_inner_PyErr_GivenExceptionMatches2(exc_type, NULL, t)) return 1;
        } else {
        }
    }
    return 0;
}
static CYTHON_INLINE int __Pyx_PyErr_GivenExceptionMatches(PyObject *err, PyObject* exc_type) {
    if (likely(err == exc_type)) return 1;
    if (likely(PyExceptionClass_Check(err))) {
        if (likely(PyExceptionClass_Check(exc_type))) {
            return __Pyx_inner_PyErr_GivenExceptionMatches2(err, NULL, exc_type);
        } else if (likely(PyTuple_Check(exc_type))) {
            return __Pyx_PyErr_GivenExceptionMatchesTuple(err, exc_type);
        } else {
        }
    }
    return PyErr_GivenExceptionMatches(err, exc_type);
}
static CYTHON_INLINE int __Pyx_PyErr_GivenExceptionMatches2(PyObject *err, PyObject *exc_type1, PyObject *exc_type2) {
    assert(PyExceptionClass_Check(exc_type1));
    assert(PyExceptionClass_Check(exc_type2));
    if (likely(err == exc_type1 || err == exc_type2)) return 1;
    if (likely(PyExceptionClass_Check(err))) {
        return __Pyx_inner_PyErr_GivenExceptionMatches2(err, exc_type1, exc_type2);
    }
    return (PyErr_GivenExceptionMatches(err, exc_type1) || PyErr_GivenExceptionMatches(err, exc_type2));
}
#endif

/* CheckBinaryVersion */
  static int __Pyx_check_binary_version(void) {
    char ctversion[4], rtversion[4];
    PyOS_snprintf(ctversion, 4, "%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
    PyOS_snprintf(rtversion, 4, "%s", Py_GetVersion());
    if (ctversion[0] != rtversion[0] || ctversion[2] != rtversion[2]) {
        char message[200];
        PyOS_snprintf(message, sizeof(message),
                      "compiletime version %s of module '%.100s' "
                      "does not match runtime version %s",
                      ctversion, __Pyx_MODULE_NAME, rtversion);
        return PyErr_WarnEx(NULL, message, 1);
    }
    return 0;
}

/* FunctionExport */
  static int __Pyx_ExportFunction(const char *name, void (*f)(void), const char *sig) {
    PyObject *d = 0;
    PyObject *cobj = 0;
    union {
        void (*fp)(void);
        void *p;
    } tmp;
    d = PyObject_GetAttrString(__pyx_m, (char *)"__pyx_capi__");
    if (!d) {
        PyErr_Clear();
        d = PyDict_New();
        if (!d)
            goto bad;
        Py_INCREF(d);
        if (PyModule_AddObject(__pyx_m, (char *)"__pyx_capi__", d) < 0)
            goto bad;
    }
    tmp.fp = f;
#if PY_VERSION_HEX >= 0x02070000
    cobj = PyCapsule_New(tmp.p, sig, 0);
#else
    cobj = PyCObject_FromVoidPtrAndDesc(tmp.p, (void *)sig, 0);
#endif
    if (!cobj)
        goto bad;
    if (PyDict_SetItemString(d, name, cobj) < 0)
        goto bad;
    Py_DECREF(cobj);
    Py_DECREF(d);
    return 0;
bad:
    Py_XDECREF(cobj);
    Py_XDECREF(d);
    return -1;
}

/* InitStrings */
  static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        #if PY_MAJOR_VERSION < 3
        if (t->is_unicode) {
            *t->p = PyUnicode_DecodeUTF8(t->s, t->n - 1, NULL);
        } else if (t->intern) {
            *t->p = PyString_InternFromString(t->s);
        } else {
            *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        }
        #else
        if (t->is_unicode | t->is_str) {
            if (t->intern) {
                *t->p = PyUnicode_InternFromString(t->s);
            } else if (t->encoding) {
                *t->p = PyUnicode_Decode(t->s, t->n - 1, t->encoding, NULL);
            } else {
                *t->p = PyUnicode_FromStringAndSize(t->s, t->n - 1);
            }
        } else {
            *t->p = PyBytes_FromStringAndSize(t->s, t->n - 1);
        }
        #endif
        if (!*t->p)
            return -1;
        if (PyObject_Hash(*t->p) == -1)
            return -1;
        ++t;
    }
    return 0;
}

static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char* c_str) {
    return __Pyx_PyUnicode_FromStringAndSize(c_str, (Py_ssize_t)strlen(c_str));
}
static CYTHON_INLINE const char* __Pyx_PyObject_AsString(PyObject* o) {
    Py_ssize_t ignore;
    return __Pyx_PyObject_AsStringAndSize(o, &ignore);
}
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
#if !CYTHON_PEP393_ENABLED
static const char* __Pyx_PyUnicode_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
    char* defenc_c;
    PyObject* defenc = _PyUnicode_AsDefaultEncodedString(o, NULL);
    if (!defenc) return NULL;
    defenc_c = PyBytes_AS_STRING(defenc);
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
    {
        char* end = defenc_c + PyBytes_GET_SIZE(defenc);
        char* c;
        for (c = defenc_c; c < end; c++) {
            if ((unsigned char) (*c) >= 128) {
                PyUnicode_AsASCIIString(o);
                return NULL;
            }
        }
    }
#endif
    *length = PyBytes_GET_SIZE(defenc);
    return defenc_c;
}
#else
static CYTHON_INLINE const char* __Pyx_PyUnicode_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
    if (unlikely(__Pyx_PyUnicode_READY(o) == -1)) return NULL;
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
    if (likely(PyUnicode_IS_ASCII(o))) {
        *length = PyUnicode_GET_LENGTH(o);
        return PyUnicode_AsUTF8(o);
    } else {
        PyUnicode_AsASCIIString(o);
        return NULL;
    }
#else
    return PyUnicode_AsUTF8AndSize(o, length);
#endif
}
#endif
#endif
static CYTHON_INLINE const char* __Pyx_PyObject_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
    if (
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
            __Pyx_sys_getdefaultencoding_not_ascii &&
#endif
            PyUnicode_Check(o)) {
        return __Pyx_PyUnicode_AsStringAndSize(o, length);
    } else
#endif
#if (!CYTHON_COMPILING_IN_PYPY) || (defined(PyByteArray_AS_STRING) && defined(PyByteArray_GET_SIZE))
    if (PyByteArray_Check(o)) {
        *length = PyByteArray_GET_SIZE(o);
        return PyByteArray_AS_STRING(o);
    } else
#endif
    {
        char* result;
        int r = PyBytes_AsStringAndSize(o, &result, length);
        if (unlikely(r < 0)) {
            return NULL;
        } else {
            return result;
        }
    }
}
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject* x) {
   int is_true = x == Py_True;
   if (is_true | (x == Py_False) | (x == Py_None)) return is_true;
   else return PyObject_IsTrue(x);
}
static CYTHON_INLINE int __Pyx_PyObject_IsTrueAndDecref(PyObject* x) {
    int retval;
    if (unlikely(!x)) return -1;
    retval = __Pyx_PyObject_IsTrue(x);
    Py_DECREF(x);
    return retval;
}
static PyObject* __Pyx_PyNumber_IntOrLongWrongResultType(PyObject* result, const char* type_name) {
#if PY_MAJOR_VERSION >= 3
    if (PyLong_Check(result)) {
        if (PyErr_WarnFormat(PyExc_DeprecationWarning, 1,
                "__int__ returned non-int (type %.200s).  "
                "The ability to return an instance of a strict subclass of int "
                "is deprecated, and may be removed in a future version of Python.",
                Py_TYPE(result)->tp_name)) {
            Py_DECREF(result);
            return NULL;
        }
        return result;
    }
#endif
    PyErr_Format(PyExc_TypeError,
                 "__%.4s__ returned non-%.4s (type %.200s)",
                 type_name, type_name, Py_TYPE(result)->tp_name);
    Py_DECREF(result);
    return NULL;
}
static CYTHON_INLINE PyObject* __Pyx_PyNumber_IntOrLong(PyObject* x) {
#if CYTHON_USE_TYPE_SLOTS
  PyNumberMethods *m;
#endif
  const char *name = NULL;
  PyObject *res = NULL;
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_Check(x) || PyLong_Check(x)))
#else
  if (likely(PyLong_Check(x)))
#endif
    return __Pyx_NewRef(x);
#if CYTHON_USE_TYPE_SLOTS
  m = Py_TYPE(x)->tp_as_number;
  #if PY_MAJOR_VERSION < 3
  if (m && m->nb_int) {
    name = "int";
    res = m->nb_int(x);
  }
  else if (m && m->nb_long) {
    name = "long";
    res = m->nb_long(x);
  }
  #else
  if (likely(m && m->nb_int)) {
    name = "int";
    res = m->nb_int(x);
  }
  #endif
#else
  if (!PyBytes_CheckExact(x) && !PyUnicode_CheckExact(x)) {
    res = PyNumber_Int(x);
  }
#endif
  if (likely(res)) {
#if PY_MAJOR_VERSION < 3
    if (unlikely(!PyInt_Check(res) && !PyLong_Check(res))) {
#else
    if (unlikely(!PyLong_CheckExact(res))) {
#endif
        return __Pyx_PyNumber_IntOrLongWrongResultType(res, name);
    }
  }
  else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_TypeError,
                    "an integer is required");
  }
  return res;
}
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject* b) {
  Py_ssize_t ival;
  PyObject *x;
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_CheckExact(b))) {
    if (sizeof(Py_ssize_t) >= sizeof(long))
        return PyInt_AS_LONG(b);
    else
        return PyInt_AsSsize_t(b);
  }
#endif
  if (likely(PyLong_CheckExact(b))) {
    #if CYTHON_USE_PYLONG_INTERNALS
    const digit* digits = ((PyLongObject*)b)->ob_digit;
    const Py_ssize_t size = Py_SIZE(b);
    if (likely(__Pyx_sst_abs(size) <= 1)) {
        ival = likely(size) ? digits[0] : 0;
        if (size == -1) ival = -ival;
        return ival;
    } else {
      switch (size) {
         case 2:
           if (8 * sizeof(Py_ssize_t) > 2 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -2:
           if (8 * sizeof(Py_ssize_t) > 2 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case 3:
           if (8 * sizeof(Py_ssize_t) > 3 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -3:
           if (8 * sizeof(Py_ssize_t) > 3 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case 4:
           if (8 * sizeof(Py_ssize_t) > 4 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -4:
           if (8 * sizeof(Py_ssize_t) > 4 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
      }
    }
    #endif
    return PyLong_AsSsize_t(b);
  }
  x = PyNumber_Index(b);
  if (!x) return -1;
  ival = PyInt_AsSsize_t(x);
  Py_DECREF(x);
  return ival;
}
static CYTHON_INLINE PyObject * __Pyx_PyBool_FromLong(long b) {
  return b ? __Pyx_NewRef(Py_True) : __Pyx_NewRef(Py_False);
}
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t ival) {
    return PyInt_FromSize_t(ival);
}


#endif /* Py_PYTHON_H */
