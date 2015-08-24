#!/usr/bin/env python
#-*-: coding: utf-8 -*-

# author : zergl <e3.gemini@qq.com>
#   date : 2015/08/20
#

def enum(args, start=0):
    class _Enum(object):
        ##todo: make sure every element is a valid variable.
        __slots__ = args.split(',')

        def __init__(self):
            for idx, key in enumerate(_Enum.__slots__, start):
                setattr(self, key, idx)
        
        def __str__(self):
            return "An enum-like wrapper."

        def __iter__(self):
            return iter(self.__slots__)

        def __len__(self):
            return len(_Enum.__slots__)
    
        def append(self, key, value):
            idx = len(_Enum.__slots__)
            setattr(self, key, )
    return _Enum()

if __name__ == "__main__":
    e = enum('a,b,c,d')
    print "len(enum): ", len(e)
    #print "e[1]: ", e[1] ## indexing -- not support
    #e = enum() ## callable -- not support
    #e.append(abcd) ## append -- not support

    for i,k in enumerate(e):
        print "%d - %s" %(i, k)

