#include <Arduino.h>
#include "Nextion.h"
#include <Bounce2.h>

Bounce debouncer = Bounce();

NexDSButton dsbutton = NexDSButton(0, 1, "bt1");

NexTouch *nex_listen_list[] = {
		&dsbutton,
		NULL
};


#define BUTTON_PIN 2
char LED1 = A0;

void dsbuttonPopCallback(void *ptr){
	uint32_t value;
	dsbutton.getValue(&value);
	if(value == 1){
		digitalWrite(LED1, HIGH);
	}
	else{
		digitalWrite(LED1, LOW);
	}
}

void setup() {

	pinMode(LED1, OUTPUT);

	nexInit();
	dsbutton.attachPop(dsbuttonPopCallback, &dsbutton);

	debouncer.attach(BUTTON_PIN);
	debouncer.interval(50); // interwa³ w ms
}

unsigned long oldTime = 0;

void loop() {
	nexLoop(nex_listen_list);
	if(debouncer.update()){
		int value = debouncer.read();
		if(value == 1){
			digitalWrite(LED1, !digitalRead(LED1));
			dsbutton.setValue(digitalRead(LED1));
		}
	}
}
