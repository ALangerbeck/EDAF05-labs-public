# Report

## Briefly comment the results:
**Did the script say all your solutions were correct?**
Yes the scripts passed all test

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
