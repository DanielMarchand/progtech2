#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Author:  Mario S. Könz <mskoenz@gmx.net>
# Date:    30.09.2015 11:25:10 CEST
# File:    penna_week01.py

from __future__ import division, print_function

import random

class PropClass:
    def __init__(self):
        self.gene_size = 0;
        self.repr_age = 0;
        self.mut_rate = 0;
        self.threshold = 0;
        self.N_init = 0;
        self.N_t = 0;
        self.N_max = 0;
        self.N_all = 0;

class Sheep(object):
    prop = PropClass()
    
    def __init__ (self, age = 0):
        prop = self.__class__.prop
        
        self.age = age
        self.gene = [False for i in range(prop.gene_size)]
        self.bad_genes = 0
    
    def adult(self):
        return self.age >= self.__class__.prop.repr_age
    
    def make_child(self):
        prop = self.__class__.prop
        
        child = Sheep()
        child.gene[:] = self.gene[:]
        
        for m in range(prop.mut_rate):
            pos = self.random_age()
            child.gene[pos] = not child.gene[pos]
        
        return child
    
    def progress(self):
        cls = self.__class__
        prop = cls.prop
        
        self.bad_genes += self.gene[self.age];
        self.age += 1;
        
        if self.bad_genes >= prop.threshold: # darwin selection
            return False
        
        if random.random() > (1 - float(prop.N_t)/prop.N_max): # resource selection
            return False
        
        if self.age == prop.gene_size:
            return False
        
        return True
        
    @classmethod
    def random_age(cls):
        return random.randint(0, cls.prop.gene_size-1)
    
    @staticmethod
    def name():
        return "sheep"
    
    def __str__(self): # print
        res = "{} age: {} ".format(self.name(), self.age)
        res += "".join([str(int(x)) for x in self.gene[:self.age]])
        res += "<-"
        res += "".join([str(int(x)) for x in self.gene[self.age:]])
        return res

def main():
    # seed random number generator engine
    random.seed(0)
    
    # set up sheep parameters
    Sheep.prop.gene_size = 32
    Sheep.prop.repr_age = 8
    Sheep.prop.threshold = 3
    Sheep.prop.mut_rate = 2
    Sheep.prop.N_init = 1000
    Sheep.prop.N_max = 1000
    
    # generate initial population
    pop = [] # list
    for i in range(Sheep.prop.N_init):
        pop.append(Sheep(Sheep.random_age()))
        Sheep.prop.N_t += 1
    
    # prepare output file
    with open("py_penna_week01.txt", "w") as ofs:
        ofs.write("time sheep\n")
        
        ofs.write("#param seed {} ".format(random.seed()))
        ofs.write("N_init {} ".format(Sheep.prop.N_init))
        ofs.write("N_max {} ".format(Sheep.prop.N_max))
        ofs.write("gene_size {} ".format(Sheep.prop.gene_size))
        ofs.write("repr_age {} ".format(Sheep.prop.repr_age))
        ofs.write("mut_rate {} ".format(Sheep.prop.mut_rate))
        ofs.write("threshold {}\n".format(Sheep.prop.threshold))
        
        # run simulation
        for gen in range(300):
            for s in pop[:]:
                if not s.progress():
                    pop.remove(s)
                    Sheep.prop.N_t -= 1
                elif s.adult():
                    pop.insert(0, s.make_child())
                    Sheep.prop.N_t += 1
            
            ofs.write("{} {}\n".format(gen, Sheep.prop.N_t))
    
    print("total sheep: {}".format(Sheep.prop.N_t))
    print(pop[-1])
    
if __name__ == "__main__":
    main()
