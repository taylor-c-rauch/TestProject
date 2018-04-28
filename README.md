# TestProject
Test project for Metis Machine

Requirements:
 - For the purposes of the test, the articles will be denoted by a single letter and contain no other information.
 - Given a list of A, B, C, and D, where C depends on A, D depends on B, and A depends on B, find the proper order.
 - Given the same list above, check that your algorithm holds when A depends on C, D on A, and B on D.
 - Your algorithm should work for any arbitrary set of article letters, with any given dependence on one another. You do not have to solve for circular dependencies.

Bonus Points implemented:
 - Solve for: A->B, A->D, B->C, B->E, C->D, C->E, where the -> denotes a dependence of the right hand side, on the left hand side.
 - Solve for circular dependencies in a reasonable way.
 
 Files:
  - test.cpp : code written to fulfill the requirements
  - testNoComments.cpp : same code as test.cpp but with no comments to facilitate viewing the code
  - Makefile: to compile test.cpp
  
 Language: C++
  
Overview:
  In order to solve this problem, I treated the articles as vertices in a graph and implemented a topological sort, to print out the letters associated with the letters in the correct order.
