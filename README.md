# XMC4500 PWM Example
This is an simple XMC4500 Barebone PWM Example which use the CCU4 in Edge Aligned Mode<br />
The PWM duty cycle can change over the Compare Value.<br />
    => DC = 1 - Compare-Value / (Period-Value +1)<br />
The PWM Frequency can change over the Period Value.<br />
    => T  = Period-Value + 1<br />
    
The following example show a pwm with a duty-cycle from 20% and a pwm Frequency from 1kHz. <br /><br />

Calculating the Period-Value: <br />
Period-Value = (10E-3/16,666ns) - 1 <br /><br />
Calculating the Compare-Value: <br />
Compare-value = Period-value - (Period-value * 0,20) <br />


The following picture shows the Output on P1.3 <br />
    



![alt text](https://cloud.githubusercontent.com/assets/11082084/6355945/3979d322-bc5a-11e4-9414-2d4ba341b2a7.png)

