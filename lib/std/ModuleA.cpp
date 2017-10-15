class ModuleA : public Module{
protected:
public:
	PinA A0;
	ModuleA() : Module () {}
	ModuleA(uint8_t pin, uint8_t mode) : Module(pin, mode) {
		A0.init(pin, mode);
	};
	void write(int data) { A0.write(data); }
	uint16_t read() { return A0.read(); }
};