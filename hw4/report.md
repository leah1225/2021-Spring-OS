<h1 align = "center">Hw4 Report</h1>

### Q1-7.1

####(a)

- **mutual exclusion:** only one car can occupy an intersection at a time.

- **hold and wait:** cars can hold an intersection while waiting in a line for access to the next intersection.
- **circular wait:** there are four lines of cars, each line is waiting for the line in front of them, thus form a circular as it shown on the figure.
- **no preemption:** cars can't be removed from where they are in the traffic flow, the only way is to move forward.

#### (b)

- No car can hold an intersection and wait for access to the next intersection, which means that no car can stay in the intersectionD



### Q2-7.3

The CPU scheduler plays as the short-term scheduler, which will select a process from the ready queue and give the control of CPU to that selected process. 

Deadlock will occur when either thread_one or thread_two is able to acquire only one lock before the other thread acquires the second lock.

On the other hand, if either thread_one or thread_two is able to acquire both locks before the other thread is schedule, then deadlock will not occur.



### Q3-7.13

#### (a)

$Available = <3, 3, 2, 1>$

$Need = P_0 <2,  2,  1,  1>$

​			  $P_1 <2,  1,  3,  1>$

​			  $P_2 <0,  2,  1,  3>$

​			  $P_3 <0,  1,  1,  2>$

​			  $P_4 <2,  2,   3,  3>$

- Pick $P_0$ first, since it is the only one that  <= Available

  After $P_0$ is finished, $Available = <3, 3, 2, 1> + <2, 0, 0, 1> = <5, 3, 2, 2>$

- Then pick $P_3$, after $P_0$ is finished, $Available = <5, 3, 2, 2> + <3, 1, 2, 1> = <6, 6, 3, 4>$

- Like wise, pick $P_4$, and then $P_1$, and then $P_2$

$Safe$ $sequence = <P_0, P_3, P_4, P_1, P_2>$

#### (b)

- Step 1: $Request = (1, 1, 0, 0)  \le  Need = (2, 1, 3, 1)$

- Step 2: $Request = (1, 1, 0, 0)  \le  Available = (3, 3, 2, 1)$

- We can find a $Safe$ $sequence = <P_0, P_3, P_4, P_1, P_2>$ after we pretend that this request has been fulfilled.

  **The request can be granted immediately.**

#### (c)

- Step 1: $Request = (0, 0, 2, 0)  \le  Need = (2, 2, 3, 3)$

- Step 1: $Request = (0, 0, 2, 0)  \le  Available = (3, 3, 2, 1)$

- We can not find a $safe$ $sequence$ after we pretend that this request has been fulfilled, since $Available = (3, 3, 0, 1)$

  $Need = P_0 <2,  2,  1,  1>$

  ​			   $P_1 <2,  1,  3,  1>$

  ​			   $P_2 <0,  2,  1,  3>$

  ​			   $P_3 <0,  1,  1,  2>$

  ​			   $P_4 <2,  2,   1,  3>$

  $Available < Need$, none of the $Need$ can be selected.

  **The request can't be granted immediately.**