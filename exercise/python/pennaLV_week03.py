#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Author:  Mario S. Könz <mskoenz@gmx.net>
# Date:    30.09.2015 11:25:16 CEST
# File:    pennaLV_week03.py

from __future__ import division, print_function

import util
import time

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

class Animal(object):
    def __init__ (self, age = 0):
        prop = self.__class__.prop
        
        self.age = age
        self.gene = [False for i in range(prop.gene_size)]
        self.bad_genes = 0
    
    def adult(self):
        return self.age >= self.__class__.prop.repr_age
    
    def make_child(self):
        cls = self.__class__
        prop = cls.prop
        
        child = cls()
        child.gene[:] = self.gene[:]
        
        for m in range(prop.mut_rate):
            pos = self.__class__.gene_rng()
            child.gene[pos] = not child.gene[pos]
        
        return child
    
    def progress(self):
        cls = self.__class__
        prop = cls.prop
        
        self.bad_genes += self.gene[self.age];
        self.age += 1;
        
        if self.bad_genes >= prop.threshold: # darwin selection
            return False
        
        if cls.prob_rng() > (1 - float(prop.N_t)/prop.N_max): # resource selection
            return False
        
        if self.age == prop.gene_size:
            return False
        
        if cls.prob_rng() > self.interaction():
            return False
        
        return True
        
    @classmethod
    def set_gene_size(cls, size):
        cls.gene_rng.set_range(0, size - 1)
        cls.prop.gene_size = size
    
    @classmethod
    def random_age(cls):
        return cls.gene_rng()

    def __str__(self): # print
        res = "{} age: {} ".format(self.name(), self.age)
        res += "".join([str(int(x)) for x in self.gene[:self.age]])
        res += "<-"
        res += "".join([str(int(x)) for x in self.gene[self.age:]])
        return res

class Sheep(Animal):
    prop = PropClass()
    gene_rng = util.int_rng(0, 1);
    prob_rng = util.float_rng(0, 1);
    
    def name(self):
        return "sheep"
    
    def interaction(self):
        return 1 - 0.1 * Bear.prop.N_t / float(Sheep.prop.N_t)

class Bear(Animal):
    prop = PropClass()
    gene_rng = util.int_rng(0, 1);
    prob_rng = util.float_rng(0, 1);
    
    def name(self):
        return "bear"
    
    def interaction(self):
        return Sheep.prop.N_t / float(2 * Bear.prop.N_t)
    
        
def main():
    # seed random number generator engine
    util.seed(0)
    
    # set up sheep parameters
    Sheep.set_gene_size(32)
    Sheep.prop.repr_age = 8
    Sheep.prop.threshold = 3
    Sheep.prop.mut_rate = 2
    Sheep.prop.N_max = 1000
    Sheep.prop.N_init = 1000
    # set up bear parameters
    Bear.set_gene_size(32)
    Bear.prop.repr_age = 8
    Bear.prop.threshold = 3
    Bear.prop.mut_rate = 2
    Bear.prop.N_max = 1000
    Bear.prop.N_init = 1000
    
    # generate initial population
    pop = [] # list
    for i in range(Sheep.prop.N_init):
        pop.append(Sheep(Sheep.random_age()))
        Sheep.prop.N_t += 1
    
    for i in range(Bear.prop.N_init):
        pop.append(Bear(Bear.random_age()))
        Bear.prop.N_t += 1
    
    # prepare output file
    with open("py_pennaLV_week03.txt", "w") as ofs:
        ofs.write("time sheep bear\n")
        
        ofs.write("#param seed {} ".format(util.seed()))
        ofs.write("N_init {} ".format(Sheep.prop.N_init))
        ofs.write("N_max {} ".format(Sheep.prop.N_max))
        ofs.write("gene_size {} ".format(Sheep.prop.gene_size))
        ofs.write("repr_age {} ".format(Sheep.prop.repr_age))
        ofs.write("mut_rate {} ".format(Sheep.prop.mut_rate))
        ofs.write("threshold {}\n".format(Sheep.prop.threshold))
        
        ofs.write("b_N_init {} ".format(Bear.prop.N_init))
        ofs.write("b_N_max {} ".format(Bear.prop.N_max))
        ofs.write("b_gene_size {} ".format(Bear.prop.gene_size))
        ofs.write("b_repr_age {} ".format(Bear.prop.repr_age))
        ofs.write("b_mut_rate {} ".format(Bear.prop.mut_rate))
        ofs.write("b_threshold {}\n".format(Bear.prop.threshold))
        
        # run simulation
        for gen in range(300):
            
            for s in pop[:]:
                if not s.progress():
                    pop.remove(s)
                    s.prop.N_t -= 1
                elif s.adult():
                    pop.insert(0, s.make_child())
                    s.prop.N_t += 1
            
            #~ print("{} {} {}".format(gen, Sheep.prop.N_t, Bear.prop.N_t))
            ofs.write("{} {} {}\n".format(gen, Sheep.prop.N_t, Bear.prop.N_t))
    
    print("total sheep: {}".format(Sheep.prop.N_t))
    print("total bear:  {}".format(Bear.prop.N_t))
    print(pop[-1])
    
if __name__ == "__main__":
    main()
