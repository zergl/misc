#!/usr/bin/env python
#-*-: coding: utf-8 -*-

# author : zergl <e3.gemini@qq.com>
#   site : https://github.com/zergl
#   date : 2015/08/20
#

def enum(args, start=0):
    class _Enum(object):
        ##todo: make sure every element is a valid variable.
        __slots__ = args.split(',')
        __item_str = {}

        def __init__(self):
            for idx, key in enumerate(_Enum.__slots__, start):
                key = key.strip()
                setattr(self, key, idx)
                self.__item_str[idx] = key
        
        def __str__(self):
            return "An Enum-like Wrapper."

        def __iter__(self):
            return iter(self.__slots__)
        
        def __getitem__(self, key):
            return getattr(self, key)

        def __len__(self):
            return len(_Enum.__slots__)
    
        def append(self, key, value):
            idx = len(_Enum.__slots__)
            setattr(self, key, )
    
        def str(self, key):
            return self.__item_str[key]

    return _Enum()

if __name__ == "__main__":
    e = enum('BUDEG,INFO,ALERT,CRITI')
    print "value of e.INFO: ", e.INFO
    print "string value of e.INFO: ", e.str(e.INFO)

    print "len(e): ", len(e)
    #print "e[1]: ", e[1] ## indexing -- not support
    #e = enum() ## callable -- not support
    #e.append(abcd) ## append -- not support

    for k in e:
        print "%s - %s " %(k, e[k])

    print "--------"
    for i,k in enumerate(e):
        print "%d - %s" %(i, k)

