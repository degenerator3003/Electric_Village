#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HOURS 24
#define NUM_GENERATORS 2
#define NUM_CONSUMERS 3
#define NUM_BALANCERS 1

typedef struct {
    char *name;
    float capacity;  // max generation per hour (MW)
    float current_output;
} Generator;

typedef struct {
    char *name;
    float base_demand;  // average MW usage
    float demand;
} Consumer;

typedef struct {
    char *name;
    float buffer;  // energy stored or drawn (MW)
} Balancer;

float random_variation(float base, float variation) {
    return base + ((rand() % 1000) / 1000.0 - 0.5) * 2 * variation;
}

int main() {
    srand(time(NULL));

    Generator generators[NUM_GENERATORS] = {
        {"Hydro Station", 150.0, 0},
        {"Solar Farm", 80.0, 0}
    };

    Consumer consumers[NUM_CONSUMERS] = {
        {"Village", 30.0, 0},
        {"Town", 60.0, 0},
        {"City", 120.0, 0}
    };

    Balancer balancers[NUM_BALANCERS] = {
        {"Main Grid Station", 0.0}
    };

    for (int hour = 0; hour < HOURS; hour++) {
        printf("\nHour %02d:\n", hour);

        // Update generators
        float total_generation = 0;
        for (int i = 0; i < NUM_GENERATORS; i++) {
            generators[i].current_output = random_variation(generators[i].capacity, 20.0);
            total_generation += generators[i].current_output;
            printf("  Generator %s produces %.2f MW\n", generators[i].name, generators[i].current_output);
        }

        // Update consumers
        float total_demand = 0;
        for (int i = 0; i < NUM_CONSUMERS; i++) {
            consumers[i].demand = random_variation(consumers[i].base_demand, 15.0);
            total_demand += consumers[i].demand;
            printf("  Consumer %s needs %.2f MW\n", consumers[i].name, consumers[i].demand);
        }

        // Balance the system
        float imbalance = total_generation - total_demand;
        balancers[0].buffer += imbalance;

        printf("  Balance Station buffer change: %.2f MW → total buffer: %.2f MW\n",
               imbalance, balancers[0].buffer);

        if (balancers[0].buffer > 100) {
            printf("  ⚠ Overproduction! Consider storing or exporting energy.\n");
        } else if (balancers[0].buffer < -100) {
            printf("  ⚠ Underproduction! Risk of blackout or need import!\n");
        }
    }

    return 0;
}
