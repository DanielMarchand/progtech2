#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Author:  Mario S. Könz <mskoenz@gmx.net>
# Date:    10.12.2015 05:32:13 CET
# File:    part1.py

class c1:
    """
    This is a very useful class to demonstrate how documantation works
    """
    def __init__ (self):
        """
        This is the constructor
        """
        self.x = 10
    
    def show_x_twice(self):
        self.show_x()
        self.show_x()
    
    def show_x(self):
        """
        Useful function to print x
        """
        print(self.x)
    
