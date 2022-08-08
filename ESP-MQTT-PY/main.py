import network
import time
from machine import Pin
from umqtt.simple import MQTTClient

led = Pin(2, Pin.OUT)
led.value(1)


## Activate wireless AP
sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)

print("Wireless station active: " + str(sta_if.active()))

print("Wireless station connected: " + str(sta_if.isconnected()))

wlan = network.WLAN(network.STA_IF)


def do_connect():
    wlan.active(True)
    if not wlan.isconnected():
        print('connecting to network...')
        wlan.connect("Agartha", "12345678")
        while not wlan.isconnected():
            pass
    print('network config:', wlan.ifconfig())
    led.value(0)
    
def publish(server="172.20.10.2"): # Add router's IP address
    c = MQTTClient("umqtt_client", server)
    c.connect()
    c.publish(b"foo_topic", b"hello")
    c.disconnect()
    
do_connect()
  


while True:
    
    
    print("Moi")
    try:
        publish()
    except:
        print("Did not publish on MQTT")
        0
    print(wlan.isconnected())
    time.sleep(1)
    
    
    