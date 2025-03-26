# How much combinations from k = 5 elements are possible in cube 10x8x8 with minimal distance allowed r = 7?
```cpp
    vector <int> dims = {10, 8, 8};
    int r = 7, k = 5;
    auto m = MultidimensionalBoxIterator(dims, r);
    m.run(k); 
```

Test runs in 5s on my laptop and combination space can be just iterated (without any checks and counting, $C_{640}^{5} ~ 0.8 #cdot 10^12$) in ~320s 
which is decent lower bound for naive solution.
