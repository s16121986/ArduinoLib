class Motion : public ModuleD{
public:
	Motion(int pin): ModuleD(pin, INPUT) {
		stateFlag = false;
	}
	void listen() {
		if (stateFlag == false && getState() == HIGH) {
			stateFlag = true;
		}
		return false;
	}
	bool onHigh() {
		if (stateFlag) {
			stateFlag = false;
			return true;
		}
		return false;
	}
private:
	bool stateFlag;
};
