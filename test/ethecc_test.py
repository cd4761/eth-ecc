import pyecceth
from random import randint
import codecs


def test():
    # ph = b'0xb0be837a1107b5628c0c3c306f751edf632b919bb0d4395b73022ae868de602f'
    # ch = b'0x728a7a4c4f10e12815353148a9f361db0c7c1dc640c31c7f730c75e0031e7499'
    ph = b'abc255dff722ddddffff3ffffd3'
    ch = b'1fdf22ffc2233ff'
    result = pyecceth.eth_ecc(ph, ch, 24, 3, 6)


test()
