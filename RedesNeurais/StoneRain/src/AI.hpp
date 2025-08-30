#ifndef AI_HPP
#define AI_HPP

#include "Player.hpp"

struct Bot {
	double pos[2] = {0, 0};
	SDL_Rect rect{0, 0, 15, 15};
};

class AI : public Player {
private: 

	const int max_threads = 2;
	std::atomic<int> var{0};

	std::vector<bool> running_flags;
	std::vector<std::thread> workers;

public:
	AI() = default;

	/**
	 * @brief Responsável por desligar cada uma das threads ligadas.	
	 */
	~AI(){

		// Forçar desligamento de todas
		for(
			int i = 0;
				i < max_threads;
				i++
		){

			running_flags[i] = False;
			if(workers[i].joinable()){
				workers[i].join();
			}
		}
	}

	/**
	 * @brief As threads jogarão utilizando essa função.
	 */
	void
	run(int id = -1) override {

		// Não ocupará nova memória, lembra?
		const std::vector<Object>& obsts = rain->get_obsts();

		Bot player;
		fprintf(stderr, "\nSai da thread %d", id);
	}

	/**
	 * @brief Contará quantas threads ainda estão vivas.	
	 */
	bool
	is_alive() override { return var.load() > 0; };

	/**
	 * @brief Iniciará as threads.	
	 */
	void
	init() override {

		workers.reserve(max_threads);
		running_flags.reserve(max_threads);
		for(
			int i = 0;
				i < max_threads;
				i++
		){
			running_flags.emplace_back(True);
			workers.emplace_back(
				[this, i](){ run(i); }
			);
			
		}

	}

	/**
	 * @brief Sem utilidade.
	 * @details
	 * 
	 * Mais responsabilidades serão jogadas para a thread.
	 */
	void
	move_and_print( SDL_Renderer* renderer, double interv ) override {}
};

#endif // AI_HPP