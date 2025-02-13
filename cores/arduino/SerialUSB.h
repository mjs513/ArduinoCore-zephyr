/*
 * Copyright (c) 2024 Arduino SA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <zephyrSerial.h>

namespace arduino {

class SerialUSB_ : public ZephyrSerial {

public:
	SerialUSB_(const struct device *dev) : ZephyrSerial(dev) { }
	void begin(unsigned long baudrate, uint16_t config);
	void begin(unsigned long baudrate) { begin(baudrate, SERIAL_8N1); }

	operator bool() override;

protected:
	uint32_t dtr = 0;
	uint32_t baudrate;
	void _baudChangeHandler();
	static void _baudChangeDispatch(struct k_timer *timer);

private:
	struct k_timer baud_timer;
	bool started = false;
};
}  // namespace arduino

#if (DT_NODE_HAS_PROP(DT_PATH(zephyr_user), cdc_acm) && CONFIG_USB_CDC_ACM)
extern arduino::SerialUSB_ Serial;
#endif