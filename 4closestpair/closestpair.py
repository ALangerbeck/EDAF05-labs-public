#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri May  4 09:11:37 2018

@author: martin
"""
import math
import sys
import time

res =[]


class Point:
    xcomp = True
    
    def __init__(self,name,x,y):
        self.x = x
        self.y = y
        self.name = name
        self.index = 0
    
    def dist(self, other):
        return (self.x-other.x)**2+(self.y-other.y)**2
    
    def __lt__(self, other):
        return self.x < other.x if self.xcomp else self.y < other.y
    
    def __le__(self, other):
        return self.x <= other.x if self.xcomp else self.y <= other.y
    
    def __eq__(self, other):
        return self.x == other.x if self.xcomp else self.y == other.y
    
    def __ne__(self, other):
        return self.x != other.x if self.xcomp else self.y != other.y

    def __gt__(self, other):
        return self.x > other.x if self.xcomp else self.y > other.y

    def __ge__(self, other):
        return self.x >= other.x if self.xcomp else self.y >= other.y
    def __hash__(self):
        return hash((str(self.x), str(self.y),str(self.name)))

def mergesort(lista):
    l = len(lista)
    if l > 1:
        mitten = l//2
        
        left=lista[:mitten]
        right = lista[mitten:]
        
        mergesort(left)
        mergesort(right)
        
        
        #merga left och right
        
        i = 0
        l_i = 0
        r_i = 0
        while l_i <len(left) and r_i < len(right):
            if left[l_i] <= right[r_i]:
                lista[i] = left[l_i]
                l_i += 1
            else:
                lista[i] = right[r_i]
                r_i += 1
            i += 1
        while l_i < len(left):
            lista[i] = left[l_i]
            l_i += 1
            i += 1
        while r_i < len(right):
            lista[i] = right[r_i]
            r_i += 1
            i += 1
    return lista

def findclosest(xlista,ylista,fi):
    if len(xlista)<=30:
        d, points = -1, []
        for i in range(len(xlista)-1):
            for j in range(i+1,len(xlista)):
                di = xlista[i].dist(xlista[j])
                global res
                res.append(di)
                if di < d or d == -1:
                    d = di
                    points = [xlista[i],xlista[j]]
        return d, points

    mitten = len(xlista)//2 
        
    lefty = []
    righty =[]

    
    for i in range(len(ylista)):
        point = ylista[i]
        if point.index < mitten+fi:
            lefty.append(point)
        else:
            righty.append(point)
            
    leftx = xlista[:mitten]
    rightx = xlista[mitten:]
        
        
    d1, pair1 = findclosest(leftx,lefty,fi)
    d2, pair2 = findclosest(rightx,righty,mitten+fi)
    
    if d1 < d2:
        d, pair = d1, pair1
    else:
        d, pair = d2, pair2
        
    xd = leftx[-1].x
    S = set()
    i =0
    while i < len(leftx) and abs(leftx[-(i+1)].x -xd) <= d:
        S.add(leftx[-(i+1)])
        i +=1
    i = 0    
    while i < len(rightx) and abs(rightx[i].x-xd) <= d:
        S.add(rightx[i])
        i +=1
            
    Sy = []
    for i in range(len(ylista)):
        if ylista[i] in S:
            Sy.append(ylista[i])
    
    dl, pairl = 0, []
    
    for i in range(len(Sy)-1):
        for j in range(i+1,min(i+16,len(Sy))):
            dist = Sy[i].dist(Sy[j])
            
            if dist < dl or dl == 0:
                dl = dist
                pairl = [Sy[i],Sy[j]]
    
    if dl < d and dl != 0:
        return dl, pairl
    else:
        return d, pair
    
def parse(lines):
    k = 0
    P = []
    for i,line in enumerate(lines):
        linesplit= line.split()
        if i == 0 and (linesplit[0] == "NAME" or linesplit[0] == "NAME:"): 
            k = 4
        if i >=k and len(linesplit) == 3:
            if k == 0 or linesplit[0].isdigit():
                P.append(Point(linesplit[0],float(linesplit[1]),float(linesplit[2])))
    return P
#filename = sys.argv[1]
#filename = "data/kroA100-tsp.txt"
#filename = "data/nrw1379-tsp.txt"
#filename= "data/close-pairs-5-in.txt"
filename = "data/usa13509-tsp.txt"
#filename = "data/vm1748-tsp.txt"
#filename = "data/wc-instance-65534.txt"
#filename = "data/att532-tsp.txt"
#filename = "data/d2103-tsp.txt"
#filename = "data/brd14051-tsp.txt"
with open(filename) as file:
    lines = file.readlines()
    P = parse(lines)

Px = mergesort(P)

for i in range(len(P)):
    Px[i].index=i

Point.xcomp = False
Py = mergesort(P)
Point.xcomp = True
#t = time.time()
d, points = findclosest(Px,Py,0)
dl, pointsl = 1000, []
#for i in range(len(P)):
#    for j in range(i+1,len(P)):
#        if P[i].dist(P[j]) < dl:
#            dl = P[i].dist(P[j])
#            pointsl = [P[i], P[j]]
#print(time.time()-t)
output = filename+':'+' '+str(len(Px))+' '+str(math.sqrt(d))
print(output)
#print(math.sqrt(dl),pointsl[0].x-pointsl[1].x,pointsl[0].y-pointsl[1].y,math.sqrt(pointsl[0].dist(pointsl[1])))
#for i in range(len(Px)):
#    if Px[i] == pointsl[0]:
#        print(i)
#    if Px[i] == pointsl[1]:
#        print(i)