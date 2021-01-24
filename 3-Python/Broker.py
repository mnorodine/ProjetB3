# Broker

import logging
import asyncio
from hbmqtt.broker import Broker

logger = logging.getLogger(__name__)

config ={
	'listeners':{
		'default': {
			'type': 'tcp',
			'bind': 'localhost:1883'
		}
	},
	'sys_interval': 10,
	'topic-check':{
	'enabled':False
	}
}

broker = Broker(config)

async def startBroker():
	broker.start()

if __name__ == '__main__':
	formatter = "[%(asctime)s]:: %(levelname)s :: %(name)s :: %(message)s"
	logging.basicConfig(level=logging.INFO, format= formatter)
	asyncio.get_event_loop().run_until_complete(startBroker())
	asyncio.get_event_loop().run_forever()
	

print("1")