## Word ladders report}

# Results

**Briefly comment the results, did the script say all your solutions were correct?**
**Approximately how long time does it take for the program to run on the largest input?**
real	0m1.012s
user	0m1.002s
sys	0m0.007s
**What takes the majority of the time?**

only init graph: 
real	0m0.610s
user	0m0.607s
sys	0m0.002s

everything but bfs:
real	0m0.944s
user	0m0.940s
sys	0m0.002s



# Implementation details

**How did you implement the solution?**
**Which data structures were used?**
**Which modifications to these data structures were used?**
**What is the overall running time?** 
**Why?**

## Questions
**How do you represent the problem as a graph, and how is the graph built?**
Every word is a node and that has directed arches with nodes that fulfills the criteria
**If one were to perform backtracking (find the path along which we went), how would that be done?**
I already do it, follow the predecessors of the found nodes.
**What is the time complexity, and more importantly why?**
Allegedly O(n+m) since the outer loop can go through all nodes and we can go through all edges. Note this is  sudo directed.
**Is it possible to solve the problem with DFS: why or why not?**
yes, just need to go keep track of the shortest path and maybe heights.
**Can you think of any applications of this? Of BFS/DFS in general?**
lots of search algorithms is based on. Finding paths in general gps. Decision making in general.

