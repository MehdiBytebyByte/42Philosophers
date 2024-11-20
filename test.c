#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_data
{
	pthread_t       thread;
	int             num;
	pthread_mutex_t mutex;
} t_data;

void *func(void *arg)
{
	t_data *data = (t_data *)arg;
	pthread_mutex_lock(&data->mutex);
	if (data->num == 1)
	{
		pthread_mutex_unlock(&data->mutex);
		printf("Hello from thread %d\n", data->num);
	}
	else if (data->num == 2)
	{
		usleep(1000);
		pthread_mutex_unlock(&data->mutex);
		printf("Hello from thread %d\n", data->num);
	}
	else if (data->num == 3)
	{
		usleep(2000);
		pthread_mutex_unlock(&data->mutex);
		printf("Hello from thread %d\n", data->num);
	}
	return NULL;
}

int main(int ac, char **av)
{
	t_data *data = malloc(sizeof(t_data));
	t_data *data2 = malloc(sizeof(t_data));
	t_data *data3 = malloc(sizeof(t_data));
	pthread_mutex_init(&data->mutex, NULL);
	data2->mutex = data->mutex;
	data3->mutex = data->mutex;

	data->num = 1;
	data2->num = 2;
	data3->num = 3;

	pthread_create(&data->thread, NULL, &func, (void *)data);
	pthread_create(&data2->thread, NULL, &func, (void *)data2);
	pthread_create(&data3->thread, NULL, &func, (void *)data3);

	pthread_join(data->thread, NULL);
	pthread_join(data2->thread, NULL);
	pthread_join(data3->thread, NULL);

	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data2->mutex);
	pthread_mutex_destroy(&data3->mutex);

	free(data);
	free(data2);
	free(data3);

	return 0;
}