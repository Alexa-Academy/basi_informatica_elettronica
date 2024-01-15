// Attenzione: questo codice funziona solo su Arduino UNO R4 (Minima o WiFi)

#include "FspTimer.h"

#define NUM_SAMPLES 1024

FspTimer sample_timer;

int samples[NUM_SAMPLES];
int idx_sample=0;

bool doPrint=false;

// callback method used by timer
void timer_callback(timer_callback_args_t __attribute((unused)) *p_args) {
  if (doPrint) 
    return;

  if (idx_sample >= NUM_SAMPLES) {
    idx_sample = 0;
    doPrint = true;
    return;
  } 

  samples[idx_sample++] = analogRead(A0);
}

bool beginTimer(float rate) {
  uint8_t timer_type = GPT_TIMER;
  int8_t tindex = FspTimer::get_available_timer(timer_type);
  if (tindex < 0){
    tindex = FspTimer::get_available_timer(timer_type, true);
  }
  if (tindex < 0){
    return false;
  }

  FspTimer::force_use_of_pwm_reserved_timer();

  if(!sample_timer.begin(TIMER_MODE_PERIODIC, timer_type, tindex, rate, 0.0f, timer_callback)){
    return false;
  }

  if (!sample_timer.setup_overflow_irq()){
    return false;
  }

  if (!sample_timer.open()){
    return false;
  }

  if (!sample_timer.start()){
    return false;
  }
  return true;
}

void printSamples() {
  for(int i=0; i<NUM_SAMPLES; ++i) {
    //Serial.println((float)samples[i]/1023.0*4.99);
    Serial.println(samples[i]);
  }

}

void setup() {
  Serial.begin(115200);
  beginTimer(16000);
}

void loop() {
  if (doPrint) {
    printSamples();
    doPrint=false;
  }
   
}
