import json
from pymongo import MongoClient
from kafka import KafkaConsumer

# mongo =====
## Connect
cliente = MongoClient('mongodb://stagioptr:ipbl2019@localhost:27017/')

## Selecionando um Banco
banco = cliente.stagioptr

## collection
album = banco.feeding

#kafka======
consumer = KafkaConsumer('feeding')

print('Iniciando Consumer Feeding!')

for message in consumer:
    assert isinstance(message, object)
    mjson = json.loads(message.value)
    if type(mjson) is dict:
        print(mjson)
        documento_id = album.insert_one(mjson).inserted_id