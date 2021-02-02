# Cpp-container-benchmarks
C++ container benchmarks.

Benchmarks random access of vector, list, set and unordered_set in increasing sizes through random find calls. This is done first as standalone containers producing expected results. Then scattered flag is enabled that produces thousands of containers and are randomly accessed to simulate real-world applications where data is most likely not in caches. This produces interesting results showing a vector is faster than a set, up to around 2048 elements. Meaning a linear O(n) number of reads of a 2048 size vector is on average faster than O(n log n) reads for a set in busy applications.

output on i9 macbook pro 2020:

```
/Users/sebastianwarren/CLionProjects/container_performance/cmake-build-release/container_performance
2021-02-02T15:16:33+00:00
Running /Users/sebastianwarren/CLionProjects/container_performance/cmake-build-release/container_performance
Run on (16 X 2300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 256 KiB (x8)
  L3 Unified 16384 KiB (x1)
Load Average: 3.62, 3.08, 2.72
--------------------------------------------------------------------------------------------------------------------
Benchmark                                                                          Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------------------
VecListFixture<std::vector<int64_t>>/VectorTest/8                               25.0 ns         25.0 ns     29005925
VecListFixture<std::vector<int64_t>>/VectorTest/16                              28.3 ns         28.3 ns     26971002
VecListFixture<std::vector<int64_t>>/VectorTest/32                              32.0 ns         32.0 ns     23057869
VecListFixture<std::vector<int64_t>>/VectorTest/64                              34.1 ns         34.1 ns     17810481
VecListFixture<std::vector<int64_t>>/VectorTest/128                             49.7 ns         49.5 ns     15792015
VecListFixture<std::vector<int64_t>>/VectorTest/256                             71.0 ns         70.8 ns     10736196
VecListFixture<std::vector<int64_t>>/VectorTest/512                              103 ns          102 ns      6485024
VecListFixture<std::vector<int64_t>>/VectorTest/1024                             220 ns          216 ns      3799371
VecListFixture<std::vector<int64_t>>/VectorTest/2048                             293 ns          293 ns      2298863
VecListFixture<std::vector<int64_t>>/VectorTest/4096                             533 ns          533 ns      1294810
VecListFixture<std::vector<int64_t>>/VectorTest/8192                            1106 ns         1104 ns       663576
VecListFixture<std::vector<int64_t>>/VectorTest/16384                           2060 ns         2058 ns       335045
VecListFixture<std::vector<int64_t>>/VectorTest/32768                           5389 ns         5367 ns       100000
VecListFixture<std::list<int64_t>>/ListTest/8                                   26.9 ns         26.8 ns     25828352
VecListFixture<std::list<int64_t>>/ListTest/16                                  27.0 ns         27.0 ns     25661329
VecListFixture<std::list<int64_t>>/ListTest/32                                  40.0 ns         39.9 ns     19738716
VecListFixture<std::list<int64_t>>/ListTest/64                                  49.9 ns         49.9 ns     13328763
VecListFixture<std::list<int64_t>>/ListTest/128                                 79.6 ns         79.6 ns      9078058
VecListFixture<std::list<int64_t>>/ListTest/256                                  148 ns          148 ns      4891582
VecListFixture<std::list<int64_t>>/ListTest/512                                  282 ns          281 ns      2066878
VecListFixture<std::list<int64_t>>/ListTest/1024                                 540 ns          539 ns      1000000
VecListFixture<std::list<int64_t>>/ListTest/2048                                1470 ns         1468 ns       437949
VecListFixture<std::list<int64_t>>/ListTest/4096                                3482 ns         3477 ns       255843
VecListFixture<std::list<int64_t>>/ListTest/8192                                5948 ns         5946 ns       109629
VecListFixture<std::list<int64_t>>/ListTest/16384                              12839 ns        12836 ns        55592
VecListFixture<std::list<int64_t>>/ListTest/32768                              25627 ns        25617 ns        27658
SetHashFixture<std::set<int64_t>>/SetTest/8                                     14.8 ns         14.8 ns     49252765
SetHashFixture<std::set<int64_t>>/SetTest/16                                    26.3 ns         26.2 ns     26964665
SetHashFixture<std::set<int64_t>>/SetTest/32                                    30.0 ns         30.0 ns     23203702
SetHashFixture<std::set<int64_t>>/SetTest/64                                    34.0 ns         34.0 ns     19913009
SetHashFixture<std::set<int64_t>>/SetTest/128                                   36.9 ns         36.9 ns     18915085
SetHashFixture<std::set<int64_t>>/SetTest/256                                   41.8 ns         41.7 ns     17621766
SetHashFixture<std::set<int64_t>>/SetTest/512                                   45.1 ns         45.0 ns     15336919
SetHashFixture<std::set<int64_t>>/SetTest/1024                                  45.7 ns         45.7 ns     15131307
SetHashFixture<std::set<int64_t>>/SetTest/2048                                  50.6 ns         50.6 ns     10000000
SetHashFixture<std::set<int64_t>>/SetTest/4096                                  68.3 ns         68.2 ns     11394713
SetHashFixture<std::set<int64_t>>/SetTest/8192                                  83.1 ns         83.1 ns      8617082
SetHashFixture<std::set<int64_t>>/SetTest/16384                                 91.4 ns         91.3 ns      7692477
SetHashFixture<std::set<int64_t>>/SetTest/32768                                  138 ns          138 ns      5221893
SetHashFixture<std::unordered_set<int64_t>>/HashTest/8                          10.5 ns         10.5 ns     68812976
SetHashFixture<std::unordered_set<int64_t>>/HashTest/16                         10.4 ns         10.4 ns     66264034
SetHashFixture<std::unordered_set<int64_t>>/HashTest/32                         10.5 ns         10.5 ns     65552278
SetHashFixture<std::unordered_set<int64_t>>/HashTest/64                         10.5 ns         10.5 ns     68521310
SetHashFixture<std::unordered_set<int64_t>>/HashTest/128                        10.5 ns         10.5 ns     68193553
SetHashFixture<std::unordered_set<int64_t>>/HashTest/256                        10.4 ns         10.4 ns     66359517
SetHashFixture<std::unordered_set<int64_t>>/HashTest/512                        10.5 ns         10.5 ns     64310454
SetHashFixture<std::unordered_set<int64_t>>/HashTest/1024                       10.4 ns         10.4 ns     67135979
SetHashFixture<std::unordered_set<int64_t>>/HashTest/2048                       11.2 ns         11.2 ns     67987568
SetHashFixture<std::unordered_set<int64_t>>/HashTest/4096                       11.3 ns         11.3 ns     57919211
SetHashFixture<std::unordered_set<int64_t>>/HashTest/8192                       13.8 ns         13.8 ns     53453068
SetHashFixture<std::unordered_set<int64_t>>/HashTest/16384                      16.0 ns         16.0 ns     44075609
SetHashFixture<std::unordered_set<int64_t>>/HashTest/32768                      17.5 ns         17.5 ns     37488887
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/8                45.1 ns         44.8 ns     15784216
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/16               57.5 ns         57.4 ns     10000000
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/32               54.5 ns         54.5 ns      9525282
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/64                102 ns          102 ns      6694017
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/128               174 ns          174 ns      4236596
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/256               233 ns          233 ns      3005130
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/512               321 ns          321 ns      2249271
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/1024              566 ns          565 ns      1329535
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/2048              879 ns          876 ns       787588
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/4096             1464 ns         1461 ns       485774
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/8192             2942 ns         2939 ns       198325
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/16384            5392 ns         5391 ns       131248
VecListFixture<std::vector<int64_t>, true>/VectorTestScattered/32768           10109 ns        10095 ns        73768
VecListFixture<std::list<int64_t>, true>/ListTestScattered/8                    76.7 ns         76.4 ns     10713356
VecListFixture<std::list<int64_t>, true>/ListTestScattered/16                    125 ns          125 ns      4973004
VecListFixture<std::list<int64_t>, true>/ListTestScattered/32                    194 ns          193 ns      3390766
VecListFixture<std::list<int64_t>, true>/ListTestScattered/64                    261 ns          261 ns      2553719
VecListFixture<std::list<int64_t>, true>/ListTestScattered/128                   406 ns          406 ns      1370292
VecListFixture<std::list<int64_t>, true>/ListTestScattered/256                   702 ns          701 ns       815442
VecListFixture<std::list<int64_t>, true>/ListTestScattered/512                  1175 ns         1175 ns       608415
VecListFixture<std::list<int64_t>, true>/ListTestScattered/1024                 2348 ns         2336 ns       319515
VecListFixture<std::list<int64_t>, true>/ListTestScattered/2048                 3776 ns         3773 ns       194489
VecListFixture<std::list<int64_t>, true>/ListTestScattered/4096                 7476 ns         7473 ns        82305
VecListFixture<std::list<int64_t>, true>/ListTestScattered/8192                13288 ns        13286 ns        53240
VecListFixture<std::list<int64_t>, true>/ListTestScattered/16384               26243 ns        26240 ns        27210
VecListFixture<std::list<int64_t>, true>/ListTestScattered/32768               51343 ns        51215 ns        10000
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/8                      93.3 ns         93.2 ns      8957707
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/16                      175 ns          175 ns      3974089
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/32                      226 ns          225 ns      2999824
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/64                      351 ns          351 ns      2126929
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/128                     494 ns          493 ns      1339277
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/256                     626 ns          625 ns      1189182
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/512                     747 ns          747 ns       929417
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/1024                    933 ns          931 ns       721434
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/2048                    938 ns          937 ns       559646
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/4096                   1142 ns         1141 ns       610102
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/8192                   1141 ns         1141 ns       584185
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/16384                  1265 ns         1264 ns       556231
SetHashFixture<std::set<int64_t>, true>/SetTestScattered/32768                  1515 ns         1513 ns       539079
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/8           43.7 ns         43.7 ns     15846139
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/16          95.7 ns         95.7 ns      8374408
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/32           125 ns          125 ns      6020987
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/64           146 ns          146 ns      4257131
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/128          139 ns          139 ns      4701457
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/256          166 ns          166 ns      4613458
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/512          170 ns          170 ns      4163940
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/1024         190 ns          190 ns      3575880
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/2048         176 ns          176 ns      3959119
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/4096         168 ns          168 ns      3907951
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/8192         170 ns          169 ns      3977544
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/16384        167 ns          167 ns      4085182
SetHashFixture<std::unordered_set<int64_t>, true>/HashTestScattered/32768        170 ns          170 ns      3772202

Process finished with exit code 0
```
