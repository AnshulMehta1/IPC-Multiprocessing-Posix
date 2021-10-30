import random
import time
import os
import sys
import threading
import array

# Initializing the buffer size
BUFSIZE=10
# Initially the buffer has 0s
buf=[0]*BUFSIZE
# Buffer can be taken as a stack or a queue
# So we will initialize the producer and consumer index as same 0
p_index=0
c_index=0
counter=0
# Now we will need a Mutex for managing the critical section
# We will need two semaphores for managing the empty and occupied buffer
# Initially capacity available = BUFSIZE
available=threading.Semaphore(BUFSIZE)
# Initially space of Buffer occupied = 0
occupied=threading.Semaphore(0)
# Init mutex 
mutex = threading.Lock()
# For this we will have to use lock.acquire and lock.release
# Producer Class 
class Producer(threading.Thread):
    def run(self):
        global BUFSIZE,buf,p_index,c_index,counter
        global mutex,available,occupied
    # Producer Function provide a random Sleep time and a Random Entity to Produce
        i=0
        while(i<20):
            timesl =random.randrange(0,5,1)
            # ranrange --> (start,stop,step)
            time.sleep(timesl/20)
            item=random.randrange(0,1000,1)
            # Generate random Number
            # Semaphore Waiting on available 
            available.acquire()
            # Locking mutex
            mutex.acquire()
            # Placing the Produced Item in the Buffer 
            if(counter<BUFSIZE):
                buf[counter]=item
                print("Entity Produced",item)
                p_index=p_index+1
                counter+=1
            else:
                # Checks and Balances
                print("Entity skipped")
            # Sem Post like on Operation on Occupied semaphore
            occupied.release()
            mutex.release()
            i+=1


# Consumer Thread Class
class Consumer(threading.Thread):
    def run(self):
        global BUFSIZE,buf,p_index,c_index,counter
        global mutex,available,occupied
        # Item to be consumed by the Buffer
        out=-1
        k=0
        while(k<20):
            timesl =random.randrange(0,5,1)
            # ranrange --> (start,stop,step)
            time.sleep(timesl/20)
            occupied.acquire()
            mutex.acquire()
            if (counter>0):
                out=buf[counter-1]
                print("Entity Consumed" ,out)
                # Decrement the counter
                counter-=1


            mutex.release()
            available.release()
            k+=1

# Main Function
def main():
    print("Consumer Producer Question")
    threads=[]
    # Multi-Threading Approach can also be done if threads number increased
    # Initializing the Threads
    producer=[0]*6
    consumer=[0]*6
    for i in range(5):
        producer[i]=Producer()
        consumer[i]=Consumer()
    # Starting Threads
    for i in range(5):
        producer[i].start()
        consumer[i].start()
        threads.append(producer[i])
        threads.append(consumer[i])
    # Joining the Threads
    for t in threads:
        t.join()
    # program exits
    print("Exit Program")
    # After threads have been joined Terminate the Program
    sys.exit()

if __name__ == "__main__":
    main()



