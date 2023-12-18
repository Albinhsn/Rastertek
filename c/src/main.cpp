#include "stdio.h"
#include "system.h"
#include <cstdlib>

int main() {
    System *system = (System *)malloc(sizeof(System));

    bool result = InitializeSystem(system);

    if (!result) {
        printf("ERROR: Couldn't initialize system\n");
        return -1;
    }
    Frame(system);

    ShutdownSystem(system);
    free(system);
    system = 0;
    return 0;
}
