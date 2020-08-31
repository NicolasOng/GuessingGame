#adapted from: https://www.geeksforgeeks.org/wrapping-cc-python-using-swig-set-1/
from distutils.core import setup, Extension

name = "rf"

example_module = Extension('_' + name, sources=[name + '.c', name + '.i'])

setup(name=name, ext_modules=[example_module], py_modules=[name])


'''
swig -python rf.i
python3 rf_setup.py build_ext --inplace

type:
from rf import *

at the beginning of any new python file in that folder.
'''
