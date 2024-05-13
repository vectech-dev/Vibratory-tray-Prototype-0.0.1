Virbatory tray 0.0.1 
==================
 

* Tray runs for 400ms in each cycle with 90% pwm.
  * 90% pwm is the minimum for the motor to start rotation.
    * Motor can continue running at 80% pwm once it reaches maximum speed.
  * The motor takes about ~400ms to reach the maximum speed.
    * Running the motor at 90% pwm for 300 ms does not move the mosquitoes as we haven't achieved the maximum speed at that point of time.
  * The mosquitoes move for about 20-25mm in each cycle. In other words, everything in the last 20-25mm section is going to fall off the vibratory tray.
  * The goal is to reduce the distance to a few mm(3-5) to make sure it is only mosquito that falls off the edge of the tray.  

----
  ## ver 0.0.2 ##

  * 100% pwm for 50ms to start the motor and speed it up.
  * 300 ms of 80% to move the mosquito.
  * The moving distance is 7-15mm.

ver 0.0.3 
----

  * 100% pwm for 50ms to start the motor and speed it up.
  * 300 ms of 70% to move the mosquito.
  * The moving distance is 1-5mm.
  * ### con: ### The moevemnt of mosquitoes is unreliable. They are riding up on the ramp and clumped up the one time I tried using these values.
