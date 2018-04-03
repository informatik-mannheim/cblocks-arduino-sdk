from subprocess import call

result = call(["pio", "run", "-t", "upload"])

if result is 0:
    call(["pio", "device", "monitor", "-b", "115200"])
