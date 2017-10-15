class Switch : public ModuleD{
public:
	Switch(int pin): ModuleD(pin, INPUT) {}
	bool loop() {
		if (0 == led) return;
		if (getState() == HIGH) {
			if (!event) {
				event = true;
				return true;
			}
		} else {
			event = false;
		}
		return false;
	}
private:
	bool event = false;
};
