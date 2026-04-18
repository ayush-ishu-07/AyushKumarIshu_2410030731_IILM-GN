#include <stdio.h>
#include <windows.h>

#define N 5

HANDLE mutex;
HANDLE S[N];

int state[N]; // 0=thinking, 1=hungry, 2=eating

void test(int i) {
    if (state[i] == 1 &&
        state[(i + 4) % N] != 2 &&
        state[(i + 1) % N] != 2) {

        state[i] = 2;
        printf("Philosopher %d is Eating\n", i);
        ReleaseSemaphore(S[i], 1, NULL);
    }
}

void take_fork(int i) {
    WaitForSingleObject(mutex, INFINITE);

    state[i] = 1;
    printf("Philosopher %d is Hungry\n", i);

    test(i);

    ReleaseMutex(mutex);
    WaitForSingleObject(S[i], INFINITE);
}

void put_fork(int i) {
    WaitForSingleObject(mutex, INFINITE);

    state[i] = 0;
    printf("Philosopher %d is Thinking\n", i);

    test((i + 4) % N);
    test((i + 1) % N);

    ReleaseMutex(mutex);
}

DWORD WINAPI philosopher(LPVOID num) {
    int i = *(int*)num;

    for (int j = 0; j < 3; j++) {
        printf("Philosopher %d is Thinking\n", i);
        Sleep(1000);

        take_fork(i);

        Sleep(1000);

        put_fork(i);
    }
    return 0;
}

int main() {
    HANDLE thread_id[N];
    int phil[N];

    mutex = CreateMutex(NULL, FALSE, NULL);

    for (int i = 0; i < N; i++) {
        S[i] = CreateSemaphore(NULL, 0, 1, NULL);
    }

    for (int i = 0; i < N; i++) {
        phil[i] = i;
        thread_id[i] = CreateThread(NULL, 0, philosopher, &phil[i], 0, NULL);
    }

    for (int i = 0; i < N; i++) {
        WaitForSingleObject(thread_id[i], INFINITE);
    }

    return 0;
}