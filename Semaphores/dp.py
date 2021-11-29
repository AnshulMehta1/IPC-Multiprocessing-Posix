
# This solution consists of giving each philosopher one of three states (thinking, hungry or eating).

# PHILOSOPHERS = 5
# state = ['thinking'] * PHILOSOPHERS
# sem = [Semaphore(0) for _ in range(PHILOSOPHERS)]
# mutex = Semaphore(1)
# sem indicates whether a philosopher can start eating or not.
# mutex is used so that no two philosophers may access the pickup or putdown list at the same time.
# The state list is used to know the state of each philosopher.
# A philosopher will only eat if its neighbors are not eating
import threading 
import time
import random

N  = 5
def LEFT  (i): 
    return (i-1) % N
def RIGHT (i):
    return (i+1) % N
Thinking = 0
Hungry   = 1
Eating   = 2

mutex = threading.Semaphore(1) 
s = [threading.Semaphore(1) for n in range(N)]
state = [Thinking] * N

def pickUp(sem): sem.acquire()
def putDown(sem):   sem.release()

def sleep_between(min, max):
    
    time.sleep(min)
    time.sleep(random.random()*(max-min))
    
def philosopher(i):
    
    for o in range(10):
        think(i)
        take_forks(i)
        eat(i)
        put_forks(i)

def think(i):
    
    print("phil %d THINKING" % i)
    # sleep_between(0.5, 2.0)

def eat(i):

    print("phil %d EATING" % i)
    print_eaters()
    # sleep_between(0.2, 1.0)

def test(i):
  
    if (state[i]     == Hungry and
        state[LEFT(i)]  != Eating and
        state[RIGHT(i)] != Eating):
    
        state[i] = Eating
        putDown(s[i])     

def take_forks(i):

    pickUp(mutex)
    state[i] = Hungry
    print("phil %d HUNGRY" % i)
    test(i)
    putDown(mutex)
    pickUp(s[i])  

def put_forks(i):

    pickUp(mutex)
    state[i] = Thinking
    test(LEFT(i))
    test(RIGHT(i))
    putDown(mutex)

def print_eaters(): 

    state_names = "THE"
    
    pickUp(mutex)

    ss = [state_names[state[i]] for i in range(N)]
    print("states: %s" % " ".join(ss))
    ss = [str(i)
        for i in range(N)
        if state[i] == Eating]
    c  = len(ss)
    if c > 2:
        print("ERROR: more than one phil eating!")
    if c > 0:
        print("eaters: %s" % " ".join(ss))
    putDown(mutex)

def main():

    print("MAIN: starting with %d philosophers" % N)

    putDown(mutex)

    tt = [threading.Thread(target=philosopher, args=(i,))
          for i in range(N)]
    for t in tt:
        t.start()
    for t in tt:
        t.join()
    
if __name__ == '__main__':

    main()
