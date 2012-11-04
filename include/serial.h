
struct serial_device {
	void (*write_char)(char c);
};

struct serial_device *active_console;
