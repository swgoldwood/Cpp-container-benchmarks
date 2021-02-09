# Cpp-container-benchmarks
C++ container benchmarks.

Benchmarks random access of vector, list, set and unordered_set in increasing sizes by measuring performance of random find calls. Add --benchmark_format=(json|csv) as argument to output these file formats, for python or excel munging.

The benchmarking is first executed as standalone containers for each type producing results we would expect. List slower than vector. vector slower than set. unordered_set is very consistently fast.

Then scatterRead bool is enabled that produces thousands of containers and are randomly accessed to simulate real-world applications where data is most likely not in caches. This produces interesting results showing a vector is faster than a set, up to around 2048 elements. Meaning a linear O(n) number of reads of a 2048 size vector is on average faster than O(log n) reads for a set in busy applications. Additionally vector is faster than unordered_map

Finally the scatterWrite. Somewhat contrived but I think it simulates worst case access times, which could happen in real-world applications that have organically growing data sets.

Output on i9 macbook pro 2020:

```
/Users/sebastianwarren/CLionProjects/container_performance/cmake-build-release/container_performance
2021-02-09T11:53:46+00:00
Running /Users/sebastianwarren/CLionProjects/container_performance/cmake-build-release/container_performance
Run on (16 X 2300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 256 KiB (x8)
  L3 Unified 16384 KiB (x1)
Load Average: 2.56, 1.42, 1.02
----------------------------------------------------------------------------------------------------------------------
Benchmark                                                                            Time             CPU   Iterations
----------------------------------------------------------------------------------------------------------------------
VecListFixture<std::vector<int64_t>>/Vector/8                                     21.8 ns         21.8 ns     29958315
VecListFixture<std::vector<int64_t>>/Vector/16                                    23.5 ns         23.5 ns     30130076
VecListFixture<std::vector<int64_t>>/Vector/32                                    27.8 ns         27.7 ns     24661781
VecListFixture<std::vector<int64_t>>/Vector/64                                    32.8 ns         32.8 ns     19235631
VecListFixture<std::vector<int64_t>>/Vector/128                                   42.9 ns         42.8 ns     16341166
VecListFixture<std::vector<int64_t>>/Vector/256                                   61.0 ns         60.9 ns     10897316
VecListFixture<std::vector<int64_t>>/Vector/512                                   86.8 ns         86.7 ns      8105417
VecListFixture<std::vector<int64_t>>/Vector/1024                                   153 ns          153 ns      4595075
VecListFixture<std::vector<int64_t>>/Vector/2048                                   272 ns          272 ns      2421073
VecListFixture<std::vector<int64_t>>/Vector/4096                                   527 ns          526 ns      1303975
VecListFixture<std::vector<int64_t>>/Vector/8192                                   971 ns          970 ns       695362
VecListFixture<std::vector<int64_t>>/Vector/16384                                 1894 ns         1893 ns       363880
VecListFixture<std::vector<int64_t>>/Vector/32768                                 3848 ns         3848 ns       179822
VecListFixture<std::list<int64_t>>/List/8                                         22.3 ns         22.3 ns     31073823
VecListFixture<std::list<int64_t>>/List/16                                        25.9 ns         25.9 ns     26788619
VecListFixture<std::list<int64_t>>/List/32                                        32.3 ns         32.3 ns     21431305
VecListFixture<std::list<int64_t>>/List/64                                        47.4 ns         47.4 ns     14384261
VecListFixture<std::list<int64_t>>/List/128                                       76.3 ns         76.3 ns      9054925
VecListFixture<std::list<int64_t>>/List/256                                        136 ns          136 ns      5270727
VecListFixture<std::list<int64_t>>/List/512                                        249 ns          248 ns      2632579
VecListFixture<std::list<int64_t>>/List/1024                                       485 ns          485 ns      1438840
VecListFixture<std::list<int64_t>>/List/2048                                      1268 ns         1268 ns       532348
VecListFixture<std::list<int64_t>>/List/4096                                      3133 ns         3132 ns       266318
VecListFixture<std::list<int64_t>>/List/8192                                      5034 ns         5034 ns       141245
VecListFixture<std::list<int64_t>>/List/16384                                    11627 ns        11626 ns        59808
VecListFixture<std::list<int64_t>>/List/32768                                    23914 ns        23910 ns        28590
SetHashFixture<std::set<int64_t>>/Set/8                                           14.5 ns         14.5 ns     47795272
SetHashFixture<std::set<int64_t>>/Set/16                                          23.3 ns         23.3 ns     30237973
SetHashFixture<std::set<int64_t>>/Set/32                                          28.1 ns         28.1 ns     24922828
SetHashFixture<std::set<int64_t>>/Set/64                                          31.9 ns         31.9 ns     21914240
SetHashFixture<std::set<int64_t>>/Set/128                                         34.8 ns         34.8 ns     19622024
SetHashFixture<std::set<int64_t>>/Set/256                                         37.5 ns         37.5 ns     18315258
SetHashFixture<std::set<int64_t>>/Set/512                                         39.8 ns         39.8 ns     17595102
SetHashFixture<std::set<int64_t>>/Set/1024                                        44.7 ns         44.7 ns     15995868
SetHashFixture<std::set<int64_t>>/Set/2048                                        50.8 ns         50.8 ns     13355720
SetHashFixture<std::set<int64_t>>/Set/4096                                        58.5 ns         58.5 ns     11843530
SetHashFixture<std::set<int64_t>>/Set/8192                                        64.8 ns         64.8 ns     10851872
SetHashFixture<std::set<int64_t>>/Set/16384                                       93.8 ns         93.8 ns      7460460
SetHashFixture<std::set<int64_t>>/Set/32768                                        133 ns          133 ns      4901583
SetHashFixture<std::unordered_set<int64_t>>/Hash/8                                10.1 ns         10.1 ns     70771408
SetHashFixture<std::unordered_set<int64_t>>/Hash/16                               9.93 ns         9.93 ns     67501109
SetHashFixture<std::unordered_set<int64_t>>/Hash/32                               10.1 ns         10.1 ns     70852354
SetHashFixture<std::unordered_set<int64_t>>/Hash/64                               9.98 ns         9.98 ns     69618491
SetHashFixture<std::unordered_set<int64_t>>/Hash/128                              9.99 ns         9.99 ns     71080422
SetHashFixture<std::unordered_set<int64_t>>/Hash/256                              9.93 ns         9.93 ns     70840164
SetHashFixture<std::unordered_set<int64_t>>/Hash/512                              9.91 ns         9.91 ns     68945818
SetHashFixture<std::unordered_set<int64_t>>/Hash/1024                             10.0 ns         10.0 ns     70852354
SetHashFixture<std::unordered_set<int64_t>>/Hash/2048                             10.2 ns         10.2 ns     69560378
SetHashFixture<std::unordered_set<int64_t>>/Hash/4096                             10.8 ns         10.8 ns     64572667
SetHashFixture<std::unordered_set<int64_t>>/Hash/8192                             12.4 ns         12.4 ns     56684752
SetHashFixture<std::unordered_set<int64_t>>/Hash/16384                            14.8 ns         14.8 ns     46605768
SetHashFixture<std::unordered_set<int64_t>>/Hash/32768                            16.2 ns         16.2 ns     42523980
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/8                   40.5 ns         40.5 ns     17141654
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/16                  45.8 ns         45.8 ns     15308611
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/32                  53.8 ns         53.7 ns     13556433
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/64                  92.1 ns         92.1 ns      7792150
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/128                  164 ns          164 ns      4145741
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/256                  229 ns          229 ns      3062827
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/512                  317 ns          316 ns      2224963
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/1024                 511 ns          511 ns      1221214
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/2048                 834 ns          834 ns       882357
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/4096                1479 ns         1479 ns       483502
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/8192                2761 ns         2761 ns       265559
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/16384               5208 ns         5208 ns       100000
VecListFixture<std::vector<int64_t>, true>/VectorScatterReads/32768               9769 ns         9769 ns        78494
VecListFixture<std::list<int64_t>, true>/ListScatterReads/8                       45.4 ns         45.4 ns     13978752
VecListFixture<std::list<int64_t>, true>/ListScatterReads/16                      88.6 ns         88.5 ns      7954365
VecListFixture<std::list<int64_t>, true>/ListScatterReads/32                       161 ns          161 ns      4136089
VecListFixture<std::list<int64_t>, true>/ListScatterReads/64                       244 ns          244 ns      2874861
VecListFixture<std::list<int64_t>, true>/ListScatterReads/128                      391 ns          391 ns      1959999
VecListFixture<std::list<int64_t>, true>/ListScatterReads/256                      703 ns          703 ns      1157446
VecListFixture<std::list<int64_t>, true>/ListScatterReads/512                     1115 ns         1115 ns       644728
VecListFixture<std::list<int64_t>, true>/ListScatterReads/1024                    1996 ns         1996 ns       357125
VecListFixture<std::list<int64_t>, true>/ListScatterReads/2048                    3433 ns         3433 ns       207619
VecListFixture<std::list<int64_t>, true>/ListScatterReads/4096                    6114 ns         6113 ns       109036
VecListFixture<std::list<int64_t>, true>/ListScatterReads/8192                   12069 ns        12069 ns        57446
VecListFixture<std::list<int64_t>, true>/ListScatterReads/16384                  26891 ns        26888 ns        26899
VecListFixture<std::list<int64_t>, true>/ListScatterReads/32768                  46059 ns        46053 ns        14946
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/8                         53.2 ns         53.2 ns     12917751
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/16                         121 ns          121 ns      5943536
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/32                         213 ns          213 ns      3392015
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/64                         333 ns          333 ns      2146258
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/128                        482 ns          482 ns      1517770
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/256                        609 ns          609 ns      1101530
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/512                        819 ns          819 ns       818761
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/1024                      1017 ns         1017 ns       618610
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/2048                      1126 ns         1125 ns       544057
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/4096                      1161 ns         1161 ns       549692
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/8192                      1264 ns         1263 ns       527975
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/16384                     1263 ns         1262 ns       541364
SetHashFixture<std::set<int64_t>, true>/SetScatterReads/32768                     1366 ns         1365 ns       521660
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/8              60.7 ns         60.7 ns     12083758
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/16              110 ns          110 ns      6742829
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/32              131 ns          131 ns      5599283
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/64              143 ns          143 ns      5020080
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/128             157 ns          157 ns      4666573
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/256             161 ns          161 ns      4499640
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/512             170 ns          170 ns      4119174
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/1024            181 ns          181 ns      3480959
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/2048            171 ns          171 ns      3845816
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/4096            174 ns          173 ns      3837088
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/8192            171 ns          171 ns      4227564
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/16384           170 ns          170 ns      4045588
SetHashFixture<std::unordered_set<int64_t>, true>/HashScatterReads/32768           176 ns          176 ns      3976279
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/8                44.2 ns         44.2 ns     13392772
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/16               50.3 ns         50.2 ns     14175263
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/32               67.0 ns         67.0 ns     10749386
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/64                116 ns          116 ns      6410198
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/128               172 ns          172 ns      4038330
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/256               243 ns          243 ns      2941214
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/512               345 ns          345 ns      2019491
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/1024              557 ns          556 ns      1388173
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/2048              901 ns          901 ns       814664
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/4096             1547 ns         1546 ns       439820
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/8192             2781 ns         2779 ns       253531
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/16384            5357 ns         5353 ns       100000
VecListFixture<std::vector<int64_t>, true, true>/VectorScatterRW/32768           10571 ns        10565 ns        68500
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/8                    89.5 ns         89.4 ns      7635336
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/16                    305 ns          305 ns      2257649
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/32                   1131 ns         1130 ns       671843
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/64                   2929 ns         2928 ns       234960
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/128                  6524 ns         6521 ns       117980
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/256                 13848 ns        13843 ns        51972
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/512                 29069 ns        29059 ns        24516
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/1024                59023 ns        58989 ns        10891
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/2048               122151 ns       122126 ns         6204
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/4096               240804 ns       240710 ns         2910
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/8192               474504 ns       473830 ns         1463
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/16384              889498 ns       889410 ns          783
VecListFixture<std::list<int64_t>, true, true>/ListScatterRW/32768             1770331 ns      1768627 ns          426
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/8                      93.2 ns         93.1 ns      7528663
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/16                      227 ns          227 ns      3245639
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/32                      364 ns          363 ns      1917504
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/64                      512 ns          512 ns      1000000
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/128                     669 ns          669 ns      1128413
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/256                     811 ns          811 ns       926907
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/512                     988 ns          987 ns       720951
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/1024                   1243 ns         1239 ns       539408
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/2048                   1312 ns         1311 ns       534527
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/4096                   1384 ns         1383 ns       507404
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/8192                   1494 ns         1494 ns       487211
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/16384                  1568 ns         1567 ns       455545
SetHashFixture<std::set<int64_t>, true, true>/SetScatterRW/32768                  1721 ns         1713 ns       414233
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/8            150 ns          149 ns      5112213
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/16           154 ns          154 ns      3820564
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/32           166 ns          166 ns      4276611
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/64           190 ns          190 ns      3803624
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/128          201 ns          201 ns      3569553
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/256          203 ns          203 ns      3428448
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/512          207 ns          207 ns      3383817
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/1024         205 ns          205 ns      3508209
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/2048         223 ns          223 ns      3231495
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/4096         220 ns          220 ns      3244391
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/8192         218 ns          218 ns      3226862
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/16384        218 ns          218 ns      3275252
SetHashFixture<std::unordered_set<int64_t>, true, true>/HashScatterRW/32768        213 ns          213 ns      3348113

Process finished with exit code 0
```
