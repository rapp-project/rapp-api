#!/usr/bin/env python

import os
from os import path
try:
    from setuptools import setup, find_packages
except ImportError:
    from distutils.core import setup, find_packages


# Utility function to read the README file.
# Used for the long_description.  It's nice, because now
#   1) we have a top level README file
#   2) it's easier to type in the README file than to put a raw string in below
def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

cfgDestPath = path.expanduser('~/.config/rapp_platform/python_platform_api')

setup(
    install_requires = [
        'requests==2.10.0',
        'ndg-httpsclient',
        'urllib3',
        'pyopenssl',
        'pyasn1',
        'futures==3.0.5'
    ],
    name='RappCloud',
    version='0.6.0',
    description='Rapp Platform Python API',
    url='https://github.com/rapp-project/rapp-api/tree/master/python',
    download_url='https://github.com/rapp-project/rapp-api/tree/master/python',
    author='Konstantinos Panayiotou',
    author_email='klpanagi@gmail.com',
    maintainer='Konstantinos Panayiotou',
    maintainer_email='klpanagi@gmail.com',
    license='Apache 2',
    test_suite='tests',
    include_package_data=True,
    # A list naming all the packages you want to include
    packages=find_packages(),
    # Package data to be added to packages
    package_data={
        # 'RappCloud': ['']
    },
    # Specify additional files needed by the module distribution: configuration files, message catalogs, data files
    data_files=[
        (cfgDestPath, ['RappCloud/config']),
    ],
    # A script(s) to be installed into standard locations like /usr/bin
    scripts=[],
    zip_safe=True,
    long_description=read('README.md') if os.path.exists('README.md') else ""
)
