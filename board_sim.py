import time
import paho.mqtt.client as mqtt
import json
from math import sin
from random import randint

ts_start = time.time()

def on_connect(client, userdata, flags, reason_code, properties):
    print("CONNECTED:", reason_code)

client = mqtt.Client(
    mqtt.CallbackAPIVersion.VERSION2,
    client_id="debug-client"
)

client.on_connect = on_connect

client.connect("localhost", 1883, 60)

client.loop_start()
time.sleep(2)

def gen_data():
    time_curr = ts_start - time.time()
    return (sin(time_curr/100)+1)*50 + 100 + randint(-10, 10)

while True:
    
    data = {
        "air_quality" : gen_data()
    }
    data_str = json.dumps(data)
    result = client.publish("DATA", data_str, qos=1)
    print("publish rc:", result.rc)
    time.sleep(3)

client.loop_stop()
client.disconnect()