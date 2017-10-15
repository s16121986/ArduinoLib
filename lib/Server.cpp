
#define STATE_AVAILABLE     1
#define STATE_ENABLED       2
#define STATE_ON            4

namespace Server{
	void send(byte pckg, byte id, byte param, byte data) {
		Serial.write(pckg);
#ifdef DEBUG_MODE
			Serial.print(id);
			Serial.print(" ");
			Serial.print(param);
			Serial.print(" ");
			Serial.print(data);
			Serial.println(";");
#else
			Serial.write(id);
			Serial.write(param);// == 0 ? 255 : param
			Serial.write(data);
			Serial.write(10); //NL
#endif
	}
	void sendState(byte id, byte state, byte data = 0) { send(60, id, state, data); }
	void sendData(byte id, byte data) { sendState(id, STATE_AVAILABLE | STATE_ENABLED, data); }
	class State{
	public:
		byte id;
		byte state;
		byte data;
		State(byte id, byte state = 3, byte data = 0) {
			this->id = id;
			this->state = state;
			this->data = data;
		}
		//State &operator+=( byte value ) { this->state |= value;send();return *this; }
		State &operator|=( byte value ) { this->state |= value;send();return *this; }
		//State &operator-=( byte value ) { this->state ^= value;send();return *this; }
		State &operator^=( byte value ) {
			if (state & value)
				this->state ^= value;
			send();
			return *this;
		}
		bool operator==( byte value ) { return this->state & value; }
		bool operator!=( byte value ) { return ~this->state & value; }
		void enable() { this->state |= STATE_ENABLED; }
		void disable() { this->state ^= STATE_ENABLED; }
		bool isEnabled() { return this->state & STATE_ENABLED; }
		void high() { *this |= STATE_ON; }
		void low() { *this ^= STATE_ON; }
		bool isHigh() { return this->state & STATE_ON; }
		bool isLow() { return ~this->state & STATE_ON; }
		void set(byte state, byte data) {
			this->data = data;
			this->state |= state;
			send();
		}
		void setData(byte data) { this->data = data;send(); }
		void send() { Server::sendState(id, state, data); }
	};
}
