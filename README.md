# XMC4500 PWM Example
This is an simple XMC4500 Barebone PWM Example which use the CCU4.
The PWM duty cycle can change over the Compare Value.
    => DC = 1 - <Compare-Value> / (<Period-Value> +1)
The PWM Frequency can change over the Period Value.
    => T  = <Period-Value> + 1 // only for Edge Aligned Mode


