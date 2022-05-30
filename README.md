# Deep First Search in Graphs using Multithreading

Project made by [Eduardo Henrique](https://github.com/ed-henrique) and [Guilherme Lirioberto]()

## Table of Contents

- [Deep First Search in Graphs using Multithreading](#deep-first-search-in-graphs-using-multithreading)
- [Table of Contents](#table-of-contents)
- [Goals](#goals)
- [Problems Encountered](#problems-encountered)
- [Demo](#demo)
- [References](#references)

## Goals

This problem was created with two tests in mind:

- Solve a given maze;
- Print the path to the deepest node of a given graph;

Tests aside, this program must also show how well we can work using threads.

It would also be nice to implement the same thing in C, C++ and Rust, creating room for discussion about the different approaches taken in each one.

## Problems Encountered

What is going wrong right now:

1. Something regarding DFSUtil while loop, certainly;
2. No threads are applied yet;
3. Graph is dynamically allocated, what does not make things easier;

Possible solutions:

1. No fucking idea;
2. Threads may only be applied once we can solve the DFS without them;
3. We can use an adjacency matrix instead of a linked list;

## Demo

<!--- Remember to put the video in here after --->

## References

Most of the code regarding graphs was taken from [GeeksForGeeks](https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/).

We have also used the references given out by our professor:

- [Busca em Profundidade](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dfs.html)
- [Parallel DFS](https://www.daniweb.com/programming/software-development/threads/456242/parallel-dfs)