class ModuleD : public Module{
public:
	PinD D0;
	ModuleD() : Module() {}
	ModuleD(uint8_t pin, uint8_t mode) : Module(pin, mode) {
		D0.init(pin, mode);
	};
	virtual void setState(uint8_t s) { D0.write(s); }
	uint16_t getState() { return disabled ? LOW : D0.read(); }
	void write(int data) { D0.write(data); }
	void setPWMMode(bool flag) { D0.setPWMMode(flag); }
	void high() { write(HIGH); }
	void low() { write(LOW); }
	bool isHigh() { return getState() == HIGH; }
};