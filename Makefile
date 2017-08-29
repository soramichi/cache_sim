all:
	g++ -lm cache_sim.cpp -o cache_sim

debug:
	g++ -lm cache_sim.cpp -o cache_sim -g -O0
