# Questions
**Why does your algorithm obtain a stable solution?** 
Same number of proposers and proposees means that everyone is paired, and since a proposer only starts with their top choice and 
is only discarde by a proposees higher choice noone is left alone in the end. Which means at least one in the pair is completly satisfied.
**Could there be other stable solutions? Do you have an example/proof of uniqueness?**
GS favors the proposer and will give a stable solution in which proposers is favored.

From Wikipedia:

    A: YXZ   B: ZYX   C: XZY  
    X: BAC   Y: CBA   Z: ACB

There are three stable solutions to this matching arrangement:

    men get their first choice and women their third - (AY, BZ, CX);
    all participants get their second choice - (AX, BY, CZ);
    women get their first choice and men their third - (AZ, BX, CY).

**What is the time complexity and why?**
 n^2 since in the worst case senario each man will be gone through and each man will go through each woman once.
 in the best case senario each man will be matched perfectly and only goes through once.

**Is this (the algorithm) how matching is performed in real life? If not, what flaws does it have?**

**Are there any applications of the algorithm (as it is or in a slightly shifted version)?**


# Report
## Briefly comment the results:
**Did the script say all your solutions were correct?**
Yes the script passed all test

**Approximately how long time does it take for the program to run on the largest input?**
  Time for 5Messy:
  - real	0m1.818s
  - user	0m1.216s
  - sys	  0m0.124s
**What takes the majority of the time?**

  Running the code only doing the input opperation gives the results bellow. This seem to indicate quite 
  a lot of time is taken up by reading the data compared to the actual algorithm

  Without actual calculation:
  real	0m1.029s
  user	0m0.925s
  sys	  0m0.099s

  ## Implementation details

  **How did you implement the solution?**
  In C using first input into arrays, then structs to store information about the arrays. Usin the GS algorithm
  Putting al bachlors in a list. Going through the first ones prefrence list and taking th first women who has not yet been proposed to, 
  saving the index of the last woman propsed to. Evaluation the proposal and either pairing, pairing and kicking out someone else and finally putting back the first bachelor,
  if the bachelor is not good enought.
  **Which data structures were used?**
  arrays, structs to implement a linked list
  **Which modifications to these data structures were used?**
  **What is the overall running time?** 
  **Why?**
