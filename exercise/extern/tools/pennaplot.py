#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Author:  Mario S. Könz <mskoenz@gmx.net>
# Date:    14.09.2015 11:20:31 CEST
# File:    pennaplot.py

import matplotlib.pyplot as plt

import re
import os
import sys
import collections
import numpy as np

#------------------- helper -------------------
def listable(fct):
    def inner(arg, *args, **kwgs):
        if isinstance(arg, list) or isinstance(arg, tuple):
            return list(map(lambda a: inner(a, *args, **kwgs), arg))
        else:
            return fct(arg, *args, **kwgs)
    return inner

@listable
def split_clean(string, strip_quotes = False):
    string = re.sub("^[\\s]+|[\\s]+$", "", string) # remove front and back whitespace (strip would also work)
    not_in_quotes = '(?=(?:[^"\']*(?:"[^"]*"|\'[^\']*\'))*[^"\']*$)'
    e = '\\s+'+not_in_quotes # split on whitespace sections but not in "" or ''
    prog = re.compile(e)
    res = prog.split(string)
    if strip_quotes:
        for i in range(len(res)):
            res[i] = re.sub('^(["\'])([\s\S]*)(\\1)$', "\\2", res[i]) #strips "" or '' if found at ^ and $
        return res
    else:
        return res

@listable
def to_number(obj, strip_quotes = True):
    try:
        res = int(obj)
        return res
    except:
        pass
    try:
        res = float(obj)
        return res
    except:
        pass
    
    if strip_quotes == True:
        return re.sub('^[\s]*(["\'])([\s\S]*)(\\1)$', "\\2", obj)
    return obj

#------------------- main -------------------
def main():
    # check file sanity
    if len(sys.argv) != 2: # argv[0] is the program name
        raise RuntimeError("pennaplot: please supply exactly one file to plot")
    
    file_ = sys.argv[1]
    if not os.access(file_, os.R_OK):
        raise RuntimeError("pennaplot: file {} is not readable".format(file_))
    
    # read data
    with open(file_, "r") as f:
        res = split_clean(f.readlines())
    
    # get data names
    header = res[0]
    del res[0]
    
    # get parameter if supplied
    param = collections.OrderedDict()
    if res[0][0] == "#param":
        temp = res[0][1:]
        for k, v in zip(temp[0::2], temp[1::2]):
            param[k] = to_number(v)
    
    # remove all comments beginning with #
    res = list(filter(lambda x: x[0][0] != "#", res))
    
    # convert to numbers
    res = to_number(res)
    
    # sanity check for data
    L = len(header)
    for r in res:
        if len(r) != L:
            raise RuntimeError("pennaplot: line {} has not exactly {} entries".format(r, L))
    
    # store to numpy array and transpose
    data = np.array(res).T
    
    # plot data
    fig, ax = plt.subplots()
    dq = collections.deque(["b", "r", "g", "c", "m", "y", "k"])
    
    for i in range(1, len(data)):
        opt = {}
        opt["color"] = dq[0]
        dq.rotate(-1)
        opt["marker"] = "."
        
        res = plt.plot(data[0], data[i], **opt)
    
    # parameterbox
    if param:
        text = []
        for k, v in param.items():
            text.append("{} = {}".format(k, v))
        text = "\n".join(text)
        plt.text( .03
                , .97
                , text
                , transform=ax.transAxes
                , fontsize = 8
                , verticalalignment='top'
                , horizontalalignment='left'
                , bbox=dict(boxstyle='square', facecolor="w", edgecolor="k")
            )
    
    # labels & title
    plt.xlabel(header[0])
    plt.ylabel("population size")
    plt.legend(header[1:])
    
    basename = os.path.basename(file_).rsplit(".", 1)[0];
    plt.title(basename)
    
    # show & save
    plt.savefig("{}.pdf".format(basename))
    plt.show() # comment this line if you only want to save the result
    
    print("pennaplot: plotted {} to {}".format(file_, "{}.pdf".format(basename)))

if __name__ == "__main__":
    main()
