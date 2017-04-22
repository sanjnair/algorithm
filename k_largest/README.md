## Question
Order k largest elements at the begining of the array.



## Solution
We'll use quick select algorithm to solve this problem.

* Partition array so that
	* Entry ```a[j]``` is in place
	* No larger entry to the left of ```j```
	* No smaller entry to the right of ```j```
* Repeat in one sub-array, depending on ```j```; finished when ```j = k```



The average time complexity of this approach is ```O(N)```
But worst case complexity is ```O(N^2)```, which occurs due to sub-optimal piovt selection (array doesn't partition well).
The best case performance occurs when the pivot divides the array into to equal sized partitions, which results in a linear complexity. Average case is linear.



