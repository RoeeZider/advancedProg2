cmake_minimum_required(VERSION 3.15)
project(advancedProg2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(advancedProg2 main.cpp ClientHandler.h Server.h CacheManager.h Solver.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.cpp MyTestClientHandler.h FileCacheManager.cpp FileCacheManager.h stringReverser.cpp stringReverser.h State.h Searchable.h ISearcher.h BestFirstSearch.cpp BestFirstSearch.h Searcher.h PriorityQueue.h Point.cpp Point.h Matrix.h MyClientHandler.h SolverMatrix.cpp SolverMatrix.h Dfs.cpp Dfs.h AStar.cpp AStar.h BreadthFS.cpp BreadthFS.h MyParallelServer.cpp MyParallelServer.h)