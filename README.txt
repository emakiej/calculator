Assumptions:

1. very long strings are provided and have to be handled properly

2. Application is using stack memory. In case of really large expressions we'd need to switch to using heap memory in some cases.

3. BigInteger class is not expected to be as efficient as possible but to be as readable as possible

4. In other cases sometimes decision to resign of efficiency for clarity sake was made. If some of such places would appear to be a bottleneck, then the particular part would be optimised

5. The following expression is incorrect: 7–2

6. The following expression is correct: 7-(-2)

7. Application is going to be build with O2 in release mode.

8. Depencies (gtest, gmock, pthread) are installed in system







