class Light{
public:
	void setup() {
		r.off();
	}
	void listen() {
		b.listen();
	}
	void loop() {
		if (b.onPress()) {
			r.toggle();
		}
	}
	
	void setButton(Button b) {
		
	}
protected:
	
};
