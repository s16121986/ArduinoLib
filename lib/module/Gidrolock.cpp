class Gidrolock{
public:
	Gidrolock(int pinPower, int pinOut, bool flagOpen = false) {
		this->pinPower.init(pinPower, OUTPUT);
		this->pinOut.init(pinOut, OUTPUT);
		this->flagOpen = flagOpen;
		timerOff.set(15000);
	}
	void listen() { if (timerOff.onExpire()) off(); }
	void open() {
		pinPower.write(HIGH);
		pinOut.write(LOW);
		timerOff.start();
		flagOpen = true;
	}
	void close() {
		pinPower.write(HIGH);
		pinOut.write(HIGH);
		timerOff.start();
		flagOpen = false;
	}
	void off() { pinPower.write(LOW);pinOut.write(LOW); }
	bool getState() { return flagOpen; }
private:
	PinD pinPower;	
	PinD pinOut;
	Timeout timerOff;
	bool flagOpen;
};
