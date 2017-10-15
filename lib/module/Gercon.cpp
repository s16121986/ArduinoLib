class Gercon : public ModuleD{
public:
	Gercon(int pin): ModuleD(pin, INPUT) {
		lastState = 0;
		currentState = 0;
		changed = false;
	}
	void listen() {
		currentState = getState();
		if (currentState != lastState) {
			changed = true;
			lastState = currentState;
		}
	}
	bool onChange() {
		if (changed) {
			changed = false;
			return true;
		}
		return false;
	}
private:
	bool lastState;
	bool currentState;
	bool changed;
};
