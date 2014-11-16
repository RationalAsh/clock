Clock
======

I'm making a digital clock as a learning exercise. All the files/code related to it will be in this repo.


16/11/2014 - Update
====================

Made some minor changes to the code. I thought initially that the internal oscillator would be good enough
for the clock since having it really accurate was not really my goal in the first place. So even though
there was a 12MHz crystal on the dev board I was  using, I didn't use it. I kept the fuse settings at the
default values which specified that the atmega8 use the internal 1Mhz oscillator. But after testing
the clock for a bit I found that the inaccuracy in the internal oscillator was much bigger than I thought
it would be. The clock was losing a second evey couple of minutes or so. I changed the time period inside
the clock to compensate but even after quite a few attempts at "calibrating" the clock to work with the 
internal timer it was still losing a couple of seconds every hour. So I decided to use the 12MHz crystal
after all! 

Here are the new fuse settings of the atmega8:
lfuse: 0xFF
hfuse: 0xD9

I think that this will probably be the final revision of the code. I don't really plan on adding any new
features to the clock at the moment. The only thing left to do is to finish up the actual body of the
clock. And that sould be done in a couple of days. 


10/8/2014 - Update
===================

The project is coming along nicely. A lot of the initial wiring work is done. The LCD is interfaced properly with the
microcontroller and the Day of Week function is working fine. The clock even has a body now! :D 

TODO:
 * Interface buttons for changing/setting time and date
 * Cover the body in something more attractive so that it looks good

Photos of the clock:

![Image1](http://i.imgur.com/jBAIYdC.jpg)

![Image2](http://i.imgur.com/cZot5nH.jpg)