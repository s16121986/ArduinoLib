class Dimmer : public Button{
public:
	Dimmer(int pin): Button(pin) {
		pwm = 0;
		holdDelay = 400;
	}
	void listen() {
		Button::listen();
		if (0 == pwm) return;
		if (pwm->isDimming()) {
			if (justReleased) {
				pwm->setDimming(false);
				justReleased = false;
			} else {
				pwm->listen();
			}
		} else {
			if (justReleased) {
				justReleased = false;
				pwm->toggle();
			} else if (isHold()) {
				pwm->setDimming(true);
			} else {
				pwm->listen();
			}
		}
	}
	void setPWM(PWM &p) { pwm = &p; }
private:
	PWM *pwm;
};
