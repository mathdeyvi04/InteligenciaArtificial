#ifndef GRAPHICX_HPP
#define GRAPHICX_HPP

#define True true
#define False false

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

/**
 * @brief Representará nossa janela e suas funcionalidades
 */
class Graphicx {
private:

	SDL_Window*   _window   = nullptr;
	SDL_Renderer* _renderer = nullptr;
	const int _width, _height = 0;
	bool _is_running = False;

	int    _FPS = 30;            ///< Quantidade de frames por segundo
	int    _delay = 1000 / _FPS;  ///< Tempo ideal por frame em Milisegundos
	Uint32 _last_frame = 0;      ///< Momento do Último frame 
	int    _frame_time = 0;  	 ///< Intervalo de Tempo Medido
	int   _switch_phase_fps = 0; ///< Contador Auxiliar para Fases do Controle de FPS
	int   _switch_phase_renderer = 0; ///< Contador Auxiliar para Fases do Renderizador
	SDL_Event evento;

public:

	/**
	 * @brief Construtor da Classe
	 * @details 
	 * 
	 * Cada inicialização é verificada. Havendo erro, os passos anteriores
	 * são revertidos/liberados.	
	 */
	Graphicx(
		const std::string nome_da_janela,
		int width,
		int height
	) : _width(width),
		_height(height)
	{	

		srand(time(NULL));

		if(
			SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0
		){

			std::cerr << "Erro ao inicializar SDL: "
					  << SDL_GetError() 
					  << std::endl;
		}

		_window = SDL_CreateWindow(
			nome_da_janela.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width, height,
			SDL_WINDOW_SHOWN
		);

		if(
			!_window
		){

			std::cerr << "Erro ao criar Window: "
					  << SDL_GetError() 
					  << std::endl;
			SDL_Quit();
		}

		_renderer = SDL_CreateRenderer(
			_window,
			-1,
			SDL_RENDERER_ACCELERATED
		);

		if(
			!_renderer
		){

			std::cerr << "Erro ao criar Renderer: "
					  << SDL_GetError() 
					  << std::endl;
			SDL_DestroyWindow(_window);
			SDL_Quit();
		}

		// Se chegou até aqui, foi bem sucedido.
		_is_running = True;
	}

	/**
	 * @brief Destrutor da Classe
	 */
	~Graphicx(){

		if( _renderer){ SDL_DestroyRenderer(_renderer);}
		if( _window  ){ SDL_DestroyWindow(_window);    } 
		SDL_Quit();
	}

	/**
	 * @brief Getter do Window	
	 */
	SDL_Window*
	get_window() const { return _window; }

	/**
	 * @brief Getter do Renderer	
	 */
	SDL_Renderer*
	get_renderer() const { return _renderer; }

	/**
	 * @brief Getter do comprimento
	 */
	int
	get_width() const { return _width; }

	/**
	 * @brief Getter da largura	
	 */
	int
	get_height() const { return _height; }

	/**
	 * @brief Verificação de Funcionamento
	 */
	bool
	if_is_running() const { return _is_running; }

	/**
	 * @brief Responsável por controlar FPS da aplicação.
	 * @details
	 * 
	 * Implementação inteligente e que retira quaisquer responsabilidades
	 * do usuário.
	 */
	void
	controll_fps(){

		if(
			!_switch_phase_fps
		){

			_last_frame = SDL_GetTicks();
		}
		else{

			_frame_time = SDL_GetTicks() - _last_frame;
			if( _delay > _frame_time ){ return SDL_Delay( _delay - _frame_time); }
			//printf("\ndelay_aplicado = %d | _delay = %d | _frame_time = %d", _delay - _frame_time, _delay, _frame_time);
		}

		// Garantimos que não exceda mais que 2.
		_switch_phase_fps = (_switch_phase_fps + 1) % 2;
	}

	/**
	 * @brief Controlador de Inputs
	 * @details
	 * 
	 * Usamos um `while(SDL_PollEvent(...))` para garantir que todos 
	 * as entradas sejam tratadas antes do próximo frame.
	 */
	void
	get_keys(){

		while(
			SDL_PollEvent(&evento)
		){

			if( evento.type == SDL_QUIT ){
				_is_running = False;
			}
		}
	}

	/**
	 * @brief Renderizador básico
	 * @details
	 * 
	 * Se concentra em limpar a tela e preenchê-la.	
	 */
	void
	set_renderer(){

		if(
			!_switch_phase_renderer
		){

			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255); // Branco
			SDL_RenderClear(_renderer);
		}
		else{

			SDL_RenderPresent(_renderer);
		}

		_switch_phase_renderer = (_switch_phase_renderer + 1) % 2;
	}





};

#endif // GRAPHICX_HPP