unit_run:
	pio run -d test/unit -t upload; pio device monitor -b 115200

unit_build:
	pio run -d test/unit

integration_run:
	pio run -d test/integration -t upload; pio device monitor -b 115200

integration_build:
	pio run -d test/integration

temperature_build:
	pio run -d examples/temperature/src

temperature_run:
	pio run -d examples/temperature/src -t upload; pio device monitor -b 115200

temperature_test:
	pio run -d examples/temperature/tests -t upload; pio device monitor -b 115200

neopixel_build:
	pio run -d examples/neopixel/src

neopixel_run:
	pio run -d examples/neopixel/src -t upload; pio device monitor -b 115200

neopixel_test:
	pio run -d examples/neopixel/tests -t upload; pio device monitor -b 115200
