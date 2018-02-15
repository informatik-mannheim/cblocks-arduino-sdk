unit_run:
	pio run -d test/unit -t upload; pio device monitor -b 115200

unit_build:
	pio run -d test/unit

integration_run:
	pio run -d test/integration -t upload; pio device monitor -b 115200

integration_build:
	pio run -d test/integration
