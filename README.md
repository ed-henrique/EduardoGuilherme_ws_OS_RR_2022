# Deep First Search in Graphs using Multithreading

Project made by [Eduardo Henrique](https://github.com/ed-henrique) and [Guilherme Lirioberto](https://github.com/Liriogui).

---

## Table of Contents

- [Goals](#goals)
- [Problems Encountered](#problems-encountered)
  - [In C](#in-c)
  - [In C++](#in-c-1)
- [Demo](#demo)
- [References](#references)

---

## Goals

This problem was created with a maze-solving test in mind, but we couldn't implement it in time.

Tests aside, this program must also show how well we can work using threads.

It would also be nice to implement the same thing in C, C++ and Rust, creating room for discussion about the different approaches taken in each one.

---

## Problems Encountered

#### __In C:__

Problems:

1. Running through disconnected graphs;

Possible solutions:

1. Change the code to not stop unless all nodes are visited;

#### __In C++:__

Problems:

1. Can't apply threads to methods inside classes with our knowledge;

Possible solutions:

1. Study threads in C++ or turn the methods into functions outside the class;


## Demo

<!--- Remember to put the video in here after --->

---

## References

Most of the C++ code regarding graphs was taken from [GeeksForGeeks](https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/).
Most of the C code regarding graphs was taken from [Youtube](https://www.youtube.com/watch?v=jQmlXAwUvZ4).

We have also used the references given out by our professor:

- [Busca em Profundidade](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dfs.html)
- [Parallel DFS](https://www.daniweb.com/programming/software-development/threads/456242/parallel-dfs)
