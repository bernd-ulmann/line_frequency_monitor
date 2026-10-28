# A simple power line frequency monitor
Due to the "Energiewende", the European power grid's frequency got much more volatile, 
compared to one or two decades ago. In earlier times, the 50 Hz frequency could be 
considered as stable enough to directly drive clocks with synchronous motors from mains.
Doing something like this nowadays is a recipe for at least very bad time-keeping as
the frequency deviates quite considerably from the desired 50 Hz over the days. 

This little Arduino based project implements basically a reciprocal counter to determine
the duration of a single mains period. It requires an Arduino Uno, a cheap two line
LC-display, and a little circuit for powering the Arduino and deriving an interrupt 
signal based on the mains signal. 
