#ifndef DSA_SCHEDULER_H
#define DSA_SCHEDULER_H

// Simulates round-robin scheduling on the processes present in file stored at path argument
// and prints the process stats to stdout in order of their completion.
void visualize_round_robin(char *path);
void visualize_round_robin_array(char *path);

#endif //DSA_SCHEDULER_H
