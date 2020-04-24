Frequency counter Command Line Interface
========================================
Brief description of the serial commands that accepts the frequency counter.

The frequency counter communicates with PC via serial.
A USB-Serial converter is needed in order to make serial communications.

The configuration of serial interface is standard:
  * 1 initial start bit
  * 8 data bits
  * 1 stop bit at the end
  * 115200 bauds

Every command line must be terminated with new line character ('\n' or 0x0A).
Other characters like carriage return ('\r' or 0x0D) will be ignored.

Outputs
-------

<dl>

<dt>output time on</dt>
<dd>Enable printing of the duration of the sampling period.</dd>

<dt>output time off</dt>
<dd>Disable printing of the duration of the sampling period.</dd>

<dt>output pulses on</dt>
<dd>Enable printing of counted pulses during the sampling period.</dd>

<dt>output pulses off</dt>
<dd>Disable printing of counted pulses during the sampling period.</dd>

<dt>output longfreq on</dt>
<dd>Enable printing of average frequency of last 10 readings 
    with one digit of resolution added.</dd>

<dt>output longfreq off</dt>
<dd>Disable printing of average frequency.</dd>

<dt>output period on</dt>
<dd>Enable printing of period instead of frequency.</dd>

<dt>output period off</dt>
<dd>Disable printing of frequency instead of period.</dd>

<dt>output phase on</dt>
<dd>Enable printing of time phase between 2 inputs. 
    A minimal phase of 250us is needed between the inputs.</dd>

<dt>output phase off</dt>
<dd>Disable printing of phase between 2 inputs.</dd>

</dl>


Inputs
------

<dl>

<dt>input ch A</dt>
<dd>Activate frequency measure in channel A and switch off channel B.</dd>


<dt>input ch B</dt>
<dd>Activate frequency measure in channel B and switch off channel A.</dd>


<dt>input ch AB</dt>
<dd>Activate frequency measure in both channel A and channel B.</dd>


<dt>input ch</dt>
<dd>Return actual active channels.</dd>


<dt>input ctmu on</dt>
<dd>Enable measurement of frequency with one digit more resolution.
    The measurement is developed with the charge of capacitor 
    (Charge Time Measurement Unit).</dd>

<dt>input ctmu off</dt>
<dd>Disable measurement of frequency with CTMU.</dd>

<dt>input ctmu</dt>
<dd>Return the actual value of ctmu measurement.</dd>


<dt>input fast on</dt>
<dd>Enable fast measurement of frequency (gate time of 0.1 second).</dd>

<dt>input fast off</dt>
<dd>Disable fast measurement of frequency (gate time of 1.0 second).</dd>

<dt>input fast</dt>
<dd>Return the actual value of fast measurement.</dd>


<dt>input zcd on</dt>
<dd>Enable ZCD input instead of Input A.
    The ZCD (Zero Cross Detect) input detects zero crossing of 
    sinusoidal signals like pure audio tones.</dd>


<dt>input zcd off</dt>
<dd>Disable the ZCD input and connect the Input A.</dd>


Calibration
-----------

<dl>

<dt>cal read</dt>
<dd>Read calibration value in PPB (Parts Per Billion).
  Show the calibration value in RAM (value currently used)
  and the calibration value in EPROM (value used after power on).
</dd>


<dt>cal write [number]</dt>
<dd>Writes a new calibration value to calibration variable.</dd>


<dt>cal save</dt>
<dd>Save the actual value of calibration in Flash memory, so this 
  value will be readed after next reset or power on.</dd>


<dt>cal auto on</dt>
<dd>Switch on the autocalibration mode. 
  In this mode the frequency counter changes the calibration value 
  so that the reading is exactly 1Hz or 10MHz.
  
  The frequency counter detects automatically the frequency measured
  and only responds to frequencies near 1Hz or near 10MHz.
  This calibration value in maintained in RAM memory. If you want
  to make this value fixed, use the "cal save" command</dd>

  
<dt>cal auto off</dt>
<dd>switch off autocalibration mode.</dd>


<dt>cal auto</dt>
<dd>Return the actual value of autocalibration mode.</dd>


</dl>


Reset
-----
<dl>
<dt>reset</dt>
<dd>Reset frequency counter options and counters.</dd>
</dl>


Version
-------
<dl>
<dt>version</dt>
<dd>Shows the version date of the firmware.</dd>
</dl>

