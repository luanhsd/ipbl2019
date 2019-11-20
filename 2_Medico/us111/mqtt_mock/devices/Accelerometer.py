from datetime import datetime
import random
from devices import BaseDevice

class Accelerometer(BaseDevice.BaseDevice):
  def __init__(self, uuid, range_min, range_max, broker_info, ue):
    super(Accelerometer, self).__init__(uuid, range_min, range_max, ue)
    super().configure(broker_info)

  def format_message(self, kwargs):
    msg = {
      'deviceid': self.uuid,
      'time': datetime.today().strftime('%Y%m%d%H%M%S%f'),
      'value': kwargs['value'],
      'unit': kwargs['ue'],
    }
    if random.getrandbits(1) == 1:
      del msg['unit']
    return msg

  def publish(self):
    value = super().get_value()
    super().publish(value, self.format_message)