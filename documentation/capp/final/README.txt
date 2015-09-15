If recompiling, please compile twice for the cititions to be correct.

--------------------------- CHANGES ---------------------------------

As per the reveiwers suggestions, the following changes were made:

- References were fixed (capitalization etc...)
- As per reviewer 3:
  - It was made clear that the c++ code has knowledge of the aspects, 
    which is not pure aspect-orientation, and why the framwork is still
    beneficial (compile time performance of aspects and modularity)

  - A comparison was made against c++ AMP for the number of lines of code
    as it is also a high-level parallel framework. The perormance of C++ AMP
    was not added since it is for windows and AspectC++ support for windows is 
    limited at the moment, thus a comparison could not be made since a common 
    compiler could not be used.

- As per reviewer 2:
  - More details as per the performance results were given, and why they are 
    different for the two examples provided 

As the c++ code using CAPP does have knowledge of the aspects, the CAPP maodel 
was changed to an aspect-oriented based framework for parallel programming.
