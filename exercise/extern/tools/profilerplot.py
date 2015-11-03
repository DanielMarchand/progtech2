#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Author:  Mario S. Könz <mskoenz@gmx.net>
# Date:    27.10.2015 15:15:58 CET
# File:    profilerplot.py

import re
import os
import sys
import collections
import numpy as np

#------------------- perf class -------------------
class perf_class(object):
    def __init__(self, parent = None, name = "sentinel_root", mean = None, std = None, count = None):
        self.parent = parent
        self.name = name
        self.mean = mean
        self.std = std
        self.count = count
        self.child = []
    
    def add(self, parent_name, name, mean, std, count):
        if self.name == parent_name:
            self.child.append(perf_class(self, name, mean, std, count))
            return True
        else:
            for c in self.child:
                if c.add(parent_name, name, mean, std, count):
                    return True
        return False
    
    def get(self, name):
        if name == self.name:
            return self
        else:
            for c in self.child:
                nm = c.get(name)
                if nm:
                    return nm
        return None
    
    @property
    def total_cyc(self):
        if self.parent == None: # root
            return sum([c.total_cyc for c in self.child])
        else:
            return self.count * self.mean
    
    @property
    def percent(self):
        if self.parent == None: # root
            return 1.0
        else:
            return self.total_cyc / self.parent.total_cyc
    
    def __str__(self, indent = ""):
        os = indent
        os += "{} {}\n".format(self.name, self.percent)
        for c in self.child:
            os += c.__str__(indent + "    ")
        return os
    



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
    if len(sys.argv) == 1: # argv[0] is the program name
        raise RuntimeError("pennaplot: please supply one or more file to plot")
    
    opt = dict(depth = 0
             , obs = "total_cyc"
             , root = "sentinel_root"
             , edge = 0.1
             , out = "noname"
             , fontsize = 12)
    
    # parse options
    files = []
    for arg in sys.argv[1:]:
        if "=" in arg:
            k, v = arg.split("=", 1)
            if k not in ["root", "depth", "out"]:
                raise RuntimeError("pennaplot: {} is not a valid option".format(k))
            else:
                opt[k] = to_number(v)
        else:
            files.append(arg)
    
    # automatic properties
    opt["height"] = (1-2*opt["edge"])/(opt["depth"]+1)
    
    for fn in files:
        if not os.access(fn, os.R_OK):
            raise RuntimeError("pennaplot: file {} is not readable".format(fn))
    
    # read in
    data = []
    header = []
    for fn in files:
        # read data
        with open(fn, "r") as f:
            res = split_clean(f.readlines())
        
        res = res[1:]
        
        # remove all comments beginning with #
        res = list(filter(lambda x: x[0][0] != "#", res))
        
        # convert to numbers
        res = to_number(res)
        
        # read lines into perf_class
        obj = perf_class()
        
        i = 0
        while len(res):
            v = res[i]
            if obj.add(*v):
                del res[i]
                i = 0
            else:
                i += 1
        
        data.append(obj)
        header.append(os.path.basename(fn).rsplit(".", 1)[0]) # add filename without ending
    
    # preprocess data
    dq = collections.deque(["r", "b", "g", "y", "m", "c", "gray", "k"])
    
    dataset = {}
    for major, r in enumerate(data):
        def collect_child(node, start, minor, attr):
            if node.name not in dataset.keys():
                dataset[node.name] = []
            dataset[node.name].append([major, minor, start, getattr(node, attr)])
        
        def collect_rec(node, start, minor, attr):
            t = start
            for c in node.child:
                collect_child(c, t, minor, attr)
                if minor > 0:
                    collect_rec(c, t, minor - 1, attr)
                t += getattr(c, attr)
        
        collect_rec(r.get(opt["root"]), 0, opt["depth"], opt["obs"])
    
    temp = sorted(list(dataset.items()), key = lambda kv: kv[0])
    temp = sorted(temp, key = lambda kv: -kv[1][0][1])
    y_range = np.array(range(len(data)))
    
    # plot data
    subplot = plt.subplot()
    ax = plt.gca()
    fig = plt.gcf()
    for i, (key, val) in enumerate(temp):
        opt["_kwgs"] = {}
        opt["_kwgs"]["color"] = dq[0]
        dq.rotate(-1)
        x_start = [v[2] for v in val]
        x_len = [v[3] for v in val]
        y_pos = np.array([y_range[v[0]] for v in val]) + opt["edge"] + opt["height"]*np.array([v[1] for v in val])
        ax.barh(left=x_start, width=x_len, height=opt["height"], bottom=y_pos
              , label=key, edgecolor = "none", **opt["_kwgs"])
    
    #=================== postprocess ===================
    ax.set_yticks(0.5 + y_range)
    ax.set_yticklabels(header, fontsize = opt["fontsize"])
    
    #~ ax.set_yticklabels([core.filename(f, suffix = False) for f in popt.source], fontsize = 12)
    ax.set_ylim(0, y_range[-1]+1)
    
    handles, labels = ax.get_legend_handles_labels()
    
    box = ax.get_position()
    ax.set_position([box.x0 + box.width * 0.05, box.y0, box.width * 0.8, box.height])
    
    ax.legend(handles, labels, loc='center left', bbox_to_anchor=(1, 0.5))
    ax.yaxis.grid(False)
    ax.xaxis.grid(True)
    
    # labels & title
    plt.xlabel(opt["obs"])
    
    basename = opt["out"]
    plt.title(basename)
    #~ plt.tight_layout()
    
    # show & save
    plt.savefig("{}.pdf".format(basename))
    plt.show() # comment this line if you only want to save the result
    
    print("pennaplot: plotted {} to {}".format(files, "{}.pdf".format(basename)))

if __name__ == "__main__":
    main()
