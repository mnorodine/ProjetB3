import machine as Pin
import onewire
import ds18x20
import time

ow= onewire.OneWire(Pin(14))
sensor = ds18x20.DS18X20(ow)
roms = sensor.scan()
print('Numéro de série ROM : ', end= '')
for el in roms[0]:
    print('{:02x}'.format(el), end='')
print()
while True:
    time.sleep(1)
    print(sensor.red_temp(roms[0]))
    
