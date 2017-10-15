class Relay : public ModuleD{
public:
	Relay(uint8_t pin): ModuleD(pin, OUTPUT) {
		highState = LOW;
		off();
	}
	void loop() { if (ti.onExpire()) off(); }
	void disable(unsigned long msec = 0) {
		Module::disable(msec);
		off();
	}
	void on(unsigned long msec = 0) {
		if (disabled) return;
		currentState = highState;
		setState(currentState);
		if (msec > 0) {
			ti.start(msec);
		} else {
			ti.stop();
		}
	}
	void off() {
		currentState = !highState;
		setState(currentState);
		ti.stop();
	}
	void toggle() {
		if (currentState == highState) off(); else on();
	}
	bool isOn() { return getState() == highState; }
	unsigned long getTimeout() { return ti.getTimeout(); }
private:
	Timeout ti;
	bool highState;
	bool currentState;
};
