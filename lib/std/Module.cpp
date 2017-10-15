//using ::NSTrigger::Action;
using namespace Enum;

class Module{
protected:
	uint8_t mode;
	bool disabled;
	//virtual void setup();
public:
	uint8_t id;
	Module() {}
	Module(uint8_t argPin, uint8_t mode) {
		this->mode = mode;
		id = argPin;
		disabled = false;
	};
	virtual bool writeOnly() {return false;}
	virtual void loop() {
		//if (tDisabled.loop()) enable();
	}
	/*virtual int command(Action &action) {
		if (action.is("enable")) {enable();return 1;}
		//else if (status != DEVICE::ENABLED) {return 0;}
		else if (action.is("disable")) {disable();return 1;}
		return 0;
	}*/
	virtual void enable() { disabled = false; }
	virtual void disable(unsigned long msec = 0) {
		disabled = true;
		//if (msec > 0) tDisabled.start(msec);
	}
	bool isEnabled() { return !disabled; }
	int getMode() { return mode;}
	int getId() { return id;}
protected:
};