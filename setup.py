import os
from distutils.core import setup, Extension
sources = [
    'ETH-ECC.cpp',
    'LDPC.cpp',
    'sha256.cpp'
    ]

depends = [
    'LDPC.h',
    'Memory_Manage.h',
    'Def_List.h',
    'cmath',
    'string'

]
ecceth = Extension('ecceth',
                     sources=sources,
                     depends=depends,
                     extra_compile_args=["-Isrc/", "-Wall"])

setup(
    name='ecceth',
    author="Jason Hwang",
    author_email="jason.h@onther.io",
    license='GPL',
    version='0.1.23',
    url='https://github.com/cd4761/ecceth',
    download_url='https://github.com/cd4761/ecceth/tarball/v23',
    description=('Python wrappers for eccpow, the ethereum proof of work'
                 'hashing function with LDPC'),
    ext_modules=[ecceth],
)
