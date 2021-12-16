
# This solution consists of giving each philosopher one of three states (thinking, hungry or eating).

# PHILOSOPHERS = 5
# state = ['thinking'] * PHILOSOPHERS
# sem = [Semaphore(0) for _ in range(PHILOSOPHERS)]
# mutex = Semaphore(1)
# sem indicates whether a philosopher can start eating or not.
# mutex is used so that no two philosophers may access the pickup or putdown list at the same time.
# The state list is used to know the state of each philosopher.
# A philosopher will only eat if its neighbors are not eating
# The Tanenbaum Solution Allows multiple philosophers to eat at the same time.
import threading 
import time
import random

NumPhilosophers  = 5
def LEFT (i): 
    return (i-1) % NumPhilosophers
def RIGHT (i):
    return (i+1) % NumPhilosophers
Thinking = 0
Hungry   = 1
Eating   = 2
# Binary Semaphore can be Initialised with a value of 1 or 0. threading.Lock() 
mutex = threading.Semaphore(1) 
s = [threading.Semaphore(1) for n in range(NumPhilosophers)]
# Initially all are thinking
state = [Thinking] * NumPhilosophers
# Pickup and Putdown stand for acquire and release of the semaphore/Locks
def pickUp(sem): 
    sem.acquire()
def putDown(sem):   
    sem.release()
# Sleep Random Function
def sleep_between(min, max):
    time.sleep(min)
    time.sleep(random.random()*(max-min))

#  The Philosopher Thread
def philosopher(i):
    
    for o in range(20):
        think(i)
        pick_Chopsticks(i)
        eat(i)
        drop_Chopsticks(i)
# Thinking Function
def think(i):
    
    print("Philosopher %d is Thinking" % i)
    sleep_between(0.5, 2.0)

# Eat Function
def eat(i):

    # print("Philosophers %d is Eating" % i)
    print_eaters()
    sleep_between(0.2, 1.0)

def checkAvailability(i):
#   Check the availability of the Left and Right Chopstick
    if (state[i]     == Hungry and
        state[LEFT(i)]  != Eating and
        state[RIGHT(i)] != Eating):
    # Tanenbaum proposed this solution that if the philosopher is hungry and both of its neighbors are not eating, then he can start eating.
        state[i] = Eating
        putDown(s[i])     

def pick_Chopsticks(i):
    # mutex.acquire()
    pickUp(mutex)
    state[i] = Hungry
    # If the Philosopher attempts to pick up a chopstick when it is already held by another philosopher, then the philosopher will wait until the other philosopher has finished using the chopstick.
    # This means if he attempts to Pick the Chopstick we can label him Hungry
    print("Philosopher %d  Is Hungry" % i)
    checkAvailability(i)
    # mutex.release()
    putDown(mutex)
    pickUp(s[i])  

def drop_Chopsticks(i):
    # mutex.acquire()
    pickUp(mutex)
    state[i] = Thinking
    checkAvailability(LEFT(i))
    checkAvailability(RIGHT(i))
    # mutex.release()
    putDown(mutex)

def print_eaters(): 

    state_names = "THE"
    # mutex.acquire()
    pickUp(mutex)

    ss = [state_names[state[i]] for i in range(NumPhilosophers)]
    print("Current States of All Philosophers: %s" % " ".join(ss))
    ss = [str(i)
        for i in range(NumPhilosophers)
        if state[i] == Eating]
    count = len(ss)
    # Error Handling block this is not Possible
    if count > 2:
        print("ERROR: more than Two Philosophers eating!")
    if count > 0:
        print("The current Eaters: %s" % " ".join(ss))
    # mutex.release()
    putDown(mutex)

def main():

    print("Starting with %d philosophers" % NumPhilosophers)

    putDown(mutex)

    threads = [threading.Thread(target=philosopher, args=(i,))
          for i in range(NumPhilosophers)]
    # Start all threads
    for thread1 in threads:
        thread1.start()
    # Wait for all threads to finish
    for thread1 in threads:
        thread1.join()
    
if __name__ == '__main__':

    main()