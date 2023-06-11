#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

struct TimerData
{
    timer_t timerid;
};

void timer_isr(int signum, siginfo_t *info, void *context)
{
    struct TimerData *timerData = (struct TimerData *)info->si_value.sival_ptr;
    timer_t timerid = timerData->timerid;

    // Timer-Interrupt-Verarbeitung
    printf("Timer ausgelöst.\n");
}

int main()
{
    timer_t timerid;
    struct sigevent sev;
    struct itimerspec its;
    struct TimerData timerData;

    // Timer-Initialisierung
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGALRM;
    sev.sigev_value.sival_ptr = &timerData;
    timer_create(CLOCK_REALTIME, &sev, &timerid);

    // Timer-Intervall
    its.it_value.tv_sec = 1; // Startzeit: 1 Sekunde
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 1; // Intervall: 1 Sekunde
    its.it_interval.tv_nsec = 0;
    timer_settime(timerid, 0, &its, NULL);

    // Endlosschleife, um den Timer zu verwenden
    while (1)
    {
        // Hier kannst du andere Aufgaben ausführen, während der Timer-Interrupt die ISR aufruft
        // ...
    }

    // Timer entfernen
    timer_delete(timerid);

    return 0;
}

// void timer_isr(union sigval sv)
// {
//     printf("Timer ausgelöst.\n");
// }

// int main()
// {
//     timer_t timerid;
//     struct sigevent sev;
//     struct itimerspec its;

//     printf("Hello RPI3 user, let's start coding!\n");

//     // Timer-Initialisierung
//     sev.sigev_notify = SIGEV_THREAD;
//     sev.sigev_notify_function = timer_isr;
//     sev.sigev_value.sival_ptr = &timerid;
//     sev.sigev_notify_attributes = NULL;
//     timer_create(CLOCK_REALTIME, &sev, &timerid);

//     // Timer-Intervall
//     its.it_value.tv_sec = 1; // Startzeit: 1 Sekunde
//     its.it_value.tv_nsec = 0;
//     its.it_interval.tv_sec = 1; // Intervall: 1 Sekunde
//     its.it_interval.tv_nsec = 0;
//     timer_settime(timerid, 0, &its, NULL);

//     // Endlosschleife, um den Timer zu verwenden
//     while (1)
//     {
//         // Hier kannst du andere Aufgaben ausführen, während der Timer-Interrupt die ISR aufruft
//         // ...
//     }

//     // Timer entfernen
//     timer_delete(timerid);

//     return 0;
// }
