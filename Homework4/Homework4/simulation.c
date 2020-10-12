// Simulation.cpp : Defines the entry point for the console application.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE	100


typedef struct element {
	int id;
	int arrival_time;
	int service_time;
} element;	 	// Customer structure

typedef struct QueueType {
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;
QueueType queue;

// Real random number generation function between 0 and 1
double random() {
	return rand() / (double)RAND_MAX;
}

// Various state variables needed for simulation
int duration = 20; // Simulation time, 명확한 비교를 위해 10->20 으로 수정
double arrival_prob = 0.7; // Average number of customers arriving in one time unit
int max_serv_time = 5; // maximum service time for one customer
int clock;

// Results of the simulation
int customers; // Total number of customers
int served_customers; // Number of customers served
int waited_time; // Time the customers waited

// Empty state detection function
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}
// Full state detection function
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// Insert function
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		printf("Queue is full\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
// delete function
element dequeue(QueueType* q)
{
	if (is_empty(q))
		printf("Queue is empty\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

// Generate a random number.
// If it is smaller than ‘arrival_prov’, assume that new customer comes in the bank.
int is_customer_arrived()
{
	if (random() < arrival_prob)
		return true;
	else return false;
}
// Insert newly arrived customer into queue
void insert_customer(int arrival_time)
{
	element customer;

	customer.id = customers++;
	customer.arrival_time = arrival_time;
	customer.service_time = (int)(max_serv_time * random()) + 1;
	enqueue(&queue, customer);
	printf("Customer %d comes in %d minutes. Service time is %d minutes.\n", customer.id, customer.arrival_time, customer.service_time);
}

// Retrieve the customer waiting in the queue and return the customer's service time.
int remove_customer()
{
	element customer;
	int service_time = 0;

	if (is_empty(&queue)) return 0;
	customer = dequeue(&queue);
	service_time = customer.service_time - 1;
	served_customers++;
	waited_time += clock - customer.arrival_time;
	printf("Customer %d starts service in %d minutes. Wait time was %d minutes.\n", customer.id, clock, clock - customer.arrival_time);
	return service_time;
}


// Print the statistics.
void print_stat()
{
	printf("Number of customers served = %d\n", served_customers);
	printf("Total wait time =% d minutes\n", waited_time);
	printf("Average wait time per person = %f minutes\n",
		(double)waited_time / served_customers);
	printf("Number of customers still waiting = %d\n", customers - served_customers);
}


// Simulation program
/*
직원 1명 / 직원 2명
서비스 받은 손님의 수 : 5명 / 15명
총 대기 시간 : 26분 / 23분
평균 대기 시간 : 5.2분 / 1.5분
대기 중인 손님의 수 : 12명 / 2명
*/
void main()
{
	//아래 두줄이랑 조교님이 주신 힌트랑 같은 내용입니다.
	int staff1_service_time = 0;
	int staff2_service_time = 0;

	clock = 0;
	while (clock < duration) {
		clock++;
		printf("Current time=%d\n", clock);
		if (is_customer_arrived()) {
			insert_customer(clock);
		}

		if (staff1_service_time > 0) //staff1이 아직 서비스 중
			staff1_service_time--;
		else { //staff1이 노는 중
			staff1_service_time = remove_customer();
			if (staff1_service_time > 0) //staff1이 서비스를 시작
				printf("Staff1 starts service.\n");
		}

		if (staff2_service_time > 0) //staff2가 아직 서비스 중
			staff2_service_time--;
		else { //staff2가 노는 중
			staff2_service_time = remove_customer();
			if (staff2_service_time > 0) //staff2가 서비스를 시작
				printf("Staff2 starts service.\n");
		}
	}
	print_stat();
}