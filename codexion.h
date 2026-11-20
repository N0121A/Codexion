#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define GO_SIM 0
# define STOP_SIM 1

typedef struct s_sim		t_sim;

typedef enum s_scheduler
{
	FIFO,
	EDF,
} t_scheduler;

typedef struct s_config
{
	int				number_of_coders;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	int				nbr_of_compiles_required;
	long			dongle_cooldown;
	t_scheduler		scheduler;
} t_config;

typedef struct s_dongle
{
	int				id;
	int				in_use;
	long			cooldown_until;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
} t_dongle;

typedef struct s_coder
{
    int				id;
    int				compile_done;
    t_dongle		*left;
    t_dongle		*right;
	pthread_mutex_t	lock;
	pthread_t		thread;
	long			last_compile_start;
	t_sim    		*sim;
} t_coder;

typedef struct s_sim
{
	t_config		config;
	long			start_time;
	int				stop;
	pthread_mutex_t log_lock;
	pthread_mutex_t stop_lock;
	t_coder			*coders;
	t_dongle		*dongles;
} t_sim;


typedef enum s_scheduler
{
	FIFO,
	EDF
} t_scheduler;

int parse_input(t_sim *sim, int argc, const char **argv);

int init_coders(t_sim *sim);
void destroy_coders(t_sim *sim, int count);

int init_dongles(t_sim *sim);
void destroy_dongles(t_sim *sim, int count);

int init_simulation(t_sim *sim);
int start_simulation(t_sim *sim);
int stop_flag(t_sim *sim, int set);
int join_them(t_sim *sim, int count);

void *coder_routine(void *arg);


#endif