# shortcut_processor

In this project you will implement a preprocessor to process shortcuts for arithmetic operations on arrays.
You will use C language for programming. Use gcc compiler in Linux environment. Prior to project submission, you must make sure that your project executes correctly with the specified setting. Projects producing errors during the demonstrations due to the differences in the platform will not be accepted.
Your preprocessor should read a C file with preprocessor commands, parse the commands into its tokens and expand the commands by substituting the appropriate C codes. Preprocessor commands start with “$”.
Following preprocessor commands must be implemented:

Declaration
$dec(array, n, type)
Declares an array with n elements, of the given type (eg. int, float, char).
ex: $dec(A, 10, int)  declares 1D integer array A with 10 elements

Input
$read(file, array)
Reads n elements of the array from the file.
ex: $read(f1, A)  reads all elements of 1D array A from file f1

Output
$print(array)
Prints the array elements on the screen.
ex: $print(A)  prints array A on the screen

Copy
$destination = $source
Copies all elements of source array to destination array.
ex: $A = $B  copies 5 elements form array B to array A
Initialization $array = x
Sets all array elements to value x.
ex: $A = 0sets array elements to 0

Arithmetic operations
Performs four arithmetic operations (+, -, *, /) on arrays. 
ex: 
$Y=$A+$B
$Y = $A - $B 
$Y = $A * $B 
$Y = $A / $B 
$Y = $A + 5 
$A = $A - 1 
$A = $A * 3 
$A = $A / 2 
$Y = 2 / $A
