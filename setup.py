# -*- coding: utf-8 -*-

from distutils.core import setup, Extension


class numpy_include():
    def __str__(self):
        import numpy as np
        return np.include_dir()


xgrab_module = Extension('xgrab',
                         sources=['xgrab/python.c', 'xgrab/xgrab.c'],
                         libraries=['X11'],
                         extra_compile_args=['-fPIC', '-O3'])

setup(name='xgrab',
      version='0.0.1',
      description='X screen grab.',
      install_requires=['numpy'],
      include_dirs=[numpy_include],
      ext_modules=[xgrab_module])
