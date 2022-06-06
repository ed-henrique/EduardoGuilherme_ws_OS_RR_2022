# Deep First Search in Graphs using Multithreading

Project made by [Eduardo Henrique](https://github.com/ed-henrique) and [Guilherme Lirioberto](https://github.com/Liriogui).

---

## Table of Contents

- [Goals](#goals)
- [Problems Encountered](#problems-encountered)
- [Demo](#demo)
- [References](#references)

---

## Goals

Things we have done:
- Implement randomly generated graphs with a given size;
- Implement DFS without multithreading;
- Implement a DFS with multithreading that works from time to time;

Things we haven't done:
- Implement a maze-solving test for the algorithm;
- Implement a fully-functional DFS with multithreading;

---

## Problems Encountered

Problems:

1. Running through disconnected graphs;
2. Some nodes are not visiting their neighbors before leaving the stack;

Possible solutions:

1. Not required to solve this specific issue;
2. No idea;

## Demo

<!--- Remember to put the video in here after --->

---

## References

Most of the code regarding graphs was inspired by this [Youtube Video](https://www.youtube.com/watch?v=jQmlXAwUvZ4).

Most of the code regarding DFS using multithreading was taken from this [Github Repo](https://github.com/Raafm/algorithm_visualization/blob/main/multithreadDFS.py).

We have also used the references given out by our professor:

- [Busca em Profundidade](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dfs.html)
- [Parallel DFS](https://www.daniweb.com/programming/software-development/threads/456242/parallel-dfs)
