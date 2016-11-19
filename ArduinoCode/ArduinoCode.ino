/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 * 
 * 
 * http://stefanjones.ca/blog/arduino-leonardo-remote-multimedia-keys/
 * 21010745 - off
 * 1237685689 - minus volume
 * 1124205877 - plus volume
 * 241965117 - rewind
 * 2665507385 - forward
 * 389208477 - play
 */

#include <IRremote.h>

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  irrecv.enableIRIn(); // Start the receiver
  Keyboard.begin();
}

void loop() {
  if (irrecv.decode(&results))
  {   
    if (results.value == 21010745) //Off
    {
      Remote.mute();
      delay(300);
    }
    if (results.value == 1237685689) //minus volume
    {
      Remote.decrease();
    }
    if (results.value == 1124205877) //plus volume
    {
      Remote.increase(); 
    }
    if (results.value == 241965117) //rewind
    {
      Remote.previous();
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_LEFT_ARROW);
    }
    if (results.value == 2665507385) //forward
    {
      Remote.next();
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_RIGHT_ARROW);
    }
    if (results.value == 389208477) //play
    {
      Remote.pause();
      Keyboard.press(' ');
      Keyboard.releaseAll();
      delay(300);
    }
    Remote.clear();
    Keyboard.releaseAll();
    delay(100);
    irrecv.resume();// Receive the next value
  }
}
