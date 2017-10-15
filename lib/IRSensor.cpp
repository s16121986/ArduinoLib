class IRSensor : public ModuleD{
public:
	IRSensor(int pin): ModuleD(pin, INPUT) {
		stateFlag = false;
	}
	bool high() {
		if (getState() == HIGH) {
			if (stateFlag == false) {
				stateFlag = true;
				return true;
			}
		} else {
			if (stateFlag == true) {
				stateFlag = false;
			}
		}
		return false;
	}
private:
	bool stateFlag;
};
