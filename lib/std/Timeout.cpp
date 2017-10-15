class Timeout{
public:
	Timeout(unsigned long int msec = 1000) {
		startTime = 0;
		set(msec);
		disabled = false;
	}
	void start() { startTime = CURRENT_TIME; }
	void start(unsigned long int msec) { set(msec);start(); }
	void enable() { disabled = false; }
	void disable() { disabled = true;stop(); }
	void stop() { startTime = 0; }
	void set(unsigned long int msec) { timeout = msec; }
	bool isStarted() { return startTime > 0; }
	bool isEnabled() { return !disabled && timeout > 0; }
	virtual void tick() { stop(); }
	void update() {
		currentTimeout = CURRENT_TIME - startTime;
		if (currentTimeout > timeout) {
			tick();
		}
	}
	bool onExpire() {
		if (isStarted()) {
			update();
			return !isStarted();
		}
		return false;
	}
	unsigned long getTimeout() { return timeout; }
protected:
	bool disabled;
	unsigned long int timeout;
	unsigned long int currentTimeout;
	unsigned long int startTime;
};
class Timeinterval : public Timeout{
public:
	Timeinterval(unsigned long int msec = 1000) : Timeout(msec) { s = 0; }
	void tick() { s++;start(); }
	unsigned long getnum() { return s; }
private:
	unsigned long s;
};
Timeinterval TIMER = Timeinterval();

class AutoTimeout{
public:
	AutoTimeout() {}
	AutoTimeout(unsigned long int autoTimeout, unsigned long int delayTimeout) {
		tAuto.set(autoTimeout);
		tDelay.set(delayTimeout);
		disabled = false;
		flagOff = false;
	}
	void off() { flagOff = true;tAuto.stop(); }
	void on() { flagOff = false; }
	bool isOn() { return !flagOff; }
	bool isEnabled() { return !disabled; }
	void enable() { disabled = false;on(); }
	void disable() {
		disabled = true;
		off();
		tDelay.start();
	}
	void startAuto() { tAuto.start(); }
	bool isAuto() { return tAuto.isStarted(); }
	bool onAuto() { return tAuto.onExpire(); }
	void startDelay() { tDelay.start(); }
	void stopDelay() { tDelay.stop(); }
	bool isDelay() { return tDelay.isStarted(); }
	bool onDelay() { return tDelay.onExpire(); }
protected:
	bool disabled;
	bool flagOff;
	Timeout tAuto;
	Timeout tDelay;
};
