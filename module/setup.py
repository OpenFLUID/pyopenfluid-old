#!/usr/bin/env python
# -*- coding: UTF-8 -*-

PYOPENFLUID_LIBRARY = @PYOPENFLUID_DYNAMIC_LIBRARY@


from distutils.core import setup

setup(name='@PYOPENFLUID_DISPLAY_NAME@',
      version='@PYOPENFLUID_VERSION@',
      description='@PYOPENFLUID_SHORT_DESCRIPTION@',
      long_description='@PYOPENFLUID_LONG_DESCRIPTION@',
      author='@PYOPENFLUID_AUTHORS_LIST@',
      author_email='@PYOPENFLUID_EMAIL_LIST@',
      maintainer='@PYOPENFLUID_MAINTAINER@',
      maintainer_email='@PYOPENFLUID_EMAIL_MAINTAINER@',
      url='@PYOPENFLUID_URL@',
      licence='@PYOPENFLUID_LICENCE@',
      classifiers=[
          'Development Status :: @PYOPENFLUID_MAJOR_VERSION@ - @PYOPENFLUID_MINOR_VERSION@ - @PYOPENFLUID_PATCH_VERSION@ - @PYOPENFLUID_RELEASE_VERSION@',
          'Environment :: Console',
          'Operating System :: POSIX',
          'Programming Language :: Python',
          'Topic :: Communications :: Email',
          'Topic :: Office/Business',
          'Topic :: Software Development :: Simulation',
          ],
      packages=['PyOpenFLUID'],
      package_dir={'PyOpenFLUID': './'},
      package_data={'PyOpenFLUID': ['PyOpenFLUID.py', '__init__.py']},
     )
