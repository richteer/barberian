# barberian
An implementation of the Barber Shop Problem as defined [here](http://web2.clarkson.edu/class/cs444/cs444.sp2015/assignments/sync/)
Yes, the name is an intentional misspelling.

# Usage
Run the program an enjoy the lovely output.
The following options are supported for modifying your barber shop experience.
- `-t <time>` - Time in seconds it takes for each barber to process a customer
- `-b <number>` - Number of barbers that exist
- `-w <max waiting>` - Maximum number of customers that can wait
- `-c <number>` - Number of customers that will enter the barber shop
- `-d <delay>` - Number of seconds in between customer entries
- `-v <variance>` - Random range to modulate the delay specified by `-d`

# Synchronization Scheme
The general approach to this problem was to spawn a thread for each customer.
Each thread then waits on a semaphore that is initialized to the number of barbers.
Thus, the "barbers" are active only when one of the customer threads is active.
Furthermore, the number of customers waiting in the staging area is determined by the semaphore value.
Customers enter at a varying interval and will immediately wait on the semaphore, indicating that they are in the staging area.
Currently, the maximum number of customers is unbounded, as Linux's implementation of semaphores returns only 0 for the value, rather than the negative value.
Thus, implementation of a waiting customer count is more involved, thus left unimplemented.

In summary, the entire queue for the customers is implemented as the queue for the semaphore.
No other locks are used, and the barbers themselves are "virtual"; there is no dedicated resource or thread for them specifically.
The barbers instead are the critical section that exists inside the customer thread.
