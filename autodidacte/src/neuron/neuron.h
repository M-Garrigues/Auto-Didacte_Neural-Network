#ifndef NEURON_H_INCLUDED
#define NEURON_H_INCLUDED
#include "../link/link.h"
typedef struct Neurons
{
    double input;
    double output;
    int activation;
    Link * links;
}; Neuron


#endif // NEURON_H_INCLUDED
