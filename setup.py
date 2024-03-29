import os
from setuptools import setup, Extension

sources = [
    'ecc-lib/ETH-ECC.cpp',
    'ecc-lib/LDPC.cpp',
    'ecc-lib/sha256.cpp'
    ]

depends = [
    'ecc-lib/LDPC.h',
    'ecc-lib/Memory_Manage.h',
    'ecc-lib/Def_List.h'

]
pyeccpow = Extension('pyeccpow',
                     sources=sources,
                     depends=depends,
                     extra_compile_args=["-Isrc/", "-std=c++11", "-Wall"])

setup(
    name='pyeccpow',
    author="Jason Hwang",
    author_email="jason.h@onther.io",
    license='GPL',
    version='0.1.2',
    url='https://github.com/cd4761/eccpow',
    download_url='https://github.com/cd4761/eccpow/tarball/v23',
    description=('Python wrappers for eccpow, the ethereum proof of work'
                 'hashing function with LDPC'),
    ext_modules=[pyeccpow],
)
