### MultidimensionalBoxIterator
Generalized version of CombsOnGrid without hashing, connectivity and templates.

### Example 
> How much combinations from k = 5 elements are possible on 10x8x8 grid with minimal Chebyshev distance between any pair r = 7?
```cpp
    vector <int> dims = {10, 8, 8};
    int r = 7, k = 5;
    auto m = MultidimensionalBoxIterator(dims, r);
    m.run(k); 
```

This test runs in 5s on my laptop.
For comparison combination space can be just iterated (without minimal distance counting and checks, $C_{640}^{5} \sim 0.8 \cdot 10^{12} $) in ~320s 
which is decent lower bound for any naive solution.
