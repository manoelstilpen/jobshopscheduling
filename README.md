### Introduction

This project was developed in Federal University of Ouro Preto, Brazil
and tried to solve the Job Shop Scheduing Problem with total
weighted tardiness.

### Problem Representation

The considered problem representation was based on a disjuctive graph
model which each job operation is equivalent a vertex and a restriction
between two operations generates an edge; Two dummy nodes were added to
help the solution evaluation. Originally this representation was
extracted from [(Kuhpfahl and Bierwirth, 2016)](https://www.sciencedirect.com/science/article/pii/S0305054815001860).

### Implemented Methods

To create a initial solution was tested many dispatch rules and those
that presented the best results were: ASPRT, MOD, SPRT and WSPT rules.

To explore the search space was implemented some algorithms:
"Variable Neighborhood Search", "Smart Variable Neighborhood Search", GRASP,
and "Simulated Annealing". Also, some local searches were implemented:
"Best Improvent" and "First Improvement".

All methods mentioned above are available in this repository.

### Contact

Any question you cand find me on: manoelvstilpen@gmail.com