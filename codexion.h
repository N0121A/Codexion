#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_sim		t_sim;
typedef enum s_scheduler	t_scheduler;

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
    int				compile_count;
    t_dongle		*left;
    t_dongle		*right;
	pthread_mutex_t	lock;
	pthread_t		thread;
	long			last_compile_start;
	t_sim    		*sim;
} t_coder;

typedef struct s_sim
{
	long			start_ms;
	int				stop;
	int				number_of_coders;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	int				number_of_compiles_required;
	long			dongle_cooldown;
	t_scheduler		scheduler;
	long			start_time;
	pthread_mutex_t print_mutex;
	t_coder			*coders;
	t_dongle		*dongles;
} t_sim;


typedef enum s_scheduler
{
	FIFO,
	EDF
} t_scheduler;

int parse_args(int argc, const char **argv, t_sim *sim);
int init_coders(t_sim *sim);
int init_dongles(t_sim *sim);

#endif
