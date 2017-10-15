class Button : public ModuleD {
public:
	Button(int pin) : ModuleD(pin, INPUT) {
		lastState = LOW;
		currentState = LOW;
		pressedState = HIGH;

		lastDebouncedState = 0;
		currentDebouncedState  = 0;
		debounceTimerStartTime = 0;
		debounceDelay = 30;

		pressed = false;
		released = true;

		changed = false;
		justPressed = false;
		justReleased = false;
		pressCount = 0;
		releaseCount = 0;

		doubleClickDelay = 400; 
		holdDelay = 1000; 

		pToggleFlag = 0; //starts in off
		rToggleFlag = 1; //starts in off

		lastPressTime = 0;
		currentPressTime = 0;
		lastReleaseTime = 0;
		currentReleaseTime = 0;
	}
	
	bool onPress() {
		if (justPressed) {
			justPressed = false;
			return true;
		}
		return false;
	}
	bool onRelease() {
		if (justReleased) {
			justReleased = false;
			return true;
		}
		return false;
	}
	bool onChange(){
		if (changed) {
			changed = false;
			return true;
		}
		return false;
	}
	bool onDoubleClick(void)  { return (justReleased && (currentReleaseTime - lastReleaseTime) <= doubleClickDelay); }
	bool isHold(void)  { return pressed && (currentTime - currentPressTime) > holdDelay; }
	void listen() {
		currentTime = CURRENT_TIME;
		currentState = getState();

		if (currentState != lastState) {
			debounceTimerStartTime = currentTime;
		} else if (debounceTimerStartTime > 0 && (currentTime - debounceTimerStartTime) > debounceDelay) { //debounced
			debounceTimerStartTime = 0;
			lastDebouncedState = currentDebouncedState;
			currentDebouncedState = currentState;
			
			if (currentDebouncedState == pressedState) {
				pressed = true;
				released = false;
				justReleased = false;
			} else {
				pressed = false;
				released = true;
				justPressed = false;
			}

			if (lastDebouncedState != currentDebouncedState) {
				changed = true;
			} else {
				changed = false;
				justPressed = false;
				justReleased = false;
			}

			if (changed) {
				if (pressed) {
					justPressed = true;
					pressCount++;
					lastPressTime = currentPressTime;
					currentPressTime = currentTime;
					justReleased = false;
				} else if (released) {
					justPressed = false;
					justReleased = true;
					releaseCount++;
					lastReleaseTime = currentReleaseTime;
					currentReleaseTime = currentTime;
				}
			}
		}

		//wrap up the funtion
		lastState = currentState;
	}
protected:
	bool pressedState; //HIGH == pressed (1) or LOW == pressed (0)

	bool lastState;
	bool currentState;

	bool lastDebouncedState;
	bool currentDebouncedState;
	unsigned long int debounceTimerStartTime;
	unsigned int debounceDelay;

	bool pressed;
	bool released;

	bool changed;
	bool justPressed;
	bool justReleased;
	unsigned int pressCount;
	unsigned int releaseCount;


	unsigned int doubleClickDelay;
	unsigned int holdDelay;

	bool pToggleFlag;
	bool rToggleFlag;

	unsigned long int lastPressTime;
	unsigned long int currentPressTime;
	unsigned long int lastReleaseTime;
	unsigned long int currentReleaseTime;

	unsigned long int currentTime;
};
