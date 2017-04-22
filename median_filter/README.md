## Question
Implement a median filter on the image.


## Solution
Couple of points to note:
* Finding median for each pixel is an expensive operation. So, optimizing that would greatly improve the performance. Some  techniques are used here to improve performance:
	* Since we know that the max values of pixels are 256, we can use an array of 256 to find the median without sorting
	* We are moving in raster order. We don't have to recalculate all the elements in nxn matrix. 
	* When we reach at the end of a row (last column), do not come back to the begining. Instead come down a row and start applying the filter from right to left,

P.S. Code is not fully tested or optimized. TBD



