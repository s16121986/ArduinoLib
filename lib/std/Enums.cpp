namespace Enum{
	namespace DEVICE{
		enum TYPE {
			BUTTON = 1,
			LED = 2
		};
		enum STATUS{
			ENABLED = 1,
			DISABLED = 2,
			BROKEN = 3
		};
	}
	namespace ERROR{
		enum COMMAND{
			DATA_INVALID = -1,
			DEVICE_NOT_FOUND = -2,
			COMMAND_NOT_FOUND = -3
		};
	}
}