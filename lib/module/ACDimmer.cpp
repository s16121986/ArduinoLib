class ACDimmer{
public:
	ACDimmer() {
		flagAttached = false;
		flagOn = false;
		currentPower = 255;
	}
	void init(int pin, int attachPin, void (*attachFn)(), unsigned int &offDelay) {
		this->pin = pin;
		this->attachPin = attachPin;
		this->interruptPin = pinToInterrupt(attachPin);
		this->attachFn = attachFn;
		this->offDelay = &offDelay;
		pinMode(pin, OUTPUT);
		pinMode(attachPin, INPUT);
	}
	void off() {
		detach();
		digitalWrite(pin, LOW);
		flagOn = false;
	}
	void on (byte power) {
		if (power == 0) {
			off();
		} else {
			flagOn = true;
			currentPower = power;
			if (currentPower == 255) {
				detach();
				digitalWrite(pin, HIGH);
			} else {
				*offDelay = int(255 - currentPower) * 38;
				attach();
			}
		}
	}
	void on() { on(currentPower); }
protected:
	void (*attachFn)();
	int pin;
	int attachPin;
	int interruptPin;
	bool flagAttached;
	bool flagOn;
	byte currentPower;
	unsigned int *offDelay;
	void attach() {
		if (flagAttached) return;
		flagAttached = true;
		attachInterrupt(interruptPin, (*attachFn), RISING);
	}
	void detach() {
		if (!flagAttached) return;
		flagAttached = false;
		detachInterrupt(interruptPin);
	}
	
};
