#include "data.h"
#include "stdio.h"
#include "system.h"
#include <cstdlib>

#define APP 23

int main() {
    System *system = (System *)malloc(sizeof(System));
    TutorialData *tutorial;
    switch (APP) {
    case 5: {
        tutorial = Tutorial5();
        break;
    }
    case 6: {
        tutorial = Tutorial6();
        break;
    }
    case 7: {
        tutorial = Tutorial7();
        break;
    }
    case 8: {
        tutorial = Tutorial8();
        break;
    }
    case 9: {
        tutorial = Tutorial9();
        break;
    }
    case 10: {
        tutorial = Tutorial10();
        break;
    }
    case 11: {
        tutorial = Tutorial11();
        break;
    }
    case 12: {
        tutorial = Tutorial12();
        break;
    }
    case 13: {
        tutorial = Tutorial13();
        break;
    }
    case 14: {
        tutorial = Tutorial14();
        break;
    }
    case 15: {
        tutorial = Tutorial15();
        break;
    }
    case 16: {
        tutorial = Tutorial16();
        break;
    }
    case 17: {
        tutorial = Tutorial17();
        break;
    }
    case 18: {
        tutorial = Tutorial18();
        break;
    }
    case 19: {
        tutorial = Tutorial19();
        break;
    }
    case 20: {
        tutorial = Tutorial20();
        break;
    }
    case 21: {
        tutorial = Tutorial21();
        break;
    }
    case 22: {
        tutorial = Tutorial22();
        break;
    }
    case 23: {
        tutorial = Tutorial23();
        break;
    }
    default: {
        printf("Unknown tutorial \n");
        exit(1);
    }
    }
    bool result = InitializeSystem(system, tutorial);
    if (!result) {
        printf("ERROR: Couldn't initialize system\n");
        return -1;
    }
    printf("INFO: Initialized system\n");
    Frame(system, tutorial);
    printf("INFO: Shuting Down\n");

    ShutdownSystem(system);
    free(system);
    printf("Shut down system\n");
    ShutdownTutorial(tutorial);
    free(tutorial);
    printf("INFO: Exiting\n");
    return 0;
}
