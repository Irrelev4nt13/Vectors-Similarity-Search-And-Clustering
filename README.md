# Vectors-Similarity-Search-And-Clustering

Implement the `LSH` algorithm for vectors in d-dimensional space based on the euclidean metric (L2), as well as the random projection algorithm on the `HyperCube` for the same metric. The program will be implemented so that, taking as input a vector `q` and integers `N` and `R`, it returns approximately:

1. The Nearest Neighbor to q
2. The `N` Nearest Neighbors to q
3. The vectors of radius `R` from q (range search).

The design of the code should allow its easy extension to vector spaces with another metric, e.g. p-norm or different spaces.

Implementation of algorithms for vector clustering in $R^d$ space. The L2 metric will be used. The initialization is performed with the `k-Means++` technique and the update based on the `MacQueen` method. The algorithms differ in the assignment step where one of the following algorithms is used:

1. `Lloyd's` exact algorithm

or inverse search by region search with:

2. `LSH`
3. Random `HyperCube` projection
